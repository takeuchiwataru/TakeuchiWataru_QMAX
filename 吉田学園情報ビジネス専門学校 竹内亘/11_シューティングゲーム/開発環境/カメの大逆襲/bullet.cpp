//=============================================================================
//
// 弾の処理 [bullet.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "bullet.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "explosion.h"
#include "enemy.h"
#include "boss.h"
#include "score.h"
#include "effect.h"
#include "item.h"
#include "player.h"
#include "life.h"
#include "particle.h"

#include "game.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;
//CScore * CBullet::m_pScore = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CBullet::CBullet():CScene2D(3)
{
	m_bulletType = BULLETTYPE_NONE;
}
//=============================================================================
// デストラクタ
//=============================================================================
CBullet::~CBullet()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE BulletType)
{
	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_BULLET);

	CScene2D::Init(pos);

	// 位置の設置
	CScene2D::SetPosition(pos, BULLET_SIZE, BULLET_SIZE);

	// 情報の初期化
	m_move = move;
	m_nLife = BULLET_LIFE;
	m_bulletType = BulletType;

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CBullet::Uninit(void)
{
	//m_pScore = NULL;

	CScene2D::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CBullet::Update(void)
 {
	bool bUse = false;

	// 位置
	D3DXVECTOR3 pos;

	D3DXCOLOR col;

	// 位置の取得
	pos = CScene2D::GetPosition();

	// サウンドの取得
	CSound * pSound = CManager::GetSound();

	// スコアの取得
	CScore * pScore = CGame::GetScore();

	//// プレイヤーの取得
	//CPlayer * pPlayer = CGame::GetPlayer();

	//// ライフの取得
	//CLife *pLife = CGame::GetLife();

	pos += m_move;

	// 位置の設置
	CScene2D::SetPosition(pos, BULLET_SIZE, BULLET_SIZE);

	m_nLife--;
	if (m_nLife <= 0 || pos.y < 0)
	{
		CExplosion::Create(pos);

		bUse = true;
	}

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			CScene2D *pScene;

			// Sceneの取得
			pScene = (CScene2D*)CScene::GetScene(nCntPriority,nCntScene);

			if (pScene != NULL)
			{
				CScene::OBJTYPE objType;

				// オブジェクトの取得
				objType = pScene->GetObjType();

				if (m_bulletType == BULLETTYPE_PlAYER000 && objType == CScene::OBJTYPE_ENEMY)
				{// プレイヤーの弾だったら
					D3DXVECTOR3 Enemypos;

					// 敵の取得
					Enemypos = pScene->GetPosition();

					if (pos.x >= Enemypos.x - HIT_SIZE && pos.x <= Enemypos.x + HIT_SIZE
						&& pos.y <= Enemypos.y + HIT_SIZE && pos.y >= Enemypos.y - HIT_SIZE)
					{// 敵とプレイヤーの弾の当たり判定
						pScore->AddScore(100);

						//CExplosion::Create(Enemypos);
						for (int nCntParticle = 0; nCntParticle < 30; nCntParticle++)
						{
							CParticle::Create(Enemypos, D3DXVECTOR3(sinf(rand() % 628 / 100.0f) * (rand() % 5 + 1) , cosf(rand() % 628 / 100.0f) * (rand() % 5+ 1), 0.0f), 30, 30);
						}

						pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);

						pScene->Uninit();

						bUse = true;

						break;
					}
				}
				else if (m_bulletType == BULLETTYPE_PlAYER000 && objType == CScene::OBJTYPE_BOSS)
				{// プレイヤーの弾だったら
					D3DXVECTOR3 Bosspos;

					CBoss * pBoss = (CBoss*)pScene;

					// ボスの取得
					Bosspos = pScene->GetPosition();

					if (pos.x >= Bosspos.x - 100 && pos.x <= Bosspos.x + 100
						&& pos.y <= Bosspos.y + 100 && pos.y >= Bosspos.y - 100)
					{// ボスとプレイヤーの弾の当たり判定

						pBoss->HitBoss(1);

						bUse = true;

						break;
					}
				}

				else if (m_bulletType == BULLETTYPE_PlAYER000 && objType == CScene::OBJTYPE_MAEINAPLANT)
				{// プレイヤーの弾
					D3DXVECTOR3 Marinepos;

					// 海藻の取得
					Marinepos = pScene->GetPosition();

					if (pos.x >= Marinepos.x - HIT_SIZE && pos.x <= Marinepos.x + HIT_SIZE
						&& pos.y <= Marinepos.y + HIT_SIZE && pos.y >= Marinepos.y - HIT_SIZE)
					{// 海藻とプレイヤーの弾の当たり判定

						CExplosion::Create(Marinepos);

						pScene->Uninit();

						if (rand() % 3 == 0)
						{// スコア
							CItem::Create(Marinepos, CItem::ITEMTYPE_000);
						}
						else if (rand() % 5 == 0)
						{// 2way
							CItem::Create(Marinepos, CItem::ITEMTYPE_001);
						}
						else if (rand() % 10 == 0)
						{// 2way
							CItem::Create(Marinepos, CItem::ITEMTYPE_001);
						}

						bUse = true;

						break;
					}
				}

				else if (m_bulletType == BULLETTYPE_ENEMY000 && objType == CScene::OBJTYPE_PLAYER)
				{// 敵の弾だったら

					 // 移動量の更新
					D3DXVECTOR3 PlayerPos;

					int nState;

					CPlayer * pPlayer = (CPlayer*)pScene;
					nState = pPlayer->GetState();

					// プレイヤーの取得
					PlayerPos = pScene->GetPosition();

					if (nState == pPlayer->PLAYERSTATE_NORMAL)
					{
						if (pos.x >= PlayerPos.x - HIT_SIZE && pos.x <= PlayerPos.x + HIT_SIZE
							&& pos.y <= PlayerPos.y + HIT_SIZE && pos.y >= PlayerPos.y - HIT_SIZE)
						{// プレイヤーと敵の弾の当たり判定

							pPlayer->Hit(1);

							pSound->PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);

							CExplosion::Create(PlayerPos);

							//	pScene->Uninit();

							bUse = true;

							break;
						}
					}
				}

				else if (m_bulletType == BULLETTYPE_ENEMY000 && objType == CScene::OBJTYPE_PLAYER)
				{// 敵の弾だったら

					// 移動量の更新
					D3DXVECTOR3 PlayerPos;

					int nState;

					CPlayer * pPlayer = (CPlayer*)pScene;
					nState = pPlayer->GetState();

					// プレイヤーの取得
					PlayerPos = pScene->GetPosition();

					if (nState == pPlayer->PLAYERSTATE_NORMAL)
					{
						if (pos.x >= PlayerPos.x - HIT_SIZE && pos.x <= PlayerPos.x + HIT_SIZE
							&& pos.y <= PlayerPos.y + HIT_SIZE && pos.y >= PlayerPos.y - HIT_SIZE)
						{// プレイヤーと敵の弾の当たり判定

							pPlayer->Hit(1);

							//音テスト
							pSound->PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);

							CExplosion::Create(PlayerPos);

							//	pScene->Uninit();

							bUse = true;

							break;
						}
					}
				}

				else if (m_bulletType == BULLETTYPE_ENEMY000 && objType == CScene::OBJTYPE_PLAYER)
				{// ボスの弾だったら

					// 移動量の更新
					D3DXVECTOR3 PlayerPos;

					int nState;

					CPlayer * pPlayer = (CPlayer*)pScene;
					nState = pPlayer->GetState();

					// プレイヤーの取得
					PlayerPos = pScene->GetPosition();

					if (nState == pPlayer->PLAYERSTATE_NORMAL)
					{
						if (pos.x >= PlayerPos.x - HIT_SIZE && pos.x <= PlayerPos.x + HIT_SIZE
							&& pos.y <= PlayerPos.y + HIT_SIZE && pos.y >= PlayerPos.y - HIT_SIZE)
						{// プレイヤーと敵の弾の当たり判定

							pPlayer->Hit(1);

							//音テスト
							pSound->PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);

							CExplosion::Create(PlayerPos);

							//	pScene->Uninit();

							bUse = true;

							break;
						}
					}
				}

			}
		}
	}

	// エフェクトの生成
	CEffect::Create(pos, D3DXCOLOR(0.0f, 0.6f, 0.5f, 1.0f));

	if (bUse == true)
	{// 弾の破棄
		Uninit();
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// 弾の生成
//=============================================================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE BulletType)
{
	CBullet *pBullet = NULL;

	if (pBullet == NULL)
	{
		pBullet = new CBullet;

		if (pBullet != NULL)
		{
			pBullet->Init(pos,move,BulletType);
			pBullet->BindTexture(m_pTexture);
		}
	}
	return pBullet;
}
//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CBullet::Load(void)
{
	CManager manager;	// インスタンス

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, BULEET_TEXTURE_000, &m_pTexture);

	return S_OK;
}
//=============================================================================
// テクスチャの破棄
//=============================================================================
void CBullet::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}