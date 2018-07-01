// zuoye_1_12.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SwapBuffer.h"
#include "Player.h"
#include "Cmap.h"
#include "CEnemyManager.h"
#include "BulletManager.h"
#include "CImpact.h"
#include "PropsManager.h"

Cmap *g_pMap;
CPlayer *g_pPlayer;
//游戏操作说明
void InitTitle()
{
	vector<string> vec;
	FILE *file;
	fopen_s(&file, "../bin/res/介绍1.txt", "r");
	while (true)
	{
		char buf[256];
		char *p = fgets(buf, 256, file);
		if (!p)
			break;
		int len = 0;
		for (int i = 0; i < strlen(buf); ++i)
		{
			if (buf[i] == '\r' || buf[i] == '\n')
			{
				buf[i] = '\0';
				break;
			}
		}
		len = strlen(buf);
		vec.push_back(buf);
	}
	fclose(file);
	WORD color2[2] = { { FOREGROUND_GREEN | FOREGROUND_INTENSITY } ,{ FOREGROUND_GREEN | FOREGROUND_INTENSITY } };
	COORD pos = { 0,0 };
 	CSwapBuffer::GetsinglenPtr()->ShowObject(vec, pos, color2);
	CSwapBuffer::GetsinglenPtr()->Draw();
 	int aa=_getch();     
}
int main()
{
	InitTitle();
	srand(GetTickCount());
	SetConsoleTitleA("飞机大战");
	COORD Pos;
	Pos = { 20,40 };
	g_pPlayer =new CPlayer(Pos);
	g_pMap = new Cmap;

	g_pPlayer->SetMap(g_pMap);

	//初始化碰撞类
	CImpact::GetsinglenPtr()->SetPlayer(g_pPlayer);
	CImpact::GetsinglenPtr()->SetMap(g_pMap);
	

	//初始化敌人管理类
	CEnemyManager::GetsinglenPtr()->SetPmap(g_pMap);
	CEnemyManager::GetsinglenPtr()->SetPplayer(g_pPlayer);
	CEnemyManager::GetsinglenPtr()->SetImpact(CImpact::GetsinglenPtr());
	
	

	//初始化玩家子弹管理类
	CBulletManager::GetsinglenPtr()->SetPmap(g_pMap);
	CBulletManager::GetsinglenPtr()->SetPplayer(g_pPlayer);
	CBulletManager::GetsinglenPtr()->Init(1000);///<创建1个内存池 里面是100个子弹类的对象
	
	CEnemyManager::GetsinglenPtr()->SetBulletManager(CBulletManager::GetsinglenPtr());
	CEnemyManager::GetsinglenPtr()->Init(100);///<创建1个内存池 里面是100个敌人类的对象

	//初始化道具管理类
	CPropsManager::GetsinglenPtr()->SetPmap(g_pMap);
	CPropsManager::GetsinglenPtr()->SetPplayer(g_pPlayer);
	CPropsManager::GetsinglenPtr()->Init(100);///<创建1个内存池 里面是100个道具类的对象


	while (true)
	{
		static DWORD preTime = GetTickCount();
		DWORD curTime = GetTickCount();
		if (curTime - preTime > 16)
		{
			preTime = curTime;

			g_pMap->Move();
			g_pMap->Draw(CSwapBuffer::GetsinglenPtr()->GetBufferHandle());

			int c=g_pPlayer->Move();
			g_pPlayer->Draw();
			
			CEnemyManager::GetsinglenPtr()->Update(CBulletManager::GetsinglenPtr());
			CEnemyManager::GetsinglenPtr()->Draw(CSwapBuffer::GetsinglenPtr()->GetBufferHandle());

			CBulletManager::GetsinglenPtr()->UpDate(c, CEnemyManager::GetsinglenPtr()->GetListActive());
			CBulletManager::GetsinglenPtr()->Draw(CSwapBuffer::GetsinglenPtr()->GetBufferHandle());

			if (CImpact::GetsinglenPtr()->AabbMove(CEnemyManager::GetsinglenPtr()->GetListActive(), CBulletManager::GetsinglenPtr()->GetlistActive()))
			{
				CEnemyManager::GetsinglenPtr()->Update(CBulletManager::GetsinglenPtr());
				CEnemyManager::GetsinglenPtr()->Draw(CSwapBuffer::GetsinglenPtr()->GetBufferHandle());			
			}

			CPropsManager::GetsinglenPtr()->Update(CBulletManager::GetsinglenPtr());
			CPropsManager::GetsinglenPtr()->Draw();


			CSwapBuffer::GetsinglenPtr()->Draw();
		}
		else
			Sleep(1);
	}
	delete g_pPlayer;
	delete g_pMap;
	
	delete CBulletManager::GetsinglenPtr();
	delete CEnemyManager::GetsinglenPtr();
	delete CSwapBuffer::GetsinglenPtr();
	delete CImpact::GetsinglenPtr();
	delete CPropsManager::GetsinglenPtr();
    return 0;
}

