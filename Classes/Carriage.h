#pragma once
#include "cocos2d.h"

class CCarriage : public cocos2d::Sprite
{
public:
	CCarriage(const std::string &fileName);
	static CCarriage* Create(const std::string &fileName);
	bool Init(cocos2d::Sprite *sprite);
	void SetContactListener();
	void RemoveListener();
private:
	std::string m_spriteFileName;
};

