#pragma once
#include "Definition.h"
#include "GameBase.h"
#include "GameTank.h"
#include "GameBullet.h"

class BulletMgr : public GameBase
{
public:
	BulletMgr();
	~BulletMgr();
public:
	static BulletMgr* GetInstance();
	virtual void Init() override;
	virtual void Update() override;
	//开火
	void Fire(ObjectBase *pTank);
	//子弹移动
	void BulletMove();
	//子弹碰撞
	void BulletCollision();
	//玩家子弹与敌人子弹的碰撞
	void EnemyBulletCollision(ObjectBase *pBullet, int x, int y);
	//是否可以开火
	bool IsFire(ObjectBase *pTank);
	//移除子弹
	std::vector<ObjectBase*>::iterator& RemoveBullet(std::vector<ObjectBase*>::iterator& it);
	//移除所有子弹
	void RemoveAllBullet();
public:
	//管理子弹的容器
	std::vector<ObjectBase*> m_vBulletList;
};

