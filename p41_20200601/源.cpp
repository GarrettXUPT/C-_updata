#include<iostream>
#include<thread>
#include<vector>
#include<list>
#include<mutex>


using namespace std;

/*
第四节：创建多个线程、数据共享问题分析、案例代码
1、创建和等待多个线程
	1. 多个线程执行顺序是不确定的，这与操作系统内部对线程的调度机制有关
	2. 主线程等待子线程运行结束，才结束，最好使用join的方法，使多线程程序更加稳定
	3. 使用迭代器创建多个线程，看起来向是thread对象数组，这对我们管理大量线程很方便

2、数据共享问题分析
	1. 只读数据：安全稳定，不需要特殊的手段，直接读就可以
	2. 又读又写的数据
		最简单的不崩溃处理方法：读的时候不能写，写的时候不能读。两个线程不能同时写，八个线程不能同时读
		由于任务切换，导致程序崩溃
	3. 其他案例
		数据共享：两个窗口订一个座位的票

3、共享数据的保护案例代码
	网络游戏服务器：
		两个知己创建的线程：
			一个线程收集玩家命令，将命令数据写到一个队列中
			一个线程从队列中取出玩家发来的命令，解析，然后执行玩家需要的命令
		使用vector和list。 list按顺序插入删除的数据效率较高，vector对于随机的插入和删除效率较高

		准备用成员函数作为线程函数的方法写线程，需要代码化解决多线程数据共享问题：使用互斥量


第五节、互斥量的概念、用法、死锁演示及解决详解
1、互斥量(mutex)的基本概念
	保护共享数据，操作时，用代码将共享数据锁住，其他想操作共享数据的线程必须等待解锁，解锁之后，其他线程才能操作数据
		互斥量是一个类对象，理解成一把锁，同一时间，多个线程都可尝试使用lock()成员函数来加锁，只有一个线程可以锁定成功
	
	成功地标志是lock函数进行了返回，若没锁成功，那么线程的执行流程就会卡在lock上，不断尝试去加锁，直到成功
		
		互斥量使用要小心，少了达不到保护效果，多了还影响效率

2、互斥量的使用
	2.1 lock和unlock
		步骤：先lock加锁，操作共享数据，unlock
		lock和unlock要成对使用，有lock必然要有unlock，不应该也不允许调用一次lock确调用了多次unlock
		若不符合使用规则，则会导致程序崩溃，而且该错误是非常难排查的

		为防止开发者忘记unlock，引入一个叫lock_guard类模板，你忘了unlock，该函数会自动unlock
		lock_guard:同时取代lock和unlock
		智能指针(unique_ptr<>)，你忘记释放内存不要紧，该指针自动释放,保姆式服务

	2.2 lock_guard类模板，可以直接取代lock和unlock，也就是说，使用lock_guard之后，就再也不能使用lock和unlock

3、死锁
	生活：庄三在北京等李四，李四在深圳等张三，俩人就是死锁状态
	
	c++中：一个互斥量就是一把锁，死锁必须有两个锁，也就是两个互斥量：
		两个线程A, B
		1、线程A执行的时候，这个线程先锁锁1，锁成功，然后去lock锁2.。正要去锁lock2时，此时出现了上下文切换
		2、线程B开始执行，这个线程去锁锁2，锁成功，然后去lock锁1，
		3、此时死锁现象就产生了，线程A拿不到锁2，线程B拿不到锁1，流程都走不下去，线程A等线程B，线程B等待线程A
	
	解决方案：
		只要是加锁的顺序是一致的，就不会出现死锁

	lock()函数模板：(用来处理多个互斥量)
		一次锁住两个或者多个互斥量(至少两个)，它就不存在在多个线程中顺序问题导致死锁的风险
		若互斥量中有一个没锁住，他就在那里等所有互斥量都锁住，它才能向下走，若发现有一个锁不上，那么会释放以前的锁
		要么两个互斥量都锁住，要么两个互斥量都没锁住
		使用方式：
			lock(mutex1, mutex2...);
			相当于每一个互斥量都调用了lock 
			解锁：mutex1.unlock()
				  mutex2.unlock()

	adopt_lock：结构体对象，起到一个标记作用，表示这个互斥量已经lock，不需要在lock_guard中对对象再次进行lock了

	lock一次锁定多个互斥量，谨慎使用(建议一个一个锁
*/


/*
	共享数据
	只读的数据
*/
vector<int> g_v = { 1, 2, 3 };


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
			//my_mutex.lock();
			// 用大括号来限定lock_guard作用域
			{
				lock_guard<mutex> sbguard(my_mutex);
				msgRecvQueue.push_back(i);  // 玩家命令放到消息队列里面
			}
			
			/*
				数据写入完毕，解锁
			*/
			//my_mutex.unlock();
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

	mutex my_mutex;  // 创建了一个互斥量
	
	bool outMsgLULProc(int& command) {
		/*
			使用类对象
			lock_guard构造和函数中执行了lock()函数
			超出作用域即为return时候，析构的时候调用了unlock，
			也可以使用 大括号 来限定作用域，即为大括号里面就是lock_guard的生命周期
		*/
		lock_guard<mutex> sbguard(my_mutex);  // 对象名可自己改变
		/*
			加锁
		*/
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
		return false;
	}
};



