//매크로 함수 //DXUtil에서 가져옴


#include "stdafx.h"

#include "MainGame.h"

char				m_sCls[128]; //윈도우 이름에 필요
HINSTANCE			m_hInst		= NULL;
HWND				m_hWnd		= NULL;
DWORD				m_dWinStyle	= WS_OVERLAPPEDWINDOW| WS_VISIBLE;
DWORD				m_dScnX		= 800;			// Screen Width
DWORD				m_dScnY		= 600;			// Screen Height

//DirectX에 필요한 변수
												// 항상 포인터들은 NULL로 초기화
LPDIRECT3D9			m_pD3D		= NULL;			// D3D
LPDIRECT3DDEVICE9	m_pd3dDevice= NULL;			// Device
BOOL				m_bWindow	= TRUE;			// Window mode
BOOL				m_bShowCusor= TRUE;			// Show Cusor

LPDIRECT3DTEXTURE9	m_pTx1		= NULL;			// 배경 텍스처



//Window+Device관련 함수들
INT		Create(HINSTANCE hInst);
INT		Run();
void	Cleanup();

//게임 실행 관련 함수들
INT		Init();
void	Destroy();
INT		FrameMove();
INT		Render();

LRESULT MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
LRESULT WINAPI WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

MainGame mainGame;

float curTime;
float oldTime;

float deltaTime;


INT Create( HINSTANCE hInst)
{
	m_hInst	= hInst;
	strcpy_s(m_sCls, TEXT("D3D Tutorial"));

	//윈도우 클래스 초기화
	WNDCLASS wc ={CS_CLASSDC, WndProc, 0L, 0L, m_hInst, NULL, 
		LoadCursor(NULL,IDC_ARROW), (HBRUSH)GetStockObject(LTGRAY_BRUSH), 
		NULL, m_sCls	};

	RegisterClass( &wc ); //윈도우 클래스 등록

	RECT rc;									//Create the application's window

	SetRect( &rc, 0, 0, m_dScnX, m_dScnY);
	AdjustWindowRect( &rc, m_dWinStyle, FALSE );

	int iScnSysW = GetSystemMetrics(SM_CXSCREEN);
	int iScnSysH = GetSystemMetrics(SM_CYSCREEN);

	m_hWnd = CreateWindow( m_sCls
		, m_sCls
		, m_dWinStyle
		, (iScnSysW - (rc.right - rc.left))/2 //윈도우 X
		, (iScnSysH - (rc.bottom - rc.top))/2 //윈도우 Y
		, (rc.right - rc.left) //윈도우 너비
		, (rc.bottom - rc.top) //윈도우 높이
		, GetDesktopWindow()
		, NULL
		, m_hInst
		, NULL );


	// D3D생성
	if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return -1;

	// 디바이스를 생성하기 위해서는 프리젠트 파라메터 구조체가 필요
	// 전부 0으로 셋팅한다음 일부만 변수세팅

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory( &d3dpp, sizeof(d3dpp) ); //전부 초기화

	d3dpp.Windowed				= m_bWindow; //전체화면과 윈도우모드 설정
	d3dpp.SwapEffect			= D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat		= D3DFMT_X8R8G8B8; //32bit화면
	d3dpp.BackBufferWidth		= m_dScnX; //DX표면 너비
	d3dpp.BackBufferHeight		= m_dScnY; //DX표면 높이
	d3dpp.EnableAutoDepthStencil= TRUE;
	d3dpp.AutoDepthStencilFormat= D3DFMT_D16;


	// D3DADAPTER_DEFAULT: 대부분의 그래픽카드는 모노 듀얼일 경우 이부분을 수정
	// D3DDEVTYPE_HAL : 하드웨어 가속(가장 큰 속도)을 받을 것인가.. 하드웨어 지
	// 원이 없을 경우 D3D는 소프트웨어로 이를 대체 할 수 있다.

	if( FAILED( m_pD3D->CreateDevice(	D3DADAPTER_DEFAULT
									,	D3DDEVTYPE_HAL
									,	m_hWnd
									,	D3DCREATE_MIXED_VERTEXPROCESSING
									,	&d3dpp
									,	&m_pd3dDevice ) ) )
	{
		if( FAILED( m_pD3D->CreateDevice(	D3DADAPTER_DEFAULT
										,	D3DDEVTYPE_HAL
										,	m_hWnd
										,	D3DCREATE_SOFTWARE_VERTEXPROCESSING
										,	&d3dpp
										,	&m_pd3dDevice ) ) )
		{
			SAFE_RELEASE(	m_pd3dDevice	);
			SAFE_RELEASE(	m_pD3D			);
			return -1;
		}
	}

	ShowWindow( m_hWnd, SW_SHOW );
	UpdateWindow( m_hWnd );
	::ShowCursor(m_bShowCusor);


	if(FAILED(Init()))
		return -1;


	return 0;
}


void Cleanup()
{
	Destroy();

	SAFE_RELEASE(	m_pd3dDevice	);
	SAFE_RELEASE(	m_pD3D			);
}


LRESULT MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
		case WM_KEYDOWN:
		{

			switch(wParam)
			{
				case VK_ESCAPE:
				{
					SendMessage(hWnd, WM_DESTROY, 0,0);
					break;
				}
			}

			return 0;
		}

		case WM_DESTROY:
		{
			Cleanup();
			PostQuitMessage( 0 );
			return 0;
		}
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}



INT Run()
{
	oldTime = curTime;
	curTime = GetTickCount();

	deltaTime = curTime - oldTime;

	// Enter the message loop
	MSG msg;
	memset( &msg, 0, sizeof(msg) );

	while( msg.message != WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			if(FAILED(FrameMove()))
				SendMessage(m_hWnd, WM_QUIT,0,0);

			if(FAILED(Render()))
				SendMessage(m_hWnd, WM_QUIT,0,0);
		}
	}

	UnregisterClass( m_sCls, m_hInst);

	return 0;
}



INT Init()
{
	mainGame.Init();

	return 0;
}

void Destroy()
{
	// 디바이스 해제 이전에 텍스처를 해제
	if(m_pTx1)
	{
		m_pTx1->Release();
		m_pTx1 = NULL;
		mainGame.Destroy();
	}
}

INT FrameMove()
{
	mainGame.Update();
	return 0;
}


INT Render()
{
	if( NULL == m_pd3dDevice ) //D3D디바이스가 살아 있으면 실행
		return -1;

	m_pd3dDevice->Clear( 0
						, NULL
						, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER
						, D3DCOLOR_XRGB(0,120,160)
						, 1.0f
						, 0 );


	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;

	mainGame.Render();


	m_pd3dDevice->EndScene();

	return m_pd3dDevice->Present( 0, 0, 0, 0);
}



LRESULT WINAPI WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	return MsgProc(hWnd, msg, wParam, lParam);
}


//윈도우 시작점 //프로그램 시작
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
	if(FAILED(Create(hInst)))
		return -1;

	return Run();
}

LPDIRECT3DDEVICE9 GetD3D9Device() { return m_pd3dDevice; }
HWND GetHWnd() { return m_hWnd; }
float GetDeltaTime() { return deltaTime; }














