#include "BreakWall.h"


BreakWall::BreakWall()
{
	isDone = isFire = false;
}

void BreakWall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
}

void BreakWall::Render()
{
	/*for (int i = 0; i < listpiece.size(); i++)
		listpiece[i]->Render();*/


	if (!isDone)
		animation_set->at(state)->Render(-1, x, y);
	else
		return;
}



void BreakWall::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (!isDone)
	{
		left = x;
		top = y;
		right = left + breakwall_width;
		bottom = top + breakwall_height;
	}
}


//Piece* BreakWall::CreatePiece(float x, float y, int type)
//{
//	return new Piece(x, y, type);
//}

BreakWall::~BreakWall()
{
}
