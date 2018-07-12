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
	if (!m_isInit)//ÿ��ֻ���Ƴ�ʼ��һ��
		return;
	system("cls");// ÿһ�����½����ʼ����������һ��
	m_nY = 15;
	strcpy_s(m_szString, "��");
	OnRender();
	//���ű�������
	PlaySound("./sound/background.wav");
	m_isInit = false;
}

void GameMenu::Update() {
	if (KEYDOWN(VK_UP)) {//�������ϼ�
		OnRenderChar(m_nY, 18, "  ", NULL);
		m_nY-=2;
		if (m_nY < 15) {
			m_nY = 21;
		}
		OnRenderChar(m_nY, 18, m_szString, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	else if (KEYDOWN(VK_DOWN)) {//�������¼�
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
			//�õ�ͼ��̹�˳�ʼ��
			GameMap::GetInstance()->m_isInit = true;
			TankMgr::GetInstance()->m_isInit = true;
		}
		else if (m_nY == 17) {
			g_GameStatus = GAME_EDITOR;
		}
		else if (m_nY == 19) {
			g_GameStatus = GAME_READFILE;
			//��ȡ�浵
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
	//�༭��ͼʱ������ɫ��ͬ ��ı�˵�����ɫ ������Ⱦ�˵�ʱ�ȸĻ�ԭ������ɫ
	OnRenderChar(0, 0, "", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	printf("\n\n\t\t\t���������������������������\n");
	printf("\t\t\t��              ����                              ��\n");
	printf("\t\t\t��            ����                          ̹    ��\n");
	printf("\t\t\t��      ��      ����                              ��\n");
	printf("\t\t\t��    ������                                ��    ��\n");
	printf("\t\t\t��    ��  ��                                      ��\n");
	printf("\t\t\t��                      ����                ��    ��\n");
	printf("\t\t\t��                    ����                        ��\n");
	printf("\t\t\t��                      ����                ս    ��\n");
	printf("\t\t\t��                                                ��\n");
	printf("\t\t\t���������������������������\n\n\n");
	printf("\t\t\t\t\t�� ʼ �� Ϸ\n\n");
	printf("\t\t\t\t\t�� �� �� ͼ\n\n");
	printf("\t\t\t\t\t�� ȡ �� ��\n\n");
	printf("\t\t\t\t\t�� �� �� Ϸ\n\n");

	OnRenderChar(m_nY, 18, m_szString, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
