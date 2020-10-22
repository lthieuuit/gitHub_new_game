#include "Knight.h"



Knight::Knight()
{
	hp = knight_hp;
	damage = knight_damage;
	SetState(knight_ani_run);
	score = knight_score;
}

void Knight::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject,bool clk)
{
	
	if (state == knight_ani_die && animation_set->at(knight_ani_die)->RenderOver(knight_ani_die_time))
	{
		isDone = true;
		return;
	}

	if (clk)
		return;


	Enemy::Update(dt);

	if(state!= knight_ani_die)
		vy += knight_gra * dt;
	
	

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	vector<LPGAMEOBJECT> COOBJECTS;
	COOBJECTS.clear();

	for (int i = 0; i < coObject->size(); i++)
	{
		if (coObject->at(i) == dynamic_cast<Ground*>(coObject->at(i)))
		{
			COOBJECTS.push_back(coObject->at(i));
		}
	}

	if(state!= knight_ani_die)
		CalcPotentialCollisions(&COOBJECTS, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);


		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (ny == -1.0f)
		{
			vy = 0;
		}	

		if (nx == 1 ||nx==-1)
		{		
			
			this->nx *= -1;
			this->vx *= -1;
		}		
	}

	if (GetTickCount() - timestop >= knight_time_stop && state != knight_ani_die)
	{
		if (nx > 0) vx = knight_speed;
		else vx = -knight_speed;
	}
	//DebugOut(L"SIZE: %d\n", coEvents.size());

	if (coEvents.size() >= coeventtwo && ((rand() % randommax) < randommin))
	{
		this->nx *= -1;
		this->vx *= -1;
	}

	if (coEvents.size() == 1)
	{
		if (!back)
		{
			this->nx *= -1;
			this->vx *= -1;
			back = true;
		}
	}
	if (coEvents.size() > 1)
		back = false;

	

	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
}

void Knight::Render()
{
	if(!isDone)
		animation_set->at(state)->Render(nx, x, y);
	else return;
	//RenderBoundingBox();
}

void Knight::SetState(int State)
{
	Enemy::SetState(State);
	switch (State)
	{
	case knight_ani_run:
		if (nx > 0) vx = knight_speed;
		else vx = -knight_speed;
		vy = 0;
		break;
	case knight_ani_die:
		vx = vy = 0;
		animation_set->at(State)->StartAni();
		break;
	default:
		break;
	}
}

int Knight::getHp()
{
	return Enemy::getHp();
}

void Knight::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	if (state != knight_ani_die)
	{
		r = l + knight_box_width;
		b = t + knight_box_height;
	}
	else if (state == knight_ani_die)
	{
		r = l+1;
		b = t+1;
	}
}

void Knight::loseHp(int x)
{
	Enemy::loseHp(x);
}
Knight::~Knight()
{
}
