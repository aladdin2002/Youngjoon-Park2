//=============================================================================
//
// タイトル画面処理 [turorial.h]
// Author : 
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TUTORIAL		"data/TEXTURE/nojyo.png"			// 読み込むテクスチャファイル名
#define	TEXTURE_TUTORIAL_LOGO	"data/TEXTURE/tutoriall.png"		// 読み込むテクスチャファイル名
#define	TUTORIAL_POS_X			(0)								// タイトルの表示位置
#define	TUTORIAL_POS_Y			(0)								// タイトルの表示位置
#define	TUTORIAL_SIZE_X		(800)							// タイトルの幅
#define	TUTORIAL_SIZE_Y		(600)							// タイトルの高さ
#define	TUTORIALLOGO_POS_X		(160)							// タイトルロゴの表示位置
#define	TUTORIALLOGO_POS_Y		(200)							// タイトルロゴの表示位置
#define	TUTORIALLOGO_SIZE_X	(480)							// タイトルロゴの幅
#define	TUTORIALLOGO_SIZE_Y	(300)							// タイトルロゴの高さ


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

#endif


