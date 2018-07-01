#include "stdafx.h"
#include "Bullet.h"
#include"Player.h"
#include"Cmap.h"
#include "Enemy.h"
#include "SwapBuffer.h"
#include "Boss.h"

void CBullet::Draw(WORD *color)
{
	CSwapBuffer::GetsinglenPtr()->ShowBullet(pos, color);
}

void CBullet::Update()
{
	if (AttributeOj == 1)
	{
		if (pos.Y >= 0)
		{
			pos.Y--;			
		}
		if (pos.Y <=-1)
		{
			this->bDead = true;
		}
	}
	if(AttributeOj ==2)
	{
		if (pos.Y <=/*65*/ m_pMap->GetRows())
		{
			pos.Y++;
		}
		if (pos.Y >/*65*/ m_pMap->GetRows())
		{
			this->bDead = true;
		}
	}
	if (AttributeOj == 3)
	{
		if (pos.Y <=/*65*/ m_pMap->GetRows())
		{
			pos.Y++;
		}
		if (pos.Y >/*65*/ m_pMap->GetRows())
		{
			this->bDead = true;
		}
	}
}



void CBullet::Init()
{

	if (AttributeOj == 1)//Íæ¼Ò
	{
		pos.X = m_Pplayer->GetPlayerMaxCols()/2  + m_Pplayer->GetPos().X  - 1;
		pos.Y = m_Pplayer->GetPos().Y;
	}
	if (AttributeOj == 2)//µÐÈË
	{
		pos.X = m_pEnemy->GetEnemyMaxCols()/2  + m_pEnemy->GetPos().X  - 1;
		pos.Y = m_pEnemy->GetPos().Y+m_pEnemy->rows;
	}
	if (AttributeOj == 3)//boss
	{
		pos.X = m_pBoss->GetEnemyMaxCols() / 2 + m_pEnemy->GetPos().X - 1;
		pos.Y = m_pBoss->GetPos().Y + m_pEnemy->rows;
	}

}

CBullet::CBullet()
{

}


CBullet::~CBullet()
{
}
