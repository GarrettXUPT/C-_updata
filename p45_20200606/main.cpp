#include<iostream>
#include<future>
#include<mutex>

using namespace std;

/*
	һ��ԭ�Ӳ���std::atomic��̸
		һ���ԭ�Ӳ����������++,--,+=,&=,|=,^=��֧�ֵģ������Ŀ��ܲ�֧��
	����std::async����̸
		1����������
			async����һ���첽����
			������std::launch::deferred[]�ӳٵ��� �Լ�std::launch::asyncǿ�ƴ���һ���߳�
			��ʹ�õ���std::thread() ��ϵͳ��Դ���ţ���ô���ܻᵼ�´����߳�ʧ�ܣ���ôִ�д����̴߳���ʱ������������ܻ����	
			std::async()���ǲ�������������߳�(async���Դ����߳�)������һ���������һ���첽����
			std::async��std::thread�����ԵĲ�ͬ����async��ʱ�����������̣߳������ڵ���get�����߳�ִ��
			1����ʹ��std::launch::deferred����async
				�Ὣ�߳�ִ���ӳٵ�����get��ʱ������̵߳Ĵ���������Ҳ���������߳�
				���ں���������get����ô���߳̾Ͳ��ᱻ����
			2��std::launch::async��
				ǿ������첽���������߳���ִ�У�ϵͳ���봴���µ��߳�������mythread��ں�������������ִ��
			3��std::launch::async | std::launch::deferred
				�����|����ζ�ŵ���async����Ϊ������std::launch::async�������̲߳�����ִ�У�������û�д������̲߳����ӳٵ���	
			4����������Ĳ���
				�ھŽڿ��д��󣬵������κβ�����ʱ��Ĭ��ֵ����std::launch::async | std::launch::deferred����3Ч������ȫһ�µ�
				����ϵͳ�����о����첽(�������̲߳�����ִ��)����ͬ������(�ӳٵ���)����
		2��std::async��std::thread������
			��ʹ�õ���std::thread() ��ϵͳ��Դ���ţ���ô���ܻᵼ�´����߳�ʧ�ܣ���ôִ�д����̴߳���ʱ������������ܻ����	
			std::async�Ǵ����첽���������ܴ����߳�Ҳ���ܲ��ᴴ���̣߳�����async���÷����������õ��̵߳ķ���ֵ
			1������ϵͳ��Դ���ƣ���ʹ��std::thread�������߳�̫�࣬����ܼ�������ʱ�ͻᴴ��ʧ�ܣ�ϵͳ�ͻ����
			2����ʹ��std::async��һ��Ͳ��ᱨ�쳣�������������Ϊϵͳ��Դ�����޷��������̵߳�ʱ��
			   std::async���Ӷ�������ĵ��þͻ�ʹ���ӳٵ��ã������ᴴ�����̲߳�����ִ�У���ǿ��ʹ�ò����������̣߳���ôϵͳ��Դ���ŵ�ʱ�򣬿��ܱ���
			3��һ���������߳��������˳���100-200
	����std::async��ȷ��������
		std::async��ʹ���κζ����������ϵͳ���о����Ƿ񴴽����߳�
		����д����������ͬ�������첽�ͻ᲻ȷ����Ҫ�ж��̵߳�����û�б������Ϳ���ʹ��std::future�����wait_for����
		Ȼ���жϵ�ǰ�̵߳�״̬
*/

/*
	ԭ�Ӳ�������
*/
// ����ԭ�Ӳ���
std::atomic<int> g_count = 0;
void mythread() {
	for (int i = 0; i < 10000000; i++) {
		g_count++;
	}
	return;
}

void test01() {
	std::thread t1(mythread);
	std::thread t2(mythread);
	t1.join();
	t2.join();
	cout << g_count << endl;
}

/*
	std::async����̸
*/
int mythread2() {
	cout << "mythread start threadID = " << std::this_thread::get_id() << endl;
	std::chrono::milliseconds dura(2000);
	std::this_thread::sleep_for(dura);
	return 1;
}

/*
	std::async��ʹ���κζ����������ϵͳ���о����Ƿ񴴽����߳�
	����д����������ͬ�������첽�ͻ᲻ȷ����Ҫ�ж��̵߳�����û�б������Ϳ���ʹ��std::future�����wait_for����
	Ȼ���жϵ�ǰ�̵߳�״̬
*/
void test02() {
	cout << "main thread start threadID = " << std::this_thread::get_id() << endl;
	std::future<int> res = std::async(mythread2);
	//cout << res.get() << endl;
	std::future_status status = res.wait_for(std::chrono::seconds(3));  // Ҳ������wait_for�д��ݲ���3s��ʵ����ͬ��Ч��Ҳ����wait_for(10min)��ʮ����
	if (status == std::future_status::deferred) {
		cout << "�̱߳��ӳٵ���" << endl;
		cout << res.get() << endl;
	}
	else if (status == std::future_status::timeout) {
		cout << "�߳�ִ�г�ʱ" << endl;
	}
	else if (status == std::future_status::ready) {
		cout << "���������̣߳�������" << endl;
		cout << res.get() << endl;
	}
	cout << "main thread end" << endl;
}

/*
	��ʹ��std::launch::deferred����async
	�Ὣ�߳�ִ���ӳٵ�����get��ʱ������̵߳Ĵ���������Ҳ���������߳�
	���ں���������get����ô���߳̾Ͳ��ᱻ����
*/
void test03() {
	cout << "main thread start threadID = " << std::this_thread::get_id() << endl;
	std::future<int> res = std::async(std::launch::deferred,mythread2);
	cout << res.get() << endl;
	cout << "main thread end" << endl;
}

/*
	std::launch::async��
		ǿ������첽���������߳���ִ�У�ϵͳ���봴���µ��߳�������mythread��ں���
*/
void test04() {
	cout << "main thread start threadID = " << std::this_thread::get_id() << endl;
	std::future<int> res = std::async(std::launch::async, mythread2);
	cout << res.get() << endl;
	cout << "main thread end" << endl;
}



int main() {
	test02();
	return 0;
}