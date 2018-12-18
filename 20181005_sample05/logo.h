//=============================================================================
//
// タイトル画面処理 [logo.h]
// Author : 
//
//=============================================================================
#ifndef _LOGO_H_
#define _LOGO_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_LOGO		"data/TEXTURE/LighteningCat.png"			// 読み込むテクスチャファイル名
#define	TEXTURE_LOGO_LOGO	"data/TEXTURE/火山爆発.png"		// 読み込むテクスチャファイル名
#define	LOGO_POS_X			(0)								// タイトルの表示位置
#define	LOGO_POS_Y			(0)								// タイトルの表示位置
#define	LOGO_SIZE_X		(800)							// タイトルの幅
#define	LOGO_SIZE_Y		(600)							// タイトルの高さ
#define	LOGOLOGO_POS_X		(300)							// タイトルロゴの表示位置
#define	LOGOLOGO_POS_Y		(100)							// タイトルロゴの表示位置
#define	LOGOLOGO_SIZE_X	(480)							// タイトルロゴの幅
#define	LOGOLOGO_SIZE_Y	(300)							// タイトルロゴの高さ


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitLogo(void);
void UninitLogo(void);
void UpdateLogo(void);
void DrawLogo(void);

#endif


