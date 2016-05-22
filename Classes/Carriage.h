#pragma once
#include "cocos2d.h"
#include "string"

using namespace std;
using namespace cocos2d;

class CCarriage : public Sprite
{
public:
	CCarriage(const string &fileName);
	~CCarriage();

	static CCarriage* Create(const string &fileName);
	bool Init(Sprite *sprite);
	void SetContactListener();

private:
	void TouchEvent(Touch* touch);
	string m_spriteFileName;
};

