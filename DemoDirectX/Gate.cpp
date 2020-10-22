#include "Gate.h"

Gate::Gate()
{
}


void Gate::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{

}

void Gate::Render()
{
	RenderBoundingBox();
}

void Gate::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = l+gate_box_width;
	b = t+gate_box_height;
}

Gate::~Gate()
{
}
