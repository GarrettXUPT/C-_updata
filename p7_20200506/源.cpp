#include<iostream>
#include<vector>

using namespace std;

/*
	һ��vector���ͼ��
		������/��̬���飬���Խ��������
		vector���Խ���������װ������Ҳ����Ϊ����

	��������ͳ�ʼ��vector����

	����vector�����ϵĲ���
*/

/*
	vector��ʹ��
*/
void test01() {
	vector<int> vec; // ��ʾ�������int������ vector����ģ�� <int>��ʾ������ģ���ʵ��������
	vector<vector<string>> strlist;  // �ü��ϵ�ÿһ��Ԫ���ֶ���һ��vector<string>���󣬼����׼��ϣ�����vector�в�����װ����
}

/*
	����ͳ�ʼ��vector����
*/
void test02() {
	/*
		����һ���յ�string���͵�vector����
	*/
	vector<string> vec1;
	vec1.push_back("Garrett");
	vec1.push_back("Walker");
	for (string str : vec1) {
		cout << str << " ";
	}
	cout << endl;

	/*
		Ԫ�ؿ����ĳ�ʼ����ʽ
	*/
	vector<string> vec2(vec1);  // ��vec1��Ԫ�ؿ�����vec2�� Ҳ���� vec2 = vec1��ɿ���

	/*
		C++11�У����б��ʼ����������ֵ�����г�ʼ��
	*/
	vector<string> vec3 = { "aaa", "bbb" };

	/*
		����ָ��������Ԫ��,��Ԫ��������صģ�һ�㶼����Բ����
	*/
	vector<string> vec4(10, "aaa");   // ��ʾ������10��aaa�ַ���
	vector<int> intVec(20);  // ������20��Ϊ0��int����
	vector<string> strVec(10);  // ����һ������10��Ԫ�صĿմ�

	/*
		���ֳ�ʼ����ʽ��()��ʾԪ�������ĸ��{}��ʾԪ�����ݵĸ�����ǲ�����
	*/
	vector<int> intVec1{ 10 };  // ����������ֻ����10һ��Ԫ��

	vector<string> strVec1{ 10 }; // ����10��Ԫ�أ�ÿ��Ԫ�ض��ǿմ�

}

/*
	vector�����ϵĲ���,��̬���Ӽ���Ԫ��
*/
void test03() {
	/*
		�ж������Ƿ�Ϊ��
	*/
	vector<int> vec1;
	cout << "vector�Ƿ�Ϊ�գ�" << vec1.empty() << endl;  // 1

	/*
		push_back������������ĩβ���Ԫ��
	*/
	vec1.push_back(1);
	for (int ele : vec1) {
		cout << ele << " ";
	}
	cout << endl;	// 1

	/*
		size����Ԫ�ظ���
	*/
	cout << "the vec's size is " << vec1.size() << endl;

	/*
		clear�Ƴ�����Ԫ�أ����������
	*/
	//vec1.clear();
	//cout << "vector�Ƿ�Ϊ�գ�" << vec1.empty() << endl;  // 0

	/*
		vec[n]����vec�е�n��Ԫ��
	*/
	cout << "��1��Ԫ��" << vec1[0] << endl;  // 1

	/*
		=��ֵ,��vec2��գ�Ȼ��vec1������vec2��
	*/
	vector<int> vec2;
	vec2.push_back(12);
	vec2 = vec1;

	/*
		== != �ж�����������Ԫ���Ƿ���ȣ�Ԫ�������Ƿ�һ�£���Ӧλ�õ�Ԫ��ֵ�Ƿ�һ��
	*/

	/*
		��Χfor������
	*/
	vector<int> vec;
	for (int i = 0; i < 10; i++) {
		vec.push_back(i);
	}

	for (auto& ele : vec) { // ���ʹ������
		cout << ele << " ";  // 0 1 2 3 4 5 6 7 8 9
	}
	cout << endl;

	/*
		��Χfor�����
		��ִ��forѭ���У��в����������м����µ�Ԫ��ֵ��Ҳ������ɾ��ԭ��Ԫ��
	*/


}

int main() {

	test03();

	system("pause");
	return 0;
}