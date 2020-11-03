#pragma once
#include "GameObject.h"
#include "Utils.h"


#define ZOMBIE_WALKING				2

#define ZOMBIE_STATE_DIE	3


#define ZOMBIE_ANI_WALKING				0


#define ZOMBIE_WALKING_SPEED_X			0.13f
#define ZOMBIE_WALKING_SPEED_Y			0.2f
#define ZOMBIE_GRAVITY					0.001f

#define ZOMBIE_BBOX_WIDTH			32
#define ZOMBIE_BBOX_HEIGHT			64

class CZombie : public CGameObject
{
public:
	bool isHidden = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	CZombie();
	virtual void SetState(int state);
};

