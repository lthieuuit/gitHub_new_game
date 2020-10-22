#include "CGhost.h"

void CGhost::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GHOST_STATE_ACTIVE)
	{
		left = x;
		top = y;
		right = x + GHOST_BBOX_WIDTH;
		bottom = y - GHOST_BBOX_HEIGHT;
	}
	else
		left = top = right = bottom = 0;
}

void CGhost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	x += vx;
	y += dy;
	if (vx < 0 && x < 80) {
		x = 80; vx = -vx;
	}

	if (vx > 0 && x > 200) {
		x = 200; vx = -vx;
	}
}

void CGhost::Render()
{
	int ani;
		if (vx > 0)
			ani = GHOST_ANI_WALKING_RIGHT;
		else
			ani = GHOST_ANI_WALKING_LEFT;
	animations[ani]->Render(x, y);
}

void CGhost::SetState(int state)
{

	CGameObject::SetState(state);
	switch (state)
	{
	case GHOST_STATE_ACTIVE:
		vx = GHOST_WALKING_SPEED;
	}
}
