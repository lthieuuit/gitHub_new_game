#include "Raven.h"



Raven::Raven(LPGAMEOBJECT simon)
{
	this->simon = simon;
	hp = raven_hp;
	damage = raven_damage;
	score = raven_score;
}


void Raven::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject,bool clk)
{
	Enemy::Update(dt);

	if (!CheckCam() && state == raven_ani_fly)
	{
		collisimon = true;
		state = raven_ani_die;
	}

	if (state == raven_ani_die && animation_set->at(raven_ani_die)->RenderOver(raven_time))
	{
		isDone = true;
		return;
	}

	if (clk)
		return;

	if (CheckCam()&&state!=raven_ani_die)
		state = raven_ani_fly;

	if(CheckCam()&&state!=raven_ani_die)
	{
		if(!timeflydown)
			timerstopdown->Start();
		int a = rand_dis1_min + rand() % rand_dis_max;
		int b = rand_dis2_min + rand() % rand_dis_max;
		if (x < simon->GetPositionX())
		{
			//float a = 30 + rand() % 120;//% 91;
			if (abs(simon->GetPositionX() - x) > a/*100*/)
			{
				wait->Start();
				if (!wait1->IsTimeUp())
					vx = 0;
				else
					vx = raven_vx;
				nx = 1;
			}
		}
		else if (x > simon->GetPositionX())
		{
			if (abs(simon->GetPositionX() - x) > b)
			{
				wait1->Start();
				if (!wait->IsTimeUp())
				{
					vx = 0;		
				}
				else {
					vx = -raven_vx;
					
				}
					
				nx = -1;
			}
		}

		int c = rand_dis3_min + rand() % rand_dis3_max;
		int d = rand_dis4_min + rand() % rand_dis4_max;
		if (checkstar)
		{
			if (simon->GetPositionY() - c > y)
			{
				dow->Start();
				if (!dow1->IsTimeUp())
					vy = 0;
				else
					vy = raven_vy;
			}
			else if (simon->GetPositionY() + d< y)
			{
				dow1->Start();
				if (!dow->IsTimeUp())
					vy = 0;
				else
					vy = -raven_vy;
			}
		}

		


		if (timerstopdown->IsTimeUp())
			checkstar = true;

		timeflydown = true;

	}

	if (state != raven_ani_die)
	{
		x += dx;
		y += dy;
	}
}

void Raven::Render()
{
	if (!isDone)
		animation_set->at(state)->Render(nx, x, y);
	else return;
	//RenderBoundingBox();
}

void Raven::SetState(int State)
{
	Enemy::SetState(State);
	switch (State)
	{
	case raven_ani_idle:
		vx = vy = 0;
		break;
	case raven_ani_fly:
		break;
	case raven_ani_die:
		vx = vy = 0;
		animation_set->at(State)->StartAni();
		break;
	}
}

bool Raven::CheckCam()
{
	CGame *game = CGame::GetInstance();
	return (x >= game->GetCamPosX() + 10 && x < game->GetCamPosX() + (SCREEN_WIDTH) && y >= game->GetCamPosY() && y < game->GetCamPosY() + (SCREEN_HEIGHT - 30));
}

int Raven::getHp()
{
	return Enemy::getHp();
}

void Raven::GetBoundingBox(float &l, float &t, float &r, float &b)
{

	l = x;
	t = y;
	if (state != raven_ani_die)
	{
		r = l + raven_box_width;
		b = t + raven_box_height;
	}
	else if (state == raven_ani_die)
	{
		r = l + 1;
		b = t + 1;
	}
}

void Raven::loseHp(int x)
{
	Enemy::loseHp(x);
}


Raven::~Raven()
{
}
