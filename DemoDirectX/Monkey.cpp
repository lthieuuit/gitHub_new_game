#include "Monkey.h"



Monkey::Monkey(LPGAMEOBJECT simon)
{
	this->simon = simon;
	hp = monkey_hp;
	score = monkey_score;
	damage = monkey_damage;
}

void Monkey::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject,bool clk)
{

	if (state == monkey_ani_die && animation_set->at(monkey_ani_die)->RenderOver(monkey_time))
	{
		isDone = true;
		return;
	}

	if (clk)
		return;

	Enemy::Update(dt);

	if (!CheckCam() && active)
		state = monkey_ani_die;



	if (state != monkey_ani_die)
		vy += monekey_gra * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPGAMEOBJECT> COOBJECTS;
	COOBJECTS.clear();

	for (int i = 0; i < coObject->size(); i++)
	{
		if (coObject->at(i) == dynamic_cast<Ground*>(coObject->at(i)))
		{
			COOBJECTS.push_back(coObject->at(i));
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
		float min_tx, min_ty, nx = 0, ny = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		
		if (ny!=0)
		{
			if (ny == -1)
			{
				vy = 0;
				
			}

		}
	}

	
	
	//else
	if (CheckCam() && state != monkey_ani_die /*&& !runfar*/)
	{
		/*if (!check)
			timerunfar = GetTickCount();
		check = true;*/
		
		
		active = true;
		if (x < simon->GetPositionX())
		{
			if (abs(simon->GetPositionX() - x) > small_dis)
			{
				//vx =0.16;
				nx = 1;
			}
		}
		else if (x > simon->GetPositionX())
		{
			if ((abs(simon->GetPositionX() - x) > small_dis))
			{
				//vx = -0.16;
				nx = -1;
			}
		}
		
		if (((rand() % rand_max < rand_min)&& (abs(simon->GetPositionX() - x) < dis_si_monkey)) && y > allow_y_jump)
		{
			vy = monkey_vy;
			//jump = false;
		}
		
		if (vy < 0)
			vx = nx * monkey_vx_jump;
		else
			vx = nx * monkey_vx_notjump;
	}

	// clean up collision events
	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];


}

void Monkey::Render()
{
	if (!isDone)
		animation_set->at(state)->Render(nx, x, y);
	else return;
	//RenderBoundingBox();
}

void Monkey::SetState(int State)
{
	Enemy::SetState(State);
	switch (State)
	{
	case monkey_ani_die:
		vx = vy = 0;
		animation_set->at(State)->StartAni();
		break;
	default:
		break;
	}
}

int Monkey::getHp()
{
	return Enemy::getHp();
}

void Monkey::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	if (state != monkey_ani_die)
	{
		r = l + monkey_box_width;
		b = t + monkey_box_height;
	}
	else if (state == monkey_ani_die)
	{
		r = l + 1;
		b = t + 1;
	}
}

bool Monkey::CheckCam()
{
	CGame *game = CGame::GetInstance();
	return (x >= game->GetCamPosX()+50 && x < game->GetCamPosX() + (SCREEN_WIDTH) && y >= game->GetCamPosY() && y < game->GetCamPosY() + (SCREEN_HEIGHT-32));
}

void Monkey::loseHp(int x)
{
	Enemy::loseHp(x);
}


Monkey::~Monkey()
{
}
