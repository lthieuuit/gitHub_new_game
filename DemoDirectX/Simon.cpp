#include "Simon.h"
#include"Ground.h"


Simon::Simon() 
{
	whip = new Whip();
	for (int i = 0; i < max_sub; i++)
	{
		knife[i] = new Knife();
		
		axe[i] = new Axe();

		boom[i] = new Boomerang(this);

		holywater[i] = new Holywater();
	}
	clk = new Clock();
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(simon_ani_set));
	currentWeapon = -1;
	isGrounded = false;
	health = simon_max_health;
	//state = simon_ani_idle;
	score = simon_score;
	mana = simon_mana;
	life = simon_life;
	this->nextscene = simon_nextscene;
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects,bool clk)
{
	CGameObject::Update(dt);
	
	/*if (!isStandOnStair&&y > 400)
	{
		SetState(simon_ani_dead);
		return;
	}*/

	if (untouchtime->IsTimeUp())
		untouchtime->Stop();
	if (watertime->IsTimeUp())
		watertime->Stop();
	

	if (x < max_screen_left) //để cài không cho simon đi ngược màn hình
		x = max_screen_left;
	if (x > max_screen_right)
		x = max_screen_right;

	


	if (isStandOnStair == false && isWalkStair == false)
		vy += simon_gravity * dt;

	
	if (health == 0)
	{
		SetState(simon_ani_dead);
		return;
	}


	if (isWalkStair == true)
		DoAutoWalkStair();

	

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	vector<LPGAMEOBJECT> COOBJECTS;
	COOBJECTS.clear();


	for (int i = 0; i < coObjects->size(); i++)
	{	
		if (coObjects->at(i) == dynamic_cast<Ground*>(coObjects->at(i)) || coObjects->at(i) == dynamic_cast<Gate*>(coObjects->at(i)) || coObjects->at(i) == dynamic_cast<GroundMoving*>(coObjects->at(i)) || coObjects->at(i) == dynamic_cast<BreakWall*>(coObjects->at(i)))
		//if (coObjects->at(i) != dynamic_cast<Candle*>(coObjects->at(i)) && coObjects->at(i) != dynamic_cast<SmallCandle*>(coObjects->at(i)) && (coObjects->at(i) != dynamic_cast<Monkey*>(coObjects->at(i))) && (coObjects->at(i) != dynamic_cast<Frog*>(coObjects->at(i))) && (coObjects->at(i) != dynamic_cast<Knight*>(coObjects->at(i))) && coObjects->at(i) != dynamic_cast<Zombie*>(coObjects->at(i)) && coObjects->at(i) != dynamic_cast<Skeleton*>(coObjects->at(i)) && coObjects->at(i) != dynamic_cast<Boss*>(coObjects->at(i)) && coObjects->at(i) != dynamic_cast<Bone*>(coObjects->at(i)) && coObjects->at(i) != dynamic_cast<Raven*>(coObjects->at(i)))
		{
			COOBJECTS.push_back(coObjects->at(i));
		}
	}
	
	

	SimonColliWithMob(coObjects);

	CalcPotentialCollisions(&COOBJECTS/*coObjects*/, coEvents);


	if (coEvents.size() == 0 && !isWalkStair)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		
		if (!isWalkStair)
		{
			x += min_tx * dx + nx * 0.4f;			
			y += min_ty * dy + ny * 0.4f;
		}

		
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Ground *>(e->obj)||dynamic_cast<BreakWall*>(e->obj))
			{
				//DebugOut(L"size: %d\n", coEvents.size());
				//Ground *ground = dynamic_cast<Ground *>(e->obj);

				if (e->ny != 0)
				{
					if (e->ny == -1&&(state!=simon_ani_hurt||(state==simon_ani_hurt&&vy>0)))
					{
						checkgroundmove = false;
						isGrounded = true;
						vy = 0;	
					}
					else
						y += dy;
				}

				if (state == simon_ani_stair_up || state == simon_ani_stair_down)
				{
					if (nx != 0) x -= nx * 0.4f;
				}
			}
			else if (dynamic_cast<Gate*>(e->obj))
			{

				Gate *p = dynamic_cast<Gate*>(e->obj);
				this->nextscene = p->nextscene;
				isChangeScene = true;
				isWalkStair = false;
				//isGrounded = true;//thử
				
			}
			else if(dynamic_cast<GroundMoving*>(e->obj))
			{					
				if (e->ny != 0)
				{
					//DebugOut(L"size: %d\n", e->ny);
					if (e->ny == -1)
					{
						vx = e->obj->vx;
						checkgroundmove = true;
						isGrounded = true;				
						vy = 0;
					}
					//else
						//y += dy;
				}
				/*else
					vx = 0;*/
			}
			//else if (dynamic_cast<Bat*>(e->obj))
			//{
			//	if (untouchtime->IsTimeUp() && state != simon_ani_led && watertime->IsTimeUp())
			//	{
			//		untouchtime->Start();
			//		Bat* bat = dynamic_cast<Bat*>(e->obj);
			//		//batdie = true;
			//		bat->Setcollisimon(true);
			//		bat->SetState(bat_ani_die);
			//		loseHp(bat->getDamage());
			//		//health -= bat->getDamage();

			//		if (isStandOnStair == false || health == 0)
			//		{
			//			if (e->nx != 0)
			//			{
			//				if (e->nx == 1)
			//					SetNx(-1);
			//				else
			//					SetNx(1);
			//			}
			//			SetState(simon_ani_hurt);
			//		}
			//	}
			//	else
			//	{
			//		if (e->ny != 0)
			//			y += dy;
			//		if (e->nx != 0)
			//			x += dx;
			//	}
			//}
			
		}
	}
	

	for (UINT i = 0; i < coEvents.size(); i++) 
		delete coEvents[i];
}

