#pragma once
#include "Singleton.h"
#include "Enemy.h"

/**
  *����һ��boss��

  * @param len1 ���һ�е��ַ����� Ҳ����ÿ��Ҫ�������ӵ���
  * @param len2 �ӵ���ʼλ��
  * @param BossDead ��ʾboss�Ƿ�����
  * @param flag ����boss�������ƶ�
  */		   
class CBoss:public CEnemy
{
public:
	bool BossDead;///<����boss�����ͼ���
	bool flag;///<����boss�ƶ�
	int len1;///<���һ�е��ַ����� Ҳ����ÿ��Ҫ�������ӵ���
	int len2;///<�ӵ���ʼλ��
	int AttributeOj;
public:
	/**
	  *����boss���ƶ� 
	*/
	void Update();
	/**
	  *��ʼ��boss������ ������bossͼ���ļ� ��ȥͼ�ε�������� \n
	  *���ƴ�ź�ȥ������Ҫ���ַ� ��س��� �ո����
	*/
	void Init();
	CBoss();
	~CBoss();
};

