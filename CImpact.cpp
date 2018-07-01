#include "stdafx.h"
#include "CImpact.h"
#include"Bullet.h"
#include"Cmap.h"
#include"Player.h"
#include "Enemy.h"
#include"CEnemyManager.h"
#include "BulletManager.h"
#include "Boss.h"
#include"Props.h"
#include"PropsManager.h"

bool CImpact::AabbMove( list<CEnemy*>&listActive1, list<CBullet*>&listActive2)
{
	int i = 0;
	for (list<CBullet*>::iterator itBullet = listActive2.begin();
		itBullet != listActive2.end(); itBullet++)
	{
		for (list<CEnemy*>::iterator itEnemy = listActive1.begin();
			itEnemy != listActive1.end(); itEnemy++)  
		{
			if ((*itBullet)->AttributeOj == 1)
			{
				//玩家打敌人
				if(AABB(*itBullet, *itEnemy))
				{
					if (Exact((*itEnemy)->vec, *itEnemy, itBullet))
					{
						m_pPlayer->AttributeOj++;
						if (m_pPlayer->AttributeOj == 1)
							m_pBoss->BossDead = true;//激活boss
						(*itEnemy)->bDead = true;
						(*itBullet)->bDead = true;

					}
				}
			}
		}
		//玩家打boss
		if ((*itBullet)->AttributeOj == 1)
		{
			if (AABB(*itBullet, m_pBoss))
			{
				if (Exact(m_pBoss->vec, m_pBoss, itBullet))
				{
					if (m_pBoss->BossDead)
						m_pBoss->AttributeOj++;
					if (m_pBoss->AttributeOj == 1)//boss被打三次后死亡
					{
						//m_pBoss->BossDead = false;//boss死亡
						m_pBoss->bDead = true;//boss颜色变红
						//m_pPlayer->AttributeOj = 0;
					}


					if (m_pBoss->AttributeOj == 2)//boss被打三次后死亡
					{
						m_pBoss->BossDead = false;//boss死亡
						m_pBoss->bDead = false;//boss颜色变绿
						m_pPlayer->AttributeOj = 0;
						m_pBoss->AttributeOj = 0;
					}
					(*itBullet)->bDead = true;
				}
			}
		}
		//敌人打玩家
		if ((*itBullet)->AttributeOj == 2)
		{
			if (!((*itBullet)->pos.X > (m_pPlayer->GetPos().X + (short)(m_pPlayer)->GetPlayerMaxCols()) ||
				(*itBullet)->pos.X < (m_pPlayer)->GetPos().X-1 ||
				(*itBullet)->pos.Y >((m_pPlayer)->GetPos().Y + (short)(m_pPlayer)->rows) ||
				(*itBullet)->pos.Y < (m_pPlayer)->GetPos().Y))
			{
				if (Exact(m_pPlayer->GetEnemyVec(), m_pPlayer, itBullet))
				{
					m_pPlayer->bDead = true;
					(*itBullet)->bDead = true;
				}
			}
		}
		//boss打玩家
		if ((*itBullet)->AttributeOj == 3)
		{
			if (!((*itBullet)->pos.X > (m_pPlayer->GetPos().X + (short)(m_pPlayer)->GetPlayerMaxCols()) ||
				(*itBullet)->pos.X < (m_pPlayer)->GetPos().X - 1 ||
				(*itBullet)->pos.Y >((m_pPlayer)->GetPos().Y + (short)(m_pPlayer)->rows) ||
				(*itBullet)->pos.Y < (m_pPlayer)->GetPos().Y))
			{
				if (Exact(m_pPlayer->GetEnemyVec(), m_pPlayer, itBullet))
				{
					m_pPlayer->bDead = true;
					(*itBullet)->bDead = true;
				}
			}
		}
	}
	return false;
}

CImpact::CImpact()
{
}


CImpact::~CImpact()
{
}
