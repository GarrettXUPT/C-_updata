#include<iostream>
#include<string>

using namespace std;

/*
	一、unique_ptr概述
		是一种独占式的智能指针，对对象有专属所有权，同一时刻，只能有一个unique_ptr指向该对象
		当unique_ptr被销毁时候，它所指向的对象也会被销毁
		格式：
			unique_ptr<指向的对象类型> 指针变量名；
		1、常规初始化(unique_ptr和new相互配合)
		2、make_unique函数
	二、unique_ptr常规操作
		1、unique_ptr不支持的操作
			不允许多个指针指向一个对象，不允许赋值、拷贝的操作
		2、移动语义

		3、下有各种方法举例
			
*/

/*
	常规初始化
*/
void test01() {
	unique_ptr<int> p1;  // 表示一个指向int对象的空智能指针
	if (p1 == nullptr) {
		cout << "该智能指针为空指针" << endl;
	}
	unique_ptr<int> p2(new int(105));  // unique_ptr指向了一个值为105的int对象
}

/*
	使用make_unique函数初始化，在C++11中没有，但是在C++14中有，也是优化的智能指针生成器，不支持指定的删除器语法，
	若不是自己定义删除器，那么优先选择make_unique生成智能指针
*/
void test02() {
	auto p1 = make_unique<int>(100);
	cout << *p1 << endl;
}

/*
	unique_ptr常规操作
*/
void test03() {
	/*
		移动语义
	*/
	unique_ptr<string> ps1(new string("Garrett"));
	
	// 将ps1的对象移动到ps2中
	auto ps2 = std::move(ps1);

	/*
		release：放弃对对象的控制权，切断了智能指针和它所指向对象之间的联系，返回的是指向对象的裸指针，
		同时将智能指针置空，返回的裸指针可以手动delete来释放(若不使用就得释放，否则会导致内存泄漏)，
		也可以用来初始化另外一个裸指针，或者给另外一个智能指针赋值
	*/
	auto ps3 = make_unique<int>(200);
	unique_ptr<int> ps4(ps3.release());
	if (ps1 == nullptr) {
		cout << "ps1被置空" << endl;
	}
	cout << *ps4 << endl;  // 200
	// 手动delete释放
	int* p = ps4.release();
	delete p;
	/*
		reset：
			不带参数的时候：释放智能指针所指向的对象，并将智能指针置空
			带参数的时候：释放智能指针所指向的对象，并让智能指针指向新对象
	*/
	auto ps5 = make_unique<int>(400);
	ps5.reset();
	if (ps5 == nullptr) {
		cout << "ps5已经为空" << endl;
	}

	// 下面代码描述正确，不存在内存泄漏
	auto ps6 = make_unique<string>("garrett");
	auto ps7 = make_unique<string>("walker");
	ps6.reset(ps7.release());  // reset释放ps6所指向的对象内存，让ps7指向ps6指向的对象，同时ps7被置空
	cout << *ps6 << endl;  // walker
	
	/*
		= nullptr释放智能指针所指向的对象，并将智能指针置空	
	*/
	auto ps8 = make_unique<int>(500);
	ps8 = nullptr;  // 释放ps8指向的对象，并将ps8置空
	
	/*
		指向一个数组
	*/
	unique_ptr<int[]> psarr1(new int[10]);  // 指向一个数组的智能指针
	for (int i = 0; i < 10; i++) {
		psarr1[i] = i;
	}
	for (int i = 0; i < 10; i++) {
		cout << psarr1[i] << " ";
	}
	cout << endl;

	/*
		get：返回智能指针中所保存的裸指针
	*/
	auto ps9 = make_unique<string>("Garrett");
	string* pstr = ps9.get();
	*pstr = "Walker";
	cout << *pstr << endl;
	// 千万不要delete pstr;
	
	/*
		*解引用，在智能指针指向数组的时候，就不可以使用*进行解引用	
	*/

	/*
		swap：交换两个智能指针所指向的对象
	*/
	auto pstr1 = make_unique<string>("Garrett");
	auto pstr2 = make_unique<string>("Walker");
	cout << "pstr1 = " << *pstr1 << " pstr2 = " << *pstr2 << endl;
	pstr1.swap(pstr2);
	cout << "pstr1 = " << *pstr1 << " pstr2 = " << *pstr2 << endl;

	/*
		智能指针名字作为判断条件
	*/
	auto pstr3 = make_unique<string>("China");
	if (pstr3) {
		cout << "该指针不为空，可进行相关操作" << endl;
	}
}


/*
	转换为shared_ptr，若unique_ptr为右值的时候，就可以将它赋给shared_ptr
	因为shared_ptr包含一个显式的构造函数，可以将unique_ptr转化为shared_ptr，
	shared_ptr会接管原来unique_ptr所管理的对象
*/

auto myfunc() {
	return unique_ptr<string>(new string("Garrett")); // 临时对象都是右值
}

void test04() {
	shared_ptr<string> pstr1 = myfunc();  // 将unique_ptr转换为shared_ptr

	unique_ptr<string> ps(new string("Garrett"));
	shared_ptr<string> pstr2 = std::move(ps);   // 将本来是左值的ps转移到右值
}

int main() {
	test03();
	return 0; 
}