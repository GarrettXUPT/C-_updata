#include<iostream>

using namespace std;

/*
	一、临时对象的概念
		i++ 返回右值表达式，会产生临时对象
		++i 返回左值表达式
		还有一些临时对象是因为代码书写产生的，统一称临时变量为临时对象 
		因为临时对象会额外的消耗系统资源，所以产生的越少越好
		new会分派到堆上，栈上会产生一些临时变量，这些临时变量需要操作系统自己释放
		多数情况，临时对象的产生都是由于代码书写问题产生的

	二、产生临时对象的情况及解决(三种的情况和解决方案)
		1、以传值方式给函数传递参数
			不建议直接传对象，建议传递引用的方式来传递参数，可提高代码效率

		2、类型转换生成的临时对象/隐式类型转换以保证函数调用成功
			在编程时，最好不要有类型转换，若有类型转换，则一定要加const

		3、函数返回对象的时候

	四、总结
		以这节课的经验写代码，提高代码运行效率
			
			
*/

class CTempValue {
public:
	int val1;
	int val2;
public:
	CTempValue(int va1 = 0,int val2 = 0);
	/*
		拷贝构造函数
	*/
	CTempValue(const CTempValue& t) : val1(t.val1), val2(t.val2) {
		cout << "调用了拷贝构造函数" << endl;
	}

	CTempValue& operator=(const CTempValue& tmpv) {
		val1 = tmpv.val1;
		val2 = tmpv.val2;
		return*this;
	}

	virtual ~CTempValue() {
		cout << "调用了析构函数" << endl;
	}
public:
	int Add(CTempValue& ts);  // 普通函数
	//CTempValue Double(CTempValue& ts);
};

/*
	高消耗性版本
*/
//CTempValue Double(CTempValue& ts) {
//	CTempValue tmpm;  // 该处会消耗一个构造函数和一个析构函数,系统产生了临时对象
//	tmpm.val1 = ts.val1 * 2;
//	tmpm.val2 = ts.val2 * 2;
//	return tmpm;  // 还执行了一个拷贝构造函数
//}

/*
	低消耗型版本，该种优化，我们节省了一个拷贝构造函数和一个析构函数
*/
CTempValue Double(CTempValue& ts) {
	return CTempValue(ts.val1 * 2, ts.val2 * 2);  // 系统在此处也会产生一个临时对象
}

 

CTempValue::CTempValue(int v1, int v2): val1 (v1), val2 (v2) {
	cout << "调用了构造函数" << endl;
	cout << "val1 = " << val1 << " val2 = " << val2 << endl;
}

int CTempValue::Add(CTempValue& ts) {  // 该处使用引用引用，就可以消除临时对象
	int tmp = ts.val1 + ts.val2;
	ts.val1 = 1000;  // 这里修改值对于外界对象没有影响，只有引用才有影响,使用引用后，就会改变外界对象的值
	return tmp;
}
/*
	临时对象的概念
*/
void test01() {
	int i = 1;
	/*
		r1属于临时变量，与i之间没有关系,绑定之后，临时变量就不会被释放
		i++因为功能需要所以产生临时对象
	*/
	int&& r1 = i++;
	cout << "r1 = " << r1 << " i = " << i << endl;  // 1   2 
	r1 = 19;  // 此处对于r1的赋值，不会对i值造成任何影响
	cout << "r1 = " << r1 << " i = " << i << endl;  // 19  2
	i = 6;  // 对i进行赋值也不会对r1造成影响
	cout << "r1 = " << r1 << " i = " << i << endl;  // 19  6
}

/*
	以传值方式给函数传递参数
*/
void test02() {
	CTempValue tm(10, 20);
	int sum = tm.Add(tm);  // 会导致拷贝构造函数的执行,这里直接使用tm,会将tm拷贝一份进去，若使用引用传入就不会调用拷贝构造函数
	cout << "sum = " << sum << endl;   // 30
	// 未使用引用
	//cout << "tm.val1 = " << tm.val1 << " tm.val2 = " << tm.val2 << endl;  // 10 20 
	// 使用引用
	cout << "tm.val1 = " << tm.val1 << " tm.val2 = " << tm.val2 << endl;  // 1000 20 
}

