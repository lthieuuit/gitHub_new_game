#include "Torch.h"

void CTorch::Render()
{
	animation_set->at(0)->Render(1, x, y);
	RenderBoundingBox();
}


void CTorch::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + TORCH_BBOX_WIDTH;
	b = y + TORCH_BBOX_HEIGHT;
}