#include "Axe.h"
#include <time.h>
#include "Utils.h"
#include "Textures.h"
#include "Game.h"


CAxe::CAxe() {
	this->SetState(AXE_STATE_HIDDEN);
	x = -100;
	y = -100;
	isHidden = false;
	level = 1;
}

void CAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	//DebugOut(L"isHidden  %d\n", this->isHidden);
	//DebugOut(L"action_time UPDATE %d\n", this->action_time);

	if (!isHidden) {
		if (GetTickCount() - action_time > AXE_ATTACK_TIME) {
			isHidden = true;
			this->action_time = 0;
			ResetBB();
		}
		else
		{
			x += dx;
			y -= speedy * dt;
			speedy -= 0.019;
		}
	}
}

void CAxe::Render()
{
	if (isHidden) return;
	int ani = GetAnimation();
	animation_set->at(ani)->Render(nx, x, y, 255);
}
void CAxe::ResetAnimation(int ani)
{
	animation_set->at(ani)->ResetFrame();
}

void CAxe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = x + width;
	top = y;
	bottom = y + height;
}

void CAxe::SetState(int state)
{
	CGameObject::SetState(state);
	int ani;
	switch (state)
	{
	case AXE_STATE_ATTACK:
		ani = GetAnimation();
		if (nx > 0) vx = AXE_SPEED_X;
		else vx = -AXE_SPEED_X;
		frame = 3;
		this->action_time = GetTickCount();
		isHidden = false;
		break;
	case AXE_STATE_HIDDEN:
		ani = GetAnimation();
		//ResetAnimation(ani);
		isHidden = true;
		speedy = AXE_SPEED_Y;
		break;
	default:
		break;
	}
}

CAxe* CAxe::__instance = NULL;
CAxe* CAxe::GetInstance()
{
	if (__instance == NULL) __instance = new CAxe();
	return __instance;
}

int CAxe::GetAnimation() {
	int ani;
	switch (this->level)
	{
	case 1: {
		ani = AXE_ANI;
		break;
	}
	default:
		ani = AXE_STATE_HIDDEN;
		break;
	}
	return ani;
}

void CAxe::UpdatePosionWithSimon(int _x, int _y, int _nx) {
	this->x = _x;
	this->y = _y;
	this->nx = _nx;

}

void CAxe::GetPositionForSimon() {


}