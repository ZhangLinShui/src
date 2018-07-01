#include "stdafx.h"
#include"CEnemyManager.h"
#include "Enemy.h"
#include "Cmap.h"
#include "Player.h"
#include "CImpact.h"

#include "Boss.h"
//#include "BulletManager.h"

void CEnemyManager::Draw(HANDLE hand)
{
	if (m_pBoss->BossDead)
	{
		m_pBoss->Draw();
	}

	//绘制所有敌人
	for (list<CEnemy*>::iterator it = listActive.begin(); it != listActive.end(); it++)
	{
		(*it)->Draw();
	}
}

void CEnemyManager::Init(int size)
{
	Size = size;
	vecEnemy.reserve(Size);//<分配size个空间给vecEnemy后台敌人对象池链表
	for (int i = 0; i < Size; ++i)
	{
		CEnemy*pEnemy = new CEnemy();///<给每个对象分配空间 并调用无参构造函数
		vecEnemy.push_back(pEnemy);///<把创建好的对象压入后台敌人对象池链表 vecEnemy
	}
	
	//把对象池空间全部转移到死亡链表中，等待产生敌人
	for (vector<CEnemy*>::iterator it = vecEnemy.begin(); it != vecEnemy.end(); it++)
	{
		listDead.push_back(*it);
	}


	m_pBoss = new CBoss();
	m_pBoss->SetPmap(m_pMap);
	m_pImpact->SetBoss(m_pBoss);
    isBoss = true;
	m_pBulletManager->SetBoss(m_pBoss);
	
}

void CEnemyManager::Update(CBulletManager*BulletManager)
{	
	//产生敌人
	if (!m_pBoss->BossDead)//控制boss出现
	{
		static DWORD preTime = GetTickCount();///<获取系统当前时间
		DWORD curTime = GetTickCount();
		if ((curTime - preTime)*0.001 > 2)///<如果当前时间和上一次运行的时间差为2秒
		{
			if (!listDead.empty())///<死亡链表池不为空
			{
				//把死亡池链表的第一个敌人压入激活链表池的末尾
				listActive.splice(listActive.end(), listDead, listDead.begin());
				CEnemy*pEnemy = listActive.back();
				//初始化敌人的数据
				pEnemy->SetPmap(m_pMap);
				pEnemy->SetPplayer(m_Pplayer);
				BulletManager->SetEnemy(pEnemy);
				pEnemy->Init();///<初始化敌人的坐标

			}
			preTime = curTime;
		}
	}
	else//否则产生boss
	{
		if (isBoss) //只产生一次boss
		{
			m_pBoss->Init();
			isBoss = false;
		}
	}
	//遍历激活链表，更新敌人数据
	for (list<CEnemy*>::iterator it = listActive.begin(); it != listActive.end(); it++)
	{
		(*it)->Update();
	}
	if (m_pBoss->BossDead)
		m_pBoss->Update();
		int aaaaa = 3;//防止上一行注释掉后不执行下一句
	Death();
}

void CEnemyManager::Death()
{
	//将死亡私人压入死亡链表
	int flag = 0;
	for (list<CEnemy*>::iterator it = listActive.begin(); it != listActive.end(); /*it++*/)
	{
		if (flag == 1)flag = 0;
		if ((*it)->bDead && !listActive.empty())
		{
			//把激活池链表的满足死亡条件的敌人压入死亡链表池的第一个位置
			/*listDead.splice(listDead.begin(), listActive, it);
			(*it)->bDead = false;///<死亡条件bool开关
			break;///<跳出是因为splice函数会破坏链表*/

			listDead.push_back(*it);
			(*it)->bDead = false;
			it = listActive.erase(it);
			flag = 1;
		}
		if (flag == 0)it++;
	}
}


CEnemyManager::CEnemyManager()
{
}


CEnemyManager::~CEnemyManager()
{
	for (vector<CEnemy*>::iterator it = vecEnemy.begin(); it != vecEnemy.end(); it++)
		delete (*it);
	delete m_pBoss;
}
