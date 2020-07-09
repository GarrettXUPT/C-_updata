#include<iostream>
#include<array>
#include<string>
#include<vector>
#include<deque>
#include<stack>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<forward_list>

using namespace std;

/*
	一、容器的分类
		vector、list、map，用于保存数据
		可以分为三大类：
			1、顺序容器(sequence Constainers):放进去在哪里，元素就会一直在那里，比如：array/vector/deque/forward_list
			2、关联容器(Associative Containers):元素是键值对，特别适合做查找，我们在放置的时候，是不可以控制插入元素的位置的(内部是树/哈希表)
			3、无序容器(unordered Containers):元素的位置不重要，重要的是该元素是否在这个容器里面，无序容器也属于一种关联容器(内部是哈希表)
		C++标准并没有规定任何容器必须使用任何特定的实现手段

	二、容器的说明和应用事项
		1、array:是个顺序容器，代表的是一个数组，内存空间是连续的，大小是固定的
		2、vector容器：在容器后面进行增删速度是非常快的，向中间插入元素可能会导致后面的元素后移，所以效率比较低，查找效率较低
		   vector容器的内存空间也是连续的，vector容器有一个"空间"的概念，每一个空间都可以容纳一个元素

*/

void test01() {
	// 包含五个元素的数组
	array<string, 5>mystring = { "Hello", "World", "Garrett", "Walker" };
	cout << "mystring.size() = " << mystring.size() << endl;

	mystring[0] = "China";
	mystring[4] = "this is a joke";
	cout << "sizeof(string) = " << sizeof(string) << endl;
	cout << "mytring.size() = " << mystring.size() << endl;
	for (size_t i = 0; i < mystring.size(); ++i) {
		cout << mystring[i] << endl;
		printf("元素地址值%p\n", &mystring[i]);
	}
}

class A {
public:
	int m_i;
	A(int tmpv) :m_i(tmpv) {
		cout << "构造函数执行" << endl;
	}
	A(const A& tmpA){
		m_i = tmpA.m_i;
		cout << "拷贝构造函数执行" << endl;
	}

	virtual ~A(){
		cout << "析构构造函数执行" << endl;
	}
};

void test02() {
	/*
		每插入一次，都会调用一次构造函数、一次拷贝构造函数(将元素拷贝到容器中)、一次析构函数
	*/
	vector<A> vec;
	for (int i = 0; i < 5; ++i) {
		vec.push_back(A(i)); 
	}
	cout << "capacity is " << vec.capacity() << endl;
	auto start = vec.begin();
	while (start != vec.end()) {
		cout << start->m_i << endl;
		start++;
	}
}

/*
	deque使用示例：
		双向队列，相当于动态数组，在头部或者是尾部增删数据，速度都很快；
		若向中间插入元素，会导致移动其他元素，效率上较低
		根据测试结果来看，该双端队列的内存并不是连续的，deque其实是一个分段数组，即分段连续内存
*/
void test03() {
	deque<A> mydeque;
	for (int i = 0; i < 5; ++i) {
		mydeque.push_front(A(i));
	}

	for (int i = 5; i < 10; ++i) {
		mydeque.push_back(A(i));
	}

	auto start = mydeque.begin();
	while (start != mydeque.end()) {
		cout << start->m_i << endl;
		start++;
	}
}

/*
	stack容器
		先进后出FILO
		stack只支持从栈顶放入元素和取出元素
		deque实际上是包含着stack的功能
*/
void test04() {
	stack<A> myStack;
	for (int i = 0; i < 5; ++i) {
		myStack.push(A(i));
	}
	
	for (int i = 0; i < myStack.size(); ++i) {
		A* tmp = &(myStack.top());
		cout << tmp->m_i << endl;
		myStack.pop();
	}
}

