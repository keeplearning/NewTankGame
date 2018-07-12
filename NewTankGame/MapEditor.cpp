#include "stdafx.h"
#include "MapEditor.h"
#include "GameMap.h"
#include "GameMenu.h"

static MapEditor *pMapEditor = nullptr;

MapEditor::MapEditor() :
	m_szSign("  "),
	m_wColor(NULL),
	m_isEditor(false)
{
}

MapEditor::~MapEditor()
{
}

MapEditor* MapEditor::GetInstance()
{
	if (pMapEditor == nullptr) {
		pMapEditor = new MapEditor();
	}
	return pMapEditor;
}

void MapEditor::Init()
{
	//��ʼ����ͼ ȫ����Ϊ�յ�
	for (int i = 0; i < MAXROW; i++)
	{
		for (int j = 0; j < MAXCOL; j++)
		{
			GameMap::GetInstance()->m_Map[i][0] = GAME_WALL;
			GameMap::GetInstance()->m_Map[0][j] = GAME_WALL;
			GameMap::GetInstance()->m_Map[MAXROW - 1][j] = GAME_WALL;
			GameMap::GetInstance()->m_Map[i][MAXCOL - 1] = GAME_WALL;
			if (i >= 1 && i < MAXROW - 1 && j >= 1 && j < MAXCOL - 1)
				GameMap::GetInstance()->m_Map[i][j] = 0;
		}
	}

	//��Ⱦ��ͼ
	OnRender();
}

//���µ�ͼ�༭��
void MapEditor::Update()
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD stcRecord = { 0 };
	DWORD dwRead;
	SetConsoleMode(hStdin, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
	while (true)
	{
		ReadConsoleInput(hStdin, &stcRecord, 1, &dwRead);
		if (stcRecord.EventType == MOUSE_EVENT)
			MouseEventProc(stcRecord.Event.MouseEvent);
		if (KEYDOWN(VK_SPACE))															// ���¿ո���յ�ͼ
			Init();
		else if (KEYDOWN(VK_ESCAPE))													
		{
			m_isEditor = true;
			GameMenu::GetInstance()->m_isInit = true;
			g_GameStatus = GAME_MENU;													// ״̬�л�
			break;
		}
		if (KEYDOWN('1')) {
			m_wColor = COLOR_WALL;
			strcpy_s(m_szSign, 3, "��");
		}
		else if (KEYDOWN('2')) {
			m_wColor = NULL;
			strcpy_s(m_szSign, 3, "  ");
		}											
		else if (KEYDOWN('3')) {
			m_wColor = COLOR_GRASS;
			strcpy_s(m_szSign, 3, "��");
		}
															
		else if (KEYDOWN('4')) {
			m_wColor = COLOR_BRICK;
			strcpy_s(m_szSign, 3, "��");
		}
	}
}

void MapEditor::OnRender()
{
	GameMap::GetInstance()->OnRender();

	OnRenderChar(35, 1, "ESC�����ͼ�����ز˵�", COLOR_WALL);
	OnRenderChar(35, 25, "����1�������༭ǽ", COLOR_WALL);
	OnRenderChar(36, 1, "����2�������༭�յ�", COLOR_WALL);
	OnRenderChar(36, 25, "����3�������༭�ݵ�", COLOR_WALL);
	OnRenderChar(37, 1, "����4�������༭ש��", COLOR_WALL);
	OnRenderChar(37, 25, "���ո����յ�ͼ", COLOR_WALL);
}

// ����¼� 
void MapEditor::MouseEventProc(MOUSE_EVENT_RECORD mer)
{
	switch (mer.dwEventFlags)
	{
	case 0:
	{
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)								// ����������
		{
			WriteMap(mer.dwMousePosition);
		}
	}
	break;
	case MOUSE_MOVED:
	{
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)								// �϶�״̬��������������
		{
			WriteMap(mer.dwMousePosition);
		}
	}
	default:
		break;
	}
}

//������д���ͼ��
void MapEditor::WriteMap(COORD pos) {
	if (pos.Y>= MAXROW || pos.X / 2 >= MAXCOL)
		return;

	OnRenderChar(pos.Y, pos.X / 2, m_szSign, m_wColor);
	if (strcmp(m_szSign, "��") == 0)
		GameMap::GetInstance()->m_Map[pos.Y][pos.X / 2] = 1;
	else if (strcmp(m_szSign, "  ") == 0)
		GameMap::GetInstance()->m_Map[pos.Y][pos.X / 2] = 0;
	else if (strcmp(m_szSign, "��") == 0)
		GameMap::GetInstance()->m_Map[pos.Y][pos.X / 2] = 2;
	else if (strcmp(m_szSign, "��") == 0)
		GameMap::GetInstance()->m_Map[pos.Y][pos.X / 2] = 3;

}

