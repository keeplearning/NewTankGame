#include "stdafx.h"
#include "Definition.h"
#include "GameBase.h"
#include "GameMenu.h"
#include "GameMap.h"
#include "TankMgr.h"
#include "BulletMgr.h"
#include "MapEditor.h"
#include "GameOver.h"


//��Ϸ��س��������ݵȳ�ʼ��
void InitGame() {
	if (g_GameStatus == GAME_MENU) 
	{
		GameMenu::GetInstance()->Init();
	}
	else if (g_GameStatus == GAME_EDITOR)
	{
		MapEditor::GetInstance()->Init();
	}
	else if (g_GameStatus == GAME_PLAY || g_GameStatus == GAME_READFILE)
	{
		GameMap::GetInstance()->Init();
		TankMgr::GetInstance()->Init();
	}
	else if (g_GameStatus == GAME_OVER)
	{
		GameOver::GetInstance()->Init();
	}
}

//��Ϸ��س��������ݸ���
void UpdateGame() {
	if (g_GameStatus == GAME_MENU) 
	{
		GameMenu::GetInstance()->Update();
	}
	else if (g_GameStatus == GAME_EDITOR) 
	{
		MapEditor::GetInstance()->Update();
	}
	else if (g_GameStatus == GAME_PLAY)
	{
		BulletMgr::GetInstance()->Update();
		TankMgr::GetInstance()->Update();
	}
	else if (g_GameStatus == GAME_OVER)
	{
		GameOver::GetInstance()->Update();
	}
}

