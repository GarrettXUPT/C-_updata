#include<iostream>

using namespace std;

/*
	һ����ʱ����ĸ���
		i++ ������ֵ���ʽ���������ʱ����
		++i ������ֵ���ʽ
		����һЩ��ʱ��������Ϊ������д�����ģ�ͳһ����ʱ����Ϊ��ʱ���� 
		��Ϊ��ʱ�������������ϵͳ��Դ�����Բ�����Խ��Խ��
		new����ɵ����ϣ�ջ�ϻ����һЩ��ʱ��������Щ��ʱ������Ҫ����ϵͳ�Լ��ͷ�
		�����������ʱ����Ĳ����������ڴ�����д���������

	����������ʱ�������������(���ֵ�����ͽ������)
		1���Դ�ֵ��ʽ���������ݲ���
			������ֱ�Ӵ����󣬽��鴫�����õķ�ʽ�����ݲ���������ߴ���Ч��

		2������ת�����ɵ���ʱ����/��ʽ����ת���Ա�֤�������óɹ�
			�ڱ��ʱ����ò�Ҫ������ת������������ת������һ��Ҫ��const

		3���������ض����ʱ��

	�ġ��ܽ�
		����ڿεľ���д���룬��ߴ�������Ч��
			
			
*/

class CTempValue {
public:
	int val1;
	int val2;
public:
	CTempValue(int va1 = 0,int val2 = 0);
	/*
		�������캯��
	*/
	CTempValue(const CTempValue& t) : val1(t.val1), val2(t.val2) {
		cout << "�����˿������캯��" << endl;
	}

	CTempValue& operator=(const CTempValue& tmpv) {
		val1 = tmpv.val1;
		val2 = tmpv.val2;
		return*this;
	}

	virtual ~CTempValue() {
		cout << "��������������" << endl;
	}
public:
	int Add(CTempValue& ts);  // ��ͨ����
	//CTempValue Double(CTempValue& ts);
};

/*
	�������԰汾
*/
//CTempValue Double(CTempValue& ts) {
//	CTempValue tmpm;  // �ô�������һ�����캯����һ����������,ϵͳ��������ʱ����
//	tmpm.val1 = ts.val1 * 2;
//	tmpm.val2 = ts.val2 * 2;
//	return tmpm;  // ��ִ����һ���������캯��
//}

/*
	�������Ͱ汾�������Ż������ǽ�ʡ��һ���������캯����һ����������
*/
CTempValue Double(CTempValue& ts) {
	return CTempValue(ts.val1 * 2, ts.val2 * 2);  // ϵͳ�ڴ˴�Ҳ�����һ����ʱ����
}

 

CTempValue::CTempValue(int v1, int v2): val1 (v1), val2 (v2) {
	cout << "�����˹��캯��" << endl;
	cout << "val1 = " << val1 << " val2 = " << val2 << endl;
}

int CTempValue::Add(CTempValue& ts) {  // �ô�ʹ���������ã��Ϳ���������ʱ����
	int tmp = ts.val1 + ts.val2;
	ts.val1 = 1000;  // �����޸�ֵ����������û��Ӱ�죬ֻ�����ò���Ӱ��,ʹ�����ú󣬾ͻ�ı��������ֵ
	return tmp;
}
/*
	��ʱ����ĸ���
*/
void test01() {
	int i = 1;
	/*
		r1������ʱ��������i֮��û�й�ϵ,��֮����ʱ�����Ͳ��ᱻ�ͷ�
		i++��Ϊ������Ҫ���Բ�����ʱ����
	*/
	int&& r1 = i++;
	cout << "r1 = " << r1 << " i = " << i << endl;  // 1   2 
	r1 = 19;  // �˴�����r1�ĸ�ֵ�������iֵ����κ�Ӱ��
	cout << "r1 = " << r1 << " i = " << i << endl;  // 19  2
	i = 6;  // ��i���и�ֵҲ�����r1���Ӱ��
	cout << "r1 = " << r1 << " i = " << i << endl;  // 19  6
}

/*
	�Դ�ֵ��ʽ���������ݲ���
*/
void test02() {
	CTempValue tm(10, 20);
	int sum = tm.Add(tm);  // �ᵼ�¿������캯����ִ��,����ֱ��ʹ��tm,�Ὣtm����һ�ݽ�ȥ����ʹ�����ô���Ͳ�����ÿ������캯��
	cout << "sum = " << sum << endl;   // 30
	// δʹ������
	//cout << "tm.val1 = " << tm.val1 << " tm.val2 = " << tm.val2 << endl;  // 10 20 
	// ʹ������
	cout << "tm.val1 = " << tm.val1 << " tm.val2 = " << tm.val2 << endl;  // 1000 20 
}

