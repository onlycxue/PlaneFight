#include "cocos2d.h"
#include "Plane.h"
#include "Bullet.h"

class HeroPlane:public Plane
{
public:
	virtual bool initWithFile(const char*fileName, int hp, int Sensitivity);
	//virtual Bullet *createBullet() = 0;
	//��ȡ����������ӵ�
	cocos2d::CCArray* getBulletArray();
	Bullet* createBullet(Bullet* bullet);
	//�ӵ��Ƴ��߽�
	void moveFinished(CCNode* sender);
	
protected:
	//���ݶ�
	CC_SYNTHESIZE(int, _sensitivity, Sensitivity);
private:
	cocos2d::CCArray* m_bulletArray;
	cocos2d::CCNode* m_parent;
};

//װ���ɫ�ӵ���ս��
class WeakHeroPlane :public HeroPlane
{
public:
	virtual bool init();
	CREATE_FUNC(WeakHeroPlane);
};

//װ����ɫ�ӵ���ս��
class StrongHeroPlane :public HeroPlane
{
public:
	virtual bool init();
	CREATE_FUNC(StrongHeroPlane);
};



