#include "Zombie.h"
#include"Weapon.h"
#include"Axe.h"
void CZombie::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + ZOMBIE_BBOX_WIDTH;
	bottom = y + ZOMBIE_BBOX_HEIGHT;
}

void CZombie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	DWORD now = GetTickCount64();
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
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT obj = coObjects->at(i);
			if (dynamic_cast<CWeapon*>(obj))
			{
				CWeapon* e = dynamic_cast<CWeapon*>(obj);

				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);
				
				if (CheckColli(left, top, right, bottom))
				{
					this->isHidden = true;
					//e->Set
					
				}

			}
			else if (dynamic_cast<CAxe*>(obj))
			{
				CAxe* e = dynamic_cast<CAxe*>(obj);

				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);

				if (CheckColli(left, top, right, bottom))
				{
					this->isHidden = true;
					//e->isHidden = true;
				}

			}
		}
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
	 //Calculate dx, dy 
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	
}

void CZombie::Render()
{
	int ani = ZOMBIE_ANI_WALKING;
	/*if (state == BLACK_LEOPARD_IDLE)
		ani = BLACK_LEOPARD_ANI_IDLE;
	else*/
	if (isHidden)
		return;
	if (state == ZOMBIE_ANI_WALKING)
		ani = ZOMBIE_ANI_WALKING;
	else if (state == ZOMBIE_STATE_DIE)
	{
		return;
	}
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
bool CZombie::CheckColli(float left_a, float top_a, float right_a, float bottom_a)
{
	float l, t, r, b;
	CZombie::GetBoundingBox(l, t, r, b);

	if (CGameObject::AABBCheck(l, t, r, b, left_a, top_a, right_a, bottom_a))
		return true;
	else
		return false;
}