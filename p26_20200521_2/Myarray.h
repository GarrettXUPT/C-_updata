#pragma once
#ifndef __MYARRAY__H__
#define __MYARRAY__H__
template<typename T2, int size = 10>
class MyArray {
public:
	MyArray(){}
	void func();
private:
	T2 arr[size];
};

/*
	���ⶨ���Ա����
*/
template<typename T2, int size>
void MyArray<T2, size>::func() {
	cout << "MyArray's size is " << size << endl;
}

#endif // !__MYARRAY__H__

