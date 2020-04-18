#pragma once
#include"Bullet.h"
class CEnemy;
class Cmap;
class CPlayer 
{
	
	short cols;///<Ĭ������
	int MaxCols;///<����ַ�������
	int DoubleByte;
	COORD pos;///<����λ��
	vector<string> vec;///<�����ı�����
	CEnemy *m_pEnemy;
	Cmap*m_pMap;
	//CBullet*m_pBullet;
public:
	int AttributeOj;//ɱ����
	bool bDead;
	short rows;///<�������
	void Draw();
	CPlayer(COORD Pos);
	int  Move();
	bool isMove();
	void SetEnemy(CEnemy *m_pEnemy){this->m_pEnemy = m_pEnemy;}
	void SetMap(Cmap*map) { this->m_pMap = map; }
	int GetPlayerMaxCols() { return MaxCols; }
	COORD GetPos() { return pos; }
	int GetRows() {return rows;}

	vector<string> GetEnemyVec() { return vec; }
	COORD GetBulletPlayer() 
	{ 
		COORD Pos; 
		Pos.X = MaxCols / 2 + pos.X * 2 - 1;
		Pos.Y = pos.Y;
		return Pos;
	}
	~CPlayer();
	//嘿嘿 本地更改 测试提交
};

