//=============================================================================
//
// ���f������ [enemy.cpp]
// Author : 
//
//=============================================================================
#include "enemy.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ENEMY_AIRPLANE		"data/ENEMY/onna.x"	// �ǂݍ��ރ��f����
#define	VALUE_MOVE_ENEMY	(0.50f)						// �ړ����x
#define	RATE_MOVE_ENEMY		(0.20f)						// �ړ������W��
#define	VALUE_ROTATE_ENEMY	(D3DX_PI * 0.05f)			// ��]���x
#define	RATE_ROTATE_ENEMY	(0.20f)						// ��]�����W��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
SHADOW *shadow[1];
LPDIRECT3DTEXTURE9	g_pD3DTextureEnemy;			// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pD3DXMeshEnemy;			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXBuffMatEnemy;		// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatEnemy;				// �������̑���

D3DXMATRIX			g_mtxWorldEnemy;			// ���[���h�}�g���b�N�X
D3DXVECTOR3			g_posEnemy;					// ���݂̈ʒu
D3DXVECTOR3			g_moveEnemy;				// �ړ���
D3DXVECTOR3			g_rotEnemy;					// ���݂̌���
D3DXVECTOR3			g_rotDestEnemy;				// �ړI�̌���

SHADOW				shadowWk[SHADOW_MAX];			// �v���C���[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SHADOW *shadow = GetShadow(0);
	g_pD3DTextureEnemy = NULL;
	g_pD3DXMeshEnemy = NULL;
	g_pD3DXBuffMatEnemy = NULL;

	g_posEnemy = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_moveEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotDestEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(ENEMY_AIRPLANE,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pD3DXBuffMatEnemy,
		NULL,
		&g_nNumMatEnemy,
		&g_pD3DXMeshEnemy)))
	{
		return E_FAIL;
	}

#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FILENAME,		// �t�@�C���̖��O
		&g_pD3DTextureEnemy);	// �ǂݍ��ރ������[
