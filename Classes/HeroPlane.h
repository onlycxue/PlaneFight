#include "cocos2d.h"
#include "Plane.h"
#include "Bullet.h"

class HeroPlane:public Plane
{
public:
	virtual bool initWithFile(const char*fileName, int hp, int Sensitivity);
	//virtual Bullet *createBullet() = 0;
	//获取发射的所有子弹
	cocos2d::CCArray* getBulletArray();
	Bullet* createBullet(Bullet* bullet);
	//子弹移除边界
	void moveFinished(CCNode* sender);
	
protected:
	//敏捷度
	CC_SYNTHESIZE(int, _sensitivity, Sensitivity);
private:
	cocos2d::CCArray* m_bulletArray;
	cocos2d::CCNode* m_parent;
};

//装配黄色子弹的战机
class WeakHeroPlane :public HeroPlane
{
public:
	virtual bool init();
	CREATE_FUNC(WeakHeroPlane);
};

//装配蓝色子弹的战机
class StrongHeroPlane :public HeroPlane
{
public:
	virtual bool init();
	CREATE_FUNC(StrongHeroPlane);
};



