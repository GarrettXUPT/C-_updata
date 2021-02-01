#include<iostream>

using namespace std;

/*
	一、shared_ptr引用计数的增加和减少
		共享式，引用计数，每一个shared_ptr的拷贝都会指向相同的内存，只有最后一个，指向该对象的shared_ptr指针不需要再指向该对象的时候，
		那么shared_ptr才会去释放指向的内存
		1、引用计数的增加
			每个shared_ptr都会记录有多少个其他的shared_ptr指向相同的对象
			在如下情况下，所有指向这个对象的shared_pr引用计数都会增加1
				1、使用一个智能指针来初始化另一个智能指针
				2、将智能指针当做实参向函数内传递, 但是如果传引用的话，计数器不会增加
				3、作为函数返回值
		2、引用计数减少
			1、给shared_ptr赋予新值，让shared_ptr指向一个新对象
			2、局部的shared_ptr离开作用域
			3、当一个智能指针引用计数由0变为1，它会自动释放自己所管理(指向)得原对象，释放原来指向的内存

	二、shared_ptr的常用操作
			1、use_count() 返回多少个智能指针指向某个对象，主要是用于调试目的
			2、unique是否该智能指针独占某个对象,是的话，返回true，否则返回false
			3、reset：恢复，复位
				1、不带参的时候，若pi是唯一指向该对象的指针，那么释放pi所指向的对象，并将pi置空
									若pi不是唯一指向该对象的指针，那么不释放pi所指向的对象，但是指向该对象的引用计数会减少一，同时将pi置空
				2、带参的时候：参数一般是一个new出来的指针，若pi是唯一指向该对象的指针，则释放该对象，让pi再指向新对象
						   若不是唯一指向该对象的指针，但是指向该对象的引用计数会减一，同时pi指向其他对象
			4、使用*进行解引用，获得p所指向的对象
			5、get():返回p中保存的指针，此处返回的是裸指针，要小心使用，若智能指针释放了所指向的对象，返回的裸指针也就变得无效了
			   虽然可以这样操作，但是智能指针和常规指针不要混着用，该函数的出现是考虑到有些函数(第三方)的参数是一个内置的裸指针，而不是智能指针
			   此时只能出此下策
			6、swap:交换两个智能指针所指向的对象，这个不常用
			7、= nullptr 的作用
				1、将所指对象的引用计数减一，若引用计数变为0，则释放智能指针所指向的对象
				2、将智能指针置空
			8、 智能指针的名字作为判断条件
			9、指定删除器以及数组问题
				1、指定删除器：一定的时机帮我删除所指定的对象 delete是默认的删除方式，我们可以指定我们自己的删除器二替代系统给我们的删除器
								当我们指定要删除的对象的时候，编译器就会调用我们自己的删除器
								添加方式：
									一般在参数中添加自己的删除器即可
				  有些情况默认删除器处理不了，需要我们提供自己指定的删除器：比如使用shared_ptr管理默认数组的时候，默认删除器处理不了
				2、指定删除器额外说明
					就算是两个智能指针指定了不同的删除器，只要他们指向的对象类型相同，那么这两个shared_ptr也属于同一个类型
					类型相同，就代表可以放到元素类型为该对象类型的容器中
					make_shared<int>是提倡的生成shared_ptr,但是遗憾的是，make_shared这种方法，使我们不能指定自己的删除器

			

			

*/

/*
	引用计数的增加
*/
/*
	将智能指针当做实参向函数内传递
*/
shared_ptr<int> func1(shared_ptr<int> ptr) {
	return ptr;
}

void func2(shared_ptr<int>& ptr) {
	return;
}

void test01() {
	/*
		目前只有一个p1指向该内存
	*/
	auto p1 = make_shared<int>(100);

	auto p2(p1);  // 智能指针定义的时候的初始化，此对象(内存块有两个指针指向它)目前有两个引用者

	// 将指针传入函数内,也会使计数器加1，但是如果传引用的话，计数器不会增加
	
	//func1(p2);  // 若没有变量来接收这个临时的智能指针，则临时指针的生命周期到了， 虽然作为返回值，但是引用计数就不会增加
	
	//func2(p2);  

	auto p3 = func1(p2);
}

