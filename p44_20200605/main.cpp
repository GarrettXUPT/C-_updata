#include<iostream>
#include<thread>
#include<future>
#include<mutex>


using namespace std;

/*
	一、std::future的其他成员函数

	二、std::shared_future
		
	三、std::atomic
		原子操作：
			可以将原子操作理解为不需要用到互斥量加锁(无锁)技术的多线程并发编程方式
			原子操作是不会被打断的程序执行片段
			原子操作的效率比加锁操作更加高

		原子操作一般都是指不可分割的操作，也就是说，这种操作状态要么完成，要么没完成，不可能出现中间状态
		使用std::atomic来代表原子操作，其实它是一个类模板，其实这个类模板是用来封装某个类型的值的

		互斥量：用来在多线程编程的时候保护共享数据：基本流程是 锁，操作共享数据，开锁
		有两个线程这两个线程对一个变量进行操作，一个线程读，一个线程写
		每一条简单的语句都是由很多个操作完成的，所以多线程的时候，如果操作不当，都会读到一些不可预料的中间值
		互斥量加锁是针对一个代码段(几行代码)，原子操作针对的一般都是一个变量，而不是一个代码段

		原子操作一般用来计数或者统计(累计发送出去多少个数据包)，累计收到了多少个数据包
		
		
*/



/*
	std::future的其他成员函数
*/
int mythread(int par) {
	cout << "mythread start " << "threadId = " << std::this_thread::get_id() << endl;
	std::chrono::milliseconds dura(5000);
	std::this_thread::sleep_for(dura);
	cout << "mythread end" << "threadId = " << std::this_thread::get_id() << endl;
	return par;
} 

void test01() {
	cout << "main thread start " << "threadId = " << std::this_thread::get_id() << endl;
	std::future<int> res = std::async(mythread, 10);
	cout << "continue...." << endl;
	cout << res.get() << endl;
	cout << "main thread end " << endl;
}

void test02() {
	/*
		std::future_status 枚举类型
	*/
	cout << "main thread start " << "threadId = " << std::this_thread::get_id() << endl;
	//std::future<int> res = std::async(mythread, 10);
	std::future<int> res = std::async(std::launch::deferred,mythread, 10);  // 将线程延迟到调用get时进行执行
	cout << "continue...." << endl;
	// 此处等待6秒钟
	// wait_for就是在这里等待规定的时间，等待的方式就是阻塞在这里
	std::future_status status1 = res.wait_for(std::chrono::seconds(2));

	// 若等待超时，表示线程在等待时间内并没有执行完
	if (status1 == std::future_status::timeout) {
		cout << "线程执行超时，线程还没有执行完毕" << endl;
		//cout << res.get() << endl;
	}else if (status1 == std::future_status::ready) {  // 表示线程执行完毕，成功返回
		cout << "该线程执行完毕" << endl;
		cout << res.get() << endl;
	}
	else if (status1 == std::future_status::deferred) {  // 表示该线程进行了延迟
		// 若是在async的第一个参数设置为std::launch::deferred,则本条件成立
		cout << "线程被延迟执行" << endl;
		cout << res.get() << endl;  // 若该条件成立，则该线程被延迟到调用get时进行执行，且使用的是主线程执行，并没有创建子线程
	}
	cout << "main thread end" << endl;
}

/*
	std::shared_future
	类模板，普通std::future的get函数是转移数据，而这里的std::shared_future的get函数是复制数据 
*/
void mythread2(std::future<int>& tmpp) {  // 此时要注意的是第一个参数
	cout << "mythread start " << "threadId = " << std::this_thread::get_id() << endl;
	auto res = tmpp.get();	// std::future.get函数是一个移动语义，这里只允许一个future获取到它的结果
	cout << "res = " << res << endl;
	return;
}

void mythread3(std::shared_future<int>& tmpp) {  // 此时要注意的是第一个参数
	cout << "mythread start " << "threadId = " << std::this_thread::get_id() << endl;
	auto res = tmpp.get();	// std::shared_future.get函数是一个复制语义，这里允许多个future获取结果
	cout << "first get " << res << endl;
	cout << "second get " << tmpp.get() << endl;
	cout << "third get " << tmpp.get() << endl;
	return;
}


void test03() {
	cout << "main thread start " << "threadId = " << std::this_thread::get_id() << endl;
	std::packaged_task<int(int)> mypt(mythread);
	std::thread t1(std::ref(mypt), 10);
	t1.join();

	std::packaged_task<int(int)> mypt2(mythread);
	std::thread t3(std::ref(mypt2), 100);
	t3.join();
	
	/*
		std::shared_future的第一种用法
	*/
	std::shared_future<int> res = mypt.get_future();
	std::thread t2(mythread3, std::ref(res));  // 在线程2中获取线程1的返回值
	t2.join();

	/*
		std::shared_future的第二种用法
	*/
	std::future<int> res2 = mypt2.get_future();
	std::shared_future<int> res2_s(res2.share());  // 将res2的结果移动到了res2_s中
	std::thread t4(mythread3, std::ref(res2_s));
	t4.join();
	cout << "main thread end" << endl;
}

/*
	std::atomic原子操作
*/
// 定义原子全局变量
std::atomic<int> g_count = 0;  // 封装了一个类型为int的对象的值，我们可以像操作int变量一样去操作这个原子对象
void mythread4() {
	for (int i = 0; i < 10000000; i++) {
		g_count++;  // 此处是定义的原子操作，在单次相加过程中，不会被打断
	}
}

void test04() {
	std::thread t1(mythread4);
	std::thread t2(mythread4);
	t1.join();
	t2.join();
	cout << g_count << endl;
}

/*
	布尔型原子操作
	线程退出标记，防止读写乱套
*/
std::atomic<bool> flag = false;
void mythread5() {
	std::chrono::milliseconds dura(1000);  // 建立一个1秒钟对象
	while (flag == false) {  // flag为false，则说明系统没有要求线程退出
		cout << "threadId = " << std::this_thread::get_id() << " 运行中" << endl;
		std::this_thread::sleep_for(dura);
	}
	cout << "threadId = " << std::this_thread::get_id() << " 运行结束" << endl;
}

void test05() {
	std::thread t1(mythread5);
	std::thread t2(mythread5);
	std::chrono::milliseconds dura(5000);  // 建立一个1秒钟对象
	std::this_thread::sleep_for(dura);
	flag = true;  // 使线程可以自行的运行结束,当主线程将falg修改为true以后，子线程因为条件不成立而导致运行结束
	t1.join();
	t2.join();
	cout << "程序执行完毕，退出..." << endl;
}

int main() {
	test05();
	return 0;
}