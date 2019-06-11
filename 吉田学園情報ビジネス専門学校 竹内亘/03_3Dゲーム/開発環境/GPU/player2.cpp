//=============================================================================
//
// プレイヤー処理(親子関係なし) [player2.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "player2.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"
#include "meshWall.h"
#include "item2.h"
#include "model.h"
#include "enemy2.h"
#include "life.h"
#include "fade.h"
#include "game.h"
#include "effect.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_NAME "data/MODEL/houki2.x"	// モデル名
#define MOVE_SPEED (1.0f)					// プレイヤーの動くスピード
#define	MAX_MODEL (10)						// 読み込むモデルの数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXMESH g_pMeshPlayer2 = NULL;				// メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatPlayer2 = NULL;			// マテリアル情報へのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePlayer2 = NULL;	// テクスチャへのポインタ
DWORD g_nNumMatPlayer2 = 0;						// マテリアル情報の数
//D3DXVECTOR3 g_posModel;						// 位置
//D3DXVECTOR3 g_rotModel;						// 向き
//D3DXMATRIX g_mtxWorldModel;					// ワールドマトリックス
Player2 g_Player2;								// モデルの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX(PLAYER_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer2,
		NULL,
		&g_nNumMatPlayer2,
		&g_pMeshPlayer2);

	// プレイヤーの初期化
	g_Player2.pos = D3DXVECTOR3(300.0f, 50.0f, 0.0f);
	g_Player2.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player2.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player2.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player2.nIdexShadow = SetShadow(g_Player2.pos, g_Player2.rot);
	g_Player2.nLife = 5;
	g_Player2.state = PLAYERSTATE2_APPEAR;
	g_Player2.nCounterState = 120;
	g_Player2.VtxMinModel = D3DXVECTOR3(10000, 10000, 10000);
	g_Player2.VtxMaxModel = D3DXVECTOR3(-10000, -10000, -10000);
	g_Player2.bDisp = true;

	int nNumVtex;					// 頂点数
	DWORD sizeFvF;					// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;					// 頂点バッファへのポインタ

	// 頂点数を取得
	nNumVtex = g_pMeshPlayer2->GetNumVertices();

	// 頂点フォーマットのサイズを取得
	sizeFvF = D3DXGetFVFVertexSize(g_pMeshPlayer2->GetFVF());

	// 頂点バッファをロック
	g_pMeshPlayer2->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (g_Player2.VtxMinModel.x >= vtx.x)
		{
			g_Player2.VtxMinModel.x = vtx.x;
		}
		if (g_Player2.VtxMinModel.y >= vtx.y)
		{
			g_Player2.VtxMinModel.y = vtx.y;
		}
		if (g_Player2.VtxMinModel.z >= vtx.z)
		{
			g_Player2.VtxMinModel.z = vtx.z;
		}

		if (g_Player2.VtxMaxModel.x <= vtx.x)
		{
			g_Player2.VtxMaxModel.x = vtx.x;
		}
		if (g_Player2.VtxMaxModel.y <= vtx.y)
		{
			g_Player2.VtxMaxModel.y = vtx.y;
		}
		if (g_Player2.VtxMaxModel.z <= vtx.z)
		{
			g_Player2.VtxMaxModel.z = vtx.z;
		}
		pVtxBuff += sizeFvF;
	}
	// 頂点バッファをアンロック
	g_pMeshPlayer2->UnlockVertexBuffer();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer2(void)
{
	// メッシュの開放
	if (g_pMeshPlayer2 != NULL)
	{
		g_pMeshPlayer2->Release();
		g_pMeshPlayer2 = NULL;
	}

	// マテリアルの開放
	if (g_pBuffMatPlayer2 != NULL)
	{
		g_pBuffMatPlayer2->Release();
		g_pBuffMatPlayer2 = NULL;
	}

	// テクスチャの解放
	if (g_pTexturePlayer2 != NULL)
	{
		g_pTexturePlayer2->Release();
		g_pTexturePlayer2 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer2(void)
{
	// 過去の位置を取得
	g_Player2.posOld = g_Player2.pos;

	float fDiffAngle; // 差分

	// カメラの取得
	Camera *pCamera;
	pCamera = GetCamera();

	switch (g_Player2.state)
	{
	case  PLAYERSTATE2_APPEAR:
		g_Player2.nCounterState--;
		if (g_Player2.nCounterState <= 0)
		{// ある程度時間が経ったら
			g_Player2.state = PLAYERSTATE2_NORMAL;
		}
		break;

	case PLAYERSTATE2_NORMAL:
		break;

	case PLAYERSTATE2_DAMEGE:
		g_Player2.nCounterState--;
		if (g_Player2.nCounterState <= 0)
		{// ある程度時間が経ったら
			g_Player2.state = PLAYERSTATE2_NORMAL;
		}
		break;

	case PLAYERSTATE2_DEATH:
		g_Player2.nCounterState--;
		if (g_Player2.nCounterState <= 0)
		{// ある程度時間が経ったら

			SetGameState(GAMESTATE_GAMEOVER);
			g_Player2.state = PLAYERSTATE2_MAX;
		}
		break;

	}

	if (GetKeyboardPress(DIK_UP) == true || GetKeyboardPress(DIK_W) == true)
	{// ↑を押したら or Wを押したら
		if (GetKeyboardPress(DIK_RIGHT) == true || GetKeyboardPress(DIK_D) == true)
		{// 同時に→を押したら or Dを押したら
			g_Player2.move.x -= sinf(pCamera->rot.y - D3DX_PI * 0.75f) * MOVE_SPEED;
			g_Player2.move.z -= cosf(pCamera->rot.y - D3DX_PI * 0.75f) * MOVE_SPEED;

			fDiffAngle = (pCamera->rot.y - (D3DX_PI * 0.75f)) - g_Player2.rot.y;
			if (fDiffAngle > D3DX_PI)
			{
				fDiffAngle -= D3DX_PI * 2.0f;
			}
			else if (fDiffAngle < -D3DX_PI)
			{
				fDiffAngle += D3DX_PI * 2.0f;
			}

			g_Player2.rot.y += fDiffAngle * 0.3f;

			if (g_Player2.rot.y > D3DX_PI)
			{
				g_Player2.rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_Player2.rot.y < -D3DX_PI)
			{
				g_Player2.rot.y += D3DX_PI * 2.0f;
			}
		}
		else if (GetKeyboardPress(DIK_LEFT) == true || GetKeyboardPress(DIK_A) == true)
		{// 同時に←を押したら or Aを押したら
			g_Player2.move.x -= sinf(pCamera->rot.y + D3DX_PI * 0.75f) * MOVE_SPEED;
			g_Player2.move.z -= cosf(pCamera->rot.y + D3DX_PI * 0.75f) * MOVE_SPEED;

			fDiffAngle = (pCamera->rot.y + (D3DX_PI * 0.75f)) - g_Player2.rot.y;
			if (fDiffAngle > D3DX_PI)
			{
				fDiffAngle -= D3DX_PI * 2.0f;
			}
			else if (fDiffAngle < -D3DX_PI)
			{
				fDiffAngle += D3DX_PI * 2.0f;
			}

			g_Player2.rot.y += fDiffAngle * 0.3f;

			if (g_Player2.rot.y > D3DX_PI)
			{
				g_Player2.rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_Player2.rot.y < -D3DX_PI)
			{
				g_Player2.rot.y += D3DX_PI * 2.0f;
			}
		}
		else
		{
			g_Player2.move.x -= sinf((D3DX_PI * 1.0f) + pCamera->rot.y) * MOVE_SPEED;
			g_Player2.move.z -= cosf((D3DX_PI * 1.0f) + pCamera->rot.y) * MOVE_SPEED;

			fDiffAngle = (pCamera->rot.y - (D3DX_PI * 1.0f)) - g_Player2.rot.y;
			if (fDiffAngle > D3DX_PI)
			{
				fDiffAngle -= D3DX_PI * 2.0f;
			}
			else if (fDiffAngle < -D3DX_PI)
			{
				fDiffAngle += D3DX_PI * 2.0f;
			}

			g_Player2.rot.y += fDiffAngle * 0.3f;

			if (g_Player2.rot.y > D3DX_PI)
			{
				g_Player2.rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_Player2.rot.y < -D3DX_PI)
			{
				g_Player2.rot.y += D3DX_PI * 2.0f;
			}
		}
		SetEffect(D3DXVECTOR3(g_Player2.pos.x, g_Player2.pos.y - 40, g_Player2.pos.z), 10.0f, 5);
	}
	else if (GetKeyboardPress(DIK_DOWN) == true || GetKeyboardPress(DIK_S) == true)
	{// ↓を押したら or Sを押したら
		if (GetKeyboardPress(DIK_RIGHT) == true || GetKeyboardPress(DIK_D) == true)
		{// 同時に→を押したら or Dを押したら
			g_Player2.move.x -= sinf(pCamera->rot.y - D3DX_PI * 0.25f) * MOVE_SPEED;
			g_Player2.move.z -= cosf(pCamera->rot.y - D3DX_PI * 0.25f) * MOVE_SPEED;

			fDiffAngle = (pCamera->rot.y - (D3DX_PI * 0.25f)) - g_Player2.rot.y;
			if (fDiffAngle > D3DX_PI)
			{
				fDiffAngle -= D3DX_PI * 2.0f;
			}
			else if (fDiffAngle < -D3DX_PI)
			{
				fDiffAngle += D3DX_PI * 2.0f;
			}

			g_Player2.rot.y += fDiffAngle * 0.3f;

			if (g_Player2.rot.y > D3DX_PI)
			{
				g_Player2.rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_Player2.rot.y < -D3DX_PI)
			{
				g_Player2.rot.y += D3DX_PI * 2.0f;
			}
		}
		else if (GetKeyboardPress(DIK_LEFT) == true || GetKeyboardPress(DIK_A) == true)
		{// 同時に←を押したら or Aを押したら
			g_Player2.move.x -= sinf(pCamera->rot.y + D3DX_PI * 0.25f) * MOVE_SPEED;
			g_Player2.move.z -= cosf(pCamera->rot.y + D3DX_PI * 0.25f) * MOVE_SPEED;

			fDiffAngle = (pCamera->rot.y + (D3DX_PI * 0.25f)) - g_Player2.rot.y;
			if (fDiffAngle > D3DX_PI)
			{
				fDiffAngle -= D3DX_PI * 2.0f;
			}
			else if (fDiffAngle < -D3DX_PI)
			{
				fDiffAngle += D3DX_PI * 2.0f;
			}

			g_Player2.rot.y += fDiffAngle * 0.3f;

			if (g_Player2.rot.y > D3DX_PI)
			{
				g_Player2.rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_Player2.rot.y < -D3DX_PI)
			{
				g_Player2.rot.y += D3DX_PI * 2.0f;
			}
		}
		else
		{
			g_Player2.move.x -= sinf((D3DX_PI * 0.0f) + pCamera->rot.y) * MOVE_SPEED;
			g_Player2.move.z -= cosf((D3DX_PI * 0.0f) + pCamera->rot.y) * MOVE_SPEED;

			fDiffAngle = (pCamera->rot.y - (D3DX_PI * 0.0f)) - g_Player2.rot.y;
			if (fDiffAngle > D3DX_PI)
			{
				fDiffAngle -= D3DX_PI * 2.0f;
			}
			else if (fDiffAngle < -D3DX_PI)
			{
				fDiffAngle += D3DX_PI * 2.0f;
			}

			g_Player2.rot.y += fDiffAngle * 0.3f;

			if (g_Player2.rot.y > D3DX_PI)
			{
				g_Player2.rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_Player2.rot.y < -D3DX_PI)
			{
				g_Player2.rot.y += D3DX_PI * 2.0f;
			}
		}
		SetEffect(D3DXVECTOR3(g_Player2.pos.x, g_Player2.pos.y - 40, g_Player2.pos.z), 10.0f, 5);
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true || GetKeyboardPress(DIK_D) == true)
	{// →を押したら or Dを押したら
		g_Player2.move.x += sinf((D3DX_PI * 0.5f) + pCamera->rot.y) * MOVE_SPEED;
		g_Player2.move.z += cosf((D3DX_PI * 0.5f) + pCamera->rot.y)* MOVE_SPEED;

		fDiffAngle = (pCamera->rot.y - (D3DX_PI * 0.5f)) - g_Player2.rot.y;
		if (fDiffAngle > D3DX_PI)
		{
			fDiffAngle -= D3DX_PI * 2.0f;
		}
		else if (fDiffAngle < -D3DX_PI)
		{
			fDiffAngle += D3DX_PI * 2.0f;
		}

		g_Player2.rot.y += fDiffAngle * 0.3f;

		if (g_Player2.rot.y > D3DX_PI)
		{
			g_Player2.rot.y -= D3DX_PI * 2.0f;
		}
		else if (g_Player2.rot.y < -D3DX_PI)
		{
			g_Player2.rot.y += D3DX_PI * 2.0f;
		}
		SetEffect(D3DXVECTOR3(g_Player2.pos.x, g_Player2.pos.y - 40, g_Player2.pos.z), 10.0f, 5);
	}
	else if (GetKeyboardPress(DIK_LEFT) == true || GetKeyboardPress(DIK_A) == true)
	{// ←を押したら or Aを押したら
		g_Player2.move.x += sinf((D3DX_PI * -0.5f) + pCamera->rot.y) * MOVE_SPEED;
		g_Player2.move.z += cosf((D3DX_PI * -0.5f) + pCamera->rot.y) * MOVE_SPEED;

		fDiffAngle = (pCamera->rot.y - (D3DX_PI * -0.5f)) - g_Player2.rot.y;
		if (fDiffAngle > D3DX_PI)
		{
			fDiffAngle -= D3DX_PI * 2.0f;
		}
		else if (fDiffAngle < -D3DX_PI)
		{
			fDiffAngle += D3DX_PI * 2.0f;
		}

		g_Player2.rot.y += fDiffAngle * 0.3f;

		if (g_Player2.rot.y > D3DX_PI)
		{
			g_Player2.rot.y -= D3DX_PI * 2.0f;
		}
		else if (g_Player2.rot.y < -D3DX_PI)
		{
			g_Player2.rot.y += D3DX_PI * 2.0f;
		}
		SetEffect(D3DXVECTOR3(g_Player2.pos.x, g_Player2.pos.y - 40, g_Player2.pos.z), 10.0f, 5);
	}

	//if (GetKeyboardTrigger(DIK_SPACE) == true)
	//{// 弾の発射
	//	SetBullet(D3DXVECTOR3(g_Player2.pos.x,g_Player2.pos.y + 20, g_Player2.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f) * D3DX_PI,
	//		D3DXVECTOR3(sinf(g_Player2.rot.y) * -D3DX_PI, 0.0f, cosf(g_Player2.rot.y) * -D3DX_PI));
	//}

	// メッシュウォールの取得
	MeshWall *pMeshWall;
	pMeshWall = GetMeshWall();

	// 壁との当たり判定
	if (g_Player2.pos.z > 720)
	{ 
		g_Player2.pos.z = 720;
	}
	else if (g_Player2.pos.z < -20)
	{
		g_Player2.pos.z = -20;
	}
	else if (g_Player2.pos.x > 720)
	{
		g_Player2.pos.x = 720;
	}
	else if (g_Player2.pos.x < -20)
	{
		g_Player2.pos.x = -20;
	}
	else
	{
		g_Player2.move;
	}

	// ほうき振る
	g_Player2.rot.z += 0.05f;
	if (g_Player2.rot.z > 0.5)
	{
		g_Player2.rot.z -= 1.0;
	}
	else if (g_Player2.rot.z < -0.5)
	{
		g_Player2.rot.z += 1.0;
	}

	// 慣性
	g_Player2.pos += g_Player2.move;
	g_Player2.move.x += (0.0f - g_Player2.move.x) * 0.2f;
	g_Player2.move.z += (0.0f - g_Player2.move.z) * 0.2f;

	//アイテムとの当たり判定
	if (CollisionItem2(&g_Player2.pos, &g_Player2.posOld, &g_Player2.move) == true)
	{
		g_Player2.bDisp = false;			//使用してない
	}
	else
	{
		if (g_Player2.bDisp == false)
		{
			g_Player2.bDisp = true;		//使用してる
		}
	}

	// 敵との当たり判定
	if (CollisionEnemy2(&g_Player2.pos, &g_Player2.posOld, &g_Player2.move) == true)
	{
		g_Player2.bDisp = false;			//使用してない
	}
	else
	{
		if (g_Player2.bDisp == false)
		{
			g_Player2.bDisp = true;		//使用してる
		}
	}

	// モデルとの当たり判定
	if (CollisionModel(&g_Player2.pos, &g_Player2.posOld, &g_Player2.move) == true)
	{
		g_Player2.bDisp = false;			//使用してない
	}
	else
	{
		if (g_Player2.bDisp == false)
		{
			g_Player2.bDisp = true;		//使用してる
		}
	}

	SetPositionShadow(g_Player2.nIdexShadow, D3DXVECTOR3(g_Player2.pos.x,g_Player2.pos.y -50,g_Player2.pos.z));
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ
	D3DXMATRIX mtxParent;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player2.mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player2.rot.y, g_Player2.rot.x, g_Player2.rot.z);
	D3DXMatrixMultiply(&g_Player2.mtxWorld, &g_Player2.mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player2.pos.x, g_Player2.pos.y, g_Player2.pos.z);
	D3DXMatrixMultiply(&g_Player2.mtxWorld, &g_Player2.mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player2.mtxWorld);

	// Xファイル描画
	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer2->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer2; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		pDevice->SetTexture(0, g_pTexturePlayer2);

		// モデル(パーツ)の描画
		g_pMeshPlayer2->DrawSubset(nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// プレイヤーのダメージ処理
//=============================================================================
void HitPlayer(int nDamage)
{
	g_Player2.nLife -= nDamage;

	if (g_Player2.nLife <= 0)
	{// プレイヤーのライフが0になったら
		if (g_Player2.bDisp == true)
		{
			g_Player2.bDisp = false;
			SetGameState(GAMESTATE_END);
		}
		else
		{
			g_Player2.state = PLAYERSTATE2_DAMEGE;
			g_Player2.nCounterState = 120;
		}
	}
	CutLife(1);
}

//=============================================================================
// プレイヤーの当たり判定処理
//=============================================================================
bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove)
{
	bool bHit = false;		// 当たったかどうか

	if (g_Player2.bDisp == true)
	{// プレイヤーが使われている
		if (pPos->x >= g_Player2.pos.x + g_Player2.VtxMinModel.x &&
			pPos->x <= g_Player2.pos.x + g_Player2.VtxMaxModel.x)
		{// Z面の判定
			if (pPosold->z <= g_Player2.pos.z + g_Player2.VtxMinModel.z &&
				pPos->z >= g_Player2.pos.z + g_Player2.VtxMinModel.z)
			{// 手前の判定
				pPos->z = pPosold->z;
			}
			else if (pPosold->z >= g_Player2.pos.z + (g_Player2.VtxMaxModel.z) &&
				pPos->z <= g_Player2.pos.z + (g_Player2.VtxMaxModel.z))
			{// 奥の判定
				pPos->z = pPosold->z;
			}
		}
		if (pPos->z >= g_Player2.pos.z + g_Player2.VtxMinModel.z &&
			pPos->z <= g_Player2.pos.z + g_Player2.VtxMaxModel.z)
		{// X面の判定
			if (pPosold->x >= g_Player2.pos.x + g_Player2.VtxMaxModel.x &&
				pPos->x <= g_Player2.pos.x + g_Player2.VtxMaxModel.x)
			{// 右面の判定
				pPos->x = pPosold->x;
			}
			else if (pPosold->x <= g_Player2.pos.x + (g_Player2.VtxMinModel.x) &&
				pPos->x >= g_Player2.pos.x + (g_Player2.VtxMinModel.x))
			{// 左面の判定
				pPos->x = pPosold->x;
			}
		}

	}
	return bHit;
}

//=============================================================================
// プレイヤーの取得
//=============================================================================
Player2 *GetPlayer2(void)
{
	return &g_Player2;
}
