#include "Board.h"



Board::Board(int HealSimon,int HealBoss)
{
	//board = CAnimations::GetInstance()->Get(board_ani);
	board = CAnimationSets::GetInstance()->Get(board_ani_set);
	//board = CSprites::GetInstance()->Get(board_sprite);
	healsimon = new HealthBar(HealSimon);
	heallost = new HealthBar(max_heal);
	healboss = new HealthBar(HealBoss);

	subweapon.push_back(CSprites::GetInstance()->Get(sprite_knife));
	subweapon.push_back(CSprites::GetInstance()->Get(sprite_watch));
	subweapon.push_back(CSprites::GetInstance()->Get(sprite_axe));
	subweapon.push_back(CSprites::GetInstance()->Get(sprite_boom));
	subweapon.push_back(CSprites::GetInstance()->Get(sprite_holy));


	doubletriple.push_back(CSprites::GetInstance()->Get(sprite_double));
	doubletriple.push_back(CSprites::GetInstance()->Get(sprite_triple));

	timemax = def_time_max;
	time = 0;
}



void Board::Update(DWORD a,int currenhealsimon,int currenthealboss)
{
	//this->posx = x;
	//this->posy = y;
	healsimon->Update(currenhealsimon);
	heallost->Update(max_heal);
	healboss->Update(currenthealboss);

	time += a;
	timeremain = timemax - (time / CLOCKS_PER_SEC);

	if (timeremain <= 0)
	{
		timeremain = 0;
		checktime = true;
	}
}

string Board::FillNumber(string s, UINT maxnumb)
{
	while (s.size() < maxnumb)
		s = "0" + s;
	return s;
}

void Board::Render(int idmap,int camx,int camy,Simon* simon)
{

	

	//this->posx = camx;
	//this->posy = camy;
	//board->Render(-1,posx,posy);
	board->at(board_ani)->Render(-1, camx, camy);
	heallost->Render(lose_heal,camx,camy);
	//board->Draw(-1, posx, posy);
	healsimon->Render(simon_heal, camx, camy);
	healboss->Render(boss_heal, camx, camy);


	if (simon->hitDoubleTriple != -1)
	{
		doubletriple[simon->hitDoubleTriple]->Draw(-1, camx + add_x_doutriple, camy + add_y_doutriple);
	}

	

	if (simon->getcurrentweapon() !=-1)
	{
		if (simon->getcurrentweapon() == weapon_boom)
			subweapon[simon->getcurrentweapon()]->Draw(-1, camx + add_x_sub, camy + add_y_boom);
		else if (simon->getcurrentweapon() == weapon_holy || simon->getcurrentweapon() == weapon_axe)
			subweapon[simon->getcurrentweapon()]->Draw(-1, camx + add_x_sub, camy + add_y_holy_axe);
		else if(simon->currentWeapon== weapon_watch)
			subweapon[simon->getcurrentweapon()]->Draw(-1, camx + add_x_sub, camy + add_y_watch);
		else
			subweapon[simon->getcurrentweapon()]->Draw(-1, camx + add_x1_sub, camy + add_y_knife);
	}

	numb.Render(camx + add_x_time, camy + add_y_time, FillNumber(to_string(timeremain), max_num_time));
	numb.Render(camx + add_x_score, camy + add_y_score, FillNumber(to_string(simon->getscore()), max_num_score));
	numb.Render(camx + add_x_mana, camy + add_y_mana, FillNumber(to_string(simon->getmana()), max_num_mana));
	numb.Render(camx + add_x_stage, camy + add_y_stage, FillNumber(to_string(idmap), max_num_stage));
	numb.Render(camx + add_x_life, camy + add_y_life, FillNumber(to_string(simon->getlife()), max_num_life));
	
}

Board::~Board()
{
}
