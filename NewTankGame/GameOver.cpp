#include "stdafx.h"
#include "GameOver.h"
#include "GameMenu.h"
#include "BulletMgr.h"
#include "TankMgr.h"


static GameOver* pOver = nullptr;
GameOver::GameOver()
{
}


GameOver::~GameOver()
{
}

GameOver* GameOver::GetInstance()
{
	if (pOver == nullptr) {
		pOver = new GameOver();
	}
	return pOver;
}

void GameOver::Init()
{
	if (!m_isInit) return;
	system("cls");
	//播放游戏结束音乐
	PlaySound("./sound/background.wav");
	OnRender();
	m_isInit = false;
}

void GameOver::Update()
{
	//按ESC键返回菜单
	if (KEYDOWN(VK_ESCAPE)) {
		GameMenu::GetInstance()->m_isInit = true;
		g_GameStatus = GAME_MENU;
	}
}

void GameOver::OnRender()
{
	//编辑地图时物体颜色不同 会改变菜单的颜色 所以渲染菜单时先改回原来的颜色
	OnRenderChar(0, 0, "", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	printf("\n\n\t\t\t★★★★★★★★★★★★★★★★★★★★★★★★★★\n");
	printf("\t\t\t★                                                ★\n");
	printf("\t\t\t★                                                ★\n");
	printf("\t\t\t★                                                ★\n");
	printf("\t\t\t★                                                ★\n");
	printf("\t\t\t★      游戏结束，请按ESC键返回菜单！             ★\n");
	printf("\t\t\t★                                                ★\n");
	printf("\t\t\t★                                                ★\n");
	printf("\t\t\t★                                                ★\n");
	printf("\t\t\t★                                                ★\n");
	printf("\t\t\t★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n\n");
}
