#include "Map.h"

void CMap::Render()
{
	if (state == 0)
	{
		animation_set->at(0)->Render(0,0,0, 255);
	}
	else
	{
		for (int i = 0; i < row - 1; i++)
		{
			for (int j = 0; j < col; j++)
			{
				animation_set->at(TileMap[i][j])->Render(0, -x + j * 32, fit + i * 32, 255);
			}
		}
	}
}
void CMap::ReadMap(int state, LPCWSTR FilePath)// đường dẫn đọc mảng,sate
{
	
	//int i = 0;
	switch (state)
	{
	case 1: col = 48; break;
	case 2: col = 176; fit = 58; break;
	case 3: col = 128; fit = 58; break;
	default:; break;
	}
		ifstream file;
		file.open(FilePath, ios::in);
		while (!file.eof())
		{
			for (int j = 0; j < col; j++)
			{
				file >> TileMap[row][j];
			}
			row++;
		}
	
}
void CMap::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	//l = x;
	//t = y;
	//r = col * BRICK_BBOX_WIDTH;
	//b = 10 * BRICK_BBOX_HEIGHT + 80;
}