void Simon::Render()
{
	int alpha = simon_alpha_base;
	if (!untouchtime->IsTimeUp())
		alpha = rand() % simon_alpha_base;
	if (!watertime->IsTimeUp() && state != simon_ani_led)
	{
		if ((float)(GetTickCount() - watertime->GetTimeStart()) < simon_one_second)
			alpha = simon_alpha_one_second;
		else if (simon_one_second <= (float)(GetTickCount() - watertime->GetTimeStart()) < simon_two_second)
		{
			alpha = rand() % simon_alpha_one_to_two_second + simon_alpha_random_one_to_two_second;
		}
		else
			alpha = rand() & simon_alpha_random_more_two_second + (simon_alpha_one_to_two_second + simon_alpha_random_one_to_two_second);
	}
	animation_set->at(state)->Render(nx, x, y, alpha);
	
	//RenderBoundingBox();
}


void Simon::SetState(int State)
{
	CGameObject::SetState(State);
	switch (State)
	{
	case simon_ani_run:
		isStandOnStair = false;
		if (nx > 0)
			vx = simon_run;
		else
			vx = -simon_run;
		break;
	case simon_ani_idle:
		//this->StairLeftFirst = false;
		if (!checkgroundmove)
			vx = 0;
		isStandOnStair = false;
		break;
	case simon_ani_jump:
		if (isGrounded)
		{
			if (vx != simon_run && vx != -simon_run)
				vx = 0;
			checkgroundmove = false;
			isGrounded = false;
			vy = simon_jump;
		}
		break;
	case simon_ani_sit:
		isStandOnStair = false;
		if(!checkgroundmove)
			vx = 0;
		break;
	case simon_ani_stand_hit:
		isStandOnStair = false;
		animation_set->at(State)->ResetcurrentFrame();
		animation_set->at(State)->StartAni();
		break;
	case simon_ani_sit_hit:	
		vx = 0;
		isStandOnStair = false;
		animation_set->at(State)->ResetcurrentFrame();
		animation_set->at(State)->StartAni();
		break;
	case simon_ani_led:
		vx = 0;
		isStandOnStair = false;
		animation_set->at(State)->StartAni();
		break;
	case simon_ani_stair_up:
		isGrounded = true;
		isStandOnStair = true;
		if (nx > 0) vx = simon_stair;
		else vx = -simon_stair;
		vy = -simon_stair;
		animation_set->at(State)->ResetcurrentFrame();
		animation_set->at(State)->StartAni();
		break;
	case simon_ani_stair_down:
		isGrounded = true;
		isStandOnStair = true;
		if (nx > 0) vx = simon_stair;
		else vx = -simon_stair;
		vy = simon_stair;
		animation_set->at(State)->ResetcurrentFrame();
		animation_set->at(State)->StartAni();
		break;
	case simon_ani_stair_down_hit:
		vx = vy = 0;
		animation_set->at(State)->ResetcurrentFrame();
		animation_set->at(State)->StartAni();
		break;
	case simon_ani_stair_up_hit:
		vx = vy = 0;
		animation_set->at(State)->ResetcurrentFrame();
		animation_set->at(State)->StartAni();
		break;
	case simon_ani_hurt:
		vy = simon_hurt_vy;
		if (nx > 0) vx = -simon_hurt_vx;
		else vx = simon_hurt_vx;
		animation_set->at(State)->ResetcurrentFrame();
		animation_set->at(State)->StartAni();
		break;
	case simon_ani_dead:
		untouchtime->Stop();
		watertime->Stop();
		vx = 0;
		vy = simon_dead_vy;
		//life -= 1;
		break;
	}

}

