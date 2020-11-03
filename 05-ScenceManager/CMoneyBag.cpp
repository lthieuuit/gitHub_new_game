#include "CMoneyBag.h"

CMoneyBag::CMoneyBag(D3DXVECTOR2 position, int id)
{
	this->x = position.x;
	this->y = position.y;

	showScoreStart = 0;
}

CMoneyBag::~CMoneyBag()
{
}

void CMoneyBag::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (showScoreStart == 0)
	{
		l = x;
		t = y - MONEY_BAG_BBOX_HEIGHT;
		r = x + MONEY_BAG_BBOX_WIDTH;
		b = y;
	}
	else
		l = t = r = b = 0;
}

void CMoneyBag::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CItem::Update(dt, objects);

	if (!isOnGround)
		vy += MONEY_BAG_GRAVITY * dt;
	/*if (showScoreStart > 0)
		vy = 0;

	if (showScoreStart > 0 && GetTickCount() - showScoreStart > MONEY_BAG_SHOW_SCORE_TIME)
		state = STATE_DESTROYED;*/
}

void CMoneyBag::Render()
{
	int ani = 0;
		if (showScoreStart == 0)
			ani = MONEY_BAG_BONUS_ANI;
		else
			ani = MONEY_BAG_BONUS_SCORE_ANI;
}

void CMoneyBag::StartShowScore()
{
	showScoreStart = GetTickCount();
}
