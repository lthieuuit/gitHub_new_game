
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Mario.h"
#include "Brick.h"
#include "Goomba.h"
#include "Weapon.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 120

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_WEAPON_RIGHT 30
#define ID_WEAPON_LEFT 35

CGame *game;

CMario *mario;
CGoomba *goomba;
CWeapon* weapon;

vector<LPGAMEOBJECT> objects;
LPANIMATION ani;

CTextures* textures = CTextures::GetInstance();
CSprites* sprites = CSprites::GetInstance();
CAnimations* animations = CAnimations::GetInstance();

class CSampleKeyHander: public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler; 

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_A: // reset
		mario->SetState(MARIO_STATE_IDLE);
		mario->SetLevel(MARIO_LEVEL_BIG);
		mario->SetPosition(50.0f,0.0f);
		mario->SetSpeed(0, 0);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_DOWN);
		break;
	case DIK_X:
		mario->SetState(STATE_ATTACK);
		weapon->UpdatePosionWithSimon(mario->x, mario->y, mario->nx);
		weapon->SetState(WEAPON_STATE_ATTACK);
		break;
	case DIK_2 :
		weapon->SetLevel(2);
		break;
	case DIK_3:
		weapon->SetLevel(3);
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	// disable control key when Mario die 
	if (mario->GetState() == MARIO_STATE_DIE) return;
	if (!mario->GetAttack()) {
		if (game->IsKeyDown(DIK_RIGHT))
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
		else if (game->IsKeyDown(DIK_LEFT))
			mario->SetState(MARIO_STATE_WALKING_LEFT);
		else
			mario->SetState(MARIO_STATE_IDLE);
	}
	
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void InitSimon() {

	textures->Add(ID_TEX_MARIO, L"textures\\simon.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	// sprite for simmon
	LPDIRECT3DTEXTURE9 texMario = textures->Get(ID_TEX_MARIO);
	sprites->Add(101, 163, 41, 180, 71, texMario);		// idle right
	sprites->Add(102, 205, 41, 218, 71, texMario);		// walk
	sprites->Add(103, 244, 41, 259, 71, texMario);
	sprites->Add(104, 283, 44, 300, 67, texMario);		//sit

	sprites->Add(105, 160, 201, 184, 231, texMario);		//attact right
	sprites->Add(106, 204, 201, 220, 231, texMario);
	sprites->Add(107, 241, 201, 263, 231, texMario);

	sprites->Add(108, 163, 278, 188, 303, texMario);		//attact sit
	sprites->Add(109, 211, 284, 228, 307, texMario);
	sprites->Add(110, 249, 284, 272, 307, texMario);


	sprites->Add(111, 124, 41, 139, 71, texMario);		// idle left
	sprites->Add(112, 85, 41, 98, 71, texMario);			// walk
	sprites->Add(113, 44, 41, 59, 71, texMario);
	sprites->Add(114, 3, 44, 20, 67, texMario);			//sit

	sprites->Add(115, 120, 201, 144, 231, texMario);		//attact left
	sprites->Add(116, 84, 201, 100, 231, texMario);
	sprites->Add(117, 41, 201, 63, 231, texMario);

	sprites->Add(118, 116, 280, 148, 311, texMario);		//attact sit
	sprites->Add(119, 76, 284, 108, 307, texMario);
	sprites->Add(120, 10, 285, 54, 307, texMario);

	sprites->Add(121, 235, 7, 268, 23, texMario);			// die 

	// animation for simon

	ani = new CAnimation(100);	// idle big right
	ani->Add(101);
	animations->Add(400, ani);

	ani = new CAnimation(100);	// idle big left
	ani->Add(111);
	animations->Add(401, ani);

	ani = new CAnimation(100);	// walk right big
	ani->Add(101);
	ani->Add(102);
	ani->Add(103);
	animations->Add(402, ani);

	ani = new CAnimation(100);	// // walk left big
	ani->Add(111);
	ani->Add(112);
	ani->Add(113);
	animations->Add(403, ani);

	ani = new CAnimation(100);		// Mario sit right
	ani->Add(104);
	animations->Add(406, ani);

	ani = new CAnimation(100);		// Mario sit right
	ani->Add(114);
	animations->Add(407, ani);

	ani = new CAnimation(100);	// attact right
	ani->Add(105,200);
	ani->Add(106);
	ani->Add(107,200);
	ani->Add(101);
	animations->Add(408, ani);

	ani = new CAnimation(100);	// attact left
	ani->Add(115,200);
	ani->Add(116);
	ani->Add(117,200);
	ani->Add(111);
	animations->Add(409, ani);

	ani = new CAnimation(100);	// attact sit right
	ani->Add(108);
	ani->Add(109);
	ani->Add(110);
	animations->Add(410, ani);

	ani = new CAnimation(100);	// attact sit left
	ani->Add(118);
	ani->Add(119);
	ani->Add(120);
	animations->Add(411, ani);

	ani = new CAnimation(100);		// Mario die
	ani->Add(121);
	animations->Add(499, ani);

	mario = new CMario();
	mario->AddAnimation(400);		// idle right big
	mario->AddAnimation(401);		// idle left big

	mario->AddAnimation(402);		// walk right big
	mario->AddAnimation(403);		// walk left big

	mario->AddAnimation(406);		// sit right
	mario->AddAnimation(407);		//	sit left

	mario->AddAnimation(408);		// attact right
	mario->AddAnimation(409);		//	attact left

	mario->AddAnimation(410);		// attact sit right
	mario->AddAnimation(411);		//	attact sit left
	mario->AddAnimation(499);		// die


	mario->SetPosition(0, 0);
	objects.push_back(mario);

}

void InitBrick(){

	textures->Add(ID_TEX_MISC, L"textures\\misc.png", D3DCOLOR_XRGB(255, 255, 255));
	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);

	sprites->Add(20001, 354, 171, 370, 187, texMisc);

	ani = new CAnimation(100);
	ani->Add(20001);
	animations->Add(601, ani);

	for (int i = 0; i < 20; i++)
	{
		CBrick* brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(0 + i * 16.0f, 170);
		objects.push_back(brick);
	}
}

