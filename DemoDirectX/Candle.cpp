#include "Candle.h"


Candle::Candle()
{
	//this->SetAnimationSet(CAnimationSets::GetInstance()->Get(candle_ani_set));
	isDone = false;
}
void Candle::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects,bool clk)
{
	if (state == break_candle && animation_set->at(break_candle)->RenderOver(time_render_fire))
		isDone = true;
}

void Candle::Render()
{
	if (!isDone)
		animation_set->at(state)->Render(-1, x, y);
	else
		return;

	//RenderBoundingBox();
}

void Candle::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	if(state!=break_candle)
	{
		r = l + candle_width;
		b = t + candle_height;
	}
	else if (state == break_candle)
	{
		r = l + 1;
		b = t + 1;
	}
}

void Candle::SetState(int State)
{
	CGameObject::SetState(State);
	switch (State)
	{
	case break_candle:
		animation_set->at(State)->StartAni();
		break;
	}
}

Candle::~Candle()
{
}
