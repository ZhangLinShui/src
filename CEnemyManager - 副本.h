#pragma once
#include"Singleton.h"
#include "BulletManager.h"
class CEnemy;
class Cmap;
class CPlayer;
class CBoss;
class CImpact;
/**
  *���ǵ��˹�����
  
  *@param vector<CEnemy*> vecEnemy ���˵��ڴ��ʹ��һ��
  *@param list<CEnemy*> listActive ���˵��ڴ�� ��ż���ĵ���
  *@param list<CEnemy*> listDead ���˵��ڴ�� ��������ĵ���
*/
class CEnemyManager :public Singleton<CEnemyManager>
{
	vector<CEnemy*> vecEnemy;  ///<��ʼ������
	
	list<CEnemy*> listActive;  ///<��������
	
	list<CEnemy*> listDead;   ///<��������

	int Size;
	bool bDead = false;           ///<����ؿռ����
	bool isBoss = false;          ///<���Ʋ���boss ��ֻ����һ��
public:
	Cmap *m_pMap; ///<��ͼָ��
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

