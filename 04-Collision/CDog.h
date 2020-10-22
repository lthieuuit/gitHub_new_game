#pragma once
#include "GameObject.h"

#define DOG_WALKING_SPEED 1.0f;
#define DOG_GRAVITY		0.002f

#define DOG_BBOX_WIDTH_SIT 24
#define DOG_BBOX_HEIGHT_SIT 15

#define DOG_BBOX_WIDTH_STAND 28
#define DOG_BBOX_HEIGHT_STAND 16

#define DOG_BBOX_WIDTH_WALK 30
#define DOG_BBOX_HEIGHT_WALK 16

#define DOG_BBOX_WIDTH_RUN 32
#define DOG_BBOX_HEIGHT_RUN 13

#define DOG_ANI_SIT_RIGHT 0
#define DOG_ANI_SIT_LEFT  1
//#define DOG_ANI_STAND_RIGHT 2
//#define DOG_ANI_STAND_LEFT 3
#define DOG_ANI_WALKING_RIGHT 2
#define DOG_ANI_WALKING_LEFT 3
//#define DOG_ANI_RUN_RIGHT 2
//#define DOG_ANI_RUN_LEFT 3

//#define DOG_IDLE_SIT 4
#define DOG_STATE_DIE 0
//#define DOG_ANI_DIE 1
#define DOG_STATE_ACTIVE 3
#define DOG_STATE_WALK 1
#define DOG_STATE_JUMP 2

class CDog : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	virtual void StopFall(float y);
	virtual void SetState(int state);
};
