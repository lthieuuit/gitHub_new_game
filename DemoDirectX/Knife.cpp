#include "Knife.h"


Knife::Knife()
{
	isDone = true;
	isFire = false;
	SetAnimationSet(CAnimationSets::GetInstance()->Get(knife_ani_set));
}

void Knife::collisionwith(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	aabbmob(coObjects);
	SubWeapon::collisionwith(dt, coObjects);
}

void Knife::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	SubWeapon::Update(dt);
	SubWeapon::ClearListHit();

	if (CheckPosKnife(POSX))
	{
		isFire = false;
		isDone = true;
		return;
	}

	collisionwith(dt, coObjects);
}


void Knife::Render()
{
	if (!isDone && !CheckPosKnife(POSX))
		SubWeapon::Render();

	SubWeapon::renderlisthit();

	//RenderBoundingBox();

}



void Knife::SetV()
{
	//CGameObject::SetState(State);

	if (nx > 0)
		vx = knife_vx;
	else
		vx = -knife_vx;
	vy = 0;
}

void Knife::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (!isDone)
	{
		left = x;
		top = y;
		right = left + 28;//knife_box_width;
		bottom = top + knife_box_height;
	}

}

void Knife::aabbmob(vector<LPGAMEOBJECT>* listmob)
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
				isDone = true;
				isFire = false;
			}
		}
	}
}

void Knife::SetPosSubWeapon(D3DXVECTOR3 pos, bool isstanding)
{
	SubWeapon::SetPosSubWeapon(D3DXVECTOR3(pos.x+5, pos.y, 0), isstanding);
	POSX = pos.x;
}

bool Knife::CheckPosKnife(float a)
{
	if (vx > 0)
	{
		if (x - a >= ((SCREEN_WIDTH / 2) + add_dis_max))
			return true;
	}
	else if (vx < 0)
	{
		if (a - x >= ((SCREEN_WIDTH / 2) + add_dis_max))
			return true;
	}
	return false;
}
Knife::~Knife()
{
}
