#include "stdafx.h"
#include "GameBullet.h"
#include "GameMap.h"

GameBullet::GameBullet(int x, int y, int dir, int color, int type, int hp, int attack, char* str, int ascription):
	ObjectBase(x, y, dir, color, type, hp, attack, str, ascription)
{
}


GameBullet::GameBullet()
{

}

GameBullet::~GameBullet()
{
}


void GameBullet::OnClear()
{
	OnRenderWithThing(m_nPosX, m_nPosY, "  ");
}

void GameBullet::OnRender()
{
	OnRenderWithThing(m_nPosX, m_nPosY, m_szStr);
}
