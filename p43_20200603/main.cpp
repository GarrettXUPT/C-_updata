#include<iostream>
#include<mutex>
#include<thread>
#include<future>
#include<vector>

using namespace std;

/*
	一、std::async/std::future创建后台任务并返回值
		我们希望线程返回一个结果
		std::async是一个函数模板，是一个启动一个异步任务，启动后返回一个std::future对象
		启动一个异步任务，就是创建一个线程，并开始执行对应的线程入口函数，返回一个std::future对象，
		这个对象中就含有线程入口函数所返回的结果(线程返回的结果)，我们可以使用std::future对象中的成员函数get来获取结果
		future的成员函数get只能被调用一次，不能被调用多次

		std::future提供了一种访问异步操作结果的机制，这个结果可能没有办法马上拿到，但是在线程执行完毕的时候，可以得到结果
		future.wait()只是等待线程返回，并不会获取返回的结果

		我们通过额外向std::async()传递一个参数，该参数类型是std:launch(枚举)类型，达到一些特殊的目的
		1、std::launch::deferred表示线程入口函数被延迟到std::future的wait或者get调用时才会执行，在调用get以后，也没有创建子线程，
		   是在主线程中执行的mythread()入口函数
		   若在使用该参数以后不调用get也不调用wait的话，该线程就不会被执行。实际上线程都没有被创建
		2、std::launch::async，再调用async函数的时候，就会创建线程
		   在使用该标记的时候不需要get程序就会自动执行起来，但是获取不了线程的返回结果
		   std::future默认使用的就是该标记
		
	二、std::packaged_task
		类模板，模板参数是各种可调用对象，通过该类模板将各种可调用对象包装起来，方便以后作为线程入口函数来调用
		
		packaged_task包装起来的可调用对象，还可以直接调用，所以packaged_task对象也是一个可调用对象,但是此时就是使用主线程执行该可调用对象
		相当于函数调用

	三、std::promise
		类模板：作用是可以在某个线程中进行赋值，然后在其他线程中将该值取出来使用
		通过promise保存一值，在将来的某一个时刻，我们把一个future绑定到这个promise上来得到这个绑定值

*/

/*
	线程返回一个结果
*/
// 线程入口函数
int mythread(int mypar) {
	cout << "thread start" << " thread ID = " << std::this_thread::get_id() << endl;  // 打印新线程
	// 模拟操作过程,操作时间为5秒
	std::chrono::milliseconds dura(5000);
	std::this_thread::sleep_for(dura);
	cout << "thread end" << " thread ID = " << std::this_thread::get_id() << endl;  // 打印新线程
	return mypar;
}

// 使用类的成员函数作为入口函数
class A {
public:
	int funcTest(int mypar) {
		cout << mypar << endl;
		cout << "thread start" << " thread ID = " << std::this_thread::get_id() << endl;  // 打印新线程
	// 模拟操作过程,操作时间为5秒
		std::chrono::milliseconds dura(5000);
		std::this_thread::sleep_for(dura);
		cout << "thread end" << " thread ID = " << std::this_thread::get_id() << endl;  // 打印新线程
		return mypar;
	}
};

/*
	下函数是通过future的成员函数get等待子线程结束并获取子线程返回结果
*/
void test01() {
	cout << "main thread ID = " << std::this_thread::get_id() << endl;
	std::future<int> res = std::async(mythread, 20);
	cout << "contiue。。。" << endl;
	int def = 0;
	// 虽然没有使用join，但是因为get会使用到结果，所以系统会自动阻塞到这里，等待子线程结果
	cout << res.get() << endl;

	/*
		使用类的成员函数作为线程的入口
	*/
	A a;
	std::future<int> res2 = std::async(&A::funcTest, &a, 10);  // 最后一个参数为成员函数的输入
																// 这里对象的引用是为了保证同一线程中，使用的是同一个对象
	cout << res2.get() << endl;
	cout << "main thread end" << endl;
}

/*
	std::future  std::launch::deferred参数示例
*/
void test02() {
	cout << "main thread ID = " << std::this_thread::get_id() << endl;
	std::future<int> res = std::async(std::launch::deferred, mythread, 20);
	cout << "contiue。。。" << endl;
	int def = 0;
	cout << res.get() << endl;
	cout << "main thread end" << endl;
}

/*
	std::future std::launch::async参数演示
*/
void test03() {
	cout << "main thread ID = " << std::this_thread::get_id() << endl;
	std::future<int> res = std::async(std::launch::async, mythread, 20);
	cout << "contiue。。。" << endl;
	int def = 0;
	//cout << res.get() << endl;
	cout << "main thread end" << endl;
}

