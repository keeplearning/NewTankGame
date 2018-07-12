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
	//������Ļ
	system("cls");
	//ֻ����Ϸ״̬Ϊ������ʼ��Ϸ��û�б༭����ͼ����Ҫ��ȡ��ͼ
	if (g_GameStatus == GAME_PLAY)
	{
		if (!MapEditor::GetInstance()->m_isEditor){
			//��ȡ��ͼ
			ReadMap();
		}
	}
	
	//��Ⱦ��ͼ
	OnRender(); 

	//���ű�������
	PlaySound("./sound/background.wav");

	m_isInit = false;
	//�´��ٽ�����Ϸ�������¶�ȡ��ͼ
	MapEditor::GetInstance()->m_isEditor = false;
}

void GameMap::Update()
{
	//�Ƴ�����̹�˺��ӵ�
	BulletMgr::GetInstance()->RemoveAllBullet();
	TankMgr::GetInstance()->RemoveAllTank();
	//���������ʤ������Ϸ����
	if (nMapId >= 3)
	{
		nMapId = 1;
		GameOver::GetInstance()->m_isInit = true;
		g_GameStatus = GAME_OVER;
	}
	else {
		//������һ��
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
		printf("�ļ���ȡʧ�ܣ�");
		return;
	}
	fseek(pFileText, 0, SEEK_END); //��ָ���ƶ����ļ��Ľ�β ����ȡ�ļ�����
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
			if (m_Map[i][j] == GAME_WALL)//ǽ
				OnRenderChar(i, j, "��", COLOR_WALL);
			else if (m_Map[i][j] == GAME_GRASS)//�ݵ�
				OnRenderChar(i, j, "��", COLOR_GRASS);
			else if (m_Map[i][j] == GAME_BRICK) //ש��
				OnRenderChar(i, j, "��", COLOR_BRICK);
			else
				OnRenderChar(i, j, "  ", NULL);
		}
		printf("\n");
	}


}

