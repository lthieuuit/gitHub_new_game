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

	if (!isHidden) {
		if (GetTickCount() - action_time > WEAPON_ATTACK_TIME) {
			isHidden = true;
			this->action_time = 0;
		}
		else {
			GetPositionForSimon();
		}
	}
}

void CWeapon::Render()
{
	if (isHidden) return;
	int ani = GetAnimation();
	animation_set->at(ani)->Render(nx,x, y, 255);
}
void CWeapon::ResetAnimation(int ani)
{
	animation_set->at(ani)->ResetFrame();
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
		//ResetAnimation(ani);
		frame = 3;
		this->action_time = GetTickCount();
		isHidden = false;
		break;
	case WEAPON_STATE_HIDDEN:
		ani = GetAnimation();
		//ResetAnimation(ani);
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

void CWeapon::UpdatePosionWithSimon(int _x, int _y, int _nx) {
	this->x = _x;
	this->y = _y;
	this->nx = _nx;
	DebugOut(L"x update %d \n", x);
	DebugOut(L"y update %d \n", y);
	DebugOut(L"nx update %d \n", nx);
}
void CWeapon::GetPositionForSimon() {
	int ani = GetAnimation();
	DebugOut(L"x %d \n", x);
	DebugOut(L"y %d \n", y);
	DebugOut(L"nx %d \n", nx);
	int currenFrame = animation_set->at(ani)->GetCurrentFrame();
	DebugOut(L"frame %d \n", currenFrame);
	if (nx > 0) {
		if (currenFrame != frame) {
			if (currenFrame == 0) {
				SetFrame(frame - 1);
				x -= 50;
				y += 2;
				frame = 0;
			}
			else if (currenFrame == 1) {
				x -= 7;
				y -= 1;
				frame = 1;
			}
			else if (currenFrame == 2) {
				x += 32;
				y += 2;
				frame = 2;
			}
		}
	}
	else {
		if (currenFrame != frame) {
			if (currenFrame == 0) {
				SetFrame(frame - 1);
				x += 20;
				y += 2;
				frame = 0;
			}
			else if (currenFrame == 1) {
				x -= 10;
				y -= 1;
				frame = 1;
			}
			else if (currenFrame == 2) {
				if (level == 3) {
					x -= 45;
					y += 2;
					frame = 2;
				}
				else {
					x -= 32;
					y += 2;
					frame = 2;
				}
			}
		}
	}

}