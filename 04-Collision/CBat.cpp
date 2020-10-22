#include "CBat.h"



void CBat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == BAT_STATE_ACTIVE)
	{
		left = x;
		top = y;
		right = x + BAT_BBOX_WIDTH_SIT;
		bottom = y - BAT_BBOX_HEIGHT_SIT;
	}
	else
		left = top = right = bottom = 0;
}

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	x += dx;
	y = sin(x * 0.03) * 41.3 + 60;
	if (vx < 0 && x < 30) {
		x = 30; vx = -vx;

	}
	if (vx > 0 && x > 250) {
		x = 250; vx = -vx;
	}
	if (y < 150)
		y += 1.0f;
}

void CBat::Render()
{
	int ani;

	if (vx == 0)
	{
		ani = BAT_ANI_SIT_LEFT;
	}
	else
	{
		if (vx < 0)
			ani = BAT_ANI_FLY_LEFT;
		else
			ani = BAT_ANI_FLY_RIGHT;
	}


	animations[ani]->Render(x, y);
}


void CBat::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BAT_STATE_ACTIVE:
		vx = 0;
		break;
	case BAT_STATE_FLY:
		vx = BAT_FLY_SPEED;
		break;
	}
}

