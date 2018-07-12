#pragma once
#include "Definition.h"

class GameBase
{
public:
	GameBase();
	~GameBase();
public:
	//播放声音
	void PlaySound(const char *str);
	//渲染字符
	void OnRenderChar(int High, int Wide, char* pszChar, WORD wArr);
	//初始化
	virtual void Init();
	//更新
	virtual void Update();
	//渲染
	virtual void OnRender();
public:
	//控制是否初始化
	bool m_isInit;
};

class ObjectBase : public GameBase
{
public:
	ObjectBase();
	ObjectBase(int x, int y, int dir, int color, int type, int hp, int attack, char *str, int ascription);
	~ObjectBase();
public:
	//清理函数
	virtual void OnClear();
	//移动函数
	virtual void OnMove();
	virtual bool IsMove();
	//获取下一个位置的坐标
	int GetNextPosX(int num);
	int GetNextPosY(int num);
	//在草内子弹变色
	void OnRenderWithThing(int x, int y, char *pStr);
public:
	//坦克坐标
	int m_nPosX;
	int m_nPosY;
	//方向
	int m_nDir;
	//颜色
	int m_nColor;
	//类型
	int m_nType;
	//是否存活
	bool m_isAlive;
	//血量
	int m_nHp;
	//攻击力
	int m_nAttack;
	//计时器，用来做移动速度
	clock_t m_nBegin;
	//用来画坦克或者子弹的字符串
	char m_szStr[3];
	//归属于敌方坦克还是玩家
	int m_nAscription;
};






