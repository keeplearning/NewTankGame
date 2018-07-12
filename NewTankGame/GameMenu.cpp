#include "stdafx.h"
#include "GameMenu.h"
#include "GameMap.h"
#include "TankMgr.h"

static GameMenu *pMenu = nullptr;
GameMenu::GameMenu()
{
}


GameMenu::~GameMenu()
{
}

GameMenu* GameMenu::GetInstance()
{
	if (pMenu == nullptr) {
		pMenu = new GameMenu();
	}
	return pMenu;
}

void GameMenu::Init() {
	if (!m_isInit)//每次只控制初始化一次
		return;
	system("cls");// 每一次重新进入初始化进行清屏一次
	m_nY = 15;
	strcpy_s(m_szString, "→");
	OnRender();
	//播放背景音乐
	PlaySound("./sound/background.wav");
	m_isInit = false;
}

void GameMenu::Update() {
	if (KEYDOWN(VK_UP)) {//按下向上键
		OnRenderChar(m_nY, 18, "  ", NULL);
		m_nY-=2;
		if (m_nY < 15) {
			m_nY = 21;
		}
		OnRenderChar(m_nY, 18, m_szString, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	else if (KEYDOWN(VK_DOWN)) {//按下向下键
		OnRenderChar(m_nY, 18, "  ", NULL);
		m_nY += 2;
		if (m_nY > 21) {
			m_nY = 15;
		}
		OnRenderChar(m_nY, 18, m_szString, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	else if (KEYDOWN(VK_RETURN)) {
		if (m_nY == 15) {
			g_GameStatus = GAME_PLAY;
			//让地图和坦克初始化
			GameMap::GetInstance()->m_isInit = true;
			TankMgr::GetInstance()->m_isInit = true;
		}
		else if (m_nY == 17) {
			g_GameStatus = GAME_EDITOR;
		}
		else if (m_nY == 19) {
			g_GameStatus = GAME_READFILE;
			//读取存档
			m_objLoad.GameRead();
			GameMap::GetInstance()->m_isInit = true;
			TankMgr::GetInstance()->m_isInit = true;
		}
		else if (m_nY == 21) {
			g_GameStatus = GAME_EXIT;
		}
	}
}

void GameMenu::OnRender()
{
	//编辑地图时物体颜色不同 会改变菜单的颜色 所以渲染菜单时先改回原来的颜色
	OnRenderChar(0, 0, "", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	printf("\n\n\t\t\t★★★★★★★★★★★★★★★★★★★★★★★★★★\n");
	printf("\t\t\t★              ■■                              ★\n");
	printf("\t\t\t★            ■■                          坦    ★\n");
	printf("\t\t\t★      ■      ■■                              ★\n");
	printf("\t\t\t★    ■■■                                克    ★\n");
	printf("\t\t\t★    ■  ■                                      ★\n");
	printf("\t\t\t★                      ■■                大    ★\n");
	printf("\t\t\t★                    ■■                        ★\n");
	printf("\t\t\t★                      ■■                战    ★\n");
	printf("\t\t\t★                                                ★\n");
	printf("\t\t\t★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n\n");
	printf("\t\t\t\t\t开 始 游 戏\n\n");
	printf("\t\t\t\t\t编 辑 地 图\n\n");
	printf("\t\t\t\t\t读 取 存 档\n\n");
	printf("\t\t\t\t\t退 出 游 戏\n\n");

	OnRenderChar(m_nY, 18, m_szString, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
