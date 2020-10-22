#include "Bat.h"



Bat::Bat(LPGAMEOBJECT simon)
{
	this->simon = simon;
	hp = bat_hp;
	isDone = false;
	SetState(bat_ani_idle);
	damage = bat_damage;
	score = bat_score;
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject,bool clk)
{
	
	Enemy::Update(dt);	
	

	if (state == bat_ani_die && animation_set->at(bat_ani_die)->RenderOver(bat_time))
	{
		isDone = true;
		return;
	}
	if (clk)
		return;

	if (state!= bat_ani_die)
	{
		if (simon->GetState() != simon_ani_stair_down && simon->GetState() != simon_ani_stair_up && simon->GetState() != simon_ani_jump && simon->GetState() != simon_ani_stand_hit)
		{
			if (sqrt(pow(x - simon->GetPositionX(), 2) + pow(y - simon->GetPositionY(), 2))<= bat_distance_max)
			{
				SetState(bat_ani_fly);
				if (y < bat_distance)
					vy += bat_gravity;
				else
					vy = 0;
				
			}
		}
		else
		{
			if (sqrt(pow(x - simon->GetPositionX(), 2) + pow(y - simon->GetPositionY(), 2)) <= bat_distance_min)
			{
				SetState(bat_ani_fly);
				if (y < bat_distance)
					vy += bat_gravity;
				else
					vy = 0;
			}

		}

		if (!CheckCam()&&state==bat_ani_fly)
		{
			collisimon = true;
			SetState(bat_ani_die);
		}
		
	}

	x += dx;
	y += dy;
	
	
}

void Bat::Render()
{
	if(!isDone)
		animation_set->at(state)->Render(nx, x, y);
	else return;
	//RenderBoundingBox();
}

void Bat::SetState(int State)
{
	Enemy::SetState(State);
	switch (State)
	{
	case bat_ani_idle:
		vx = vy = 0;
		break;
	case bat_ani_fly:
		if (nx > 0) vx = bat_speed;
		else vx = -bat_speed;
		vy = bat_ani_fly_vy;
		break;
	case bat_ani_die:
		vx = vy = 0;
		animation_set->at(State)->StartAni();
		break;
	}
}

bool Bat::CheckCam()
{
	CGame *game = CGame::GetInstance();
	return (x >= game->GetCamPosX() && x < game->GetCamPosX() + (SCREEN_WIDTH-10)&& y >= game->GetCamPosY() && y < game->GetCamPosY() + (SCREEN_HEIGHT));
}

int Bat::getHp()
{
	return Enemy::getHp();
}

void Bat::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	if (state != bat_ani_die)
	{
		r = l + bat_box_width;
		b = t + bat_box_height;
	}
	else if (state == bat_ani_die)
	{
		r = l + 1;
		b = t + 1;
	}
}

void Bat::loseHp(int x)
{
	Enemy::loseHp(x);
}
Bat::~Bat()
{
}
