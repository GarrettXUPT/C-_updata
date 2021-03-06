#include<iostream>

using namespace std;

/*
C++11
一、并发、进程、线程的基本概念及综述
 1.1 并发：
	一个程序两个或者更多的独立的任务同时进行
	单CPU同一时刻只能执行一个任务，由操作系统调用，单位时间内进行任务切换。
	上下文切换是要有时间开销的，任务越多，开销越大(保存现场，恢复现场)
	随着硬件发展，出现了多处理器计算机。用于服务器和高性能计算领域，就可以进行并行操作

	使用并行的作用：同时执行多个任务，提高性能

 1.2 可执行程序
	磁盘上的文件windows .exe

1.3 进程
	windows下双击可执行程序来运行，linux下 ./文件名运行
	进程就是一个正在运行的可执行程序

1.4 线程
	每个进程都有一个主线程，主线程是唯一的，进程执行，主线程自动执行，主线程执行main函数
	真正执行起来的是线程，线程其实是一条代码的执行通路

	除了主线程之外，也可以通过自己写代码，来创建其他线程，其他线程走的其它道路，每创建一个线程，程序就可以多干一件事
	线程并不是越多越好，每一个线程都需要一个独立的堆栈空间(1M)，线程之间切换要保存很多中间状态，切换回耗费本该程序运行时间

1.5 学习心得
	开发多线程程序，实力的体现，一个是商用的必须要求
	线程实现代码复杂，理解上困难

二、并发的实现方法
	实现并行的手段：
		多个进程实现并发，在单独的进程中，创建多个线程实现并发，自己写代码创建除了主线程之外的其他线程

	2.1 多进程并发
		服务器进程之间的通信

	2.2 多线程并发
		单个进程中，创建多个线程
		线程：进程的执行单位，一个进程中的所有线程是共享内存的，使用多线程开销远远小于多进程
		共享内存带来新问题，即为数据一致性问题
		后续的并发指的是都是多线程并发

	2.3 总结
		和进程比线程的优点：
			1、线程启动速度快，更轻量级
			2、系统资源开销较小，执行速度快，比如共享内存这种通信方式，比其他任何通信方式都快
		缺点：
			使用起来有难度，要小心处理数据一致性问题

三、C++11新标准线程库
	以往：windows下： CeatThread(), _beginthread(),大多数情况下，_beginthread()较为安全
		  Linux下：pthread_create():创建线程
		  临界区、互斥量
		  以往的多线程代码不能跨平台编译
		  POSIX thread(pthread)可跨平台，但是需要配置
		  从C++11新标准开始，C++本身增加了多线程的支持，是可移植的，大大减少了开发人员的工作量
*/

int main() {

	return 0;
}
