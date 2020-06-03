#include<iostream>
#include<thread>
#include<mutex>
#include<list>

using namespace std;

/*
	һ����������std::condition_variable/wait/notify_one
		�߳�A���ȴ�һ����������
		�߳�B������Ϣ�����д�����Ϣ���߳�B֪ͨ�߳�A��ʱ�򣬾�������A������ʱ��
		std::condition_variableʵ�����Ǹ��࣬����������ص�һ���࣬�ȴ�������ɣ����������Ҫ�뻥����֮����Ϲ�����
		notify_one��ֻ��֪ͨһ���߳�

	����notify_all
		��wait������߳�ȫ������
*/

/*
	���ݱ���������
*/
class A {

public:
	// ���յ�����Ϣ���뵽���е��߳�
	void inMsgRecvQueue() {
		for (int i = 0; i < 10000; i++) {
			cout << "inMsgRecvQueueִ�У�����һ��Ԫ��" << i << endl;
			/*
				��������������
			*/			
			unique_lock<mutex> sbguard(my_mutex);
			msgRecvQueue.push_back(i);  // �������ŵ���Ϣ��������
			/*
				���﻽�ѵ���wait���̣߳�ִ�������У��ͻὫoutMsgRecQueue����wait�ᱻ����

				��outMsgRecQueue���ڴ������񣬶����ǿ���wait����ȴ����ѣ���ʱnotify_one�ͻ�û��Ч��
			*/
			myCondition.notify_all();
			
		}
	}

	// �����ݴ���Ϣ������ȡ�����߳�
	void outMsgRecQueue() {
		int command = 0;
		while (true)
		{ 
			std::unique_lock<mutex> sbguard(my_mutex);
			// ʹ��lambda���ɿɵ��ö��󣬴˴���wait�������ȴ��������㣬���ڶ��������ķ���ֵ��false����ôwait�ͻ������������������������
			// �������������̵߳���notify_one()Ϊֹ�����ڶ����������ص���true����ôwaitֱ�ӷ���
			// ��waitû�еڶ�����������ô�ͺ͵ڶ�����������trueЧ��һ�£��������ִ��
			// �������߳�ʹ��notify_one����λ�õ�wait״̬���ѣ����Ѻ�
			// 1���ٴβ��ϳ��Ի�ȡ��������������ȡ��������ô���̾ͻῨ��wait������Ż�ȡ������������ȡ���ˣ��ͼ���ִ��
			// 2����ʱ���ٴ��жϵڶ��������Ƿ񷵻�true������������ִ�У�������false������ٴν���wait״̬���ȴ�������
			// �߳���wait״̬ʱ��������С������Ч�ʽϸ�
			myCondition.wait(sbguard, [this] {
				if (!msgRecvQueue.empty()) {
					return true;
				}
				else
				{
					return false;
				}
			});
			// �����ߵ����������һ�������ŵģ����򣬴��벻����ִ�е����Ҳ����˵��������msgRecvQueue����������һ�����ݵ�
			command = msgRecvQueue.front();  // ���ض��е�һ��Ԫ�أ����ǲ����Ԫ���Ƿ����
			msgRecvQueue.pop_front();  // �Ƴ����е�һ��Ԫ�أ����ǲ�����
			// ������ſ��������Ч��
			cout << "outMsgRecQueue()ִ�У�ȡ��һ��Ԫ��" << command << endl;
			sbguard.unlock();
			// ִ��һЩ����Ķ���
		}
			
	}

private:
	list<int> msgRecvQueue;  // ר�����ڴ�����Ҹ�������������

	mutex my_mutex;  // ������һ��������

	std::condition_variable myCondition;  // ����һ��������������
};

void test01() {
	A myobja;

	thread myOutMsgObj1(&A::outMsgRecQueue, &myobja); // �ڶ������������ã��������ܱ�֤���߳���ʹ�õ���myobja�������
	thread myOutMsgObj2(&A::outMsgRecQueue, &myobja); // �ڶ������������ã��������ܱ�֤���߳���ʹ�õ���myobja�������

	thread myInMsgObj(&A::inMsgRecvQueue, &myobja);

	myOutMsgObj1.join();
	myOutMsgObj2.join();

	myInMsgObj.join();
}

int main() {
	test01();
	return 0;
}