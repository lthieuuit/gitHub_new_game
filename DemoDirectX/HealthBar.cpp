#include "HealthBar.h"


HealthBar::HealthBar(int heal)
{
	//healthbar = CAnimations::GetInstance()->Get(board_ani);
	currenthealth = heal;
	maxhealth = max_heal;
	for (int i = 0; i < maxhealth; i++)
	{
		healthbar.push_back(CAnimationSets::GetInstance()->Get(healthbar_ani_set));
	}
	// = CAnimationSets::GetInstance()->Get(9);
	//this->healthsimon = healthsimon;
}
void HealthBar::Update(int currenthealth/*,float x,float y*/)
{
	this->currenthealth = currenthealth;
	/*this->posx = x;
	this->posy = y;*/

}

void HealthBar::Render(int state,int camx,int camy)
{
	if (currenthealth <= 0)
		return;
	else
	{
		if (state == simon_heal)
		{
			for (int i = 0; i < currenthealth; i++)
			{
				healthbar[i]->at(0)->Render(-1, 108 + i * 9 + camx, 31);
			}
		}
		else if (state == lose_heal)
		{
			//if (healthsimon)
			{
				for (int i = 0; i < maxhealth; i++)
				{
					healthbar[i]->at(1)->Render(-1, 108 + i * 9 + camx, 31);
				}
			}
			//else
			{
				for (int i = 0; i < maxhealth; i++)
				{
					healthbar[i]->at(state)->Render(-1, 108 + i * 9 + camx, 47);
				}
			}
		}
		else if (state == boss_heal)
		{
			for (int i = 0; i < currenthealth; i++)
			{
				healthbar[i]->at(state)->Render(-1, 108 + i * 9 + camx, 47);
			}
		}
	}
	
}
HealthBar::~HealthBar()
{
}
