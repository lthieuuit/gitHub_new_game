#pragma once
#include"GameObject.h"
#define piece_aniset 300
#define piece_y 500

#define piece_type_0 0
#define piece_type_1 1
#define piece_type_2 2
#define piece_type_3 3

#define piece_vy_up -0.14
#define piece_vy_down 0.02

#define piece_0_vx 0.12
#define piece_1_vx 0.12
#define piece_2_vx 0.15
#define piece_3_vx 0.13

class Piece;
typedef Piece* LPPIECE;
class Piece : public CGameObject
{
	int type;
	float x, y;
public:
	Piece(float x, float y, int type);
	void Render();
	void Update(DWORD dt);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) { left = top; right = bottom; }
	~Piece();
};

