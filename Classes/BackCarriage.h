#pragma once
#include "cocos2d.h"

class BackCarriage : public cocos2d::Sprite
{
public:
	BackCarriage(const std::string &fileName);
	static BackCarriage* Create(const std::string &fileName);	
	bool Init(cocos2d::Sprite *sprite);
	void SetContactListener();
private:	
	std::string m_spriteFileName;
};