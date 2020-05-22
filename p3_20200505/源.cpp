#include<iostream>

using namespace std;

/*
	һ����Χfor���(���ڱ���һ������)
		��Ϊ��ǿforѭ��

	������̬�ڴ��������
		C�У����û�ʹ�õĴ洢�ռ䣬�г���������̬�洢������̬ �洢��
		C++�У����ڴ��һ����Ϊ����� 
			1��ջ�������еľֲ��������ᱣ��������������Զ�����
			2��������malloc / new ���䣬ʹ��free / delete�ͷ�
			3��ȫ��/��̬�洢������ȫ�ֱ����;�̬����static���������ʱ�ͷ�
			4�������洢�����ַ���������
			5�����������

			�Ѻ�ջ��ͬ����;������
				1��ջ�Ŀռ������޵ģ�ϵͳ�涨�������ٶȿ죬Ҫ��ֹջ���
				2���ѣ�ֻҪ������ʵ��ӵ�е������ڴ棬Ҳ�ڲ���ϵͳ�����ܹ����������ڴ��С֮�ڣ������ٶȽ���
			��C�����У�ʹ��malloc��free������ͷ��ڴ�
			��C++�У�ʹ��new��delete
			newһ��ʹ�ø�ʽ��
				1��ָ������� = new ���ʶ����
				2��ָ�������� = new ���ͱ�ʶ��(��ʼֵ)��
				3��ָ�������� = new ���ͱ�ʶ��[�ڴ浥Ԫ����]; ����һ������
		���ʹ������:
			1����malloc/new,�ͱ�����free / delete�ͷţ��ͷ�Ҳ��Ҫ�ظ��ͷ�
			2��new��malloc�������ǣ�new���������ڴ棬���һ����г�ʼ�� delete�����ͷ��ڴ棬���һ�����������

	����nullptr
		��C++11��������¹ؼ���
		nullptr�����Ҳ�ǿ�ָ�룬���ǿ��Ա����ָ��������0���л���
		NULL��nullptr���Ͳ�ͬ
		����ָ��ĳ�ʼ��������nullptr�ľ�ʹ��nullptr������ʹ��NULL,ֻ��nullptr�ű���Ϊ��������ָ������
*/

/*
	��Χfor���ʾ��
*/
void test01() {
	int arr[] = { 1, 2, 3, 4, 5 };
	for (auto x : arr) {  // ����arr��ÿһ��Ԫ�����ο�����x�в���ӡx��ֵ
		cout << x << endl;
	}

	for (auto x : { 6, 7, 8,9,10 }) {
		cout << x << endl;
	}

	/*
		�Ľ�Ч��,ʡȥ�˿��������������ϵͳЧ��
	*/
	for (auto& x : arr) {
		cout << x << endl;
	}
}

/*
	��̬�ڴ���估�ͷ�
*/
void test02() {
	int* myint = new int; // ����һ���洢�����Ĵ洢�ռ䣬����ָ����ڴ��ָ��
	if (myint == nullptr) {
		cout << "�ڴ����ʧ��" << endl;
		return;
	}
	*myint = 8;
	cout << *myint << endl;
	delete myint;  // һ��Ҫ�ǵ��ͷſռ�


	int* myint1 = new int(18);
	if (myint1 == nullptr) {
		cout << "�ڴ����ʧ��" << endl;
		return;
	}
	cout << *myint1 << endl;
	delete myint1;

	int* arr = new int[100];  // ����һ����СΪ100����������
	if (arr == nullptr) {
		cout << "�ڴ����ʧ��" << endl;
		return;
	}
	int* pointer = arr;
	*pointer++ = 12;   // [0] = 12
 	*pointer++ = 18;  // [1] = 18, ִ�������У����pointer��ʵ�Ѿ�ָ����[2]
	cout << *arr << endl;
	cout << *(arr + 1) << endl;

	delete[] arr; // �ͷ�����ռ䣬[]�в�д�����С

}

/*
	nullptr��ʹ��,nullptr���ǿ�ָ��
*/
void test03() {
	char* p1 = NULL;  // NULLʵ���Ͼ���0
	char* p2 = nullptr;

	cout << typeid(NULL).name() << endl;  // int
	cout << typeid(nullptr).name() << endl;  // std::nullptr_t
}

int main() {
	/*
		��ǿforѭ������
	*/
	//test01();

	/*
		��̬�ڴ���估�ͷ�
	*/
	//test02();

	test03();
	system("pause");
	return 0;
}