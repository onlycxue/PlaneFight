#include "HeroPlane.h"

USING_NS_CC;
bool HeroPlane::initWithFile(const char* fileName, int hp, int Sensitivity)
{
	if (!Plane::initWithFile(fileName, hp))
	{
		return false;
	}
	_sensitivity = Sensitivity;
	m_bulletArray = CCArray::create();
	m_bulletArray->retain();
	return true;
	
}
cocos2d::CCArray* HeroPlane::getBulletArray()
{
	return m_bulletArray;
}
Bullet* HeroPlane::createBullet(Bullet* bullet)
{
	if (getParent() != NULL)
	{
		m_parent = getParent();
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		bullet->setPosition(ccp(getPosition().x, getPosition().y + this->getContentSize().height / 2));
		getParent()->addChild(bullet);
		bullet->setTag(0);
		bullet->retain();
		CCMoveTo *actionMove = CCMoveTo::create(2, ccp(bullet->getPosition().x, winSize.height + bullet->getContentSize().width / 2));
		CCCallFuncN *actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(HeroPlane::moveFinished));
		bullet->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
		m_bulletArray->addObject(bullet);
		return bullet;
	}
	return NULL;
}
//子弹移除边界
void HeroPlane::moveFinished(CCNode* sender)
{
	Bullet *bullet = (Bullet*)(sender);
	m_parent->removeChild(bullet);
	m_bulletArray->removeObject(bullet);
}


//装配黄色子弹的战机
bool WeakHeroPlane::init()
{
	return HeroPlane::initWithFile("hero1.png", 5, 30);
}

bool StrongHeroPlane::init()
{ 
	return HeroPlane::initWithFile("hero1.png", 5, 30);
}
