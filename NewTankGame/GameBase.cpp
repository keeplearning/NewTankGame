#include "stdafx.h"
#include "GameBase.h"
#include "GameMap.h"


ObjectBase::ObjectBase(int x, int y, int dir, int color, int type, int hp, int attack, char *str, int ascription) :
	m_nPosX(x),
	m_nPosY(y),
	m_nDir(dir),
	m_nColor(color),
	m_nType(type),
	m_isAlive(true),
	m_nHp(hp),
	m_nAttack(attack),
	m_nAscription(ascription),
	m_nBegin(clock())
{
	strcpy_s(m_szStr, str);
}

ObjectBase::ObjectBase()
{

}

ObjectBase::~ObjectBase()
{

}

//在草丛中或其他物体中不渲染坦克或者子弹 只改变该物体的颜色，例如草丛
void ObjectBase::OnRenderWithThing(int x, int y, char *pStr)
{
	int color = 0;
	pStr == "  " ? color = COLOR_GRASS : color = m_nColor;
	GameMap::GetInstance()->m_Map[x][y] == GAME_GRASS ? OnRenderChar(x, y, "※", color) : OnRenderChar(x, y, pStr, m_nColor);
}

void ObjectBase::OnClear() {

}

void ObjectBase::OnMove()
{
	if (m_nDir == DIR_UP) {
		m_nPosX--;
	}
	else if (m_nDir == DIR_DOWN) {
		m_nPosX++;
	}
	else if (m_nDir == DIR_LEFT) {
		m_nPosY--;
	}
	else if (m_nDir == DIR_RIGHT) {
		m_nPosY++;
	}
}

bool ObjectBase::IsMove()
{
	return false;
}

//获取物体的下一个X坐标 这样不会把一些不能删除的物体例如墙删除掉
int ObjectBase::GetNextPosX(int num)
{
	int posX = m_nPosX;
	if (m_nDir == DIR_UP)
	{
		posX-=num;
	}
	else if (m_nDir == DIR_DOWN)
	{
		posX+=num;
	}
	return posX;
}

//获取物体的下一个Y坐标
int ObjectBase::GetNextPosY(int num)
{
	int posY = m_nPosY;
    if (m_nDir == DIR_LEFT)
	{
		 posY -= num;
	}
	else if (m_nDir == DIR_RIGHT)
	{
		posY += num;
	}
	return posY;
}

GameBase::GameBase():
	m_isInit(true)
{

}

GameBase::~GameBase()
{

}

//播放音乐
void GameBase::PlaySound(const char *str) {
	PlaySoundA(str, NULL, SND_ASYNC | SND_NODEFAULT);
}

void GameBase::OnRenderChar(int High, int Wide, char* pszChar, WORD wArr)// 渲染函数
{
	CONSOLE_CURSOR_INFO cci;		// 设置光标属性
	cci.dwSize = 1;
	cci.bVisible = FALSE;			// 是否显示光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	COORD loc = { Wide * 2, High };	// x的值是Wide的2倍
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wArr);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
	printf(pszChar);			//打印时需要注意有些特殊字符是占两个字节
}

void GameBase::Init()
{

}

void GameBase::Update()
{

}

void GameBase::OnRender()
{

}

