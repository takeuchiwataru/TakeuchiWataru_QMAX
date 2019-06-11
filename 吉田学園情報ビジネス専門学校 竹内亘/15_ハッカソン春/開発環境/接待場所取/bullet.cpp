//=============================================================================
//
// 弾処理 [bullet.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "camera.h"
#include "scene3D.h"
#include "meshField.h"
#include "player.h"
#include "game.h"
#include "enemy.h"
#include "effect3D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULLET_NAME	"data\\MODEL\\sakebottle.x"	// ブロックのモデル名
#define BLOCKSIZE	(15.0f)					// ブロックのサイズ

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPD3DXMESH CBullet::m_pMesh = NULL;		// メッシュ情報（頂点情報）へのポインタ
LPD3DXBUFFER CBullet::m_pBuffMat = NULL;	// マテリアル情報へのポインタ
DWORD CBullet::m_nNumMat = 0;			// マテリアル情報の数
LPDIRECT3DTEXTURE9 *CBullet::m_pTexture = 0;			// テクスチャ情報

//=============================================================================
// プレイヤークラスのコンストラクタ
//=============================================================================
CBullet::CBullet()
{
	// 値をクリア
	m_pVtxBuff = NULL;						// 頂点バッファへのポインタ
	D3DXMatrixIdentity(&m_mtxWorld);		// ワールドマトリックス
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_bHit = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	CBullet *pBullet = NULL;

	if (pBullet == NULL)
	{
		// オブジェクトクラスの生成
		pBullet = new CBullet;

		if (pBullet != NULL)
		{
			pBullet->SetPosition(pos);
			pBullet->m_pos = pos;
			pBullet->m_move = move;
			pBullet->m_nLife = nLife;
			pBullet->BindModel(m_pBuffMat, m_nNumMat, m_pMesh);
			pBullet->BindMat(m_pTexture);
			pBullet->Init();
		}
	}

	return pBullet;
}

//=============================================================================
// ブロック初期化処理
//=============================================================================
HRESULT CBullet::Init(void)
{
	// 初期化処理
	CSceneX::Init();

	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_BULLET);

	// 拡大率の設定
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_bHit = false;

	return S_OK;
}

//=============================================================================
// ブロック終了処理
//=============================================================================
void CBullet::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// ブロック更新処理
//=============================================================================
void CBullet::Update(void)
{
	CollisonBlock(&m_pos, 45.0f);

	// 弾を動かす
	m_pos += m_move;

	m_rot.x += 0.2f;

	CSceneX::SetPosition(m_pos);
	CSceneX::SetRot(m_rot);

	// 弾のライフを減らす
	m_nLife--;

	if (m_nLife <= 0)
	{//	弾削除
		m_bHit = true;
	}

	if (m_bHit == true)
	{
		Uninit();
	}
}

//=============================================================================
// ブロック描画処理
//=============================================================================
void CBullet::Draw(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}


	// 頂点法線の自動正規化	開始
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	CSceneX::Draw();

	// 頂点法線の自動正規化	終了
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

}

//=============================================================================
// ブロックとの当たり判定処理
//=============================================================================
bool CBullet::Collision(D3DXVECTOR3 *pos, float fRadius)
{
	bool bHit = false;	// 当たっていない状態

						// 中心と中心の差を求める
	D3DXVECTOR3 DiffLength = D3DXVECTOR3(pos->x - m_pos.x, pos->y - m_pos.y, pos->z - m_pos.z);

	// 中心から中心のベクトルの長さを算出
	float distance = sqrtf((DiffLength.x * DiffLength.x) + (DiffLength.y * DiffLength.y) + (DiffLength.z * DiffLength.z));

	if (distance < fRadius + m_VtxMax.x && distance < fRadius + m_VtxMax.y && distance < fRadius + m_VtxMax.z)
	{// 長さが半径の和より小さければ当たっている
		bHit = true;
	}

	return bHit;	// ブロックに当たっているかどうかを返す
}

//=============================================================================
// ブロックの破壊の判定
//=============================================================================
void CBullet::CollisonBlock(D3DXVECTOR3 *pos, float fRadius)
{
	// モードの取得
	CManager::MODE mode;
	mode = CManager::GetMode();
	//エフェクト用関数
	D3DXVECTOR3 RotRand;
	D3DXVECTOR3 PosRand;
	D3DXVECTOR3 effectmove;
	//アイテムの数をセット
	CUIEnemy *m_pUIEnemy = CGame::GetUIEnemy ();
	//サウンド情報を取得
	CSound *pSound = CManager::GetSound(0);
	//サウンド情報を取得
	CSound *pSound2 = CManager::GetSound(1);

	CScene *pScene = NULL;

	// 先頭のオブジェクトを取得
	pScene = CScene::GetTop(6);

	while (pScene != NULL)
	{// 優先順位が3のオブジェクトを1つ1つ確かめる
	 // 処理の最中に消える可能性があるから先に記録しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// 死亡フラグが立っていないもの
			if (pScene->GetObjType() == CScene::OBJTYPE_ENEMY)
			{// オブジェクトの種類を確かめる
				if (((CEnemy*)pScene)->Collision(pos, fRadius) == true)
				{
					if (((CEnemy*)pScene)->GetMotionState() != CEnemy::MOTIONSTATE_DAMAGE)
					{
						pSound->PlaySound(pSound->SOUND_LABEL_SE_DAMAGE);
						pSound2->PlaySound(pSound->SOUND_LABEL_SE_BREAK);
						m_pUIEnemy->PlusEnemy(1);
						((CEnemy*)pScene)->SetMotionState(CEnemy::MOTIONSTATE_DAMAGE);
						// エネミー削除
						//((CEnemy*)pScene)->Uninit();

						for (int nCnt = 0; nCnt < 10; nCnt++)
						{
							//ランダムな値
							RotRand.x = (float)(rand() % 20 - 10);
							PosRand.y = (float)(rand() % 20);
							PosRand.x = (float)(rand() % 50 - 25);
							//移動量の設定
							effectmove.x = (float)(rand() % 20 - 10);
							effectmove.y = (float)(rand() % 20 - 10);
							effectmove.z = (float)(rand() % 20 - 10);
							//エフェクトを生成
							C3DEffect::Create(D3DXVECTOR3(m_pos.x + PosRand.x, m_pos.y + PosRand.y, m_pos.z + 50), effectmove,
								D3DXVECTOR3(sinf(RotRand.x), sinf(RotRand.x), sinf(RotRand.x)), C3DEffect::EFFECTTYPE_BIN000, 30);
						}

						m_bHit = true;
					}
				}
			}
		}

		// 次のシーンに進める
		pScene = pSceneNext;
	}
}

//=============================================================================
// ブロックのモデル読み込み処理
//=============================================================================
HRESULT CBullet::LoadModel(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// Xファイルの読み込み
	D3DXLoadMeshFromX(BULLET_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	return S_OK;
}

//=============================================================================
// ブロックのモデル解放処理
//=============================================================================
void CBullet::UnloadModel(void)
{
	// メッシュの開放
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// マテリアルの開放
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//=============================================================================
// 位置の取得
//=============================================================================
D3DXVECTOR3 CBullet::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// 位置の設定
//=============================================================================
void CBullet::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}