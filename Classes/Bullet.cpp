#include "Bullet.h"

USING_NS_CC;

bool Bullet::initWithFile(const char* fileName, int lethality)
{
	bool bRet = false;
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("plane00.plist");
	do{
		CC_BREAK_IF(!CCSprite::initWithSpriteFrameName(fileName));
		bRet = true;
		_lethality = lethality;

	} while (0);
	return bRet;
}

bool YellowBullet::init(void)
{
	return 	Bullet::initWithFile("bullet2.png", 2);

}
bool BlueBullet::init(void)
{

	return Bullet::initWithFile("bullet.png", 1);
}

bool GrayBullet::init(void)
{
	return Bullet::initWithFile("bullet1.png", 1);

}