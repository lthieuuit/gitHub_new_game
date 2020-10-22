#include "Items.h"
Items::Items()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(items_ani_set));

	timeStart = -1;	
	isDone = false;
}

void Items::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects,bool clk)
{
	CGameObject::Update(dt);

	
	


	if (state == items_small_heart&&vy!=0)
	{
		vx += small_heart_vx;
		if (vx >= 0.1|| vx <= -0.1)
			vx *= -1;
	}


	if (timeStart == -1)
		timeStart = GetTickCount();
	else
	{
		if (GetTickCount() - timeStart > time_items_des&&state != items_boss)
		{
			isDone = true;
			return;
		}
	}


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> COOBJECTS;
	COOBJECTS.clear();

	for (int i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i) == dynamic_cast<Ground*>(coObjects->at(i)) || coObjects->at(i) == dynamic_cast<BreakWall*>(coObjects->at(i)))
		{
			COOBJECTS.push_back(coObjects->at(i));
		}
	}

	CalcPotentialCollisions(&COOBJECTS, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		y += min_ty * dy + ny * 0.1f;

		if (ny != 0)
			vx = vy = 0;
		
	}

	if (state == items_crown && y > crown_hight)
		vy = -crown_appear_vy;
	if (state == items_crown && y <= crown_hight)
		vy = 0;
	
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Items::Render()
{
	if (isDone)
		return;

	if(state!=-1)
		animation_set->at(state)->Render(-1, x, y);
	else return;
	//RenderBoundingBox();
}

void Items::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (!isDone)
	{
		switch (state)
		{
		case items_for_whip:
			l = x;
			t = y;
			r = l + items_whip_box_width;
			b = t + items_whip_box_height;
			break;
		case items_big_heart:
			l = x;
			t = y;
			r = l + items_bigheart_box_width;
			b = t + items_bigheart_box_height;
			break;
		case items_knife:
			l = x;
			t = y;
			r = l + items_knife_box_width;
			b = t + items_knife_box_height;
			break;
		case items_watch:
			l = x;
			t = y;
			r = l + items_watch_box_width;
			b = t + items_watch_box_height;
			break;
		case items_axe:
			l = x;
			t = y;
			r = l + items_axe_box_width;
			b = t + items_axe_box_height;
			break;
		case items_boom:
			l = x;
			t = y;
			r = l + items_boom_box_width;
			b = t + items_boom_box_height;
			break;
		case items_holywater:
			l = x;
			t = y;
			r = l + items_holy_box_width;
			b = t + items_holy_box_height;
			break;
		case items_watterbottle:
			l = x;
			t = y;
			r = l + items_water_box_width;
			b = t + items_water_box_height;
			break;
		case items_corss:
			l = x;
			t = y;
			r = l + items_cross_box_width;
			b = t + items_cross_box_height;
			break;
		case items_double:
			l = x;
			t = y;
			r = l + items_double_box_width;
			b = t + items_double_box_height;
			break;
		case items_triple:
			l = x;
			t = y;
			r = l + items_triple_box_width;
			b = t + items_triple_box_height;
			break;
		case items_meat:
			l = x;
			t = y;
			r = l + items_meat_box_width;
			b = t + items_meat_box_height;
			break;
		case items_small_heart:
			l = x;
			t = y;
			r = l + items_smallheart_box_width;
			b = t + items_smallheart_box_height;
			break;
		case items_redmoney:
		case items_bluemoney:
		case items_whitemoney:
			l = x;
			t = y;
			r = l + items_money_box_width;
			b = t + items_money_box_height;
			break;
		case items_crown:
			l = x;
			t = y;
			r = l + items_crown_box_width;
			b = t + items_crown_box_height;
			break;
		case items_boss:
			l = x;
			t = y;
			r = l + items_boss_box_width;
			b = t + items_boss_box_height;
			break;
		default:
			l = t = r = b = 0;
			break;
		}
	}
}

void Items::SetState(int State)
{
	CGameObject::SetState(State);
	switch (State)
	{
	case items_for_whip:
		vx = items_vx;
		vy = items_vy;
		break;
	case items_big_heart:
		vx = items_vx;
		vy = items_vy;
		break;
	case items_knife:
		vx = items_vx;
		vy = items_vy;
		break;
	case items_watch:
		vx = items_vx;
		vy = items_vy;
		break;
	case items_axe:
		vx = items_vx;
		vy = items_vy;
		break;
	case items_boom:
		vx = items_vx;
		vy = items_vy;
		break;
	case items_holywater:
		vx = items_vx;
		vy = items_vy;
		break;
	case items_watterbottle:
		vx = items_vx;
		vy = items_vy;
		break;
	case items_corss:
		vx = items_vx;
		vy = items_vy;
		break;
	case items_double:
		vx = items_vx;
		vy = items_vy;
		break;
	case items_triple:
		vx = items_vx;
		vy = items_vy;
		break;
	case items_meat:
		vx = items_vx;
		vy = items_vy;
		break;
	case items_small_heart:
		vx = items_vx;
		vy = 0.05;
		break;
	case items_redmoney:
	case items_bluemoney:
	case items_whitemoney:
		vx = items_vx;
		vy = items_vy;
		break;
	case items_crown:
		vx = items_vx;
		vy = items_vy;
		break;
	case items_boss:
		vx = items_vx;
		vy = items_vy;
		break;
	default:
		vx = vy = 0;
		break;
	}
}

Items::~Items()
{
	
}