/*
	演示死锁案例
*/
class B {
public:
	// 将收到的消息，入到队列的线程
	void inMsgRecvQueue() {
		for (int i = 0; i < 10000; i++) {
			cout << "inMsgRecvQueue执行，插入一个元素" << i << endl;

			/*
				加锁，保护数据,先锁锁1，再锁锁2
				这两个锁不一定挨着，可能会保存不同的数据块
			*/
			//lock_guard<mutex> sbguard1(my_mutex1);
			//lock_guard<mutex> sbguard2(my_mutex2);
			my_mutex1.lock();
			my_mutex2.lock();
			msgRecvQueue.push_back(i);  // 玩家命令放到消息队列里面
			/*
				数据写入完毕，解锁
			*/
			my_mutex1.unlock();
			my_mutex2.unlock();
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
	mutex my_mutex1;  // 创建了一个互斥量
	mutex my_mutex2;

	bool outMsgLULProc(int& command) {
		/*
			使用类对象
			lock_guard构造和函数中执行了lock()
			超出作用域即为return时候，析构的时候调用了unlock，也可以使用大括号来限定作用域，即为大括号里面就是lock_guard的生命周期
		*/
		//lock_guard<mutex> sbguard(my_mutex1);  // 对象名可自己改变
		/*
			加锁
			若是死锁，则先锁2，再锁1
			若是要避免死锁，那么就是先锁1，再锁2
		*/

		/*
			此处的lock可以一次锁住两个或者两个以上的互斥量(至少两个，多了不限)
			使用它的话就不会存在在多个线程中，因为所得顺序问题导致的死锁的风险
			它就是使连个互斥量都锁住，或者是两个互斥量都没锁住。若是只锁了一个，另外一个没锁成功，则立即将锁住的锁进行解锁
			它和两个unlock共同使用，也可以直接使用lock_guard
			在实际运用过程中，同时lock的情况是比较少的
		*/
		lock(my_mutex1, my_mutex2);

		/*
			此时不再调用unlock，因为在析构lock_guard时候，就会自动unlock，因为添加了adopt_lock，已经lock了，就不需要再次lock
		*/
		lock_guard<mutex> sbguard1(my_mutex1, adopt_lock);
		lock_guard<mutex> sbguard2(my_mutex2, adopt_lock);

		if (!msgRecvQueue.empty()) {
			// 若消息队列不为空
			command = msgRecvQueue.front();  // 返回队列第一个元素，但是不检查元素是否存在
			msgRecvQueue.pop_front();  // 移除队列第一个元素，但是不返回

			/*
				该函数会有两个出口，所以在每一个可能退出前都要执行unlock
			*/
			return true;
		}
		return false;
	}
};



/*
	创建和等待多个线程
*/
/*
	线程入口函数
*/
void test01(int num) {
	cout << "子线程" << num << "的创建" << endl;
	//.....也不知道干了点啥
	//cout << "子线程" << num << "的销毁" << endl;
}
void testf1() {
	cout << "主线程开始执行" << endl;
	vector<thread> mythreads;
	// 创建十个线程，每个线程都统一使用test01函数
	for (int i = 0; i < 10; i++) {
		mythreads.push_back(thread(test01, i)); // 创建并开始执行线程,线程执行顺序是不一致的
	}
	for (auto iter = mythreads.begin(); iter != mythreads.end(); iter++) {
		iter->join();  // 等待10个线程全都结束运行
	}
	cout << "主线程执行完毕" << endl;
}



/*
	共享数据
*/
/*
	打印共享数据
*/
void test02() {
	cout << "id = " << this_thread::get_id() << " 打印 = " << g_v[0] << g_v[1] << g_v[2] << endl;
}
void testf2() {
	cout << "主线程开始执行" << endl;
	vector<thread> mythreads;
	// 创建十个线程，每个线程都统一使用test01函数
	for (int i = 0; i < 10; i++) {
		mythreads.push_back(thread(test02)); // 创建并开始执行线程,线程执行顺序是不一致的
	}
	for (auto iter = mythreads.begin(); iter != mythreads.end(); iter++) {
		iter->join();  // 等待10个线程全都结束运行
	}
	cout << "主线程执行完毕" << endl;
}


/*
	共享数据的保护案例代码
*/
void test03() {
	A myobja;

	thread myOutMsgObj(&A::outMsgRecQueue, &myobja); // 第二个参数是引用，这样才能保证在线程中使用的是myobja这个对象

	thread myInMsgObj(&A::inMsgRecvQueue, &myobja);

	myOutMsgObj.join();
		
	myInMsgObj.join();
}


/*
	死锁现象演示代码
*/
void test04() {
	B myobjb;

	thread myOutMsgObjb(&B::outMsgRecQueue, &myobjb); // 第二个参数是引用，这样才能保证在线程中使用的是myobja这个对象
	thread myInMsgObjb(&B::inMsgRecvQueue, &myobjb);
	myOutMsgObjb.join();
	myInMsgObjb.join();
}


int main() {
	test04();
	system("pause");
	return 0;
}