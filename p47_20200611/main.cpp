#include<iostream>
#include<thread>
#include<mutex>
#include<list>
#include<atomic> 

using namespace std;

/*
	һ��֪ʶ����
		1����ٻ���:wait��Ҫ�еڶ�������(lambda)���ʽ������lambda��Ҫ��ȷ�ж�Ҫ����Ĺ��������Ƿ����
			wait(), notify_one(), notify_all()

		2��atomicԭ�Ӳ���

	�����̳߳�
		����������-���ͻ��ˣ�û��һ���ͻ��ˣ��ͺô���һ�����߳�Ϊ�ÿͻ��ṩ����
		1��������Ϸ��2�����ң�������Ϊÿ����Ҷ��������߳�
		2���ȶ������⣺��д�Ĵ����У�ż������һ���̣߳�����д���Ͳ��ȶ�
		�̳߳أ���һ���߳�Ū��һ��ͳһ��������ͬ�������ȣ�ѭ�����õ��̷߳�ʽ�����̳߳�
		�ڳ�������ʱ��һ���ԵĴ�����һ���������̣߳��ڳ���ִ�еĹ����оͲ����ٴ��������������̣߳�������ȶ���

	�����̴߳�������
		1���̴߳��������ļ�������
			2000���߳̾��Ѿ��Ǽ����ˣ��ٴ����̳߳���ͻ����
		2���̴߳��������Ľ���
			1��������ĳЩ�������������ʱ�򣬽ӿ��ṩ�̾ͻὨ���㴴�����߳���������CPU����������ѭ����ʱ��רҵ�����ָʾ��ȷ�������Чִ��
			2�������߳������ҵ���ʱ��һ���߳̾���һ��ִ��ͨ·��
			
*/

class A {

public:
	atomic<int> atm;
	A(){
		atm = 0;
	}

	// ���յ�����Ϣ���뵽���е��߳�
	void inMsgRecvQueue() {
		for (int i = 0; i < 10000; i++) {
			cout << "inMsgRecvQueueִ�У�����һ��Ԫ��" << i << endl;
			/*
				��������������
			*/
			unique_lock<mutex> sbguard(my_mutex);
			msgRecvQueue.push_back(i);  // �������ŵ���Ϣ��������
			myCondition.notify_one();

		}
	}

	// �����ݴ���Ϣ������ȡ�����߳�
	void outMsgRecQueue() {
		int command = 0;
		while (true)
		{
			std::unique_lock<mutex> sbguard(my_mutex);
			myCondition.wait(sbguard, [this] {
				if (!msgRecvQueue.empty()) {
					return true;
				}
				else
				{
					return false;
				}
			});
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

	thread myOutMsgObj1(&A::outMsgRecQueue, &myobja); 
	thread myInMsgObj2(&A::inMsgRecvQueue, &myobja); 

	myOutMsgObj1.join();
	myInMsgObj2.join();
}

/*
	�̳߳ص�ʵ�ַ�ʽ
*/

int main() {
	test01();
	return 0;
}