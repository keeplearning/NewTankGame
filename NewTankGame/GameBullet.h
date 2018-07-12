#pragma once
#include "Definition.h"
#include "GameBase.h"

class GameBullet : public ObjectBase
{
public:
	GameBullet();
	GameBullet(int x, int y, int dir, int color, int type, int hp, int attack, char* str, int ascription);
	~GameBullet();
public:
	virtual void OnRender();
	virtual void OnClear();
	
};

