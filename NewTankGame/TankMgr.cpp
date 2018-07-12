#include "stdafx.h"
#include "TankMgr.h"
#include "GameMap.h"
#include "BulletMgr.h"
#include "GameMenu.h"
#include "GameOver.h"
#include "GameLoad.h"

//������Ҫ�������е�ͼ������̹�˵Ĺ���
static TankMgr *pTankMgr = nullptr;

TankMgr::TankMgr():
	m_pPlayer1(nullptr),
	m_pPlayer2(nullptr)
{
}


TankMgr::~TankMgr()
{
}

//���õ�������ַȫ��Ψһ
TankMgr* TankMgr::GetInstance() {
	if (pTankMgr == nullptr) {
		pTankMgr = new TankMgr();
	}
	return pTankMgr;
}

void TankMgr::Init()
{
	if (!m_isInit) return;
	if (g_GameStatus == GAME_READFILE)
	{
		//�Ӷ�ȡ�浵������Ϸ,�Ѿ����ļ���ȡ����Ϸ���ݣ�ֻҪ��Ⱦ�˾���
		for (int i = 0; i < m_vTankList.size(); ++i)
		{
			m_vTankList[i]->OnRender();
		}
		//����Ϸ״̬�޸�ΪPlay
		g_GameStatus = GAME_PLAY;
	}
	else {
		//���ݹؿ�������̹������
		int tankNum = 0;
		switch (GameMap::GetInstance()->nMapId)
		{
		case 1:
			tankNum = 5;
			break;
		case 2:
			tankNum = 7;
			break;
		case 3:
			tankNum = 10;
			break;
		default:
			break;
		}

		//��ʼ���ҷ�̹�˺͵з�̹��
		ObjectInfo data;
		for (int i = 0; i < tankNum; ++i)
		{
			if (i == 0)
			{
				data.nPosX = 32;
				data.nPosY = 20;
				data.nDir = DIR_UP;
				data.nColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
				data.nType = PLAYER1_TYPE;
				data.nHp = 3;
				data.nAttack = 1;
				strcpy_s(data.szStr, "��");
				data.nAscription = PLAYER_TYPE;
			}
			else if (i == 1)
			{
				data.nPosX = 32;
				data.nPosY = 30;
				data.nDir = DIR_UP;
				data.nColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
				data.nType = PLAYER2_TYPE;
				data.nHp = 3;
				data.nAttack = 1;
				strcpy_s(data.szStr, "��");
				data.nAscription = PLAYER_TYPE;
			}
			else
			{
				data.nPosX = rand() % 10 + 2;
				data.nPosY = rand() % 40 + 2;
				data.nDir = rand() % DIR_RIGHT;
				data.nType = rand() % (ENEMY_NORMAL + 1);
				data.nAscription = ENEMY_TYPE;
				if (data.nType == ENEMY_FAST)
				{
					data.nColor = FOREGROUND_RED;
					data.nHp = 1;
					data.nAttack = 1;
					strcpy_s(data.szStr, "��");
				}
				else if (data.nType == ENEMY_SLOWLY)
				{
					data.nColor = FOREGROUND_GREEN;
					data.nHp = 3;
					data.nAttack = 3;
					strcpy_s(data.szStr, "��");
				}
				else if (data.nType == ENEMY_NORMAL)
				{
					data.nColor = FOREGROUND_BLUE;
					data.nHp = 2;
					data.nAttack = 1;
					strcpy_s(data.szStr, "��");
				}

			}
			ObjectBase *tank = new GameTank(data.nPosX, data.nPosY, data.nDir, data.nColor, data.nType, data.nHp, data.nAttack, data.szStr, data.nAscription);
			tank->OnRender();
			m_vTankList.push_back(tank);
		}
	}
	

	m_isInit = false;
	
	//������ҵĵ�ַ
	if (m_vTankList[0]->m_nType == PLAYER1_TYPE)
	{
		m_pPlayer1 = m_vTankList[0];
	}
	if (m_vTankList[1]->m_nType == PLAYER2_TYPE)
	{
		m_pPlayer2 = m_vTankList[1];
	}
	

	//����˵��
	OnRenderChar(35, 1, "SP1�������: W���� S���� A���� D��  �����ӵ���   J��\t\t\tSP1�÷֣�", 7);
	OnRenderChar(35, 43, "0", 7);		// ��ʼ������
	OnRenderChar(36, 1, "SP2�������:����������������������  �����ӵ����س���\t\t\tSP2�÷֣�", 7);
	OnRenderChar(36, 43, "0", 7);		// ��ʼ������
	OnRenderChar(37, 1, "ESC�����ز˵�", 7);
	OnRenderChar(37, 20, "G��������Ϸ", 7);

	//��ʼ����ҷ���
	m_nPlayer1Score = 0;
	m_nPlayer2Score = 0;
}


