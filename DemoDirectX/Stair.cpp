#include "Stair.h"

Stair::Stair()
{
	
}
void Stair::Render()
{
	animation_set->at(0)->Render(-1, x, y);
	RenderBoundingBox();
}
void Stair::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = l + stair_box_width;
	b = t + stair_box_height;
}

Stair::~Stair()
{
}