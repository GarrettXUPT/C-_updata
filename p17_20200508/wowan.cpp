#include"wowan.h"

Woman::Woman() {
    cout << "调用了Woman的构造函数" << endl;
}

void Woman::testClass() {
    cout << "使用的是Woman类" << endl; 
}

/*
    实现基类中的的纯虚函数
*/
void Woman::eat() {
    cout << "女人喜欢吃米饭" << endl;
}

Woman::~Woman() {
    cout << "调用了woman的析构函数" << endl;
}