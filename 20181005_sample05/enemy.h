//=============================================================================
//
// ���f������ [model.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#define SHADOW_MAX					(1) // �v���C���[�̍ő吔
//*****************************************************************************
// �v���g�^�C�v�錾
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
	int					g_nIdxShadow;				// �eID
	float				g_fSizeShadow;				// �e�̃T�C�Y
	D3DXCOLOR			g_colShadow;				// �e�̐F
	D3DXMATERIAL *pD3DXMat;

}SHADOW;


SHADOW *GetShadow(int no);
#endif
