#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Simon.h"
#include "Candle.h"
#include "Whip.h"
#include "Ground.h"
#include "Items.h"
#include "Knife.h"
#include "Hit.h"
#include "TileMap.h"
#include "Gate.h"
#include "Board.h"
#include "Stair.h"
#include "GroundMoving.h"
#include "Knight.h"
#include "Bat.h"
#include "Timer.h"
#include "Monkey.h"
#include "Skeleton.h"
#include "Frog.h"
#include "Raven.h"
#include "BreakWall.h"
#include "SmallCandle.h"
#include "Zombie.h"
#include "Grid.h"
#include "Piece.h"
#include "Boss.h"

#define time_use_cross 500
#define time_revival 2000
#define time_delay_hp 100
#define time_use_clk 4000
#define dis_add_auto_walk 5.0f
#define dis_sub_auto_walk 31.0f
#define dis_down_st_1 4.0f
#define dis_up_st 4.0f
#define dis_sub_auto_walk_up 32.0f

#define first_sub 0
#define sec_sub 1
#define last_sub 2
#define rand_items_max 191
#define min_rand_1 0
#define max_rand_2 30
#define max_rand_3 50
#define max_rand_4 180
#define max_rand_5 60
#define max_rand_6 70
#define max_rand_7 80
#define max_rand_8 90
#define max_rand_9 100

#define max_rand_10 110
#define max_rand_11 120
#define max_rand_12 125
#define max_rand_13 130

#define max_rand_14 135
#define max_rand_15 145
#define max_rand_16 165

#define zombie_drop_item_x 10
#define breakwall_drop_item_y 10
#define breakwall_drop_item_y_crown 80
#define piece_0_x 3
#define piece_1_x_y 10
#define piece_2_x 10
#define piece_2_y 40
#define piece_3_x 5
#define piece_3_y 8
#define skele_drop_item_x 10
#define monkey_drop_item_y 6
#define boss_drop_item_y 40

#define sub_dis_cam_boss 10

#define add_score_time_up 100
#define add_score_time 10
#define time_reset 7000


class CPlayScene : public CScene
{
protected:
	Simon *simon;

	int idstage;
	int current_scene;
	
	TileMap *tilemap;
	Board *board;
	Grid* grid;
	Grid* grididle;
	
	Boss* boss;

	vector<LPGAMEOBJECT> objects;
	
	vector<LPGAMEOBJECT> listitems;
	
	vector<LPGAMEOBJECT> liststairleft;
	vector<LPGAMEOBJECT> liststairright;

	vector<LPGAMEOBJECT> listpush;
	vector<LPGAMEOBJECT> listidle;
	vector<LPGAMEOBJECT> listget;
	
	
	vector<LPPIECE> listpiece;

	void _ParseSection_CLEARTEXTURES(string line);
	void _ParseSection_CLEARSPRITES(string line);
	void _ParseSection_CLERANIMATIONS(string line);
	void _ParseSection_CLERANIMATIONSSET(string line);



	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_LINKMAP(string line);
	void _ParseSection_SETTINGS(string line);
	void _ParseSection_OBJECTS(string line);

	void _ParseSection_LINKOBJECTS(string line);
	void _ParseSection_INFOMAP(string line);

	vector<string> linkmap;

public:
	
	CPlayScene();

	virtual void ClearAll(LPCWSTR a);

	virtual void Load(LPCWSTR sceneFilePath);
	virtual void LoadObject();
	virtual void LoadMap(LPCWSTR map);
	virtual void LoadBaseObject();
	virtual void SwitchScene(int id);
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	Items* DropItem(float x, float y,int id);

	Piece* CreatePiece(float x, float y, int type)
	{
		return new Piece(x, y, type);
	}

	bool CheckInCam(LPGAMEOBJECT a);
	void UseCross();
	void Revival();
	void ResetGame();
	/*void SetDie();*/
	int RandomItems();

	Timer* timecross = new Timer(time_use_cross);
	Timer* timedeadsimon = new Timer(time_revival);
	Timer* timerclk = new Timer(time_use_clk);
	Timer* delayaddhp = new Timer(time_delay_hp);
	Timer* reset = new Timer(time_reset);
	bool checkreset;

	vector<LPGAMEOBJECT> * GetListStairsLeft() { return &(liststairleft); }
	vector<LPGAMEOBJECT> * GetListStairsRight() { return &(liststairright); }

	void GetObjectGrid();
	
	
	friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	void RunRight();
	void RunLeft();
	void Jump();
	void Idle();
	void Sit();
	void Hit();
	void Hit_SubWeapon();

	void Stair_Up();
	void Stair_Down();
	bool Simon_Stair_Stand();
	bool StairCollisionsDetectionLeft();
	bool StairCollisionsDetectionRight();
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

