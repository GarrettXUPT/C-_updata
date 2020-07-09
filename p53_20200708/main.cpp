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
	һ�������ķ���
		vector��list��map�����ڱ�������
		���Է�Ϊ�����ࣺ
			1��˳������(sequence Constainers):�Ž�ȥ�����Ԫ�ؾͻ�һֱ��������磺array/vector/deque/forward_list
			2����������(Associative Containers):Ԫ���Ǽ�ֵ�ԣ��ر��ʺ������ң������ڷ��õ�ʱ���ǲ����Կ��Ʋ���Ԫ�ص�λ�õ�(�ڲ�����/��ϣ��)
			3����������(unordered Containers):Ԫ�ص�λ�ò���Ҫ����Ҫ���Ǹ�Ԫ���Ƿ�������������棬��������Ҳ����һ�ֹ�������(�ڲ��ǹ�ϣ��)
		C++��׼��û�й涨�κ���������ʹ���κ��ض���ʵ���ֶ�

	����������˵����Ӧ������
		1��array:�Ǹ�˳���������������һ�����飬�ڴ�ռ��������ģ���С�ǹ̶���
		2��vector���������������������ɾ�ٶ��Ƿǳ���ģ����м����Ԫ�ؿ��ܻᵼ�º����Ԫ�غ��ƣ�����Ч�ʱȽϵͣ�����Ч�ʽϵ�
		   vector�������ڴ�ռ�Ҳ�������ģ�vector������һ��"�ռ�"�ĸ��ÿһ���ռ䶼��������һ��Ԫ��

*/

void test01() {
	// �������Ԫ�ص�����
	array<string, 5>mystring = { "Hello", "World", "Garrett", "Walker" };
	cout << "mystring.size() = " << mystring.size() << endl;

	mystring[0] = "China";
	mystring[4] = "this is a joke";
	cout << "sizeof(string) = " << sizeof(string) << endl;
	cout << "mytring.size() = " << mystring.size() << endl;
	for (size_t i = 0; i < mystring.size(); ++i) {
		cout << mystring[i] << endl;
		printf("Ԫ�ص�ֵַ%p\n", &mystring[i]);
	}
}

class A {
public:
	int m_i;
	A(int tmpv) :m_i(tmpv) {
		cout << "���캯��ִ��" << endl;
	}
	A(const A& tmpA){
		m_i = tmpA.m_i;
		cout << "�������캯��ִ��" << endl;
	}

	virtual ~A(){
		cout << "�������캯��ִ��" << endl;
	}
};

