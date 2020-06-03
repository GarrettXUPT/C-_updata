#include<iostream>
#include<thread>
#include<vector>
#include<list>
#include<mutex>


using namespace std;

/*
���Ľڣ���������̡߳����ݹ��������������������
1�������͵ȴ�����߳�
	1. ����߳�ִ��˳���ǲ�ȷ���ģ��������ϵͳ�ڲ����̵߳ĵ��Ȼ����й�
	2. ���̵߳ȴ����߳����н������Ž��������ʹ��join�ķ�����ʹ���̳߳�������ȶ�
	3. ʹ�õ�������������̣߳�����������thread�������飬������ǹ�������̺ܷ߳���

2�����ݹ����������
	1. ֻ�����ݣ���ȫ�ȶ�������Ҫ������ֶΣ�ֱ�Ӷ��Ϳ���
	2. �ֶ���д������
		��򵥵Ĳ�����������������ʱ����д��д��ʱ���ܶ��������̲߳���ͬʱд���˸��̲߳���ͬʱ��
		���������л������³������
	3. ��������
		���ݹ����������ڶ�һ����λ��Ʊ

3���������ݵı�����������
	������Ϸ��������
		����֪���������̣߳�
			һ���߳��ռ�����������������д��һ��������
			һ���̴߳Ӷ�����ȡ����ҷ��������������Ȼ��ִ�������Ҫ������
		ʹ��vector��list�� list��˳�����ɾ��������Ч�ʽϸߣ�vector��������Ĳ����ɾ��Ч�ʽϸ�

		׼���ó�Ա������Ϊ�̺߳����ķ���д�̣߳���Ҫ���뻯������߳����ݹ������⣺ʹ�û�����


����ڡ��������ĸ���÷���������ʾ��������
1��������(mutex)�Ļ�������
	�����������ݣ�����ʱ���ô��뽫����������ס������������������ݵ��̱߳���ȴ�����������֮�������̲߳��ܲ�������
		��������һ�����������һ������ͬһʱ�䣬����̶߳��ɳ���ʹ��lock()��Ա������������ֻ��һ���߳̿��������ɹ�
	
	�ɹ��ر�־��lock���������˷��أ���û���ɹ�����ô�̵߳�ִ�����̾ͻῨ��lock�ϣ����ϳ���ȥ������ֱ���ɹ�
		
		������ʹ��ҪС�ģ����˴ﲻ������Ч�������˻�Ӱ��Ч��

2����������ʹ��
	2.1 lock��unlock
		���裺��lock�����������������ݣ�unlock
		lock��unlockҪ�ɶ�ʹ�ã���lock��ȻҪ��unlock����Ӧ��Ҳ���������һ��lockȷ�����˶��unlock
		��������ʹ�ù�����ᵼ�³�����������Ҹô����Ƿǳ����Ų��

		Ϊ��ֹ����������unlock������һ����lock_guard��ģ�壬������unlock���ú������Զ�unlock
		lock_guard:ͬʱȡ��lock��unlock
		����ָ��(unique_ptr<>)���������ͷ��ڴ治Ҫ������ָ���Զ��ͷ�,��ķʽ����

	2.2 lock_guard��ģ�壬����ֱ��ȡ��lock��unlock��Ҳ����˵��ʹ��lock_guard֮�󣬾���Ҳ����ʹ��lock��unlock

3������
	���ׯ���ڱ��������ģ����������ڵ����������˾�������״̬
	
	c++�У�һ������������һ������������������������Ҳ����������������
		�����߳�A, B
		1���߳�Aִ�е�ʱ������߳�������1�����ɹ���Ȼ��ȥlock��2.����Ҫȥ��lock2ʱ����ʱ�������������л�
		2���߳�B��ʼִ�У�����߳�ȥ����2�����ɹ���Ȼ��ȥlock��1��
		3����ʱ��������Ͳ����ˣ��߳�A�ò�����2���߳�B�ò�����1�����̶��߲���ȥ���߳�A���߳�B���߳�B�ȴ��߳�A
	
	���������
		ֻҪ�Ǽ�����˳����һ�µģ��Ͳ����������

	lock()����ģ�壺(����������������)
		һ����ס�������߶��������(��������)�����Ͳ������ڶ���߳���˳�����⵼�������ķ���
		������������һ��û��ס����������������л���������ס�������������ߣ���������һ�������ϣ���ô���ͷ���ǰ����
		Ҫô��������������ס��Ҫô������������û��ס
		ʹ�÷�ʽ��
			lock(mutex1, mutex2...);
			�൱��ÿһ����������������lock 
			������mutex1.unlock()
				  mutex2.unlock()

	adopt_lock���ṹ�������һ��������ã���ʾ����������Ѿ�lock������Ҫ��lock_guard�жԶ����ٴν���lock��

	lockһ���������������������ʹ��(����һ��һ����
*/


