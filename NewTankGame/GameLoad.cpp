#include "stdafx.h"
#include "GameLoad.h"
#include "Definition.h"
#include "TankMgr.h"
#include "BulletMgr.h"
#include "GameMap.h"


GameLoad::GameLoad()
{
}


GameLoad::~GameLoad()
{
}

void GameLoad::GameSave()
{
	FILE *pFile = nullptr;
	errno_t err;
	err = fopen_s(&pFile, "info.i", "w");
	if (err != 0) {
		printf("读取文件失败");
		return;
	}
	//保存关卡
	fwrite(&GameMap::GetInstance()->nMapId, sizeof(int), 1, pFile);
	//保存地图
	fwrite(&GameMap::GetInstance()->m_Map, sizeof(GameMap::GetInstance()->m_Map), 1, pFile);
	//保存坦克数量
	unsigned int num = TankMgr::GetInstance()->m_vTankList.size();
	fwrite(&num, sizeof(unsigned int), 1, pFile);
	//保存坦克数据
	for (int i = 0; i < TankMgr::GetInstance()->m_vTankList.size(); i++)
	{
		ObjectBase *pObj = TankMgr::GetInstance()->m_vTankList[i];
		ObjectInfo obj;
		obj.nPosX = pObj->m_nPosX;
		obj.nPosY = pObj->m_nPosY;
		obj.nDir = pObj->m_nDir;
		obj.nColor = pObj->m_nColor;
		obj.nType = pObj->m_nType;
		obj.isAlive = pObj->m_isAlive;
		obj.nHp = pObj->m_nHp;
		obj.nAttack = pObj->m_nAttack;
		obj.nBegin = pObj->m_nBegin;
		strcpy_s(obj.szStr, pObj->m_szStr);
		obj.nAscription = pObj->m_nAscription;
		fwrite(&obj, sizeof(ObjectInfo), 1, pFile);
	}
	//保存子弹数量
	num = BulletMgr::GetInstance()->m_vBulletList.size();
	fwrite(&num, sizeof(unsigned int), 1, pFile);
	//保存子弹数据
	for (int i = 0; i < BulletMgr::GetInstance()->m_vBulletList.size(); i++)
	{
		ObjectBase *pObj = BulletMgr::GetInstance()->m_vBulletList[i];
		ObjectInfo obj;
		obj.nPosX = pObj->m_nPosX;
		obj.nPosY = pObj->m_nPosY;
		obj.nDir = pObj->m_nDir;
		obj.nColor = pObj->m_nColor;
		obj.nType = pObj->m_nType;
		obj.isAlive = pObj->m_isAlive;
		obj.nHp = pObj->m_nHp;
		obj.nAttack = pObj->m_nAttack;
		obj.nBegin = pObj->m_nBegin;
		strcpy_s(obj.szStr, pObj->m_szStr);
		obj.nAscription = pObj->m_nAscription;
		fwrite(&obj, sizeof(ObjectInfo), 1, pFile);
	}
	fclose(pFile);
}

void GameLoad::GameRead()
{
	FILE *pFile = nullptr;
	errno_t err;
	err = fopen_s(&pFile, "info.i", "r");
	if (err != 0) {
		printf("读取文件失败");
		return;
	}
	//读取关卡
	fread(&GameMap::GetInstance()->nMapId, sizeof(int), 1, pFile);
	//读取地图
	fread(&GameMap::GetInstance()->m_Map, sizeof(GameMap::GetInstance()->m_Map), 1, pFile);
	//读取坦克数量
	unsigned int num = 0;
	fread(&num, sizeof(unsigned int), 1, pFile);
	//读取坦克数据
	for (int i = 0; i < num; i++)
	{
		
		ObjectInfo obj;
		fread(&obj, sizeof(ObjectInfo), 1, pFile);
		ObjectBase *pTank = new GameTank();
		pTank->m_nPosX = obj.nPosX;
		pTank->m_nPosY = obj.nPosY;
		pTank->m_nDir = obj.nDir;
		pTank->m_nColor = obj.nColor;
		pTank->m_nType = obj.nType;
		pTank->m_isAlive = obj.isAlive;
		pTank->m_nHp = obj.nHp;
		pTank->m_nAttack = obj.nAttack;
		pTank->m_nBegin = obj.nBegin;
		strcpy_s(pTank->m_szStr, obj.szStr);
		pTank->m_nAscription = obj.nAscription;
		TankMgr::GetInstance()->m_vTankList.push_back(pTank);
	}
	//读取子弹数量
	fread(&num, sizeof(unsigned int), 1, pFile);
	//读取子弹数据
	for (int i = 0; i < num; i++)
	{
		ObjectBase *pBullet = new GameBullet();
		ObjectInfo obj;
		fread(&obj, sizeof(ObjectInfo), 1, pFile);
		pBullet->m_nPosX = obj.nPosX;
		pBullet->m_nPosY = obj.nPosY;
		pBullet->m_nDir = obj.nDir;
		pBullet->m_nColor = obj.nColor;
		pBullet->m_nType = obj.nType;
		pBullet->m_isAlive = obj.isAlive;
		pBullet->m_nHp = obj.nHp;
		pBullet->m_nAttack = obj.nAttack;
		pBullet->m_nBegin = obj.nBegin;
		strcpy_s(pBullet->m_szStr, obj.szStr);
		pBullet->m_nAscription = obj.nAscription;
		BulletMgr::GetInstance()->m_vBulletList.push_back(pBullet);
	}

	fclose(pFile);
}
