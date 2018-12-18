//=============================================================================
//
// モデル処理 [model.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#define SHADOW_MAX					(1) // プレイヤーの最大数
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

D3DXVECTOR3 GetPositionEnemy(void);
D3DXVECTOR3 GetRotationEnemy(void);
D3DXVECTOR3 GetRotationDestEnemy(void);

typedef struct
{
	int					g_nIdxShadow;				// 影ID
	float				g_fSizeShadow;				// 影のサイズ
	D3DXCOLOR			g_colShadow;				// 影の色
	D3DXMATERIAL *pD3DXMat;

}SHADOW;


SHADOW *GetShadow(int no);
#endif