void TankMgr::PlayerOperate()
{
	if (KEYDOWN('W')) {
		TankMove(m_pPlayer1, DIR_UP);
	}
	if (KEYDOWN('S')) {
		TankMove(m_pPlayer1, DIR_DOWN);
	}
	if (KEYDOWN('A')) {
		TankMove(m_pPlayer1, DIR_LEFT);
	}
	if (KEYDOWN('D')) {
		TankMove(m_pPlayer1, DIR_RIGHT);
	}
	if (KEYDOWN('J')) {
		BulletMgr::GetInstance()->Fire(m_pPlayer1);
	}
	if (KEYDOWN('G'))
	{
		//������Ϸ
		m_objLoad.GameSave();
	}
	if (KEYDOWN(VK_UP)) {
		TankMove(m_pPlayer2, DIR_UP);
	}
	if (KEYDOWN(VK_DOWN)) {
		TankMove(m_pPlayer2, DIR_DOWN);
	}
	if (KEYDOWN(VK_LEFT)) {
		TankMove(m_pPlayer2, DIR_LEFT);
	}
	if (KEYDOWN(VK_RIGHT)) {
		TankMove(m_pPlayer2, DIR_RIGHT);
	}
	if (KEYDOWN(VK_RETURN)) {
		BulletMgr::GetInstance()->Fire(m_pPlayer2);
	}
	if (KEYDOWN(VK_ESCAPE)) {
		//���ز˵�����
		BulletMgr::GetInstance()->RemoveAllBullet();
		RemoveAllTank();
		GameMenu::GetInstance()->m_isInit = true;
		g_GameStatus = GAME_MENU;
	}
}

//�з�̹�˵��ƶ�
void TankMgr::EnemyOperate()
{
	int nNum = rand() % 10;
	std::vector<ObjectBase*>::iterator it = m_vTankList.begin();
	for (;it != m_vTankList.end(); ++it)
	{
		//��Ҳ����Լ����
		if((*it)->m_nType == PLAYER1_TYPE || (*it)->m_nType == PLAYER2_TYPE) continue;
		//̹������ı��ƶ�����
		if (nNum >= 0 && nNum <= 2) {
			TankMove(*it, rand()%(DIR_RIGHT + 1));
		}
		else {
			TankMove(*it, (*it)->m_nDir);
		}
		
		//�з�̹����������ӵ�
		if (nNum == 0) {
			BulletMgr::GetInstance()->Fire(*it);
		}
	}
}

void TankMgr::Update()
{

	//��Ϸ�Ƿ����
	if (IsGameOver()) {
		//ʤ���� ������һ��
		if (m_isWin)
		{
			GameMap::GetInstance()->Update();
		}
		//ʧ���� �����������
		else
		{
			BulletMgr::GetInstance()->RemoveAllBullet();
			RemoveAllTank();
			GameOver::GetInstance()->m_isInit = true;
			g_GameStatus = GAME_OVER;
		}
	}

	PlayerOperate();
	EnemyOperate();
}

//��Ϸ�Ƿ������
bool TankMgr::IsGameOver() {
	//���ʤ������
	if (GameMap::GetInstance()->nMapId == 1) {
		if ((m_nPlayer1Score + m_nPlayer2Score) == 10) {
			m_isWin = true;
			return true;
		}
	}
	else if (GameMap::GetInstance()->nMapId == 2) {
		if ((m_nPlayer1Score + m_nPlayer2Score) == 10){
			m_isWin = true;
			return true;
		}
	}
	else if (GameMap::GetInstance()->nMapId == 3) {
		if ((m_nPlayer1Score + m_nPlayer2Score) == 10) {
			m_isWin = true;
			return true;
		}
	}

	//���ʧ�ܽ���
	if (m_pPlayer1 == nullptr && m_pPlayer2 == nullptr) {
		m_isWin = false;
		return true;
	}

	return false;
}

