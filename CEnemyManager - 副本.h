#pragma once
#include"Singleton.h"
#include "BulletManager.h"
class CEnemy;
class Cmap;
class CPlayer;
class CBoss;
class CImpact;
/**
  *这是敌人管理类
  
  *@param vector<CEnemy*> vecEnemy 敌人的内存池使用一次
  *@param list<CEnemy*> listActive 敌人的内存池 存放激活的敌人
  *@param list<CEnemy*> listDead 敌人的内存池 存放死亡的敌人
*/
class CEnemyManager :public Singleton<CEnemyManager>
{
	vector<CEnemy*> vecEnemy;  ///<初始化链表
	
	list<CEnemy*> listActive;  ///<激活链表
	
	list<CEnemy*> listDead;   ///<死亡链表

	int Size;
	bool bDead = false;           ///<对象池空间分配
	bool isBoss = false;          ///<控制产生boss 且只产生一次
public:
	Cmap *m_pMap; ///<地图指针
	CPlayer*m_Pplayer;
	CBoss *m_pBoss;
	CImpact *m_pImpact;
	CBulletManager*m_pBulletManager;

public:
	void Draw(HANDLE hand);
	void Init(int size);
	void SetPmap(Cmap*map) { m_pMap = map; }
	void SetPplayer(CPlayer*player) { m_Pplayer = player; }
	void SetImpact(CImpact *Impact) { m_pImpact = Impact; }
	void SetBulletManager(CBulletManager*BulletManager) { m_pBulletManager = BulletManager; }

	list<CEnemy*> GetListActive() { return listActive; }
	void Update(CBulletManager*BulletManager);
	void Death();

public:
	CEnemyManager();
	~CEnemyManager();
};