void Simon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x+ box_simon_add;
	top = y;
	right = left +simon_box_width;
	bottom = top +simon_box_height;
}

void Simon::SimonColliWithMob(vector<LPGAMEOBJECT> *listmob)
{
	float l_mob, t_mob, r_mob, b_mob, l_simon, t_simon, r_simon, b_simon;
	GetBoundingBox(l_simon, t_simon, r_simon, b_simon);

	for (UINT i = 0; i < listmob->size(); i++)
	{
		LPGAMEOBJECT e = listmob->at(i);
		if (dynamic_cast<Knight*>(e))
		{
			Knight* knight = dynamic_cast<Knight*>(e);
			knight->GetBoundingBox(l_mob, t_mob, r_mob, b_mob);
			if (CGameObject::AABBCheck(l_mob, t_mob, r_mob, b_mob, l_simon, t_simon, r_simon, b_simon) && untouchtime->IsTimeUp() && watertime->IsTimeUp() && state != simon_ani_led && knight->GetState() != knight_ani_die)
			{
				untouchtime->Start();
				loseHp(knight->getDamage());
				if (isStandOnStair == false /*|| health == 0*/)
				{
					if (e->nx != 0)
					{
						if (e->nx == 1)
							SetNx(-1);
						else
							SetNx(1);
					}

					SetState(simon_ani_hurt);
				}

			}

		}
		else if (dynamic_cast<Bat*>(e))
		{
			Bat* bat = dynamic_cast<Bat*>(e);
			bat->GetBoundingBox(l_mob, t_mob, r_mob, b_mob);
			if (CGameObject::AABBCheck(l_mob, t_mob, r_mob, b_mob, l_simon, t_simon, r_simon, b_simon) && untouchtime->IsTimeUp() && watertime->IsTimeUp() && state != simon_ani_led&&bat->GetState()!=bat_ani_die)
			{
				untouchtime->Start();
				loseHp(bat->getDamage());
				bat->Setcollisimon(true);
				bat->SetState(bat_ani_die);
				if (isStandOnStair == false /*|| health == 0*/)
				{
					if (e->nx != 0)
					{
						if (e->nx == 1)
							SetNx(-1);
						else
							SetNx(1);
					}
					SetState(simon_ani_hurt);						
				}
			}
		}
		else if (dynamic_cast<Frog*>(e))
		{
			Frog* frog = dynamic_cast<Frog*>(e);
			frog->GetBoundingBox(l_mob, t_mob, r_mob, b_mob);
			if (CGameObject::AABBCheck(l_mob, t_mob, r_mob, b_mob, l_simon, t_simon, r_simon, b_simon) && untouchtime->IsTimeUp() && watertime->IsTimeUp() && state != simon_ani_led && frog->GetState()!=frog_ani_die &&frog->check)
			{
				untouchtime->Start();
				loseHp(frog->getDamage());
				if (isStandOnStair == false /*|| health == 0*/)
				{
					if (e->nx != 0)
					{
						if (e->nx == 1)
							SetNx(-1);
						else
							SetNx(1);
					}
					SetState(simon_ani_hurt);
				}
			}
		}
		else if (dynamic_cast<Monkey*>(e))
		{
			Monkey* monkey = dynamic_cast<Monkey*>(e);
			monkey->GetBoundingBox(l_mob, t_mob, r_mob, b_mob);
			if (CGameObject::AABBCheck(l_mob, t_mob, r_mob, b_mob, l_simon, t_simon, r_simon, b_simon) && untouchtime->IsTimeUp() && watertime->IsTimeUp() && state != simon_ani_led && monkey->GetState()!=monkey_ani_die)
			{
				untouchtime->Start();
				loseHp(monkey->getDamage());
				if (isStandOnStair == false /*|| health == 0*/)
				{
					if (e->nx != 0)
					{
						if (e->nx == 1)
							SetNx(-1);
						else
							SetNx(1);
					}

					SetState(simon_ani_hurt);
				}
			}
		}
		else if (dynamic_cast<Skeleton*>(e))
		{
			Skeleton* skele = dynamic_cast<Skeleton*>(e);
			skele->GetBoundingBox(l_mob, t_mob, r_mob, b_mob);
			if (CGameObject::AABBCheck(l_mob, t_mob, r_mob, b_mob, l_simon, t_simon, r_simon, b_simon) && untouchtime->IsTimeUp() && watertime->IsTimeUp() && state != simon_ani_led&&skele->GetState()!=skeleton_ani_die)
			{
				untouchtime->Start();
				loseHp(skele->getDamage());
				if (isStandOnStair == false /*|| health == 0*/)
				{
					if (e->nx != 0)
					{
						if (e->nx == 1)
							SetNx(-1);
						else
							SetNx(1);
					}
					SetState(simon_ani_hurt);
				}
			}
		}
		else if (dynamic_cast<Zombie*>(e))
		{
			Zombie* zombie = dynamic_cast<Zombie*>(e);
			zombie->GetBoundingBox(l_mob, t_mob, r_mob, b_mob);
			if (CGameObject::AABBCheck(l_mob, t_mob, r_mob, b_mob, l_simon, t_simon, r_simon, b_simon) && untouchtime->IsTimeUp() && watertime->IsTimeUp() && state != simon_ani_led && zombie->GetState() != zombie_ani_die)
			{
				untouchtime->Start();
				loseHp(zombie->getDamage());
				if (isStandOnStair == false /*|| health == 0*/)
				{
					if (e->nx != 0)
					{
						if (e->nx == 1)
							SetNx(-1);
						else
							SetNx(1);
					}
					SetState(simon_ani_hurt);
				}
			}
		}
		else if (dynamic_cast<Boss*>(e))
		{
			Boss* boss = dynamic_cast<Boss*>(e);
			boss->GetBoundingBox(l_mob, t_mob, r_mob, b_mob);
			if (CGameObject::AABBCheck(l_mob, t_mob, r_mob, b_mob, l_simon, t_simon, r_simon, b_simon) && untouchtime->IsTimeUp() && watertime->IsTimeUp() && state != simon_ani_led && boss->GetState() != boss_ani_die)
			{
				untouchtime->Start();
				loseHp(boss->getDamage());
				if (isStandOnStair == false /*|| health == 0*/)
				{
					if (e->nx != 0)
					{
						if (e->nx == 1)
							SetNx(-1);
						else
							SetNx(1);
					}
					SetState(simon_ani_hurt);
				}
			}
		}
		else if (dynamic_cast<Bone*>(e))
		{
			Bone* bone = dynamic_cast<Bone*>(e);
			bone->GetBoundingBox(l_mob, t_mob, r_mob, b_mob);
			if (CGameObject::AABBCheck(l_mob, t_mob, r_mob, b_mob, l_simon, t_simon, r_simon, b_simon) && untouchtime->IsTimeUp() && watertime->IsTimeUp() && state != simon_ani_led)
			{
				untouchtime->Start();
				loseHp(bone->getDamage());
				if (isStandOnStair == false /*|| health == 0*/)
				{
					if (e->nx != 0)
					{
						if (e->nx == 1)
							SetNx(-1);
						else
							SetNx(1);
					}
					SetState(simon_ani_hurt);
				}
			}
		}
		else if (dynamic_cast<FireBall*>(e))
		{
			FireBall* fireball = dynamic_cast<FireBall*>(e);
			fireball->GetBoundingBox(l_mob, t_mob, r_mob, b_mob);
			if (CGameObject::AABBCheck(l_mob, t_mob, r_mob, b_mob, l_simon, t_simon, r_simon, b_simon) && untouchtime->IsTimeUp() && watertime->IsTimeUp())
			{
				untouchtime->Start();
				loseHp(fireball->getDamage());
				if (isStandOnStair == false)
				{
					if (e->nx != 0)
					{
						if (e->nx == 1)
							SetNx(-1);
						else
							SetNx(1);
					}
					SetState(simon_ani_hurt);
				}
			}

		}
		else if (dynamic_cast<Raven*>(e))
		{
			Raven* raven = dynamic_cast<Raven*>(e);
			raven->GetBoundingBox(l_mob, t_mob, r_mob, b_mob);
			if (CGameObject::AABBCheck(l_mob, t_mob, r_mob, b_mob, l_simon, t_simon, r_simon, b_simon) && untouchtime->IsTimeUp() && watertime->IsTimeUp() && state != simon_ani_led&&raven->GetState()!=raven_ani_die)
			{
				untouchtime->Start();
				raven->Setcollisimon(true);
				raven->SetState(raven_ani_die);
				loseHp(raven->getDamage());
				if (isStandOnStair == false /*|| health == 0*/)
				{
					if (e->nx != 0)
					{
						if (e->nx == 1)
							SetNx(-1);
						else
							SetNx(1);
					}
					SetState(simon_ani_hurt);
				}
			}
		}
	}
}

