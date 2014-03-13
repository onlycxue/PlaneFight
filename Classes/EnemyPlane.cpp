#include "EnemyPlane.h"

USING_NS_CC;

bool EnemyPlane::initWithFile(const char *frameName, int hp, int minMoveDuration, int maxMoveDuration)
{
	if (!Plane::initWithFile(frameName, hp))
	{
		return false;
	}
	_minMoveDuration = minMoveDuration;
	_maxMoveDuration = maxMoveDuration;

	int rangeDuration = _maxMoveDuration - _minMoveDuration;
	_speed = (rand() % rangeDuration) + _minMoveDuration;

	m_bulletArray = CCArray::create();
	m_bulletArray->retain();
	this->schedule(schedule_selector(EnemyPlane::addBullet),2);

	return true;
}
Bullet* EnemyPlane::createBullet()
{
	if (getParent() != NULL&&(getPosition().y-getContentSize().height/2) >= 0)
	{
		m_parent = getParent();
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		Bullet* bullet = GrayBullet::create();
		bullet->setPosition(ccp(getPosition().x, getPosition().y - bullet->getContentSize().height / 2));
		bullet->retain();
		bullet->setTag(0);
		//m_bulletArray->addObject(m_bullet);

		CCMoveTo *actionMove = CCMoveTo::create((_minMoveDuration - 2)*(this->getPosition().y/ winSize.height), ccp(bullet->getPosition().x, -bullet->getContentSize().width));
		CCCallFuncN *actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(EnemyPlane::moveFinished));
		bullet->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
		getParent()->addChild(bullet);
		m_bulletArray->addObject(bullet);
		return bullet;
	}
	return NULL;
}

void EnemyPlane::moveFinished(CCNode *sender)
{

	Bullet *bullet = (Bullet*)(sender);
	m_parent->removeChild(bullet,true);
	m_bulletArray->removeObject(bullet);
}
cocos2d::CCArray* EnemyPlane::getBulletArray()
{
	return m_bulletArray;
}


//定时添加子弹
void EnemyPlane::addBullet(float dt)
{
	createBullet();
}


bool WeakEnemPlane::init()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("plane00.plist");
	EnemyPlane::initWithFile("boss3.png",1,3,6);
	return true;
}
bool StrongEnemPlane::init()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("plane00.plist");
	StrongEnemPlane::initWithFile("boss.png",4,6,12);
	return true;
}

bool MidEnemPlane::init(void)
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("plane00.plist");
	MidEnemPlane::initWithFile("boss2.png", 2, 6, 12);
	return true;
}