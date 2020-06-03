#include<iostream>
#include<thread>
#include"class_obj.h"
using namespace std;

/*
第二节 线程启动、结束、创建线程的多种方法、join detach
	1、范例演示线程运行的开始与结束
		程序运行起来，生成一个进程，该进程所属的主线程开始自动运行
			1、包含头文件thread
			2、创建函数
			3、main中运行
		主线程从main函数开始执行，创建的进程，也需要从一个函数开始执行（初始函数）,函数运行完毕，就代表线程运行结束。
		一般情况下：整个进程执行完毕的标志其实是主线程是否执行完毕，若此时还有子进程没有执行完毕，那么这些子进程就会被强行结束
					要保证主线程的运行，其他线程才能正常运行

	1.1 thread是标准库中的类
		thread myobj(test01); test01是可调用对象
			1.创建了线程，线程的执行的起点(入口)test01
			2.test01开始执行

		myobj.join();
		阻塞主线程，让主线程等待子线程执行完毕，然后子线程与主线程回合，然后主线程继续向下执行
		主线程执行完毕，子线程没有执行完毕，程序是不稳定的

		一个标准的多线程程序，要保证主线程等待子线程执行完毕，才能结束，否则就会有未知后果
	
	1.2 detach()
		主线程可以提前结束，主线程不与子线程汇合，使主线程的执行不影响子线程的执行
		
		我们创建了很多子线程，使主线程逐个等待执行完毕，该种执行方法不太好
		
		使用detach之后，主线程相关的thread对象就会失去与主线程的关联,此时子线程就会进入后台运行
		这个子进程就相当于被C++运行时库接管，当子线程执行完毕后，由运行时库负责清理该线程相关的资源，驻留后台(守护线程)
		
		主线程与子线程互不影响，但是detach会使线程失去控制
		一但调用了detach就不能再使用join，否则会有异常

	1.3 joinable判断是否可以成功使用join还是detach的，返回true或者是false

	1.4 其他创建线程的手法
		其他可调用对象
			1、类对象
			2、lambda表达式


*/


/*
	初始函数
*/
void test01() {
	cout << "线程执行开始" << endl;
	/*
		主线程执行，主线程从main函数返回，整个进程执行完毕
	*/
	cout << "线程执行完毕" << endl;
}

/*
	创建进程join
*/
void test02() {
	/*
		创建一个线程,并使用join进行执行
		此时程序就有两条线程，一条子线程一条主线程，所以可以同时做两件事
	*/
	thread myobj(test01);
	myobj.join();  // 使主线程等待子线程执行完毕，主线程继续执行然后共同结束程序
					// 若不使用join，那么主线程和子线程的执行顺序就会发生混乱，导致异常
	cout << "主线程收尾，主线程退出" << endl;
}

/*
	detach：主线程与子线程分离
	主线程与子线程是分离执行的，主线程也不会等待子线程执行完毕
	*******在实际编程的时候，最好不要使用这种东西*********
*/
void test03() {
	thread myobj(test01);
	myobj.detach();
	cout << "主线程执行" << endl;
}

/*
	joinable判断是否可以成功使用join还是detach的，返回true或者是false
	join/detach以后就不能再次使用join或者是detach
	返回的是true的话，说明是可以使用join/detach的；返回false是不能使用join/detach
*/
void test04() {
	thread myobj(test01);
	if (myobj.joinable()) {
		cout << "joinable == True" << endl;
	}
	else
	{
		cout << "joinable == False" << endl;
	}
	myobj.join(); 
	if (myobj.joinable()) {
		cout << "joinable == True" << endl;
	}
	else
	{
		cout << "joinable == False" << endl;
	}
}

/*
	使用对象直接作为可调用对象
*/
void test05() {
	int value = 6;
	TA ta(value);
	thread myobj1(ta); // ta为可调用对象，此时是将对象直接复制进入子线程的
	myobj1.join();  // 等待子进程执行完毕
	//myobj1.detach(); // 此时detach可以正常工作，因为子线程中并没有指向主线程地址的引用
	/*
		若在此处使用detach，子线程中也是引用主线程中的变量，即访问的是主进程中的地址，使主线程与子线程分离，当主线程提前指向完毕以后，
		会回收value的值，但是子线程仍然还在使用，此时就会出现无法预料的结果
		所以这种情况下，就不要使用引用传值，而是直接使用复制传值

		主线程结束就是连ta对象也会被销毁，为啥会执行正确。虽然对象被销毁，但是对象被复制到了线程中，所以执行完主线程后，ta会被销毁
		但是复制的对象仍旧存在，所以对象中没有引用、指针之类的东西，就不会产生问题
	*/
}


/*
	使用lamadb表达式来创建线程
*/
void test06() {
	auto mylamthread = [] {
	cout << "线程3开始执行" << endl;
	//.....
	cout << "线程3执行结束" << endl;
	};
	thread obj2(mylamthread);
	obj2.join();
//
}

/*
	适用对象作为可调用对象
*/
int main() {
	test06();
	cout << "主线程收尾，主线程退出" << endl;
}

