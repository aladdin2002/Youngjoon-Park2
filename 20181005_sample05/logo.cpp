//=============================================================================
//
// �^�C�g����ʏ��� [logo.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "logo.h"
#include "input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexLogo(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureLogo = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureLogoLogo = NULL;	// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkLogo[NUM_VERTEX];			// ���_���i�[���[�N
VERTEX_2D				g_vertexWkLogoLogo[NUM_VERTEX];		// ���_���i�[���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_LOGO,				// �t�@�C���̖��O
		&g_pD3DTextureLogo);		// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_LOGO_LOGO,			// �t�@�C���̖��O
		&g_pD3DTextureLogoLogo);	// �ǂݍ��ރ������[

// ���_���̍쐬
	MakeVertexLogo();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitLogo(void)
{
	if (g_pD3DTextureLogo != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureLogo->Release();
		g_pD3DTextureLogo = NULL;
	}

	if (g_pD3DTextureLogoLogo != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureLogoLogo->Release();
		g_pD3DTextureLogoLogo = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateLogo(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{// Enter��������A�X�e�[�W��؂�ւ���
		SetStage(STAGE_TITLE);
	}
	// �Q�[���p�b�h�łňړ�����
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
// �`�揈��
//=============================================================================
void DrawLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureLogo);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkLogo, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureLogoLogo);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkLogoLogo, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexLogo(void)
{

	// ���_���W�̐ݒ�
	g_vertexWkLogo[0].vtx = D3DXVECTOR3(LOGO_POS_X, LOGO_POS_Y, 0.0f);
	g_vertexWkLogo[1].vtx = D3DXVECTOR3(LOGO_POS_X + LOGO_SIZE_X, LOGO_POS_Y, 0.0f);
	g_vertexWkLogo[2].vtx = D3DXVECTOR3(LOGO_POS_X, LOGO_POS_Y + LOGO_SIZE_Y, 0.0f);
	g_vertexWkLogo[3].vtx = D3DXVECTOR3(LOGO_POS_X + LOGO_SIZE_X, LOGO_POS_Y + LOGO_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkLogo[0].rhw =
		g_vertexWkLogo[1].rhw =
		g_vertexWkLogo[2].rhw =
		g_vertexWkLogo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	g_vertexWkLogoLogo[0].vtx = D3DXVECTOR3(LOGOLOGO_POS_X, LOGOLOGO_POS_Y, 0.0f);
	g_vertexWkLogoLogo[1].vtx = D3DXVECTOR3(LOGOLOGO_POS_X + LOGOLOGO_SIZE_X, LOGOLOGO_POS_Y, 0.0f);
	g_vertexWkLogoLogo[2].vtx = D3DXVECTOR3(LOGOLOGO_POS_X, LOGOLOGO_POS_Y + LOGOLOGO_SIZE_Y, 0.0f);
	g_vertexWkLogoLogo[3].vtx = D3DXVECTOR3(LOGOLOGO_POS_X + LOGOLOGO_SIZE_X, LOGOLOGO_POS_Y + LOGOLOGO_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkLogoLogo[0].rhw =
		g_vertexWkLogoLogo[1].rhw =
		g_vertexWkLogoLogo[2].rhw =
		g_vertexWkLogoLogo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkLogoLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkLogoLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkLogoLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkLogoLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkLogoLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkLogoLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkLogoLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkLogoLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}