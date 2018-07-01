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

	//�������е���
	for (list<CEnemy*>::iterator it = listActive.begin(); it != listActive.end(); it++)
	{
		(*it)->Draw();
	}
}

void CEnemyManager::Init(int size)
{
	Size = size;
	vecEnemy.reserve(Size);//<����size���ռ��vecEnemy��̨���˶��������
	for (int i = 0; i < Size; ++i)
	{
		CEnemy*pEnemy = new CEnemy();///<��ÿ���������ռ� �������޲ι��캯��
		vecEnemy.push_back(pEnemy);///<�Ѵ����õĶ���ѹ���̨���˶�������� vecEnemy
	}
	
	//�Ѷ���ؿռ�ȫ��ת�Ƶ����������У��ȴ���������
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
	//��������
	if (!m_pBoss->BossDead)//����boss����
	{
		static DWORD preTime = GetTickCount();///<��ȡϵͳ��ǰʱ��
		DWORD curTime = GetTickCount();
		if ((curTime - preTime)*0.001 > 2)///<�����ǰʱ�����һ�����е�ʱ���Ϊ2��
		{
			if (!listDead.empty())///<��������ز�Ϊ��
			{
				//������������ĵ�һ������ѹ�뼤������ص�ĩβ
				listActive.splice(listActive.end(), listDead, listDead.begin());
				CEnemy*pEnemy = listActive.back();
				//��ʼ�����˵�����
				pEnemy->SetPmap(m_pMap);
				pEnemy->SetPplayer(m_Pplayer);
				BulletManager->SetEnemy(pEnemy);
				pEnemy->Init();///<��ʼ�����˵�����

			}
			preTime = curTime;
		}
	}
	else//�������boss
	{
		if (isBoss) //ֻ����һ��boss
		{
			m_pBoss->Init();
			isBoss = false;
		}
	}
	//���������������µ�������
	for (list<CEnemy*>::iterator it = listActive.begin(); it != listActive.end(); it++)
	{
		(*it)->Update();
	}
	if (m_pBoss->BossDead)
		m_pBoss->Update();
		int aaaaa = 3;//��ֹ��һ��ע�͵���ִ����һ��
	Death();
}

void CEnemyManager::Death()
{
	//������˽��ѹ����������
	int flag = 0;
	for (list<CEnemy*>::iterator it = listActive.begin(); it != listActive.end(); /*it++*/)
	{
		if (flag == 1)flag = 0;
		if ((*it)->bDead && !listActive.empty())
		{
			//�Ѽ����������������������ĵ���ѹ����������صĵ�һ��λ��
			/*listDead.splice(listDead.begin(), listActive, it);
			(*it)->bDead = false;///<��������bool����
			break;///<��������Ϊsplice�������ƻ�����*/

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
