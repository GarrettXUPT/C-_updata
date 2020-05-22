#include<iostream>
#include<string>

using namespace std;

/*
	һ��string���ͼ�飺
		string:�ɱ䳤�ַ���,��C++����һ����
	��������ͳ�ʼ��

	����string�����ϵĲ���

*/

/*
	string���弰���ʼ��
*/
void test01() {

	string str1; // Ĭ�ϳ�ʼ������ʾ�մ�""
	string str2 = "I Love China";  // ���ַ���������str2�У������в�����ĩβ��\0
	string str3("I Love China");  // Ч����str2��Ч����һ����
	string str4 = str2;  // ��str2�е����ݿ�����str4��
	string str5(6, 'a');   // ��ʾ6���ַ�a����ַ��������ַ�ʽ���ã���Ϊ����ϵͳ�ڲ�������ʱ����
}

/*
	string�Ĳ���
*/
void test02() {
	/*
		�ж��Ƿ�Ϊ��
	*/
	string str1 = "Garrett";
	cout << "str�Ƿ�Ϊ��: " << str1.empty() << endl;  // 0

	/*
		�����ֽ�/�ַ�����,�����ַ�������(unsigned int)
	*/
	cout << "str's size is " << str1.size() << " str's length is " << str1.length() << endl;  // 7

	/*
		str[n] ����str�еĵ�n���ַ�
	*/
	cout << "number 2 char is " << str1[1] << endl;  // a

	/*
		�ַ�������,�õ�һ���µ�string����
	*/
	cout << str1 + " Walker" << endl;  // Garrett Walker

	/*
		s1 = s2 �ַ�������ĸ�ֵ��str2�е�����ȡ��str1�е�����
	*/
	string str2 = "Walker";
	str1 = str2;
	cout << str1 << endl;  // Walker

	/*
		str1 == str2 �ж������ַ����Ƿ���ͬ��Ҫע����� �ַ�����Сд����
		str1 != str2 �ж������ַ����Ƿ����
	*/
	if (str1 == str2) {
		cout << "str1��str2���" << endl;  // str1��str2���
	}
	else
	{
		cout << "str1��str2�����" << endl;
	}

	/*
		str.c_str()  �����ַ���s�е�����ָ�룬����һ��ָ�������c�ַ�����ָ�볣������\0��β
		Ϊ����c���Լ��ݣ���string����ת��Ϊc�������ַ�����ʽ
	*/


	/*
		��дstring����
	*/
	//string str3;
	//cin >> str3; // 1234
	//cout << "������ַ����ǣ�" << str3 << endl;  // 1234

	/*
		����ֵ��string���
		�����﷨�ϲ������ַ���ֱ����ӣ����� str = "abs" + "www" ���ǿ��� str = "abs" + str + "www"
		�������ַ��������԰���ֱ�����
	*/
	string str4 = str1 + " and " + str2 + " end";
	cout << str4 << endl;  // Walker and Walker end

	/*
		��Χfor���string��ʹ��,���Խ�string�����ַ�����
	*/
	for (auto x : str1) {
		cout << x;  // Walker
	}
	cout << endl;

	/*
		���ַ�����Ϊ��д
	*/
	for (auto& c : str1) {
		c = toupper(c);
	}
	cout << str1 << endl;  // WALKER
}

int main() {

	/*
		string��������
	*/
	test02();

	system("pause");
	return 0;
}