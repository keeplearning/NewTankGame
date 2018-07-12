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

//��������
enum 
{
	ENEMY_FAST,//�ٶȿ죬�������ͣ�Ѫ��
	ENEMY_SLOWLY,//�ٶ������������ߣ�Ѫ��
	ENEMY_NORMAL//�ٶ�������������һ�㣬Ѫһ��
};

struct ObjectInfo
{
	//̹������
	int nPosX;
	int nPosY;
	//����
	int nDir;
	//��ɫ
	int nColor;
	//����
	int nType;
	//�Ƿ���
	bool isAlive;
	//Ѫ��
	int nHp;
	//������
	int nAttack;
	//��ʱ�����������ƶ��ٶ�
	clock_t nBegin;
	//������̹�˻����ӵ����ַ���
	char szStr[3];
	//�����ڵз�̹�˻������
	int nAscription;
};

// ���̰���
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000)?1:0)

extern int g_GameStatus; //��Ϸ״̬ ����������Ϸ�Ľ���

