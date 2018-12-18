//=============================================================================
//
// タイトル画面処理 [logo.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "logo.h"
#include "input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexLogo(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureLogo = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureLogoLogo = NULL;	// テクスチャへのポインタ

VERTEX_2D				g_vertexWkLogo[NUM_VERTEX];			// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkLogoLogo[NUM_VERTEX];		// 頂点情報格納ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_LOGO,				// ファイルの名前
		&g_pD3DTextureLogo);		// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_LOGO_LOGO,			// ファイルの名前
		&g_pD3DTextureLogoLogo);	// 読み込むメモリー

// 頂点情報の作成
	MakeVertexLogo();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitLogo(void)
{
	if (g_pD3DTextureLogo != NULL)
	{// テクスチャの開放
		g_pD3DTextureLogo->Release();
		g_pD3DTextureLogo = NULL;
	}

	if (g_pD3DTextureLogoLogo != NULL)
	{// テクスチャの開放
		g_pD3DTextureLogoLogo->Release();
		g_pD3DTextureLogoLogo = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLogo(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{// Enter押したら、ステージを切り替える
		SetStage(STAGE_TITLE);
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
void DrawLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureLogo);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkLogo, sizeof(VERTEX_2D));


	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureLogoLogo);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkLogoLogo, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexLogo(void)
{

	// 頂点座標の設定
	g_vertexWkLogo[0].vtx = D3DXVECTOR3(LOGO_POS_X, LOGO_POS_Y, 0.0f);
	g_vertexWkLogo[1].vtx = D3DXVECTOR3(LOGO_POS_X + LOGO_SIZE_X, LOGO_POS_Y, 0.0f);
	g_vertexWkLogo[2].vtx = D3DXVECTOR3(LOGO_POS_X, LOGO_POS_Y + LOGO_SIZE_Y, 0.0f);
	g_vertexWkLogo[3].vtx = D3DXVECTOR3(LOGO_POS_X + LOGO_SIZE_X, LOGO_POS_Y + LOGO_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkLogo[0].rhw =
		g_vertexWkLogo[1].rhw =
		g_vertexWkLogo[2].rhw =
		g_vertexWkLogo[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点座標の設定
	g_vertexWkLogoLogo[0].vtx = D3DXVECTOR3(LOGOLOGO_POS_X, LOGOLOGO_POS_Y, 0.0f);
	g_vertexWkLogoLogo[1].vtx = D3DXVECTOR3(LOGOLOGO_POS_X + LOGOLOGO_SIZE_X, LOGOLOGO_POS_Y, 0.0f);
	g_vertexWkLogoLogo[2].vtx = D3DXVECTOR3(LOGOLOGO_POS_X, LOGOLOGO_POS_Y + LOGOLOGO_SIZE_Y, 0.0f);
	g_vertexWkLogoLogo[3].vtx = D3DXVECTOR3(LOGOLOGO_POS_X + LOGOLOGO_SIZE_X, LOGOLOGO_POS_Y + LOGOLOGO_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkLogoLogo[0].rhw =
		g_vertexWkLogoLogo[1].rhw =
		g_vertexWkLogoLogo[2].rhw =
		g_vertexWkLogoLogo[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkLogoLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkLogoLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkLogoLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkLogoLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkLogoLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkLogoLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkLogoLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkLogoLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}