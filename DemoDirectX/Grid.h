#pragma once
#include"GameObject.h"
#include"Game.h"
#include"Utils.h"
#define Cell_width 265
#define Cell_height 250
class Grid
{
	int map_width, map_height;
	int cell_width, cell_height;
	vector<vector<vector<LPGAMEOBJECT>>> allcells;
public:
	Grid(int cell_width = Cell_width, int cell_height = Cell_height);
	~Grid();
	void Resize(int map_width, int map_height);
	void ClearGrid(int nums_row, int nums_col);
	void ResetGrid(vector<LPGAMEOBJECT> list);
	void PushGrid(vector<LPGAMEOBJECT> list);
	void GetGrid(vector<LPGAMEOBJECT> &list);
	void PushGridStart(LPGAMEOBJECT obj, int row, int col);
	void CheckCamGrid(vector<LPGAMEOBJECT>& list);

};

