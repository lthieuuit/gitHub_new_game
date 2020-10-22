#include "Skeleton.h"



Skeleton::Skeleton(LPGAMEOBJECT simon)
{
	this->simon = simon;
	score = skeleton_score;
	hp = skeleton_hp;
	damage = skeleton_damage;
	for (int i = 0; i < max_bone; i++)
	{
		bone[i] = new Bone();
	}

}

void Skeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject,bool clk)
{
	if (!bone[bone_2]->isDone)
	{
		if (rand() % max_rand < rand_fire_bone2)
		{
			if (!bone[bone_2]->getcheck())
			{
				bone[bone_2]->SetNx(nx);
				bone[bone_2]->setpos(D3DXVECTOR2(x, y));
				bone[bone_2]->SetState(bone_ani_fly);
				bone[bone_2]->setcheck(true);
			}
		}
		bone[bone_2]->Update(dt, coObject);
	}
	if (bone[bone_2]->isDone)
		bone[bone_2]->isDone = false;

	if (!bone[bone_3]->isDone)
	{
		if (rand() % max_rand < rand_fire_bone3)
		{
			if (!bone[bone_3]->getcheck())
			{
				bone[bone_3]->SetNx(nx);
				bone[bone_3]->setpos(D3DXVECTOR2(x, y));
				bone[bone_3]->SetState(bone_ani_fly);
				bone[bone_3]->setcheck(true);
			}
		}
		bone[bone_3]->Update(dt, coObject);
	}
	if (bone[bone_3]->isDone)
		bone[bone_3]->isDone = false;

	if (!bone[bone_1]->isDone)
	{
		if (rand() % max_rand < rand_fire_bone1)
		{
			if (!bone[bone_1]->getcheck())
			{
				bone[bone_1]->SetNx(nx);
				bone[bone_1]->setpos(D3DXVECTOR2(x, y));
				bone[bone_1]->SetState(bone_ani_fly);
				bone[bone_1]->setcheck(true);
			}
		}

		bone[bone_1]->Update(dt, coObject);
	}
	if (bone[bone_1]->isDone)
		bone[bone_1]->isDone = false;

	if (!CheckCam() && state == skeleton_ani_idle && active)
		state = skeleton_ani_die;

	if (state == skeleton_ani_die && animation_set->at(skeleton_ani_die)->RenderOver(skeleton_time))
	{
		isDone = true;
		return;
	}


	if (clk)
		return;
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPGAMEOBJECT> COOBJECTS;
	coEvents.clear();




	COOBJECTS.clear();

	for (int i = 0; i < coObject->size(); i++)
	{
		if (coObject->at(i) == dynamic_cast<Ground*>(coObject->at(i)))
			COOBJECTS.push_back(coObject ->at(i));
	}

	CalcPotentialCollisions(&COOBJECTS/*coObject*/, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		
		if(nhay1lan) //cham đất thì mới nhảy
			jump = true;
	}
	else
	{
		
		float min_tx, min_ty, nx = 0, ny=0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 1.9f;
		y += min_ty * dy + ny * 0.1f;

		


		if (ny != 0)
		{

			if (ny == -1)
			{
				vy = 0;
				nhay1lan = true;
			}
			else
				y += dy;

		}

		
	
	}


	Enemy::Update(dt);
	if(state!=skeleton_ani_die)
		vy += skeleton_gra * dt;

	


	if (x >= simon->GetPositionX())
		nx = -1;
	else
		nx = 1;

	if (abs(x - simon->GetPositionX()) < active_max_dis&&CheckCam())
	{
		active = true;
		if (abs(simon->GetPositionX() - x) > small_dis_one)
		{
			if (coEvents.size() != 0 && state != skeleton_ani_die)
				vx = skeleton_vx * nx;
		}
		else if (abs(simon->GetPositionX() - x) < small_dis_two)
		{
			if (coEvents.size() != 0 && state != skeleton_ani_die)
				vx = -skeleton_vx * nx;
		}





		if (jump&&y > max_y_jump && state != skeleton_ani_die)
		{
			vy = skeleton_vy;
			nhay1lan = jump = false;
		}
	}

}

void Skeleton::Render()
{
	for (int i = 0; i < max_bone; i++)
		bone[i]->Render();

	if (!isDone)
	{	
		animation_set->at(state)->Render(nx, x, y);
	}
	else return;
	//RenderBoundingBox();
}

void Skeleton::SetState(int State)
{
	Enemy::SetState(State);
	switch (State)
	{
	case skeleton_ani_idle:
		vx = vy = 0;
		break;
	case skeleton_ani_die:
		vx = vy = 0;
		animation_set->at(State)->StartAni();
	default:
		break;
	}
}

int Skeleton::getHp()
{
	return Enemy::getHp();
}

void Skeleton::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	if (state != skeleton_ani_die)
	{
		r = l + skeleton_box_width;
		b = t + skeleton_box_height;
	}
	else if (state == skeleton_ani_die)
	{
		r = l + 1;
		b = t + 1;
	}
}

bool Skeleton::CheckCam()
{
	CGame *game = CGame::GetInstance();
	return (x >= game->GetCamPosX() -5/*+5*/ && x < game->GetCamPosX() + (SCREEN_WIDTH)-5/*20*/ &&y >= game->GetCamPosY() && y < game->GetCamPosY() + (SCREEN_HEIGHT)-20);
}

void Skeleton::loseHp(int x)
{
	Enemy::loseHp(x);
}

Skeleton::~Skeleton()
{
}
