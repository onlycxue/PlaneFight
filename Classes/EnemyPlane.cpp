#include "EnemyPlane.h"
USING_NS_CC;

bool EnemyPlane::initWithFile(const char *frameName, int hp, int minMoveDuration, int maxMoveDuration)
{
	bool bRet = false;
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("plane0.plist");
	do{
		CC_BREAK_IF(!CCSprite::initWithSpriteFrameName(frameName));
		bRet = true;
		_hp = hp;
		_minMoveDuration = minMoveDuration;
		_maxMoveDuration = maxMoveDuration;
		

	} while (0);
	
}


bool WeakEnemPlane::init()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("plane0.plist");
	EnemyPlane::initWithFile("boss3.png",2,3,6);

}
bool StrongEnemPlane::init()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("plane0.plist");
	StrongEnemPlane::initWithFile("boss.png",2,3,6);

}