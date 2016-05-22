#include "AirPLane.h"
#include "cocos2d.h"
#include "string"

USING_NS_CC;

using namespace std;
using namespace cocos2d;

CAirPLane::CAirPLane()
{
}

CAirPLane::~CAirPLane()
{
}

CAirPLane* CAirPLane::Create(const string &fileName)
{
	auto enemySprite = new (nothrow)CAirPLane();
	if (enemySprite && enemySprite->initWithFile(fileName))
	{
		if (!enemySprite->Init(enemySprite))
		{
			CC_SAFE_DELETE(enemySprite);
			return nullptr;
		}
		else
		{
			enemySprite->autorelease();
			return enemySprite;
		}
	}
	else
	{
		CC_SAFE_DELETE(enemySprite);
		return nullptr;
	}
}

bool CAirPLane::Init(Sprite *sprite)
{
	if (sprite)
	{
		sprite->setPositionX(20);
		sprite->setPositionY(20);
		return true;
	}
	else
	{
		return false;
	}
}

void CAirPLane::TestFly(const set<MyPoint*> points)
{
	int i = 0;
	//vector<FiniteTimeAction*> moves;
	MoveTo* moves[3];
	for (set<MyPoint*>::iterator it = points.begin(); it != points.end(), i < 3; ++it, ++i)
	{
		auto elem = *it;
		auto moveTo = MoveTo::create(5.0, Vec2(elem->x, elem->y));
		moves[i] = moveTo;
		this->runAction(moveTo);
		/*while (!(moveTo->isDone()))
		{
			void();
		}*/
	}


	/*auto sequence = Sequence::create(const_cast<MoveTo*>(moves[3]));
	this->runAction(sequence);*/
	//this->setPosition(Vec2(elem->x, elem->y));
}