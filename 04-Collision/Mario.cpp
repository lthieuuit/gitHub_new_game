#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Weapon.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += MARIO_GRAVITY*dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	DebugOut(L"simon y %f \n ", y);

	// turn off collision when die 
	if (state!=MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (isAttack) {
		if (GetTickCount() - action_time > MARIO_ATTACK_TIME) {
			resetAttack();
		}
		return;
	}

	// No collision occured, proceed normally
	if (coEvents.size()==0)
	{
		x += dx; 
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx*dx + nx*0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty*dy + ny*0.4f;
		
		if (nx!=0) vx = 0;
		if (ny!=0) vy = 0;

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState()!= GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable==0)
					{
						if (goomba->GetState()!=GOOMBA_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else 
								SetState(MARIO_STATE_DIE);
						}
					}
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CMario::SitDown() {
	isSit = true;
	height = MARIO_HEGHT_IS_SIT;
}

void CMario::ResetSitDown() {
	isSit = false;
	height = MARIO_HEGHT;
	y -= MARIO_HEGHT_RESET_SIT;
}

void CMario::attack() {
	
	if (!isAttack) {
		action_time = GetTickCount();
		isAttack = true;
	}
}

void CMario::resetAttack()
{
	action_time = 0;
	isAttack = false;
	for (unsigned int i = 0; i < animations.size(); i++)
	{
		animations[i]->ResetFrame();
	}
}


void CMario::Render()
{
	int ani;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else {
		if (vx == 0)
		{
			if (nx > 0) {
				if (isSit) ani = MARIO_ANI_SIT_DOWN_RIGHT;
				else ani = MARIO_ANI_BIG_IDLE_RIGHT;
				if (isAttack) {
					if(isSit) ani = MARIO_ANI_ATTACK_SIT_RIGHT;
					else ani = MARIO_ANI_ATTACK_RIGHT;
				}
			} 
			else {
				if (isSit) ani = MARIO_ANI_SIT_DOWN_LEFT;
				else ani = MARIO_ANI_BIG_IDLE_LEFT;
				if (isAttack) {
					if (isSit) ani = MARIO_ANI_ATTACK_SIT_LEFT;
					else ani = MARIO_ANI_ATTACK_LEFT;
				}
			} 
		}
		else if (vx > 0)
			ani = MARIO_ANI_BIG_WALKING_RIGHT;
		else ani = MARIO_ANI_BIG_WALKING_LEFT;
	}

	int alpha = 255;
	//if (untouchable) alpha = 128;
	animations[ani]->Render(x, y, alpha);

	RenderBoundingBox();
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		if(isSit) ResetSitDown();
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSit) ResetSitDown();
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		vy = -MARIO_JUMP_SPEED_Y;
	case MARIO_STATE_IDLE: 
		vx = 0;
		break;
	case MARIO_STATE_SIT_DOWN:
		SitDown();
		break;
	case STATE_ATTACK:
		resetAttack();
		attack();
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	}
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 
	right = x + width;
	bottom = y + height;
}

