#pragma once

#include "cocos2d.h"
#include "..\cocos2d\cocos\physics\CCPhysicsBody.h"
#include "string"

using namespace std;
using namespace cocos2d;

class CBackGround : public Sprite
{
public:
	CBackGround();
	static CBackGround* Create(const string &fileName);
	~CBackGround();
};

