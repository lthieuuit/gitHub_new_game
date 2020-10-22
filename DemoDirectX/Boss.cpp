#include "Boss.h"



Boss::Boss(LPGAMEOBJECT s)
{
	this->s = s;
	hp = boss_max_hp;//1; 
	damage = boss_damage;
	score = boss_score;
	fireball = new FireBall();
}

void Boss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject, bool clk)
{

	Enemy::Update(dt);
	
	



	if (state == boss_ani_die && animation_set->at(boss_ani_die)->RenderOver(boss_time))
	{
		isDone = true;
		return;
	}


	if (clk)
		return;


	if (s->x - this->x >= boss_active && !checkactive)
	{
		
		checkactive = true;
	}

	//int a = 80 + rand() % 200;
	//int b = rand() % 50;

	if (checkactive&&state != boss_ani_die)
	{	
		
		if (hp > 0)
			state = boss_ani_fly;

		if (x > s->x)
			nx = -1;
		else nx = 1;

		if (y > s->y)
			ny = -1;
		if (y <= s->y)
			ny = 1;

		if (rand() % rand_min ==1 && (x > CGame::GetInstance()->GetCamPosX() - screen_box_left) && (x < CGame::GetInstance()->GetCamPosX() + screen_box_right) && !target)
		{
			if (!fly)
			{
				vx = (float)(nx*abs(s->x - x)) / max_distance;
				vy = (float)(ny*abs(s->y - y)) / max_distance;
			}
			//checkstop = false;
		}
		
		if (/*rand() % 4 < 3 && */abs(s->x - x) <= 1.0f)
		{
			timer1->Start();
			vy = -vy_donw;
			if (rand() % 2 == 1)
				vx = vx_close;
			else
				vx = -vx_close;
			fly = true;
			checkstop = true;
		}
		if (timer1->IsTimeUp() && checkstop)
		{
			vx = vy = 0;
			fly = false;
			target=false;
			checkstop = false;
		}

		
		


		if (x <= CGame::GetInstance()->GetCamPosX() - screen_box_left)
		{
			//timer1->Start();
			target = true;
			vx = vx_close;
			vy = -vy_donw;
			if (abs(x - s->x) > max_dis_right_left)
			{
				target = false;
			}
		}
		else if (x > CGame::GetInstance()->GetCamPosX() + screen_box_right)
		{
			
			target = true;
			vx = -vx_close;
			if (rand() % 2 == 1)
				vy = vy_right_left;
			else
				vy = -vy_right_left;
			if (abs(x - s->x) > max_dis_right_left)
			{
				target = false;
			}
		}
		else if (y < CGame::GetInstance()->GetCamPosY() + screen_box_up)
		{
			target = true;
			vy = vy_right_left;
			if (abs(y - s->y) > max_dis_up_down)
			{

				target = false;
			}
		}
		else if (y > CGame::GetInstance()->GetCamPosY() + screen_box_down)
		{
			//timer1->Stop();
			target = true;
			vy = -vy_donw;
			if (abs(y - s->y) > max_dis_up_down)
			{

				target = false;
			}
		}
		/*if (hp > 0)
			state = 1;

		if (x > s->x)
		{
			if (abs(s->GetPositionX() - x) > a && (x > CGame::GetInstance()->GetCamPosX() - 10))
			{		
				nx = -1;
				vx = 0.12*nx;
			}
		}

		if (x < s->x)
		{
			if (abs(s->GetPositionX() - x) > a && (x + 70 <= CGame::GetInstance()->GetCamPosX() + 530))
			{
				nx = 1;
				vx = 0.12*nx;
			}
		}

		int c = 100+rand() % 150;
		int d = 30+rand() % 70;
		if (y < s->y - c)
			vy += 0.0007;
		else if (s->y + d < y)
			vy -= 0.004;
		if (x < CGame::GetInstance()->GetCamPosX() - 10)
		{
			vx = 0.16;
			vy =-0.009;
		}
		if (x >= CGame::GetInstance()->GetCamPosX() + 420)
		{
			x = CGame::GetInstance()->GetCamPosX() + 420;
		}*/

	}


	if (!fireball->isDone&&vx == 0 && vy == 0 && checkactive &&state != boss_ani_die)
	{
		if (!fireball->checkset)
		{
			fireball->setpos(D3DXVECTOR2(x, y));
			fireball->setspeed(s->x, s->y,this->nx,this->ny);
			fireball->checkset = true;
		}

	}
	fireball->Update(dt);
	if (fireball->isDone)
		fireball->isDone = false;



	x += dx;
	y += dy;
}

void Boss::Render()
{
	fireball->Render();
	if (!isDone)
		animation_set->at(state)->Render(1, x, y);
	else return;
	//RenderBoundingBox();
}

void Boss::SetState(int State)
{
	Enemy::SetState(State);
	switch (State)
	{
	case boss_ani_die:
		vx = vy = 0;
		animation_set->at(State)->StartAni();
		break;
	}
}



int Boss::getHp()
{
	return Enemy::getHp();
}

void Boss::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x + 13;
	t = y;
	if (state != boss_ani_die)
	{
		r = l + boss_box_width;
		b = t + boss_box_height;
	}
	else if (state == boss_ani_die)
	{
		r = l + 1;
		b = t + 1;
	}
}

void Boss::loseHp(int x)
{
	Enemy::loseHp(x);
}

Boss::~Boss()
{
}
