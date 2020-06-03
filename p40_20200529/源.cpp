#include<iostream>
#include<thread>
#include<string>

using namespace std;

/*
第三节、线程传参详解，detach大坑，成员函数做线程函数

1、传递临时参数作为线程参数
	1.1 要避免的陷阱：
		若主线程与子线程分离，若主线程提前结束，那么引用的地址就会被主线程回收
		虽然传入的是引用，但是仍然是对mvar的复制，所以是安全的
		在detach使用时，子线程传参时不推荐使用引用，也绝对不可以使用指针

	1.2 要避免的陷阱
		只要使用临时构造的A类对象作为参数传递给线程，那么就一定能够在主线程执行完毕前，就可以将第二个参数构造
		完成，即便detach了，子线程也是安全的

	1.3 总结
		1、detach时，若传递int这种简单的参数，建议都是值传递，不要使用引用
		2、在使用类对象时，要避免隐式类型转换，全部都在创建线程时就构建出临时对象，在函数参数里用引用来接，
		   否则系统又会构造出一个对象，造成浪费
		终极结论：
			最好不要使用detach，只使用join。这样就不存在局部变量失效，导致线程对内存的非法应用问题

2、临时对象作为线程参数
	2.1 线程id
		每个线程都对应着一个唯一的数字，不同的线程对于不同的id是不同的，可以通过函数库中函数去获取
		this_thread::get_id() 来获取

	2.2 临时对象构造时间抓捕

3、传递类对象，智能指针作为线程参数
	std::ref函数

4、使用成员函数的指针作为线程函数  operator()
		
*/



/*
	作为线程函数
*/
void myprint1(const int &i, char* pmybuf) {
	cout << i << endl;
	cout << pmybuf << endl;
	cout << "子线程id = " << this_thread::get_id() << endl;
}

void myprint2(const int& i, const string& pmybuf) {
	cout << i << endl;
	cout << pmybuf.c_str() << endl;
	cout << "子线程id = " << this_thread::get_id() << endl;
}

class A {
public:
	int m_i;
	// 类型转换构造参数，可以将int转化为类A对象
	A(int a) :m_i(a) { cout << "构造函数执行" << endl; }
	
	A(const A& a) : m_i(a.m_i) { cout << "拷贝构造函数" << endl; }

	~A() { cout << "析构函数" << endl; }

	void thread_work(int num) {
		cout << "子线程的thread_work开始执行了" << endl;
	}

	/*
		线程的入口函数
	*/
	void operator()(int num) {
		this->m_i = num;
		cout << "子线程被创建" << endl;
	}
};


/*
	要避免的陷阱
*/
void test01() {
	int mvar = 1;
	int& mvary = mvar;
	char mybuf[] = "this is a test";
	// 虽然在这里函数接的是引用，但是内部确实是mvar的拷贝(值传递),即便主线程中的mvar会被回收，但是子线程仍然是安全的
	// 所以这样使用detach是安全的， 虽然这样但是还不建议使用detach
	// 一定要记住，在detach使用时，指针是绝对有问题的
	thread myobj(myprint1, mvar, mybuf);
	myobj.detach();
	cout << "Garrett" << endl;
}

/*
	解决子进程中的字符串传值问题
*/
void test02() {
	int mvar = 1;
	char mybuf[] = "this is a test";
	string str = "this is a str";
	/*
		mybuf是什么时候转化为string，
		当存在主程序执行完毕，还在使用主线程局部变量使结果不可预料，若不进行显式类型转换的话，会有这种错误的可能性

		直接将mybuf转化为string对象，这样就可以保证在线程中一定有有效变量,在主线程执行完毕之前，对象已经被复制
		在创建线程的同时构造临时对象的方法传递参数是可行的
	*/
	thread myobj1(myprint2, mvar, string(mybuf));
	thread myobj2(myprint2, mvar, str);
	myobj1.join();
	myobj2.join();
	cout << "Garrett" << endl; 
}



/*
	无论下列传参是否是引用型传参，但实际上都是拷贝型传参
*/
void myprint3(A& pmybuf) {
	pmybuf.m_i = 199;  // 我们修改该值不会影响到main函数中的数值
	cout << pmybuf.m_i << endl;
}

void test03() {
	/*
		生成一个类对象
	*/
	A myobj1(10);
	
	// thread mytobj1(myprint2, myobj1);  该种传参方式并不会改变主线程中的A.m_i结果

	/*
		下式表示真正需要在子线程中改变A.m_i的值，做到主线程与子线程的数据是同步的，但是要注意，此时就不可以使用detach
		传入参数为类对象
		&myobj 等价于 ref(obj)的效果
		这种方式说明，在创建线程的同时，再构建临时对象的方法是可行的
	*/
	thread mytobj1(myprint3, ref(myobj1));
	mytobj1.join();
	cout << myobj1.m_i << endl;
}

/*
	传入参数为智能指针
*/

/*
	智能指针的传参方式
*/
void myprint4(unique_ptr<int> pzn) {
	cout << *pzn << endl;
}

void test04() {
	unique_ptr<int> mvp(new int(100));  // 独占式智能指针
	// move将独占式智能指针mvp转移到独占式智能指针pzn中，转以后mvp就是空了
	thread myobj2(myprint4, move(mvp));
	myobj2.join();
}

  
/*
	传入参数为成员函数，需要传入三个参数
*/
void test05() {
	// 生成一个类A的对象
	A myobj1(10);
	thread myobj3(&A::thread_work, myobj1, 15);
	myobj3.join();
}

///*
//	使用重写运算符创建线程入口,传入两个参数,使用括号运算符函数作为进程的入口
//*/
void test06() {
	A myobj3(100);
	//thread mytobj2(myobj3, 15);
	thread mytobj2(ref(myobj3), 15); // 不再调用拷贝构造函数，此时不能使用detach
	mytobj2.join();
	cout << myobj3.m_i << endl;
}

int main() {
	test06();
	//getchar();
	return 0;
}