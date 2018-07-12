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
	//����
	void Fire(ObjectBase *pTank);
	//�ӵ��ƶ�
	void BulletMove();
	//�ӵ���ײ
	void BulletCollision();
	//����ӵ�������ӵ�����ײ
	void EnemyBulletCollision(ObjectBase *pBullet, int x, int y);
	//�Ƿ���Կ���
	bool IsFire(ObjectBase *pTank);
	//�Ƴ��ӵ�
	std::vector<ObjectBase*>::iterator& RemoveBullet(std::vector<ObjectBase*>::iterator& it);
	//�Ƴ������ӵ�
	void RemoveAllBullet();
public:
	//�����ӵ�������
	std::vector<ObjectBase*> m_vBulletList;
};

