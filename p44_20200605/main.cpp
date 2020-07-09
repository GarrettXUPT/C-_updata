#include<iostream>
#include<thread>
#include<future>
#include<mutex>


using namespace std;

/*
	һ��std::future��������Ա����

	����std::shared_future
		
	����std::atomic
		ԭ�Ӳ�����
			���Խ�ԭ�Ӳ������Ϊ����Ҫ�õ�����������(����)�����Ķ��̲߳�����̷�ʽ
			ԭ�Ӳ����ǲ��ᱻ��ϵĳ���ִ��Ƭ��
			ԭ�Ӳ�����Ч�ʱȼ����������Ӹ�

		ԭ�Ӳ���һ�㶼��ָ���ɷָ�Ĳ�����Ҳ����˵�����ֲ���״̬Ҫô��ɣ�Ҫôû��ɣ������ܳ����м�״̬
		ʹ��std::atomic������ԭ�Ӳ�������ʵ����һ����ģ�壬��ʵ�����ģ����������װĳ�����͵�ֵ��

		�������������ڶ��̱߳�̵�ʱ�򱣻��������ݣ����������� ���������������ݣ�����
		�������߳��������̶߳�һ���������в�����һ���̶߳���һ���߳�д
		ÿһ���򵥵���䶼���ɺܶ��������ɵģ����Զ��̵߳�ʱ����������������������һЩ����Ԥ�ϵ��м�ֵ
		���������������һ�������(���д���)��ԭ�Ӳ�����Ե�һ�㶼��һ��������������һ�������

		ԭ�Ӳ���һ��������������ͳ��(�ۼƷ��ͳ�ȥ���ٸ����ݰ�)���ۼ��յ��˶��ٸ����ݰ�
		
		
*/



/*
	std::future��������Ա����
*/
int mythread(int par) {
	cout << "mythread start " << "threadId = " << std::this_thread::get_id() << endl;
	std::chrono::milliseconds dura(5000);
	std::this_thread::sleep_for(dura);
	cout << "mythread end" << "threadId = " << std::this_thread::get_id() << endl;
	return par;
} 

void test01() {
	cout << "main thread start " << "threadId = " << std::this_thread::get_id() << endl;
	std::future<int> res = std::async(mythread, 10);
	cout << "continue...." << endl;
	cout << res.get() << endl;
	cout << "main thread end " << endl;
}

void test02() {
	/*
		std::future_status ö������
	*/
	cout << "main thread start " << "threadId = " << std::this_thread::get_id() << endl;
	//std::future<int> res = std::async(mythread, 10);
	std::future<int> res = std::async(std::launch::deferred,mythread, 10);  // ���߳��ӳٵ�����getʱ����ִ��
	cout << "continue...." << endl;
	// �˴��ȴ�6����
	// wait_for����������ȴ��涨��ʱ�䣬�ȴ��ķ�ʽ��������������
	std::future_status status1 = res.wait_for(std::chrono::seconds(2));

	// ���ȴ���ʱ����ʾ�߳��ڵȴ�ʱ���ڲ�û��ִ����
	if (status1 == std::future_status::timeout) {
		cout << "�߳�ִ�г�ʱ���̻߳�û��ִ�����" << endl;
		//cout << res.get() << endl;
	}else if (status1 == std::future_status::ready) {  // ��ʾ�߳�ִ����ϣ��ɹ�����
		cout << "���߳�ִ�����" << endl;
		cout << res.get() << endl;
	}
	else if (status1 == std::future_status::deferred) {  // ��ʾ���߳̽������ӳ�
		// ������async�ĵ�һ����������Ϊstd::launch::deferred,����������
		cout << "�̱߳��ӳ�ִ��" << endl;
		cout << res.get() << endl;  // ������������������̱߳��ӳٵ�����getʱ����ִ�У���ʹ�õ������߳�ִ�У���û�д������߳�
	}
	cout << "main thread end" << endl;
}

/*
	std::shared_future
	��ģ�壬��ͨstd::future��get������ת�����ݣ��������std::shared_future��get�����Ǹ������� 
*/
void mythread2(std::future<int>& tmpp) {  // ��ʱҪע����ǵ�һ������
	cout << "mythread start " << "threadId = " << std::this_thread::get_id() << endl;
	auto res = tmpp.get();	// std::future.get������һ���ƶ����壬����ֻ����һ��future��ȡ�����Ľ��
	cout << "res = " << res << endl;
	return;
}

void mythread3(std::shared_future<int>& tmpp) {  // ��ʱҪע����ǵ�һ������
	cout << "mythread start " << "threadId = " << std::this_thread::get_id() << endl;
	auto res = tmpp.get();	// std::shared_future.get������һ���������壬����������future��ȡ���
	cout << "first get " << res << endl;
	cout << "second get " << tmpp.get() << endl;
	cout << "third get " << tmpp.get() << endl;
	return;
}


void test03() {
	cout << "main thread start " << "threadId = " << std::this_thread::get_id() << endl;
	std::packaged_task<int(int)> mypt(mythread);
	std::thread t1(std::ref(mypt), 10);
	t1.join();

	std::packaged_task<int(int)> mypt2(mythread);
	std::thread t3(std::ref(mypt2), 100);
	t3.join();
	
	/*
		std::shared_future�ĵ�һ���÷�
	*/
	std::shared_future<int> res = mypt.get_future();
	std::thread t2(mythread3, std::ref(res));  // ���߳�2�л�ȡ�߳�1�ķ���ֵ
	t2.join();

	/*
		std::shared_future�ĵڶ����÷�
	*/
	std::future<int> res2 = mypt2.get_future();
	std::shared_future<int> res2_s(res2.share());  // ��res2�Ľ���ƶ�����res2_s��
	std::thread t4(mythread3, std::ref(res2_s));
	t4.join();
	cout << "main thread end" << endl;
}

/*
	std::atomicԭ�Ӳ���
*/
// ����ԭ��ȫ�ֱ���
std::atomic<int> g_count = 0;  // ��װ��һ������Ϊint�Ķ����ֵ�����ǿ��������int����һ��ȥ�������ԭ�Ӷ���
void mythread4() {
	for (int i = 0; i < 10000000; i++) {
		g_count++;  // �˴��Ƕ����ԭ�Ӳ������ڵ�����ӹ����У����ᱻ���
	}
}

void test04() {
	std::thread t1(mythread4);
	std::thread t2(mythread4);
	t1.join();
	t2.join();
	cout << g_count << endl;
}

/*
	������ԭ�Ӳ���
	�߳��˳���ǣ���ֹ��д����
*/
std::atomic<bool> flag = false;
void mythread5() {
	std::chrono::milliseconds dura(1000);  // ����һ��1���Ӷ���
	while (flag == false) {  // flagΪfalse����˵��ϵͳû��Ҫ���߳��˳�
		cout << "threadId = " << std::this_thread::get_id() << " ������" << endl;
		std::this_thread::sleep_for(dura);
	}
	cout << "threadId = " << std::this_thread::get_id() << " ���н���" << endl;
}

void test05() {
	std::thread t1(mythread5);
	std::thread t2(mythread5);
	std::chrono::milliseconds dura(5000);  // ����һ��1���Ӷ���
	std::this_thread::sleep_for(dura);
	flag = true;  // ʹ�߳̿������е����н���,�����߳̽�falg�޸�Ϊtrue�Ժ����߳���Ϊ�������������������н���
	t1.join();
	t2.join();
	cout << "����ִ����ϣ��˳�..." << endl;
}

int main() {
	test05();
	return 0;
}