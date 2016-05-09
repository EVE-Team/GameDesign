#include "Sequence.h"
#include "cocos2d.h"
#include <random>

using namespace std;
using namespace cocos2d;

MyCSequence::MyCSequence()
{
	FillBasicPoints();
}

MyCSequence::~MyCSequence()
{
}

void MyCSequence::FillBasicPoints()
{
	auto point = new MyPoint();
	point->x = 60;
	point->y = 160;
	basicPoints.push_back(point);

	auto point1 = new MyPoint();
	point1->x = 120;
	point1->y = 60;
	basicPoints.push_back(point1);

	auto point2 = new MyPoint();
	point2->x = 120;
	point2->y = 260;
	basicPoints.push_back(point2);

	auto point3 = new MyPoint();
	point3->x = 180;
	point3->y = 160;
	basicPoints.push_back(point3);

	auto point4 = new MyPoint();
	point4->x = 240;
	point4->y = 60;
	basicPoints.push_back(point4);

	auto point5 = new MyPoint();
	point5->x = 240;
	point5->y = 260;
	basicPoints.push_back(point5);

	auto point6 = new MyPoint();
	point6->x = 300;
	point6->y = 160;
	basicPoints.push_back(point6);

	auto point7 = new MyPoint();
	point7->x = 360;
	point7->y = 60;
	basicPoints.push_back(point7);

	auto point8 = new MyPoint();
	point8->x = 360;
	point8->y = 260;
	basicPoints.push_back(point8);

	auto point9 = new MyPoint();
	point9->x = 420;
	point9->y = 160;
	basicPoints.push_back(point9);
}

vector<MyPoint*> MyCSequence::Create(const int count)
{
	int prevRandom = -1;
	int currRandom = 0;
	for (int i = 0; i < count; ++i)
	{
		currRandom = rand() % 10;
		if (currRandom != prevRandom)
		{
			points.push_back(basicPoints[currRandom]);
			prevRandom = currRandom;
		}
		else
		{
			--i;
		}
	}

	return points;
}