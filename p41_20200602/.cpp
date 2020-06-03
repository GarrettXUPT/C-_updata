#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

/*
	一、设计模式概述
		设计模式：代码的写法，写法与普通写法有所不同，特点是：程序灵活，维护起来方便，为了应付大项目的开发经验和模块划分经验进行总结

	二、单例设计模式
		该设计模式使用的频率较高，
		单例：在整个可执行文件中，由某个或者某些特殊的类，属于该类的对象，只能创建一个，不可创建多个
		单例类：可以保证生成的对象只有一个

	三、单例设计模式下的共享数据问题分析
		最好在创建子线程之前，在主线程中就将单例对象创建好，调用成员函数将必要数据进行装载，后续只读即可
		面临问题：需要在自己创建的线程中创建单例对象，这种线程还可能不止一个，此时就需要成员函数进行互斥

	四、std::call_once
		这是一个函数模板，也是C++11才引入的函数，该函数的第二个参数是一个函数名
		功能是能够保证函数a只被调用一次，具备互斥量的能力，效率上比互斥量消耗的资源更少
		call_once需要与标记结合使用，这个标记是std::once_flag配合使用，这个标记是一个结构
		call_once就是通过标记来判断对应的函数a是否执行，调用call_once成功后，标记就会设置为已调用状态，后续再次使用call_once的时候，
		若标记已经被设置为已调用，那么对应的函数a就不会再被执行了
*/

/*
	单例类的创建
*/

// 加入互斥量，防止多个线程同时调用单例对象创建
std::mutex resource_mutex;

// 使用call_once解决共享数据保护问题
std::once_flag g_flag;

class MyCAS {
public:

	// 只被调用一次的函数
	static void CreatInstance() {
		m_instance = new MyCAS();
		// 当程序退出的时候会自动调用c1对象的析构函数，正好用来释放对象
		static CGarhuishou cl;
	}

	/*
		使用call_once解决共享数据保护问题
	*/
	static MyCAS* getObj() {
		// 两个线程同时执行到这里，其中一个线程成功调用call_once，使用CreatInstance创建单例对象
		// 此时g_flag就可以看做是一个锁
		std::call_once(g_flag, CreatInstance);
		return m_instance;
	}

	/*
		使用双重锁定解决共享数据保护问题
	*/
	static MyCAS* getInstance() {
		// 这种写法为双重锁定(检查),这样样可以提高效率，若判断条件成立，则表示m_instance已经被new过了
		// 这种写法如果m_instance == nullptr,不代表m_instance一定没被new过
		if (m_instance == nullptr) {
			std::unique_lock<mutex> mymutex(resource_mutex);  // 自动加锁
			if (m_instance == nullptr) {
				m_instance = new MyCAS();
				// 当程序退出的时候会自动调用c1对象的析构函数，正好用来释放对象
				static CGarhuishou cl;
			}
		}
		return m_instance;
	}

	void func() {
		cout << "测试" << endl;
	}

	/*
		使用类中套用类来释放对象
	*/
	class CGarhuishou {
	public:
		~CGarhuishou() {
			if (MyCAS::m_instance) {  // 若类中的对象不为空
				delete MyCAS::m_instance;
				MyCAS::m_instance = nullptr;
			}
		}
	};

/*
	将构造函数进行私有化
*/
private:
	MyCAS() {};

private:
	static MyCAS* m_instance;  // 静态成员变量
	
};

/*
	静态成员初始化
*/
MyCAS* MyCAS::m_instance = nullptr;

/*
	单例对象的调用
*/
void test01() {
	// 创建一个对象，返回该类对象的指针
	MyCAS* pa1 = MyCAS::getInstance();
	// 因为使用的是单例类，所以再次得到的也是第一个对象，pa1、pa2指向的是同一个对象
	MyCAS* pa2 = MyCAS::getInstance();
	pa1->func();
}

/*
	单例类中的的共享数据问题分析与解决
*/

void mythread() {
	cout << "线程开始执行了" << endl;
	MyCAS* pa = MyCAS::getInstance();  // 在这里初始化，因为两个线程共同使用一个带有单例对象的入口函数，会就可能会有问题
	cout << "线程执行完毕" << endl;
	return;
}

void test02() {

	std::thread myobj1(mythread);
	std::thread myobj2(mythread);

	myobj1.join();
	myobj2.join();
}

int main() {
	test02();
	return 0;
}