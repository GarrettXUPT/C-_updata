#include<iostream>

using namespace std;

/*
	����ģ��
	һ������
		1�����ͱ�����Զ������κ��ض����͵ķ�ʽ��д�Ĵ��룬ʹ�÷��ͱ��ʱ��������Ҫ�ṩ�������ʵ������������ϰ�߻���ֵ
		2��ģ���Ƿ��ͱ�̵Ļ�����ģ���Ǵ�������ߺ�������ͼ�����ǹ�ʽ�����Ǹ���Щ��ʽ�ṩ��Ҫ����Ϣ��ʹ������ת��Ϊ���������ߺ���(ת�䷢���ڱ���ʱ)
		3��ģ��֧�ֽ�������Ϊ�����ĳ�����Ʒ�ʽ���Ӷ�ʵ�ֶԷ��ͳ�����Ƶ�ֱ��֧�֣�C++�����ڶ�������ߺ���ʱ����������Ϊ����
		ģ��һ���Ϊ������ģ�����ģ��

	��������ģ��Ķ���
		1��ģ�嶨����template�ؼ��ֿ�ͷ���������ģ������б�����ģ������б����ж����������ô���Զ��ŷֿ���ģ������б�������Ҫ��һ��ģ�����
		   ģ������б��мȿ�����typenameҲ������class�ؼ���
		   ��ģ������б��о��ж��ĩ���������ô����Ҫʹ�ö��typaname/class
		2��ģ������б��б�ʾ�ں���������Ҫ�õ������ͻ�����ֵ��Ҳ�ͺ��������б����ƣ�������ʹ��ʱ����ʱָ��ģ��ʵ�Σ�ָ����ʱ��Ҫʹ��<>������
		   �е�ʱ�򲢲���Ҫģ��ʵ�Σ���ʱ��ϵͳ���Ը�����Ϣ�ƶϳ���
		3��funAdd��������������ΪT�����Ͳ�����T�����ͣ��������ڱ���ʱ�����ݸú���ģ��ĵ��þͿ���ȷ��

	��������ģ���ʹ��
		����ģ����úͺ����������𲻴󣬵��õ�ʱ�򣬱���������ݵ��ø�ģ��ʱ��ʵ��ȥ�ƶ�ģ������б����ƶϵ����ݾ��Ǹ��ݵ��ú���ʱ��ʵ��
		��Ȼ��ʱ����ƾ���ṩ�ĺ���ʵ�����ƶϲ�����ģ������ģ���ʱ�����Ǿ���Ҫʹ��<>�����ṩģ�����
	
	�ġ�������ģ�����
		��������ģ��typename/classʹ�õ������Ͳ���
		��ô��ģ������б��л����Զ�������Ͳ����������Ͳ�����������һ��ֵ����ô���ǲ�����ʹ��typename/class�ؼ���������
		����Ҫʹ������ѧϰ���Ĵ�ͳ��������ָ�������Ͳ����������Ͳ���S�������ͣ�int s,
		��ģ�屻ʵ����ʱ��������ģ�������ֵ �������û��ṩ�ģ�Ҳ�п����Ǳ������ƶϵģ�������Щ�����͵�ģ�������ֵ�����ǳ�������ʽ
		��Ϊʵ������Щģ�嶼��զ����������ʱ��ʵ�����ģ����Ա����ǳ�������ʽ

	ģ�嶨��ʱ���������ǲ������ɴ���ģ�ֻ���ٵ��ú���ģ��ʱ��������Ϊ����ʵ����һ���ض��İ汾֮�󣬱������Ż����ɴ���
	******���������ɴ���ʱ��Ҫ�ܹ��ҵ�����ĺ����壬���Ժ���ģ��Ķ���ͨ��������.h�ļ���******
*/

/*
	����ģ�嶨��(�൱�ڹ�ʽ����������)
*/
template<typename T>
T funcAdd(T i1, T i2) {
	return i1 + i2;
}

/*
	�����Ͳ���ģ��
*/
template<int s1, int s2>
int funMul() {
	return s1 + s2;
}

template<unsigned L1, unsigned L2>
int charscomp(const char(&arr1)[L1], const char(&arr2)[L2]) {
	return strcmp(arr1, arr2);
}

/*
	����ģ������ͷ�����ģ���������
	����ģ���ǿ���inline��
*/
template<typename T, int a, int b>
inline T funSub(T c) {
	return a + b - c;
}



/*
	����ģ���ʹ��
	�������ƶϳ����ģ����β������Ժ󣬱�������Ϊ����ʵ������һ���ض��汾�ĺ���int funAdd(int i1, int i2);
*/
void test01() {
	/*
		����ģ���ʹ��,ע��ʹ�õ�����Ҫͳһ
	*/
	int sum = funcAdd(3, 1);
	cout << "sum = " << sum << endl;   // 4
	/*
		������ģ�����,��<>��ֵ�����ݵı����ǳ�������ʽ���������ڱ���ʱ�Ϳ���ȷ������Ϊʵ��������ģ�����ڱ���ʱ��ɵ�
		��ʽָ��ģ�����
	*/
	int mul = funMul<12, 2>();
	cout << "mul = " << mul << endl;  // 24 
	/*
		����ģ������ͷ�����ģ��������ã�ʵ��ʹ�õ�ʱ����<>��ʽ���ݽ�ȥ������Ϊ׼
	*/
	int sub = funSub<int, 12, 13>(20);
	cout << "sub = " << sub << endl;  // 5

	/*
		�����ʹ��
		����ϵͳ�Զ��ƶ����鳤��
	*/
	int res = charscomp("test", "test2");
	cout << "res = " << res << endl;  // -1

}

int main() {
	test01();
	return 0;
}