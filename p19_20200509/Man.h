#pragma once

#include"Human.h"

#ifndef __MAN__H__
#define __MAN__H__

class Man : public Human{  // Man�̳�Human

public:
	Man();
	~Man();

	void setHuman(int age, string name);
	virtual void testClass() override { cout << "ʹ�õ���Man��" << endl; };
	virtual void eat();
	void test01();

private:
	
};

#endif // !__MAN__H__

