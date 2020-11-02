#include "Zombie.h"

void CZombie::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + ZOMBIE_BBOX_WIDTH;
	bottom = y + ZOMBIE_BBOX_HEIGHT;
}

void CZombie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	DWORD now = GetTickCount();
	CGameObject::Update(dt, coObjects);
	vy += ZOMBIE_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0, rdx = 0, rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += dx;
		y += min_ty * dy + ny * 0.1f;

		if (vx < 0 && x < 0) {
			x = 0; vx = -vx;
			this->nx = 1;
		}

		if (vx > 0 && x > 500) {
			x = 500; vx = -vx;
			this->nx = -1;
		}
	}
	/*CGameObject::Update(dt, coObjects);
	x += dx;
	y += dy;
	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
		nx = 1;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
		nx = -1;
	}*/
}

void CZombie::Render()
{
	int ani = ZOMBIE_ANI_WALKING;
	/*if (state == BLACK_LEOPARD_IDLE)
		ani = BLACK_LEOPARD_ANI_IDLE;
	else*/
	if (state == ZOMBIE_ANI_WALKING)
		ani = ZOMBIE_ANI_WALKING;
	else
		ani = ZOMBIE_ANI_WALKING;
	animation_set->at(ani)->Render(nx, x, y);
	RenderBoundingBox();
}

CZombie::CZombie()
{
	SetState(ZOMBIE_WALKING);
}


void CZombie::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ZOMBIE_WALKING:
		DebugOut(L"nx %d \n", nx);
		if (nx > 0)
			vx = ZOMBIE_WALKING_SPEED_X;
		else
			vx = -ZOMBIE_WALKING_SPEED_X;
		DebugOut(L"vx %f \n", vx);
		break;
	}
}
