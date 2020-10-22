#include "Zombie.h"



Zombie::Zombie()
{
	hp = zombie_hp;
	score = zombie_score;
	damage = zombie_damage;
}

void Zombie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool clk)
{
	if (state == zombie_ani_die && animation_set->at(zombie_ani_die)->RenderOver(zombie_time))
	{
		isDone = true;
		return;
	}

	
	if (clk)
		return;
		

	Enemy::Update(dt);
	if (!CheckCam()&&check)
		state = zombie_ani_die;

	if (state != zombie_ani_die)
		vy += zombie_gra * dt;


	if (CheckCam() && state != zombie_ani_die)
	{
		check = true;
		vx = nx * zombie_vx;
	}

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

	//if (state != 1)
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


		x += min_tx * dx + nx * 0.1f;
		y += min_ty * dy + ny * 0.1f;


		if (ny != 0)
		{
			if (ny == -1.0f)
			{
				vy = 0;
			}
		}
		
	}
	
	

	for (int i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void Zombie::Render()
{
	if (!isDone)
		animation_set->at(state)->Render(nx, x, y);
	else return;
	//RenderBoundingBox();
}

void Zombie::SetState(int State)
{
	Enemy::SetState(State);
	switch (State)
	{
	case zombie_ani_die:
		vx = vy = 0;
		animation_set->at(State)->StartAni();
		break;
	default:
		break;
	}
}

int Zombie::getHp()
{
	return Enemy::getHp();
}

void Zombie::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	if (state != zombie_ani_die)
	{
		r = l + zombie_box_width;
		b = t + zombie_box_height;
	}
	else if (state == zombie_ani_die)
	{
		r = l + 1;
		b = t + 1;
	}
}

void Zombie::loseHp(int x)
{
	Enemy::loseHp(x);
}


bool Zombie::CheckCam()
{
	CGame *game = CGame::GetInstance();
	return (x >= game->GetCamPosX() - 10 && x < game->GetCamPosX() + (SCREEN_WIDTH-10) && y >= game->GetCamPosY() && y < game->GetCamPosY() + (SCREEN_HEIGHT));
}

Zombie::~Zombie()
{
}
