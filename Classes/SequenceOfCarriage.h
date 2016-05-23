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

	vector<int> Create(const int count);
	void FillBasicPoints();

private:
	vector<int> m_points;
	vector<MyPoint*> m_basicPoints;
};

