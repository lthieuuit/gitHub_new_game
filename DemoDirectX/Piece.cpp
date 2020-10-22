#include "Piece.h"



Piece::Piece(float x, float y, int type)
{
	this->x = x;
	this->y = y;
	this->type = type;
	vy = 0;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(piece_aniset));
}

void Piece::Update(DWORD dt)
{
	if (y > piece_y)
		isDone = true;
	if (isDone)
		return;

	switch (type)
	{
	case piece_type_0:
		nx = -1;
		vx = nx * piece_0_vx;
		if (vy == 0)
			vy = piece_vy_up;
		else
			vy += piece_vy_down;
		break;
	case piece_type_1:
		nx = -1;
		vx = nx * piece_1_vx;
		if (vy==0)
			vy = piece_vy_up;
		else
			vy += piece_vy_down;
		break;
	case piece_type_2:
		nx = 1;
		vx = nx * piece_2_vx;
		if (vy == 0)
			vy = piece_vy_up;
		else
			vy += piece_vy_down;
		break;
	case piece_type_3:
		nx = 1;
		vx = nx * piece_3_vx;
		if (vy == 0)
			vy = piece_vy_up;
		else
			vy += piece_vy_down;
		break;
	default:
		break;
	}

	x += vx * dt;
	y += vy * dt;
}

void Piece::Render()
{
	if (!isDone)
	{
		animation_set->at(0)->Render(nx, x, y);
	}
}

Piece::~Piece()
{
}
