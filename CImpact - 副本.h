#pragma once
#include "Singleton.h"
class CPlayer;
class CEnemy;
class CBullet;
class Cmap;
class CBoss;
class CProps;

//class CBulletManager;
//class CEnemyManager;
//class CPropsManager;
class CImpact :public Singleton<CImpact>
{
	CPlayer * m_pPlayer;
	CEnemy*m_pEnemy;
	CBullet*m_pBullet;
	Cmap*m_pMap;
	CBoss*m_pBoss;
	CProps *m_pProps;
public:

	void SetPlayer(CPlayer*player) { m_pPlayer = player; }
	void SetEnemy(CEnemy*enemy) { m_pEnemy = enemy; }
	void SetBullet(CBullet*bullet) { m_pBullet = bullet; }
	void SetMap(Cmap*map){m_pMap = map;}
	void SetBoss(CBoss*Boss) { m_pBoss = Boss; }
	void SetProps(CProps*Props) {m_pProps = Props;}

public:
	bool AabbMove(list<CEnemy*>&listActive1, list<CBullet*>&listActive2);
	CImpact();
	~CImpact();
};

template<typename T>
bool Exact(vector<string>&vec, T*m_pBoss, list<CBullet*>::iterator &itBullet)
{
	short i = 0;//行数
	for (vector<string>::iterator it = vec.begin();
		it != vec.end(); it++)
	{
		for (short j = 0; j < (short)(*it).length(); ++j)
		{
			if ((*it)[j] == ' ')
				continue;
			if (((*itBullet)->pos.X == (short)(m_pBoss)->GetPos().X + j ||
				(*itBullet)->pos.X + 1 == (short)(m_pBoss)->GetPos().X + j) &&
				(*itBullet)->pos.Y == (m_pBoss)->GetPos().Y + i)
				return true;
		}
		i++;
	}
	return false;
}
template<typename T1,typename T2>
bool AABB(T1 *itBullet,T2*itEnemy)
{
	//玩家打敌人
	if (!((itBullet)->pos.X > ((itEnemy)->pos.X + (short)(itEnemy)->MaxCols) ||
		(itBullet)->pos.X < (itEnemy)->pos.X - 1 ||
		(itBullet)->pos.Y >((itEnemy)->pos.Y + (short)(itEnemy)->rows) ||
		(itBullet)->pos.Y < (itEnemy)->pos.Y))
		return true;
	return false;
}
