#pragma once
#include "cocos2d.h"

class CTrain : public cocos2d::Sprite
{
public:
	CTrain();
	static CTrain* Create(const std::string &fileName);
	bool Init(cocos2d::Sprite *sprite);
	void SetContactListener();
};

