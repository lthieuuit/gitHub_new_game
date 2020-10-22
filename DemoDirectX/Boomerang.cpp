#include "Boomerang.h"

Boomerang::Boomerang(LPGAMEOBJECT simon)
{
	SetAnimationSet(CAnimationSets::GetInstance()->Get(boom_aniset));
	isDone = true;
	isFire = false;
	this->simon = simon;
}

void Boomerang::collisionwith(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> COOBJECTS;
	COOBJECTS.clear();
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i) != dynamic_cast<Gate*>(coObjects->at(i)) && coObjects->at(i) != dynamic_cast<Ground*>(coObjects->at(i)) && coObjects->at(i) != dynamic_cast<BreakWall*>(coObjects->at(i)))
		{
			COOBJECTS.push_back(coObjects->at(i));
		}
	}
	COOBJECTS.push_back(simon);

	
	CalcPotentialCollisions(&COOBJECTS, coEvents);
	aabbmob(&COOBJECTS);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		

		// kiểm tra va chạm với object
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Candle *>(e->obj))
			{
				x += dx;
				Candle *candle = dynamic_cast<Candle *>(e->obj);

				if (e->nx != 0 || e->ny != 0)
				{
					listHit.push_back(CreateHit(candle->GetPositionX(), candle->GetPositionY() + add_dis_hit));
					candle->SetState(break_candle);

				}
			}
			else if (dynamic_cast<Simon*>(e->obj))
			{
				this->isDone = true;
				this->isFire = false;
				checkdamage1 = false;
			}
			else if (dynamic_cast<Knight*>(e->obj))
			{
				x += dx;

				Knight *knight = dynamic_cast<Knight*>(e->obj);

				if (!checkdamage1)
				{
					checkdamage1 = true;
					if (e->nx != 0)
					{
						knight->loseHp(dame_into_knight);
						if (knight->GetState() != knight_ani_die)
						{
							listHit.push_back(CreateHit(knight->GetPositionX(), knight->GetPositionY() + add_dis_hit));

						}
						if (knight->getHp() <= 0)
						{
							knight->SetState(knight_ani_die);
						}
					}
					checkdamage1 = false;
					return;
				}
			}
			else if (dynamic_cast<Frog*>(e->obj))
			{
				x += dx;
				Frog *frog = dynamic_cast<Frog*>(e->obj);


				if (!checkdamage1&&frog->check)
				{
					checkdamage1 = true;
					if (e->nx != 0)
					{

						frog->loseHp(dame_into_frog);

						if (frog->GetState() != frog_ani_die)
							listHit.push_back(CreateHit(frog->GetPositionX(), frog->GetPositionY() + add_dis_hit));


						if (frog->getHp() <= 0)
							frog->SetState(frog_ani_die);

					}
					checkdamage1 = false;
				}
				return;
			}
			else if (dynamic_cast<Monkey*>(e->obj))
			{
				x += dx;
				Monkey *monkey = dynamic_cast<Monkey*>(e->obj);

				if (e->nx != 0 || e->ny != 0)
				{
					monkey->loseHp(dame_into_monkey);
					if (monkey->GetState() != monkey_ani_die)
						listHit.push_back(CreateHit(monkey->GetPositionX(), monkey->GetPositionY() + add_dis_hit));


					if (monkey->getHp() <= 0)
						monkey->SetState(monkey_ani_die);
							
				}
			}
			else if (dynamic_cast<Bat*>(e->obj))
			{
				x += dx;
				Bat  *bat = dynamic_cast<Bat*>(e->obj);

				if (e->nx != 0 || e->ny != 0)
				{
					bat->loseHp(dame_into_bat);
					if (bat->GetState() != bat_ani_die)
						listHit.push_back(CreateHit(bat->GetPositionX(), bat->GetPositionY() + add_dis_hit));


					if (bat->getHp() <= 0)
						bat->SetState(bat_ani_die);
				}
			}
			else if (dynamic_cast<SmallCandle *>(e->obj))
			{
				x += dx;
				SmallCandle *candle = dynamic_cast<SmallCandle *>(e->obj);

				if (candle->GetState() != break_candle)
				{
					listHit.push_back(CreateHit(candle->GetPositionX(), candle->GetPositionY() + add_dis_hit));
					candle->SetState(break_candle);
				}
			}
			else if (dynamic_cast<Skeleton*>(e->obj))
			{
				x += dx;
				//Skeleton *skele = dynamic_cast<Skeleton*>(e->obj);

				////if (e->nx != 0 || e->ny != 0)
				//{
				//	skele->loseHp(dame_into_skele);
				//	if (skele->GetState() != skeleton_ani_die)
				//		listHit.push_back(CreateHit(skele->GetPositionX(), skele->GetPositionY() + add_dis_hit));

				//	if (skele->getHp() <= 0)
				//		skele->SetState(skeleton_ani_die);
				//}
			}
			else if (dynamic_cast<Raven*>(e->obj))
			{
				x += dx;
				Raven *raven = dynamic_cast<Raven*>(e->obj);

				if (e->nx != 0 || e->ny != 0)
				{
					
					raven->loseHp(dame_into_raven);
					if (raven->GetState() != raven_ani_die)
						listHit.push_back(CreateHit(raven->GetPositionX(), raven->GetPositionY() + add_dis_hit));


					if (raven->getHp() <= 0)
						raven->SetState(raven_ani_die);
				}
			}
			else if (dynamic_cast<Zombie*>(e->obj))
			{
				x += dx;
				Zombie *zombie = dynamic_cast<Zombie*>(e->obj);

				if (e->nx != 0 || e->ny != 0)
				{
					zombie->colliwhip = true;
					zombie->loseHp(dame_into_zombie);
					if (zombie->GetState() != zombie_ani_die)
						listHit.push_back(CreateHit(zombie->GetPositionX(), zombie->GetPositionY() + add_dis_hit));


					if (zombie->getHp() <= 0)
						zombie->SetState(zombie_ani_die);
				}
			}
			else if (dynamic_cast<Boss*>(e->obj))
			{
				x += dx;
				Boss *boss = dynamic_cast<Boss*>(e->obj);

				if (!checkdamage1)
				{
					checkdamage1 = true;
					//if (e->nx != 0)
					{

						boss->loseHp(dame_into_boss);
						if (boss->GetState() != boss_ani_die)
							listHit.push_back(CreateHit(boss->GetPositionX(), boss->GetPositionY() + add_dis_hit));


						if (boss->getHp() <= 0)
							boss->SetState(boss_ani_die);

					}
					checkdamage1 = false;
					return;
				}
			}
		}

		
	}



	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void Boomerang::aabbmob(vector<LPGAMEOBJECT>* listmob)
{
	float l, t, r, b, l_mob, t_mob, r_mob, b_mob;
	this->GetBoundingBox(l, t, r, b);
	for (int i = 0; i < listmob->size(); i++)
	{
		LPGAMEOBJECT e = listmob->at(i);
		if (dynamic_cast<Skeleton*>(e))
		{
			Skeleton *skele = dynamic_cast<Skeleton*>(e);
			skele->GetBoundingBox(l_mob, t_mob, r_mob, b_mob);
			if (CGameObject::AABBCheck(l, t, r, b, l_mob, t_mob, r_mob, b_mob))
			{
				skele->loseHp(dame_into_skele);
				if (skele->GetState() != skeleton_ani_die)
					listHit.push_back(CreateHit(skele->GetPositionX(), skele->GetPositionY() + add_dis_hit));


				if (skele->getHp() <= 0)
					skele->SetState(skeleton_ani_die);
			}
		}
	}
}

