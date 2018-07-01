#include "stdafx.h"
#include "PropsManager.h"
#include "Props.h"


void CPropsManager::Draw()
{
	//�������е���
	for (list<CProps*>::iterator it = listActive.begin(); it != listActive.end(); it++)
	{
		(*it)->Draw();
	}
}

void CPropsManager::Init(int size)
{
	vecEnemy.reserve(size);//<����size���ռ��vecEnemy��̨���˶��������
	for (int i = 0; i < size; ++i)
	{
		CProps*pEnemy = new CProps();///<��ÿ���������ռ� �������޲ι��캯��
		vecEnemy.push_back(pEnemy);///<�Ѵ����õĶ���ѹ���̨���˶�������� vecEnemy
	}

	//�Ѷ���ؿռ�ȫ��ת�Ƶ����������У��ȴ���������
	for (vector<CProps*>::iterator it = vecEnemy.begin(); it != vecEnemy.end(); it++)
	{
		listDead.push_back(*it);
	}

	FILE*file;
	fopen_s(&file, "../bin/res/���߹���.txt", "r");
	while (true)
	{
		char buf[256];
		char *p = fgets(buf, 256, file);
		if (!p)break;
		//ȥ�����з�
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
	//��������
	thing = rand() % rows;
	static DWORD preTime = GetTickCount();///<��ȡϵͳ��ǰʱ��
	DWORD curTime = GetTickCount();
	if ((curTime - preTime)*0.001 > 7)///<�����ǰʱ�����һ�����е�ʱ���Ϊ2��
	{
		if (!listDead.empty())///<��������ز�Ϊ��
		{
			//������������ĵ�һ������ѹ�뼤������ص�ĩβ
			listActive.splice(listActive.end(), listDead, listDead.begin());
			CProps*pEnemy = listActive.back();
			//��ʼ�����˵�����
			pEnemy->SetPmap(m_pMap);
			pEnemy->SetPplayer(m_Pplayer);
			//BulletManager->SetEnemy(pEnemy);
			pEnemy->Init(VecString[thing].c_str());///<��ʼ�����˵�����

		}
		preTime = curTime;
	}

	//���������������µ�������
	for (list<CProps*>::iterator it = listActive.begin(); it != listActive.end(); it++)
	{
		(*it)->Update();
	}


	//������˽��ѹ����������
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
