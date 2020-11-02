#include "BlackLeopard.h"

void CBlackLeopard::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BLACK_LEOPARD_BBOX_WIDTH;
	bottom = y + BLACK_LEOPARD_BBOX_HEIGHT;
}

void CBlackLeopard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	DWORD now = GetTickCount();
	CGameObject::Update(dt, coObjects);
	vy += BLACK_LEOPARD_GRAVITY * dt;
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

}

void CBlackLeopard::Render()
{
	int ani = BLACK_LEOPARD_ANI_RUN;
	/*if (state == BLACK_LEOPARD_IDLE)
		ani = BLACK_LEOPARD_ANI_IDLE;
	else*/
	if (state == BLACK_LEOPARD_ANI_RUN)
		ani = BLACK_LEOPARD_ANI_RUN;
	animation_set->at(ani)->Render(nx, x, y);
	RenderBoundingBox();
}

CBlackLeopard::CBlackLeopard()
{
	SetState(BLACK_LEOPARD_RUN);
}

void CBlackLeopard::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BLACK_LEOPARD_RUN:
		DebugOut(L"nx %d \n", nx);
		if (nx > 0)
			vx = BLACK_LEOPARD_RUNNING_SPEED_X;
		else
			vx = -BLACK_LEOPARD_RUNNING_SPEED_X;
		DebugOut(L"vx %f \n", vx);
		break;

	case BLACK_LEOPARD_IDLE:
		vx = 0;
		break;
	}
}