/*
	std::packaged_task
*/
void test04() {
	cout << "main thread ID = " << std::this_thread::get_id() << endl;
	std::packaged_task<int(int)> mypt1(mythread);  // 将mythread通过packaged_task函数包装起来
	std::thread t1(std::ref(mypt1), 12);  // 线程直接开始执行  12指的是传入的实参
	t1.join(); // 等待线程执行完毕
	std::future<int> res = mypt1.get_future();  // 可将结果与mypt1对象进行绑定
	cout << res.get() << endl;  // 因为在使用join时就将线程结果计算出来了，所以此时直接获取结果
	cout << "main thread end" << endl;
}


/*
	lambda表达式型的packaged_task应用
*/
void test05() {
	cout << "main thread ID = " << std::this_thread::get_id() << endl;
	std::packaged_task<int(int)> mypt2([](int par) {
		cout << "thread start" << " thread ID = " << std::this_thread::get_id() << endl;  // 打印新线程
		// 模拟操作过程,操作时间为5秒
		std::chrono::milliseconds dura(5000);
		std::this_thread::sleep_for(dura);
		cout << "thread end" << " thread ID = " << std::this_thread::get_id() << endl;  // 打印新线程
		return par;
	});
	std::thread t2(std::ref(mypt2), 20);
	t2.join();
	std::future<int> res2 = mypt2.get_future();
	cout << res2.get() << endl;
	cout << "main thread end" << endl;
}

/*
	packaged_task包装起来的可调用对象，还可以直接调用，所以packaged_task对象也是一个可调用对象
	这样的话，他就相当于是函数调用，并不会产生新的线程
*/
void test06() {
	cout << "main thread ID = " << std::this_thread::get_id() << endl;
	std::packaged_task<int(int)> mypt2([](int par) {
		cout << "thread start" << " thread ID = " << std::this_thread::get_id() << endl;  // 打印新线程
		// 模拟操作过程,操作时间为5秒
		std::chrono::milliseconds dura(5000);
		std::this_thread::sleep_for(dura);
		cout << "thread end" << " thread ID = " << std::this_thread::get_id() << endl;  // 打印新线程
		return par;
	});
	mypt2(105);
	std::future<int> res = mypt2.get_future();
	cout << res.get() << endl;
	cout << "main thread end" << endl;
}

/*
	容器
*/
vector<std::packaged_task<int(int)>> mytask;
void test07() {
	cout << "main thread ID = " << std::this_thread::get_id() << endl;

	std::packaged_task<int(int)> mypt2([](int par) {
		cout << "thread start" << " thread ID = " << std::this_thread::get_id() << endl;  // 打印新线程
		// 模拟操作过程,操作时间为5秒
		std::chrono::milliseconds dura(5000);
		std::this_thread::sleep_for(dura);
		cout << "thread end" << " thread ID = " << std::this_thread::get_id() << endl;  // 打印新线程
		return par;
	});

	// 将可调用对象放入容器中
	mytask.push_back(std::move(mypt2));  // 这里使用移动语义，进入容器后，mypt2就是空
	// 取出调用
	std::packaged_task<int(int)> mypt3;
	auto iter = mytask.begin();
	// 将迭代器所指向的对象移动到mypt3中
	mypt3 = std::move(*iter);
	// 去除掉拿出来的一项，后续代码不可以再使用iter
	mytask.erase(iter);
	// 直接调用容器中的元素
	mypt3(20);
	std::future<int> res = mypt3.get_future();
	cout << res.get() << endl;
	cout << "main thread end" << endl;
}

/*
	std::promise的使用
*/
void mythread2(std::promise<int>& tmpp, int calc) {  // 此时要注意的是第一个参数
	//...此处可执行一些操作
	calc++;
	// 做其他运算假设花费了5秒钟
	std::chrono::milliseconds dura(5000);
	cout << "不要慌，正在算" << endl;
	std::this_thread::sleep_for(dura);
	// 这里计算出了结果
	int res = calc;
	// 这样tmpp对象中就保存了
	tmpp.set_value(res);
}

void test08() {
	// 声明一个std::promise对象mypro,保存的值类型就是int
	std::promise<int> mypro;
	std::thread t1(mythread2, std::ref(mypro), 12); // 第二个参数是形参列表的第一个参数，第三个参数是形参列表的第二个参数
	t1.join();  // 使用thread对象，一定要让子线程等待主线程执行完毕
	// 获取结果值
	std::future<int> fu1 = mypro.get_future();  //将promise绑定到future上，使用该值
	auto res = fu1.get();
	cout << res << endl;
}


int main() {
	test08();
	return 0;
}