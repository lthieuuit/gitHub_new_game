#pragma once
#include"Sprites.h"
#include"Textures.h"
#define sprite_0 129
#define sprite_1 130
#define sprite_2 131
#define sprite_3 132
#define sprite_4 133
#define sprite_5 134
#define sprite_6 135
#define sprite_7 136
#define sprite_8 137
#define sprite_9 138
class Number
{
	LPSPRITE num;
public:
	void Render(float x, float y, string &a);
	Number();
	~Number();
};

