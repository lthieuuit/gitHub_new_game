#include "Weapon.h"
#include <time.h>
#include "Utils.h"
#include "Textures.h"
#include "Game.h"


CWeapon::CWeapon() {
	this->SetState(WEAPON_STATE_HIDDEN);
	x = -100;
	y = -100;
	isHidden = false;
	level = 1;
}

void CWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	//DebugOut(L"isHidden  %d\n", this->isHidden);
	//DebugOut(L"action_time UPDATE %d\n", this->action_time);

	if (!isHidden) {
		if (GetTickCount() - action_time > WEAPON_ATTACK_TIME) {
			isHidden = true;
			this->action_time = 0;
		}
			
	}
}

void CWeapon::Render()
{
	if (isHidden) return;
	int ani = GetAnimation();
	animation_set->at(ani)->Render(nx,x, y, 255);
}
void CWeapon::ResetAnimation()
{
	for (int i = 0; i < animation_set->size(); i++) {
		animation_set->at(i)->ResetFrame();
	}
}

void CWeapon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

void CWeapon::SetState(int state)
{
	CGameObject::SetState(state);
	int ani;
	switch (state)
	{
	case WEAPON_STATE_ATTACK:
		ani = GetAnimation();
		animation_set->at(ani)->ResetFrame();
		frame = 3;
		this->action_time = GetTickCount();
		isHidden = false;
		break;
	case WEAPON_STATE_HIDDEN:
		isHidden = true;
		break;
	default:
		break;
	}
}

CWeapon* CWeapon::__instance = NULL;
CWeapon* CWeapon::GetInstance()
{
	if (__instance == NULL) __instance = new CWeapon();
	return __instance;
}

int CWeapon::GetAnimation() {
	int ani;
		switch (this->level)
		{
		case 1: {
			ani = WEAPON_ANI_1;
			break;
		}
		case 2: {
			ani = WEAPON_ANI_2;
			break;
		}
		case 3: {
			ani = WEAPON_ANI_3;
			break;
		}
		default:
			ani = WEAPON_STATE_HIDDEN;
			break;
		}
	return ani;
}

void CWeapon::UpdatePosionWithSimon(float _x, float _y, int _nx) {
	DebugOut(L"x update %f \n", _x);
	DebugOut(L"y update %f \n", _y);
	DebugOut(L"nx update %d \n", _nx);
	//x = _x;
	//y = _y;
	nx = _nx; 
	int ani = GetAnimation();
	int currenFrame = animation_set->at(ani)->GetCurrentFrame();
	//DebugOut(L"frame %d \n", currenFrame);
	if (nx > 0) {
		if (currenFrame != frame) {
			if (currenFrame == 0) {
				SetFrame(frame - 1);
				x = _x - 10;
				y = _y + 11.0f;
				frame = 0;
			}
			else if (currenFrame == 1) {
				x = _x - 10.0f;
				y = _y + 2;
				frame = 1;
			}
			else if(currenFrame == 2) {
				DebugOut(L"a %d \n", currenFrame);
				x = _x + 43.0f;
				y = _y +  8.0f;
				frame = 2;
			}
		}
	}
	else {
		if (currenFrame != frame) {
			if (currenFrame == 0) {
				SetFrame(frame - 1);
				x = _x + 55;
				y = _y + 11;
				frame = 0;
			}
			else if (currenFrame == 1) {
				x = _x ;
				y = _y + 2;
				frame = 1;
			}
			else if (currenFrame == 2) {
				DebugOut(L"b %d \n", currenFrame);
				x = _x - 45;
				y = _y + 10;
				frame = 2;
			}
		}
	}
	DebugOut(L"x %f \n", x);
	DebugOut(L"y %f \n", y);
	DebugOut(L"nx %d \n", nx);
}
void CWeapon::GetPositionForSimon() {
	
}