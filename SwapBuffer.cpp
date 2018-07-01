#include "stdafx.h"
#include "SwapBuffer.h"


CSwapBuffer::CSwapBuffer()
{
	//system("mod con cols=100 lines=100");
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(hOutput, screenSize);
	SMALL_RECT rect = { 0,0,screenSize.X - 1,screenSize.Y - 1 };
	hOutBuf = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	SetConsoleScreenBufferSize(hOutBuf, screenSize);
	SetConsoleWindowInfo(hOutBuf, true, &rect);
	SetConsoleActiveScreenBuffer(hOutBuf);///<激活句柄



	/*HWND hwnd = FindWindowA(NULL, "飞机大战");
	WINDOWINFO info;
	GetWindowInfo(hwnd, &info);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int posX = (screenWidth - info.rcClient.right) / 2;
	int posY = (screenHeight - info.rcClient.bottom) / 2;
	MoveWindow(hwnd, posX, posY, info.rcClient.right, info.rcClient.bottom, true);*/


	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize = 1;
	SetConsoleCursorInfo(hOutBuf, &cci);
	SetConsoleCursorInfo(hOutput, &cci);
}


CSwapBuffer::~CSwapBuffer()
{
}

void CSwapBuffer::ShowObject(vector<string> vec, COORD pos, WORD *color)
{
	DWORD wr;
	COORD Pos;
	int i = 0;
	for (vector<string>::iterator it = vec.begin(); it != vec.end(); i++)
	{
		//for (short j = 0; j < it->length()-2; j+=2)
		/*{
		Pos = { pos.X*2,pos.Y + (short)i };
		WriteConsoleOutputCharacterA(hand, (*it).c_str(), (*it).length()-1, Pos, &wr);
		}*/
		for (short j = 0; j < (*it).length() ; ++j)
		{
			if ((*it)[j] >= 0)
			{
				if ((*it)[j] == ' ')
				{
					continue;
				}
				Pos = { pos.X  + j ,pos.Y + (short)i };
				WriteConsoleOutputCharacterA(hOutput, &(*it)[j], 1, Pos, &wr);
				WriteConsoleOutputAttribute(hOutput, color, 2, Pos, &wr);
			}
			else
			{
				char arr[3] = { (*it)[j], (*it)[++j] };
				Pos = { pos.X  + j - 1  ,pos.Y + (short)i };
				WriteConsoleOutputCharacterA(hOutput, arr, strlen(arr), Pos, &wr);
				WriteConsoleOutputAttribute(hOutput, color, 2, Pos, &wr);
			}
		}
		it++;
	}
}

void CSwapBuffer::ShowBullet(COORD pos, WORD * color)
{
	DWORD wr;
	COORD Pos = pos;
	WriteConsoleOutputCharacterA(hOutput, "●", strlen("●"), Pos, &wr);
	WriteConsoleOutputAttribute(hOutput, color, 2, Pos, &wr);
}


void CSwapBuffer::Draw()
{
	//双缓冲处理
	ReadConsoleOutputAttribute(hOutput, atti, 5980, coord, &bytes);
	WriteConsoleOutputAttribute(hOutBuf, atti, 5980, coord, &bytes);
	ReadConsoleOutputCharacterA(hOutput, data, 5980, coord, &bytes);
	WriteConsoleOutputCharacterA(hOutBuf, data, 5980, coord, &bytes);
}