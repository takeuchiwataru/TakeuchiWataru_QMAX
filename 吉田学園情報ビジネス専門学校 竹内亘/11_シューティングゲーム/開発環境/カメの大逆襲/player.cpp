//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "effect.h"
#include "particle.h"
#include "item.h"
#include "sound.h"
#include "life.h"
#include "remain.h"
#include "fade.h"
#include "score.h"
#include "avatar.h"
#include "boss.h"

#include "game.h"
//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_apTexture[PLAYERTYPE_MAX] = {};
int CPlayer::m_nNumPlayer = 0;
//CPlayer::PLAYERSTATE CPlayer::m_State = PLAYERSTATE_NORMAL;
//CLife * CPlayer::m_pLife = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer():CScene2D(4)
{
	m_rot = 0.0f;
	m_State = PLAYERSTATE_NORMAL;
	m_ItemState = ITEMSTATE_NORMAL;
}
//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, PLAYERTYPE type)
{
	CScene2D::Init(pos); 

	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_PLAYER);

	// 位置の設置
	CScene2D::SetPosition(pos, PLAYER_SIZE, PLAYER_SIZE);

	//m_nLife = 3;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nRemain = PLAYER_REMAIN;
	m_nType = type;
	m_State = PLAYERSTATE_INVICIBLE;
	m_ItemState = ITEMSTATE_NORMAL;
	m_nCounterState = 120;
	m_nNumPs = 1;
	m_nNumPlayer = 2;

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	// 位置
	D3DXVECTOR3 pos;

	float fCol = 1.0f;

	// キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// ジョイパッドの取得
	CInputJoyPad *pInputJoyPad = CManager::GetJoyPad();

	// ジョイパッド(XInput)の取得
	CXInputJoyPad *pXInputJoyPad = CManager::GetXInputJoyPad();

	// フェードの取得
	CFade *pFade = CManager::GetFade();

	// サウンドの取得
	CSound * pSound = CManager::GetSound();

	// 位置の取得
	m_pos = CScene2D::GetPosition();

	// スコアの取得
	CScore * pScore = CGame::GetScore();

	switch (m_State)
	{
	case PLAYERSTATE_NORMAL:
		break;

	case PLAYERSTATE_DAMEGE:
		m_nCounterState--;
		if (m_nCounterState <= 0)
		{
			m_State = PLAYERSTATE_INVICIBLE;
		}
		break;

	case PLAYERSTATE_DEATH:
		break;

	case PLAYERSTATE_INVICIBLE:
		m_nTime++;
		m_nCounterState++;

		if (m_nCounterState % 10 == 0)
		{
			m_nCounterState = 0;
		}
		if (m_nCounterState < 5)
		{
			fCol = 1.0f;
		}
		else
		{
			fCol = 0.0f;
		}
		if (m_nTime % 120 == 0)
		{
			m_nTime = 0;
		}
		if (m_nTime == 100)
		{
			m_State = PLAYERSTATE_NORMAL;
		}
		break;

	case PLAYERSTATE_PS:

		m_nTime++;
		m_rot -= 0.09f;

		if (m_rot > D3DX_PI)
		{// 回転
			m_rot -= D3DX_PI * 2.0f;
		}
		else if (m_rot < -D3DX_PI)
		{
			m_rot += D3DX_PI * 2.0f;
		}

		if (m_nTime % 720 == 0)
		{// 無敵
			m_nTime = 0;
		}
		if (m_nTime == 600)
		{// 無敵終了
			m_State = PLAYERSTATE_NORMAL;
			m_rot = 0.0f;
		}

		for (int nCntParticle = 0; nCntParticle < 5; nCntParticle++)
		{// パーティクルの生成
			CParticle::Create(m_pos, D3DXVECTOR3(sinf(rand() % 628 / 100.0f) * (rand() % 7 + 1), cosf(rand() % 628 / 100.0f) * (rand() % 7 + 1), 0.0f), 20, 20);
		}
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

					if (objType == CScene::OBJTYPE_ENEMY)
					{// 敵だったら
						D3DXVECTOR3 Enemypos;

						// プレイヤーの取得
						Enemypos = pScene->GetPosition();

						if (m_pos.x >= Enemypos.x - PLAYER_SIZE && m_pos.x <= Enemypos.x + PLAYER_SIZE
							&& m_pos.y <= Enemypos.y + PLAYER_SIZE && m_pos.y >= Enemypos.y - PLAYER_SIZE)
						{// プレイヤーと敵の当たり判定

							pScore->AddScore(100);

							for (int nCntParticle = 0; nCntParticle < 30; nCntParticle++)
							{
								CParticle::Create(Enemypos, D3DXVECTOR3(sinf(rand() % 628 / 100.0f) * (rand() % 5 + 1), cosf(rand() % 628 / 100.0f) * (rand() % 5 + 1), 0.0f), 30, 30);
							}

							pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);

							pScene->Uninit();

							break;
						}
					}
					else if (objType == CScene::OBJTYPE_BOSS)
					{// ボスだったら
						D3DXVECTOR3 Bosspos;

						CBoss * pBoss = (CBoss*)pScene;

						// ボスの取得
						Bosspos = pScene->GetPosition();

						if (m_pos.x >= Bosspos.x - PLAYER_SIZE && m_pos.x <= Bosspos.x + PLAYER_SIZE
							&& m_pos.y <= Bosspos.y + PLAYER_SIZE && m_pos.y >= Bosspos.y - PLAYER_SIZE)
						{// プレイヤーと敵の当たり判定

							pBoss->HitBoss(1);

							break;
						}
					}
				}
			}
		}
		break;
	}

	 //XInput入力
	if (m_nType == PLAYERTYPE_000)
	{// プレイヤー1

		// 左スティック
		if (pXInputJoyPad->GetStick(0, 0) == true)
		{
			m_pos.x += sinf(pXInputJoyPad->GetLeftAxiz(0)) * PLAYER_MOVESPEED;
			m_pos.y -= cosf(pXInputJoyPad->GetLeftAxiz(0)) * PLAYER_MOVESPEED;

			//エフェクトの生成
			CEffect::Create(m_pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		}

		// 十字キー(XInput)
		if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_LEFT, 0) == true || pInputKeyboard->GetPress(DIK_A) == true)
		{// ←を押したら
			if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_UP, 0) == true || pInputKeyboard->GetPress(DIK_W) == true)
			{// 同時に↑を押したら	// 左上移動
				m_pos.x += sinf(D3DX_PI * -0.75f) * PLAYER_MOVESPEED;
				m_pos.y += cosf(D3DX_PI * -0.75f) * PLAYER_MOVESPEED;
			}
			else if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_DOWN, 0) == true || pInputKeyboard->GetPress(DIK_S) == true)
			{// 同時に↓を押したら	// 左下移動
				m_pos.x += sinf(D3DX_PI * -0.25f) * PLAYER_MOVESPEED;
				m_pos.y += cosf(D3DX_PI * -0.25f) * PLAYER_MOVESPEED;
			}
			else
			{// 左移動
				m_pos.x -= PLAYER_MOVESPEED;
			}
			//エフェクトの生成
			CEffect::Create(m_pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		}
		else if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_RIGHT, 0) == true || pInputKeyboard->GetPress(DIK_D) == true)
		{// →を押したら
			if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_UP, 0) == true || pInputKeyboard->GetPress(DIK_W) == true)
			{// 同時に←を押したら	// 右上移動
				m_pos.x += sinf(D3DX_PI * 0.75f) * PLAYER_MOVESPEED;
				m_pos.y += cosf(D3DX_PI * 0.75f) * PLAYER_MOVESPEED;
			}
			else if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_DOWN, 0) == true || pInputKeyboard->GetPress(DIK_S) == true)
			{// 同時に→を押したら	// 右下移動
				m_pos.x += sinf(D3DX_PI * 0.25f) * PLAYER_MOVESPEED;
				m_pos.y += cosf(D3DX_PI * 0.25f) * PLAYER_MOVESPEED;
			}
			else
			{// 右移動
				m_pos.x += PLAYER_MOVESPEED;
			}
			//エフェクトの生成
			CEffect::Create(m_pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		}
		else if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_UP, 0) == true || pInputKeyboard->GetPress(DIK_W) == true)
		{// ↑を押したら	// 上移動
			m_pos.y -= PLAYER_MOVESPEED;

			//エフェクトの生成
			CEffect::Create(m_pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		}
		else if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_DOWN, 0) == true || pInputKeyboard->GetPress(DIK_S) == true)
		{// ↓を押したら	// 下移動
			m_pos.y += PLAYER_MOVESPEED;

			//エフェクトの生成
			CEffect::Create(m_pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		}

		if (pXInputJoyPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true || pInputKeyboard->GetTrigger(DIK_SPACE) == true)
		{// 弾の発射
			switch (m_ItemState)
			{
			case ITEMSTATE_NORMAL:
				CBullet::Create(m_pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), CBullet::BULLETTYPE_PlAYER000);
				break;

			case ITEMSTATE_ITEM_2WAY:
				CBullet::Create(D3DXVECTOR3(m_pos.x - PLAYER_BULLET_INTERVAL, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, -10.0f, 0.0f), CBullet::BULLETTYPE_PlAYER000);
				CBullet::Create(D3DXVECTOR3(m_pos.x + PLAYER_BULLET_INTERVAL, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, -10.0f, 0.0f), CBullet::BULLETTYPE_PlAYER000);
				break;

			}
			pSound->PlaySound(CSound::SOUND_LABEL_SE_BABURU);
		}
		if (m_nNumPs == 1)
		{// 1回のみ
			if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_B, 0) == true || pInputKeyboard->GetPress(DIK_F) == true)
			{// パーフェクトシェル
				m_State = PLAYERSTATE_PS;
				m_nNumPs--;
				pSound->PlaySound(CSound::SOUND_LABEL_SE_PS);
			}
		}
	}
	else if (m_nType == PLAYERTYPE_001)
	{// プレイヤー2

		// 左スティック
		if (pXInputJoyPad->GetStick(0, 1) == true)
		{
			m_pos.x += sinf(pXInputJoyPad->GetLeftAxiz(1)) * PLAYER_MOVESPEED;
			m_pos.y -= cosf(pXInputJoyPad->GetLeftAxiz(1)) * PLAYER_MOVESPEED;

			//エフェクトの生成
			CEffect::Create(m_pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}

		// 十字キー
		if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_LEFT, 1) == true || pInputKeyboard->GetPress(DIK_LEFT) == true)
		{// ←を押したら
			if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_UP, 1) == true || pInputKeyboard->GetPress(DIK_UP) == true)
			{// 同時に↑を押したら	// 左上移動
				m_pos.x += sinf(D3DX_PI * -0.75f) * PLAYER_MOVESPEED;
				m_pos.y += cosf(D3DX_PI * -0.75f) * PLAYER_MOVESPEED;
			}
			else if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_DOWN, 1) == true || pInputKeyboard->GetPress(DIK_DOWN) == true)
			{// 同時に↓を押したら	// 左下移動
				m_pos.x += sinf(D3DX_PI * -0.25f) * PLAYER_MOVESPEED;
				m_pos.y += cosf(D3DX_PI * -0.25f) * PLAYER_MOVESPEED;
			}
			else
			{// 左移動
				m_pos.x -= PLAYER_MOVESPEED;
			}
			//エフェクトの生成
			CEffect::Create(m_pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
		else if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_RIGHT, 1) == true || pInputKeyboard->GetPress(DIK_RIGHT) == true)
		{// →を押したら
			if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_UP, 1) == true || pInputKeyboard->GetPress(DIK_UP) == true)
			{// 同時に←を押したら	// 右上移動
				m_pos.x += sinf(D3DX_PI * 0.75f) * PLAYER_MOVESPEED;
				m_pos.y += cosf(D3DX_PI * 0.75f) * PLAYER_MOVESPEED;
			}
			else if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_DOWN, 1) == true || pInputKeyboard->GetPress(DIK_DOWN) == true)
			{// 同時に→を押したら	// 右下移動
				m_pos.x += sinf(D3DX_PI * 0.25f) * PLAYER_MOVESPEED;
				m_pos.y += cosf(D3DX_PI * 0.25f) * PLAYER_MOVESPEED;
			}
			else
			{// 右移動
				m_pos.x += PLAYER_MOVESPEED;
			}
			//エフェクトの生成
			CEffect::Create(m_pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
		else if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_UP, 1) == true || pInputKeyboard->GetPress(DIK_UP) == true)
		{// ↑を押したら	// 上移動
			m_pos.y -= PLAYER_MOVESPEED;

			//エフェクトの生成
			CEffect::Create(m_pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
		else if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_DPAD_DOWN, 1) == true || pInputKeyboard->GetPress(DIK_DOWN) == true)
		{// ↓を押したら	// 下移動
			m_pos.y += PLAYER_MOVESPEED;

			//エフェクトの生成
			CEffect::Create(m_pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}

		if (pXInputJoyPad->GetTrigger(XINPUT_GAMEPAD_A, 1) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{// 弾の発射
			switch (m_ItemState)
			{
			case ITEMSTATE_NORMAL:
				CBullet::Create(m_pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), CBullet::BULLETTYPE_PlAYER000);
				break;

			case ITEMSTATE_ITEM_2WAY:
				CBullet::Create(D3DXVECTOR3(m_pos.x - PLAYER_BULLET_INTERVAL, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, -10.0f, 0.0f), CBullet::BULLETTYPE_PlAYER000);
				CBullet::Create(D3DXVECTOR3(m_pos.x + PLAYER_BULLET_INTERVAL, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, -10.0f, 0.0f), CBullet::BULLETTYPE_PlAYER000);
				break;
			}
			pSound->PlaySound(CSound::SOUND_LABEL_SE_BABURU);
		}
		if (m_nNumPs == 1)
		{// 1回のみ
			if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_B, 1) == true || pInputKeyboard->GetPress(DIK_M) == true)
			{// パーフェクトシェル
				m_State = PLAYERSTATE_PS;
				m_nNumPs--;
				pSound->PlaySound(CSound::SOUND_LABEL_SE_PS);
			}
		}
	}

	SetColor(D3DXCOLOR(1.0f,1.0f,1.0f, fCol));

	// 画面の判定横
	if (m_pos.x > 920)
	{// 右
		m_pos.x = 920;
	}
	else if (m_pos.x < 280)
	{// 左
		m_pos.x = 280;
	}

	// 画面の判定縦
	if (m_pos.y > SCREEN_HEIGHT)
	{// 上
		m_pos.y = SCREEN_HEIGHT;
	}
	else if (m_pos.y < 0)
	{// 上
		m_pos.y = 0;
	}

	// 位置の設置
	CScene2D::SetPosition(m_pos, PLAYER_SIZE, PLAYER_SIZE);

	// 頂点バッファの取得
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = CScene2D::GetVtxBuff();

	// 頂点情報を設定
	VERTEX_2D * pVtx;					// 頂点情報へのポインタ

	// 頂点バッファをロック
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.75f - m_rot) * PLAYER_SIZE, m_pos.y + cosf(-D3DX_PI * 0.75f - m_rot) * PLAYER_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.75f - m_rot) * PLAYER_SIZE, m_pos.y + cosf(D3DX_PI * 0.75f - m_rot) * PLAYER_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.25f - m_rot) * PLAYER_SIZE, m_pos.y + cosf(-D3DX_PI * 0.25f - m_rot) * PLAYER_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.25f - m_rot) * PLAYER_SIZE, m_pos.y + cosf(D3DX_PI * 0.25f - m_rot) * PLAYER_SIZE, 0.0f);

	// 頂点バッファをアンロック
	pVtxBuff->Unlock();
}
//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	CManager manager;	//インスタンス

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// 頂点バッファの取得
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;
	pVtxBuff = CScene2D::GetVtxBuff();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_apTexture[m_nType]);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//=============================================================================