void InitWeapon() {
	textures->Add(ID_WEAPON_RIGHT, L"textures\\weapon.png", D3DCOLOR_XRGB(255, 255, 255));
	weapon = new CWeapon();
	LPDIRECT3DTEXTURE9 texWeapon = textures->Get(ID_WEAPON_RIGHT);
	sprites->Add(701, 0, 2, 9, 27, texWeapon);		//level 1
	sprites->Add(702, 19, 0, 37, 20, texWeapon);		
	sprites->Add(703, 45, 1, 71, 9, texWeapon);

	sprites->Add(704, 0, 32, 9, 58, texWeapon);		//level 2
	sprites->Add(705, 19, 59, 57, 80, texWeapon);
	sprites->Add(706, 45, 35, 72, 48, texWeapon);

	sprites->Add(707, 0, 62, 9, 88, texWeapon);		//level 3
	sprites->Add(708, 19, 0, 37, 20, texWeapon);
	sprites->Add(709, 45, 63, 85, 72, texWeapon);

	ani = new CAnimation(100);
	ani->Add(701,200);
	ani->Add(702);
	ani->Add(703,200);
	animations->Add(710, ani);
	weapon->AddAnimation(710);

	ani = new CAnimation(100);
	ani->Add(704, 200);
	ani->Add(705);
	ani->Add(706, 200);
	animations->Add(711, ani);
	weapon->AddAnimation(711);

	ani = new CAnimation(100);
	ani->Add(707, 200);
	ani->Add(708);
	ani->Add(709, 200);
	animations->Add(712, ani);
	weapon->AddAnimation(712);


	textures->Add(ID_WEAPON_LEFT, L"textures\\weapon2.png", D3DCOLOR_XRGB(255, 255, 255));

	LPDIRECT3DTEXTURE9 texWeaponLeft = textures->Get(ID_WEAPON_LEFT);
	sprites->Add(713, 76, 2, 87, 29, texWeaponLeft);		//level 1
	sprites->Add(714, 49, 0, 67, 20, texWeaponLeft);
	sprites->Add(715, 15, 1, 40, 11, texWeaponLeft);

	sprites->Add(716, 77, 32, 87, 58, texWeaponLeft);		//level 2
	sprites->Add(717, 49, 31, 67, 50, texWeaponLeft);
	sprites->Add(718, 15, 34, 40, 42, texWeaponLeft);

	sprites->Add(719, 77, 62, 87, 88, texWeaponLeft);		//level 3
	sprites->Add(720, 49, 58, 67, 80, texWeaponLeft);
	sprites->Add(721, 0, 64, 40, 72, texWeaponLeft);

	ani = new CAnimation(100);
	ani->Add(713, 200);
	ani->Add(714);
	ani->Add(715, 200);
	animations->Add(722, ani);
	weapon->AddAnimation(722);

	ani = new CAnimation(100);
	ani->Add(716, 200);
	ani->Add(717);
	ani->Add(718, 200);
	animations->Add(723, ani);
	weapon->AddAnimation(723);

	ani = new CAnimation(100);
	ani->Add(719, 200);
	ani->Add(720);
	ani->Add(721, 200);
	animations->Add(724, ani);
	weapon->AddAnimation(724);

	objects.push_back(weapon);
}
 
void LoadResources()
{
	InitSimon();
	InitWeapon();
	InitBrick();
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt,&coObjects);
	}


	// Update camera to follow mario
	float cx, cy;
	mario->GetPosition(cx, cy);

	
	cx -= SCREEN_WIDTH / 2 ;
	cy -= SCREEN_HEIGHT / 2;

	CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
}

/*
	Render a frame 
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT*2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}