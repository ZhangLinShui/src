#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include"Cmap.h"
#include "SwapBuffer.h"
void CPlayer::Draw()
{

	WORD color1[2] = { { FOREGROUND_RED | FOREGROUND_INTENSITY } ,{ FOREGROUND_RED | FOREGROUND_INTENSITY } };

	WORD color2[2] = { { FOREGROUND_GREEN | FOREGROUND_INTENSITY } ,{ FOREGROUND_GREEN | FOREGROUND_INTENSITY } };
		if (bDead)
			CSwapBuffer::GetsinglenPtr()->ShowObject(vec, pos, color1);
		else
			CSwapBuffer::GetsinglenPtr()->ShowObject(vec, pos, color2);

}

CPlayer::CPlayer(COORD Pos)
{
	AttributeOj = 0;//杀敌个数
	bDead = false;
	pos = Pos;
	cols = 0;
	MaxCols = 0;
	DoubleByte = 0;
	FILE *file;
	fopen_s(&file, "../bin/res/player1.txt", "r");
	int i = 0;
	while (true)
	{
		char buf[256];
		char *p = fgets(buf, 256, file);
		if (!p)
			break;
		int len = 0;
		int Double = 0;

		for (int i = 0; i < strlen(buf); ++i)
		{
			if (buf[i] == '\r' || buf[i] == '\n')
			{
				buf[i] = '\0';
				break;
			}
		}

		len = strlen(buf);
		MaxCols = len > MaxCols ? len : MaxCols;
		DoubleByte = Double > DoubleByte ? Double : DoubleByte;
		rows++;
		vec.push_back(buf);
	}
	fclose(file);
}

int CPlayer::Move()
{
	if (_kbhit())
	{
		int key = _getch();
		switch (key)
		{
		case 72://w  72
			if (!(pos.Y==0))
			pos.Y--;
			break;
		case 80://s  80
			if (!(pos.Y == (50-rows)))
			pos.Y++;
			break;
		case 75://a		75 	
			if (!(pos.X == 0))
				pos.X-=2;
			break;
		case 77: //d  77
			if (!(pos.X > (m_pMap->GetCols() - (short)MaxCols-2)))
				pos.X+=2;
			break;
		case ' ':
			return 1;
			break;
		}
	}
}

bool CPlayer::isMove()
{
	int PlayerWidth = MaxCols / 2;
	int PlayerHight = rows;
	int MapWight = m_pMap->GetCols() / 2;
	//int MapHigth = m_pMap->GetRows();///<地图的总行数
	int MapHigth = 50;
	if ((pos.X+1 + PlayerWidth) != MapWight /*|| pos.X-1 != 0*/)
		return true;
	return false;
}


CPlayer::~CPlayer()
{
}
