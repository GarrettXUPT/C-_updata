#include<iostream>

using namespace std;

/*
	һ����ģ���ػ�
		�ػ��뷺���෴���������ָ�������Ƿ����������������(����ģ�����)��������ĶԴ�������д�ʺ�����ר�ô���
		1����ģ���ȫ�ػ�
			1������ȫ�ػ�
				�������ɷ����汾���ܴ����ػ��汾��ֻҪ���ػ�����һ���з���
			2���ػ���Ա����������ģ��
		2����ģ���ƫ�ػ�(�ֲ��ػ�)
			ƫ�ػ��������������
				1����ģ���������
					
				2����ģ�������Χ��
		�ֲ��ػ��ػ�����Ժ󣬱����ϻ���ģ��

	��������ģ���ػ�
		1������ģ��ȫ�ػ�

		2������ģ��ƫ�ػ�

	����ģ���ػ��汾 ����λ�ý���
		ģ�嶨�塢ʵ�ֶ�����.h�ļ���
		ģ����ػ��汾��ģ��ķ����汾������ͬһ��.h�ļ���
		.h�ļ���ǰ��ŷ����汾��������ػ��汾

*/

/*
	����ȫ�ػ�
*/
template<typename T, typename U>
struct TC  // ������TC��ģ��
{
	void functest() {
		cout << "���Ƿ����汾" << endl;
	}
};
/*
	�ػ�����ʽ����T��U����ģ���������int����ʱ������ϣ����Ը������һ���ػ��汾
	ȫ�ػ�ָ�ľ��ǣ���������ģ�����(����ָ����T��U)�������þ�������ʹ���
*/
template<> // ȫ�ػ�ָ������������ģ��������þ������ʹ�������template���<>���ǿ�
struct TC<int, int> {

	TC() {
		cout << "����int int�ػ��Ĺ��캯��" << endl;
	}

	// ������ԶԸ��ػ��汾����һ���Ĵ���
	void functest() {
		cout << "�����������Ͷ���int���ػ��汾" << endl;
	}
};

template<> // ȫ�ػ�ָ������������ģ��������þ������ʹ�������template���<>���ǿ�
struct TC<double, int> {
	// ������ԶԸ��ػ��汾����һ���Ĵ���
	void functest() {
		cout << "����һ����double,һ����int���ػ��汾" << endl;
	}
};

// �ڵ��õ�ʱ�����ȿ��ǵ����ػ�������
void test01() {
	TC<int, int> tc1;
	tc1.functest();  // �����������Ͷ���int���ػ��汾

	TC<double, int>tc2;  
	tc2.functest();  // ����һ����double,һ����int���ػ��汾

	//TC<double, double>tc3;
	//tc3.functest();  // ���Ƿ����汾
}

/*
	�ػ���Ա����������ģ��
*/
template<>
void TC<double, double>::functest() {
	cout << "�����������Ͷ���double��functest�ػ��汾" << endl;
}

void test02() {
	TC<double, double> tcobj;  // ��Ȼ�˴���tc�Ƿ����汾�Ķ��󣬵��������ػ���double double��functest���������Դ˴����õľ����ػ���functest����
	tcobj.functest();
}


/*
	��ģ���ƫ�ػ�(�ֲ��ػ�)
*/
template<typename T, typename U, typename Q>
struct TC1  // ������TC��ģ��
{
	void functest() {
		cout << "���Ƿ����汾" << endl;
	}
};
/*
	�Ӳ���������,����ƫ�ػ�
	����ȷ���������Ͳ�������һ��ģ�����Ͳ���
*/
template<typename U> // ��Ϊ���������󶨵���������
struct TC1<int, U, double> {
	void functest() {
		cout << "��������ƫ�ػ��汾" << endl;
	}
};

void test03() {
	TC1<int, double, double> tcTest1;
	tcTest1.functest();  // ��������ƫ�ػ��汾

	TC1<double, int, double> tcTest2;
	tcTest2.functest();  // ���Ƿ����汾 
}

/*
	��ģ�������Χ��,����ƫ�ػ� int ��Ϊconst int��Χ��ԭ������ΪT��ΪT*��Ҳ�Ƿ�Χ����С
	�ֲ��ػ��ػ�����Ժ󣬱����ϻ���ģ��
*/
template<typename T>
struct TC2  // ������TC��ģ��
{
	void functest() {
		cout << "���Ƿ����汾" << endl;
	}
};

template<typename T>
struct TC2<const T> {  // const���ػ��汾
	void functest() {
		cout << "����const T�ػ��汾" << endl;
	}
};

template<typename T>
struct TC2<T*> {  // T*���ػ��汾�����߱���������ʹ��ָ�������
	void functest() {
		cout << "����T*�ػ��汾" << endl;
	}
};

template<typename T>
struct TC2<T&> {  // T&(��ֵ����)���ػ��汾�����߱���������ʹ��ָ�������
	void functest() {
		cout << "����T&(��ֵ����)�ػ��汾" << endl;
	}
};

void test04() {
	TC2<double> td;
	td.functest();  // ���Ƿ����汾

	TC2<double*> tdx;
	tdx.functest();  // ����T*�ػ��汾

	TC2<double&> tdy;
	tdy.functest();  // ����T&(��ֵ����)�ػ��汾
}

/*
	����ģ��ȫ�ػ�
	ȫ�ػ�����ģ��ʵ���ϵȼ���ʵ����һ������ģ�壬�����ǵȼ���һ����������
	���ȴ������غ����ִ���ȫ�ػ��汾��ϵͳ��ѡ�����غ�������������ѡ��ԭ���ǣ�����ͨ���������ȣ���û�У���ʹ���ػ��汾����û���ػ��汾����ô��ѡ�����汾
	void tfunc(int, double)(int&, double&);
	�������ַ������ػ��汾��������������ģ�������ָ������ģ�����������������Ϊ��������ģ�������ָ������ģ�����������
	��������ѡ���������͵�ģ��������ػ��汾
*/
template<typename T, typename U>   // �����汾
void tfunc(T& tmp1, U& tmp2) {
	cout << "����һ����������ģ��" << endl;
	cout << "tmp1 = " << tmp1 << endl;
	cout << "tmp2 = " << tmp2 << endl;
}
 
// T = int, U = double
template<>
void tfunc(int& tmp1, double& tmp2) {
	cout << "����һ��ȫ�ػ�����ģ��" << endl;
	cout << "tmp1 = " << tmp1 << endl;
	cout << "tmp2 = " << tmp2 << endl;
}

void test05() {
	const char* p = "Garrett";
	int i = 12;
	tfunc(p, i);

	/*
		�˴����õ�ʱ�򣬲�Ҫ���볣�����ʽ
	*/
	double ad = 1.2;
	tfunc(i, ad);	// ����һ��ȫ�ػ�����ģ��
}

/*
	����ģ�岻��ƫ�ػ��汾
*/
//template<typename T, typename U>   // �����汾
//void tfunc1(T& tmp1, U& tmp2) {
//	cout << "����һ����������ģ��" << endl;
//	cout << "tmp1 = " << tmp1 << endl;
//	cout << "tmp2 = " << tmp2 << endl;
//}
//
//template<typename U>
//void tfunc1<double, U>(double& tmp1, U& tmp2) {
//
//}

int main() {

	test05();
	return 0;
}