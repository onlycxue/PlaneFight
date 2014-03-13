#pragma once
#include "cocos2d.h"

class Plane:public cocos2d::CCSprite
{
public:
	virtual bool initWithFile(const char *frameName, int hp);
protected:
	CC_SYNTHESIZE(int, _hp, Hp);

};

