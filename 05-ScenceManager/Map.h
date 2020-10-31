#pragma once
#include "GameObject.h"
#include <iostream>
#include <fstream>

/*
	Object that triggers scene switching
*/
#define BRICK_BBOX_WIDTH  32
#define BRICK_BBOX_HEIGHT 32

class CMap : public CGameObject
{
public:
	int col = 0;
	int row = 0;
	int TileMap[500][176];
	int fit = 90;
public:
	virtual void Render();
	//virtual void LoadMap(int state);
	virtual void ReadMap(int state, LPCWSTR FilePath);
	//virtual void GetTileMap(int i, int j);
	//virtual void ();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
