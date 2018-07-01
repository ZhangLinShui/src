#pragma once

class Cmap;
class CPlayer;
class CProps
{
public:
	bool bDead;

	COORD pos;
	vector<string> vec;
	short rows;
	int MaxCols;///<最大元素个数
	int DoubleByte;
	int HP;
	Cmap *m_pMap;
	CPlayer*m_Pplayer;
	DWORD preTime1;
public:
	void Update();
	void SetPmap(Cmap*map) { m_pMap = map; }
	void SetPplayer(CPlayer*player) { m_Pplayer = player; }
	void Draw();
	int GetEnemyMaxCols() { return MaxCols; }
	COORD GetPos() { return pos; }
	COORD SetPos(COORD Pos)
	{
		pos.X = Pos.X;
		pos.Y = Pos.Y;
	}
	COORD GetBulletEnemy()
	{
		COORD Pos;
		Pos.X = MaxCols / 2 + pos.X * 2 - 1;
		Pos.Y = pos.Y;
		return Pos;
	}
	vector<string> GetEnemyVec() { return vec; }
	void Init(const char *name);
public:

	CProps();
	~CProps();
};