/*
	类型转换生成的临时对象/隐式类型转换以保证函数调用成功
*/
void test03() {
	/*
		该种方式：构造函数调用两次，析构函数调用两次
	*/
	//CTempValue sum;
	//sum = 1000; // 该处产生了一个真正的CTempValue类型的临时对象 
	//			// 这里将1000转化为CTempValue对象 此时的1000会赋值给第一个默认参数val1，第二个参数还是采用默认参数
	//			// 在1000赋值给sum时，导致调用了拷贝赋值运算符
	//cout << "val1 = " << sum.val1 << "val2 = " << sum.val2 << endl;

	/*
		处理方式,将定义对象好给对象初值放在一行上 
				 此种方式，构造函数和析构函数只调用了一次
	*/
	CTempValue sum = 1000;   // 此处指的是定义时初始化，不是赋值运算符
						    // 此处定义了sum对象，为sum对象预留了空间，用1000来构造sum对象，并且直接构建在sum对象的预留空间
	cout << "val1 = " << sum.val1 << "val2 = " << sum.val2 << endl;
}

/*
	隐式类型转换，保证函数调用成功
	统计字符ch在字符串strsorce里出现的次数
	C++语言只会为const引用产生临时变量，而不会为非const引用参数创建临时对象
*/
int calc(const string& strsource, char target) {  // 该处形参必须是有const标识符，否则，系统怀疑你会通过引用改变字符串，所以报错
									// strsource这个形参就绑定到了string临时对象上，当函数返回时，该临时对象就会被销毁
	const char* p = strsource.c_str();
	int icount = 0;
	while (*p != '\0')
	{
		if (*p == target) {
			icount++;
		}
		p++;
	}
	return icount;
}

/*
	这里编译器会自动的将char[] 类型转化为string类型
*/
void test04() {
	char mystr[100] = "I Love China";
	int result = calc(mystr, 'o');
	cout << result << endl;
}

/*
	函数返回对象的时候
	
*/
void test05() {
	CTempValue ts(10, 20);
	cout << "ts.val1 = " << ts.val1 << " ts.val2 = " << ts.val2 << endl;
	/*
		返回了一个临时对象，使系统又自动调用了一个构造函数和析构函数
	*/
	//Double(ts);
	
	/*
		若使用类型对返回值进行接收,这里的临时对象没有被析构，返回的临时对象直接构建到res的预留空间中
	*/
	/*CTempValue res = Double(ts);
	cout << "res.val1 = " << res.val1 << " res.val2 = " << res.val2 << endl;*/
	
	/*
		使用右值引用接收临时对象,该种方式与上种方式的效果相同
		最好不用右值引用，还是使用上一种形势比较好，临时对象就是一种右值
	*/
	CTempValue&& res = Double(ts);
	cout << "res.val1 = " << res.val1 << " res.val2 = " << res.val2 << endl; 

	/*
		Double引起的消耗
		CTempValue ts;  会消耗一个构造函数和一个析构函数
		return tmpm;  会产生一个临时对象，会占用一个拷贝构造函数和析构函数
	*/
}

class mynum {
public:
	/*
		必须有对应的构造函数
	*/
	mynum(int x = 0, int y = 0) :num1(x), num2(y){}
public:
	int num1, num2;
};
mynum operator+(const mynum& tmpnum1, const mynum& tmpnum2) {
	return mynum(tmpnum1.num1 + tmpnum2.num1, tmpnum1.num2 + tmpnum2.num2);
}

/*
	类外的运算符重载
*/
void test06() {
	mynum num1(10, 20);
	mynum num2(50, 60);
	mynum res = num1 + num2;
	cout << res.num1 << "  " << res.num2 << endl;  // 60  80
}

int main() {

	//test01();
	//test03();
	test06();
	return 0;
}