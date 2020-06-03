#include<iostream>
#include<thread>
#include<vector>
#include<list>
#include<mutex>


using namespace std;

/*
	一、使用unique_lock取代lock_guard
		unique_lock是一个类模板，工作中一般使用lock_guard就足够了，lock_guard取代了mutex的lock()和unlock()
		unique_guard比lock_guard灵活一些，但是代价是效率比较差，内存占用多一点
	
	二、unique_lock的第二个参数
		lock_guard带第二个参数 lock_guard<mutex> sbguard(my_mutex, adop_lock); 此处的adop_lock起到的是标记作用
		1、std::adop_lock
			也是进行标记，表示互斥量已经被lock(使用该参数时，互斥量已经被lock了，否则就会报异常)，标记的效果就是假设调用方线程已经有了互斥的所有权，
			也就是说已经lock成功了，通知lock_guard不需要在构造函数中lock这个互斥量了。unique_lock使用时，含义相同。
			先lock，才能使用该标记
		2、std::try_to_lock
			表示尝试使用mutex的lock进行锁定mutex，若没有锁定成功，那么也会立即返回，并不会阻塞在那里
			使用该标记的前提是不能先去lock
		3、std::defer_lock
			使用该标记的前提是自己不能先lock，否则就会报异常
			含义：不需要给mutex加锁，初始化了一个没锁的mutex
	
	三、unique_lock的成员函数，都是在defer_lock标记下
		1、lock加锁
		2、unlock解锁，当处理非共享代码的时候，就可以临时unlock，再处理非共享代码。处理完毕以后，再次调用lock即可
		   使用lock锁住的代码段越少，执行的效率越高，整个的程序运行效率就越高，也有人将锁头锁住的代码的多少称之为锁的粒度，使用粗细来描述
		   粒度细，锁住的代码较少，运算效率就高，反之运行效率就低，要尽量选择合适粗细的代码进行共享数据保护
		3、try_lock尝试给互斥量加锁，若是拿不到锁，则返回false，若拿到锁，返回true，也是不阻塞的
		4、release 返回它所管理的mutex对象指针，并释放所有权，也就是unique_lock和mutex不再有关系
		要区分：unlock和release的区别
			unlock只是解锁，并不是放弃了它和unique_lock之间的关系
			若原来mutex对象处于加锁状态，有责任接管过来并进行解锁
			std::unique_lock<mutex> sbguard(my_metux);
			std::mutex* ptx = sbguard.release();
			ptx->unlock()
	
	四、unique_lock所有权的传递
		所有权的概念：std::unique<mutex> sbguard(my_mutex); 所有权概念：sbguard对象是拥有my_mutex的
		sbguard可以将my_mutex的所有权转移给其他的unique_lock对象，所以unique_lock对象的所有权可以转移但是不能复制
		复制所有权是非法的：std::unique<mutex> sbguard2(sbguard1);  
		移动所有权是合法的：std::unique<mutex> sbguard2(std::move(sbguard1));

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
			// 此处使用unique_lock取代了lock_guard
			{	
				//lock_guard<mutex> sbguard(my_mutex);
				
				//unique_lock<mutex> sblock(my_mutex);
				
				//使用std::try_to_lock进行尝试锁定，若没有锁定也会立即返回，不会形成阻塞


				//unique_lock<mutex> sblock(my_mutex, std::try_to_lock);
				//if (sblock.owns_lock()) {  // 拿到锁
				//	cout << "执行拿到锁的操作" << endl;
				//	msgRecvQueue.push_back(i);  // 玩家命令放到消息队列里面
				//}
				//else
				//{
				//	cout << "未拿到锁，进行返回" << endl;
				//}

				/*
					使用defer_lock
					此处是没有加锁的mutex
				*/
				unique_lock<std::mutex> sbguard(my_mutex, std::defer_lock);
				// 此处调用的是unique_lock进行加锁，我们不需要关心解锁，因为unique_lock会自动解锁的
				sbguard.lock();

				// 临时将锁放开，处理非共享数据
				sbguard.unlock();
				//..........此处处理非共享数据,处理过以后，再锁上，以保证共享数据安全
				//sbguard.lock();

				/*
					使用unique_lock的try_lock函数
				*/
				if (sbguard.try_lock()) {
					msgRecvQueue.push_back(i);  // 玩家命令放到消息队列里面
				}
				else
				{
					cout << "未拿到锁" << endl;
				}

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
		// 此处使用unique_lock取代了lock_guard
		//unique_lock<mutex> sblock(my_mutex);
		//lock_guard<mutex> sbguard(my_mutex);  // 对象名可自己改变
		// 使用std::try_to_lock进行尝试锁定，若没有锁定也会立即返回，不会形成阻塞
		//unique_lock<mutex> sblock(my_mutex, std::try_to_lock);

		unique_lock<mutex> sblock(my_mutex, std::defer_lock);
		sblock.lock();

		/*
			加锁
		*/
		//my_mutex.lock();

		/*
			使用该段程序使该线程进行睡眠2s 
		*/
		/*std::chrono::milliseconds dura(2000);
		std::this_thread::sleep_for(dura);*/

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
	共享数据的保护案例代码
*/
void test01() {
	A myobja;

	thread myOutMsgObj(&A::outMsgRecQueue, &myobja); // 第二个参数是引用，这样才能保证在线程中使用的是myobja这个对象

	thread myInMsgObj(&A::inMsgRecvQueue, &myobja);

	myOutMsgObj.join();

	myInMsgObj.join();
}



int main() {
	test01();
	return 0;
}