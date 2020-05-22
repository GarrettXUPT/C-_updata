#include"Man.h"

Man::Man() {
    //cout << "使用了man的构造函数" << endl; 
};

/*
    调用父类protected
*/
void Man::setHuman(int age, string name) {
    Human::setAge(age);
    Human::setName(name);
}