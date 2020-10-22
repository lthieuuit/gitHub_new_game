#include "CDog.h"


void CDog::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == DOG_STATE_ACTIVE)
	{
		left = x;
		top = y;
		right = x + DOG_BBOX_WIDTH_SIT;
		bottom = y - DOG_BBOX_HEIGHT_SIT;
	}
	else
		left = top = right = bottom = 0;
}

void CDog::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (vx < 0 && x < 30) {
		x = 30; vx = -vx;
		
	}

	if (vx > 0 && x > 200) {
		x = 200; vx = -vx;
	}
	if(y<155)
	y += 0.5f;
	x += vx;

}

void CDog::Render()
{
	int ani;

	if (vx == 0)
	{
		ani = DOG_ANI_SIT_LEFT;
	}
	else
	{
		if (vx < 0)
			ani = DOG_ANI_WALKING_LEFT;
		else
			ani = DOG_ANI_WALKING_RIGHT;
	}
	
	
	animations[ani]->Render(x, y);
}

void CDog::StopFall(float y)
{

}
void CDog::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case DOG_STATE_ACTIVE:
		vx = 0;
		break;
	case DOG_STATE_JUMP:
		vx = DOG_WALKING_SPEED;
		vy = 55;
	case DOG_STATE_WALK:
		vx = DOG_WALKING_SPEED;
		break;
	}
}
