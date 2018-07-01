#include "stdafx.h"
#include "Cmap.h"


void Cmap::Draw(HANDLE hand)
{

	int i = 0;
	DWORD wr;
	COORD Pos;
	COORD Pos1;
	for (vector<string>::iterator it = vec.begin(); it != vec.end(); i++)
	{
		
		//WORD color[2] = { FOREGROUND_RED/* | FOREGROUND_BLUE*/ | FOREGROUND_GREEN | FOREGROUND_INTENSITY };
		WORD color[2] = { { FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY } ,{ FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY } };
		Pos = { pos.X ,pos.Y + (short)i };
		WriteConsoleOutputCharacterA(hand, vec[i].c_str(), strlen(vec[i].c_str()) , Pos, &wr);
		WriteConsoleOutputAttribute(hand, color, 2, Pos, &wr);
	

		//color[1] = { FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY };
		Pos1 = { pos.X,pos.Y  +1-rows+ (short)i };
		WriteConsoleOutputCharacterA(hand, vec[i].c_str(), strlen(vec[i].c_str()) , Pos1, &wr);
		WriteConsoleOutputAttribute(hand, color, 2, Pos1, &wr);
		it++;
	}
	

}

Cmap::Cmap()
{
	pos = { 0,0 };
	/*int fhandle = _open("../bin/res/map.txt", _O_RDONLY);///<只读模式 创建一个文件指针fhandle
	int len = _filelength(fhandle);///<获取整个文件的总大小 也就是总督额字节数
	buf = new char[len];
	FILE *fp;
	fopen_s(&fp, "../bin/res/map.txt", "r");*/

	
	 
	// fseek(fp, 0, 0);///<回到文件的起始位置
	//int mm = 0;///<代表文件总行数
	////计算文件的总行数
	//while (true)
	//{
	//	char *p = fgets(buf, len, fp);
	//	if (!p)
	//		break;
	//	mm++;
	//}
	//rows = mm;
	//fseek(fp, 0, 0);
	//fclose(fp);
	//fopen_s(&fp, "../bin/res/map.txt", "r");
	//buf[0] = '\0';
	//fread(buf, 1, len, fp);
	//buf[len] = '\0';
	 FILE *file;
	 fopen_s(&file, "../bin/res/map.txt", "r");
	 char buf[256];
	while (true)
	{
		char *p = fgets(buf, 256, file);
		if (!p)
			break;
		rows++;
		for (int i = 0; i < strlen(buf); ++i)
		{
			if (buf[i] == '\r' || buf[i] == '\n')
			{
				buf[i] = '\0';
				break;
			}
		}
		vec.push_back(buf);
	}
	cols = strlen(vec[0].c_str());
	fclose(file);
	GetRows();
	GetCols();
}

void Cmap::Move()
{
	if (pos.Y <= rows)
		pos.Y++;
	else
		pos.Y = 1;
}


Cmap::~Cmap()
{
}
