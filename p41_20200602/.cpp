#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

/*
	һ�����ģʽ����
		���ģʽ�������д����д������ͨд��������ͬ���ص��ǣ�������ά���������㣬Ϊ��Ӧ������Ŀ�Ŀ��������ģ�黮�־�������ܽ�

	�����������ģʽ
		�����ģʽʹ�õ�Ƶ�ʽϸߣ�
		��������������ִ���ļ��У���ĳ������ĳЩ������࣬���ڸ���Ķ���ֻ�ܴ���һ�������ɴ������
		�����ࣺ���Ա�֤���ɵĶ���ֻ��һ��

	�����������ģʽ�µĹ��������������
		����ڴ������߳�֮ǰ�������߳��оͽ��������󴴽��ã����ó�Ա��������Ҫ���ݽ���װ�أ�����ֻ������
		�������⣺��Ҫ���Լ��������߳��д����������������̻߳����ܲ�ֹһ������ʱ����Ҫ��Ա�������л���

	�ġ�std::call_once
		����һ������ģ�壬Ҳ��C++11������ĺ������ú����ĵڶ���������һ��������
		�������ܹ���֤����aֻ������һ�Σ��߱���������������Ч���ϱȻ��������ĵ���Դ����
		call_once��Ҫ���ǽ��ʹ�ã���������std::once_flag���ʹ�ã���������һ���ṹ
		call_once����ͨ��������ж϶�Ӧ�ĺ���a�Ƿ�ִ�У�����call_once�ɹ��󣬱�Ǿͻ�����Ϊ�ѵ���״̬�������ٴ�ʹ��call_once��ʱ��
		������Ѿ�������Ϊ�ѵ��ã���ô��Ӧ�ĺ���a�Ͳ����ٱ�ִ����
*/

/*
	������Ĵ���
*/

// ���뻥��������ֹ����߳�ͬʱ���õ������󴴽�
std::mutex resource_mutex;

// ʹ��call_once����������ݱ�������
std::once_flag g_flag;

class MyCAS {
public:

	// ֻ������һ�εĺ���
	static void CreatInstance() {
		m_instance = new MyCAS();
		// �������˳���ʱ����Զ�����c1������������������������ͷŶ���
		static CGarhuishou cl;
	}

	/*
		ʹ��call_once����������ݱ�������
	*/
	static MyCAS* getObj() {
		// �����߳�ͬʱִ�е��������һ���̳߳ɹ�����call_once��ʹ��CreatInstance������������
		// ��ʱg_flag�Ϳ��Կ�����һ����
		std::call_once(g_flag, CreatInstance);
		return m_instance;
	}

	/*
		ʹ��˫����������������ݱ�������
	*/
	static MyCAS* getInstance() {
		// ����д��Ϊ˫������(���),�������������Ч�ʣ����ж��������������ʾm_instance�Ѿ���new����
		// ����д�����m_instance == nullptr,������m_instanceһ��û��new��
		if (m_instance == nullptr) {
			std::unique_lock<mutex> mymutex(resource_mutex);  // �Զ�����
			if (m_instance == nullptr) {
				m_instance = new MyCAS();
				// �������˳���ʱ����Զ�����c1������������������������ͷŶ���
				static CGarhuishou cl;
			}
		}
		return m_instance;
	}

	void func() {
		cout << "����" << endl;
	}

	/*
		ʹ���������������ͷŶ���
	*/
	class CGarhuishou {
	public:
		~CGarhuishou() {
			if (MyCAS::m_instance) {  // �����еĶ���Ϊ��
				delete MyCAS::m_instance;
				MyCAS::m_instance = nullptr;
			}
		}
	};

/*
	�����캯������˽�л�
*/
private:
	MyCAS() {};

private:
	static MyCAS* m_instance;  // ��̬��Ա����
	
};

/*
	��̬��Ա��ʼ��
*/
MyCAS* MyCAS::m_instance = nullptr;

/*
	��������ĵ���
*/
void test01() {
	// ����һ�����󣬷��ظ�������ָ��
	MyCAS* pa1 = MyCAS::getInstance();
	// ��Ϊʹ�õ��ǵ����࣬�����ٴεõ���Ҳ�ǵ�һ������pa1��pa2ָ�����ͬһ������
	MyCAS* pa2 = MyCAS::getInstance();
	pa1->func();
}

/*
	�������еĵĹ������������������
*/

void mythread() {
	cout << "�߳̿�ʼִ����" << endl;
	MyCAS* pa = MyCAS::getInstance();  // �������ʼ������Ϊ�����̹߳�ͬʹ��һ�����е����������ں�������Ϳ��ܻ�������
	cout << "�߳�ִ�����" << endl;
	return;
}

void test02() {

	std::thread myobj1(mythread);
	std::thread myobj2(mythread);

	myobj1.join();
	myobj2.join();
}

int main() {
	test02();
	return 0;
}