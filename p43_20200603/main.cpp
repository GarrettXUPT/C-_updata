#include<iostream>
#include<mutex>
#include<thread>
#include<future>
#include<vector>

using namespace std;

/*
	һ��std::async/std::future������̨���񲢷���ֵ
		����ϣ���̷߳���һ�����
		std::async��һ������ģ�壬��һ������һ���첽���������󷵻�һ��std::future����
		����һ���첽���񣬾��Ǵ���һ���̣߳�����ʼִ�ж�Ӧ���߳���ں���������һ��std::future����
		��������оͺ����߳���ں��������صĽ��(�̷߳��صĽ��)�����ǿ���ʹ��std::future�����еĳ�Ա����get����ȡ���
		future�ĳ�Ա����getֻ�ܱ�����һ�Σ����ܱ����ö��

		std::future�ṩ��һ�ַ����첽��������Ļ��ƣ�����������û�а취�����õ����������߳�ִ����ϵ�ʱ�򣬿��Եõ����
		future.wait()ֻ�ǵȴ��̷߳��أ��������ȡ���صĽ��

		����ͨ��������std::async()����һ���������ò���������std:launch(ö��)���ͣ��ﵽһЩ�����Ŀ��
		1��std::launch::deferred��ʾ�߳���ں������ӳٵ�std::future��wait����get����ʱ�Ż�ִ�У��ڵ���get�Ժ�Ҳû�д������̣߳�
		   �������߳���ִ�е�mythread()��ں���
		   ����ʹ�øò����Ժ󲻵���getҲ������wait�Ļ������߳̾Ͳ��ᱻִ�С�ʵ�����̶߳�û�б�����
		2��std::launch::async���ٵ���async������ʱ�򣬾ͻᴴ���߳�
		   ��ʹ�øñ�ǵ�ʱ����Ҫget����ͻ��Զ�ִ�����������ǻ�ȡ�����̵߳ķ��ؽ��
		   std::futureĬ��ʹ�õľ��Ǹñ��
		
	����std::packaged_task
		��ģ�壬ģ������Ǹ��ֿɵ��ö���ͨ������ģ�彫���ֿɵ��ö����װ�����������Ժ���Ϊ�߳���ں���������
		
		packaged_task��װ�����Ŀɵ��ö��󣬻�����ֱ�ӵ��ã�����packaged_task����Ҳ��һ���ɵ��ö���,���Ǵ�ʱ����ʹ�����߳�ִ�иÿɵ��ö���
		�൱�ں�������

	����std::promise
		��ģ�壺�����ǿ�����ĳ���߳��н��и�ֵ��Ȼ���������߳��н���ֵȡ����ʹ��
		ͨ��promise����һֵ���ڽ�����ĳһ��ʱ�̣����ǰ�һ��future�󶨵����promise�����õ������ֵ

*/

/*
	�̷߳���һ�����
*/
// �߳���ں���
int mythread(int mypar) {
	cout << "thread start" << " thread ID = " << std::this_thread::get_id() << endl;  // ��ӡ���߳�
	// ģ���������,����ʱ��Ϊ5��
	std::chrono::milliseconds dura(5000);
	std::this_thread::sleep_for(dura);
	cout << "thread end" << " thread ID = " << std::this_thread::get_id() << endl;  // ��ӡ���߳�
	return mypar;
}

// ʹ����ĳ�Ա������Ϊ��ں���
class A {
public:
	int funcTest(int mypar) {
		cout << mypar << endl;
		cout << "thread start" << " thread ID = " << std::this_thread::get_id() << endl;  // ��ӡ���߳�
	// ģ���������,����ʱ��Ϊ5��
		std::chrono::milliseconds dura(5000);
		std::this_thread::sleep_for(dura);
		cout << "thread end" << " thread ID = " << std::this_thread::get_id() << endl;  // ��ӡ���߳�
		return mypar;
	}
};

/*
	�º�����ͨ��future�ĳ�Ա����get�ȴ����߳̽�������ȡ���̷߳��ؽ��
*/
void test01() {
	cout << "main thread ID = " << std::this_thread::get_id() << endl;
	std::future<int> res = std::async(mythread, 20);
	cout << "contiue������" << endl;
	int def = 0;
	// ��Ȼû��ʹ��join��������Ϊget��ʹ�õ����������ϵͳ���Զ�����������ȴ����߳̽��
	cout << res.get() << endl;

	/*
		ʹ����ĳ�Ա������Ϊ�̵߳����
	*/
	A a;
	std::future<int> res2 = std::async(&A::funcTest, &a, 10);  // ���һ������Ϊ��Ա����������
																// ��������������Ϊ�˱�֤ͬһ�߳��У�ʹ�õ���ͬһ������
	cout << res2.get() << endl;
	cout << "main thread end" << endl;
}

/*
	std::future  std::launch::deferred����ʾ��
*/
void test02() {
	cout << "main thread ID = " << std::this_thread::get_id() << endl;
	std::future<int> res = std::async(std::launch::deferred, mythread, 20);
	cout << "contiue������" << endl;
	int def = 0;
	cout << res.get() << endl;
	cout << "main thread end" << endl;
}

