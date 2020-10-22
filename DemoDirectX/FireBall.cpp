#include "FireBall.h"



FireBall::FireBall()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(fireball_aniset));
	damage = fireball_damage;
}


void FireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{


	if (!CheckCam())
	{
		checkset = false;
		this->isDone = true;
		return;
	}

	Enemy::Update(dt);
	//vy += bone_gravity * dt;
	x += dx;
	y += dy;

}

void FireBall::Render()
{
	if (!isDone /*&& !CheckCam()*//*!checkposX(POSX)*/)
		animation_set->at(state)->Render(nx, x, y);
	else return;
	//RenderBoundingBox();
}



void FireBall::setspeed(float xs, float ys,int nx,int ny)
{
	float s_temp = sqrt(pow(xs - POSX, 2) + pow(ys - POSY, 2));
	float t = s_temp / v_base;

	vx = (nx*abs(xs - POSX)/t);
	vy = (ny*abs(ys - POSY)/t);
}




void FireBall::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (!isDone)
	{
		l = x;
		t = y;
		r = l + fireball_box_width;
		b = t + fireball_box_height;
	}
}

void FireBall::setpos(D3DXVECTOR2 pos)
{
	SetPosition(pos.x+ add_pos_boss, pos.y+ add_pos_boss);
	POSX = pos.x;
	POSY = pos.y;
}
bool FireBall::CheckCam()
{
	CGame *game = CGame::GetInstance();
	return (x >= (game->GetCamPosX()- add_cam_x) && x < game->GetCamPosX() + (SCREEN_WIDTH+ add_cam_x) && y >= (game->GetCamPosY()- add_cam_y) && y < game->GetCamPosY() + (SCREEN_HEIGHT+ add_cam_y));
}


FireBall::~FireBall()
{
}
