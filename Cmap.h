#pragma once
class Cmap
{
	char *buf;
	COORD pos;
	short rows;
	short cols;
	vector<string> vec;
public:
	void Draw(HANDLE hand);
	Cmap();
	void Move();
	int GetRows() { return rows; }
	int GetCols() { return cols; }
	~Cmap();
};

