#include"Man.h"

Man::Man() {
    //cout << "使用了man的构造函数" << endl; 
};

/*
    调用父类protected
*/
//void Man::setHuman(int age, string name) {
//    Human::setAge(age);
//    Human::setName(name);
//}

void Man::eat() {
    cout << "男人喜欢吃面食" << endl;
}

Man::~Man() {
    //cout << "调用了man的析构函数" << endl;
}

void Man::friendTest() {
    cout << "这是一个友元函数" << endl;
}