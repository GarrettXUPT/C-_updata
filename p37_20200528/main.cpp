#include<iostream>
#include<string>

using namespace std;

/*
	һ������unique_ptrָ��

	����ָ��ɾ����
		1��ָ��ɾ����
			һ����ȱʡʱ����ָ��Ĭ��ɾ����delete���ͷŶ���
			��ʽ��
				unique_ptr<ָ��Ķ������ͣ�ɾ����>����ָ���������
				��Ҫ������ģ������д��ݽ�ȥ��������Ȼ���ڲ������ٸ������ɾ����������
		2��ָ��ɾ��������˵��
			������������ָ��(shared_ptr)ָ����ɾ������ͬ��ֻҪ������ָ�Ķ�����ͬ����ô����������ָ��Ҳ����ͬһ������
			����unique_ptr��ͬ������ָ��unique_ptr�е�ɾ����һ����Ӱ��unique_ptr�����ͣ����Դ������������shared_ptr�������
			unique_ptr������ɾ������ͬ����ô�͵�������unique_ptr���Ͳ�ͬ���������Ͳ�ͬ��unique_ptr��û�а취�ŵ�ͬһ�������е�
	
	�����ߴ�����
		unique�ߴ�����ָ��һ�����������Լ����ɾ��������unique_ptr�ĳߴ��������Ҳ���ܲ�����
		1����ʹ��lambda���ʽ��ɾ��������ôunique_ptr�ĳߴ��û�б仯
		2����ʹ�ú��������ɾ��������ô�ߴ�ͻ����������ֽ��Ƕ�Ч����Ӱ��ģ������Զ���ɾ����Ҫ����ʹ��
		   shared_ptr�������ƶ�ʲôɾ���������Ĵ�С������䣬������ָͨ�������

	�ġ�����ָ���ܽ�
		1������ָ������˼�룺
			��ҪĿ����Ϊ�˰��������ͷ��ڴ棬�Է�ֹ�����ͷ��ڴ�����µ��ڴ�й©
			autoptr�ȼ���unique_ptrָ��
		2��auto_ptrΪʲô������
			C++98������ָ�룬������unique_ptrһ���ֵ����ԣ�auto_ptr�����������б��棬Ҳ���ܴӺ�������auto_ptr
			��Ҫ��ԭ���ǣ���ƵĲ��ã����ױ����ã�����������
		3������ָ���ѡ��
			1��������Ҫʹ�ö��ָ��ͬһ�������ָ�룬��ô��Ӧ��ѡ��shared_ptr
			2����������Ҫ���ָ��ͬһ�������ָ�룬��ô��Ӧ��ѡ��unique_ptr
			3���Ƚ��ٵĵ������ʹ�õ�shared_ptr����unique_ptr��ʹ������ָ�����ѡ
		
*/

/*
	����unique_ptrָ��,�Ӻ�������һ���ֲ�������ָ�����
	��ʱϵͳ�����������һ����ʱ��unique_ptr���󣬵���unique_ptr���ƶ����캯��
*/
unique_ptr<string> myfunc() {
	return make_unique<string>("I Love China");
}

void test01() {
	auto p1 = myfunc();  // �ô�ʹ��p1��������ʱ�������ǲ����գ���ô��ʱ������ڴ˴��ͷţ�ͬʱ���ͷŵ�ָ��Ķ���
	cout << *p1 << endl;
}

/*
	ָ��ɾ����
*/
// �������͵�ɾ����
void mydelete(string* pdel) {
	delete pdel;
	pdel = nullptr;
	// ������Դ�ӡ����־
}

void test02() {
	// ����һ������ָ�����ͣ�����Ϊfp
	typedef void (*fp)(string*);
	
	// ʹ��using���庯��ָ�����ͣ�������Ϊfp2
	using fp2 = void(*)(string*); 
	
	// ʹ�ú������͵�ɾ����
	unique_ptr<string, fp> ps1(new string("I Love China"), mydelete);

	typedef decltype(mydelete)* fp3;  // ���ﶨ����һ��ɾ������������fp3
	unique_ptr<string, fp3> ps2(new string("Garrett"), mydelete);
	cout << *ps2 << endl;  // Garrett

	unique_ptr<string, decltype(mydelete)*> fp4(new string("Walker"), mydelete);
	cout << *fp4 << endl;  // Walker

	// ʹ��lambda���ʽдɾ������lambda���ʽ�������Ϊ����operator�����͵Ķ��󣬽�lambda���ʽ���Ϊһ��class
	auto mydela = [](string* pdel) {
		delete pdel;
		pdel = nullptr;
		// ���Դ�ӡ��־
	};
	
	// ��ʱʹ��decltype�ƶϳ�������һ��������
	unique_ptr<string, decltype(mydela)> ps5(new string("Garrett_Walker"), mydela);
	cout << *ps5 << endl;  // Garrett_Walker



}

int main() {
	test02();
	return 0;
}