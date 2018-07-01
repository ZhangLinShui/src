#pragma once
#include "Singleton.h"

class Cmap;
class CPlayer;
class CEnemy;
class CBullet;
class CBoss;
class CBulletManager :public Singleton<CBulletManager>
{
	vector<CBullet*> vecEnemy;
	//º§ªÓ¡¥±Ì
	list<CBullet*> listActive;
	//À¿Õˆ¡¥±Ì
	list<CBullet*> listDead;

	int Size;
public:
	Cmap *m_pMap;
	CPlayer*m_Pplayer;
	CEnemy*m_pEnemy;
	CBoss *m_pBoss;


	void SetPmap(Cmap*map) { m_pMap = map; }
	void SetPplayer(CPlayer*player) { m_Pplayer = player; }
	void SetEnemy(CEnemy* enemy){m_pEnemy = enemy;}
	void SetBoss(CBoss*Boss) { m_pBoss = Boss; }


	void Init(int size);
	void UpDate(const char &c, list<CEnemy*>&listActive1);
	void Draw(HANDLE hand);
	list<CBullet*>GetlistActive() {return listActive;}


	CBulletManager();
	~CBulletManager();
};
