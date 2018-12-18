//=============================================================================
//
// タイトル画面処理 [tutorial.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "tutorial.h"
#include "input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTutorial(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTutorial = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureTutorialLogo = NULL;	// テクスチャへのポインタ

VERTEX_2D				g_vertexWkTutorial[NUM_VERTEX];			// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkTutorialLogo[NUM_VERTEX];		// 頂点情報格納ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_TUTORIAL,				// ファイルの名前
		&g_pD3DTextureTutorial);		// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_TUTORIAL_LOGO,			// ファイルの名前
		&g_pD3DTextureTutorialLogo);	// 読み込むメモリー

// 頂点情報の作成
	MakeVertexTutorial();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTutorial(void)
{
	if (g_pD3DTextureTutorial != NULL)
	{// テクスチャの開放
		g_pD3DTextureTutorial->Release();
		g_pD3DTextureTutorial = NULL;
	}

	if (g_pD3DTextureTutorialLogo != NULL)
	{// テクスチャの開放
		g_pD3DTextureTutorialLogo->Release();
		g_pD3DTextureTutorialLogo = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTutorial(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{// Enter押したら、ステージを切り替える
		SetStage(STAGE_GAME);
	}
	// ゲームパッドでで移動処理
	//else if (IsButtonTriggered(0, BUTTON_START))
	//{
	//	SetStage(STAGE_GAME);
	//}
	//else if (IsButtonTriggered(0, BUTTON_B))
	//{
	//	SetStage(STAGE_GAME);
	//}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTutorial);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTutorial, sizeof(VERTEX_2D));


	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTutorialLogo);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTutorialLogo, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTutorial(void)
{

	// 頂点座標の設定
	g_vertexWkTutorial[0].vtx = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y, 0.0f);
	g_vertexWkTutorial[1].vtx = D3DXVECTOR3(TUTORIAL_POS_X + TUTORIAL_SIZE_X, TUTORIAL_POS_Y, 0.0f);
	g_vertexWkTutorial[2].vtx = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y + TUTORIAL_SIZE_Y, 0.0f);
	g_vertexWkTutorial[3].vtx = D3DXVECTOR3(TUTORIAL_POS_X + TUTORIAL_SIZE_X, TUTORIAL_POS_Y + TUTORIAL_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkTutorial[0].rhw =
		g_vertexWkTutorial[1].rhw =
		g_vertexWkTutorial[2].rhw =
		g_vertexWkTutorial[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkTutorial[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorial[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorial[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorial[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkTutorial[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTutorial[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTutorial[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTutorial[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点座標の設定
	g_vertexWkTutorialLogo[0].vtx = D3DXVECTOR3(TUTORIALLOGO_POS_X, TUTORIALLOGO_POS_Y, 0.0f);
	g_vertexWkTutorialLogo[1].vtx = D3DXVECTOR3(TUTORIALLOGO_POS_X + TUTORIALLOGO_SIZE_X, TUTORIALLOGO_POS_Y, 0.0f);
	g_vertexWkTutorialLogo[2].vtx = D3DXVECTOR3(TUTORIALLOGO_POS_X, TUTORIALLOGO_POS_Y + TUTORIALLOGO_SIZE_Y, 0.0f);
	g_vertexWkTutorialLogo[3].vtx = D3DXVECTOR3(TUTORIALLOGO_POS_X + TUTORIALLOGO_SIZE_X, TUTORIALLOGO_POS_Y + TUTORIALLOGO_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkTutorialLogo[0].rhw =
		g_vertexWkTutorialLogo[1].rhw =
		g_vertexWkTutorialLogo[2].rhw =
		g_vertexWkTutorialLogo[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkTutorialLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorialLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorialLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTutorialLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkTutorialLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTutorialLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTutorialLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTutorialLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}