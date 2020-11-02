#pragma once
#include "GameObject.h"

#define TORCH_BBOX_WIDTH  31
#define TORCH_BBOX_HEIGHT 64

class CTorch : public CGameObject
{
public:
	virtual void Render();
	
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};