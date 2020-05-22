#include<iostream>
#include<vector>
#include<string>

using namespace std;

/*
	一、迭代器简介
		迭代器是一种遍历容器内元素的数据类型，有点像指针，理解为迭代器用来指向容器中的某个元素
		迭代器可以读取容器中的元素值，也可以修改某个迭代器所指向的元素值
		尽量使用迭代器访问容器中的元素

	二、容器的迭代器类型
		迭代器begin()/end()操作，反向迭代器rbegin()/rend()操作，都是返回迭代类型
	
	三、迭代器运算符
		1.*iter返回迭代器iter所指向元素的引用，需保证迭代器指向的是有效地容器元素，不能指向end，end指向的是最后一个元素的下一个元素
		2.++iter和iter++，若已经指向end，那么就不可以自加了
		3.--iter和iter--，指向当前元素的上一个元素
		4.iter1 == iter2, iter1 != iter2,若两个迭代器指向的是同一个元素，则相等，否则，不等
		5.确保迭代器指向的是有效地元素，两个迭代器相减，指的是两个迭代器之间的距离
	
	四、const_iterator迭代器，表示迭代器指向的元素的值是不可改变的，只能从迭代器中读取元素，更像一些常量指针
		若是const vector<int>则使用迭代器时候，要用常量迭代器

		cbegin()和cend()函数，功能与begin和end类似，cbegin和cend返回的都是常量迭代器

		vec.insert(begin, 80); 将80插入到容器的第一个位置
		vec.erase(begin) 删除begin位置的元素

	五、迭代器失效问题
		在循环读取时，向容器中增加内容或者删除内容
		在操作迭代器过程中(使用迭代器循环体),千万不要改变vector的容量，否则可能导致容器元素的指针。引用。迭代器失效
*/

/*
	容器的迭代器类型
*/
void test01() {
	/*
		迭代器的使用
	*/
	vector<int> vec;
	for (int i = 0; i < 10; i++) {
		vec.push_back(i);
	}

	/*
		正向迭代，若容器为空，则begin和end返回的迭代器相同
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
		cout << "该容器为空" << endl;
	}

	/*
		反向迭代,从后向前遍历元素
		rbegin:返回指向倒数第一个元素
		rend:返回一个反向迭代器，指向第一个元素的前一个元素
	*/
	vector<int>::reverse_iterator start2 = vec.rbegin();
	while (start2 != vec.rend()) {
		cout << *start2++ << " ";  // 9 8 7 6 5 4 3 2 1 0
	}
	cout << endl;

	// const_iterator迭代器
	vector<int>::const_iterator start3 = vec.begin();
	while (start3 != vec.end()) {
		cout << *start3++ << " ";
	}
	cout << endl;

	// cbegin和cend迭代器,返回的是常量迭代器
	vector<int>::const_iterator start4 = vec.cbegin();
	while (start4 != vec.cend()) {
		cout << *start4++ << " ";  // 0 1 2 3 4 5 6 7 8 9
	}
	cout << endl;
}

/*
	如何改变vector中的值，使迭代器的值不是效果，程序演示
*/
void test02() {
	vector<int> vec;
	for (int i = 0; i < 10; i++) {
		vec.push_back(i);
	}
	auto start = vec.begin();
	int count = 0;
	while (start != vec.end()) {  // 防止end失效
		// cout << *start++ << " ";  // 0 1 2 3 4 5 6 7 8 9
		start = vec.insert(start, 20 + count);  // 防止start失效
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
	使用迭代器遍历string类型数据
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
	vector常用操作及内存释放
	实践程序：
		1、SeverName = 1区	服务器名称
		2、SeverID = 10000  服务器ID
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
	strcpy_s(pconf1->itemcontent, sizeof(pconf1->itemcontent), "1区");
	
	conf* pconf2 = new conf;
	strcpy_s(pconf2->itemname, sizeof(pconf2->itemname), "SeverID");
	strcpy_s(pconf2->itemcontent, sizeof(pconf2->itemcontent), "10000");

	vector<conf*> conflist;
	conflist.push_back(pconf1);
	conflist.push_back(pconf2);

	char* p_tmp = getinfo(conflist, "SeverName");
	if (p_tmp != nullptr) {
		cout << p_tmp << endl;  // 1区
	}
	// 释放内存
	vector<conf*>::iterator pos = conflist.begin();
	while (pos != conflist.end()) {
		delete (*pos);  //*pos才是内部的元素,释放new出来的内存
		pos++;
	}
}

int main() {

	test04();

	system("pause");
	return 0;
}