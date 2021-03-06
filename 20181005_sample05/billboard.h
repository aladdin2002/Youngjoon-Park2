//=============================================================================
//
// ビルボード処理 [billboard.h]
// Author : 
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
int SetBillboard(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col);
#endif
