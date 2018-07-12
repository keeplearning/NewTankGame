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
	//������Ϸ��������
	PlaySound("./sound/background.wav");
	OnRender();
	m_isInit = false;
}

void GameOver::Update()
{
	//��ESC�����ز˵�
	if (KEYDOWN(VK_ESCAPE)) {
		GameMenu::GetInstance()->m_isInit = true;
		g_GameStatus = GAME_MENU;
	}
}

void GameOver::OnRender()
{
	//�༭��ͼʱ������ɫ��ͬ ��ı�˵�����ɫ ������Ⱦ�˵�ʱ�ȸĻ�ԭ������ɫ
	OnRenderChar(0, 0, "", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	printf("\n\n\t\t\t���������������������������\n");
	printf("\t\t\t��                                                ��\n");
	printf("\t\t\t��                                                ��\n");
	printf("\t\t\t��                                                ��\n");
	printf("\t\t\t��                                                ��\n");
	printf("\t\t\t��      ��Ϸ�������밴ESC�����ز˵���             ��\n");
	printf("\t\t\t��                                                ��\n");
	printf("\t\t\t��                                                ��\n");
	printf("\t\t\t��                                                ��\n");
	printf("\t\t\t��                                                ��\n");
	printf("\t\t\t���������������������������\n\n\n");
}
