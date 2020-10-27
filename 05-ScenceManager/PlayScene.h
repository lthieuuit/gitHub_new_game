#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Simon.h"
#include "Goomba.h"
#include "Koopas.h"

#define RIGHT	1;
#define LEFT	2;

class CPlayScene: public CScene
{
protected: 
	CSimon *simon;					// A play scene has to have player, right? 
	int nx;
	vector<LPGAMEOBJECT> objects;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);

	
public: 
	CPlayScene();

	virtual void Load(LPCWSTR sceneFilePath);
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	int GetNX() { return nx; }
	void SetNX(int _nx) { nx = _nx; }

	CSimon * GetPlayer() { return simon; } 

	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

