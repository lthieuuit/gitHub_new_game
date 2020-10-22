#pragma once
#include"GameObject.h"
//#include"Piece.h"
#define breakwall_width 32
#define breakwall_height 32

 
class BreakWall :public CGameObject
{
public:
	//vector<LPPIECE> listpiece;
	virtual void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	//Piece* CreatePiece(float x, float y, int type);
	BreakWall();
	~BreakWall();
};