/*
	list：双向链表，可头插和尾插
		不需要元素之间内存连在一起；查找效率较低，但是在任意位置插入、删除元素效率较高
		vector与list的区别：
			1、vector类似于数组，它的内存空间是连续的，list是双向链表，内存空间不一定连续
			2、vector从中间或者是开头插入元素比较低，list在任意位置插入元素效率都是比较高的
			3、vector当内存不够的时候，会重新找一块内存，对原来内存对象做析构，在新找的内存中重新构建对象
			4、vector可以高效的随机存取，而list做不到这一点，知道自己访问的元素位置，vector可以直接索引存取，但是list还是要从头或者是从尾数起
*/

/*
	forward_list：C++11新增的，单向链表(受限list)
		没了一个方向的指针，减少了内存消耗，尤其是链表较长的时候
*/
void test05() {
	forward_list<A> myfl;
	for (int i = 0; i < 5; ++i) {
		// 只能头插
		myfl.push_front(A(i));
	}
	auto start = myfl.begin();
	while (start != myfl.end()){
		cout << start->m_i << endl;
		start++;
	}
}

/*
	set/map容器
		关联容器内部实现结构多为红黑树，向这种容器中保存数据的时候，不需要我们指定数据位置。容器会自动的给加入的元素根据算法安排一个位置
	map：每个元素有两项(键值对)，一般都是通过key来找value，特点就是查找速度特别快，也不允许一个容器中有两个相同的key，若非要有，则采用multimap
		查找较为顺序，插入的速度可能会有点慢

	set不存在键值对的说法，每一个元素都是一个value，元素之间是不可以重复的，若是非要重复则可以使用multiset

	总结：
		1、插入元素的时候，因为容器会给你找一个适当的插入位，所以插入的速度可能会慢一些
		2、查找的速度比较快，若要快速找的某个元素的时候，我们就要考虑使用map/set
	
*/
void test06() {
	map<int, string> mymap;  // 保存键值对的容器map
	mymap.insert(make_pair(1, "Garrett"));
	mymap.insert(make_pair(2, "Walker"));
	mymap.insert(pair<int, string>(3, "ALisa"));

	auto iter = mymap.find(3);
	if (iter != mymap.end()) {
		// 找到了
		cout << "编号：" << iter->first << " 姓名：" << iter->second << endl;
	}
	else
	{
		cout << "该人员不存在" << endl;
	}
}
/*
	unordered_set/unordered_multiset/unordered_map/unordered_multimap
		实际上使用的是哈希表，以往的老版本是hash_set/map, hash_multiset.multimap;现在都是由ordered开头的容器取代
		自动指定元素位置，不需要使用者手动干预
*/
void test07() {
	unordered_set<int> myset;
	/*
		查看容器中的篮子数量,系统要求篮子的数量不少于元素的数量
	*/
	cout << "bucket_count = " << myset.bucket_count() << endl;  // 8

	for (int i = 0; i < 8; ++i) {
		myset.insert(i);
	}
	
	cout << "bucket_count = " << myset.bucket_count() << endl;  // 8

	/*
		插入该元素以后，篮子会扩容
	*/
	myset.insert(8);
	cout << "bucket_count = " << myset.bucket_count() << endl;  // 64

	/*
		篮子中元素的数量
	*/
	cout << myset.size() << endl;  // 9 

	/*
		打印篮子元素
	*/
	auto start = myset.begin();
	while (start != myset.end()) {
		cout << *start++ << " ";
	}
	cout << endl;
	
	auto myfind = myset.find(5); 
	if (myfind != myset.end()) {  // 若找到了
		cout << *myfind << endl;
	}
	else
	{
		cout << "没找到" << endl;
	}

	/*
		全局的find函数查找
	*/
	if (find(myset.begin(), myset.end(), 5) != myset.end()) {
		cout << "元素5存在于容器中" << endl;
	}

	for (int i = 0; i < myset.bucket_count(); ++i) {
		cout << "第" << i << "个篮子中元素的数量为：" << myset.bucket_size(i) << endl;
	}

	/*
		测试容器中最大可以有多少个篮子
	*/
	cout << "max_bucket_count = " << myset.max_bucket_count() << endl;
}

int main() {
	test07();
	return  0;
}