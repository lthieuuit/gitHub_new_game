#include "Weapon.h"
#include "Mario.h"
#include <time.h>
#include "debug.h"


CWeapon::CWeapon() {
	x = -100;
	y = -100;
	isHidden = true;
	level = 1;
}

void CWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//CGameObject::Update(dt)
	//DebugOut(L"isHidden  %d\n", this->isHidden);
	//DebugOut(L"action_time UPDATE %d\n", this->action_time);
	//DebugOut(L"GetTickCount  %d\n", GetTickCount());*/
	
	if (!isHidden){
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
	animations[ani]->Render(x, y, 255);
}
void CWeapon::ResetAttack()
{
	for (unsigned int i = 0; i < animations.size(); i++)
	{
		animations[i]->ResetFrame();
	}
}

void CWeapon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

}

void CWeapon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WEAPON_STATE_ATTACK:
		ResetAttack();
		frame = 3;
		this->action_time = GetTickCount();
		isHidden = false;
		break;
	case WEAPON_STATE_HIDDEN:
		ResetAttack();
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
	if (nx > 0) {
		switch (this->level)
		{
		case 1: {
			ani = WEAPON_ANI_1_RIGHT;
			break;
		}
		case 2: {
			ani = WEAPON_ANI_2_RIGHT;
			break;
		}
		case 3: {
			ani = WEAPON_ANI_3_RIGHT;
			break;
		}
		default:
			ani = WEAPON_STATE_HIDDEN;
			break;
		}
	}
	else {
		switch (level)
		{
		case 1: {
			ani = WEAPON_ANI_1_LEFT;
			break;
		}
		case 2: {
			ani = WEAPON_ANI_2_LEFT;
			break;
		}
		case 3: {
			ani = WEAPON_ANI_3_LEFT;
			break;
		}
		default:
			ani = WEAPON_STATE_HIDDEN;
			break;
		}
	}
	return ani;
}

void CWeapon::UpdatePosionWithSimon(int _x, int _y, int _nx) {
	this->x = _x;
	this->y = _y;
	this->nx = _nx;
}
void CWeapon::GetPositionForSimon() {
	int ani = GetAnimation();
	int currenFrame = animations[ani]->GetCurrentFrame();
	if (nx > 0) {
		if (currenFrame != frame) {
			if (currenFrame == 0) {
				SetFrame(frame - 1);
				x -= 7;
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
				x += 7;
				y += 2;
				frame = 0;
			}
			else if (currenFrame == 1) {
				x += 7;
				y -= 1;
				frame = 1;
			}
			else if (currenFrame == 2) {
				x -= 32;
				y += 2;
				frame = 2;
			}
		}
	}
	
}