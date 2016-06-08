#pragma once
#include "cocos2d.h"

class CPauseButton : public cocos2d::Sprite
{
public:
	CPauseButton(const std::string &fileName);
	static CPauseButton* Create(const std::string &fileName);
	bool Init(cocos2d::Sprite *sprite);
	void SetContactListener();
	void RemoveListener();
private:	
	std::string m_spriteFileName;
};