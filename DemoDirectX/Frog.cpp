#include "Frog.h"



Frog::Frog(LPGAMEOBJECT simon)
{
	this->simon = simon;
	hp = frog_hp;
	damage = frog_damage;
	score = frog_score;
}
void Frog::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject,bool clk)
{

	Enemy::Update(dt);

	if (state == frog_ani_die && animation_set->at(frog_ani_die)->RenderOver(frog_time))
	{
		isDone = true;
		return;
	}

	if (clk)
		return;

	if (x - simon->GetPositionX() > dis_appear &&!check)
		check = true;
	

	/*if(CheckCam())*/if (CheckCam()&&check&&state!=frog_ani_die)
	{
		if (GetTickCount() - timestop >= frog_stop && state != frog_ani_die)
		{
			if (nx > 0) vx = frog_vx;
			else vx = -frog_vx;


			if (simon->GetPositionY() - dis_up_down > y)
				vy = frog_xy;
			else if (simon->GetPositionY() + dis_up_down < y)
				vy = -frog_xy;

		}




		if (x < simon->GetPositionX())
		{
			if (abs(simon->GetPositionX() - x) > dis_back)
			{
				//vx = 0.08;
				nx = 1;
			}
		}
		else if (x > simon->GetPositionX())
		{
			if ((abs(simon->GetPositionX() - x) > dis_back))
			{
				//vx = -0.08;
				nx = -1;
			}
		}
		



	}


	x += dx;
	y += dy;

}

void Frog::Render()
{
	if (!isDone&&check)
		animation_set->at(state)->Render(nx, x, y);
	else return;
	//RenderBoundingBox();
}

void Frog::SetState(int State)
{
	Enemy::SetState(State);
	switch (State)
	{
	
	case frog_ani_die:
		vx = vy = 0;
		animation_set->at(State)->StartAni();
		break;
	}
}

bool Frog::CheckCam()
{
	CGame *game = CGame::GetInstance();
	return (x >= game->GetCamPosX() && x < game->GetCamPosX() + (SCREEN_WIDTH) && y >= game->GetCamPosY() && y < game->GetCamPosY() + (SCREEN_HEIGHT));
}

int Frog::getHp()
{
	return Enemy::getHp();
}

void Frog::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	if (state != frog_ani_die)
	{
		r = l + frog_box_width;
		b = t + frog_box_height;
	}
	else if (state == frog_ani_die)
	{
		r = l+1;
		b = t+1;
	}
}

void Frog::loseHp(int x)
{
	Enemy::loseHp(x);
}

Frog::~Frog()
{
}
