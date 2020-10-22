#pragma once
#include"GameObject.h"
#include"Ground.h"
#define groundmoving_box_width 64
#define groundmoving_box_height 16
#define groundmoving_vx 0.05
class GroundMoving :public CGameObject
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL,bool clk=false);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	GroundMoving();
	~GroundMoving();
};

