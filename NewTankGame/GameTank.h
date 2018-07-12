#pragma once
#include "Definition.h"
#include "GameBase.h"

class GameTank : public ObjectBase
{
public:
	GameTank();
	GameTank(int x, int y, int dir, int color, int type, int hp, int attack, char *str, int ascription);
	~GameTank();
	//渲染或擦除坦克
	virtual void OnRender() override;
	virtual void OnClear() override;
	//控制坦克的速度
	virtual bool IsMove() override;
};

