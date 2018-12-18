//=============================================================================
//
// �؏��� [tree.h]
// Author : 
//
//=============================================================================
#ifndef _TREE_H_
#define _TREE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TREE			(256)	// �؍ő吔
#define ALPHA_MAX					(1) // �v���C���[�̍ő吔
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 scl;		// �X�P�[��
	float fWidth;			// ��
	float fHeight;			// ����
	int nIdxShadow;			// �eID
	bool bUse;				// �g�p���Ă��邩�ǂ���
} TREE;
typedef struct
{
	int						g_nAlpha;						// �A���t�@�e�X�g��臒l
	bool					g_bAlpaTest;					// �A���t�@�e�X�gON/OFF
	bool					g_bEnableGravity = false;		// �d�͂�L���ɂ��邩�ǂ���
}ALPHA;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTree(void);
void UninitTree(void);
void UpdateTree(void);
void DrawTree(void);

int SetTree(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col);

TREE *GetTree(void);
ALPHA *GetAlpha(int no);
#endif
