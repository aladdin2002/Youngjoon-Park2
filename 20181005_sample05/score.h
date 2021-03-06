//=============================================================================
//
// スコア処理 [score.h]
// Author : 
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

// マクロ定義
#define TEXTURE_GAME_SCORE00	"data/TEXTURE/number16x32.png"	// サンプル用画像
#define TEXTURE_SCORE00_SIZE_X	(16)	// テクスチャサイズ
#define TEXTURE_SCORE00_SIZE_Y	(32)	// 同上
#define SCORE_POS_X			(500)		// ポリゴンの初期位置X
#define SCORE_POS_Y			(20)		// 同上
#define SCORE_MAX			(99999)		// スコアの最大値
#define SCORE_DIGIT			(5)			// 桁数


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitScore(int type);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void AddScore(int add);

#endif