void Simon::SimonColliWithItems(vector<LPGAMEOBJECT> *listitems)
{
	float l_items, t_items, r_items, b_items, l_simon, t_simon, r_simon, b_simon;
	GetBoundingBox(l_simon, t_simon, r_simon, b_simon);

	for (UINT i = 0; i < listitems->size(); i++)
	{
		LPGAMEOBJECT e = listitems->at(i);
		e->GetBoundingBox(l_items, t_items, r_items, b_items);
		if (CGameObject::AABBCheck(l_simon, t_simon, r_simon, b_simon, l_items, t_items, r_items, b_items))
		{
			if (e->idItems == items_for_whip && !e->isDone)
			{
				SetState(simon_ani_led);
				
				if (whip->GetState() == whip_lv1)
					whip->SetState(whip_lv2);
				else if (whip->GetState() == whip_lv2)
					whip->SetState(whip_lv3);
				e->isDone = true;

			}
			else if (e->idItems == items_big_heart && !e->isDone)
			{
							
				mana += value_big_heart;
				e->isDone = true;
			}
			else if (e->idItems == items_knife && !e->isDone)
			{
				InstallKnife();
				e->isDone = true;
			}
			else if (e->idItems == items_watch && !e->isDone)
			{
				InstallClk();
				e->isDone = true;
				//currentWeapon = weapon_watch;
			}
			else if (e->idItems == items_axe && !e->isDone)
			{
				InstallAxe();			
				e->isDone = true;
			}
			else if (e->idItems == items_boom && !e->isDone)
			{
				InstallBoom();
				e->isDone = true;
			}
			else if (e->idItems == items_holywater && !e->isDone)
			{
				InstallHoly();
				e->isDone = true;
			}
			else if (e->idItems == items_watterbottle && !e->isDone)
			{
				e->isDone = true;
				watertime->Start();
			}
			else if (e->idItems == items_corss && !e->isDone)
			{
				isCross = true;
				e->isDone = true;
			}
			else if (e->idItems == items_double && !e->isDone)
			{
				hitDoubleTriple = 0;
				e->isDone = true;
			}
			else if (e->idItems == items_triple && !e->isDone)
			{
				hitDoubleTriple = 1;
				e->isDone = true;
			}
			else if (e->idItems == items_meat && !e->isDone)
			{
				e->isDone = true;
				health += value_meat;
				if (health >= simon_max_health)
					health = simon_max_health;
			}
			else if (e->idItems == items_small_heart && !e->isDone)
			{
				e->isDone = true;
				mana += value_small_heart;
			}
			else if (e->idItems == items_bluemoney && !e->isDone)
			{
				e->isDone = true;
				score += value_bluemoney;
			}
			else if (e->idItems == items_redmoney && !e->isDone)
			{
				e->isDone = true;
				score += value_redmoney;
			}
			else if (e->idItems == items_whitemoney && !e->isDone)
			{
				e->isDone = true;
				score += value_whitemoney;
			}
			else if (e->idItems == items_crown && !e->isDone)
			{
				e->isDone = true;
				score += value_crown;
			}
			else if (e->idItems == items_boss && !e->isDone)
			{
				e->isDone = true;
				bossdie = true;
			}

		}
		



	}
}

