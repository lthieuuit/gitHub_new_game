#pragma once
#include "GameObject.h"

#define CANDLE_BBOX_WIDTH  15
#define CANDLE_BBOX_HEIGHT 31

class CCandle : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};