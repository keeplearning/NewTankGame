#pragma once
#include <tchar.h>
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <time.h> 
#include <iostream>
#include <vector>
#include <string>

using namespace std;
#pragma comment(lib,"winmm.lib")

enum {
	GAME_MENU = 1001,
	GAME_EDITOR,
	GAME_PLAY,
	GAME_READFILE,
	GAME_OVER,
	GAME_EXIT
};

enum
{
	GAME_SPACE = 0,
	GAME_WALL,
	GAME_GRASS,
	GAME_BRICK
};

enum
{
	DIR_UP = 0,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT
};

#define MAXROW 35
#define MAXCOL 50

#define COLOR_GRASS 0x000A
#define COLOR_WALL 0x0008
#define COLOR_BRICK 0x000E

#define ENEMY_TYPE 100
#define PLAYER1_TYPE 101
#define PLAYER2_TYPE 102
#define PLAYER_TYPE 103

//敌人类型
enum 
{
	ENEMY_FAST,//速度快，攻击力低，血少
	ENEMY_SLOWLY,//速度慢，攻击力高，血多
	ENEMY_NORMAL//速度正常，攻击力一般，血一般
};

struct ObjectInfo
{
	//坦克坐标
	int nPosX;
	int nPosY;
	//方向
	int nDir;
	//颜色
	int nColor;
	//类型
	int nType;
	//是否存活
	bool isAlive;
	//血量
	int nHp;
	//攻击力
	int nAttack;
	//计时器，用来做移动速度
	clock_t nBegin;
	//用来画坦克或者子弹的字符串
	char szStr[3];
	//归属于敌方坦克还是玩家
	int nAscription;
};

// 键盘按下
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000)?1:0)

extern int g_GameStatus; //游戏状态 控制整个游戏的进程

