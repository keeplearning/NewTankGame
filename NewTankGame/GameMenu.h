#pragma once
#include "Definition.h"
#include "GameBase.h"
#include "GameLoad.h"

class GameMenu : public GameBase
{
public:
	GameMenu();
	~GameMenu();
public:
	static GameMenu* GetInstance();
	virtual void Init() override;
	virtual void Update() override;
	virtual void OnRender() override;
public:
	short m_nY;					// 光标Y轴
	char m_szString[3];			// 光标字符
	GameLoad m_objLoad;
};

