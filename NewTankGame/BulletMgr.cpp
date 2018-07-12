#include "stdafx.h"
#include "BulletMgr.h"
#include "GameMap.h"
#include "TankMgr.h"
//子弹管理类
static BulletMgr* pBulletMgr = nullptr;
BulletMgr::BulletMgr()
{
}


BulletMgr::~BulletMgr()
{
}

BulletMgr* BulletMgr::GetInstance()
{
	if (pBulletMgr == nullptr) {
		pBulletMgr = new BulletMgr();
	}
	return pBulletMgr;
}

void BulletMgr::Init()
{
	//从读取存档进入游戏,已经从文件读取了游戏数据，只要渲染了就行
	for (int i = 0; i < m_vBulletList.size(); ++i)
	{
		m_vBulletList[i]->OnRender();
	}
}

void BulletMgr::Update()
{
	BulletCollision();
	BulletMove();
}

//发射子弹
void BulletMgr::Fire(ObjectBase *pTank)
{
	if (pTank == nullptr || !IsFire(pTank)) return;

	int posX = pTank->GetNextPosX(2);
	int posY = pTank->GetNextPosY(2);

	char szStr[3];
	if (pTank->m_nType == PLAYER1_TYPE || pTank->m_nType == PLAYER2_TYPE || pTank->m_nType == ENEMY_NORMAL)
	{
		strcpy_s(szStr, "◎");
	}
	else if (pTank->m_nType == ENEMY_FAST)
	{
		strcpy_s(szStr, "○");
	}
	else if (pTank->m_nType == ENEMY_SLOWLY)
	{
		strcpy_s(szStr, "●");
	}

	GameBullet *pBullet = new GameBullet(posX, posY, pTank->m_nDir, pTank->m_nColor, pTank->m_nType, -1, pTank->m_nAttack, szStr, pTank->m_nAscription);
	pBullet->OnRender();
	m_vBulletList.push_back(pBullet);
}

//子弹的移动
void BulletMgr::BulletMove()
{
	for (int i = 0; i < m_vBulletList.size(); ++i)
	{
		if (m_vBulletList[i] != nullptr) {
			m_vBulletList[i]->OnClear();
			m_vBulletList[i]->OnMove();
			m_vBulletList[i]->OnRender();
		}
	}
}

//子弹碰到墙砖块或者坦克
void BulletMgr::BulletCollision()
{
	std::vector<ObjectBase*>::iterator it = m_vBulletList.begin();
	while (it != m_vBulletList.end())
	{
		//如果子弹碰到了除了草以为的任何物体，将子弹的m_isAlive设置为false
		int posX = (*it)->GetNextPosX(1);
		int posY = (*it)->GetNextPosY(1);
		//子弹是否撞到墙
		if (GameMap::GetInstance()->m_Map[posX][posY] == GAME_WALL) {
			(*it)->m_isAlive = false;
		}
		//子弹是否撞到砖块
		else if (GameMap::GetInstance()->m_Map[posX][posY] == GAME_BRICK) {
			OnRenderChar(posX, posY, "  ", NULL);
			GameMap::GetInstance()->m_Map[posX][posY] = GAME_SPACE;
			(*it)->m_isAlive = false;
		}
		//子弹是否撞到坦克
		else if (TankMgr::GetInstance()->IsBulletCollision((*it))) {
			(*it)->m_isAlive = false;
		}
		//子弹与子弹的碰撞
		EnemyBulletCollision((*it), posX, posY);

		it++;
	}

	it = m_vBulletList.begin();
	//不能使用for循环做数组删除处理，会导致bug，只能用while循环
	while (it != m_vBulletList.end())
	{
		//如果子弹属性m_isAlive为false，说明子弹应该被销毁
		if (!(*it)->m_isAlive) {
			RemoveBullet(it);
		}
		else {
			it++;
		}
	}
}

//玩家子弹与敌方子弹的碰撞
void BulletMgr::EnemyBulletCollision(ObjectBase *pBullet, int x, int y)
{
	std::vector<ObjectBase*>::iterator it = m_vBulletList.begin();
	while (it != m_vBulletList.end())
	{
		//只有玩家子弹和敌人子弹才检测
		if (pBullet->m_nAscription == PLAYER_TYPE && (*it)->m_nAscription == ENEMY_TYPE)
		{
			if (x == (*it)->m_nPosX && y == (*it)->m_nPosY)
			{
				pBullet->m_isAlive = false;
				(*it)->m_isAlive = false;
				break;
			}
		}
		it++;
	}
}

//如果坦克炮口正前方是墙 不能发射子弹
bool BulletMgr::IsFire(ObjectBase *pTank)
{
	int posX = pTank->GetNextPosX(2);
	int posY = pTank->GetNextPosY(2);

	if (GameMap::GetInstance()->m_Map[posX][posY] == GAME_WALL) {
		return false;
	}

	return true;
}
//销毁子弹
std::vector<ObjectBase*>::iterator& BulletMgr::RemoveBullet(std::vector<ObjectBase*>::iterator& it) {
	(*it)->OnClear();
	delete((*it));
	(*it) = nullptr;
	it = m_vBulletList.erase(it);
	return it;
}

//销毁所有子弹
void BulletMgr::RemoveAllBullet() {
	std::vector<ObjectBase*>::iterator it = m_vBulletList.begin();
	while (it != m_vBulletList.end())
	{
		it = RemoveBullet(it);
	}
}
