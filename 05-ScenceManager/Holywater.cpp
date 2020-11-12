#include "Holywater.h"
#include <time.h>
#include "Utils.h"
#include "Textures.h"
#include "Game.h"
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Game.h"
#include "PlayScence.h"

#include "Goomba.h"
#include "Portal.h"

#include "Brick.h"

CHlw::CHlw() {
	this->SetState(HLW_STATE_HIDDEN);
	x = -100;
	y = -100;
	isHidden = false;
	level = 1;
}

void CHlw::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	//DebugOut(L"isHidden  %d\n", this->isHidden);
	//DebugOut(L"action_time UPDATE %d\n", this->action_time);
	//nếu đang hiện 
	if (!isHidden) {
		if (GetTickCount() - action_time > HLW_ATTACK_TIME || this->y > 400)
		{
			isHidden = true;
			this->action_time = 0;
			ResetBB();
			hlw_isAtk = 0;
			//DebugOut(L"axe_isatk: %d \f", axe_isAtk);
		}
		else
		{
			x += dx;
			y -= speedy * dt;
			speedy -= 0.019;
		}
		if (coEvents.size() == 0)
		{

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
			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;


			if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;


			//
			// Collision logic with other objects
			//
			for (UINT i = 0; i < coObjects->size(); i++)
			{
				LPGAMEOBJECT obj = coObjects->at(i);
			}
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CBrick*>(e->obj)) {
					CBrick* brick = dynamic_cast<CBrick*>(e->obj);
						if (e->nx != 0) {
							state = HLW_STATE_COLLIDE;
							vy = 0;
						}
						if (e->ny != 0) {
							state = HLW_STATE_COLLIDE;
							vy = 0;
						}

				}
			}
		}
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void CHlw::Attack(DWORD dt)
{

}

void CHlw::Render()
{
	if (isHidden) return;
	int ani = GetAnimation();
	animation_set->at(ani)->Render(nx, x, y, 255);
}
void CHlw::ResetAnimation(int ani)
{
	animation_set->at(ani)->ResetFrame();
}

void CHlw::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = x + width;
	top = y;
	bottom = y + height;
}

void CHlw::SetState(int state)
{
	CGameObject::SetState(state);
	int ani;
	switch (state)
	{
	case HLW_STATE_ATTACK:
		ani = GetAnimation();
		if (nx > 0) vx = HLW_SPEED_X;
		else vx = -HLW_SPEED_X;
		frame = 3;
		this->action_time = GetTickCount();
		isHidden = false;
		hlw_isAtk = 1;
		break;
	case HLW_STATE_HIDDEN:
		ani = GetAnimation();
		//ResetAnimation(ani);
		isHidden = true;
		hlw_isAtk = 0;
		speedy = HLW_SPEED_Y;
		break;
	case HLW_STATE_COLLIDE:
		ani = GetAnimation();
		//ResetAnimation(ani);
		//isHidden = true;
		hlw_isAtk = 0;
		speedy = HLW_SPEED_Y;
		break;
	default:
		break;
	}
}

CHlw* CHlw::__instance = NULL;
CHlw* CHlw::GetInstance()
{
	if (__instance == NULL) __instance = new CHlw();
	return __instance;
}

int CHlw::GetAnimation() {
	int ani;
	switch (this->state)
	{
	case 1: {
		ani = HLW_ANI_ATTACK;
		break;
	}
	case 2:
	{
		ani = HLW_ANI_COLLIDE;
		break;
	}
	default:
		ani = HLW_STATE_HIDDEN;
		break;
	}
	return ani;
}

void CHlw::UpdatePosionWithSimon(int _x, int _y, int _nx) {
	this->x = _x;
	this->y = _y;
	this->nx = _nx;

}
