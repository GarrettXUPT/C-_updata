#pragma once
#include"Human.h"
#ifndef __WOWAN__H__
#define __WOWAN__H__


class Woman : public Human {
public:
	Woman();
	~Woman();

	virtual void testClass() override;
	virtual void eat();

};

#endif // !__WOWAN__H__

