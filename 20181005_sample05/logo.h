//=============================================================================
//
// �^�C�g����ʏ��� [logo.h]
// Author : 
//
//=============================================================================
#ifndef _LOGO_H_
#define _LOGO_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_LOGO		"data/TEXTURE/LighteningCat.png"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_LOGO_LOGO	"data/TEXTURE/�ΎR����.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	LOGO_POS_X			(0)								// �^�C�g���̕\���ʒu
#define	LOGO_POS_Y			(0)								// �^�C�g���̕\���ʒu
#define	LOGO_SIZE_X		(800)							// �^�C�g���̕�
#define	LOGO_SIZE_Y		(600)							// �^�C�g���̍���
#define	LOGOLOGO_POS_X		(300)							// �^�C�g�����S�̕\���ʒu
#define	LOGOLOGO_POS_Y		(100)							// �^�C�g�����S�̕\���ʒu
#define	LOGOLOGO_SIZE_X	(480)							// �^�C�g�����S�̕�
#define	LOGOLOGO_SIZE_Y	(300)							// �^�C�g�����S�̍���


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitLogo(void);
void UninitLogo(void);
void UpdateLogo(void);
void DrawLogo(void);

#endif


