#pragma once
#include "Definition.h"
#include "GameBase.h"

class MapEditor : public GameBase
{
public:
	MapEditor();
	~MapEditor();
public:
	static MapEditor* GetInstance();
	virtual void Init() override;
	virtual void Update() override;
	virtual void OnRender() override;
	void MouseEventProc(MOUSE_EVENT_RECORD mer);
	void WriteMap(COORD pos);
public:
	bool m_isEditor;
private:
	char m_szSign[3];
	WORD m_wColor;
};

