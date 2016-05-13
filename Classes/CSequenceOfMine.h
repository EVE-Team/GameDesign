#pragma once

#include "cocos2d.h"
#include "Point.h"
#include <vector>

using namespace std;
using namespace cocos2d;

class CSequenceOfMine
{
public:
	CSequenceOfMine();
	~CSequenceOfMine();

	set<MyPoint*> Create(const int count);
	void FillBasicPoints();

private:
	set<MyPoint*> m_points;
	vector<MyPoint*> m_basicPoints;
};

