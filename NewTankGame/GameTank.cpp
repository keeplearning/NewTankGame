#include "stdafx.h"
#include "GameTank.h"
#include "GameMap.h"

int tank[4][3][3] = {
	{	{ 0,1,0},
		{ 1,1,1 },
		{ 1,0,1 }, },
	{
		{ 1,0,1 },
		{ 1,1,1 },
		{ 0,1,0 }, },
	{
		{ 0,1,1 },
		{ 1,1,0 },
		{ 0,1,1 }, },
	{
		{ 1,1,0 },
		{ 0,1,1 },
		{ 1,1,0 }, },
};


GameTank::GameTank(int x, int y, int dir, int color, int type, int hp, int attack, char *str, int ascription) :
		ObjectBase(x, y, dir, color, type, hp, attack, str, ascription)
{
	
}


GameTank::GameTank()
{

}

GameTank::~GameTank()
{
}

void GameTank::OnRender() {
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			int x = m_nPosX - 1 + i;
			int y = m_nPosY - 1 + j;
			if (tank[m_nDir][i][j]) {
				OnRenderWithThing(x, y, m_szStr);
			}
		}
	}
}

void GameTank::OnClear() {

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			int x = m_nPosX - 1 + i;
			int y = m_nPosY - 1 + j;
			if (tank[m_nDir][i][j]) {
				OnRenderWithThing(x, y, "  ");
			}
		}
	}
}

//根据敌方坦克类型来设置坦克的移动速度
bool GameTank::IsMove()
{
	clock_t time = clock();
	unsigned long temp = 0;

	if (m_nType == ENEMY_FAST)
	{
		temp = 100;
	}
	else if (m_nType == ENEMY_SLOWLY)
	{
		temp = 600;
	}
	else if (m_nType == ENEMY_NORMAL)
	{
		temp = 200;
	}

	if (time - m_nBegin >= temp) {
		m_nBegin = time;
		return true;
	}
	return false;
}
