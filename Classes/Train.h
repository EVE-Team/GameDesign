#pragma once
#include "cocos2d.h"
#include "string"
#include "RailTransport.h"

using namespace std;
using namespace cocos2d;

class CTrain : public Sprite
{
public:
	CTrain();
	~CTrain();

	static CTrain* Create(const string &fileName);
	bool Init(Sprite *sprite);
	void SetContactListener();

private:
	void TouchEvent(Touch* touch);
};

