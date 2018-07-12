#pragma once
#include "Definition.h"
#include "GameBase.h"

class GameTank : public ObjectBase
{
public:
	GameTank();
	GameTank(int x, int y, int dir, int color, int type, int hp, int attack, char *str, int ascription);
	~GameTank();
	//��Ⱦ�����̹��
	virtual void OnRender() override;
	virtual void OnClear() override;
	//����̹�˵��ٶ�
	virtual bool IsMove() override;
};

