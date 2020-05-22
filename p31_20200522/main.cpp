#include<iostream>

using namespace std;

/*
	һ���ɱ����ģ��(Variadic Template):����ģ���к���0-�����ģ����������﷨���봫ͳģ�岻ͬ
		Ҫע����ǣ�
			1�����ǽ�args��Ϊһ��/һ�Ѳ��������������ǿ��Ը�����ͬ�ģ����������T���͵�ʱ����������һ�����ͣ�Ҫ����0�������ͬ������
			   ��Ӧ�Ĳ���Ҳ�ǲ�ͬ���͵Ĳ���
			2��һ�������п�������0-���ģ�������ģ���������Ϊ��������
			3����������˳��T�������...���������ǳƺ�TΪ�ɱ�����ͣ�����������һ�����ͣ�ʵ������0-�����ͬ�����ͣ�argsΪ�ɱ��β�(һ���β�)
			4���ھ���ĺ����β��У�&λ�ó��������������ĺ���
		��������չ����
			�õ��������еĸ���������չ����·�ȽϹ̶���һ�㶼���õݹ�ķ�ʽ��չ��������
			Ҫ�������ڴ����д�о��в�����չ����������һ��ͬ���ĵݹ���ֹ����

	�����ɱ����ģ��
		����ģ���ж���0-�����ģ�����
		ͨ���ݹ鷽ʽչ��������
		
*/


/*
	�ɱ����ģ�巶��
*/
template<typename...T>
void myfunct1(T...args) {
	cout << "ģ���������Ϊ��" << sizeof...(args) << endl;
	cout << "���ͣ�" << sizeof...(T) << endl;
}

template<typename T, typename...U>
void myfunct2(const T& firstarg, const U&...secondargs) {
	cout << "��һ��������С" << sizeof(firstarg) << endl;
	cout << "�ڶ���������С" << sizeof...(secondargs) << endl;  // sizeof...�ɱ�ε�����Ϊ2
}

void test01() {
	myfunct1();
	myfunct1(10, 20, "str", "ing");  // 4 4

	myfunct2(10);   // 4

	myfunct2(10, "abc", 12.7);  // 4  2
}

/*
	��������չ��
	��һ��������һ�����������ǵڶ��������Ǻ�����������д�����ʺϲ�������չ��
	�ݹ���ֹ����
*/
void myfunc3() {
	cout << "ִ����չ����ֹ����" << endl;
}

template<typename T, typename...U>
void myfunc3(const T& firstarg, const U&...secondargs) {
	cout << "�յ��Ĳ���ֵΪ��" << firstarg << endl;
	myfunc3(secondargs...);  // ʹ�õݹ�չ��������
}

void test02() {
	myfunc3(1, 2, 3, 4, 5, 6);
}

/*
	�ɱ����ģ��
*/
template<typename...Args> class MyClass {};  // ��ģ��

template<typename First, typename...Others>
class MyClass<First, Others...> :private MyClass<Others...> {  // ƫ�ػ�
public:
	MyClass() : m_i(0) {
		printf("MyClass::MyClass()ִ���ˣ�this = %p\n", this);
	}

	MyClass(First parf, Others...paro) :m_i(parf), MyClass<Others...>(paro...) {
		printf("MyClass::MyClass()ִ���ˣ�this = %p\n", this);
	}
public:
	First m_i;
};

/*
	���ģ������ػ��汾
*/
template<>class MyClass<> {
public:
	MyClass() {
		cout << "ִ����0�������ػ��汾" << endl;
	}
};

void func() {
	// ʹ�������̳з����������������Ϊһ����������һ����������ֱ��������
	MyClass<int, float, double>myc1;
	cout << endl;
	MyClass<int, float, double>myc2(125, 12.5, 1.25);
	/*
		�ݹ�̳з�ʽչ��������
		
		ִ����0�������ػ��汾
		MyClass::MyClass()ִ���ˣ�this = 012FFCE8
		MyClass::MyClass()ִ���ˣ�this = 012FFCE8
		MyClass::MyClass()ִ���ˣ�this = 012FFCE8
	*/
}

int main() {
	func();
	return 0;
}