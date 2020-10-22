#pragma once
#include "GameObject.h"

#define BAT_FLY_SPEED 0.05f

#define BAT_BBOX_WIDTH_SIT 12
#define BAT_BBOX_HEIGHT_SIT 14


#define BAT_STATE_ACTIVE 0
#define BAT_IDLE_SIT 1
#define BAT_STATE_DIE 2
#define BAT_STATE_FLY 3

#define BAT_ANI_SIT_RIGHT 0
#define BAT_ANI_SIT_LEFT 1
#define BAT_ANI_FLY_RIGHT 2
#define BAT_ANI_FLY_LEFT 3

class CBat : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	virtual void SetState(int state);
};

