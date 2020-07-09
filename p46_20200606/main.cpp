#include<iostream>
#include<mutex>
#include<thread>
#include<list>
#include<Windows.h>

// 定义一个开关
//#define __WINDOWSJQ_

using namespace std;

/*
	一、windows临界区
		C++中的互斥量在功能上就等于windows的临界区概念，进入临界区就像加锁一样，进入临界区以后，再对公共数据进行操作

	二、多次进入临界区试验
		在同一个线程中，windows临界区支持多次进入临界区，但是操作完共享数据以后，对应的应该要多次离开临界区
		EnterCriticalSection(&my_winsec);  // 进入临界区(加锁)
		LeaveCriticalSection(&my_winsec);	// 离开临界区(解锁)
		C++11的互斥量而言，同一个线程中，不可以多次加锁，多次解锁

	三、自动析构技术
		std::lock_guard<std::mutex> 自动加锁和解锁

	四、recursive_mutex递归的独占互斥量
		std::mutex:独占式互斥量，自己lock锁以后，别人不可以再次lock
		std::recursive_mutex:递归式独占互斥量，可以解决多次lock，允许同一个线程，同一个互斥量多次被lock，效率上要比mutex差
		若使用了多次调用，就要考虑代码是否有优化的空间，优化以后可以调用一次解决问题
		递归次数据说有限制

	五、带超时的互斥量std::timed_mutex和std::recursive_timed_mutex 
		std::timed_mutex:带超时功能的独占互斥量
			try_lock_for():等待一段时间,若等待超时还没拿到锁，流程就会继续进行
			try_lock_until():这里的参数是未来的一个时间点，在未来的时间还没到的时间内，若是拿到了锁，流程就继续进行，若时间到了没拿到锁，
							 流程也会继续进行
		std::recursive_timed_mutex：带超时功能的递归独占互斥量

*/

// 本类用于自动释放windows下的临界区，防止忘记LeaveCriticalSection导致死锁，类似于lock_guard
class CWinLock {  // 资源获取及初始化(RAII)，技术的关键就是在构造函数中构造一个资源，然后在析构函数中析构这个东西
public:
	CWinLock(CRITICAL_SECTION* pCritmp) {
		m_critical = pCritmp;  // 指针指向传递进来的临界区变量
		EnterCriticalSection(m_critical);
	}

	~CWinLock() {
		LeaveCriticalSection(m_critical);
	}

private:
	CRITICAL_SECTION* m_critical;
};

class A {

public: 

	void testfunc1() {
		std::lock_guard<std::timed_mutex> sbguard(my_mutex);
		// 干各种事情
		testfunc2();  // 在这里调用testfunc2会导致程序崩溃，因为多次进行了加锁
	}

	void testfunc2() {
		std::lock_guard<std::timed_mutex>sbguard(my_mutex);
		// 干另一些事
	}


	A() {
#ifdef __WINDOWSJQ_
	InitializeCriticalSection(&my_winsec);  // 初始化临界区
#endif // __WINDOWSJQ_
	}

	// 将收到的消息，入到队列的线程
	void inMsgRecvQueue() {
		for (int i = 0; i < 10000; i++) {
			cout << "inMsgRecvQueue执行，插入一个元素" << i << endl;
#ifdef __WINDOWSJQ_
			// 使用自动进入和离开临界区，使用这种方式多次进入临界区也没有问题
			CWinLock wlock(&my_winsec);
			//EnterCriticalSection(&my_winsec);  // 进入临界区(加锁)
			//EnterCriticalSection(&my_winsec);
			msgRecvQueue.push_back(i);
			//LeaveCriticalSection(&my_winsec);
			//LeaveCriticalSection(&my_winsec);	// 离开临界区(解锁)
#else
			//my_mutex.lock();
			//std::lock_guard<std::recursive_mutex> sbguard(my_mutex);

			std::chrono::milliseconds timeout(100);  // 100ms
			if (my_mutex.try_lock_for(timeout)) {  // 若在规定时间内拿到锁

				msgRecvQueue.push_back(i);  // 玩家命令放到消息队列里面
				my_mutex.unlock();
			}
			else  // 超时未拿到锁
			{
				std::chrono::milliseconds sleeptime(100);
				std::this_thread::sleep_for(sleeptime);
			}
			//my_mutex.unlock();
#endif // __WIDOWSJQ_

			
		}
	}

	// 将数据从消息队列中取出的线程
	void outMsgRecQueue() {
		int command;
		for (int i = 0; i < 10000; i++) {
			bool result = outMsgLULProc(command);
			if (result == true) {
				cout << "OutMsgRecvQueue()执行，取出元素" << command << endl;
				/*
					进行数据处理
				*/
			}
			else
			{
				cout << "OutMsgRecvQueue()执行，但是队列中元素为空" << endl;
			}
		}
		return;
	}

private:
	list<int> msgRecvQueue;  // 专门用于代表玩家给发送来的命令

	//mutex my_mutex;  // 创建了一个互斥量

	//recursive_mutex my_mutex;  // 使用递归式的独占互斥量

	timed_mutex my_mutex;

#ifdef __WINDOWSJQ_
	CRITICAL_SECTION my_winsec;  // 定义一个window下的临界区，非常类似于C++11中的mutex，临界区使用时必须进行初始化
#endif


	bool outMsgLULProc(int& command) {
#ifdef __WINDOWSJQ_
		EnterCriticalSection(&my_winsec);
		if (!msgRecvQueue.empty()) {
			// 若消息队列不为空
			command = msgRecvQueue.front();  // 返回队列第一个元素，但是不检查元素是否存在
			msgRecvQueue.pop_front();  // 移除队列第一个元素，但是不返回
			LeaveCriticalSection(&my_winsec);
			return true;
	}
		LeaveCriticalSection(&my_winsec);
#else
		std::lock_guard<std::recursive_mutex> sbguard(my_mutex);
		//my_mutex.lock();
		if (!msgRecvQueue.empty()) {
			// 若消息队列不为空
			command = msgRecvQueue.front();  // 返回队列第一个元素，但是不检查元素是否存在
			msgRecvQueue.pop_front();  // 移除队列第一个元素，但是不返回
			/*
				该函数会有两个出口，所以在每一个可能退出前都要执行unlock
			*/
			//my_mutex.unlock();
			return true;
		}
		//my_mutex.unlock();
#endif // __WINDOWSJQ_
		return false;
	}
};

void test01() {
	A myobja;
	std::thread myOutMsgObj(&A::outMsgRecQueue, &myobja);
	std::thread myInMsgObj(&A::inMsgRecvQueue, &myobja);
	myInMsgObj.join();
	myOutMsgObj.join();
}

int main() {
	test01();
	return 0;
}