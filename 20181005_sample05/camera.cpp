//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 
//
//=============================================================================
#include "camera.h"
#include "model.h"
#include "enemy.h"
#include "input.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VIEW_ANGLE			(D3DXToRadian(45.0f))	// 視野角
#define	VIEW_ASPECT			((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比
#define	VIEW_NEAR_Z			(10.0f)					// ビュー平面のNearZ値
#define	VIEW_FAR_Z			(1000.0f)				// ビュー平面のFarZ値
#define	VALUE_MOVE_CAMERA	(2.0f)					// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)		// カメラの回転量

#define	INTERVAL_CAMERA_R	(12.5f)					// モデルの視線の先までの距離
#define	RATE_CHASE_CAMERA_P	(0.35f)					// カメラの視点への補正係数
#define	RATE_CHASE_CAMERA_R	(0.20f)					// カメラの注視点への補正係数

#define	CHASE_HEIGHT_P		(100.0f)				// 追跡時の視点の高さ
#define	CHASE_HEIGHT_R		(10.0f)					// 追跡時の注視点の高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DXVECTOR3		g_posCameraP;				// カメラの視点
D3DXVECTOR3		g_posCameraR;				// カメラの注視点
D3DXVECTOR3		g_posCameraU;				// カメラの上方向
D3DXVECTOR3		g_posCameraPDest;			// カメラの視点の目的位置
D3DXVECTOR3		g_posCameraRDest;			// カメラの注視点の目的位置
D3DXVECTOR3		g_rotCamera;				// カメラの回転
float			g_fLengthIntervalCamera;	// カメラの視点と注視点の距離
D3DXMATRIX		g_mtxView;					// ビューマトリックス
D3DXMATRIX		g_mtxProjection;			// プロジェクションマトリックス

//=============================================================================
// カメラの初期化
//=============================================================================
HRESULT InitCamera(void)
{
	g_posCameraP = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	g_posCameraR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_posCameraU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_posCameraPDest = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	g_posCameraRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float vx,vz;
	vx = g_posCameraP.x - g_posCameraR.x;
	vz = g_posCameraP.z - g_posCameraR.z;
	g_fLengthIntervalCamera = sqrtf(vx * vx + vz * vz);

	return S_OK;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{
	if(GetKeyboardPress(DIK_A))
	{
		if(GetKeyboardPress(DIK_W))
		{// 左前移動
			g_posCameraP.x -= cosf(g_rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
			g_posCameraP.z += sinf(g_rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
		}
		else if(GetKeyboardPress(DIK_S))
		{// 左後移動
			g_posCameraP.x -= cosf(g_rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
			g_posCameraP.z += sinf(g_rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
		}
		else
		{// 左移動
			g_posCameraP.x -= cosf(g_rotCamera.y) * VALUE_MOVE_CAMERA;
			g_posCameraP.z += sinf(g_rotCamera.y) * VALUE_MOVE_CAMERA;
		}

		g_posCameraR.x = g_posCameraP.x + sinf(g_rotCamera.y) * g_fLengthIntervalCamera;
		g_posCameraR.z = g_posCameraP.z + cosf(g_rotCamera.y) * g_fLengthIntervalCamera;
	}
	else if(GetKeyboardPress(DIK_D))
	{
		if(GetKeyboardPress(DIK_W))
		{// 右前移動
			g_posCameraP.x += cosf(g_rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
			g_posCameraP.z -= sinf(g_rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
		}
		else if(GetKeyboardPress(DIK_S))
		{// 右後移動
			g_posCameraP.x += cosf(g_rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
			g_posCameraP.z -= sinf(g_rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
		}
		else
		{// 右移動
			g_posCameraP.x += cosf(g_rotCamera.y) * VALUE_MOVE_CAMERA;
			g_posCameraP.z -= sinf(g_rotCamera.y) * VALUE_MOVE_CAMERA;
		}

		g_posCameraR.x = g_posCameraP.x + sinf(g_rotCamera.y) * g_fLengthIntervalCamera;
		g_posCameraR.z = g_posCameraP.z + cosf(g_rotCamera.y) * g_fLengthIntervalCamera;
	}
	else if(GetKeyboardPress(DIK_W))
	{// 前移動
		g_posCameraP.x += sinf(g_rotCamera.y) * VALUE_MOVE_CAMERA;
		g_posCameraP.z += cosf(g_rotCamera.y) * VALUE_MOVE_CAMERA;

		g_posCameraR.x = g_posCameraP.x + sinf(g_rotCamera.y) * g_fLengthIntervalCamera;
		g_posCameraR.z = g_posCameraP.z + cosf(g_rotCamera.y) * g_fLengthIntervalCamera;
	}
	else if(GetKeyboardPress(DIK_S))
	{// 後移動
		g_posCameraP.x -= sinf(g_rotCamera.y) * VALUE_MOVE_CAMERA;
		g_posCameraP.z -= cosf(g_rotCamera.y) * VALUE_MOVE_CAMERA;

		g_posCameraR.x = g_posCameraP.x + sinf(g_rotCamera.y) * g_fLengthIntervalCamera;
		g_posCameraR.z = g_posCameraP.z + cosf(g_rotCamera.y) * g_fLengthIntervalCamera;
	}

	if(GetKeyboardPress(DIK_Z))
	{// 視点旋回「左」
		g_rotCamera.y += VALUE_ROTATE_CAMERA;
		if(g_rotCamera.y > D3DX_PI)
		{
			g_rotCamera.y -= D3DX_PI * 2.0f;
		}

		g_posCameraP.x = g_posCameraR.x - sinf(g_rotCamera.y) * g_fLengthIntervalCamera;
		g_posCameraP.z = g_posCameraR.z - cosf(g_rotCamera.y) * g_fLengthIntervalCamera;
	}
	if(GetKeyboardPress(DIK_C))
	{// 視点旋回「右」
		g_rotCamera.y -= VALUE_ROTATE_CAMERA;
		if(g_rotCamera.y < -D3DX_PI)
		{
			g_rotCamera.y += D3DX_PI * 2.0f;
		}

		g_posCameraP.x = g_posCameraR.x - sinf(g_rotCamera.y) * g_fLengthIntervalCamera;
		g_posCameraP.z = g_posCameraR.z - cosf(g_rotCamera.y) * g_fLengthIntervalCamera;
	}
	if(GetKeyboardPress(DIK_Y))
	{// 視点移動「上」
		g_posCameraP.y += VALUE_MOVE_CAMERA;
	}
	if(GetKeyboardPress(DIK_N))
	{// 視点移動「下」
		g_posCameraP.y -= VALUE_MOVE_CAMERA;
	}

	if(GetKeyboardPress(DIK_Q))
	{// 注視点旋回「左」
		g_rotCamera.y -= VALUE_ROTATE_CAMERA;
		if(g_rotCamera.y < -D3DX_PI)
		{
			g_rotCamera.y += D3DX_PI*2.0f;
		}

		g_posCameraR.x = g_posCameraP.x + sinf(g_rotCamera.y) * g_fLengthIntervalCamera;
		g_posCameraR.z = g_posCameraP.z + cosf(g_rotCamera.y) * g_fLengthIntervalCamera;
	}
	if(GetKeyboardPress(DIK_E))
	{// 注視点旋回「右」
		g_rotCamera.y += VALUE_ROTATE_CAMERA;
		if(g_rotCamera.y > D3DX_PI)
		{
			g_rotCamera.y -= D3DX_PI*2.0f;
		}

		g_posCameraR.x = g_posCameraP.x + sinf(g_rotCamera.y) * g_fLengthIntervalCamera;
		g_posCameraR.z = g_posCameraP.z + cosf(g_rotCamera.y) * g_fLengthIntervalCamera;
	}
	if(GetKeyboardPress(DIK_T))
	{// 注視点移動「上」
		g_posCameraR.y += VALUE_MOVE_CAMERA;
	}
	if(GetKeyboardPress(DIK_B))
	{// 注視点移動「下」
		g_posCameraR.y -= VALUE_MOVE_CAMERA;
	}

	PrintDebugProc("[カメラの視点  ：(%f : %f : %f)]\n", g_posCameraP.x, g_posCameraP.y, g_posCameraP.z);
	PrintDebugProc("[カメラの注視点：(%f : %f : %f)]\n", g_posCameraR.x, g_posCameraR.y, g_posCameraR.z);
	PrintDebugProc("[カメラの向き  ：(%f)]\n", g_rotCamera.y);
	PrintDebugProc("\n");

	PrintDebugProc("*** 視点操作 ***\n");
	PrintDebugProc("前移動 : W\n");
	PrintDebugProc("後移動 : S\n");
	PrintDebugProc("左移動 : A\n");
	PrintDebugProc("右移動 : D\n");
	PrintDebugProc("上移動 : Y\n");
	PrintDebugProc("下移動 : N\n");
	PrintDebugProc("左旋回 : Z\n");
	PrintDebugProc("右旋回 : C\n");
	PrintDebugProc("\n");

	PrintDebugProc("*** 注視点操作 ***\n");
	PrintDebugProc("上移動 : T\n");
	PrintDebugProc("下移動 : B\n");
	PrintDebugProc("左旋回 : Q\n");
	PrintDebugProc("右旋回 : E\n");
	PrintDebugProc("\n");
}

//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_mtxView, 
						&g_posCameraP,		// カメラの視点
						&g_posCameraR,		// カメラの注視点
						&g_posCameraU);		// カメラの上方向

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);


	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_mtxProjection,
								VIEW_ANGLE,			// 視野角
								VIEW_ASPECT,		// アスペクト比
								VIEW_NEAR_Z,		// ビュー平面のNearZ値
								VIEW_FAR_Z);		// ビュー平面のFarZ値

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProjection);
}

//=============================================================================
// カメラの向きの取得
//=============================================================================
D3DXVECTOR3 GetRotCamera(void)
{
	return g_rotCamera;
}

//=============================================================================
// ビューマトリックスの取得
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	return g_mtxView;
}

