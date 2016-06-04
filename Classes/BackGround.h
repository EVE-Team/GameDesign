#pragma once
#include "cocos2d.h"

class CBackGround : public cocos2d::Sprite
{
public:
	CBackGround();
	static CBackGround* Create(const std::string &fileName);
	~CBackGround();
};

