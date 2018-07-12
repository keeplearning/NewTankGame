#pragma once
#include "Definition.h"
#include "GameBase.h"

class GameMap : public GameBase
{
public:
	GameMap();
	~GameMap();
public:
	static GameMap* GetInstance();
	virtual void Init() override;
	virtual void Update() override;
	virtual void OnRender() override;
	void ReadMap();
	
public:
	unsigned int nMapId;
	int m_Map[MAXROW][MAXCOL];
};

