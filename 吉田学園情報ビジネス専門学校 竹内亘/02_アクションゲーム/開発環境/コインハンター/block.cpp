//=============================================================================
//
// ブロック処理 [block.cpp]
// Author :竹内亘
//
//=============================================================================
#include "block.h"
#include "player.h"
#include "explosion.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_BLOCK			(256 * 2)							//ブロックの最大数
#define BLOCK_TEXTURENAME	"data/TEXTURE/block000.jpg"			//テクスチャ名
#define BLOCK_TEXTURENAME2	"data/TEXTURE/block500.png"			//テクスチャ名
#define BLOCK_TEXTURENAME3	"data/TEXTURE/block100.png"			//テクスチャ名
#define BLOCK_TEXTURENAME4	"data/TEXTURE/bane.png"				//テクスチャ名
#define BLOCK_TEXTURENAME5	"data/TEXTURE/block200.jpg"			//テクスチャ名

#define BLOCK_SIZE			(20)								//ブロックの大きさ
#define BLOCK_SIZE1			(100)								//ブロックの大きさ
#define BLOCK_X				(200)								//ブロックのX座標
#define BLOCK_Y				(50)								//ブロックのY座標
#define MAX_TYPE_BLOCK		(30)								//ブロックの種類
//#define POLYGON_X			(1200)								//ポリゴンのX座標
//#define POLYGON_Y			(350)								//ポリゴンのY座標

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBlock[MAX_TYPE_BLOCK] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	//頂点バッファへのポインタ
Block g_aBlock[MAX_BLOCK];


//=============================================================================
// ブロックの初期化処理
//=============================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//デバイスの取得
	pDevice = GetDevice();

	//ブロックの情報の各初期化
	for(nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aBlock[nCntBlock].fWidth = 0.0f;
		g_aBlock[nCntBlock].fHeight = 0.0f;
		g_aBlock[nCntBlock].nType = BLOCKTYPE_NOMALL;
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTURENAME, &g_pTextureBlock[0]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTURENAME2, &g_pTextureBlock[1]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTURENAME2, &g_pTextureBlock[2]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTURENAME3, &g_pTextureBlock[3]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTURENAME3, &g_pTextureBlock[4]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTURENAME4, &g_pTextureBlock[5]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTURENAME5, &g_pTextureBlock[6]);

	//頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,	//確保するバッファのサイズ
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,						//頂点フォーマット
								D3DPOOL_MANAGED,
								&g_pVtxBuffBlock,
								NULL);
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y , 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y , 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//頂点データを４つ分進める
	}
	//頂点バッファをアンロック
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// ブロックの終了処理
//=============================================================================
void UninitBlock(void)
{
	int nCntTex;

	for (nCntTex = 0; nCntTex < MAX_TYPE_BLOCK; nCntTex++)
	{
		//テクスチャの開放
		if (g_pTextureBlock[nCntTex] != NULL)
		{
			g_pTextureBlock[nCntTex]->Release();
			g_pTextureBlock[nCntTex] = NULL;
		}

		//頂点バッファの開放
		if (g_pVtxBuffBlock != NULL)
		{
			g_pVtxBuffBlock->Release();
			g_pVtxBuffBlock = NULL;
		}
	}

}

//=============================================================================
// ブロックの更新処理
//=============================================================================
void UpdateBlock(void)
{
	int nCntBlock;

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);

			pVtx += 4;	//頂点データを４つ分進める
		}
	}

	//頂点バッファをアンロック
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// ブロックの描画処理
//=============================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	for(nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)	//ブロックが使用されている
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].nType]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
									nCntBlock * 4,
									2);
		}
	}
}

