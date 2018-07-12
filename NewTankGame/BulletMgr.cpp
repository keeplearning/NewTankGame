#include "stdafx.h"
#include "BulletMgr.h"
#include "GameMap.h"
#include "TankMgr.h"
//�ӵ�������
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
	//�Ӷ�ȡ�浵������Ϸ,�Ѿ����ļ���ȡ����Ϸ���ݣ�ֻҪ��Ⱦ�˾���
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

//�����ӵ�
void BulletMgr::Fire(ObjectBase *pTank)
{
	if (pTank == nullptr || !IsFire(pTank)) return;

	int posX = pTank->GetNextPosX(2);
	int posY = pTank->GetNextPosY(2);

	char szStr[3];
	if (pTank->m_nType == PLAYER1_TYPE || pTank->m_nType == PLAYER2_TYPE || pTank->m_nType == ENEMY_NORMAL)
	{
		strcpy_s(szStr, "��");
	}
	else if (pTank->m_nType == ENEMY_FAST)
	{
		strcpy_s(szStr, "��");
	}
	else if (pTank->m_nType == ENEMY_SLOWLY)
	{
		strcpy_s(szStr, "��");
	}

	GameBullet *pBullet = new GameBullet(posX, posY, pTank->m_nDir, pTank->m_nColor, pTank->m_nType, -1, pTank->m_nAttack, szStr, pTank->m_nAscription);
	pBullet->OnRender();
	m_vBulletList.push_back(pBullet);
}

//�ӵ����ƶ�
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

//�ӵ�����ǽש�����̹��
void BulletMgr::BulletCollision()
{
	std::vector<ObjectBase*>::iterator it = m_vBulletList.begin();
	while (it != m_vBulletList.end())
	{
		//����ӵ������˳��˲���Ϊ���κ����壬���ӵ���m_isAlive����Ϊfalse
		int posX = (*it)->GetNextPosX(1);
		int posY = (*it)->GetNextPosY(1);
		//�ӵ��Ƿ�ײ��ǽ
		if (GameMap::GetInstance()->m_Map[posX][posY] == GAME_WALL) {
			(*it)->m_isAlive = false;
		}
		//�ӵ��Ƿ�ײ��ש��
		else if (GameMap::GetInstance()->m_Map[posX][posY] == GAME_BRICK) {
			OnRenderChar(posX, posY, "  ", NULL);
			GameMap::GetInstance()->m_Map[posX][posY] = GAME_SPACE;
			(*it)->m_isAlive = false;
		}
		//�ӵ��Ƿ�ײ��̹��
		else if (TankMgr::GetInstance()->IsBulletCollision((*it))) {
			(*it)->m_isAlive = false;
		}
		//�ӵ����ӵ�����ײ
		EnemyBulletCollision((*it), posX, posY);

		it++;
	}

	it = m_vBulletList.begin();
	//����ʹ��forѭ��������ɾ�������ᵼ��bug��ֻ����whileѭ��
	while (it != m_vBulletList.end())
	{
		//����ӵ�����m_isAliveΪfalse��˵���ӵ�Ӧ�ñ�����
		if (!(*it)->m_isAlive) {
			RemoveBullet(it);
		}
		else {
			it++;
		}
	}
}

//����ӵ���з��ӵ�����ײ
void BulletMgr::EnemyBulletCollision(ObjectBase *pBullet, int x, int y)
{
	std::vector<ObjectBase*>::iterator it = m_vBulletList.begin();
	while (it != m_vBulletList.end())
	{
		//ֻ������ӵ��͵����ӵ��ż��
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

//���̹���ڿ���ǰ����ǽ ���ܷ����ӵ�
bool BulletMgr::IsFire(ObjectBase *pTank)
{
	int posX = pTank->GetNextPosX(2);
	int posY = pTank->GetNextPosY(2);

	if (GameMap::GetInstance()->m_Map[posX][posY] == GAME_WALL) {
		return false;
	}

	return true;
}
//�����ӵ�
std::vector<ObjectBase*>::iterator& BulletMgr::RemoveBullet(std::vector<ObjectBase*>::iterator& it) {
	(*it)->OnClear();
	delete((*it));
	(*it) = nullptr;
	it = m_vBulletList.erase(it);
	return it;
}

//���������ӵ�
void BulletMgr::RemoveAllBullet() {
	std::vector<ObjectBase*>::iterator it = m_vBulletList.begin();
	while (it != m_vBulletList.end())
	{
		it = RemoveBullet(it);
	}
}
