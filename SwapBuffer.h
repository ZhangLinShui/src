#pragma once
#include "Singleton.h"
class CSwapBuffer :public Singleton<CSwapBuffer>
{
public:
	CSwapBuffer();
	~CSwapBuffer();
	
	void Draw();
	HANDLE GetBufferHandle() { return hOutput; }

	void ShowObject(vector<string> vec, COORD pos, WORD *color);
	void ShowBullet(COORD pos, WORD *color);
private:
	HANDLE hOutput;
	HANDLE hOutBuf;

	COORD coord = { 0,0 };
	COORD screenSize = { 92,65 };
	char data[5980];
	WORD atti[5980];
	DWORD bytes = 0;
	DWORD ret = 0;
};