#include "stdafx.h"
#include "Boss.h"
#include "SwapBuffer.h"
#include "Cmap.h"
void CBoss::Update()
{
	DWORD curTime = GetTickCount();
	if ((curTime - preTime1) > 50)
	{
		if (pos.X >= m_pMap->GetCols() - MaxCols)
			flag = false;
		if (pos.X <= 0)
			flag = true;

		if (flag)
			pos.X++;
		else
			pos.X--;
		preTime1 = curTime;
	}
}

CBoss::CBoss()
{
	this->bDead = false;
	this->BossDead = false;
	
}
void CBoss::Init()
{
	FILE *file;
	fopen_s(&file, "../bin/res/boss2.txt", "r");
	MaxCols = 0;
	DoubleByte = 0;
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
	pos = { (short)(92 / 2 - MaxCols / 2),0 };

	len1 = 0;
	len2 = 0;
	for (int i = 0; i < vec[rows - 1].length(); ++i)
	{
		if (vec[rows - 1].c_str()[i] == ' ')
			continue;
		len2++;
		if (vec[rows - 1].c_str()[i] < 0)
			++i;
		len1++;
	}
}

CBoss::~CBoss()
{
}


