#pragma once
#include "Definition.h"

class GameBase
{
public:
	GameBase();
	~GameBase();
public:
	//��������
	void PlaySound(const char *str);
	//��Ⱦ�ַ�
	void OnRenderChar(int High, int Wide, char* pszChar, WORD wArr);
	//��ʼ��
	virtual void Init();
	//����
	virtual void Update();
	//��Ⱦ
	virtual void OnRender();
public:
	//�����Ƿ��ʼ��
	bool m_isInit;
};

class ObjectBase : public GameBase
{
public:
	ObjectBase();
	ObjectBase(int x, int y, int dir, int color, int type, int hp, int attack, char *str, int ascription);
	~ObjectBase();
public:
	//������
	virtual void OnClear();
	//�ƶ�����
	virtual void OnMove();
	virtual bool IsMove();
	//��ȡ��һ��λ�õ�����
	int GetNextPosX(int num);
	int GetNextPosY(int num);
	//�ڲ����ӵ���ɫ
	void OnRenderWithThing(int x, int y, char *pStr);
public:
	//̹������
	int m_nPosX;
	int m_nPosY;
	//����
	int m_nDir;
	//��ɫ
	int m_nColor;
	//����
	int m_nType;
	//�Ƿ���
	bool m_isAlive;
	//Ѫ��
	int m_nHp;
	//������
	int m_nAttack;
	//��ʱ�����������ƶ��ٶ�
	clock_t m_nBegin;
	//������̹�˻����ӵ����ַ���
	char m_szStr[3];
	//�����ڵз�̹�˻������
	int m_nAscription;
};






