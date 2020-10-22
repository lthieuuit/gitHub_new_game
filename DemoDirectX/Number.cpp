#include "Number.h"



Number::Number()
{
}

void Number::Render(float x, float y, string &a)
{
	for (UINT i = 0; i < a.size(); i++)
	{
		if (a[i] == ' ')
			continue;

		if (a[i] == '0')
		{
			num = CSprites::GetInstance()->Get(sprite_0);
		}
		else if (a[i] == '1')
		{
			num = CSprites::GetInstance()->Get(sprite_1);
		}
		else if (a[i] == '2')
		{
			num = CSprites::GetInstance()->Get(sprite_2);
		}
		else if (a[i] == '3')
		{
			num = CSprites::GetInstance()->Get(sprite_3);
		}
		else if (a[i] == '4')
		{
			num = CSprites::GetInstance()->Get(sprite_4);
		}
		else if (a[i] == '5')
		{
			num= CSprites::GetInstance()->Get(sprite_5);
		}
		else if (a[i] == '6')
		{
			num = CSprites::GetInstance()->Get(sprite_6);
		}
		else if (a[i] == '7')
		{
			num = CSprites::GetInstance()->Get(sprite_7);
		}
		else if (a[i] == '8')
		{
			num = CSprites::GetInstance()->Get(sprite_8);
		}
		else if (a[i] == '9')
		{
			num = CSprites::GetInstance()->Get(sprite_9);
		}
		num->Draw(-1, x + (i * 15), y);
	}
}


Number::~Number()
{
}
