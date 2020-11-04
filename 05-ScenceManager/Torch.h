#pragma once
#include "GameObject.h"

#define TORCH_BBOX_WIDTH  31
#define TORCH_BBOX_HEIGHT 64

#define TORCH_STATE_DESTROYED 0
#define TORCH_STATE_ALIVE 1

#define TORCH_ANI_DESTROYED	0
#define TORCH_ANI_ALIVE	1


class CTorch : public CGameObject
{
public: 
	bool isHidden = false;
public:
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	
	bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};