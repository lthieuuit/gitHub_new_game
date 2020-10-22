#include "Whip.h"
#include"Candle.h"

Whip::Whip()
{
	
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(whip_ani_set));//truyền tất cả animation của whip vào


	state = whip_lv1;
}
void Whip::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

		for (UINT i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT obj = coObjects->at(i);

			if (dynamic_cast<Candle*>(obj))
			{
				Candle * e = dynamic_cast<Candle*>(obj);

				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);

				if (WhipCheckColli(left, top, right, bottom))
				{
					if(e->GetState()!=break_candle)
						listHit.push_back(CreateHit(e->GetPositionX(), e->GetPositionY() + 10));
					e->SetState(break_candle);			
					
				}

			}
			else if (dynamic_cast<Knight*>(obj))
			{
				Knight * e = dynamic_cast<Knight*>(obj);
				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);

				if (WhipCheckColli(left, top, right, bottom))
				{						
					if (!delaydamage)
					{			
						e->timestop = GetTickCount();
						e->vx = 0;
						if (state == whip_lv1)
							e->loseHp(whip_dame1);
						else
							e->loseHp(whip_dame2);
						delaydamage = true;
					}
					

					if (e->GetState() != knight_ani_die)
						listHit.push_back(CreateHit(e->GetPositionX(), e->GetPositionY() + 10));
					
					if (e->getHp() <= 0)
					{
						//score += e->getScore();
						e->SetState(knight_ani_die);
					}

				}
			}
			else if (dynamic_cast<Bat*>(obj))
			{
				Bat * e = dynamic_cast<Bat*>(obj);

				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);

				if (WhipCheckColli(left, top, right, bottom))
				{
					e->loseHp(whip_dame1);

					if (e->GetState() != bat_ani_die )
						listHit.push_back(CreateHit(e->GetPositionX(), e->GetPositionY() + 10));

					if (e->getHp() <= 0)
					{
						//score += e->getScore();
						e->SetState(bat_ani_die);
					}

				}
			}
			else if (dynamic_cast<Monkey*>(obj))
			{
				Monkey * e = dynamic_cast<Monkey*>(obj);

				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);

				if (WhipCheckColli(left, top, right, bottom))
				{
					e->loseHp(whip_dame1);
					if (e->GetState() != monkey_ani_die)
						listHit.push_back(CreateHit(e->GetPositionX(), e->GetPositionY() + 10));

					if (e->getHp() <= 0)
					{
						//score += e->getScore();
						e->SetState(monkey_ani_die);
					}
				}
			}
			else if (dynamic_cast<Frog*>(obj))
			{
				Frog * e = dynamic_cast<Frog*>(obj);

				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);

				if (WhipCheckColli(left, top, right, bottom)&&e->check)
				{
					if (!delaydamage)
					{
						e->timestop = GetTickCount();
						e->vx = e->vy = 0;


						if (state == whip_lv1)
							e->loseHp(whip_dame1);
						else
							e->loseHp(whip_dame2);
						delaydamage = true;
					}

					if (e->GetState() != frog_ani_die)
						listHit.push_back(CreateHit(e->GetPositionX(), e->GetPositionY() + 10));

					if (e->getHp() <= 0)
					{
						//score += e->getScore();
						e->SetState(frog_ani_die);
					}

				}
			}
			else if (dynamic_cast<Skeleton*>(obj))
			{
				Skeleton * e = dynamic_cast<Skeleton*>(obj);

				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);

				if (WhipCheckColli(left, top, right, bottom))
				{
					e->loseHp(whip_dame1);
					if (e->GetState() != skeleton_ani_die)
						listHit.push_back(CreateHit(e->GetPositionX(), e->GetPositionY() + 10));

					if (e->getHp() <= 0)
					{
						//score += e->getScore();
						e->SetState(skeleton_ani_die);
					}
				}
			}
			else if (dynamic_cast<Raven*>(obj))
			{
				Raven * e = dynamic_cast<Raven*>(obj);

				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);

				if (WhipCheckColli(left, top, right, bottom))
				{
					e->loseHp(whip_dame1);

					if (e->GetState() != raven_ani_die )
						listHit.push_back(CreateHit(e->GetPositionX(), e->GetPositionY() + 10));

					if (e->getHp() <= 0)
					{
						//score += e->getScore();
						e->SetState(raven_ani_die);
					}

				}
			}
			else if (dynamic_cast<BreakWall*>(obj))
			{
				BreakWall*e = dynamic_cast<BreakWall*>(obj);
				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);
				if (WhipCheckColli(left, top, right, bottom))
				{
					e->isDone = true;
				}

			}
			else if (dynamic_cast<SmallCandle*>(obj))
			{
				SmallCandle * e = dynamic_cast<SmallCandle*>(obj);

				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);

				if (WhipCheckColli(left, top, right, bottom))
				{
					if (e->GetState() != break_candle)
						listHit.push_back(CreateHit(e->GetPositionX(), e->GetPositionY() + 10));
					e->SetState(break_candle);

				}

			}
			else if (dynamic_cast<Zombie*>(obj))
			{
				Zombie * e = dynamic_cast<Zombie*>(obj);

				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);

				if (WhipCheckColli(left, top, right, bottom))
				{
					e->loseHp(whip_dame1);
					e->colliwhip = true;
					if (e->GetState() != zombie_ani_die )
						listHit.push_back(CreateHit(e->GetPositionX(), e->GetPositionY() + 10));

					if (e->getHp() <= 0)
					{
						e->SetState(zombie_ani_die);
					}

				}
			}
			else if (dynamic_cast<Boss*>(obj))
			{
				Boss * e = dynamic_cast<Boss*>(obj);
				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);

				if (WhipCheckColli(left, top, right, bottom))
				{						
					if (!delaydamage)
					{			
						//e->timestop = GetTickCount();
						//e->vx = 0;
						if (state == whip_lv1)
							e->loseHp(whip_dame1);
						else
							e->loseHp(whip_dame2);
						delaydamage = true;
					}
					

					if (e->GetState() != 2)
						listHit.push_back(CreateHit(e->GetPositionX()+20, e->GetPositionY() + 10));
					
					if (e->getHp() <= 0)
					{
	
						e->SetState(2);
					}

				}
			}
			
		}
		

		/*for (int i = 0; i < listHit.size(); i++)
		{
			if (listHit[i]->timedestroy())
				listHit.erase(listHit.begin() + i);
		}*/
		//DebugOut(L" SO PHAN TU TRONG LISTHIT %d \n", listHit.size());
}

