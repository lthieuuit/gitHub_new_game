#include <algorithm>
#include <assert.h>

#include "Torch.h"
#include "PlayScence.h"
#include "Utils.h"

void CTorch::Render()
{
	if (isHidden) return;
	animation_set->at(0)->Render(1, x, y);
	RenderBoundingBox();
}

void CTorch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
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
			}

		}
	}
}

bool CTorch::CheckColli(float left_a, float top_a, float right_a, float bottom_a) {
	float l, t, r, b;
	CTorch::GetBoundingBox(l, t, r, b);

	if (CGameObject::AABBCheck(l, t, r, b, left_a, top_a, right_a, bottom_a))
		return true;
	else
		return false;
}


void CTorch::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + TORCH_BBOX_WIDTH;
	b = y + TORCH_BBOX_HEIGHT;
}