void Boomerang::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	/*if (GetTickCount() - timereset >= 30)
		checkreset = true;
*/


	SubWeapon::ClearListHit();
	SubWeapon::Update(dt);

	if (nx > 0) vx -= boom_comeback_vx;
	else vx += boom_comeback_vx;
	

	if (CheckPosKnife(POSX))
	{
		isFire = false;
		isDone = true;
		checkdamage1 = false;
		return;
	}



	collisionwith(dt, coObjects);
}

void Boomerang::Render()
{
	if (!isDone && !CheckPosKnife(POSX))
		SubWeapon::Render();

	SubWeapon::renderlisthit();

	//RenderBoundingBox();
}

void Boomerang::SetV()
{
	if (nx > 0) vx = boom_vx;
	else vx = -boom_vx;
	vy = 0;
}

void Boomerang::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (!isDone)
	{
		left = x;
		top = y;
		right = left + boom_box_width;
		bottom = top + boom_box_height;
	}
}
void Boomerang::SetPosSubWeapon(D3DXVECTOR3 pos, bool isstanding)
{
	SubWeapon::SetPosSubWeapon(D3DXVECTOR3(pos.x, pos.y, 0), isstanding);
	POSX = pos.x;
}

bool Boomerang::CheckPosKnife(float a)
{

	if (vx > 0)
	{
		if (x - a >= ((SCREEN_WIDTH / 2) + add_dis_cam))
			return true;
	}
	else if (vx < 0)
	{
		if (a - x >= ((SCREEN_WIDTH / 2) + add_dis_cam))
			return true;
	}
	return false;
}


Boomerang::~Boomerang()
{
}
