#include "stdafx.h"
#include "info.h"
#include "GameBase.h"


ObjectInfo& ObjectInfo::operator=(const ObjectBase *Obj)
{
	{
		nPosX = Obj->m_nPosX;
		nPosY = Obj->m_nPosY;
		nDir = Obj->m_nDir;
		nColor = Obj->m_nColor;
		nType = Obj->m_nType;
		isAlive = Obj->m_isAlive;
		nHp = Obj->m_nHp;
		nAttack = Obj->m_nAttack;
		nBegin = Obj->m_nBegin;
		strcpy_s(szStr, Obj->m_szStr);
		nAscription = Obj->m_nAscription;
		return *this;
	}
}
