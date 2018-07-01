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
	vector<CProps*> vecEnemy;///<��ʼ��ʱ������еĵ���
	
	list<CProps*> listActive;///<��������
	
	list<CProps*> listDead;///<��������

	vector<string> VecString;///<������е��ߵ��ļ�·�����ļ���
	int rows;///<���߹������ļ�������
	int thing;///<�������
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

