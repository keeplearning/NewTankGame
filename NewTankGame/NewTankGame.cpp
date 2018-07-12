// NewTankGame.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "GameManager.h"
#include "Definition.h"

void InitWindowsSize();

//初始化游戏状态 游戏刚开始为菜单选项
int g_GameStatus = GAME_MENU;

int main()
{
	InitWindowsSize(); //初始化控制台窗口尺寸

	//shift切换中文输入法
	keybd_event(VK_SHIFT, 0, 0, 0);
	Sleep(100);
	keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);

	while (true)
	{
		InitGame();
		UpdateGame();
		if (g_GameStatus == GAME_EXIT)
			break;
		Sleep(60);
	}
    return 0;
}

void InitWindowsSize()
{
	SetConsoleTitle(L"坦克大战");
	HANDLE hStdIn, hStdCut;
	hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	hStdCut = GetStdHandle(STD_OUTPUT_HANDLE);
	// 获取控制台窗口大小
	COORD pos = GetLargestConsoleWindowSize(hStdCut);
	COORD BufferSize = { pos.X + 1, pos.Y + 1 };
	// 设置控制台缓冲区大小
	if (!SetConsoleScreenBufferSize(hStdCut, BufferSize))
	{
		printf("Buff err(%d, %d)%d\n", BufferSize.X, BufferSize.Y, GetLastError());
		return;
	}
	// 设置控制台窗口大小
	SMALL_RECT srctWindows = { 0, 0, 100, 40 };
	if (!SetConsoleWindowInfo(hStdCut, true, &srctWindows))
	{
		printf("size err %d\n", GetLastError());
		return;
	}
	//设置缓冲区大小
	COORD Buffer = { 100 + 1, 40 + 1 };
	if (!SetConsoleScreenBufferSize(hStdCut, Buffer))
	{
		printf("buffer err(%d, %d)%d\n", Buffer.X, Buffer.Y, GetLastError());
		return;
	}
}