/*
	引用计数的减少
*/
void test02() {
	auto p1 = make_shared<int>(100);

	auto p2(p1);

	auto p3 = func1(p2);

	/*
		将p3指向新地址，引用计数减一
		给shared_ptr赋予新值，让shared_ptr指向一个新对象
	*/
	p3 = make_shared<int>(200);

	p2 = make_shared<int>(300); // 现在只有p1指向原地址

	p1 = make_shared<int>(400);  // 现在p1也被指向其他地方，原内存自动释放 

	func2(p1);  // 局部的智能指针离开作用域  // 进入函数体的引用计数为1，从函数中退出的时候，引用计数为0
}


/*
	shared_ptr的常用操作
*/
void test03() {
	/*
		use_count() 返回多少个智能指针指向某个对象，主要是用于调试目的
	*/
	shared_ptr<int> myp1 = make_shared<int>(100);
	int icount = myp1.use_count();
	cout << "当前有" << icount << "个指针指向该内存" << endl;
	auto myp2(myp1);
	icount = myp1.use_count();
	cout << "当前有" << icount << "个指针指向该内存" << endl;

	/*
		unique是否该智能指针独占某个对象,是的话，返回true，否则返回false
		若是指向的内存是空，那么就返回false
	*/
	cout << "该智能指针是否独占对象：" << myp2.unique() << endl;

	/*
		reset：恢复，复位
		1、不带参的时候，若pi是唯一指向该对象的指针，那么释放pi所指向的对象，并将pi置空
						 若pi不是唯一指向该对象的指针，那么不释放pi所指向的对象，但是指向该对象的引用计数会减少一，同时将pi置空
		2、带参的时候：参数一般是一个new出来的指针，若pi是唯一指向该对象的指针，则释放该对象，让pi再指向新对象
					   若不是唯一指向该对象的指针，但是指向该对象的引用计数会减一，同时pi指向其他对象
	*/
	// 不带参
	auto myp3 = make_shared<int>(100);
	myp3.reset();  // 释放myp3指向的对象，并将myp3置空 
	if (myp3 == nullptr) {
		cout << "该指针为空" << endl;
	}
	else
	{
		cout << "该指针不为空" << endl;
	}
	auto myp4 = make_shared<int>(200);
	auto myp5(myp4);
	cout << "当前指向对象的智能指针数目：" << myp4.use_count() << endl;
	myp5.reset();
	cout << "当前指向对象的智能指针数目：" << myp4.use_count() << endl;
	if (myp5 == nullptr) {
		cout << "该指针为空" << endl;
	}
	else
	{
		cout << "该指针不为空" << endl;
	}
	// 带参
	auto myp6(myp4);
	cout << "当前myp6指向的值" << *myp6 << endl;
	// 此处new出来的东西，会被智能指针自动释放，所以不需要手动回收
	myp6.reset(new int(400));
	cout << "当前myp6指向的值" << *myp6 << endl;
	// 空指针通过reset进行重新初始化
	shared_ptr<int> p;
	p.reset(new int(500));
	cout << *p << endl;
	
	/*
		使用*进行解引用，获得p所指向的对象	
	*/
	shared_ptr<int> p1(new int(200));
	cout << *p1 << endl;

	/*
		get():返回p中保存的指针，此处返回的是裸指针，要小心使用，若智能指针释放了所指向的对象，返回的裸指针也就变得无效了
		虽然可以这样操作，但是智能指针和常规指针不要混着用，该函数的出现是考虑到有些函数(第三方)的参数是一个内置的裸指针，而不是智能指针
		此时只能出此下策
	*/
	shared_ptr<int> p2(new int(300));
	int* point = p2.get();
	cout << *point << endl;
	// 在后面千万不要进行delete，不然系统会报告异常，产生不可预料的结果

	/*
		swap:交换两个智能指针所指向的对象，这个不常用
	*/
	shared_ptr<string> strp1(new string("Garrett"));
	shared_ptr<string> strp2(new string("Walker"));
	cout << "strp1 = " << *strp1 << "  strp2 = " << *strp2 << endl;
	strp1.swap(strp2);
	cout << "strp1 = " << *strp1 << "  strp2 = " << *strp2 << endl;

	/*
		= nullptr 的作用
		1、将所指对象的引用计数减一，若引用计数变为0，则释放智能指针所指向的对象
		2、将智能指针置空
	*/
	shared_ptr<string> strp3(new string("Garrett"));
	strp3 = nullptr;

	/*
		智能指针的名字作为判断条件
	*/
	shared_ptr<string> strp4(new string("Garrett"));
	if (strp4) {
		cout << "strp4指向一个对象" << endl;
	}
	else
	{
		cout << "strp4是一个空指针" << endl;
	}
}

/*
	指定删除器以及数组问题
		1、指定删除器：一定的时机帮我删除所指定的对象 delete是默认的删除方式，我们可以指定我们自己的删除器二替代系统给我们的删除器
						当我们指定要删除的对象的时候，编译器就会调用我们自己的删除器
						添加方式：
							一般在参数中添加自己的删除器即可
		  有些情况默认删除器处理不了，需要我们提供自己指定的删除器：比如使用shared_ptr管理默认数组的时候，默认删除器处理不了
		2、指定删除器额外说明
			就算是两个智能指针指定了不同的删除器，只要他们指向的对象类型相同，那么这两个shared_ptr也属于同一个类型
			类型相同，就代表可以放到元素类型为该对象类型的容器中
			make_shared<int>是提倡的生成shared_ptr,但是遗憾的是，make_shared这种方法，使我们不能指定自己的删除器
*/

// 删除整型对象的删除器，当智能指针引用计数为0，就会调用该删除器来删除对象，自己定义的时候，一定要记得删除裸指针，否则会造成内存泄露
void myDel(int* p) {
	cout << "自定义删除器被调用" << endl;
	delete p;
}


void test04() {
	// 调用自己的删除器
	shared_ptr<int> p1(new int(100), myDel);
	auto p2(p1);
	p2.reset();  // 剩余一个引用计数，在此处释放的时候就会调用自定义的删除器，同时指针置空
	// 删除器可以是一个lambda表达式
	shared_ptr<int> p3(new int(200), [](int* p) {
		cout << "lambda表达式型删除器" << endl;
		delete p;
	});
	cout << *p3 << endl; // 300
	p3.reset();
	//cout << *p3 << endl;  空

	// 在分配的是数组的时候，若是调用默认删除器，就只会删除裸指针，这样会有异常，所以需要自己的删除器
	shared_ptr<int> p4(new int[4], [](int* p) {
		delete[]p;
	});
	/*
		可以使用default_delete来做删除器，它是标准库中的模板类，内部也是用delete实现，但是可以用来删除数组
		使用下方实例化方式可以完成删除数组的目的
	*/
	shared_ptr<int>p5(new int[4], std::default_delete<int[]>());

	/*
		定义数组的时候，在尖括号中加[]即可,这样就可以使用默认删除器删除数组，就不需要自己写删除器
	*/
	shared_ptr<int[]> p6(new int[4]);
	for (int i = 0; i < 4; i++) {
		p6[i] = i;
	}

	for (int i = 0; i < 4; i++) {
		cout << p6[i] << endl;
	}
}

/*
	使用函数模板来封装shared_ptr数组
*/
template<typename T>
shared_ptr<T> make_shared_array(size_t size) {
	return shared_ptr<T>(new T[size], default_delete<T[]>());
}
void test05() {
	// 使用函数模板来定义数组
	shared_ptr<int> p1 = make_shared_array<int>(10);

	// 指定删除器额外说明
	
	/*
		定义两个删除器
	*/
	auto lambda1 = [](int* p) {
		// 此处可填写日志
		delete p;
	};

	auto lambda2 = [](int* p) {
		// 此处可填写日志
		delete p;
	};

	shared_ptr<int> p2(new int(100), lambda1);
	shared_ptr<int> p3(new int(200), lambda2);
	p2 = p3;  // p3先调用lambda2将自己所指向的对象进行释放，然后指向p2所指向的对象，p2引用计数加一，
				// 最后函数调用时，还是调用lambda1来释放p1 p2共同指向的对象
}

int main() {
	test04();
	return 0;
}