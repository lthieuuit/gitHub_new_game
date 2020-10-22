#include "Bone.h"
#include"Simon.h"


Bone::Bone(float x,float y)
{
	this->x = x;
	this->y = y;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(bone_aniset));
	damage = bone_hp;
	hp = 1;
}


void Bone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{

	
	if (!CheckCam())
	{
		checkset = false;
		this->isDone = true;
		return;
	}

	Enemy::Update(dt);
	vy += bone_gravity * dt;
	x += dx;
	y += dy;
	
}

void Bone::Render()
{
	if (!isDone&&!checkposX(POSX))
		animation_set->at(state)->Render(nx, x, y);
	else return;
	//RenderBoundingBox();
}

void Bone::SetState(int State)
{
	Enemy::SetState(State);
	switch (State)
	{
	case bone_ani_fly:
		if (nx > 0)
			vx = bone_vx;
		else
			vx = -bone_vx;
		vy = bone_vy;
		break;
	default:
		break;
	}
}

bool Bone::checkposX(float a)
{
	if (vx > 0)
	{
		if (x - a >= ((SCREEN_WIDTH / 2) + dis_add))
			return true;
	}
	else if (vx < 0)
	{
		if (a - x >= ((SCREEN_WIDTH / 2) + dis_add))
			return true;
	}
	return false;
}

void Bone::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (!isDone)
	{
		l = x;
		t = y;
		r = l + bone_box_width;
		b = t + bone_box_height;
	}
}

void Bone::setpos(D3DXVECTOR2 pos)
{
	SetPosition(pos.x+ add_dis, pos.y+ add_dis);
	POSX = pos.x;
}
bool Bone::CheckCam()
{
	CGame *game = CGame::GetInstance();
	return (x >= game->GetCamPosX()  && x < game->GetCamPosX() + (SCREEN_WIDTH) && y >= game->GetCamPosY() && y < game->GetCamPosY() + (SCREEN_HEIGHT));
}
Bone::~Bone()
{
}
