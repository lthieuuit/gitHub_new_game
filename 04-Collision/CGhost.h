#pragma once
#include "GameObject.h"

#define GHOST_WALKING_SPEED 2.0f;
#define GHOST_GRAVITY		0.002f

#define GHOST_BBOX_WIDTH 16
#define GHOST_BBOX_HEIGHT 32

#define GHOST_ANI_WALKING_RIGHT 0
#define GHOST_ANI_WALKING_LEFT  1

#define GHOST_STATE_WALKING_RIGHT 200
#define GHOST_STATE_WALKING_LEFT 201

#define GHOST_STATE_DIE 0
#define GHOST_ANI_DIE 1
#define GHOST_STATE_ACTIVE 2


#define GHOST_STATE_DIE 0
#define GHOST_STATE_WALK 1


class CGhost : public CGameObject
{
	bool isSit = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	virtual void SetState(int state);
};


