#pragma once

#include "cocos2d.h"
#include "Point.h"
#include <vector>

using namespace std;
using namespace cocos2d;

class MyCSequence
{
public:
	MyCSequence();
	~MyCSequence();

	vector<MyPoint*> Create(const int count);
	void FillBasicPoints();

private:
	vector<MyPoint*> points;
	vector<MyPoint*> basicPoints;
};