void Whip::Render(int currentID)
{
	for (int i = 0; i < listHit.size(); i++)
	{

		listHit[i]->Render();
	
	}

	if (currentID >= 0)		
	{
		animation_set->at(state)->RenderWhip(currentID, nx, x, y);

	}
	

	
	//RenderBoundingBox();
}

void Whip::Render()
{
	
}

void Whip::SetPosWhip(D3DXVECTOR3 pos, bool isstanding)
{
	pos.x -= pos_whip_x;
	if (!isstanding)
		pos.y += pos_whip_y;
	SetPosition(pos.x, pos.y);
}
Hit* Whip::CreateHit(float x, float y)
{
	return new Hit(x, y);
}

bool Whip::WhipCheckColli(float l_b, float t_b, float r_b, float b_b)
{
	float l_whip, t_whip, r_whip, b_whip;
	GetBoundingBox(l_whip, t_whip, r_whip, b_whip);

	if (CGameObject::AABBCheck(l_whip, t_whip, r_whip, b_whip, l_b, t_b, r_b, b_b))
		return true;
	else
		return false;
}

void Whip::GetBoundingBox(float &l, float &t, float &r, float &b)
{

	t = y + pos_whip_y;
	b = t + whip_box_height;
	if (nx < 0)
	{
		if (state == whip_lv3)
			l = x + pos_whip_lv3;
		else
			l = x + pos_whip_lv1_2;
	}
	else if (nx > 0)
	{
		if (state == whip_lv3)
			l = x + pos_whip_lv3_2_1_left;
		else
			l = x + pos_whip_lv3_2_1_left;
	}

	if (state == whip_lv3)
		r = l + whip_box_width_lv3;
	else
		r = l + whip_box_width_lv12;
}



Whip::~Whip()
{
}
