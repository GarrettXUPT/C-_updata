#include"Man.h"

Man::Man() {
    //cout << "ʹ����man�Ĺ��캯��" << endl; 
};

/*
    ���ø���protected
*/
void Man::setHuman(int age, string name) {
    Human::setAge(age);
    Human::setName(name);
}

void Man::eat() {
    cout << "����ϲ������ʳ" << endl;
}

Man::~Man() {
    //cout << "������man����������" << endl;
}

void Man::test01() {
    cout << "����Man�е�һ����ͨ����" << endl;
}