/*
	��������
	ֻ��������
*/
vector<int> g_v = { 1, 2, 3 };


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
			//my_mutex.lock();
			// �ô��������޶�lock_guard������
			{
				lock_guard<mutex> sbguard(my_mutex);
				msgRecvQueue.push_back(i);  // �������ŵ���Ϣ��������
			}
			
			/*
				����д����ϣ�����
			*/
			//my_mutex.unlock();
		}
	}

	// �����ݴ���Ϣ������ȡ�����߳�
	void outMsgRecQueue() {
		int command;
		for (int i = 0; i < 10000; i++) {
			bool result = outMsgLULProc(command);
			if (result == true) {
				cout << "OutMsgRecvQueue()ִ�У�ȡ��Ԫ��" << command << endl;
				/*
					�������ݴ���
				*/
			}
			else
			{
				cout << "OutMsgRecvQueue()ִ�У����Ƕ�����Ԫ��Ϊ��" << endl;
			}
		}
		return;
	}

private:
	list<int> msgRecvQueue;  // ר�����ڴ�����Ҹ�������������

	mutex my_mutex;  // ������һ��������
	
	bool outMsgLULProc(int& command) {
		/*
			ʹ�������
			lock_guard����ͺ�����ִ����lock()����
			����������Ϊreturnʱ��������ʱ�������unlock��
			Ҳ����ʹ�� ������ ���޶������򣬼�Ϊ�������������lock_guard����������
		*/
		lock_guard<mutex> sbguard(my_mutex);  // ���������Լ��ı�
		/*
			����
		*/
		//my_mutex.lock();
		if (!msgRecvQueue.empty()) {
			// ����Ϣ���в�Ϊ��
			command = msgRecvQueue.front();  // ���ض��е�һ��Ԫ�أ����ǲ����Ԫ���Ƿ����
			msgRecvQueue.pop_front();  // �Ƴ����е�һ��Ԫ�أ����ǲ�����
			/*
				�ú��������������ڣ�������ÿһ�������˳�ǰ��Ҫִ��unlock
			*/
			//my_mutex.unlock();
			return true;
		}
		//my_mutex.unlock();
		return false;
	}
};



/*
	��ʾ��������
*/
class B {
public:
	// ���յ�����Ϣ���뵽���е��߳�
	void inMsgRecvQueue() {
		for (int i = 0; i < 10000; i++) {
			cout << "inMsgRecvQueueִ�У�����һ��Ԫ��" << i << endl;

			/*
				��������������,������1��������2
				����������һ�����ţ����ܻᱣ�治ͬ�����ݿ�
			*/
			//lock_guard<mutex> sbguard1(my_mutex1);
			//lock_guard<mutex> sbguard2(my_mutex2);
			my_mutex1.lock();
			my_mutex2.lock();
			msgRecvQueue.push_back(i);  // �������ŵ���Ϣ��������
			/*
				����д����ϣ�����
			*/
			my_mutex1.unlock();
			my_mutex2.unlock();
		}
	}

	// �����ݴ���Ϣ������ȡ�����߳�
	void outMsgRecQueue() {
		int command;
		for (int i = 0; i < 10000; i++) {
			bool result = outMsgLULProc(command);
			if (result == true) {
				cout << "OutMsgRecvQueue()ִ�У�ȡ��Ԫ��" << command << endl;
				/*
					�������ݴ���
				*/
			}
			else
			{
				cout << "OutMsgRecvQueue()ִ�У����Ƕ�����Ԫ��Ϊ��" << endl;
			}
		}
		return;
	}

private:
	list<int> msgRecvQueue;  // ר�����ڴ�����Ҹ�������������
	mutex my_mutex1;  // ������һ��������
	mutex my_mutex2;

