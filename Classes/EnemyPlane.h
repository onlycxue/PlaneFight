#pragma once
#include "cocos2d.h"
#include "Plane.h"
#include "Bullet.h"

class EnemyPlane : public Plane
{
public:
	//通过帧缓冲加载精灵图片
	virtual bool initWithFile(const char *frameName, int hp, int minMoveDuration, int maxMoveDuration);
	virtual Bullet* createBullet();

	//定时添加子弹
	void addBullet(float dt);
	//子弹移除边界
	void moveFinished(CCNode *sender);
	cocos2d::CCArray* getBulletArray();
	
protected:
	//敌机的血
	//CC_SYNTHESIZE(int, _hp, Hp);
	//敌机持续的时间 每个敌机出现的速度不确定。
	
	CC_SYNTHESIZE(int, _minMoveDuration, MinMoveDuration);
	CC_SYNTHESIZE(int, _maxMoveDuration, MaxMoveDuration);
	CC_SYNTHESIZE(int, _speed, Speed);
	Bullet* m_bullet;
	cocos2d::CCNode* m_parent;
	cocos2d::CCArray* m_bulletArray;

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

class MidEnemPlane : public EnemyPlane
{
public:
	virtual bool init(void);
	CREATE_FUNC(MidEnemPlane);
};