void test02() {
	/*
		ÿ����һ�Σ��������һ�ι��캯����һ�ο������캯��(��Ԫ�ؿ�����������)��һ����������
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
	dequeʹ��ʾ����
		˫����У��൱�ڶ�̬���飬��ͷ��������β����ɾ���ݣ��ٶȶ��ܿ죻
		�����м����Ԫ�أ��ᵼ���ƶ�����Ԫ�أ�Ч���Ͻϵ�
		���ݲ��Խ����������˫�˶��е��ڴ沢���������ģ�deque��ʵ��һ���ֶ����飬���ֶ������ڴ�
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
	stack����
		�Ƚ����FILO
		stackֻ֧�ִ�ջ������Ԫ�غ�ȡ��Ԫ��
		dequeʵ�����ǰ�����stack�Ĺ���
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
	list��˫��������ͷ���β��
		����ҪԪ��֮���ڴ�����һ�𣻲���Ч�ʽϵͣ�����������λ�ò��롢ɾ��Ԫ��Ч�ʽϸ�
		vector��list������
			1��vector���������飬�����ڴ�ռ��������ģ�list��˫�������ڴ�ռ䲻һ������
			2��vector���м�����ǿ�ͷ����Ԫ�رȽϵͣ�list������λ�ò���Ԫ��Ч�ʶ��ǱȽϸߵ�
			3��vector���ڴ治����ʱ�򣬻�������һ���ڴ棬��ԭ���ڴ�����������������ҵ��ڴ������¹�������
			4��vector���Ը�Ч�������ȡ����list��������һ�㣬֪���Լ����ʵ�Ԫ��λ�ã�vector����ֱ��������ȡ������list����Ҫ��ͷ�����Ǵ�β����
*/

/*
	forward_list��C++11�����ģ���������(����list)
		û��һ�������ָ�룬�������ڴ����ģ�����������ϳ���ʱ��
*/
void test05() {
	forward_list<A> myfl;
	for (int i = 0; i < 5; ++i) {
		// ֻ��ͷ��
		myfl.push_front(A(i));
	}
	auto start = myfl.begin();
	while (start != myfl.end()){
		cout << start->m_i << endl;
		start++;
	}
}

/*
	set/map����
		���������ڲ�ʵ�ֽṹ��Ϊ������������������б������ݵ�ʱ�򣬲���Ҫ����ָ������λ�á��������Զ��ĸ������Ԫ�ظ����㷨����һ��λ��
	map��ÿ��Ԫ��������(��ֵ��)��һ�㶼��ͨ��key����value���ص���ǲ����ٶ��ر�죬Ҳ������һ����������������ͬ��key������Ҫ�У������multimap
		���ҽ�Ϊ˳�򣬲�����ٶȿ��ܻ��е���

	set�����ڼ�ֵ�Ե�˵����ÿһ��Ԫ�ض���һ��value��Ԫ��֮���ǲ������ظ��ģ����Ƿ�Ҫ�ظ������ʹ��multiset

	�ܽ᣺
		1������Ԫ�ص�ʱ����Ϊ�����������һ���ʵ��Ĳ���λ�����Բ�����ٶȿ��ܻ���һЩ
		2�����ҵ��ٶȱȽϿ죬��Ҫ�����ҵ�ĳ��Ԫ�ص�ʱ�����Ǿ�Ҫ����ʹ��map/set
	
*/
void test06() {
	map<int, string> mymap;  // �����ֵ�Ե�����map
	mymap.insert(make_pair(1, "Garrett"));
	mymap.insert(make_pair(2, "Walker"));
	mymap.insert(pair<int, string>(3, "ALisa"));

	auto iter = mymap.find(3);
	if (iter != mymap.end()) {
		// �ҵ���
		cout << "��ţ�" << iter->first << " ������" << iter->second << endl;
	}
	else
	{
		cout << "����Ա������" << endl;
	}
}
/*
	unordered_set/unordered_multiset/unordered_map/unordered_multimap
		ʵ����ʹ�õ��ǹ�ϣ���������ϰ汾��hash_set/map, hash_multiset.multimap;���ڶ�����ordered��ͷ������ȡ��
		�Զ�ָ��Ԫ��λ�ã�����Ҫʹ�����ֶ���Ԥ
*/
void test07() {
	unordered_set<int> myset;
	/*
		�鿴�����е���������,ϵͳҪ�����ӵ�����������Ԫ�ص�����
	*/
	cout << "bucket_count = " << myset.bucket_count() << endl;  // 8

	for (int i = 0; i < 8; ++i) {
		myset.insert(i);
	}
	
	cout << "bucket_count = " << myset.bucket_count() << endl;  // 8

	/*
		�����Ԫ���Ժ����ӻ�����
	*/
	myset.insert(8);
	cout << "bucket_count = " << myset.bucket_count() << endl;  // 64

	/*
		������Ԫ�ص�����
	*/
	cout << myset.size() << endl;  // 9 

	/*
		��ӡ����Ԫ��
	*/
	auto start = myset.begin();
	while (start != myset.end()) {
		cout << *start++ << " ";
	}
	cout << endl;
	
	auto myfind = myset.find(5); 
	if (myfind != myset.end()) {  // ���ҵ���
		cout << *myfind << endl;
	}
	else
	{
		cout << "û�ҵ�" << endl;
	}

	/*
		ȫ�ֵ�find��������
	*/
	if (find(myset.begin(), myset.end(), 5) != myset.end()) {
		cout << "Ԫ��5������������" << endl;
	}

	for (int i = 0; i < myset.bucket_count(); ++i) {
		cout << "��" << i << "��������Ԫ�ص�����Ϊ��" << myset.bucket_size(i) << endl;
	}

	/*
		�����������������ж��ٸ�����
	*/
	cout << "max_bucket_count = " << myset.max_bucket_count() << endl;
}

int main() {
	test07();
	return  0;
}