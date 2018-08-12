#pragma once
#include "stdafx.h"
#include "singletonBase.h"
#include <time.h>

#define RND randomFunction::getSingleton()

class randomFunction : public singletonBase<randomFunction>
{
public:
	randomFunction()
	{
		srand(GetTickCount());
	}
	~randomFunction() {}

	inline int getInt(int num) { return rand() % num; }
	inline int getFromInto(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}



};
