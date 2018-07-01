#include "stdafx.h"
#include "Props.h"
#include "Enemy.h"
#include "Cmap.h"
#include "Player.h"
#include "SwapBuffer.h"

void CProps::Update()
{
	DWORD curTime = GetTickCount();
	if ((curTime - preTime1) > 400)
	{
		pos.Y++;
		if (pos.Y >  m_pMap->GetRows())
		{
			this->bDead = true;
		}
		preTime1 = curTime;
	}
}

void CProps::Draw()
{
	WORD color1[2] = { { FOREGROUND_RED | FOREGROUND_INTENSITY } ,{ FOREGROUND_RED | FOREGROUND_INTENSITY } };

	WORD color2[2] = { { FOREGROUND_GREEN | FOREGROUND_INTENSITY } ,{ FOREGROUND_GREEN | FOREGROUND_INTENSITY } };
	if (bDead)
		CSwapBuffer::GetsinglenPtr()->ShowObject(vec, pos, color1);
	else
		CSwapBuffer::GetsinglenPtr()->ShowObject(vec, pos, color2);
}

CProps::CProps()
{
	bDead = false;
}

void CProps::Init(const char *name)
{
	FILE *file;
	fopen_s(&file, name, "r");
	MaxCols = 0;
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
		MaxCols = len > MaxCols ? len : MaxCols;
		rows++;
		vec.push_back(buf);
	}
	fclose(file);

	pos.Y = 0;
	pos.X = (short)rand() % (m_pMap->GetCols() - MaxCols );
	preTime1 = GetTickCount();
}
CProps::~CProps()
{
}
