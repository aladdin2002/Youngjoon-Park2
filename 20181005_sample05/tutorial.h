//=============================================================================
//
// �^�C�g����ʏ��� [turorial.h]
// Author : 
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TUTORIAL		"data/TEXTURE/nojyo.png"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_TUTORIAL_LOGO	"data/TEXTURE/tutoriall.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TUTORIAL_POS_X			(0)								// �^�C�g���̕\���ʒu
#define	TUTORIAL_POS_Y			(0)								// �^�C�g���̕\���ʒu
#define	TUTORIAL_SIZE_X		(800)							// �^�C�g���̕�
#define	TUTORIAL_SIZE_Y		(600)							// �^�C�g���̍���
#define	TUTORIALLOGO_POS_X		(160)							// �^�C�g�����S�̕\���ʒu
#define	TUTORIALLOGO_POS_Y		(200)							// �^�C�g�����S�̕\���ʒu
#define	TUTORIALLOGO_SIZE_X	(480)							// �^�C�g�����S�̕�
#define	TUTORIALLOGO_SIZE_Y	(300)							// �^�C�g�����S�̍���


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

#endif


