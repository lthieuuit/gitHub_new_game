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

	GetAnimation();
	CheckSize();
	

	if (isCandle || isTorch) {
		dy = 0;
		DebugOut(L"height %d \n", height);
		DebugOut(L"width %d \n", width);
	} 


		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;


		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT obj = coObjects->at(i);
		}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			
			if (dynamic_cast<CWeapon*>(e->obj)) {
				DebugOut(L"haha %d \n", height);
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
		break;
	case ITEM_ANI_CANDLE:
		height = ITEM_HEIGHT_ID_ANI_CANDLE;
		width = ITEM_WIDTH_ID_ANI_CANDLE;
		break;
	case ITEM_ANI_FIRE:
		height = 15;
		width = 15;
		break;
	default:
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
		isTorch = true;
		isCandle = false;
		isFire = false;
		break;
	case ITEM_ANI_CANDLE:
		ani = ITEM_ANI_CANDLE;
		isTorch = false;
		isCandle = true;
		isFire = false;
		break;
	case ITEM_ANI_FIRE:
		action_time = GetTickCount();
		ani = ITEM_ANI_FIRE;
		isTorch = false;
		isCandle = false;
		isFire = true;
		break;
	default:
		break;
	}
	return ani;
}

