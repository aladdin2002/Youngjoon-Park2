//=============================================================================
//
// メイン処理 [main.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "light.h"
#include "camera.h"
#include "meshfield.h"
#include "meshwall.h"
#include "model.h"
#include "shadow.h"
#include "debugproc.h"
#include "billboard.h"
#include "tree.h"
#include "enemy.h"
#include "particle.h"
#include "title.h"
#include "result.h"
#include "logo.h"
#include "tutorial.h"
#include "score.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"AppClass"		// ウインドウのクラス名
#define WINDOW_NAME		"影表示処理"		// ウインドウのキャプション名

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
#ifdef _DEBUG
void DrawDebugFont(void);
#endif
//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3D オブジェクト
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// Deviceオブジェクト(描画に必要)
#ifdef _DEBUG
int					g_nCountFPS;			// FPSカウンタ
#endif
bool				g_bDispDebug = true;	// デバッグ表示ON/OFF
int						g_nStage = STAGE_LOGO;				// ステージ番号
void InitGame(void);
//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND hWnd;
	MSG msg;
	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindowEx(0,
						CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
						NULL,
						NULL,
						hInstance,
						NULL);

	// 初期化処理(ウィンドウを作成してから行う)
	if(FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// フレームカウント初期化
	timeBeginPeriod(1);				// 分解能を設定
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;

	// ウインドウの表示(初期化処理の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// メッセージループ
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
			{
#ifdef _DEBUG
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
#ifdef _DEBUG
				PrintDebugProc("FPS:%d\n", g_nCountFPS);
#endif

				dwExecLastTime = dwCurrentTime;

				// 更新処理
				Update();

				// 描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}
	
	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	Uninit();

	timeEndPeriod(1);				// 分解能を戻す

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
    D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
    if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferCount			= 1;						// バックバッファの数
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat			= d3ddm.Format;				// カラーモードの指定
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	d3dpp.Windowed					= bWindow;					// ウィンドウモード
	d3dpp.EnableAutoDepthStencil	= TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				// デプスバッファとして16bitを使う

	if(bWindow)
	{// ウィンドウモード
		d3dpp.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{// フルスクリーンモード
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
									D3DDEVTYPE_HAL, 
									hWnd, 
									D3DCREATE_HARDWARE_VERTEXPROCESSING, 
									&d3dpp, &g_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp, &g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp, &g_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダリングステートパラメータの設定
    g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	// サンプラーステートパラメータの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	// テクスチャステージ加算合成処理
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

	// 入力処理の初期化
	InitInput(hInstance, hWnd);

	// デバッグ表示処理の初期化
	InitDebugProc();

	// ライトの初期化
	InitLight();
	InitParticle();
	InitShadow();
	InitTree();

	// カメラの初期化
	InitCamera();

	// 地面の初期化
	InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f), 80, 80, 800.0f, 800.0f);

	// 影の初期化

	InitBillboard();
	// モデルの初期化
	InitModel();
	InitEnemy();
	InitScore(0);
	// 壁の初期化
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, 620.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 1, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(-620.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 1, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(620.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 1, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -620.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 1, 80.0f, 80.0f);

	// 壁(裏側用)
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, 620.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 8, 1, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(-620.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 8, 1, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(620.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 8, 1, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -620.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 8, 1, 80.0f, 80.0f);

	InitScore(0);
	// タイトル初期化
	InitTitle();

	// リザルト初期化
	InitResult();

	// スコア初期化


	InitTutorial();

	InitLogo();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	if(g_pD3DDevice != NULL)
	{// デバイスの開放
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if(g_pD3D != NULL)
	{// Direct3Dオブジェクトの開放
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	// 入力処理の終了処理
	UninitInput();

	UninitShadow();
	UninitTree();

	// デバッグ表示処理の終了処理
	UninitDebugProc();

	// 地面の終了処理
	UninitMeshField();
	UninitParticle();
	// 壁の終了処理
	UninitMeshWall();

	// 影の終了処理

	UninitBillboard();
	// モデルの終了処理
	UninitModel();
	UninitEnemy();
	UninitScore();

	// タイトル終了処理
	UninitTitle();

	// リザルト終了処理
	UninitResult();

	UninitTutorial();

	UninitLogo();
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{

	// 入力の更新処理
	UpdateInput();

	// 画面遷移
	switch (g_nStage)
	{
	case STAGE_LOGO :
		UpdateLogo();
		break;
	
	case STAGE_TITLE:
		UpdateTitle();
		break;

	case STAGE_TUTORIAL:
		UpdateTutorial();
		break;

	case STAGE_GAME:

		// カメラ更新
		UpdateCamera();
		UpdateEnemy();
		UpdateShadow();
		UpdateTree();
	

		// 地面処理の更新
		UpdateMeshField();

		// 壁処理の更新
		UpdateMeshWall();
		UpdateParticle();
		UpdateBillboard();
		// 影処理の更新

				// スコアの更新処理
		UpdateScore();
		// モデル処理の更新
		UpdateModel();
	
	
	//case STAGE_GAMEEND:
	//	// スコアの更新処理
	//	UpdateScore();

		if (GetKeyboardTrigger(DIK_RETURN))
		{// Enter押したら、ステージを切り替える
			SetStage(STAGE_RESULT);
		}
		//else if (IsButtonTriggered(0, BUTTON_B))
		//{
		//	InitGame();				// ゲームの再初期化処理
		//	SetStage(STAGE_RESULT);
		//}
		break;

	case STAGE_RESULT:
		UpdateResult();
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	// Direct3Dによる描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_nStage)
		{
		case STAGE_LOGO:
			DrawLogo();
			break;

		case STAGE_TITLE:
			DrawTitle();
			break;
		case STAGE_TUTORIAL:
			DrawTutorial();
			break;

		case STAGE_GAME:
			// カメラの設定
			SetCamera();

			// 地面処理の描画
			DrawMeshField();

			// 影処理の描画

			DrawShadow();


			DrawEnemy();
			// モデル処理の描画
			DrawModel();
			DrawBillboard();
			// 壁処理の描画
			DrawMeshWall();
			DrawParticle();
			DrawTree();

			DrawScore();
			break;

		case STAGE_RESULT:
			DrawResult();
			break;

		}
			// デバッグ表示処理の描画
			if (g_bDispDebug)
			{
				DrawDebugProc();
			}

			// Direct3Dによる描画の終了
			g_pD3DDevice->EndScene();
	}
	
	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// デバイスの取得
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}


//#ifdef _DEBUG
////=============================================================================
//// デバッグ表示処理
////=============================================================================
//void DrawDebugFont(void)
//{
//	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
//	char str[256];
//	PLAYER *player = GetPlayer(0);
//	// テキスト描画
//	sprintf(str, _T("FPS:%d"), g_nCountFPS);
//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
//
//	rect.top = 20;
//	sprintf(str, "PX:%f  PY:%f", player->pos.x, player->pos.y);
//	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
//
//}
//#endif		

//=============================================================================
// 画面遷移
//=============================================================================

	void SetStage(int stage)
{
	if (stage < 0 || stage >= STAGE_MAX) return;

	g_nStage = stage;


}


void InitGame(void)
{
	InitCamera();
	InitShadow();
	InitTree();
	InitParticle();
	InitBillboard();
	InitScore(0);
	InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 8, 8, 80.0f, 80.0f);

	InitModel();
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, 320.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 1, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(-320.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 1, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(320.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 1, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -320.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 1, 80.0f, 80.0f);
}