//=============================================================================
// ブロックの設定処理
//=============================================================================
void SetBlock(D3DXVECTOR3 pos,float fWidth, float fHeight,BLOCKTYPE nType)
{
	//ブロックを分割する変数
	float  fBlockHeight;
	float  fBlockWidth;

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
	int nCntBlock;

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].nType = nType;

			g_aBlock[nCntBlock].fHeight = fHeight;
			g_aBlock[nCntBlock].fWidth = fWidth;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);

			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			fBlockHeight = g_aBlock[nCntBlock].fHeight / 50;
			fBlockWidth = g_aBlock[nCntBlock].fWidth / 50;

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(fBlockWidth, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, fBlockHeight);
			pVtx[3].tex = D3DXVECTOR2(fBlockWidth, fBlockHeight);

			if (g_aBlock[nCntBlock].nType == BLOCKTYPE_BERUTOKONBEA)
			{
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			}
			else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_BERUTOKONBEA2)
			{
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			}
			else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_PUSH)
			{

			}

			g_aBlock[nCntBlock].bUse = true;	//使用してる
			break;
		}
		pVtx += 4;	//頂点データを４つ分進める
	}

	//頂点バッファをアンロック
	g_pVtxBuffBlock->Unlock();
}
//=============================================================================
// ブロックの当たり判定
//=============================================================================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove ,float * fWidth, float * fHeight ,Block **pBlock)
{
	int nCntBlock;

	bool bLand = false;			//着地したかどうか

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//ブロックが使われている
			if (pPos->x + (*fWidth / 2) > g_aBlock[nCntBlock].pos.x &&
				pPos->x - (*fWidth / 2) < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
			{//縦判定
				if (pPos->y >= g_aBlock[nCntBlock].pos.y && pPosold->y <= g_aBlock[nCntBlock].pos.y)
				{//上からめり込んだ場合
					bLand = true;
					pPos->y = g_aBlock[nCntBlock].pos.y;
					pMove->y = 0.0f;

					if (g_aBlock[nCntBlock].nType == BLOCKTYPE_BERUTOKONBEA)
					{//ベルトコンベア右
						g_aBlock[nCntBlock].pos.x += g_aBlock[nCntBlock].move.x;		//横移動
						pPos->x = pPosold->x + 7;
						pMove->y = 0.0f;
					}
					else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_BERUTOKONBEA2)
					{//ベルトコンベア左
						g_aBlock[nCntBlock].pos.x += g_aBlock[nCntBlock].move.x;		//横移動
						pPos->x = pPosold->x - 3;
						pMove->y = 0.0f;
					}
					//else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_BERUTOKONBEA3)
					//{//ベルトコンベア左
					//	g_aBlock[nCntBlock].pos.x += g_aBlock[nCntBlock].move.x;		//横移動
					//	pPos->x = pPosold->x + 5;
					//	pMove->y = 0.0f;
					//}

					else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_JUMP)
					{//ジャンプブロック
						g_aBlock[nCntBlock].pos.y += g_aBlock[nCntBlock].move.y;		//縦移動
						pMove->y = -6.0f;
						PlaySound(SOUND_LABEL_SE_JUMP001);
					}
					else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_FALL)
					{//落下ブロック
						g_aBlock[nCntBlock].pos.y = g_aBlock[nCntBlock].pos.y * 10.0f;
					}
					else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_PUSH)
					{//押せるブロック
						pMove->y = 0.0f;
					}
					//if (g_aBlock[nCntBlock].pos.y >= 680)
					//{//応急処置で使える
					//	g_aBlock[nCntBlock].pos.y = 680;
					//	g_aBlock[nCntBlock].move.y = 0.0f;
					//	g_aBlock[nCntBlock].bUse = false;
					//}
				}
				else if (pPos->y - *fHeight < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight &&
					pPosold->y - *fHeight  >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
				{//下からめり込んだ場合
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + *fHeight;
					pMove->y = 0.0f;

					if (g_aBlock[nCntBlock].nType == BLOCKTYPE_BREAK)
					{//壊せるブロック
						g_aBlock[nCntBlock].bUse = false;
						//SetExplosion(g_aBlock[nCntBlock].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
						PlaySound(SOUND_LABEL_SE_BREAK);

					}
				}
				else if (pPos->y > g_aBlock[nCntBlock].pos.y  &&
					pPos->y - (*fHeight / 2) - 10 < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
				{//横判定
					if (pPos->x + *fWidth + 10 >= g_aBlock[nCntBlock].pos.x &&
						pPosold->x - *fWidth +10 <= g_aBlock[nCntBlock].pos.x)
					{//左からめり込んだ場合
						pPos->x = g_aBlock[nCntBlock].pos.x - *fWidth + 10;
						//pPosold->x = g_aBlock[nCntBlock].pos.x - *fWidth + 10;
						pMove->x = 0.0f;

						if (g_aBlock[nCntBlock].nType == BLOCKTYPE_PUSH)
						{//押せるブロック
							g_aBlock[nCntBlock].pos.x = g_aBlock[nCntBlock].pos.x + 3.0f;			//横移動
							PlaySound(SOUND_LABEL_SE_OSU);

						}

					}
					else if (pPos->x - *fWidth - 10<= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth &&
						pPosold->x + *fWidth -10 >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
					{//右からめり込んだ場合
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + *fWidth  - 10;
						//pPosold->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + *fWidth - 10;
						pMove->x = 0.0f;
						if (g_aBlock[nCntBlock].nType == BLOCKTYPE_PUSH)
						{//押せるブロック
							g_aBlock[nCntBlock].pos.x = g_aBlock[nCntBlock].pos.x - 2.0f;		//横移動
							PlaySound(SOUND_LABEL_SE_OSU);
						}
					}
				}
			}
		}
	}
	//if (pBlock != NULL)
	//{//後で使う
	//	*pBlock = &g_aBlock[];
	//}
	return bLand;
}
