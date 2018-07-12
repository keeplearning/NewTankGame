#include "stdafx.h"
#include "GameMap.h"
#include "MapEditor.h"
#include "TankMgr.h"
#include "GameOver.h"
#include "BulletMgr.h"

static GameMap *pMap = nullptr;

GameMap::GameMap():
	nMapId(1)
{
}


GameMap::~GameMap()
{
}

GameMap* GameMap::GetInstance()
{
	if (pMap == nullptr) {
		pMap = new GameMap();
	}
	return pMap;
}

void GameMap::Init()
{
	if (!m_isInit) return;
	//清理屏幕
	system("cls");
	//只有游戏状态为正常开始游戏且没有编辑过地图才需要读取地图
	if (g_GameStatus == GAME_PLAY)
	{
		if (!MapEditor::GetInstance()->m_isEditor){
			//读取地图
			ReadMap();
		}
	}
	
	//渲染地图
	OnRender(); 

	//播放背景音乐
	PlaySound("./sound/background.wav");

	m_isInit = false;
	//下次再进入游戏，就重新读取地图
	MapEditor::GetInstance()->m_isEditor = false;
}

void GameMap::Update()
{
	//移除所有坦克和子弹
	BulletMgr::GetInstance()->RemoveAllBullet();
	TankMgr::GetInstance()->RemoveAllTank();
	//如果第三关胜利，游戏结束
	if (nMapId >= 3)
	{
		nMapId = 1;
		GameOver::GetInstance()->m_isInit = true;
		g_GameStatus = GAME_OVER;
	}
	else {
		//进入下一关
		TankMgr::GetInstance()->m_isInit = true;
		nMapId++;
		m_isInit = true;
	}
}

void GameMap::ReadMap() {
	char szTextName[64];
	sprintf_s(szTextName, "Map%d.txt",nMapId);
	FILE *pFileText;
	errno_t err;
	if ((err = fopen_s(&pFileText, szTextName, "r")) != 0)
	{
		printf("文件读取失败！");
		return;
	}
	fseek(pFileText, 0, SEEK_END); //把指针移动到文件的结尾 ，获取文件长度
	int len = ftell(pFileText);
	fseek(pFileText, 0, SEEK_SET);
	for (int i = 0; i < MAXROW; i++)
	{
		for (int j = 0; j < MAXCOL; j++) {
			fscanf_s(pFileText, "%d ", &m_Map[i][j]);
			int i = ftell(pFileText);
		}
	}
	fclose(pFileText);
}

void GameMap::OnRender() {
	for (int i = 0; i < MAXROW; i++)
	{
		for (int j = 0; j < MAXCOL; j++)
		{
			if (m_Map[i][j] == GAME_WALL)//墙
				OnRenderChar(i, j, "■", COLOR_WALL);
			else if (m_Map[i][j] == GAME_GRASS)//草地
				OnRenderChar(i, j, "※", COLOR_GRASS);
			else if (m_Map[i][j] == GAME_BRICK) //砖块
				OnRenderChar(i, j, "□", COLOR_BRICK);
			else
				OnRenderChar(i, j, "  ", NULL);
		}
		printf("\n");
	}


}

