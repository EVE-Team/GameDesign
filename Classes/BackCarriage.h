#pragma once
#include "cocos2d.h"
#include "string"

using namespace std;
using namespace cocos2d;

class BackCarriage : public Sprite
{
public:
	BackCarriage(const string &fileName);
	~BackCarriage();

	static BackCarriage* Create(const string &fileName);
	
	bool Init(Sprite *sprite);
	void SetContactListener();

private:
	void TouchEvent(Touch* touch);
	string m_spriteFileName;
};

