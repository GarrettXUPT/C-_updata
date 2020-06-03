#include<iostream>

using namespace std;
/*
    一、weak_ptr概述
        weak_ptr用来辅助shared_ptr进行工作
        shared_ptr是指的是强指针，weak_ptr指的是弱指针，也是一个类模板，也是智能指针，用来指向一个由shared_ptr管理的对象
        虽然weak_ptr这种指针不控制指针的生存期，将shared_ptr绑定到weak_pt上并不会改变shared_ptr上的引用计数，
        更确切的说：weak_ptr的构造和析构并不会影响指向对象的引用计数，当shared_ptr需要释放所指定的对象是可以正常释放的，不管是否有weak_ptr
        指向该对象，这个weak_ptr能力弱，能力弱就弱在不能控制指向对象的生存期
        作用：
            可以监视的作用，监视shared_ptr的生命周期，是一种对shared_ptr能力的扩充，它不是独立的智能指针，不能用来操作所指向的资源,所以看起来
            像shared_ptr的助手，所以weak_ptr可以监视到它指向的对象存在或者是不存在
        1、weak_ptr的创建
            创建weak_ptr的时候，一般是使用shared_ptr进行初始化
                p1w弱共享p1，p1的引用计数是不变的，但是弱引用计数会改变，弱引用计数会加一，但是只有强引用计数才可以
                控制指针的生存期，弱引用计数并不能决定对象生存期
    二、weak_ptr的常用操作
        1、use_count()获取与该弱指针共享对象的其他shared_ptr的数量，获取的是强引用的数量，或者获得当前所观测资源的强引用计数
        2、expired：是否过期，弱指针的use_count为0，表示该弱指针指向的对象已经不存在了，那么返回true，表示过期了
        3、reset：将该弱引用指针设置为空，不影响该对象的强引用数量，但是指向该对象的弱引用数量会减少一
    三、尺寸问题
        弱指针的尺寸与shared_ptr的尺寸一样大，大小就是裸指针的两倍
*/

/*
    weak_ptr的创建
*/
void test01() {
    auto p1 = make_shared<int>(100);
    weak_ptr<int>p1w(p1); // p1w弱共享p1，p1的引用计数是不变的，但是弱引用计数会改变，弱引用计数会加一，但是只有强引用计数才可以
                           // 控制指针的生存期，弱引用计数并不能决定对象生存期
    weak_ptr<int> p1w2;
    p1w2 = p1;
    weak_ptr<int> p1w3;
    p1w3 = p1w2;  // 将一个弱指针赋给另一个若指针
    /*
        lock就是检查weak_ptr指向的对象是否存在，若存在，那么lock就可以返回一个指向该对象的shared_ptr，原来的强引用计数就会加一，
        若指向的对象不存在，则返回一个空的shared_ptr
    */
    auto p2 = p1w.lock();  // p2的强引用计数就会加一
    cout << p2.use_count() << endl;  // 2
    if (p2 != nullptr) {
        cout << "指向的对象是存在的" << endl;
    }
}

/*
    weak_ptr的引用计数
*/
void test02() {
    /*
        use_count获取与该弱指针共享对象的其他shared_ptr的数量
    */
    auto p1 = make_shared<int>(100);
    auto p2(p1);
    weak_ptr<int> pw = p1;
    cout << "当前强引用计数为: " << pw.use_count() << endl;

    /*
        expired：是否过期，弱指针的use_count为0，表示该弱指针指向的对象已经不存在了，那么返回true，表示过期了
    */
    cout << "弱指针指向的对象是否存在：" << pw.expired() << endl;
    /*
        reset：将该弱引用指针设置为空，不影响该对象的强引用数量，但是指向该对象的弱引用数量会减少一
    */
    pw.reset();
    cout << "弱指针指向的对象是否存在：" << pw.expired() << endl;
    /*
        lock:
    */
    auto p3 = make_shared<int>(42);
    weak_ptr<int> pw1;
    pw1 = p1;  // 使用shared_ptr给weak_ptr进行赋值
    if (!pw1.expired()) {
        auto p4 = pw1.lock(); // 返回一个shared_ptr，并且此时，强引用计数会加一
        if (p4 != nullptr) {
            // 进行相关操作
            int test = 1;
            // 离开该范围强引用计数会恢复为1
        }
    }
    else
    {
        cout << "该弱指针指向的对象已经被释放" << endl;
    }

}

/*
    弱指针的的尺寸
*/
void test03() {
    weak_ptr<int> pw;
    int* p;
    cout << "弱指针尺寸：" << sizeof(pw) << endl;  // 8  内部具有两个裸指针，裸指针分别指向类型对象和控制块
    cout << "裸指针尺寸：" << sizeof(p) << endl;   // 4
    /*
        第一个裸指针指向的是这个智能指针所指向的对象
        第二个裸指针指向一个名为控制块的很大的数据结构，这个控制块中有：
            1、所指对象的强引用计数
            2、所指对象的弱引用计数
            3、其他数据：比如自定义删除器等
        当强指针给弱指针赋值的时候，就会使弱指针也指向强引用的控制块
    */
}

int main() {
    test03();
    return 0;
}