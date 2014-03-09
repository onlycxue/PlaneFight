#pragma once
#include "cocos2d.h"

class EnemyPlane : public cocos2d::CCSprite
{
public:
	//通过帧缓冲加载精灵图片
	virtual bool initWithFile(const char *frameName, int hp, int minMoveDuration, int maxMoveDuration);
	
protected:
	//敌机的血
	CC_SYNTHESIZE(int, _hp, Hp);
	//敌机持续的时间 每个敌机出现的速度不确定。
	CC_SYNTHESIZE(int, _minMoveDuration, MinMoveDuration);
	CC_SYNTHESIZE(int, _maxMoveDuration, MaxMoveDuration);
};

class WeakEnemPlane : public EnemyPlane
{
public:
	virtual bool init(void);
	CREATE_FUNC(WeakEnemPlane);
};

class StrongEnemPlane : public EnemyPlane
{
public:
	virtual bool init(void);
	CREATE_FUNC(StrongEnemPlane);
};

