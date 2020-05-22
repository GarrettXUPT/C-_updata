#pragma once

#include"Human.h"

#ifndef __MAN__H__
#define __MAN__H__

class Man : public Human{  // Man继承Human

public:
	Man();
	~Man();

	void setHuman(int age, string name);
	virtual void testClass() override { cout << "使用的是Man类" << endl; };
	virtual void eat();
	void test01();

private:
	
};

#endif // !__MAN__H__

