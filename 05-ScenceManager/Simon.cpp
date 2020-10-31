#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Simon.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"

CSimon::CSimon(float x, float y) : CGameObject()
{
	level = 1;
	SetState(SIMON_STATE_IDLE);
	nx = 1;
	isGrounded = true;
	this->start_x = x;
	this->start_y = y;
	this->x = x;
	this->y = y;
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += SIMON_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_ANI_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	if (state == 10)
	{
		vx = -SIMON_WALKING_SPEED;
		x += -vx;
	}
	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	//jump
	if (!isGrounded) {
		if (GetTickCount() - action_time > SIMON_RESET_JUMP_TIME) {
			action_time = 0;
			isGrounded = true;
		}
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back simon if collides with a moving objects, what if simon is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		//if (this->state == 10)
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;


		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;


		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CSimon::Render()
{
	int ani = -1;
	if (state == SIMON_ANI_DIE)
		ani = SIMON_ANI_DIE;
	else {
		if (state == SIMON_STATE_IDLE)
			ani = SIMON_ANI_IDLE;
		else
		if (state == -5)
			ani = 2;
		else
			ani = SIMON_ANI_WALKING;
		
	}
	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(nx, x, y, alpha);

	RenderBoundingBox();
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING:
		if (nx > 0)
			vx = SIMON_WALKING_SPEED;
		else
			vx = -SIMON_WALKING_SPEED;
		break;
	case SIMON_STATE_JUMP:
		action_time = GetTickCount();
		isGrounded = false;
		vy = -SIMON_JUMP_SPEED_Y;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	case SIMON_STATE_HIT:
		break;
	case SIMON_ANI_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	case -5:
		vx = 0;
		break;
	}
}

void CSimon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (nx > 0) {
		right = x + SIMON_WIDTH;
	}
	else {
		right = x + SIMON_WIDTH;
	}
	left = x;
	top = y;
	bottom = y + SIMON_HEGHT;
	
}

//CSimon::CSimon()
//{
//	level = 1;
//	this->SetState(SIMON_ANI_IDLE);
//}

void CSimon::SitDown()
{
}

void CSimon::ResetSitDown()
{
}

void CSimon::attack()
{
}

void CSimon::resetAttack()
{
}

/*
	Reset simon status to the beginning state of a scene
*/
void CSimon::Reset()
{
	SetState(SIMON_STATE_IDLE);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

