#include "Knife.h"
#include <time.h>
#include "Utils.h"
#include "Textures.h"
#include "Game.h"


CKnife::CKnife() {
	this->SetState(KNIFE_STATE_HIDDEN);
	x = -100;
	y = -100;
	isHidden = false;
	level = 1;
}

void CKnife::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	//DebugOut(L"isHidden  %d\n", this->isHidden);
	//DebugOut(L"action_time UPDATE %d\n", this->action_time);
	//nếu đang hiện 
	int distance = 0;
	if (!isHidden) {
		if (GetTickCount() - action_time > KNIFE_ATTACK_TIME) //|| SCREEN_WIDTH - this->x > 400)
		{
			isHidden = true;
			this->action_time = 0;
			ResetBB();
			knife_isAtk = 0;
			//DebugOut(L"axe_isatk: %d \f", axe_isAtk);
		}
		else
		{
			x += dx;
			distance += dx;
			if (distance > 420)
			{
				isHidden = true;
				this->action_time = 0;
				ResetBB();
				knife_isAtk = 0;
			}
		}
	}
}

void CKnife::Attack(DWORD dt)
{

}

void CKnife::Render()
{
	if (isHidden) return;
	int ani = GetAnimation();
	animation_set->at(ani)->Render(nx, x, y, 255);
}
void CKnife::ResetAnimation(int ani)
{
	animation_set->at(ani)->ResetFrame();
}

void CKnife::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = x + width;
	top = y;
	bottom = y + height;
}

void CKnife::SetState(int state)
{
	CGameObject::SetState(state);
	int ani;
	switch (state)
	{
	case KNIFE_STATE_ATTACK:
		ani = GetAnimation();
		if (nx > 0) vx = KNIFE_SPEED_X;
		else vx = -KNIFE_SPEED_X;
		frame = 3;
		this->action_time = GetTickCount();
		isHidden = false;
		knife_isAtk = 1;
		break;
	case KNIFE_STATE_HIDDEN:
		ani = GetAnimation();
		//ResetAnimation(ani);
		isHidden = true;
		knife_isAtk = 0;
		//speedy = KNIFE_SPEED_Y;
		break;
	default:
		break;
	}
}

CKnife* CKnife::__instance = NULL;
CKnife* CKnife::GetInstance()
{
	if (__instance == NULL) __instance = new CKnife();
	return __instance;
}

int CKnife::GetAnimation() {
	int ani;
	switch (this->level)
	{
	case 1: {
		ani = KNIFE_ANI;
		break;
	}
	default:
		ani = KNIFE_STATE_HIDDEN;
		break;
	}
	return ani;
}

void CKnife::UpdatePosionWithSimon(int _x, int _y, int _nx) {
	this->x = _x;
	this->y = _y;
	this->nx = _nx;

}

void CKnife::GetPositionForSimon() {


}