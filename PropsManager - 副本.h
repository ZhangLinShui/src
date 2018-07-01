#pragma once
#include"Singleton.h"
#include "BulletManager.h"

class CProps;
class CEnemy;
class Cmap;
class CPlayer;
class CBoss;
class CImpact;
class CPropsManager :public Singleton<CPropsManager>
{
	vector<CProps*> vecEnemy;///<初始化时存放所有的道具
	
	list<CProps*> listActive;///<激活链表
	
	list<CProps*> listDead;///<死亡链表

	vector<string> VecString;///<存放所有道具的文件路径和文件名
	int rows;///<道具管理类文件的行数
	int thing;///<随机道具
public:
	Cmap *m_pMap;
	CPlayer*m_Pplayer;
	CBoss *m_pBoss;
	CImpact *m_pImpact;
	CBulletManager*m_pBulletManager;

public:
	void Draw();
	void Init(int size);
	void SetPmap(Cmap*map) { m_pMap = map; }
	void SetPplayer(CPlayer*player) { m_Pplayer = player; }
	void SetImpact(CImpact *Impact) { m_pImpact = Impact; }
	void SetBulletManager(CBulletManager*BulletManager) { m_pBulletManager = BulletManager; }

	list<CProps*> GetListActive() { return listActive; }
	void Update(CBulletManager*BulletManager);
public:
	CPropsManager();
	~CPropsManager();
};

