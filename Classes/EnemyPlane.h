#pragma once
#include "cocos2d.h"
#include "Plane.h"
#include "Bullet.h"

class EnemyPlane : public Plane
{
public:
	//ͨ��֡������ؾ���ͼƬ
	virtual bool initWithFile(const char *frameName, int hp, int minMoveDuration, int maxMoveDuration);
	virtual Bullet* createBullet();

	//��ʱ����ӵ�
	void addBullet(float dt);
	//�ӵ��Ƴ��߽�
	void moveFinished(CCNode *sender);
	cocos2d::CCArray* getBulletArray();
	
protected:
	//�л���Ѫ
	//CC_SYNTHESIZE(int, _hp, Hp);
	//�л�������ʱ�� ÿ���л����ֵ��ٶȲ�ȷ����
	
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