/*
	����ת�����ɵ���ʱ����/��ʽ����ת���Ա�֤�������óɹ�
*/
void test03() {
	/*
		���ַ�ʽ�����캯���������Σ�����������������
	*/
	//CTempValue sum;
	//sum = 1000; // �ô�������һ��������CTempValue���͵���ʱ���� 
	//			// ���ｫ1000ת��ΪCTempValue���� ��ʱ��1000�ḳֵ����һ��Ĭ�ϲ���val1���ڶ����������ǲ���Ĭ�ϲ���
	//			// ��1000��ֵ��sumʱ�����µ����˿�����ֵ�����
	//cout << "val1 = " << sum.val1 << "val2 = " << sum.val2 << endl;

	/*
		����ʽ,���������ø������ֵ����һ���� 
				 ���ַ�ʽ�����캯������������ֻ������һ��
	*/
	CTempValue sum = 1000;   // �˴�ָ���Ƕ���ʱ��ʼ�������Ǹ�ֵ�����
						    // �˴�������sum����Ϊsum����Ԥ���˿ռ䣬��1000������sum���󣬲���ֱ�ӹ�����sum�����Ԥ���ռ�
	cout << "val1 = " << sum.val1 << "val2 = " << sum.val2 << endl;
}

/*
	��ʽ����ת������֤�������óɹ�
	ͳ���ַ�ch���ַ���strsorce����ֵĴ���
	C++����ֻ��Ϊconst���ò�����ʱ������������Ϊ��const���ò���������ʱ����
*/
int calc(const string& strsource, char target) {  // �ô��βα�������const��ʶ��������ϵͳ�������ͨ�����øı��ַ��������Ա���
									// strsource����βξͰ󶨵���string��ʱ�����ϣ�����������ʱ������ʱ����ͻᱻ����
	const char* p = strsource.c_str();
	int icount = 0;
	while (*p != '\0')
	{
		if (*p == target) {
			icount++;
		}
		p++;
	}
	return icount;
}

/*
	������������Զ��Ľ�char[] ����ת��Ϊstring����
*/
void test04() {
	char mystr[100] = "I Love China";
	int result = calc(mystr, 'o');
	cout << result << endl;
}

/*
	�������ض����ʱ��
	
*/
void test05() {
	CTempValue ts(10, 20);
	cout << "ts.val1 = " << ts.val1 << " ts.val2 = " << ts.val2 << endl;
	/*
		������һ����ʱ����ʹϵͳ���Զ�������һ�����캯������������
	*/
	//Double(ts);
	
	/*
		��ʹ�����ͶԷ���ֵ���н���,�������ʱ����û�б����������ص���ʱ����ֱ�ӹ�����res��Ԥ���ռ���
	*/
	/*CTempValue res = Double(ts);
	cout << "res.val1 = " << res.val1 << " res.val2 = " << res.val2 << endl;*/
	
	/*
		ʹ����ֵ���ý�����ʱ����,���ַ�ʽ�����ַ�ʽ��Ч����ͬ
		��ò�����ֵ���ã�����ʹ����һ�����ƱȽϺã���ʱ�������һ����ֵ
	*/
	CTempValue&& res = Double(ts);
	cout << "res.val1 = " << res.val1 << " res.val2 = " << res.val2 << endl; 

	/*
		Double���������
		CTempValue ts;  ������һ�����캯����һ����������
		return tmpm;  �����һ����ʱ���󣬻�ռ��һ���������캯������������
	*/
}

class mynum {
public:
	/*
		�����ж�Ӧ�Ĺ��캯��
	*/
	mynum(int x = 0, int y = 0) :num1(x), num2(y){}
public:
	int num1, num2;
};
mynum operator+(const mynum& tmpnum1, const mynum& tmpnum2) {
	return mynum(tmpnum1.num1 + tmpnum2.num1, tmpnum1.num2 + tmpnum2.num2);
}

/*
	��������������
*/
void test06() {
	mynum num1(10, 20);
	mynum num2(50, 60);
	mynum res = num1 + num2;
	cout << res.num1 << "  " << res.num2 << endl;  // 60  80
}

int main() {

	//test01();
	//test03();
	test06();
	return 0;
}