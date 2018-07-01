#pragma once
#include"Bullet.h"
class CEnemy;
class Cmap;
class CPlayer 
{
	
	short cols;///<默认列数
	int MaxCols;///<最大字符个个数
	int DoubleByte;
	COORD pos;///<人物位置
	vector<string> vec;///<人物文本数据
	CEnemy *m_pEnemy;
	Cmap*m_pMap;
	//CBullet*m_pBullet;
public:
	int AttributeOj;//杀敌数
	bool bDead;
	short rows;///<最大行数
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
};