bool Simon::SimonColliWithStair(vector<LPGAMEOBJECT> *liststair)
{
	canmovedownstair = canmoveupstair = false;
	float l_simon, t_simon, r_simon, b_simon;
	GetBoundingBox(l_simon, t_simon, r_simon, b_simon);
	t_simon += simon_t_st; // để không va chạm với cục thang phía trên
	b_simon += simon_b_st;
	r_simon += simon_r_st; //mở rộng vùng va chạm thêm 
	for (UINT i = 0; i < liststair->size(); i++)
	{
		float l_stair, t_stair, r_stair, b_stair;
		liststair->at(i)->GetBoundingBox(l_stair, t_stair, r_stair, b_stair);

		if (CGameObject::AABBCheck(l_simon, t_simon, r_simon, b_simon, l_stair, t_stair, r_stair, b_stair))
		{
			
			stairNx = liststair->at(i)->stairdir;

			stairCollided = liststair->at(i);

			if ((b_simon) < b_stair - sub_distance_down)  canmovedownstair = true;
			if (y >= t_stair - sub_distance_up) canmoveupstair = true;

			float upstair_x = max_distance, upstair_y = max_distance; // toạ độ của bậc thang liền kề

			for (UINT j = 0; j < liststair->size(); j++)
			{
				if (i == j)
					continue;

				liststair->at(j)->GetPosition(upstair_x, upstair_y);

				float dx = abs(upstair_x - l_stair);
				float dy = upstair_y - t_stair;

				if (dx == stair_box_width && dy == -stair_box_height)
					canmoveupstair = true;
				if (dx == stair_box_width && dy == stair_box_height)
					canmovedownstair = true;
			}

			return true; 
		}
	}

	return false;
}

