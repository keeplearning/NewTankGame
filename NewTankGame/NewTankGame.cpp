// NewTankGame.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "GameManager.h"
#include "Definition.h"

void InitWindowsSize();

//��ʼ����Ϸ״̬ ��Ϸ�տ�ʼΪ�˵�ѡ��
int g_GameStatus = GAME_MENU;

int main()
{
	InitWindowsSize(); //��ʼ������̨���ڳߴ�

	//shift�л��������뷨
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
	SetConsoleTitle(L"̹�˴�ս");
	HANDLE hStdIn, hStdCut;
	hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	hStdCut = GetStdHandle(STD_OUTPUT_HANDLE);
	// ��ȡ����̨���ڴ�С
	COORD pos = GetLargestConsoleWindowSize(hStdCut);
	COORD BufferSize = { pos.X + 1, pos.Y + 1 };
	// ���ÿ���̨��������С
	if (!SetConsoleScreenBufferSize(hStdCut, BufferSize))
	{
		printf("Buff err(%d, %d)%d\n", BufferSize.X, BufferSize.Y, GetLastError());
		return;
	}
	// ���ÿ���̨���ڴ�С
	SMALL_RECT srctWindows = { 0, 0, 100, 40 };
	if (!SetConsoleWindowInfo(hStdCut, true, &srctWindows))
	{
		printf("size err %d\n", GetLastError());
		return;
	}
	//���û�������С
	COORD Buffer = { 100 + 1, 40 + 1 };
	if (!SetConsoleScreenBufferSize(hStdCut, Buffer))
	{
		printf("buffer err(%d, %d)%d\n", Buffer.X, Buffer.Y, GetLastError());
		return;
	}
}

