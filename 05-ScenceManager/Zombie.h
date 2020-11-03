#pragma once
#include "GameObject.h"
#include "Utils.h"

#define BLACK_LEOPARD_ACTIVE		0    
#define BLACK_LEOPARD_DESTROYED		1
#define ZOMBIE_WALKING				2


#define BLACK_LEOPARD_ANI_IDLE			1
#define BLACK_LEOPARD_ANI_JUMP			3
#define ZOMBIE_ANI_WALKING				0
#define BLACK_LEOPARD_ANI_RUN_RIGHT		2

#define ZOMBIE_WALKING_SPEED_X			0.13f
#define ZOMBIE_WALKING_SPEED_Y			0.2f
#define ZOMBIE_GRAVITY					0.001f

#define ZOMBIE_BBOX_WIDTH			32
#define ZOMBIE_BBOX_HEIGHT			64
#define BLACK_LEOPARD_ACTIVE_BBOX_WIDTH		100
#define BLACK_LEOPARD_ACTIVE_BBOX_HEIGHT	200

class CZombie : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	bool isHidden = false;
public:
	bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	CZombie();
	virtual void SetState(int state);
};