#endif

	// �e�̐���
	shadow->g_nIdxShadow = CreateShadow(g_posEnemy, 25.0f, 25.0f);

	shadow->g_fSizeShadow = 25.0f;
	shadow->g_colShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	if (g_pD3DTextureEnemy != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureEnemy->Release();
		g_pD3DTextureEnemy = NULL;
	}

	if (g_pD3DXMeshEnemy != NULL)
	{// ���b�V���̊J��
		g_pD3DXMeshEnemy->Release();
		g_pD3DXMeshEnemy = NULL;
	}

	if (g_pD3DXBuffMatEnemy != NULL)
	{// �}�e���A���̊J��
		g_pD3DXBuffMatEnemy->Release();
		g_pD3DXBuffMatEnemy = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	SHADOW *shadow = GetShadow(0);
	D3DXVECTOR3 rotCamera;
	float fDiffRotY;

	// �J�����̌����擾
	rotCamera = GetRotCamera();

	if (GetKeyboardPress(DIK_LEFT))
	{
		if (GetKeyboardPress(DIK_UP))
		{// ���O�ړ�
			g_moveEnemy.x -= sinf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_ENEMY;
			g_moveEnemy.z -= cosf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_ENEMY;

			g_rotDestEnemy.y = rotCamera.y + D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(DIK_DOWN))
		{// ����ړ�hh
			g_moveEnemy.x -= sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;
			g_moveEnemy.z -= cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;

			g_rotDestEnemy.y = rotCamera.y + D3DX_PI * 0.25f;
		}
		else
		{// ���ړ�
			g_moveEnemy.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_ENEMY;
			g_moveEnemy.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_ENEMY;

			g_rotDestEnemy.y = rotCamera.y + D3DX_PI * 0.50f;
		}
	}
	else if (GetKeyboardPress(DIK_RIGHT))
	{
		if (GetKeyboardPress(DIK_UP))
		{// �E�O�ړ�
			g_moveEnemy.x -= sinf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_ENEMY;
			g_moveEnemy.z -= cosf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_ENEMY;

			g_rotDestEnemy.y = rotCamera.y - D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(DIK_DOWN))
		{// �E��ړ�
			g_moveEnemy.x -= sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;
			g_moveEnemy.z -= cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;

			g_rotDestEnemy.y = rotCamera.y - D3DX_PI * 0.25f;
		}
		else
		{// �E�ړ�
			g_moveEnemy.x -= sinf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_ENEMY;
			g_moveEnemy.z -= cosf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_ENEMY;

			g_rotDestEnemy.y = rotCamera.y - D3DX_PI * 0.50f;
		}
	}
	else if (GetKeyboardPress(DIK_UP))
	{// �O�ړ�
		g_moveEnemy.x -= sinf(D3DX_PI + rotCamera.y) * VALUE_MOVE_ENEMY;
		g_moveEnemy.z -= cosf(D3DX_PI + rotCamera.y) * VALUE_MOVE_ENEMY;

		g_rotDestEnemy.y = D3DX_PI + rotCamera.y;
	}
	else if (GetKeyboardPress(DIK_DOWN))
	{// ��ړ�
		g_moveEnemy.x -= sinf(rotCamera.y) * VALUE_MOVE_ENEMY;
		g_moveEnemy.z -= cosf(rotCamera.y) * VALUE_MOVE_ENEMY;

		g_rotDestEnemy.y = rotCamera.y;
	}

	if (GetKeyboardPress(DIK_LSHIFT))
	{// ����]
		g_rotDestEnemy.y -= VALUE_ROTATE_ENEMY;
		if (g_rotDestEnemy.y < -D3DX_PI)
		{
			g_rotDestEnemy.y += D3DX_PI * 2.0f;
		}
	}
	if (GetKeyboardPress(DIK_RSHIFT))
	{// �E��]
		g_rotDestEnemy.y += VALUE_ROTATE_ENEMY;
		if (g_rotDestEnemy.y > D3DX_PI)
		{
			g_rotDestEnemy.y -= D3DX_PI * 2.0f;
		}
	}

	if (GetKeyboardPress(DIK_I))
	{// �㏸
		g_moveEnemy.y += VALUE_MOVE_ENEMY * 0.5f;

		if (g_posEnemy.y < 75.0f)
		{
			shadow->g_fSizeShadow += 0.2f;
			shadow->g_colShadow.a -= 0.004f;
		}
	}
	if (GetKeyboardPress(DIK_K))
	{// ���~
		g_moveEnemy.y -= VALUE_MOVE_ENEMY * 0.5f;

		if (g_posEnemy.y > 5.0f)
		{
			shadow->g_fSizeShadow -= 0.2f;
			shadow->g_colShadow.a += 0.004f;
		}
	}

	// �ړI�̊p�x�܂ł̍���
	fDiffRotY = g_rotDestEnemy.y - g_rotEnemy.y;
	if (fDiffRotY > D3DX_PI)
	{
		fDiffRotY -= D3DX_PI * 2.0f;
	}
	if (fDiffRotY < -D3DX_PI)
	{
		fDiffRotY += D3DX_PI * 2.0f;
	}

	// �ړI�̊p�x�܂Ŋ�����������
	g_rotEnemy.y += fDiffRotY * RATE_ROTATE_ENEMY;
	if (g_rotEnemy.y > D3DX_PI)
	{
		g_rotEnemy.y -= D3DX_PI * 2.0f;
	}
	if (g_rotEnemy.y < -D3DX_PI)
	{
		g_rotEnemy.y += D3DX_PI * 2.0f;
	}

	/// �ʒu�ړ�
	g_posEnemy.x += g_moveEnemy.x;
	g_posEnemy.y += g_moveEnemy.y;
	if (g_posEnemy.y < 5.0f)
	{
		g_posEnemy.y = 5.0f;
	}
	if (g_posEnemy.y > 75.0f)
	{
		g_posEnemy.y = 75.0f;
	}
	g_posEnemy.z += g_moveEnemy.z;

	// �ړ��ʂɊ�����������
	g_moveEnemy.x += (0.0f - g_moveEnemy.x) * RATE_MOVE_ENEMY;
	g_moveEnemy.y += (0.0f - g_moveEnemy.y) * RATE_MOVE_ENEMY;
	g_moveEnemy.z += (0.0f - g_moveEnemy.z) * RATE_MOVE_ENEMY;

	if (g_posEnemy.x < -310.0f)
	{
		g_posEnemy.x = -310.0f;
	}
	if (g_posEnemy.x > 310.0f)
	{
		g_posEnemy.x = 310.0f;
	}
	if (g_posEnemy.z < -310.0f)
	{
		g_posEnemy.z = -310.0f;
	}
	if (g_posEnemy.z > 310.0f)
	{
		g_posEnemy.z = 310.0f;
	}

	// �e�̈ʒu�ݒ�
	SetPositionShadow(shadow->g_nIdxShadow, D3DXVECTOR3(g_posEnemy.x, 0.1f, g_posEnemy.z));

	SetVertexShadow(shadow->g_nIdxShadow, shadow->g_fSizeShadow, shadow->g_fSizeShadow);
	SetColorShadow(shadow->g_nIdxShadow, shadow->g_colShadow);

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	SHADOW *shadow = GetShadow(0);
	D3DMATERIAL9 matDef;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldEnemy);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotEnemy.y, g_rotEnemy.x, g_rotEnemy.z);
	D3DXMatrixMultiply(&g_mtxWorldEnemy, &g_mtxWorldEnemy, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, g_posEnemy.x, g_posEnemy.y, g_posEnemy.z);
	D3DXMatrixMultiply(&g_mtxWorldEnemy, &g_mtxWorldEnemy, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldEnemy);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	shadow->pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatEnemy->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatEnemy; nCntMat++)
	{
		// �}�e���A���̐ݒ�	
		pDevice->SetMaterial(&shadow->pD3DXMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureEnemy);

		// �`��
		g_pD3DXMeshEnemy->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �ʒu�擾
//=============================================================================
D3DXVECTOR3 GetPositionEnemy(void)
{
	return g_posEnemy;
}

//=============================================================================
// �����擾
//=============================================================================
D3DXVECTOR3 GetRotationEnemy(void)
{
	return g_rotEnemy;
}

//=============================================================================
// �ړI�̌����擾
//=============================================================================
D3DXVECTOR3 GetRotationDestEnemy(void)
{
	return g_rotDestEnemy;
}



SHADOW *GetShadow(int no)
{
	return(&shadowWk[no]);
}