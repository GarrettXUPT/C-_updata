#include<iostream>
#include<future>
#include<mutex>

using namespace std;

/*
	一、原子操作std::atomic续谈
		一般的原子操作，针对于++,--,+=,&=,|=,^=是支持的，其他的可能不支持
	二、std::async深入谈
		1、参数详述
			async创建一个异步任务
			参数：std::launch::deferred[]延迟调用 以及std::launch::async强制创建一个线程
			若使用的是std::thread() 若系统资源紧张，那么可能会导致创建线程失败，那么执行创建线程代码时，整个程序可能会崩溃	
			std::async()我们不将其叫做创建线程(async可以创建线程)，我们一般叫它创建一个异步任务
			std::async与std::thread最明显的不同在于async有时并不创建新线程，而是在调用get所在线程执行
			1、若使用std::launch::deferred调用async
				会将线程执行延迟到调用get的时候进行线程的创建，这样也不创建新线程
				若在后续不调用get，那么该线程就不会被调用
			2、std::launch::async：
				强制这个异步任务在新线程上执行，系统必须创建新的线程来运行mythread入口函数，并且立即执行
			3、std::launch::async | std::launch::deferred
				这里的|就意味着调用async的行为可能是std::launch::async创建新线程并立即执行，或者是没有创建新线程并被延迟调用	
			4、不带额外的参数
				第九节课有错误，当不带任何参数的时候，默认值就是std::launch::async | std::launch::deferred；和3效果是完全一致的
				即：系统会自行决定异步(创建新线程并立即执行)还是同步方法(延迟调用)运行
		2、std::async和std::thread的区别
			若使用的是std::thread() 若系统资源紧张，那么可能会导致创建线程失败，那么执行创建线程代码时，整个程序可能会崩溃	
			std::async是创建异步任务，它可能创建线程也可能不会创建线程，并且async调用方法很容易拿到线程的返回值
			1、由于系统资源限制，若使用std::thread创建的线程太多，则可能继续创建时就会创建失败，系统就会崩溃
			2、若使用std::async，一般就不会报异常，不会崩溃，因为系统资源紧张无法创建新线程的时候，
			   std::async不加额外参数的调用就会使用延迟调用，而不会创建新线程并立即执行，若强制使用参数创建新线程，那么系统资源紧张的时候，可能崩溃
			3、一个程序里线程数量不宜超过100-200
	三、std::async不确定问题解决
		std::async不使用任何额外参数，让系统自行决定是否创建新线程
		这种写法：到底是同步还是异步就会不确定，要判断线程到底有没有被创建就可以使用std::future对象的wait_for函数
		然后判断当前线程的状态
*/

/*
	原子操作范例
*/
// 设立原子操作
std::atomic<int> g_count = 0;
void mythread() {
	for (int i = 0; i < 10000000; i++) {
		g_count++;
	}
	return;
}

void test01() {
	std::thread t1(mythread);
	std::thread t2(mythread);
	t1.join();
	t2.join();
	cout << g_count << endl;
}

/*
	std::async深入谈
*/
int mythread2() {
	cout << "mythread start threadID = " << std::this_thread::get_id() << endl;
	std::chrono::milliseconds dura(2000);
	std::this_thread::sleep_for(dura);
	return 1;
}

/*
	std::async不使用任何额外参数，让系统自行决定是否创建新线程
	这种写法：到底是同步还是异步就会不确定，要判断线程到底有没有被创建就可以使用std::future对象的wait_for函数
	然后判断当前线程的状态
*/
void test02() {
	cout << "main thread start threadID = " << std::this_thread::get_id() << endl;
	std::future<int> res = std::async(mythread2);
	//cout << res.get() << endl;
	std::future_status status = res.wait_for(std::chrono::seconds(3));  // 也可以在wait_for中传递参数3s来实现相同的效果也可以wait_for(10min)等十分钟
	if (status == std::future_status::deferred) {
		cout << "线程被延迟调用" << endl;
		cout << res.get() << endl;
	}
	else if (status == std::future_status::timeout) {
		cout << "线程执行超时" << endl;
	}
	else if (status == std::future_status::ready) {
		cout << "创建了新线程，并返回" << endl;
		cout << res.get() << endl;
	}
	cout << "main thread end" << endl;
}

/*
	若使用std::launch::deferred调用async
	会将线程执行延迟到调用get的时候进行线程的创建，这样也不创建新线程
	若在后续不调用get，那么该线程就不会被调用
*/
void test03() {
	cout << "main thread start threadID = " << std::this_thread::get_id() << endl;
	std::future<int> res = std::async(std::launch::deferred,mythread2);
	cout << res.get() << endl;
	cout << "main thread end" << endl;
}

/*
	std::launch::async：
		强制这个异步任务在新线程上执行，系统必须创建新的线程来运行mythread入口函数
*/
void test04() {
	cout << "main thread start threadID = " << std::this_thread::get_id() << endl;
	std::future<int> res = std::async(std::launch::async, mythread2);
	cout << res.get() << endl;
	cout << "main thread end" << endl;
}



int main() {
	test02();
	return 0;
}