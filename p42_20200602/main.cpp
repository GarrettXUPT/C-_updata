#include<iostream>
#include<thread>
#include<mutex>
#include<list>

using namespace std;

/*
	一、条件变量std::condition_variable/wait/notify_one
		线程A：等待一个条件满足
		线程B：向消息队列中传递消息，线程B通知线程A的时候，就是满足A条件的时候
		std::condition_variable实际上是个类，是与条件相关的一个类，等待条件达成，这个类是需要与互斥量之间配合工作的
		notify_one：只能通知一个线程

	二、notify_all
		将wait那里的线程全部唤醒
*/

/*
	数据保护案例类
*/
class A {

public:
	// 将收到的消息，入到队列的线程
	void inMsgRecvQueue() {
		for (int i = 0; i < 10000; i++) {
			cout << "inMsgRecvQueue执行，插入一个元素" << i << endl;
			/*
				加锁，保护数据
			*/			
			unique_lock<mutex> sbguard(my_mutex);
			msgRecvQueue.push_back(i);  // 玩家命令放到消息队列里面
			/*
				这里唤醒的是wait的线程，执行完这行，就会将outMsgRecQueue里面wait会被唤醒

				若outMsgRecQueue正在处理事务，而不是卡在wait那里等待唤醒，此时notify_one就会没有效果
			*/
			myCondition.notify_all();
			
		}
	}

	// 将数据从消息队列中取出的线程
	void outMsgRecQueue() {
		int command = 0;
		while (true)
		{ 
			std::unique_lock<mutex> sbguard(my_mutex);
			// 使用lambda生成可调用对象，此处的wait是用来等待条件满足，若第二个参数的返回值是false，那么wait就会解锁互斥量，并阻塞到本行
			// 该阻塞到其他线程调用notify_one()为止，若第二个参数返回的是true，那么wait直接返回
			// 若wait没有第二个参数，那么就和第二个参数返回true效果一致，程序继续执行
			// 当其他线程使用notify_one将本位置的wait状态唤醒，唤醒后，
			// 1、再次不断尝试获取互斥量锁，若获取不到，那么流程就会卡在wait这里等着获取互斥量，若获取到了，就继续执行
			// 2、此时会再此判断第二个参数是否返回true，若是则向下执行，若还是false，则会再次进入wait状态，等待被唤醒
			// 线程在wait状态时，开销较小，所以效率较高
			myCondition.wait(sbguard, [this] {
				if (!msgRecvQueue.empty()) {
					return true;
				}
				else
				{
					return false;
				}
			});
			// 流程走到这里，互斥锁一定是锁着的，否则，代码不可能执行到这里，也就是说，在这里msgRecvQueue中至少是有一条数据的
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

	thread myOutMsgObj1(&A::outMsgRecQueue, &myobja); // 第二个参数是引用，这样才能保证在线程中使用的是myobja这个对象
	thread myOutMsgObj2(&A::outMsgRecQueue, &myobja); // 第二个参数是引用，这样才能保证在线程中使用的是myobja这个对象

	thread myInMsgObj(&A::inMsgRecvQueue, &myobja);

	myOutMsgObj1.join();
	myOutMsgObj2.join();

	myInMsgObj.join();
}

int main() {
	test01();
	return 0;
}