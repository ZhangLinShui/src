#pragma once
#include"BulletManager.h"
class Cmap;
class CPlayer;
class CBoss;
class CBullet 
{
public:
	bool bDead ;
	COORD pos;
	int AttributeOj;///<区分敌人和玩家的子弹
	Cmap *m_pMap;
	CPlayer*m_Pplayer;
	CEnemy*m_pEnemy;
	CBoss*m_pBoss;
public:
	void Draw(WORD *color);
	void Update();
	void Init();
	void SetPmap(Cmap*map) { m_pMap = map; }
	void SetPplayer(CPlayer*player) { m_Pplayer = player; }
	void setEnemy(CEnemy*m_pEnemy) { this->m_pEnemy = m_pEnemy; }
	void SetBoss(CBoss*Boss) { m_pBoss = Boss; }


	CBullet();
	~CBullet();
};

