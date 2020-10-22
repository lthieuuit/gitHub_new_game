#pragma once
#include"GameObject.h"
#define ground_ani 0
#define ground_ani_set 2

#define ground_box_width 32
#define ground_box_height 32

class Ground :public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	Ground();
	~Ground();
};

