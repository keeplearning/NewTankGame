#pragma once
#include "Definition.h"
#include "GameTank.h"
#include "GameBullet.h"
#include "GameLoad.h"

class TankMgr : public GameBase
{
public:
	TankMgr();
	~TankMgr();
	static TankMgr* GetInstance();
	virtual void Init() override;
	
	void PlayerOperate();
	void EnemyOperate();
	virtual void Update() override;

	bool IsGameOver();
	bool IsCollision(ObjectBase *pTank);

	bool IsTankCollision(ObjectBase *pTank);

	void TankMove(ObjectBase *pTank, int nDir);

	bool IsBulletCollision(ObjectBase *pBullet);

	void ReduceHp(ObjectBase *pBullet, std::vector<ObjectBase*>::iterator &it);

	std::vector<ObjectBase*>::iterator& RemoveTank(std::vector<ObjectBase*>::iterator &it);

	void RemoveAllTank();

	void AddShowScore(int type);
public:
	std::vector<ObjectBase*> m_vTankList;
	ObjectBase *m_pPlayer1;
	ObjectBase *m_pPlayer2;
	int m_nPlayer1Score;
	int m_nPlayer2Score;
	bool m_isWin;
	GameLoad m_objLoad;
};

