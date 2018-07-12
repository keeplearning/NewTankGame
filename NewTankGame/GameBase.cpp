#include "stdafx.h"
#include "GameBase.h"
#include "GameMap.h"


ObjectBase::ObjectBase(int x, int y, int dir, int color, int type, int hp, int attack, char *str, int ascription) :
	m_nPosX(x),
	m_nPosY(y),
	m_nDir(dir),
	m_nColor(color),
	m_nType(type),
	m_isAlive(true),
	m_nHp(hp),
	m_nAttack(attack),
	m_nAscription(ascription),
	m_nBegin(clock())
{
	strcpy_s(m_szStr, str);
}

ObjectBase::ObjectBase()
{

}

ObjectBase::~ObjectBase()
{

}

//�ڲݴ��л����������в���Ⱦ̹�˻����ӵ� ֻ�ı���������ɫ������ݴ�
void ObjectBase::OnRenderWithThing(int x, int y, char *pStr)
{
	int color = 0;
	pStr == "  " ? color = COLOR_GRASS : color = m_nColor;
	GameMap::GetInstance()->m_Map[x][y] == GAME_GRASS ? OnRenderChar(x, y, "��", color) : OnRenderChar(x, y, pStr, m_nColor);
}

void ObjectBase::OnClear() {

}

void ObjectBase::OnMove()
{
	if (m_nDir == DIR_UP) {
		m_nPosX--;
	}
	else if (m_nDir == DIR_DOWN) {
		m_nPosX++;
	}
	else if (m_nDir == DIR_LEFT) {
		m_nPosY--;
	}
	else if (m_nDir == DIR_RIGHT) {
		m_nPosY++;
	}
}

bool ObjectBase::IsMove()
{
	return false;
}

//��ȡ�������һ��X���� ���������һЩ����ɾ������������ǽɾ����
int ObjectBase::GetNextPosX(int num)
{
	int posX = m_nPosX;
	if (m_nDir == DIR_UP)
	{
		posX-=num;
	}
	else if (m_nDir == DIR_DOWN)
	{
		posX+=num;
	}
	return posX;
}

//��ȡ�������һ��Y����
int ObjectBase::GetNextPosY(int num)
{
	int posY = m_nPosY;
    if (m_nDir == DIR_LEFT)
	{
		 posY -= num;
	}
	else if (m_nDir == DIR_RIGHT)
	{
		posY += num;
	}
	return posY;
}

GameBase::GameBase():
	m_isInit(true)
{

}

GameBase::~GameBase()
{

}

//��������
void GameBase::PlaySound(const char *str) {
	PlaySoundA(str, NULL, SND_ASYNC | SND_NODEFAULT);
}

void GameBase::OnRenderChar(int High, int Wide, char* pszChar, WORD wArr)// ��Ⱦ����
{
	CONSOLE_CURSOR_INFO cci;		// ���ù������
	cci.dwSize = 1;
	cci.bVisible = FALSE;			// �Ƿ���ʾ���
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	COORD loc = { Wide * 2, High };	// x��ֵ��Wide��2��
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wArr);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
	printf(pszChar);			//��ӡʱ��Ҫע����Щ�����ַ���ռ�����ֽ�
}

void GameBase::Init()
{

}

void GameBase::Update()
{

}

void GameBase::OnRender()
{

}

