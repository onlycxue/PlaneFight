#include "Plane.h"

USING_NS_CC;

bool Plane::initWithFile(const char *frameName, int hp)
{
	bool bRet = false;
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("plane0.plist");
	do{
		CC_BREAK_IF(!CCSprite::initWithSpriteFrameName(frameName));
		bRet = true;
		_hp = hp;

	} while (0);
	return bRet;
}
