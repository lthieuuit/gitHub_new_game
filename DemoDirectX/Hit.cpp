#include "Hit.h"



Hit::Hit(float x,float y)
{
	this->x = x;
	this->y = y;
	timestart = -1;
	//hit = CAnimations::GetInstance()->Get(hit_ani);
	hit = CAnimationSets::GetInstance()->Get(hit_ani_set);
	//hit = CSprites::GetInstance()->Get(hit_sprite);
}

bool Hit::timedestroy()
{
	if (timestart == -1)
		timestart = GetTickCount();
	else
	{
		if (GetTickCount() - timestart > time_hit_des)
		{
			return true;
		}

	}
	return false;
}

void Hit::Render()
{
	if (!timedestroy())
		//hit->Draw(1, x, y);
		hit->at(hit_ani)->Render(1, x, y);
		//hit->Render(1, x, y);
	
}
Hit::~Hit()
{
}
