#include "stdafx.h"
#include "TankMgr.h"
#include "GameMap.h"
#include "BulletMgr.h"
#include "GameMenu.h"
#include "GameOver.h"
#include "GameLoad.h"

//该类主要用于所有地图中所有坦克的管理
static TankMgr *pTankMgr = nullptr;

TankMgr::TankMgr():
	m_pPlayer1(nullptr),
	m_pPlayer2(nullptr)
{
}


TankMgr::~TankMgr()
{
}

//设置单例，地址全局唯一
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
		//从读取存档进入游戏,已经从文件读取了游戏数据，只要渲染了就行
		for (int i = 0; i < m_vTankList.size(); ++i)
		{
			m_vTankList[i]->OnRender();
		}
		//将游戏状态修改为Play
		g_GameStatus = GAME_PLAY;
	}
	else {
		//根据关卡来设置坦克数量
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

		//初始化我方坦克和敌方坦克
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
				strcpy_s(data.szStr, "■");
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
				strcpy_s(data.szStr, "■");
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
					strcpy_s(data.szStr, "○");
				}
				else if (data.nType == ENEMY_SLOWLY)
				{
					data.nColor = FOREGROUND_GREEN;
					data.nHp = 3;
					data.nAttack = 3;
					strcpy_s(data.szStr, "●");
				}
				else if (data.nType == ENEMY_NORMAL)
				{
					data.nColor = FOREGROUND_BLUE;
					data.nHp = 2;
					data.nAttack = 1;
					strcpy_s(data.szStr, "■");
				}

			}
			ObjectBase *tank = new GameTank(data.nPosX, data.nPosY, data.nDir, data.nColor, data.nType, data.nHp, data.nAttack, data.szStr, data.nAscription);
			tank->OnRender();
			m_vTankList.push_back(tank);
		}
	}
	

	m_isInit = false;
	
	//两个玩家的地址
	if (m_vTankList[0]->m_nType == PLAYER1_TYPE)
	{
		m_pPlayer1 = m_vTankList[0];
	}
	if (m_vTankList[1]->m_nType == PLAYER2_TYPE)
	{
		m_pPlayer2 = m_vTankList[1];
	}
	

	//操作说明
	OnRenderChar(35, 1, "SP1方向操作: W键、 S键、 A键、 D键  发射子弹：   J键\t\t\tSP1得分：", 7);
	OnRenderChar(35, 43, "0", 7);		// 初始化积分
	OnRenderChar(36, 1, "SP2方向操作:↑键、↓键、←键、→右  发射子弹：回车键\t\t\tSP2得分：", 7);
	OnRenderChar(36, 43, "0", 7);		// 初始化积分
	OnRenderChar(37, 1, "ESC键返回菜单", 7);
	OnRenderChar(37, 20, "G键保存游戏", 7);

	//初始化玩家分数
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
		//保存游戏
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
		//返回菜单操作
		BulletMgr::GetInstance()->RemoveAllBullet();
		RemoveAllTank();
		GameMenu::GetInstance()->m_isInit = true;
		g_GameStatus = GAME_MENU;
	}
}

//敌方坦克的移动
void TankMgr::EnemyOperate()
{
	int nNum = rand() % 10;
	std::vector<ObjectBase*>::iterator it = m_vTankList.begin();
	for (;it != m_vTankList.end(); ++it)
	{
		//玩家不能自己随机
		if((*it)->m_nType == PLAYER1_TYPE || (*it)->m_nType == PLAYER2_TYPE) continue;
		//坦克随机改变移动方向
		if (nNum >= 0 && nNum <= 2) {
			TankMove(*it, rand()%(DIR_RIGHT + 1));
		}
		else {
			TankMove(*it, (*it)->m_nDir);
		}
		
		//敌方坦克随机发射子弹
		if (nNum == 0) {
			BulletMgr::GetInstance()->Fire(*it);
		}
	}
}

void TankMgr::Update()
{

	//游戏是否结束
	if (IsGameOver()) {
		//胜利了 继续下一关
		if (m_isWin)
		{
			GameMap::GetInstance()->Update();
		}
		//失败了 进入结束界面
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

//游戏是否结束了
bool TankMgr::IsGameOver() {
	//玩家胜利结束
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

	//玩家失败结束
	if (m_pPlayer1 == nullptr && m_pPlayer2 == nullptr) {
		m_isWin = false;
		return true;
	}

	return false;
}

//是否碰到了障碍物
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

//检测坦克与坦克的碰撞
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
	//如果玩家死亡 不能继续操作
	if (pTank == m_pPlayer1 && m_pPlayer1 == nullptr ||
		pTank == m_pPlayer2 && m_pPlayer2 == nullptr)
		return;
	//控制坦克速度
	if (!pTank->IsMove()) return;

	pTank->OnClear();
	//如果坦克的方向不等于要行走的方向，先转向
	if (pTank->m_nDir != nDir) 
	{
		pTank->m_nDir = nDir;
	}
	else 
	{
		do 
		{
			//如果前方有障碍物，不做任何数据操作
			if(IsCollision(pTank))
				break;
			pTank->OnMove();

		} while (false);
		
	}
	pTank->OnRender();
}

//子弹与坦克的碰撞
bool TankMgr::IsBulletCollision(ObjectBase *pBullet)
{
	std::vector<ObjectBase*>::iterator it = m_vTankList.begin();
	for (; it != m_vTankList.end(); ++it)
	{
		//如果是己方自己或者敌方自己的子弹就不检测
		if (pBullet->m_nAscription == PLAYER_TYPE && (*it)->m_nAscription == PLAYER_TYPE ||
			pBullet->m_nAscription == ENEMY_TYPE && (*it)->m_nAscription == ENEMY_TYPE) {
			continue;
		}

		//如果子弹碰到了坦克 销毁坦克
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
//减少坦克血量，如果小于0 移除坦克
void TankMgr::ReduceHp(ObjectBase *pBullet, std::vector<ObjectBase*>::iterator &it)
{
	(*it)->m_nHp -= pBullet->m_nAttack;
	if ((*it)->m_nHp <= 0)
	{
		AddShowScore(pBullet->m_nType);
		RemoveTank(it);
	}
}

//销毁坦克
std::vector<ObjectBase*>::iterator& TankMgr::RemoveTank(std::vector<ObjectBase*>::iterator &it)
{
	(*it)->OnClear();
	//如果删除的是玩家 也要把相应的玩家其他地址赋空
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
//销毁所有坦克
 void TankMgr::RemoveAllTank() {
	 std::vector<ObjectBase*>::iterator it = m_vTankList.begin();
	 while (it != m_vTankList.end())
	 {
		 it = RemoveTank(it);
	 }
 }
 //玩家分数
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
