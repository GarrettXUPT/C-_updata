#include<iostream>
#include<thread>
#include<mutex>
#include<list>
#include<atomic> 

using namespace std;

/*
	一、知识补充
		1、虚假唤醒:wait中要有第二个参数(lambda)表达式，并且lambda中要正确判断要处理的公共数据是否存在
			wait(), notify_one(), notify_all()

		2、atomic原子操作

	二、线程池
		服务器程序-》客户端，没来一个客户端，就好创建一个新线程为该客户提供服务
		1、网络游戏，2万个玩家，不可能为每个玩家都创建新线程
		2、稳定性问题：编写的代码中，偶尔创建一个线程，这种写法就不稳定
		线程池：将一堆线程弄到一起，统一管理。这种同意管理调度，循环利用的线程方式就是线程池
		在程序启动时，一次性的创建好一定数量的线程，在程序执行的过程中就不会再创建或者是销毁线程，提高了稳定性

	三、线程创建数量
		1、线程创建数量的极限问题
			2000个线程就已经是极限了，再创建线程程序就会崩溃
		2、线程创建数量的建议
			1、当采用某些技术开发程序的时候，接口提供商就会建议你创建的线程数量等于CPU的数量，遵循开发时的专业意见及指示，确保程序高效执行
			2、创建线程来完成业务的时候，一个线程就是一条执行通路，
			
*/

class A {

public:
	atomic<int> atm;
	A(){
		atm = 0;
	}

	// 将收到的消息，入到队列的线程
	void inMsgRecvQueue() {
		for (int i = 0; i < 10000; i++) {
			cout << "inMsgRecvQueue执行，插入一个元素" << i << endl;
			/*
				加锁，保护数据
			*/
			unique_lock<mutex> sbguard(my_mutex);
			msgRecvQueue.push_back(i);  // 玩家命令放到消息队列里面
			myCondition.notify_one();

		}
	}

	// 将数据从消息队列中取出的线程
	void outMsgRecQueue() {
		int command = 0;
		while (true)
		{
			std::unique_lock<mutex> sbguard(my_mutex);
			myCondition.wait(sbguard, [this] {
				if (!msgRecvQueue.empty()) {
					return true;
				}
				else
				{
					return false;
				}
			});
			command = msgRecvQueue.front();  // 返回队列第一个元素，但是不检查元素是否存在
			msgRecvQueue.pop_front();  // 移除队列第一个元素，但是不返回
			// 在这里放开锁，提高效率
			cout << "outMsgRecQueue()执行，取出一个元素" << command << endl;
			sbguard.unlock();
			// 执行一些具体的动作
		}

	}

private:
	list<int> msgRecvQueue;  // 专门用于代表玩家给发送来的命令
	mutex my_mutex;  // 创建了一个互斥量
	std::condition_variable myCondition;  // 创建一个条件变量对象
};

void test01() {
	A myobja;

	thread myOutMsgObj1(&A::outMsgRecQueue, &myobja); 
	thread myInMsgObj2(&A::inMsgRecvQueue, &myobja); 

	myOutMsgObj1.join();
	myInMsgObj2.join();
}

/*
	线程池的实现方式
*/

int main() {
	test01();
	return 0;
}