// ダメージ処理
//=============================================================================
void CPlayer::Hit(int nDamage)
{
	bool bDeath = false;	// 死んだかどうか

	// 保存
	int nNumPlayer = m_nNumPlayer;

	// 1P残機の取得
	CRemain * pRemain = CGame::GetRemain();

	// 2P残機の取得
	CRemain * pRemain2 = CGame::GetRemain2();

	// フェードの取得
	CFade *pFade = CManager::GetFade();

	// スコアの取得
	CScore * pScore = CGame::GetScore();

	m_nRemain -= nDamage;

	if (m_nType == PLAYERTYPE_000)
	{// プレイヤー1
		if (m_nRemain == 0)
		{// 残機0
			pRemain->AddRemain(-1);

			m_nNumPlayer--;

			bDeath = true;
		}
		else if (m_nRemain >= 1)
		{// 残機1以上
			m_State = PLAYERSTATE_INVICIBLE;
			m_ItemState = ITEMSTATE_NORMAL;
			pRemain->AddRemain(-1);

			m_nCounterState = 120;
		}
	}
	else if (m_nType == PLAYERTYPE_001)
	{// プレイヤー2
		if (m_nRemain == 0)
		{// 残機0
			pRemain2->AddRemain(-1);

			m_nNumPlayer--;

			bDeath = true;
		}
		else if (m_nRemain >= 1)
		{// 残機1以上
			m_State = PLAYERSTATE_INVICIBLE;
			m_ItemState = ITEMSTATE_NORMAL;

			pRemain2->AddRemain(-1);

			m_nCounterState = 120;
		}
	}

	if (m_nNumPlayer == 0)
	{// プレイヤーの数が0になったら

		//スコアの保存
		CManager::GetRankingScore(pScore->GetScore());

		pFade->Set(CManager::MODE_RESULT, pFade->FADE_OUT);
	}

	if (bDeath == true)
	{// プレイヤーが死んだら
		Uninit();
	}
}
//=============================================================================
// 状態の取得
//=============================================================================
CPlayer::PLAYERSTATE CPlayer::GetState(void)
{
	return m_State;
}
//=============================================================================
// 種類の取得
//=============================================================================
CPlayer::PLAYERTYPE CPlayer::GetType(void)
{
	return m_nType;
}

//=============================================================================
// 状態の設置
//=============================================================================
void CPlayer::SetItemState(ITEMSTATE itemstate)
{
	m_ItemState = itemstate;
}
//=============================================================================
// 残機の取得
//=============================================================================
int CPlayer::GetRemain(void)
{
	return m_nRemain;
}
//=============================================================================
// プレイヤーの取得
//=============================================================================
D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}
////=============================================================================
//// プレイヤーのタイプ取得
////=============================================================================
//CPlayer::PLAYERTYPE CPlayer::GetPlayerType(void)
//{
//	return m_nType;
//}
//=============================================================================
// プレイヤーの生成
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, PLAYERTYPE type)
{
	CPlayer *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;

		if (pPlayer != NULL)
		{
			pPlayer->Init(pos,type);
			pPlayer->BindTexture(m_apTexture[type]);
		}
	}
	return pPlayer;
}
//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CPlayer::Load(void)
{
	CManager manager;	// インスタンス

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTURE_000, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTURE_001, &m_apTexture[1]);

	return S_OK;
}
//=============================================================================
// テクスチャの破棄
//=============================================================================
void CPlayer::Unload(void)
{
	// テクスチャの破棄
	for (int nCntTex = 0; nCntTex < PLAYERTYPE_MAX; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}
