#pragma once
#include"GameObject.h"

#define stair_box_width 32
#define stair_box_height 32
class Stair :public CGameObject
{
public:
	Stair();
	~Stair();
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};