//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "enemy.h"
#include "renderer.h"
#include "manager.h"
#include "bullet.h"
#include "explosion.h"
#include "input.h"
#include "fade.h"

#include "player.h"
#include "life.h"
#include "sound.h"
#include "game.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemy::m_apTexture[ENEMYTYPE_MAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemy::CEnemy():CScene2D(4)
{

}
//=============================================================================
// デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, ENEMYTYPE type)
{
	CScene2D::InitAnim(pos);

	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_ENEMY);

	// 位置の設置
	CScene2D::SetPosition(pos, ENEMYSIZE, ENEMYSIZE);

	// 情報の初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 3;
	m_nType = type;

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CEnemy::Update(void)
{
	//float fAngle;	// 角度

	float fDiffAngle[2] = {};		// 差分
	float fAngle[2] = {};			// 目的の角度
	float fMoveAngle = 10.0f;	// 現在の角度 

	bool bUse = false;

	// サウンドの取得
	CSound * pSound = CManager::GetSound();

	// フェードの取得
	CFade *pFade = CManager::GetFade();

	// 位置の取得
	m_pos = CScene2D::GetPosition();

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			CScene2D *pScene;

			// Sceneの取得
			pScene = (CScene2D*)CScene::GetScene(nCntPriority, nCntScene);

			if (pScene != NULL)
			{
				CScene::OBJTYPE objType;

				// オブジェクトの取得
				objType = pScene->GetObjType();

				if (objType == CScene::OBJTYPE_PLAYER)
				{// プレイヤーだったら
					D3DXVECTOR3 Playerpos;

					int nState;

					CPlayer * pPlayer = (CPlayer*)pScene;
					nState = pPlayer->GetState();

					// プレイヤーの取得
					Playerpos = pScene->GetPosition();

					if (nState == pPlayer->PLAYERSTATE_NORMAL)
					{
						if (m_pos.x >= Playerpos.x - ENEMYSIZE && m_pos.x <= Playerpos.x + ENEMYSIZE
							&& m_pos.y <= Playerpos.y + ENEMYSIZE && m_pos.y >= Playerpos.y - ENEMYSIZE)
						{// プレイヤーと敵の当たり判定

							CExplosion::Create(Playerpos);

							pPlayer->Hit(1);

							//音テスト
							pSound->PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);

							break;
						}
					}
				}
			}
		}
	}

	m_pos += m_move;

	CGame *pGame = NULL;

	CPlayer *pPlayer = NULL;

	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 move2 = GetMove();

	if (m_nType == ENEMYTYPE_TEST)
	{// チュートリアル用の敵
		m_move.y = 1 * 1.2f;

		D3DXVECTOR3 Playerpos[2];

		Playerpos[0] = pGame->GetPlayer()->GetPos();
		Playerpos[1] = pGame->GetPlayer2()->GetPos();

		fAngle[0] = atan2f(Playerpos[0].x - m_pos.x, Playerpos[0].y - m_pos.y);
		fAngle[1] = atan2f(Playerpos[1].x - m_pos.x, Playerpos[1].y - m_pos.y);

		fDiffAngle[0] = fAngle[0] - fMoveAngle;
		fDiffAngle[1] = fAngle[1] - fMoveAngle;

		if (fDiffAngle[0] > D3DX_PI)
		{
			fDiffAngle[0] -= D3DX_PI * 2.0f;
		}
		else if (fDiffAngle[0] < D3DX_PI)
		{
			fDiffAngle[0] += D3DX_PI * 2.0f;
		}

		fMoveAngle += fDiffAngle[0] * 0.2f;

		if (fDiffAngle[1] > D3DX_PI)
		{
			fDiffAngle[1] -= D3DX_PI * 2.0f;
		}
		else if (fDiffAngle[1] < D3DX_PI)
		{
			fDiffAngle[1] += D3DX_PI * 2.0f;
		}

		fMoveAngle += fDiffAngle[1] * 0.2f;

		if (fMoveAngle > D3DX_PI)
		{
			fMoveAngle -= D3DX_PI * 2.0f;
		}
		else if (fMoveAngle < D3DX_PI)
		{
			fMoveAngle += D3DX_PI * 2.0f;
		}

		move.x += sinf(fAngle[0]) * BALLET_SPEED;
		move.y += cosf(fAngle[0]) * BALLET_SPEED;

		move2.x += sinf(fAngle[1]) * BALLET_SPEED;
		move2.y += cosf(fAngle[1]) * BALLET_SPEED;

		if (rand() % 300 == 0)
		{
			if (m_pos.x >= Playerpos[0].x - 500 && m_pos.x <= Playerpos[0].x + 500
				&& m_pos.y <= Playerpos[0].y + 500 && m_pos.y >= Playerpos[0].y - 500)
			{
				CBullet::Create(m_pos, D3DXVECTOR3(move.x, move.y, 0.0f), CBullet::BULLETTYPE_ENEMY000);
			}
			if (m_pos.x >= Playerpos[1].x - 300 && m_pos.x <= Playerpos[1].x + 300
				&& m_pos.y <= Playerpos[1].y + 300 && m_pos.y >= Playerpos[1].y - 300)
			{
				CBullet::Create(m_pos, D3DXVECTOR3(move2.x, move2.y, 0.0f), CBullet::BULLETTYPE_ENEMY000);
			}
		}
	}

	if (m_pos.y >= 0)
	{
		if (rand() % 300 == 0)
		{
			// 弾のクラス生成
			CBullet::Create(m_pos, D3DXVECTOR3(0.0f, 10.0f, 0.0f), CBullet::BULLETTYPE_ENEMY000);
		}
	}

	if (m_nType == ENEMYTYPE_000)
	{// 直進移動
		m_move.y = 1 * 1.2f;
	}
	else if (m_nType == ENEMYTYPE_001)
	{// 斜め移動
		m_move.x = 1 * m_fMoveX;
		m_move.y = 1 * m_fMoveY;

		if (m_pos.x >= 930)
		{
			m_fMoveX = -1.0f;
		}
		else if (m_pos.x <= 260)
		{
			m_fMoveX = 1.0f;
		}
	}
	else if (m_nType == ENEMYTYPE_002)
	{// 横移動
		m_move.x = 1 * 2.0f;

		if (m_pos.x > 920)
		{// 右
			bUse = true;
		}
		else if (m_pos.x < 280)
		{// 左
			bUse = true;
		}
	}

	// 画面の判定縦
	if (m_pos.y > SCREEN_HEIGHT)
	{// 下
		bUse = true;
	}

	// 敵のアニメーション
	m_nCounterAnim++;

	if ((m_nCounterAnim % 30) == 0)
	{// パターンNo.更新
		m_nPatternAnim = (m_nPatternAnim + 1) % 2;

		SetPattern2(m_nPatternAnim);
	}


	// 位置の設置
	CScene2D::SetPosition(m_pos, ENEMYSIZE, ENEMYSIZE);

	if (bUse == true)
	{// 敵の破棄
		Uninit();
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// 敵の生成
//=============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, ENEMYTYPE type)
{
	CEnemy *pEnemy = NULL;

	if (pEnemy == NULL)
	{
		pEnemy = new CEnemy;

		if (pEnemy != NULL)
		{
			pEnemy->Init(pos, type);
			pEnemy->BindTexture(m_apTexture[type]);
		}
	}
	return pEnemy;
}
//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CEnemy::Load(void)
{
	CManager manager;	// インスタンス

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_000, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_001, &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_002, &m_apTexture[2]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_000, &m_apTexture[3]);

	return S_OK;
}
//=============================================================================
// テクスチャの破棄
//=============================================================================
void CEnemy::Unload(void)
{
	// テクスチャの破棄
	for (int nCntTex = 0; nCntTex < ENEMYTYPE_MAX; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}
////=============================================================================
//// 敵のダメージ処理
////=============================================================================
//void CEnemy::HitEnemy(int nDamage)
//{
//	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;
//
//	// 頂点情報を設定
//	VERTEX_2D * pVtx;					// 頂点情報へのポインタ
//
//	// 敵の位置
//	CEnemy *pEnemy = NULL;
//
//	if (pEnemy != NULL)
//	{
//		pEnemy->m_nLife -= nDamage;
//
//		if (pEnemy->m_nLife <= 0)
//		{
//			pEnemy->Uninit();
//		}
//		else
//		{
//			pVtxBuff = pEnemy->GetVtxBuff();
//
//			// 頂点バッファをロック
//			pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//
//			// 頂点バッファをアンロック
//			pVtxBuff->Unlock();
//		}
//	}
//}
