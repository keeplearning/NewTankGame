#pragma once
#include "Definition.h"
#include "GameBase.h"

class GameOver : public GameBase
{
public:
	GameOver();
	~GameOver();
public:
	static GameOver* GetInstance();
	virtual void Init() override;
	virtual void Update() override;
	virtual void OnRender() override;
};

