#pragma once

#include "cocos2d.h"
#include "Point.h"

class MyCSequence
{
public:
	MyCSequence();
	~MyCSequence();

	static std::vector<MyPoint*> Create(const int count);
	void FillBasicPoints();

private:
	std::vector<MyPoint*> points;
	std::vector<MyPoint*> basicPoints;
};