//�Ƿ��������ϰ���
bool TankMgr::IsCollision(ObjectBase *pTank)
{
	COORD posArr[3] = { 0 };

	if (pTank->m_nDir == DIR_UP) 
	{
		posArr[0].X = pTank->m_nPosX - 2;
		posArr[0].Y = pTank->m_nPosY;
		posArr[1].X = pTank->m_nPosX - 2;
		posArr[1].Y = pTank->m_nPosY - 1;
		posArr[2].X = pTank->m_nPosX - 2;
		posArr[2].Y = pTank->m_nPosY + 1;
	}
	else if (pTank->m_nDir == DIR_DOWN) 
	{
		posArr[0].X = pTank->m_nPosX + 2;
		posArr[0].Y = pTank->m_nPosY;
		posArr[1].X = pTank->m_nPosX + 2;
		posArr[1].Y = pTank->m_nPosY - 1;
		posArr[2].X = pTank->m_nPosX + 2;
		posArr[2].Y = pTank->m_nPosY + 1;
	}
	else if (pTank->m_nDir == DIR_LEFT) 
	{
		posArr[0].X = pTank->m_nPosX;
		posArr[0].Y = pTank->m_nPosY - 2;
		posArr[1].X = pTank->m_nPosX + 1;
		posArr[1].Y = pTank->m_nPosY - 2;
		posArr[2].X = pTank->m_nPosX - 1;
		posArr[2].Y = pTank->m_nPosY - 2;
	}
	else if (pTank->m_nDir == DIR_RIGHT) 
	{
		posArr[0].X = pTank->m_nPosX;
		posArr[0].Y = pTank->m_nPosY + 2;
		posArr[1].X = pTank->m_nPosX + 1;
		posArr[1].Y = pTank->m_nPosY + 2;
		posArr[2].X = pTank->m_nPosX - 1;
		posArr[2].Y = pTank->m_nPosY + 2;
	}

	for (int i = 0; i < 3; ++i)
	{
		int x = posArr[i].X;
		int y = posArr[i].Y;
		if (GameMap::GetInstance()->m_Map[x][y] == GAME_WALL ||
			GameMap::GetInstance()->m_Map[x][y] == GAME_BRICK) 
		{
			return true;
		}
	}

	if (IsTankCollision(pTank)) return true;
	
	return false;
}

//���̹����̹�˵���ײ
bool TankMgr::IsTankCollision(ObjectBase *pTank)
{
	int posX = pTank->m_nPosX;
	int posY = pTank->m_nPosY;
	for (int i = 0; i < m_vTankList.size(); ++i)
	{
		if (m_vTankList[i] != nullptr && pTank != m_vTankList[i]) 
		{
			if (pTank->m_nDir == DIR_UP)
			{
				if (posX - 2 == m_vTankList[i]->m_nPosX + 1 && posY + 1 == m_vTankList[i]->m_nPosY - 1 ||
					posX - 2 == m_vTankList[i]->m_nPosX + 1 && posY == m_vTankList[i]->m_nPosY - 1 ||
					posX - 2 == m_vTankList[i]->m_nPosX + 1 && posY == m_vTankList[i]->m_nPosY ||
					posX - 2 == m_vTankList[i]->m_nPosX + 1 && posY == m_vTankList[i]->m_nPosY + 1 ||
					posX - 2 == m_vTankList[i]->m_nPosX + 1 && posY - 1 == m_vTankList[i]->m_nPosY + 1)
				{
					return true;
				}
			}
			else if (pTank->m_nDir == DIR_DOWN)
			{
				if (posX + 2 == m_vTankList[i]->m_nPosX - 1 && posY + 1 == m_vTankList[i]->m_nPosY - 1 ||
					posX + 2 == m_vTankList[i]->m_nPosX - 1 && posY == m_vTankList[i]->m_nPosY - 1 ||
					posX + 2 == m_vTankList[i]->m_nPosX - 1 && posY == m_vTankList[i]->m_nPosY ||
					posX + 2 == m_vTankList[i]->m_nPosX - 1 && posY == m_vTankList[i]->m_nPosY + 1 ||
					posX + 2 == m_vTankList[i]->m_nPosX - 1 && posY - 1 == m_vTankList[i]->m_nPosY + 1)
				{
					return true;
				}
			}
			else if (pTank->m_nDir == DIR_LEFT)
			{
				if (posX + 1 == m_vTankList[i]->m_nPosX - 1 && posY - 2 == m_vTankList[i]->m_nPosY + 1 ||
					posX == m_vTankList[i]->m_nPosX - 1 && posY - 2 == m_vTankList[i]->m_nPosY + 1 ||
					posX == m_vTankList[i]->m_nPosX && posY - 2 == m_vTankList[i]->m_nPosY + 1 ||
					posX == m_vTankList[i]->m_nPosX + 1 && posY - 2 == m_vTankList[i]->m_nPosY + 1 ||
					posX - 1 == m_vTankList[i]->m_nPosX + 1 && posY - 2 == m_vTankList[i]->m_nPosY + 1)
				{
					return true;
				}
			}
			else if (pTank->m_nDir == DIR_RIGHT)
			{
				if (posX + 1 == m_vTankList[i]->m_nPosX - 1 && posY + 2 == m_vTankList[i]->m_nPosY - 1 ||
					posX == m_vTankList[i]->m_nPosX - 1 && posY + 2 == m_vTankList[i]->m_nPosY - 1 ||
					posX == m_vTankList[i]->m_nPosX && posY + 2 == m_vTankList[i]->m_nPosY - 1 ||
					posX == m_vTankList[i]->m_nPosX + 1 && posY + 2 == m_vTankList[i]->m_nPosY - 1 ||
					posX - 1 == m_vTankList[i]->m_nPosX + 1 && posY + 2 == m_vTankList[i]->m_nPosY - 1)
				{
					return true;
				}
 			}
		}
	}
	return false;
}

