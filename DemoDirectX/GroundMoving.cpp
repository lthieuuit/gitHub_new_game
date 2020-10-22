#include "GroundMoving.h"



GroundMoving::GroundMoving()
{
	vx = groundmoving_vx;
}

void GroundMoving::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects,bool clk)
{
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);


	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		//y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.1f;		
		//y += min_ty * dy + ny * 1.9f;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Ground*>(e->obj))
			{
				if (nx != 0)
				{
					this->nx *= -1;
					vx *= -1;
				}
			}
		}
	}
}

void GroundMoving::Render()
{
	animation_set->at(0)->Render(-1, x, y);
}

void GroundMoving::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = l + groundmoving_box_width;
	b = t + groundmoving_box_height;
}
GroundMoving::~GroundMoving()
{
}
