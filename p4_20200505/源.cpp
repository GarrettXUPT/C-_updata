#include<iostream>

using namespace std;

/*
	һ���ṹ�ع�
		�ṹ���Զ������������
		C++�еĽṹ��C�Ľṹ��ʲô����
			C++�еĽṹ���˾߱�C�е����й����⣬�������˺ܶ���չ���ܣ���ͻ���ľ��ǣ�
			C++�еĽṹ�����г�Ա���������һ�������C�ж����Ա����

	����Ȩ�����η�
		public:
			���εĶ�������ô��Щ�����Ϳ��Ա������ʣ�����籩¶
		private:
			���εĶ�����ֻ�����ڲ��ĳ�Ա��������ʹ�ã�������籩¶
		protected�����н���

	��������
		�û��Զ������������
		�ṹ���ൽ����ʲô����
			1������C++���У�C��û���������
			2���ṹstruct ��class
			3����C++�У�����һ�����ڸ���ı���(����)���ṹ����Ľ����ṹ����
			4�������Ƕ����ǽṹ���������Ƕ���һ���ܹ��洢���ݲ��Ҿ���ĳ�����͵��ڴ�ռ�
			5��C++�нṹ���༰������
				1. �������C++�ṹ���еĳ�Ա��������Ա������Ĭ�Ϸ��ʼ�����public
				2. ���ڲ���Ա��������Ա����Ĭ�Ϸ��ʼ�����private
				3. C++�ṹ��̳�Ĭ�ϵ���public����C++��ļ̳�Ĭ�϶���private
		˵����
			1����׼��C++���а����˴����ḻ����ͺ���
			2��C++�б����ö���ʹ����
	
	�ġ������֯
		�������������Ķ���(ʵ��)���з��룬һ��һ�������һ���ļ���
*/

/*
	�ṹ
*/
typedef struct student
{
	// ��Ա����
	int number;  // ѧ��
	char name[100]; // ѧ����

	/*
		��Ա����
	*/
	void printStu() {
		cout << "stu.number = " << number << " stu.name = " << name << endl;
	}

}STU;

/*
	��ӡ�ṹ,�β�ʹ�ýṹ����������
*/
void printStu(STU const stu) {
	cout << "stu.number = " << stu.number << " stu.name = " << stu.name << endl;
}

void changeStu(STU& stu) {
	stu.number = 02;
	strcpy_s(stu.name, sizeof(stu.name), "Walker");
}

int main() {
	/*
		�ṹ��ʹ��
	*/
	STU stu1; 
	stu1.number = 01;

	strcpy_s(stu1.name, sizeof(stu1.name), "Garrett");
	//printStu(stu1);
	/*
		���ó�Ա����
	*/
	stu1.printStu();
	
	changeStu(stu1);
	printStu(stu1);

	system("pause");
	return 0;
}