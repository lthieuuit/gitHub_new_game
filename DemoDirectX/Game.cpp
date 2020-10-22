#include <iostream>
#include <fstream>

#include "Game.h"
#include "Utils.h"

#include "PlayScence.h"

CGame * CGame::__instance = NULL;

/*
	Initialize DirectX, create a Direct3D device for rendering within the window, initial Sprite library for
	rendering 2D images
	- hInst: Application instance handle
	- hWnd: Application window handle
*/
void CGame::Init(HWND hWnd)
{
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	this->hWnd = hWnd;

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(hWnd, &r);	// retrieve Window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;


	screen_height = r.bottom + 1;
	screen_width = r.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	if (d3ddv == NULL)
	{
		OutputDebugString(L"[ERROR] CreateDevice failed\n");
		return;
	}

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(d3ddv, &spriteHandler);

	OutputDebugString(L"[INFO] InitGame done;\n");
}

/*
	Utility function to wrap LPD3DXSPRITE::Draw
*/
void CGame::Draw(int nx,float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha)
{

	//D3DXVECTOR3 p(floor(x), floor(y), 0); // https://docs.microsoft.com/vi-vn/windows/desktop/direct3d9/directly-mapping-texels-to-pixels
	// Try removing floor() to see blurry Mario
	D3DXVECTOR3 p(floor(x - cam_x), floor(y - cam_y), 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;

	D3DXMATRIX oldtrans;
	D3DXMATRIX newtrans;

	D3DXVECTOR2 pheplat;
	if (nx > 0)
	{
		pheplat = D3DXVECTOR2(-1, 1);
	}
	else
	{
		pheplat = D3DXVECTOR2(1, 1);
	}

	D3DXVECTOR2 scale = D3DXVECTOR2(p.x + (right - left) / 2, p.y + (bottom - top) / 2);

	D3DXMatrixTransformation2D(&newtrans, &scale, 0, &pheplat, NULL, 0, NULL);
	spriteHandler->GetTransform(&oldtrans);
	spriteHandler->SetTransform(&newtrans);


	spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));

	spriteHandler->SetTransform(&oldtrans);
}

int CGame::IsKeyDown(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80) > 0;
}

void CGame::InitKeyboard()
{
	HRESULT
		hr = DirectInput8Create
		(
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&di, NULL
		);

	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DirectInput8Create failed!\n");
		return;
	}

	hr = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);

	// TO-DO: put in exception handling
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] CreateDevice failed!\n");
		return;
	}

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = didv->SetDataFormat(&c_dfDIKeyboard);

	hr = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);


	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = didv->Acquire();
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DINPUT8::Acquire failed!\n");
		return;
	}

	DebugOut(L"[INFO] Keyboard has been initialized successfully\n");
}

void CGame::ProcessKeyboard()
{
	HRESULT hr;

	// Collect all key states first
	hr = didv->GetDeviceState(sizeof(keyStates), keyStates);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = didv->Acquire();
			if (h == DI_OK)
			{
				DebugOut(L"[INFO] Keyboard re-acquired!\n");
			}
			else return;
		}
		else
		{
			//DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
			return;
		}
	}

	keyHandler->KeyState((BYTE *)&keyStates);



	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		//DebugOut(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hr);
		return;
	}

	// Scan through all buffered events, check if the key is pressed or released

	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			keyHandler->OnKeyDown(KeyCode);
		else
			keyHandler->OnKeyUp(KeyCode);
	}

}

CGame::~CGame()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
}