void TankMgr::TankMove(ObjectBase *pTank, int nDir)
{
	//���������� ���ܼ�������
	if (pTank == m_pPlayer1 && m_pPlayer1 == nullptr ||
		pTank == m_pPlayer2 && m_pPlayer2 == nullptr)
		return;
	//����̹���ٶ�
	if (!pTank->IsMove()) return;

	pTank->OnClear();
	//���̹�˵ķ��򲻵���Ҫ���ߵķ�����ת��
	if (pTank->m_nDir != nDir) 
	{
		pTank->m_nDir = nDir;
	}
	else 
	{
		do 
		{
			//���ǰ�����ϰ�������κ����ݲ���
			if(IsCollision(pTank))
				break;
			pTank->OnMove();

		} while (false);
		
	}
	pTank->OnRender();
}

//�ӵ���̹�˵���ײ
bool TankMgr::IsBulletCollision(ObjectBase *pBullet)
{
	std::vector<ObjectBase*>::iterator it = m_vTankList.begin();
	for (; it != m_vTankList.end(); ++it)
	{
		//����Ǽ����Լ����ߵз��Լ����ӵ��Ͳ����
		if (pBullet->m_nAscription == PLAYER_TYPE && (*it)->m_nAscription == PLAYER_TYPE ||
			pBullet->m_nAscription == ENEMY_TYPE && (*it)->m_nAscription == ENEMY_TYPE) {
			continue;
		}

		//����ӵ�������̹�� ����̹��
		if (pBullet->m_nPosX == (*it)->m_nPosX + 1 && pBullet->m_nPosY == (*it)->m_nPosY - 1 ||
			pBullet->m_nPosX == (*it)->m_nPosX + 1 && pBullet->m_nPosY == (*it)->m_nPosY ||
			pBullet->m_nPosX == (*it)->m_nPosX + 1 && pBullet->m_nPosY == (*it)->m_nPosY + 1 ||
			pBullet->m_nPosX == (*it)->m_nPosX - 1 && pBullet->m_nPosY == (*it)->m_nPosY - 1 ||
			pBullet->m_nPosX == (*it)->m_nPosX - 1 && pBullet->m_nPosY == (*it)->m_nPosY ||
			pBullet->m_nPosX == (*it)->m_nPosX - 1 && pBullet->m_nPosY == (*it)->m_nPosY + 1 ||
			pBullet->m_nPosX == (*it)->m_nPosX && pBullet->m_nPosY == (*it)->m_nPosY + 1 ||
			pBullet->m_nPosX == (*it)->m_nPosX && pBullet->m_nPosY == (*it)->m_nPosY - 1 ) {
			ReduceHp(pBullet, it);
			return true;
		}
	}
	return false;
}
//����̹��Ѫ�������С��0 �Ƴ�̹��
void TankMgr::ReduceHp(ObjectBase *pBullet, std::vector<ObjectBase*>::iterator &it)
{
	(*it)->m_nHp -= pBullet->m_nAttack;
	if ((*it)->m_nHp <= 0)
	{
		AddShowScore(pBullet->m_nType);
		RemoveTank(it);
	}
}

//����̹��
std::vector<ObjectBase*>::iterator& TankMgr::RemoveTank(std::vector<ObjectBase*>::iterator &it)
{
	(*it)->OnClear();
	//���ɾ��������� ҲҪ����Ӧ�����������ַ����
	if ((*it)->m_nType == PLAYER1_TYPE) {
		m_pPlayer1 = nullptr;
	}
	else if ((*it)->m_nType == PLAYER2_TYPE) {
		m_pPlayer2 = nullptr;
	}
	delete((*it));
	(*it) = nullptr;
	it = m_vTankList.erase(it);
	return it;
}
//��������̹��
 void TankMgr::RemoveAllTank() {
	 std::vector<ObjectBase*>::iterator it = m_vTankList.begin();
	 while (it != m_vTankList.end())
	 {
		 it = RemoveTank(it);
	 }
 }
 //��ҷ���
 void TankMgr::AddShowScore(int type) {
	 if (type == PLAYER1_TYPE) {
		 m_nPlayer1Score+=10;
	 }
	 else if (type == PLAYER2_TYPE) {
		 m_nPlayer2Score += 10;
	 }
	 char szScore1[32];
	 sprintf_s(szScore1, "%d", m_nPlayer1Score);
	 char szScore2[32];
	 sprintf_s(szScore2, "%d", m_nPlayer2Score);

	 OnRenderChar(35, 43, szScore1, 7);
	 OnRenderChar(36, 43, szScore2, 7);
	 
 }
