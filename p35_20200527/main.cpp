#include<iostream>

using namespace std;

/*
	一、shared_ptr的使用场景
	
	二、shared_ptr的陷阱与缺陷：一旦用错，也是致命的
		1、慎用裸指针
			绝对要记住，不要使用裸指针来初始化多个shared_ptr
		2、慎用get返回的指针
			永远不要使用get得到的指针来初始化另外一个智能指针或者是给另外一个智能指针赋值
		3、不要把类对象指针(this)作为shared_ptr返回，改用enable_shared_from_this
			在外面创建CT对象的智能指针以及通过CT对象返回的this智能指针都是安全的
			enable_shared_from_this中有一个弱指针weak_ptr，这个弱指针可以监视this
			在我们调用enable_shared_from_this方法时，内部实际上是调用了weak_ptr的lock方法
			lock会让shared_ptr指针的计数加一，同时可以返回shared_ptr
		4、避免循环引用
	三、性能说明
		shared_ptr的尺寸是裸指针的两倍
		1、第一个裸指针指向的是智能指针所指向的对象
		2、第二个裸指针指向一个很大的数据结构
			1.所指对象的强引用计数：shared_ptr
			2.所指对象的弱引用计数：weak_ptr
			3.其他数据，比如：删除器指针、内存分配器
			该控制块是由第一个指向某个指定对象的shared_ptr来创建
			控制块创建的时机：
				1、make_shared：分配并初始化一个对象，返回指向此对象的shared_ptr，所以，这个make_shared能够创建一个控制块
				shared_ptr p1 = make_shared_ptr<int>(100);
				2、使用裸指针创建一个shared_ptr对象的是时候
				int * p = new int(100);
				shared_ptr<int> p1(p);  裸指针只能初始化一个智能指针，千万不要初始化多个，否则就会出错 
		移动语义：
			移动操作要比复制快，复制需要增加引用计数，移动不需要
			移动构造函数快过复制构造函数，移动赋值运算符快过移动拷贝运算符
	四、补充说明和使用建议
		谨慎使用，奇怪的用法不要轻易尝试，优先使用make_shared来声明智能指针，因为make_shared中有很多优化的内存操作，效率比较高
			

*/


/*
	shared_ptr的使用场景
*/
shared_ptr<int>creat1(int value) {
	return make_shared<int>(value);
}

void myfunc1() {
	auto ptmp = creat1(100);
	return;  // 离开作用域以后，ptmp会被自动释放，它所指向的内存也会被自动释放
}

shared_ptr<int> myfunc2(int value) {
	auto ptmp = creat1(value);
	return ptmp; // 返回给临时对象 
}

void test01() {
	// 在此不使用变量来接收myfunc返回的结果，那么返回的shared_ptr就会被销毁,所指向的对象就会被销毁
	myfunc2(200);
}

/*
	慎用裸指针
*/
void proc(shared_ptr<int> ptr) {
	return;
}

void test02() {
	int* p = new int(100);  // 裸指针
	//proc(p);  不支持int*p到shared_ptr的隐式类型转换

	proc(shared_ptr<int>(p));   // 使用裸指针转化为shared_ptr显式类型转换，参数是一个临时的shared_ptr，用一个裸指针显式的构造临时对象
	//*p = 45; // 此时会造成潜在的，不可预料的问题，因为p指向的内存已经被释放了

	// 若要使用裸指针初始化过的智能指针进行操作，请也不要使用如下方式
	shared_ptr<int> p1(p);
	proc(p1);  
	//*p = 45;	// 此时的使用方式也不是安全的，将一个普通裸指针，到shared_ptr上，那么内存管理的责任就交给了shared_ptr，就不应该使用裸指针来访问内存
	//cout << *p << endl;   // 45

	shared_ptr<int> p3(new int(200));  // 该种使用方式是安全的
	proc(p3);
	*p3 = 250;  
	cout << *p3 << endl;
	// 绝对要记住，不要使用裸指针来初始化多个shared_ptr

	/*
		错误示范
		本应该p4 p5都指向同一个内存块，但是现在的结果是他们分别指向不同的内存，导致出错
	*/
	/*int* pi = new int(100);
	shared_ptr<int>p4(p);
	shared_ptr<int>p5(p);*/

	shared_ptr<int> p4(new int);
	shared_ptr<int> p5(p4);  // 这种写法是OK的，p1，p2指向同一个内存地址并且两者是互通的(用的是同一个控制块)
}

/*
	慎用get返回的指针
	get:返回的是智能指针所对应的裸指针，返回的指针是不可以delete的，否则就会异常
	结论：
		永远不要使用get得到的指针来初始化另外一个智能指针或者是给另外一个智能指针赋值
		正常的方式都是使用智能指针初始化智能指针就绝对没有问题
*/
void test03() {
	shared_ptr<int> myp(new int(100));
	int* p = myp.get();	  // 该指针不能随意释放，否则myp就无法正常管理该指针
	// 不能将其他智能指针绑定到get返回的指针上
}

/*
	不要把类对象指针(this)作为shared_ptr返回，改用enable_shared_from_this
	在外面创建CT对象的智能指针以及通过CT对象返回的this智能指针都是安全的
	enable_shared_from_this中有一个弱指针weak_ptr，这个弱指针可以监视this
	在我们调用enable_shared_from_this方法时，内部实际上是调用了weak_ptr的lock方法
	lock会让shared_ptr指针的计数加一，同时可以返回shared_ptr
*/
class CT : public enable_shared_from_this <CT>{
public:
	shared_ptr<CT> getself() {
		//return shared_ptr<CT>(this);  该种方式就是裸指针多次初始化了智能指针
		// 使用C++标准库中的类模板,要记得咋上面继承enable_shared_from_this，并将本类类型传递进去
		return shared_from_this();
	}
};

void test04() {
	shared_ptr<CT> pct1(new CT);
	shared_ptr<CT> pct2(pct1);  // 这是两个强指针

	/*
		初始化智能指针
	*/
	shared_ptr<CT> pct3 = pct1->getself();  // 成员函数返回的是this，就会出现问题，应该在类中使用enable_shared_from_this就可以
	
}

/*
	移动语义
	移动操作要比复制快，复制需要增加引用计数，移动不需要
	移动构造函数快过复制构造函数，移动赋值运算符快过移动拷贝运算符
*/
void test05() {
	shared_ptr<int> p1(new int(100));
	shared_ptr<int> p2(std::move(p1));  // 这用移动构造会导致p1不再指向该对象，引用计数依旧还是一

	shared_ptr<int> p3;
	p3 = std::move(p2);  // 移动赋值，导致p2指向空，p3指向原来的内存，引用计数还是一
}

/*
	优先使用make_shared
*/
void test05() {

	shared_ptr<string> ps1(new string("Garrett"));  // 这种方式会分配两次内存

	auto ps2 = make_shared<string>("Garrett");  // 只会分配一次内存
}

int main() {
	test04();
	return 0;
}