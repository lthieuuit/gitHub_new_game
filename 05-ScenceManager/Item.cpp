#include "Item.h"
#include "PlayScence.h"
#include "Portal.h"


CItem::CItem()
{
	nx = 1;
	isHidden = false;
}

CItem::~CItem()
{
}


void CItem::Render()
{
	if (isHidden) return;
	int ani = GetAnimation();
	animation_set->at(ani)->Render(nx, x, y, 255);
	RenderBoundingBox();
}
void CItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	r = x + width;
	t = y;
	b = y + height;

}
void CItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	vy += ITEM_GRAVITY * dt;
	coEvents.clear();
	CheckSize();
	

	if (isCandle || isTorch) {
		vy = 0;
	}
	if (isFire) {
		vy = 0;
		if (GetTickCount() - action_time > ITEM_TIME_FIRE) {
			isFire = false;
			action_time = 0;
			isHidden = true;
		}
	}

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		if (isTorch || isCandle) {
			if (dynamic_cast<CWeapon*>(obj))
			{
				CWeapon* e = dynamic_cast<CWeapon*>(obj);

				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);

				if (e->frame == 2) {
					if (CheckColli(left, top, right, bottom))
					{
						SetID(ITEM_ANI_FIRE);
						isFire = true;
						action_time = GetTickCount();
					}
				}
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

bool CItem::CheckColli(float left_a, float top_a, float right_a, float bottom_a) 
{
	float l, t, r, b;
	CItem::GetBoundingBox(l, t, r, b);

	if (CGameObject::AABBCheck(l, t, r, b, left_a, top_a, right_a, bottom_a))
		return true;
	else
		return false;
}
void CItem::CheckSize()
{
	switch (this->id)
	{
	case ITEM_ANI_ROI: {
		this->height = ITEM_HEIGHT_ID_ANI_0;
		this->width = ITEM_WIDTH_ID_ANI_0;
		break;
	}
	case ITEM_ANI_TIM: {
		this->height = ITEM_HEIGHT_ID_ANI_1;
		this->width = ITEM_WIDTH_ID_ANI_1;
		break;
	}
	case ITEM_ANI_MONEY_BAG: {
		height = ITEM_HEIGHT_ID_ANI_2;
		width = ITEM_WIDTH_ID_ANI_2;
		break;
	}
	case 3: {
		height = ITEM_HEIGHT_ID_ANI_3;
		width = ITEM_WIDTH_ID_ANI_3;
		break;
	}
	case ITEM_ANI_TORCH:
		height = ITEM_HEIGHT_ID_ANI_TORCH;
		width = ITEM_WIDTH_ID_ANI_TORCH;
		isTorch = true;
		isCandle = false;
		isFire = false;
		break;
	case ITEM_ANI_CANDLE:
		height = ITEM_HEIGHT_ID_ANI_CANDLE;
		width = ITEM_WIDTH_ID_ANI_CANDLE;
		isTorch = false;
		isCandle = true;
		isFire = false;
		break;
	case ITEM_ANI_FIRE:
		height = 15;
		width = 15;
		isTorch = false;
		isCandle = false;
		isFire = true;
		break;
	default:
		isTorch = false;
		isCandle = false;
		isFire = false;
		break;
	}
}

int CItem::GetAnimation()
{
	int ani =0;
	switch (this->id)
	{
	case ITEM_ANI_ROI: {
		ani = ITEM_ANI_ROI;
		break;
	}
	case ITEM_ANI_TIM: {
		ani = ITEM_ANI_TIM;
		break;
	}
	case 2: {
		ani = ITEM_ANI_HOLY_WATER;
		break;
	}
	case ITEM_ANI_TORCH:
		ani = ITEM_ANI_TORCH;
		
		break;
	case ITEM_ANI_CANDLE:
		ani = ITEM_ANI_CANDLE;
		break;
	case ITEM_ANI_FIRE:
		ani = ITEM_ANI_FIRE;
		break;
	default:
		break;
	}
	return ani;
}

