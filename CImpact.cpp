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
				//��Ҵ����
				if(AABB(*itBullet, *itEnemy))
				{
					if (Exact((*itEnemy)->vec, *itEnemy, itBullet))
					{
						m_pPlayer->AttributeOj++;
						if (m_pPlayer->AttributeOj == 1)
							m_pBoss->BossDead = true;//����boss
						(*itEnemy)->bDead = true;
						(*itBullet)->bDead = true;

					}
				}
			}
		}
		//��Ҵ�boss
		if ((*itBullet)->AttributeOj == 1)
		{
			if (AABB(*itBullet, m_pBoss))
			{
				if (Exact(m_pBoss->vec, m_pBoss, itBullet))
				{
					if (m_pBoss->BossDead)
						m_pBoss->AttributeOj++;
					if (m_pBoss->AttributeOj == 1)//boss�������κ�����
					{
						//m_pBoss->BossDead = false;//boss����
						m_pBoss->bDead = true;//boss��ɫ���
						//m_pPlayer->AttributeOj = 0;
					}


					if (m_pBoss->AttributeOj == 2)//boss�������κ�����
					{
						m_pBoss->BossDead = false;//boss����
						m_pBoss->bDead = false;//boss��ɫ����
						m_pPlayer->AttributeOj = 0;
						m_pBoss->AttributeOj = 0;
					}
					(*itBullet)->bDead = true;
				}
			}
		}
		//���˴����
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
		//boss�����
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
