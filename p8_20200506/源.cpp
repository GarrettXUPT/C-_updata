#include<iostream>
#include<vector>
#include<string>

using namespace std;

/*
	һ�����������
		��������һ�ֱ���������Ԫ�ص��������ͣ��е���ָ�룬���Ϊ����������ָ�������е�ĳ��Ԫ��
		���������Զ�ȡ�����е�Ԫ��ֵ��Ҳ�����޸�ĳ����������ָ���Ԫ��ֵ
		����ʹ�õ��������������е�Ԫ��

	���������ĵ���������
		������begin()/end()���������������rbegin()/rend()���������Ƿ��ص�������
	
	���������������
		1.*iter���ص�����iter��ָ��Ԫ�ص����ã��豣֤������ָ�������Ч������Ԫ�أ�����ָ��end��endָ��������һ��Ԫ�ص���һ��Ԫ��
		2.++iter��iter++�����Ѿ�ָ��end����ô�Ͳ������Լ���
		3.--iter��iter--��ָ��ǰԪ�ص���һ��Ԫ��
		4.iter1 == iter2, iter1 != iter2,������������ָ�����ͬһ��Ԫ�أ�����ȣ����򣬲���
		5.ȷ��������ָ�������Ч��Ԫ�أ����������������ָ��������������֮��ľ���
	
	�ġ�const_iterator����������ʾ������ָ���Ԫ�ص�ֵ�ǲ��ɸı�ģ�ֻ�ܴӵ������ж�ȡԪ�أ�����һЩ����ָ��
		����const vector<int>��ʹ�õ�����ʱ��Ҫ�ó���������

		cbegin()��cend()������������begin��end���ƣ�cbegin��cend���صĶ��ǳ���������

		vec.insert(begin, 80); ��80���뵽�����ĵ�һ��λ��
		vec.erase(begin) ɾ��beginλ�õ�Ԫ��

	�塢������ʧЧ����
		��ѭ����ȡʱ�����������������ݻ���ɾ������
		�ڲ���������������(ʹ�õ�����ѭ����),ǧ��Ҫ�ı�vector��������������ܵ�������Ԫ�ص�ָ�롣���á�������ʧЧ
*/

/*
	�����ĵ���������
*/
void test01() {
	/*
		��������ʹ��
	*/
	vector<int> vec;
	for (int i = 0; i < 10; i++) {
		vec.push_back(i);
	}

	/*
		���������������Ϊ�գ���begin��end���صĵ�������ͬ
	*/
	vector<int>::iterator start = vec.begin();
	while (start != vec.end()) {
		cout << *start++ << " ";  // 0 1 2 3 4 5 6 7 8 9
	}
	cout << endl;

	

	vector<int> vec1;
	vector<int>::iterator start1 = vec1.begin();
	vector<int>::iterator end1 = vec1.end();
	if (start1 == end1) {
		cout << "������Ϊ��" << endl;
	}

	/*
		�������,�Ӻ���ǰ����Ԫ��
		rbegin:����ָ������һ��Ԫ��
		rend:����һ�������������ָ���һ��Ԫ�ص�ǰһ��Ԫ��
	*/
	vector<int>::reverse_iterator start2 = vec.rbegin();
	while (start2 != vec.rend()) {
		cout << *start2++ << " ";  // 9 8 7 6 5 4 3 2 1 0
	}
	cout << endl;

	// const_iterator������
	vector<int>::const_iterator start3 = vec.begin();
	while (start3 != vec.end()) {
		cout << *start3++ << " ";
	}
	cout << endl;

	// cbegin��cend������,���ص��ǳ���������
	vector<int>::const_iterator start4 = vec.cbegin();
	while (start4 != vec.cend()) {
		cout << *start4++ << " ";  // 0 1 2 3 4 5 6 7 8 9
	}
	cout << endl;
}

/*
	��θı�vector�е�ֵ��ʹ��������ֵ����Ч����������ʾ
*/
void test02() {
	vector<int> vec;
	for (int i = 0; i < 10; i++) {
		vec.push_back(i);
	}
	auto start = vec.begin();
	int count = 0;
	while (start != vec.end()) {  // ��ֹendʧЧ
		// cout << *start++ << " ";  // 0 1 2 3 4 5 6 7 8 9
		start = vec.insert(start, 20 + count);  // ��ֹstartʧЧ
		count++;
		if (count == 3) {
			break;
		}
	}
	while (start != vec.end()) {
		cout << *start++ << " ";  // 22 21 20 0 1 2 3 4 5 6 7 8 9
	}
	cout << endl;
}

/*
	ʹ�õ���������string��������
*/
void test03() {
	string str("Garrett Walker");
	auto iter = str.begin();
	while (iter != str.end()) {
		*iter = toupper(*iter);
		iter++;
	}
	cout << str << endl;  // GARRETT WALKER
}

/*
	vector���ò������ڴ��ͷ�
	ʵ������
		1��SeverName = 1��	����������
		2��SeverID = 10000  ������ID
*/

typedef struct {
	char itemname[40]; 
	char itemcontent[100];
}conf;

char* getinfo(vector<conf*>& conflist, char const* pitem) {
	for (auto pos = conflist.begin(); pos != conflist.end(); pos++) {
		if (strcmp((*pos)->itemname, pitem) == 0) {
			return (*pos)->itemcontent;
		}
	}
	return nullptr;
}

void test04() {
	conf* pconf1 = new conf;
	strcpy_s(pconf1->itemname, sizeof(pconf1->itemname), "SeverName");
	strcpy_s(pconf1->itemcontent, sizeof(pconf1->itemcontent), "1��");
	
	conf* pconf2 = new conf;
	strcpy_s(pconf2->itemname, sizeof(pconf2->itemname), "SeverID");
	strcpy_s(pconf2->itemcontent, sizeof(pconf2->itemcontent), "10000");

	vector<conf*> conflist;
	conflist.push_back(pconf1);
	conflist.push_back(pconf2);

	char* p_tmp = getinfo(conflist, "SeverName");
	if (p_tmp != nullptr) {
		cout << p_tmp << endl;  // 1��
	}
	// �ͷ��ڴ�
	vector<conf*>::iterator pos = conflist.begin();
	while (pos != conflist.end()) {
		delete (*pos);  //*pos�����ڲ���Ԫ��,�ͷ�new�������ڴ�
		pos++;
	}
}

int main() {

	test04();

	system("pause");
	return 0;
}