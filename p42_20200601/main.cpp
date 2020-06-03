#include<iostream>
#include<thread>
#include<vector>
#include<list>
#include<mutex>


using namespace std;

/*
	һ��ʹ��unique_lockȡ��lock_guard
		unique_lock��һ����ģ�壬������һ��ʹ��lock_guard���㹻�ˣ�lock_guardȡ����mutex��lock()��unlock()
		unique_guard��lock_guard���һЩ�����Ǵ�����Ч�ʱȽϲ�ڴ�ռ�ö�һ��
	
	����unique_lock�ĵڶ�������
		lock_guard���ڶ������� lock_guard<mutex> sbguard(my_mutex, adop_lock); �˴���adop_lock�𵽵��Ǳ������
		1��std::adop_lock
			Ҳ�ǽ��б�ǣ���ʾ�������Ѿ���lock(ʹ�øò���ʱ���������Ѿ���lock�ˣ�����ͻᱨ�쳣)����ǵ�Ч�����Ǽ�����÷��߳��Ѿ����˻��������Ȩ��
			Ҳ����˵�Ѿ�lock�ɹ��ˣ�֪ͨlock_guard����Ҫ�ڹ��캯����lock����������ˡ�unique_lockʹ��ʱ��������ͬ��
			��lock������ʹ�øñ��
		2��std::try_to_lock
			��ʾ����ʹ��mutex��lock��������mutex����û�������ɹ�����ôҲ���������أ�����������������
			ʹ�øñ�ǵ�ǰ���ǲ�����ȥlock
		3��std::defer_lock
			ʹ�øñ�ǵ�ǰ�����Լ�������lock������ͻᱨ�쳣
			���壺����Ҫ��mutex��������ʼ����һ��û����mutex
	
	����unique_lock�ĳ�Ա������������defer_lock�����
		1��lock����
		2��unlock������������ǹ�������ʱ�򣬾Ϳ�����ʱunlock���ٴ���ǹ�����롣��������Ժ��ٴε���lock����
		   ʹ��lock��ס�Ĵ����Խ�٣�ִ�е�Ч��Խ�ߣ������ĳ�������Ч�ʾ�Խ�ߣ�Ҳ���˽���ͷ��ס�Ĵ���Ķ��ٳ�֮Ϊ�������ȣ�ʹ�ô�ϸ������
		   ����ϸ����ס�Ĵ�����٣�����Ч�ʾ͸ߣ���֮����Ч�ʾ͵ͣ�Ҫ����ѡ����ʴ�ϸ�Ĵ�����й������ݱ���
		3��try_lock���Ը������������������ò��������򷵻�false�����õ���������true��Ҳ�ǲ�������
		4��release �������������mutex����ָ�룬���ͷ�����Ȩ��Ҳ����unique_lock��mutex�����й�ϵ
		Ҫ���֣�unlock��release������
			unlockֻ�ǽ����������Ƿ���������unique_lock֮��Ĺ�ϵ
			��ԭ��mutex�����ڼ���״̬�������νӹܹ��������н���
			std::unique_lock<mutex> sbguard(my_metux);
			std::mutex* ptx = sbguard.release();
			ptx->unlock()
	
	�ġ�unique_lock����Ȩ�Ĵ���
		����Ȩ�ĸ��std::unique<mutex> sbguard(my_mutex); ����Ȩ���sbguard������ӵ��my_mutex��
		sbguard���Խ�my_mutex������Ȩת�Ƹ�������unique_lock��������unique_lock���������Ȩ����ת�Ƶ��ǲ��ܸ���
		��������Ȩ�ǷǷ��ģ�std::unique<mutex> sbguard2(sbguard1);  
		�ƶ�����Ȩ�ǺϷ��ģ�std::unique<mutex> sbguard2(std::move(sbguard1));

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
			// �˴�ʹ��unique_lockȡ����lock_guard
			{	
				//lock_guard<mutex> sbguard(my_mutex);
				
				//unique_lock<mutex> sblock(my_mutex);
				
				//ʹ��std::try_to_lock���г�����������û������Ҳ���������أ������γ�����


				//unique_lock<mutex> sblock(my_mutex, std::try_to_lock);
				//if (sblock.owns_lock()) {  // �õ���
				//	cout << "ִ���õ����Ĳ���" << endl;
				//	msgRecvQueue.push_back(i);  // �������ŵ���Ϣ��������
				//}
				//else
				//{
				//	cout << "δ�õ��������з���" << endl;
				//}

				/*
					ʹ��defer_lock
					�˴���û�м�����mutex
				*/
				unique_lock<std::mutex> sbguard(my_mutex, std::defer_lock);
				// �˴����õ���unique_lock���м��������ǲ���Ҫ���Ľ�������Ϊunique_lock���Զ�������
				sbguard.lock();

				// ��ʱ�����ſ�������ǹ�������
				sbguard.unlock();
				//..........�˴�����ǹ�������,������Ժ������ϣ��Ա�֤�������ݰ�ȫ
				//sbguard.lock();

				/*
					ʹ��unique_lock��try_lock����
				*/
				if (sbguard.try_lock()) {
					msgRecvQueue.push_back(i);  // �������ŵ���Ϣ��������
				}
				else
				{
					cout << "δ�õ���" << endl;
				}

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
		// �˴�ʹ��unique_lockȡ����lock_guard
		//unique_lock<mutex> sblock(my_mutex);
		//lock_guard<mutex> sbguard(my_mutex);  // ���������Լ��ı�
		// ʹ��std::try_to_lock���г�����������û������Ҳ���������أ������γ�����
		//unique_lock<mutex> sblock(my_mutex, std::try_to_lock);

		unique_lock<mutex> sblock(my_mutex, std::defer_lock);
		sblock.lock();

		/*
			����
		*/
		//my_mutex.lock();

		/*
			ʹ�øöγ���ʹ���߳̽���˯��2s 
		*/
		/*std::chrono::milliseconds dura(2000);
		std::this_thread::sleep_for(dura);*/

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
	�������ݵı�����������
*/
void test01() {
	A myobja;

	thread myOutMsgObj(&A::outMsgRecQueue, &myobja); // �ڶ������������ã��������ܱ�֤���߳���ʹ�õ���myobja�������

	thread myInMsgObj(&A::inMsgRecvQueue, &myobja);

	myOutMsgObj.join();

	myInMsgObj.join();
}



int main() {
	test01();
	return 0;
}