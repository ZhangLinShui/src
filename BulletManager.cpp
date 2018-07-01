#include "stdafx.h"
#include "BulletManager.h"
#include"Player.h"
#include "Bullet.h"
#include "Cmap.h"
#include "Enemy.h"
#include "Boss.h"



void CBulletManager::Init(int size)
{
	Size = size;
	vecEnemy.reserve(Size);//<分配size个空间给vecEnemy后台敌人对象池链表

	for (int i = 0; i < Size; ++i)
	{
		CBullet*bullet = new CBullet();///<给每个对象分配空间 并调用无参构造函数
		vecEnemy.push_back(bullet);///<把创建好的对象压入后台敌人对象池链表 vecEnemy	
	}
	//把对象池空间全部转移到死亡链表中，等待产生敌人
	for (vector<CBullet*>::iterator it = vecEnemy.begin(); it != vecEnemy.end(); it++)
		listDead.push_back(*it);
}

void CBulletManager::UpDate(const char &c, list<CEnemy*>&listActive1)
{
	if (c == 1)///<人物的子弹
	{
		if (!listDead.empty())///<死亡链表池不为空
		{
			//把死亡池链表的第一个敌人压入激活链表池的末尾
			listActive.splice(listActive.end(), listDead, listDead.begin());
			//listActive.push_front(*listDead.end());
			CBullet*bullet = listActive.back();
			//初始化敌人的数据
			bullet->SetPmap(m_pMap);
			bullet->SetPplayer(m_Pplayer);
			bullet->AttributeOj = 1;
			bullet->Init();///<初始化子弹的坐标
		}
	}
	///<产生所有激活的敌人的子弹
	static DWORD preTime1 = GetTickCount();///<获取系统当前时间
	DWORD curTime1 = GetTickCount();
	if ((curTime1 - preTime1)*0.001 > 0.2)///<如果当前时间和上一次运行的时间差为2秒
	{
		//所有激活的敌人都产生子弹
		for (list<CEnemy*>::iterator it = listActive1.begin();
			it != listActive1.end(); it++)
		{
			if (!listDead.empty())///<死亡链表池不为空
			{
				//把死亡池链表的第一个敌人压入激活链表池的末尾
				listActive.splice(listActive.end(), listDead, listDead.begin());
				//listActive.push_back(*listDead.end());
				CBullet*bullet = listActive.back();
				//初始化敌人的数据
				bullet->SetPmap(m_pMap);
				bullet->SetPplayer(m_Pplayer);
				bullet->setEnemy(*it);
				bullet->AttributeOj = 2;
				bullet->Init();///<初始化子弹的坐标	
			}
		}
		
		if (m_pBoss->BossDead)
			for (int i = 0; i < m_pBoss->vec[m_pBoss->rows - 1].length(); ++i)
			{
				if (m_pBoss->vec[m_pBoss->rows - 1].c_str()[i] == ' ')
					continue;
				//把死亡池链表的第一个敌人压入激活链表池的末尾
				if (!listDead.empty())
					listActive.splice(listActive.end(), listDead, listDead.begin());
				CBullet*bullet = listActive.back();
				bullet->SetPmap(m_pMap);
				bullet->SetPplayer(m_Pplayer);
				bullet->AttributeOj = 3;
				bullet->pos = { m_pBoss->pos.X + (short)i, m_pBoss->pos.Y + (short)m_pBoss->rows };
				if (m_pBoss->vec[m_pBoss->rows - 1].c_str()[i] < 0)
					++i;
				
			}
		preTime1 = curTime1;
	}

	//遍历激活链表，更新敌人数据
	for (list<CBullet*>::iterator it = listActive.begin(); it != listActive.end(); it++)
	{
		(*it)->Update();
	}

	//回收所有死亡的子弹
	for (list<CBullet*>::iterator it = listActive.begin(); it != listActive.end(); )
	{
		if ((*it)->bDead && !listActive.empty())
		{
			//把激活池链表的满足死亡条件的敌人压入死亡链表池的第一个位置
			//listDead.splice(listDead.begin(), listActive, it);

			listDead.push_back(*it);
			(*it)->bDead = false;
			it = listActive.erase(it);

			///<死亡条件bool开关
			//break;///<跳出是因为splice函数会破坏链表
		}
		else
			it++;  
	}
}

void CBulletManager::Draw(HANDLE hand)
{
	WORD color1[2] = { { FOREGROUND_RED | FOREGROUND_INTENSITY } ,{ FOREGROUND_RED | FOREGROUND_INTENSITY } };
	WORD color2[2] = { { FOREGROUND_BLUE | FOREGROUND_INTENSITY } ,{ FOREGROUND_BLUE | FOREGROUND_INTENSITY } };

	//绘制所有子弹
	for (list<CBullet*>::iterator it = listActive.begin(); it != listActive.end(); it++)
	{
		if((*it)->AttributeOj==1)
		(*it)->Draw(color1);
		if ((*it)->AttributeOj == 2)
		(*it)->Draw(color2);
		if ((*it)->AttributeOj == 3)
			(*it)->Draw(color2);
	}
}







CBulletManager::CBulletManager()
{
}

CBulletManager::~CBulletManager()
{

	for (vector<CBullet*>::iterator it = vecEnemy.begin(); it != vecEnemy.end(); it++)
		delete (*it);
}
