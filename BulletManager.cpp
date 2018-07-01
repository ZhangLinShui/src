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
	vecEnemy.reserve(Size);//<����size���ռ��vecEnemy��̨���˶��������

	for (int i = 0; i < Size; ++i)
	{
		CBullet*bullet = new CBullet();///<��ÿ���������ռ� �������޲ι��캯��
		vecEnemy.push_back(bullet);///<�Ѵ����õĶ���ѹ���̨���˶�������� vecEnemy	
	}
	//�Ѷ���ؿռ�ȫ��ת�Ƶ����������У��ȴ���������
	for (vector<CBullet*>::iterator it = vecEnemy.begin(); it != vecEnemy.end(); it++)
		listDead.push_back(*it);
}

void CBulletManager::UpDate(const char &c, list<CEnemy*>&listActive1)
{
	if (c == 1)///<������ӵ�
	{
		if (!listDead.empty())///<��������ز�Ϊ��
		{
			//������������ĵ�һ������ѹ�뼤������ص�ĩβ
			listActive.splice(listActive.end(), listDead, listDead.begin());
			//listActive.push_front(*listDead.end());
			CBullet*bullet = listActive.back();
			//��ʼ�����˵�����
			bullet->SetPmap(m_pMap);
			bullet->SetPplayer(m_Pplayer);
			bullet->AttributeOj = 1;
			bullet->Init();///<��ʼ���ӵ�������
		}
	}
	///<�������м���ĵ��˵��ӵ�
	static DWORD preTime1 = GetTickCount();///<��ȡϵͳ��ǰʱ��
	DWORD curTime1 = GetTickCount();
	if ((curTime1 - preTime1)*0.001 > 0.2)///<�����ǰʱ�����һ�����е�ʱ���Ϊ2��
	{
		//���м���ĵ��˶������ӵ�
		for (list<CEnemy*>::iterator it = listActive1.begin();
			it != listActive1.end(); it++)
		{
			if (!listDead.empty())///<��������ز�Ϊ��
			{
				//������������ĵ�һ������ѹ�뼤������ص�ĩβ
				listActive.splice(listActive.end(), listDead, listDead.begin());
				//listActive.push_back(*listDead.end());
				CBullet*bullet = listActive.back();
				//��ʼ�����˵�����
				bullet->SetPmap(m_pMap);
				bullet->SetPplayer(m_Pplayer);
				bullet->setEnemy(*it);
				bullet->AttributeOj = 2;
				bullet->Init();///<��ʼ���ӵ�������	
			}
		}
		
		if (m_pBoss->BossDead)
			for (int i = 0; i < m_pBoss->vec[m_pBoss->rows - 1].length(); ++i)
			{
				if (m_pBoss->vec[m_pBoss->rows - 1].c_str()[i] == ' ')
					continue;
				//������������ĵ�һ������ѹ�뼤������ص�ĩβ
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

	//���������������µ�������
	for (list<CBullet*>::iterator it = listActive.begin(); it != listActive.end(); it++)
	{
		(*it)->Update();
	}

	//���������������ӵ�
	for (list<CBullet*>::iterator it = listActive.begin(); it != listActive.end(); )
	{
		if ((*it)->bDead && !listActive.empty())
		{
			//�Ѽ����������������������ĵ���ѹ����������صĵ�һ��λ��
			//listDead.splice(listDead.begin(), listActive, it);

			listDead.push_back(*it);
			(*it)->bDead = false;
			it = listActive.erase(it);

			///<��������bool����
			//break;///<��������Ϊsplice�������ƻ�����
		}
		else
			it++;  
	}
}

void CBulletManager::Draw(HANDLE hand)
{
	WORD color1[2] = { { FOREGROUND_RED | FOREGROUND_INTENSITY } ,{ FOREGROUND_RED | FOREGROUND_INTENSITY } };
	WORD color2[2] = { { FOREGROUND_BLUE | FOREGROUND_INTENSITY } ,{ FOREGROUND_BLUE | FOREGROUND_INTENSITY } };

	//���������ӵ�
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
