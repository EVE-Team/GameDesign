#include "BackGround.h"
#include "cocos2d.h"
#include "string"

USING_NS_CC;

using namespace std;
using namespace cocos2d;

CBackGround* CBackGround::Create(const string &fileName)
{
	auto backGroundSprite = new (nothrow)CBackGround();
	if (backGroundSprite && backGroundSprite->initWithFile(fileName))
	{
		backGroundSprite->autorelease();
		backGroundSprite->setPosition(240, 150);
	}
	else
	{
		CC_SAFE_DELETE(backGroundSprite);
		return nullptr;
	}

	return backGroundSprite;
}

CBackGround::CBackGround()
{
}

CBackGround::~CBackGround()
{
}
