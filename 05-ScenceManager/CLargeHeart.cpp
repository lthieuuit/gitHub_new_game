#include "CLargeHeart.h"

CLargeHeart::CLargeHeart(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
}

CLargeHeart::~CLargeHeart()
{
}

void CLargeHeart::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y - LARGE_HEART_BBOX_HEIGHT;
	r = x + LARGE_HEART_BBOX_WIDTH;
	b = y;
}

void CLargeHeart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CItem::Update(dt, coObjects);

	if (!isOnGround)
		vy += LARGE_HEART_GRAVITY * dt;
}