void Simon::AutoWalkStair(float newPosX, int stateAfterAutoWalk, int nxAfterAutoWalk)
{
	this->isWalkStair = true;
	this->newPosX = newPosX;
	this->stateAfterAutoWalk = stateAfterAutoWalk;
	this->nxAfterAutoWalk = nxAfterAutoWalk;
}

void Simon::DoAutoWalkStair()
{
	if (x != newPosX)
	{
		x += dx;
		

		if (state != simon_ani_stair_down)
		{
			y += dy;
		}
		else if(!canmovedownstair)
		{
			if (abs(stairCollided->y - stair_box_height) > (y + dy))
				y += dy;
			else
				y = abs(stairCollided->y - stair_box_height);
			
		}


		if ((nx == 1 && x >= newPosX) || (nx == -1 && x <= newPosX))
		{
			x = newPosX;
			state = stateAfterAutoWalk;
			nx = nxAfterAutoWalk;
			SetState(state);
			
			if (state == simon_ani_stair_down && canmovedownstair)
				y += 2;// để đảm bảo simon sẽ va chạm với bậc thang 
				//y += simon_stari_down_y; // để đảm bảo simon sẽ va chạm với bậc thang 
			
			isWalkStair = false;
		}
	}
}

void Simon::InstallKnife()
{
	listsub.clear();
	currentWeapon = weapon_knfie;
	for (int i = 0; i < max_sub; i++)
		listsub.push_back(knife[i]);
}

void Simon::InstallAxe()
{
	listsub.clear();
	currentWeapon = weapon_axe;
	for (int i = 0; i < max_sub; i++)
		listsub.push_back(axe[i]);
}

void Simon::InstallBoom()
{
	listsub.clear();
	currentWeapon = weapon_boom;
	for (int i = 0; i < max_sub; i++)
		listsub.push_back(boom[i]);
}

void Simon::InstallHoly()
{
	listsub.clear();
	currentWeapon = weapon_holy;
	for (int i = 0; i < max_sub; i++)
		listsub.push_back(holywater[i]);
}

void Simon::InstallClk()
{
	listsub.clear();
	currentWeapon = weapon_watch;
	listsub.push_back(clk);
}
void Simon::StandOnStair()
{
	vx = vy = 0;
}

void Simon::loseHp(int x)
{
	health -= x;
	if (health <= 0)
		health = 0;
}
Simon::~Simon()
{

}
