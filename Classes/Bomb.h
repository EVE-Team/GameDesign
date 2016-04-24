#pragma once

#include "cocos2d.h"
#include "string"

using namespace std;
using namespace cocos2d;

class CBomb : public Sprite
{
public:
	CBomb();
	~CBomb();
	static CBomb* Create(const string &fileName);
	bool Init(Sprite *sprite);

	void SetContactListener();
};

