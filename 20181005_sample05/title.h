//=============================================================================
//
// タイトル画面処理 [title.h]
// Author : 
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TITLE		"data/TEXTURE/grassland.png"			// 読み込むテクスチャファイル名
#define	TEXTURE_TITLE_LOGO	"data/TEXTURE/title_logo.png"		// 読み込むテクスチャファイル名
#define	TITLE_POS_X			(0)								// タイトルの表示位置
#define	TITLE_POS_Y			(0)								// タイトルの表示位置
#define	TITLE_SIZE_X		(800)							// タイトルの幅
#define	TITLE_SIZE_Y		(600)							// タイトルの高さ
#define	TITLELOGO_POS_X		(160)							// タイトルロゴの表示位置
#define	TITLELOGO_POS_Y		(200)							// タイトルロゴの表示位置
#define	TITLELOGO_SIZE_X	(480)							// タイトルロゴの幅
#define	TITLELOGO_SIZE_Y	(80)							// タイトルロゴの高さ


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif

