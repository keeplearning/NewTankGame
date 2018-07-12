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
	//初始化地图 全部都为空地
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

	//渲染地图
	OnRender();
}

//更新地图编辑器
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
		if (KEYDOWN(VK_SPACE))															// 按下空格清空地图
			Init();
		else if (KEYDOWN(VK_ESCAPE))													
		{
			m_isEditor = true;
			GameMenu::GetInstance()->m_isInit = true;
			g_GameStatus = GAME_MENU;													// 状态切换
			break;
		}
		if (KEYDOWN('1')) {
			m_wColor = COLOR_WALL;
			strcpy_s(m_szSign, 3, "■");
		}
		else if (KEYDOWN('2')) {
			m_wColor = NULL;
			strcpy_s(m_szSign, 3, "  ");
		}											
		else if (KEYDOWN('3')) {
			m_wColor = COLOR_GRASS;
			strcpy_s(m_szSign, 3, "※");
		}
															
		else if (KEYDOWN('4')) {
			m_wColor = COLOR_BRICK;
			strcpy_s(m_szSign, 3, "□");
		}
	}
}

void MapEditor::OnRender()
{
	GameMap::GetInstance()->OnRender();

	OnRenderChar(35, 1, "ESC保存地图并返回菜单", COLOR_WALL);
	OnRenderChar(35, 25, "按下1键用鼠标编辑墙", COLOR_WALL);
	OnRenderChar(36, 1, "按下2键用鼠标编辑空地", COLOR_WALL);
	OnRenderChar(36, 25, "按下3键用鼠标编辑草地", COLOR_WALL);
	OnRenderChar(37, 1, "按下4键用鼠标编辑砖块", COLOR_WALL);
	OnRenderChar(37, 25, "按空格键清空地图", COLOR_WALL);
}

// 鼠标事件 
void MapEditor::MouseEventProc(MOUSE_EVENT_RECORD mer)
{
	switch (mer.dwEventFlags)
	{
	case 0:
	{
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)								// 鼠标左键单击
		{
			WriteMap(mer.dwMousePosition);
		}
	}
	break;
	case MOUSE_MOVED:
	{
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)								// 拖动状态并且鼠标左键按下
		{
			WriteMap(mer.dwMousePosition);
		}
	}
	default:
		break;
	}
}

//将数据写入地图中
void MapEditor::WriteMap(COORD pos) {
	if (pos.Y>= MAXROW || pos.X / 2 >= MAXCOL)
		return;

	OnRenderChar(pos.Y, pos.X / 2, m_szSign, m_wColor);
	if (strcmp(m_szSign, "■") == 0)
		GameMap::GetInstance()->m_Map[pos.Y][pos.X / 2] = 1;
	else if (strcmp(m_szSign, "  ") == 0)
		GameMap::GetInstance()->m_Map[pos.Y][pos.X / 2] = 0;
	else if (strcmp(m_szSign, "※") == 0)
		GameMap::GetInstance()->m_Map[pos.Y][pos.X / 2] = 2;
	else if (strcmp(m_szSign, "□") == 0)
		GameMap::GetInstance()->m_Map[pos.Y][pos.X / 2] = 3;

}

