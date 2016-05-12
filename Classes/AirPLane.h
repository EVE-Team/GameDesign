#pragma once

#include "cocos2d.h"
#include "Point.h"
#include "string"

using namespace std;
using namespace cocos2d;

class CAirPLane : public Sprite
{
public:
	CAirPLane();
	~CAirPLane();

	static CAirPLane* Create(const string &fileName);
	bool Init(Sprite *sprite);
	void TestFly(const set<MyPoint*> points);
};

