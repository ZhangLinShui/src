#include "stdafx.h"
#include "PropsManager.h"
#include "Props.h"


void CPropsManager::Draw()
{
	//绘制所有敌人
	for (list<CProps*>::iterator it = listActive.begin(); it != listActive.end(); it++)
	{
		(*it)->Draw();
	}
}

void CPropsManager::Init(int size)
{
	vecEnemy.reserve(size);//<分配size个空间给vecEnemy后台敌人对象池链表
	for (int i = 0; i < size; ++i)
	{
		CProps*pEnemy = new CProps();///<给每个对象分配空间 并调用无参构造函数
		vecEnemy.push_back(pEnemy);///<把创建好的对象压入后台敌人对象池链表 vecEnemy
	}

	//把对象池空间全部转移到死亡链表中，等待产生敌人
	for (vector<CProps*>::iterator it = vecEnemy.begin(); it != vecEnemy.end(); it++)
	{
		listDead.push_back(*it);
	}

	FILE*file;
	fopen_s(&file, "../bin/res/道具管理.txt", "r");
	while (true)
	{
		char buf[256];
		char *p = fgets(buf, 256, file);
		if (!p)break;
		//去掉换行符
		int len = 0;
		for (int i = 0; i < strlen(buf); ++i)
		{
			if (buf[i] == '\r' || buf[i] == '\n')
			{
				buf[i] = '\0';
				break;
			}
		}
		rows++;
		VecString.push_back(buf);
	}
}

void CPropsManager::Update(CBulletManager * BulletManager)
{
	//产生道具
	thing = rand() % rows;
	static DWORD preTime = GetTickCount();///<获取系统当前时间
	DWORD curTime = GetTickCount();
	if ((curTime - preTime)*0.001 > 7)///<如果当前时间和上一次运行的时间差为2秒
	{
		if (!listDead.empty())///<死亡链表池不为空
		{
			//把死亡池链表的第一个敌人压入激活链表池的末尾
			listActive.splice(listActive.end(), listDead, listDead.begin());
			CProps*pEnemy = listActive.back();
			//初始化敌人的数据
			pEnemy->SetPmap(m_pMap);
			pEnemy->SetPplayer(m_Pplayer);
			//BulletManager->SetEnemy(pEnemy);
			pEnemy->Init(VecString[thing].c_str());///<初始化敌人的坐标

		}
		preTime = curTime;
	}

	//遍历激活链表，更新敌人数据
	for (list<CProps*>::iterator it = listActive.begin(); it != listActive.end(); it++)
	{
		(*it)->Update();
	}


	//将死亡私人压入死亡链表
	int flag = 0;
	for (list<CProps*>::iterator it = listActive.begin(); it != listActive.end(); /*it++*/)
	{
		if (flag == 1)flag = 0;
		if ((*it)->bDead && !listActive.empty())
		{
			listDead.push_back(*it);
			(*it)->bDead = false;
			it = listActive.erase(it);
			flag = 1;
		}
		if (flag == 0)it++;
	}
}

CPropsManager::CPropsManager()
{
}


CPropsManager::~CPropsManager()
{
	for (vector<CProps*>::iterator it = vecEnemy.begin(); it != vecEnemy.end(); it++)
	{
		delete (*it);
	}
}