/*
	SweptAABB
*/
void CGame::SweptAABB(
	float ml, float mt, float mr, float mb,
	float dx, float dy,			 //dx và dy là khoảng cách giữa 2 vật
	float sl, float st, float sr, float sb,
	float &t, float &nx, float &ny)     // nx,ny là vector pháp tuyến trên bề mặt tiếp xúc (Ox,Oy)
{

	float dx_entry, dx_exit, tx_entry, tx_exit;   //dxentry khoảng cách gần nhất của 2 vật thể theo hướng Ox
	float dy_entry, dy_exit, ty_entry, ty_exit;   //dx_exit khoảng cách xa nhất của 2 vật thể theo hướng Ox
												  //tx_entry là thời gian 2 trục x va chạm
												  //tx_exit là thời gian 2 trục thoát ra khỏi nhau

	float t_entry;
	float t_exit;

	t = -1.0f;			// no collision
	nx = ny = 0;

	//
	// Broad-phase test 
	//

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;

	if (br < sl || bl > sr || bb < st || bt > sb)
		return;


	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

	/*Chú ý: Vận tốc của vật trong chương này là khoảng cách vật di chuyển
	trong 1 frame: có được bằng cách nhân vận tốc tính trên giây với
	khoảng thời gian giữa các frame (delta time)      CHÍNH LÀ DX VÀ DY */

	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}


	if (dy > 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy < 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}


	if (dx == 0)
	{
		tx_entry = -99999999999;
		tx_exit = 99999999999;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -99999999999;
		ty_exit = 99999999999;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}

	//tx_entry ,ty_entry sẽ cho ta biết khi nào sẽ bắt đầu va chạm
	//tx_exit  ,ty_exit exitTime sẽ cho ta	biết khi nào kết thúc va chạm
	/*Nếu thời gian va chạm
		không nằm từ 0 đến 1, thì nó sẽ không va chạm trong frame hiện
		tại*/
	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	//Để xảy ra va chạm, cả hai trục x và y phải ĐỒNG THỜI XẢY RA VA CHẠM, vậy mình lấy thời gian bắt để bắt đầu va chạm lớn nhất
	t_entry = max(tx_entry, ty_entry);

	//Còn khi hết va chạm chỉ cần 1 trong 2 trục thoát khỏi là được, nên mình lấy thời gian kết thúc va chạm nhỏ nhất giữa 2 trục x, y
	t_exit = min(tx_exit, ty_exit);


	//thời gian khi vật bắt đầu va chạm sẽ ko bao giờ xảy ra sau khi vật kết thúc va chạm
	if (t_entry > t_exit) return;

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}
}

CGame *CGame::GetInstance()
{
	if (__instance == NULL) __instance = new CGame();
	return __instance;
}



//#define MAX_GAME_LINE 1024
//
//
//#define GAME_FILE_SECTION_UNKNOWN -1
//#define GAME_FILE_SECTION_SETTINGS 1
//#define GAME_FILE_SECTION_SCENES 2
//
//void CGame::_ParseSection_SETTINGS(string line)
//{
//	vector<string> tokens = split(line);
//
//	if (tokens.size() < 2) return;
//	if (tokens[0] == "start")
//		current_scene = atoi(tokens[1].c_str());
//	else
//		DebugOut(L"[ERROR] Unknown game setting %s\n", ToWSTR(tokens[0]).c_str());
//}
//
//void CGame::_ParseSection_SCENES(string line)
//{
//	vector<string> tokens = split(line);
//
//	if (tokens.size() < 2) return;
//	int id = atoi(tokens[0].c_str());
//	LPCWSTR path = ToLPCWSTR(tokens[1]);
//
//	LPSCENE scene = new CPlayScene(id, path);
//	scenes[id] = scene;
//}
//
///*
//	Load game campaign file and load/initiate first scene
//*/
//void CGame::Load(LPCWSTR gameFile)
//{
//	DebugOut(L"[INFO] Start loading game file : %s\n", gameFile);
//
//	ifstream f;
//	f.open(gameFile);
//	char str[MAX_GAME_LINE];
//
//	// current resource section flag
//	int section = GAME_FILE_SECTION_UNKNOWN;
//
//	while (f.getline(str, MAX_GAME_LINE))
//	{
//		string line(str);
//
//		if (line[0] == '#') continue;	// skip comment lines	
//
//		if (line == "[SETTINGS]") { section = GAME_FILE_SECTION_SETTINGS; continue; }
//		if (line == "[SCENES]") { section = GAME_FILE_SECTION_SCENES; continue; }
//
//		//
//		// data section
//		//
//		switch (section)
//		{
//		case GAME_FILE_SECTION_SETTINGS: _ParseSection_SETTINGS(line); break;
//		case GAME_FILE_SECTION_SCENES: _ParseSection_SCENES(line); break;
//		}
//	}
//	f.close();
//
//
//	//LPSCENE scene = new CPlayScene(1, L"scene1.txt");
//	//scenes[1] = scene;
//	//scene = new CPlayScene(2, L"scene2.txt");
//	//scenes[2] = scene;
//
//	DebugOut(L"[INFO] Loading game file : %s has been loaded successfully\n", gameFile);
//
//	SwitchScene(current_scene);
//}
//
//void CGame::SwitchScene(int scene_id)
//{
//	// IMPORTANT: has to implement "unload" previous scene assets to avoid duplicate resources
//	current_scene = scene_id;
//	LPSCENE s = scenes[current_scene];
//	s->Unload();
//	
//	CTextures::GetInstance()->Clear();
//	CSprites::GetInstance()->Clear();
//	CAnimations::GetInstance()->Clear();
//
//	CGame::GetInstance()->SetKeyHandler(s->GetKeyEventHandler());
//	s->Load();
//}