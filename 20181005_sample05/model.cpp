//=============================================================================
//
// モデル処理 [model.cpp]
// Author : 
//
//=============================================================================
#include "model.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MODEL_AIRPLANE		"data/MODEL/umaumakun.x"	// 読み込むモデル名
#define	VALUE_MOVE_MODEL	(0.50f)						// 移動速度
#define	RATE_MOVE_MODEL		(0.20f)						// 移動慣性係数
#define	VALUE_ROTATE_MODEL	(D3DX_PI * 0.05f)			// 回転速度
#define	RATE_ROTATE_MODEL	(0.20f)						// 回転慣性係数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureModel;			// テクスチャ読み込み場所
LPD3DXMESH			g_pD3DXMeshModel;			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXBuffMatModel;		// メッシュのマテリアル情報を格納
DWORD				g_nNumMatModel;				// 属性情報の総数

D3DXMATRIX			g_mtxWorldModel;			// ワールドマトリックス
D3DXVECTOR3			g_posModel;					// 現在の位置
D3DXVECTOR3			g_moveModel;				// 移動量
D3DXVECTOR3			g_rotModel;					// 現在の向き
D3DXVECTOR3			g_rotDestModel;				// 目的の向き

int					g_nIdxShadow;				// 影ID
float				g_fSizeShadow;				// 影のサイズ
D3DXCOLOR			g_colShadow;				// 影の色

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_pD3DTextureModel = NULL;
	g_pD3DXMeshModel = NULL;
	g_pD3DXBuffMatModel = NULL;

	g_posModel = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_moveModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotDestModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Xファイルの読み込み
	if(FAILED(D3DXLoadMeshFromX(MODEL_AIRPLANE,
								D3DXMESH_SYSTEMMEM,
								pDevice,
								NULL,
								&g_pD3DXBuffMatModel,
								NULL,
								&g_nNumMatModel,
								&g_pD3DXMeshModel)))
	{
		return E_FAIL;
	}

#if 0
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_FILENAME,		// ファイルの名前
								&g_pD3DTextureModel);	// 読み込むメモリー
