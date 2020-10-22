#include "Ground.h"

Ground::Ground()
{
}

void Ground::Render()
{
	animation_set->at(0)->Render(-1, x, y);
	RenderBoundingBox();
}

void Ground::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = l + ground_box_width;
	b = t + ground_box_height;
}

Ground::~Ground()
{
}