	bool outMsgLULProc(int& command) {
		/*
			ʹ�������
			lock_guard����ͺ�����ִ����lock()
			����������Ϊreturnʱ��������ʱ�������unlock��Ҳ����ʹ�ô��������޶������򣬼�Ϊ�������������lock_guard����������
		*/
		//lock_guard<mutex> sbguard(my_mutex1);  // ���������Լ��ı�
		/*
			����
			����������������2������1
			����Ҫ������������ô��������1������2
		*/

		/*
			�˴���lock����һ����ס���������������ϵĻ�����(�������������˲���)
			ʹ�����Ļ��Ͳ�������ڶ���߳��У���Ϊ����˳�����⵼�µ������ķ���
			������ʹ��������������ס��������������������û��ס������ֻ����һ��������һ��û���ɹ�������������ס�������н���
			��������unlock��ͬʹ�ã�Ҳ����ֱ��ʹ��lock_guard
			��ʵ�����ù����У�ͬʱlock������ǱȽ��ٵ�
		*/
		lock(my_mutex1, my_mutex2);

		/*
			��ʱ���ٵ���unlock����Ϊ������lock_guardʱ�򣬾ͻ��Զ�unlock����Ϊ�����adopt_lock���Ѿ�lock�ˣ��Ͳ���Ҫ�ٴ�lock
		*/
		lock_guard<mutex> sbguard1(my_mutex1, adopt_lock);
		lock_guard<mutex> sbguard2(my_mutex2, adopt_lock);

		if (!msgRecvQueue.empty()) {
			// ����Ϣ���в�Ϊ��
			command = msgRecvQueue.front();  // ���ض��е�һ��Ԫ�أ����ǲ����Ԫ���Ƿ����
			msgRecvQueue.pop_front();  // �Ƴ����е�һ��Ԫ�أ����ǲ�����

			/*
				�ú��������������ڣ�������ÿһ�������˳�ǰ��Ҫִ��unlock
			*/
			return true;
		}
		return false;
	}
};



/*
	�����͵ȴ�����߳�
*/
/*
	�߳���ں���
*/
void test01(int num) {
	cout << "���߳�" << num << "�Ĵ���" << endl;
	//.....Ҳ��֪�����˵�ɶ
	//cout << "���߳�" << num << "������" << endl;
}
void testf1() {
	cout << "���߳̿�ʼִ��" << endl;
	vector<thread> mythreads;
	// ����ʮ���̣߳�ÿ���̶߳�ͳһʹ��test01����
	for (int i = 0; i < 10; i++) {
		mythreads.push_back(thread(test01, i)); // ��������ʼִ���߳�,�߳�ִ��˳���ǲ�һ�µ�
	}
	for (auto iter = mythreads.begin(); iter != mythreads.end(); iter++) {
		iter->join();  // �ȴ�10���߳�ȫ����������
	}
	cout << "���߳�ִ�����" << endl;
}



/*
	��������
*/
/*
	��ӡ��������
*/
void test02() {
	cout << "id = " << this_thread::get_id() << " ��ӡ = " << g_v[0] << g_v[1] << g_v[2] << endl;
}
void testf2() {
	cout << "���߳̿�ʼִ��" << endl;
	vector<thread> mythreads;
	// ����ʮ���̣߳�ÿ���̶߳�ͳһʹ��test01����
	for (int i = 0; i < 10; i++) {
		mythreads.push_back(thread(test02)); // ��������ʼִ���߳�,�߳�ִ��˳���ǲ�һ�µ�
	}
	for (auto iter = mythreads.begin(); iter != mythreads.end(); iter++) {
		iter->join();  // �ȴ�10���߳�ȫ����������
	}
	cout << "���߳�ִ�����" << endl;
}


/*
	�������ݵı�����������
*/
void test03() {
	A myobja;

	thread myOutMsgObj(&A::outMsgRecQueue, &myobja); // �ڶ������������ã��������ܱ�֤���߳���ʹ�õ���myobja�������

	thread myInMsgObj(&A::inMsgRecvQueue, &myobja);

	myOutMsgObj.join();
		
	myInMsgObj.join();
}


/*
	����������ʾ����
*/
void test04() {
	B myobjb;

	thread myOutMsgObjb(&B::outMsgRecQueue, &myobjb); // �ڶ������������ã��������ܱ�֤���߳���ʹ�õ���myobja�������
	thread myInMsgObjb(&B::inMsgRecvQueue, &myobjb);
	myOutMsgObjb.join();
	myInMsgObjb.join();
}


int main() {
	test04();
	system("pause");
	return 0;
}