#pragma once
#include "cocos2d.h"
#include "Point.h"
#include <vector>

using namespace std;
using namespace cocos2d;

class CSequenceOfCarriage
{
public:
	CSequenceOfCarriage();
	~CSequenceOfCarriage();

	vector<MyPoint*> Create(const int count);
	void FillBasicPoints();

private:
	vector<MyPoint*> m_points;
	vector<MyPoint*> m_basicPoints;
};

