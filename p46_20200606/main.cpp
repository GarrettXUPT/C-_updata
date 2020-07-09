#include<iostream>
#include<mutex>
#include<thread>
#include<list>
#include<Windows.h>

// ����һ������
//#define __WINDOWSJQ_

using namespace std;

/*
	һ��windows�ٽ���
		C++�еĻ������ڹ����Ͼ͵���windows���ٽ�����������ٽ����������һ���������ٽ����Ժ��ٶԹ������ݽ��в���

	������ν����ٽ�������
		��ͬһ���߳��У�windows�ٽ���֧�ֶ�ν����ٽ��������ǲ����깲�������Ժ󣬶�Ӧ��Ӧ��Ҫ����뿪�ٽ���
		EnterCriticalSection(&my_winsec);  // �����ٽ���(����)
		LeaveCriticalSection(&my_winsec);	// �뿪�ٽ���(����)
		C++11�Ļ��������ԣ�ͬһ���߳��У������Զ�μ�������ν���

	�����Զ���������
		std::lock_guard<std::mutex> �Զ������ͽ���

	�ġ�recursive_mutex�ݹ�Ķ�ռ������
		std::mutex:��ռʽ���������Լ�lock���Ժ󣬱��˲������ٴ�lock
		std::recursive_mutex:�ݹ�ʽ��ռ�����������Խ�����lock������ͬһ���̣߳�ͬһ����������α�lock��Ч����Ҫ��mutex��
		��ʹ���˶�ε��ã���Ҫ���Ǵ����Ƿ����Ż��Ŀռ䣬�Ż��Ժ���Ե���һ�ν������
		�ݹ������˵������

	�塢����ʱ�Ļ�����std::timed_mutex��std::recursive_timed_mutex 
		std::timed_mutex:����ʱ���ܵĶ�ռ������
			try_lock_for():�ȴ�һ��ʱ��,���ȴ���ʱ��û�õ��������̾ͻ��������
			try_lock_until():����Ĳ�����δ����һ��ʱ��㣬��δ����ʱ�仹û����ʱ���ڣ������õ����������̾ͼ������У���ʱ�䵽��û�õ�����
							 ����Ҳ���������
		std::recursive_timed_mutex������ʱ���ܵĵݹ��ռ������

*/

// ���������Զ��ͷ�windows�µ��ٽ�������ֹ����LeaveCriticalSection����������������lock_guard
class CWinLock {  // ��Դ��ȡ����ʼ��(RAII)�������Ĺؼ������ڹ��캯���й���һ����Դ��Ȼ�������������������������
public:
	CWinLock(CRITICAL_SECTION* pCritmp) {
		m_critical = pCritmp;  // ָ��ָ�򴫵ݽ������ٽ�������
		EnterCriticalSection(m_critical);
	}

	~CWinLock() {
		LeaveCriticalSection(m_critical);
	}

private:
	CRITICAL_SECTION* m_critical;
};

class A {

public: 

	void testfunc1() {
		std::lock_guard<std::timed_mutex> sbguard(my_mutex);
		// �ɸ�������
		testfunc2();  // ���������testfunc2�ᵼ�³����������Ϊ��ν����˼���
	}

	void testfunc2() {
		std::lock_guard<std::timed_mutex>sbguard(my_mutex);
		// ����һЩ��
	}


	A() {
#ifdef __WINDOWSJQ_
	InitializeCriticalSection(&my_winsec);  // ��ʼ���ٽ���
#endif // __WINDOWSJQ_
	}

	// ���յ�����Ϣ���뵽���е��߳�
	void inMsgRecvQueue() {
		for (int i = 0; i < 10000; i++) {
			cout << "inMsgRecvQueueִ�У�����һ��Ԫ��" << i << endl;
#ifdef __WINDOWSJQ_
			// ʹ���Զ�������뿪�ٽ�����ʹ�����ַ�ʽ��ν����ٽ���Ҳû������
			CWinLock wlock(&my_winsec);
			//EnterCriticalSection(&my_winsec);  // �����ٽ���(����)
			//EnterCriticalSection(&my_winsec);
			msgRecvQueue.push_back(i);
			//LeaveCriticalSection(&my_winsec);
			//LeaveCriticalSection(&my_winsec);	// �뿪�ٽ���(����)
#else
			//my_mutex.lock();
			//std::lock_guard<std::recursive_mutex> sbguard(my_mutex);

			std::chrono::milliseconds timeout(100);  // 100ms
			if (my_mutex.try_lock_for(timeout)) {  // ���ڹ涨ʱ�����õ���

				msgRecvQueue.push_back(i);  // �������ŵ���Ϣ��������
				my_mutex.unlock();
			}
			else  // ��ʱδ�õ���
			{
				std::chrono::milliseconds sleeptime(100);
				std::this_thread::sleep_for(sleeptime);
			}
			//my_mutex.unlock();
#endif // __WIDOWSJQ_

			
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

	//mutex my_mutex;  // ������һ��������

	//recursive_mutex my_mutex;  // ʹ�õݹ�ʽ�Ķ�ռ������

	timed_mutex my_mutex;

#ifdef __WINDOWSJQ_
	CRITICAL_SECTION my_winsec;  // ����һ��window�µ��ٽ������ǳ�������C++11�е�mutex���ٽ���ʹ��ʱ������г�ʼ��
#endif


	bool outMsgLULProc(int& command) {
#ifdef __WINDOWSJQ_
		EnterCriticalSection(&my_winsec);
		if (!msgRecvQueue.empty()) {
			// ����Ϣ���в�Ϊ��
			command = msgRecvQueue.front();  // ���ض��е�һ��Ԫ�أ����ǲ����Ԫ���Ƿ����
			msgRecvQueue.pop_front();  // �Ƴ����е�һ��Ԫ�أ����ǲ�����
			LeaveCriticalSection(&my_winsec);
			return true;
	}
		LeaveCriticalSection(&my_winsec);
#else
		std::lock_guard<std::recursive_mutex> sbguard(my_mutex);
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
#endif // __WINDOWSJQ_
		return false;
	}
};

void test01() {
	A myobja;
	std::thread myOutMsgObj(&A::outMsgRecQueue, &myobja);
	std::thread myInMsgObj(&A::inMsgRecvQueue, &myobja);
	myInMsgObj.join();
	myOutMsgObj.join();
}

int main() {
	test01();
	return 0;
}