/*
	std::future std::launch::async������ʾ
*/
void test03() {
	cout << "main thread ID = " << std::this_thread::get_id() << endl;
	std::future<int> res = std::async(std::launch::async, mythread, 20);
	cout << "contiue������" << endl;
	int def = 0;
	//cout << res.get() << endl;
	cout << "main thread end" << endl;
}

/*
	std::packaged_task
*/
void test04() {
	cout << "main thread ID = " << std::this_thread::get_id() << endl;
	std::packaged_task<int(int)> mypt1(mythread);  // ��mythreadͨ��packaged_task������װ����
	std::thread t1(std::ref(mypt1), 12);  // �߳�ֱ�ӿ�ʼִ��  12ָ���Ǵ����ʵ��
	t1.join(); // �ȴ��߳�ִ�����
	std::future<int> res = mypt1.get_future();  // �ɽ������mypt1������а�
	cout << res.get() << endl;  // ��Ϊ��ʹ��joinʱ�ͽ��߳̽����������ˣ����Դ�ʱֱ�ӻ�ȡ���
	cout << "main thread end" << endl;
}


/*
	lambda���ʽ�͵�packaged_taskӦ��
*/
void test05() {
	cout << "main thread ID = " << std::this_thread::get_id() << endl;
	std::packaged_task<int(int)> mypt2([](int par) {
		cout << "thread start" << " thread ID = " << std::this_thread::get_id() << endl;  // ��ӡ���߳�
		// ģ���������,����ʱ��Ϊ5��
		std::chrono::milliseconds dura(5000);
		std::this_thread::sleep_for(dura);
		cout << "thread end" << " thread ID = " << std::this_thread::get_id() << endl;  // ��ӡ���߳�
		return par;
	});
	std::thread t2(std::ref(mypt2), 20);
	t2.join();
	std::future<int> res2 = mypt2.get_future();
	cout << res2.get() << endl;
	cout << "main thread end" << endl;
}

/*
	packaged_task��װ�����Ŀɵ��ö��󣬻�����ֱ�ӵ��ã�����packaged_task����Ҳ��һ���ɵ��ö���
	�����Ļ��������൱���Ǻ������ã�����������µ��߳�
*/
void test06() {
	cout << "main thread ID = " << std::this_thread::get_id() << endl;
	std::packaged_task<int(int)> mypt2([](int par) {
		cout << "thread start" << " thread ID = " << std::this_thread::get_id() << endl;  // ��ӡ���߳�
		// ģ���������,����ʱ��Ϊ5��
		std::chrono::milliseconds dura(5000);
		std::this_thread::sleep_for(dura);
		cout << "thread end" << " thread ID = " << std::this_thread::get_id() << endl;  // ��ӡ���߳�
		return par;
	});
	mypt2(105);
	std::future<int> res = mypt2.get_future();
	cout << res.get() << endl;
	cout << "main thread end" << endl;
}

/*
	����
*/
vector<std::packaged_task<int(int)>> mytask;
void test07() {
	cout << "main thread ID = " << std::this_thread::get_id() << endl;

	std::packaged_task<int(int)> mypt2([](int par) {
		cout << "thread start" << " thread ID = " << std::this_thread::get_id() << endl;  // ��ӡ���߳�
		// ģ���������,����ʱ��Ϊ5��
		std::chrono::milliseconds dura(5000);
		std::this_thread::sleep_for(dura);
		cout << "thread end" << " thread ID = " << std::this_thread::get_id() << endl;  // ��ӡ���߳�
		return par;
	});

	// ���ɵ��ö������������
	mytask.push_back(std::move(mypt2));  // ����ʹ���ƶ����壬����������mypt2���ǿ�
	// ȡ������
	std::packaged_task<int(int)> mypt3;
	auto iter = mytask.begin();
	// ����������ָ��Ķ����ƶ���mypt3��
	mypt3 = std::move(*iter);
	// ȥ�����ó�����һ��������벻������ʹ��iter
	mytask.erase(iter);
	// ֱ�ӵ��������е�Ԫ��
	mypt3(20);
	std::future<int> res = mypt3.get_future();
	cout << res.get() << endl;
	cout << "main thread end" << endl;
}

/*
	std::promise��ʹ��
*/
void mythread2(std::promise<int>& tmpp, int calc) {  // ��ʱҪע����ǵ�һ������
	//...�˴���ִ��һЩ����
	calc++;
	// ������������軨����5����
	std::chrono::milliseconds dura(5000);
	cout << "��Ҫ�ţ�������" << endl;
	std::this_thread::sleep_for(dura);
	// ���������˽��
	int res = calc;
	// ����tmpp�����оͱ�����
	tmpp.set_value(res);
}

void test08() {
	// ����һ��std::promise����mypro,�����ֵ���;���int
	std::promise<int> mypro;
	std::thread t1(mythread2, std::ref(mypro), 12); // �ڶ����������β��б�ĵ�һ���������������������β��б�ĵڶ�������
	t1.join();  // ʹ��thread����һ��Ҫ�����̵߳ȴ����߳�ִ�����
	// ��ȡ���ֵ
	std::future<int> fu1 = mypro.get_future();  //��promise�󶨵�future�ϣ�ʹ�ø�ֵ
	auto res = fu1.get();
	cout << res << endl;
}


int main() {
	test08();
	return 0;
}