#endif

	// 影の生成
	g_nIdxShadow = CreateShadow(g_posModel, 25.0f, 25.0f);

	g_fSizeShadow = 25.0f;
	g_colShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitModel(void)
{
	if(g_pD3DTextureModel != NULL)
	{// テクスチャの開放
		g_pD3DTextureModel->Release();
		g_pD3DTextureModel = NULL;
	}

	if(g_pD3DXMeshModel != NULL)
	{// メッシュの開放
		g_pD3DXMeshModel->Release();
		g_pD3DXMeshModel = NULL;
	}

	if(g_pD3DXBuffMatModel != NULL)
	{// マテリアルの開放
		g_pD3DXBuffMatModel->Release();
		g_pD3DXBuffMatModel = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateModel(void)
{
	D3DXVECTOR3 rotCamera;
	float fDiffRotY;

	// カメラの向き取得
	rotCamera = GetRotCamera();

	if(GetKeyboardPress(DIK_LEFT))
	{
		if(GetKeyboardPress(DIK_UP))
		{// 左前移動
			g_moveModel.x -= sinf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;
			g_moveModel.z -= cosf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;

			g_rotDestModel.y = rotCamera.y + D3DX_PI * 0.75f;
		}
		else if(GetKeyboardPress(DIK_DOWN))
		{// 左後移動
			g_moveModel.x -= sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;
			g_moveModel.z -= cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;

			g_rotDestModel.y = rotCamera.y + D3DX_PI * 0.25f;
		}
		else
		{// 左移動
			g_moveModel.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
			g_moveModel.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;

			g_rotDestModel.y = rotCamera.y + D3DX_PI * 0.50f;
		}
	}
	else if(GetKeyboardPress(DIK_RIGHT))
	{
		if(GetKeyboardPress(DIK_UP))
		{// 右前移動
			g_moveModel.x -= sinf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;
			g_moveModel.z -= cosf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;

			g_rotDestModel.y = rotCamera.y - D3DX_PI * 0.75f;
		}
		else if(GetKeyboardPress(DIK_DOWN))
		{// 右後移動
			g_moveModel.x -= sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;
			g_moveModel.z -= cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;

			g_rotDestModel.y = rotCamera.y - D3DX_PI * 0.25f;
		}
		else
		{// 右移動
			g_moveModel.x -= sinf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
			g_moveModel.z -= cosf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;

			g_rotDestModel.y = rotCamera.y - D3DX_PI * 0.50f;
		}
	}
	else if(GetKeyboardPress(DIK_UP))
	{// 前移動
		g_moveModel.x -= sinf(D3DX_PI + rotCamera.y) * VALUE_MOVE_MODEL;
		g_moveModel.z -= cosf(D3DX_PI + rotCamera.y) * VALUE_MOVE_MODEL;

		g_rotDestModel.y = D3DX_PI + rotCamera.y;
	}
	else if(GetKeyboardPress(DIK_DOWN))
	{// 後移動
		g_moveModel.x -= sinf(rotCamera.y) * VALUE_MOVE_MODEL;
		g_moveModel.z -= cosf(rotCamera.y) * VALUE_MOVE_MODEL;

		g_rotDestModel.y = rotCamera.y;
	}

	if(GetKeyboardPress(DIK_LSHIFT))
	{// 左回転
		g_rotDestModel.y -= VALUE_ROTATE_MODEL;
		if(g_rotDestModel.y < -D3DX_PI)
		{
			g_rotDestModel.y += D3DX_PI * 2.0f;
		}
	}
	if(GetKeyboardPress(DIK_RSHIFT))
	{// 右回転
		g_rotDestModel.y += VALUE_ROTATE_MODEL;
		if(g_rotDestModel.y > D3DX_PI)
		{
			g_rotDestModel.y -= D3DX_PI * 2.0f;
		}
	}

	if(GetKeyboardPress(DIK_I))
	{// 上昇
		g_moveModel.y += VALUE_MOVE_MODEL * 0.5f;

		if(g_posModel.y < 75.0f)
		{
			g_fSizeShadow += 0.2f;
			g_colShadow.a -= 0.004f;
		}
	}
	if(GetKeyboardPress(DIK_K))
	{// 下降
		g_moveModel.y -= VALUE_MOVE_MODEL * 0.5f;

		if(g_posModel.y > 5.0f)
		{
			g_fSizeShadow -= 0.2f;
			g_colShadow.a += 0.004f;
		}
	}

	// 目的の角度までの差分
	fDiffRotY = g_rotDestModel.y - g_rotModel.y;
	if(fDiffRotY > D3DX_PI)
	{
		fDiffRotY -= D3DX_PI * 2.0f;
	}
	if(fDiffRotY < -D3DX_PI)
	{
		fDiffRotY += D3DX_PI * 2.0f;
	}

	// 目的の角度まで慣性をかける
	g_rotModel.y += fDiffRotY * RATE_ROTATE_MODEL;
	if(g_rotModel.y > D3DX_PI)
	{
		g_rotModel.y -= D3DX_PI * 2.0f;
	}
	if(g_rotModel.y < -D3DX_PI)
	{
		g_rotModel.y += D3DX_PI * 2.0f;
	}

	/// 位置移動
	g_posModel.x += g_moveModel.x;
	g_posModel.y += g_moveModel.y;
	if(g_posModel.y < 5.0f)
	{
		g_posModel.y = 5.0f;
	}
	if(g_posModel.y > 75.0f)
	{
		g_posModel.y = 75.0f;
	}
	g_posModel.z += g_moveModel.z;

	// 移動量に慣性をかける
	g_moveModel.x += (0.0f - g_moveModel.x) * RATE_MOVE_MODEL;
	g_moveModel.y += (0.0f - g_moveModel.y) * RATE_MOVE_MODEL;
	g_moveModel.z += (0.0f - g_moveModel.z) * RATE_MOVE_MODEL;

	if(g_posModel.x < -310.0f)
	{
		g_posModel.x = -310.0f;
	}
	if(g_posModel.x > 310.0f)
	{
		g_posModel.x = 310.0f;
	}
	if(g_posModel.z < -310.0f)
	{
		g_posModel.z = -310.0f;
	}
	if(g_posModel.z > 310.0f)
	{
		g_posModel.z = 310.0f;
	}

	// 影の位置設定
	SetPositionShadow(g_nIdxShadow, D3DXVECTOR3(g_posModel.x, 0.1f, g_posModel.z));

	SetVertexShadow(g_nIdxShadow, g_fSizeShadow, g_fSizeShadow);
	SetColorShadow(g_nIdxShadow, g_colShadow);

	PrintDebugProc("[飛行機の位置  ：(%f : %f : %f)]\n", g_posModel.x, g_posModel.y, g_posModel.z);
	PrintDebugProc("[飛行機の向き  ：(%f) < 目的の向き:(%f) >]\n", g_rotModel.y, g_rotDestModel.y);
	PrintDebugProc("\n");

	PrintDebugProc("*** 飛行機操作 ***\n");
	PrintDebugProc("前移動 : ↑\n");
	PrintDebugProc("後移動 : ↓\n");
	PrintDebugProc("左移動 : ←\n");
	PrintDebugProc("右移動 : →\n");
	PrintDebugProc("上昇   : Ｉ\n");
	PrintDebugProc("下降   : Ｋ\n");
	PrintDebugProc("左旋回 : LSHIFT\n");
	PrintDebugProc("右旋回 : RSHIFT\n");
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldModel);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, g_posModel.x, g_posModel.y, g_posModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatModel->GetBufferPointer();

	for(int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureModel);

		// 描画
		g_pD3DXMeshModel->DrawSubset(nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// 位置取得
//=============================================================================
D3DXVECTOR3 GetPositionModel(void)
{
	return g_posModel;
}

//=============================================================================
// 向き取得
//=============================================================================
D3DXVECTOR3 GetRotationModel(void)
{
	return g_rotModel;
}

//=============================================================================
// 目的の向き取得
//=============================================================================
D3DXVECTOR3 GetRotationDestModel(void)
{
	return g_rotDestModel;
}
