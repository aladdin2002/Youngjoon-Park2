//=============================================================================
//
// 木処理 [tree.cpp]
// Author : 
//
//=============================================================================
#include "tree.h"
#include "camera.h"
#include "shadow.h"
#include "input.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TREE		"data/TEXTURE/sakura.png"		// 読み込むテクスチャファイル名
#define	TREE_WIDTH			(50.0f)							// 弾の半径幅
#define	TREE_HEIGHT			(80.0f)							// 弾の半径幅
#define	VALUE_MOVE_TREE		(3.00f)							// 移動速度

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTree(LPDIRECT3DDEVICE9 pDevice);
void SetVertexTree(int nIdxTree, float fWidth, float fHeight);
void SetColorTree(int nIdxTree, D3DXCOLOR col);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
ALPHA *alpha[1];
LPDIRECT3DTEXTURE9		g_apD3DTextureTree[5] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffTree = NULL;		// 頂点バッファインターフェースへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffBill = NULL;	// 頂点バッファインターフェースへのポインタ
TREE					g_aTree[MAX_TREE];				// 木ワーク
ALPHA				alphaWk[ALPHA_MAX];			// プレイヤー構造体


const char *g_aFileName[] =
{
	"data/TEXTURE/sakura.png",
	"data/TEXTURE/sakura.png",
	"data/TEXTURE/sakura.png",
	"data/TEXTURE/sakura.png",
	"data/TEXTURE/sakura.png",
};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTree(void)
{
	ALPHA *alpha = GetAlpha(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertexTree(pDevice);

	// テクスチャの読み込み
	for(int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
									g_aFileName[nCntTex],			// ファイルの名前
									&g_apD3DTextureTree[nCntTex]);	// 読み込むメモリー
	}

	for(int nCntTree = 0; nCntTree < MAX_TREE; nCntTree++)
	{
		g_aTree[nCntTree].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTree[nCntTree].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aTree[nCntTree].fWidth = TREE_WIDTH;
		g_aTree[nCntTree].fHeight = TREE_HEIGHT;
		g_aTree[nCntTree].bUse = false;
	}

	alpha->g_bAlpaTest = false;
	alpha->g_nAlpha = 0x0;

	// 木の設定
	SetTree(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f, 90.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetTree(D3DXVECTOR3(200.0f, 0.0f, 0.0f), 60.0f, 90.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetTree(D3DXVECTOR3(-200.0f, 0.0f, 0.0f), 60.0f, 90.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetTree(D3DXVECTOR3(0.0f, 0.0f, 200.0f), 60.0f, 90.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetTree(D3DXVECTOR3(0.0f, 0.0f, -200.0f), 60.0f, 90.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTree(void)
{
	for(int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		if(g_apD3DTextureTree[nCntTex] != NULL)
		{// テクスチャの開放
			g_apD3DTextureTree[nCntTex]->Release();
			g_apD3DTextureTree[nCntTex] = NULL;
		}
	}

	if(g_pD3DVtxBuffTree != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffTree->Release();
		g_pD3DVtxBuffTree = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTree(void)
{
	ALPHA *alpha = GetAlpha(0);
	for(int nCntTree = 0; nCntTree < MAX_TREE; nCntTree++)
	{
		if(g_aTree[nCntTree].bUse)
		{
			// 影の位置設定
			SetPositionShadow(g_aTree[nCntTree].nIdxShadow, D3DXVECTOR3(g_aTree[nCntTree].pos.x, 0.1f, g_aTree[nCntTree].pos.z));
		}
	}

	// アルファテストON/OFF
	if(GetKeyboardTrigger(DIK_F1))
	{
	alpha->g_bAlpaTest = alpha->g_bAlpaTest ? false: true;
	}

	// アルファテストの閾値変更
	if(GetKeyboardPress(DIK_I))
	{
		alpha->g_nAlpha--;
		if(alpha->g_nAlpha < 0)
		{
			alpha->g_nAlpha = 0;
		}
	}
	if(GetKeyboardPress(DIK_K))
	{
		alpha->g_nAlpha++;
		if(alpha->g_nAlpha > 255)
		{
			alpha->g_nAlpha = 255;
		}
	}

	PrintDebugProc("*** アルファテスト ***\n");
	PrintDebugProc("ON / OFF：[F1] ( 現在：");
	if(alpha->g_bAlpaTest == true)
	{
		PrintDebugProc("ON");
	}
	else
	{
		PrintDebugProc("OFF");
	}
	PrintDebugProc(" )\n");

	if(alpha->g_bAlpaTest == true)
	{
		PrintDebugProc("アルファ閾値：減少[I] / 増加[K] ( 閾値：%d )\n", alpha->g_nAlpha);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTree(void)
{
	ALPHA *alpha = GetAlpha(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// αテスト設定 iguhamyun dienamuboim
	if(alpha->g_bAlpaTest == true)
	{
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, alpha->g_nAlpha);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	}

	// ラインティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for(int nCntTree = 0; nCntTree < MAX_TREE; nCntTree++)
	{
		if(g_aTree[nCntTree].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aTree[nCntTree].mtxWorld);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			// ポリゴンを正面に向ける
#if 1
			// 逆行列をもとめる
			D3DXMatrixInverse(&g_aTree[nCntTree].mtxWorld, NULL, &mtxView);
			g_aTree[nCntTree].mtxWorld._41 = 0.0f;
			g_aTree[nCntTree].mtxWorld._42 = 0.0f;
			g_aTree[nCntTree].mtxWorld._43 = 0.0f;
#else
			g_aTree[nCntTree].mtxWorld._11 = mtxView._11;
			g_aTree[nCntTree].mtxWorld._12 = mtxView._21;
			g_aTree[nCntTree].mtxWorld._13 = mtxView._31;
			g_aTree[nCntTree].mtxWorld._21 = mtxView._12;
			g_aTree[nCntTree].mtxWorld._22 = mtxView._22;
			g_aTree[nCntTree].mtxWorld._23 = mtxView._32;
			g_aTree[nCntTree].mtxWorld._31 = mtxView._13;
			g_aTree[nCntTree].mtxWorld._32 = mtxView._23;
			g_aTree[nCntTree].mtxWorld._33 = mtxView._33;
#endif

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, g_aTree[nCntTree].scl.x,
											g_aTree[nCntTree].scl.y,
											g_aTree[nCntTree].scl.z);
			D3DXMatrixMultiply(&g_aTree[nCntTree].mtxWorld, &g_aTree[nCntTree].mtxWorld, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_aTree[nCntTree].pos.x,
													g_aTree[nCntTree].pos.y,
													g_aTree[nCntTree].pos.z);
			D3DXMatrixMultiply(&g_aTree[nCntTree].mtxWorld, &g_aTree[nCntTree].mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aTree[nCntTree].mtxWorld);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffTree, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_apD3DTextureTree[nCntTree % 5]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntTree * 4), NUM_POLYGON);
		}
	}

	// ラインティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// αテストを無効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexTree(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_TREE,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,						// 頂点バッファの使用法　
												FVF_VERTEX_3D,							// 使用する頂点フォーマット
												D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffTree,						// 頂点バッファインターフェースへのポインタ
												NULL)))									// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffTree->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntTree = 0; nCntTree < MAX_TREE; nCntTree++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-TREE_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(-TREE_WIDTH / 2.0f, TREE_HEIGHT, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(TREE_WIDTH / 2.0f, 0.0f, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(TREE_WIDTH / 2.0f, TREE_HEIGHT, 0.0f);

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		}

		// 頂点データをアンロックする
		g_pD3DVtxBuffTree->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexTree(int nIdxTree, float fWidth, float fHeight)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffTree->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxTree * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fWidth / 2.0f, fHeight, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fWidth / 2.0f, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fWidth / 2.0f, fHeight, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffTree->Unlock();
	}
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorTree(int nIdxTree, D3DXCOLOR col)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffTree->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxTree * 4);

		// 頂点座標の設定
		pVtx[0].diffuse = col;
		pVtx[1].diffuse = col;
		pVtx[2].diffuse = col;
		pVtx[3].diffuse = col;

		// 頂点データをアンロックする
		g_pD3DVtxBuffTree->Unlock();
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
int SetTree(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col)
{
	int nIdxTree = -1;

	for(int nCntTree = 0; nCntTree < MAX_TREE; nCntTree++)
	{
		if(!g_aTree[nCntTree].bUse)
		{
			g_aTree[nCntTree].pos = pos;
			g_aTree[nCntTree].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_aTree[nCntTree].fWidth = fWidth;
			g_aTree[nCntTree].fHeight = fHeight;
			g_aTree[nCntTree].bUse = true;

			// 頂点座標の設定
			SetVertexTree(nCntTree, fWidth, fHeight);

			// 頂点カラーの設定
			SetColorTree(nCntTree, col);

			// 影の設定
			g_aTree[nCntTree].nIdxShadow = CreateShadow(g_aTree[nCntTree].pos, g_aTree[nCntTree].fWidth, g_aTree[nCntTree].fWidth);

			nIdxTree = nCntTree;

			break;
		}
	}

	return nIdxTree;
}

//=============================================================================
// 木を取得
//=============================================================================
TREE *GetTree(void)
{
	return &g_aTree[0];
}

ALPHA *GetAlpha(int no)
{
	return(&alphaWk[no]);
}



//=============================================================================
// 内積
//=============================================================================
float dotProduct(D3DXVECTOR3 *vl, D3DXVECTOR3 *vr)
{
	float ans = vl->x * vr->x + vl->y* vr->y + vl->z * vr->z;


	return(ans);
}


//=============================================================================
// 外積
//=============================================================================
void crossProduct(D3DXVECTOR3 *ret, D3DXVECTOR3 *vl, D3DXVECTOR3 *vr)
{
	ret->x = vl->y*vr->z - vl->z*vr->y;
	ret->y = vl->z*vr->x - vl->x*vr->z;
	ret->z = vl->x*vr->y - vl->y*vr->x;



}


//=============================================================================
// ポリゴンと線分との当たり判定
// p0  :ポリゴンの頂点1
// p1  :ポリゴンの頂点2
// p2  :ポリゴンの頂点3
// pos0:始点（移動前）
// pos1:終点（移動後）
//=============================================================================
int hitCheck(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1)
{
	D3DXVECTOR3		nor;		// ポリゴンの法線

	{	// ポリゴンの外積をとって法線を求める。そして正規化しておく。
		D3DXVECTOR3		vec01 = p1 - p0;
		D3DXVECTOR3		vec02 = p2 - p0;
		crossProduct(&nor, &vec01, &vec02);
		D3DXVec3Normalize(&nor, &nor);

	}

	{	// 平面と線分の内積とって衝突している可能性を調べる
		// 求めた法線とベクトル２つ（線分の両端とポリゴン上の任意の点）の内積とって衝突している可能性を調べる
		D3DXVECTOR3		vec1 = pos0 - p0;
		D3DXVECTOR3		vec2 = pos1 - p0;
		float a = dotProduct(&vec1, &nor);
		float b = dotProduct(&vec2, &nor);
		if ((a * b) > 0)
		{
			// 当たっている可能性は無い
			return(0);
		}
	}


	{	// ポリゴンと線分の交点を求める
		D3DXVECTOR3		vec1 = pos0 - p0;
		D3DXVECTOR3		vec2 = pos1 - p0;
		float			d1 = fabs(dotProduct(&nor, &vec1));					// 内分比を求める為の点とポリゴンとの距離
		float			d2 = fabs(dotProduct(&nor, &vec2));					// 内分比を求める為の点とポリゴンとの距離
		float			a = d1 / (d1 + d2);					// 内分比
		D3DXVECTOR3		vec3 = (1 - a)*vec1 + a * vec2;
		D3DXVECTOR3		p3 = p0 + vec3;					// 交点



		{	// 求めた交点がポリゴンの中にあるか調べる

			// ポリゴンの各辺のベクトル
			D3DXVECTOR3		v1 = p1 - p0;
			D3DXVECTOR3		v2 = p2 - p1;
			D3DXVECTOR3		v3 = p0 - p2;

			// 各頂点と交点とのベクトル
			D3DXVECTOR3		v4 = p3 - p1;
			D3DXVECTOR3		v5 = p3 - p2;
			D3DXVECTOR3		v6 = p3 - p0;

			// 各辺との外積で法線を求める
			D3DXVECTOR3		n1, n2, n3;
			crossProduct(&n1, &v1, &v4);
			crossProduct(&n2, &v2, &v5);
			crossProduct(&n3, &v3, &v6);

			// それぞれのベクトルの向きを内積でチェック
			if (dotProduct(&n1, &nor) < 0)return(0);
			if (dotProduct(&n2, &nor) < 0)return(0);
			if (dotProduct(&n3, &nor) < 0)return(0);

		}
	}

	return(1);
}


//=============================================================================
// ビルボードとの当たり判定
// pos0:始点（移動前）
// pos1:終点（移動後）
//=============================================================================
int hitCheckBill(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1)
{
	int				ans = 0;	// 一先ず当たっていないをセットしておく

	D3DXVECTOR3		pos[4];
	D3DXVECTOR3		nor;		// ポリゴンの法線

								// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	VERTEX_3D		*pVtx;
	g_pD3DVtxBuffBill->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < 1; i++, pVtx += 4)
	{	// まずは、ポリゴンの頂点を求める

		// 頂点座標の設定
		pos[0] = pVtx[0].vtx;
		pos[1] = pVtx[1].vtx;
		pos[2] = pVtx[2].vtx;
		pos[3] = pVtx[3].vtx;

		// 左下側ポリゴンと線分の当たり判定
		ans = hitCheck(pos[0], pos[2], pos[3], pos0, pos1);
		if (ans != 0) break;

		// 右上側ポリゴンと線分の当たり判定
		ans = hitCheck(pos[0], pos[3], pos[1], pos0, pos1);
		if (ans != 0) break;

	}

	// 頂点データをアンロックする
	g_pD3DVtxBuffBill->Unlock();




	return(ans);

}
