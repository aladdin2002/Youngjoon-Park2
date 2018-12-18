//=============================================================================
//
// 木処理 [tree.h]
// Author : 
//
//=============================================================================
#ifndef _TREE_H_
#define _TREE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_TREE			(256)	// 木最大数
#define ALPHA_MAX					(1) // プレイヤーの最大数
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 scl;		// スケール
	float fWidth;			// 幅
	float fHeight;			// 高さ
	int nIdxShadow;			// 影ID
	bool bUse;				// 使用しているかどうか
} TREE;
typedef struct
{
	int						g_nAlpha;						// アルファテストの閾値
	bool					g_bAlpaTest;					// アルファテストON/OFF
	bool					g_bEnableGravity = false;		// 重力を有効にするかどうか
}ALPHA;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTree(void);
void UninitTree(void);
void UpdateTree(void);
void DrawTree(void);

int SetTree(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col);

TREE *GetTree(void);
ALPHA *GetAlpha(int no);
#endif
