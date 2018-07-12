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
	short m_nY;					// ���Y��
	char m_szString[3];			// ����ַ�
	GameLoad m_objLoad;
};

