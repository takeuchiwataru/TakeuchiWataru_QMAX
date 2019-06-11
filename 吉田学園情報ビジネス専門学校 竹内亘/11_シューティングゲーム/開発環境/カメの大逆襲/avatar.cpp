//=============================================================================
//
// アバター処理 [avatar.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "avatar.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "effect.h"
#include "item.h"
#include "sound.h"
#include "life.h"
#include "remain.h"
#include "fade.h"
#include "player.h"

#include "game.h"
//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CAvatar::m_apTexture[AVATARTYPE_MAX] = {};
//CAvatar::PLAYERSTATE CAvatar::m_State = PLAYERSTATE_NORMAL;
//CLife * CAvatar::m_pLife = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CAvatar::CAvatar() :CScene2D(2)
{

}
//=============================================================================
// デストラクタ
//=============================================================================
CAvatar::~CAvatar()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CAvatar::Init(D3DXVECTOR3 pos, AVATARTYPE type)
{
	CScene2D::Init(pos);

	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_AVATAR);

	// 位置の設置
	CScene2D::SetPosition(pos, AVATAR_SIZE, AVATAR_SIZE);

	m_nType = type;
	m_nSpeed = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);

	////m_nLife = 3;
	//m_nRemain = PLAYER_REMAIN;
	//m_State = PLAYERSTATE_INVICIBLE;
	//m_ItemState = ITEMSTATE_NORMAL;
	//m_nCounterState = 120;

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CAvatar::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CAvatar::Update(void)
{
	float fDiffAngle = 0;		// 差分
	float fAngle = 0;			// 目的の角度
	float fMoveAngle = 10.0f;	// 現在の角度 

	float fDiffAngle2 = 0;		// 差分
	float fAngle2 = 0;			// 目的の角度
	float fMoveAngle2 = 10.0f;	// 現在の角度 

	D3DXVECTOR3 move = CScene2D::GetMove();

	// キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// ジョイパッドの取得
	CInputJoyPad *pInputJoyPad = CManager::GetJoyPad();

	CGame * pGame = NULL;

	// 位置の取得
	m_pos = CScene2D::GetPosition();

	//for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	//{
	//	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	//	{
	//		CScene2D *pScene;

	//		// Sceneの取得
	//		pScene = (CScene2D*)CScene::GetScene(nCntPriority, nCntScene);

	//		if (pScene != NULL)
	//		{
	//			CScene::OBJTYPE objType;

	//			// オブジェクトの取得
	//			objType = pScene->GetObjType();

	//			if (objType == CScene::OBJTYPE_PLAYER)
	//			{// プレイヤーだったら
	//				CPlayer::PLAYERTYPE nType;

	//				CPlayer * pPlayer = (CPlayer*)pScene;
	//				nType = pPlayer->GetType();

	//				if (nType == pPlayer->PLAYERTYPE_000)
	//				{// プレイヤー1
	//					D3DXVECTOR3 Playerpos;

	//					// プレイヤーの取得
	//					Playerpos = pGame->GetPlayer()->GetPos();

	//					fAngle = atan2f(Playerpos.x - m_pos.x, Playerpos.y - m_pos.y);

	//					fDiffAngle = fAngle - fMoveAngle;

	//					if (fDiffAngle > D3DX_PI)
	//					{
	//						fDiffAngle -= D3DX_PI * 2.0f;
	//					}
	//					else if (fDiffAngle < D3DX_PI)
	//					{
	//						fDiffAngle += D3DX_PI * 2.0f;
	//					}

	//					fMoveAngle += fDiffAngle * 0.2f;

	//					if (fMoveAngle > D3DX_PI)
	//					{
	//						fMoveAngle -= D3DX_PI * 2.0f;
	//					}
	//					else if (fMoveAngle < D3DX_PI)
	//					{
	//						fMoveAngle += D3DX_PI * 2.0f;
	//					}
	//					move.x += sinf(fAngle) * 3;
	//					move.y += cosf(fAngle) * 3;
	//				}
	//				else if (nType == pPlayer->PLAYERTYPE_001)
	//				{// プレイヤー2
	//					D3DXVECTOR3 Playerpos2;

	//					// プレイヤーの取得
	//					Playerpos2 = pGame->GetPlayer2()->GetPos();

	//					fAngle = atan2f(Playerpos2.x - m_pos.x, Playerpos2.y - m_pos.y);

	//					fDiffAngle = fAngle - fMoveAngle;

	//					if (fDiffAngle > D3DX_PI)
	//					{
	//						fDiffAngle -= D3DX_PI * 2.0f;
	//					}
	//					else if (fDiffAngle < D3DX_PI)
	//					{
	//						fDiffAngle += D3DX_PI * 2.0f;
	//					}

	//					fMoveAngle += fDiffAngle * 0.2f;

	//					if (fMoveAngle > D3DX_PI)
	//					{
	//						fMoveAngle -= D3DX_PI * 2.0f;
	//					}
	//					else if (fMoveAngle < D3DX_PI)
	//					{
	//						fMoveAngle += D3DX_PI * 2.0f;
	//					}
	//					move.x += sinf(fAngle) * 3;
	//					move.y += cosf(fAngle) * 3;
	//				}
	//			}
	//		}
	//	}
	//}

	D3DXVECTOR3 Playerpos;
	D3DXVECTOR3 Playerpos2;

	Playerpos = pGame->GetPlayer()->GetPos();
	Playerpos2 = pGame->GetPlayer2()->GetPos();

	fAngle = atan2f(Playerpos.x - m_pos.x, Playerpos.y - m_pos.y);
	fAngle = atan2f(Playerpos2.x - m_pos.x, Playerpos2.y - m_pos.y);

	fDiffAngle = fAngle - fMoveAngle;

	if (fDiffAngle > D3DX_PI)
	{
		fDiffAngle -= D3DX_PI * 2.0f;
	}
	else if (fDiffAngle < D3DX_PI)
	{
		fDiffAngle += D3DX_PI * 2.0f;
	}

	fMoveAngle += fDiffAngle * 0.2f;

	if (fMoveAngle > D3DX_PI)
	{
		fMoveAngle -= D3DX_PI * 2.0f;
	}
	else if (fMoveAngle < D3DX_PI)
	{
		fMoveAngle += D3DX_PI * 2.0f;
	}
	move.x += sinf(fAngle) * 3;
	move.y += cosf(fAngle) * 3;


	fAngle2 = atan2f(Playerpos2.x - m_pos.x, Playerpos2.y - m_pos.y);
	fDiffAngle2 = fAngle2 - fMoveAngle2;

	if (fDiffAngle2 > D3DX_PI)
	{
		fDiffAngle2 -= D3DX_PI * 2.0f;
	}
	else if (fDiffAngle2 < D3DX_PI)
	{
		fDiffAngle2 += D3DX_PI * 2.0f;
	}

	fMoveAngle2 += fDiffAngle2 * 0.2f;

	if (fMoveAngle2 > D3DX_PI)
	{
		fMoveAngle2 -= D3DX_PI * 2.0f;
	}
	else if (fMoveAngle2 < D3DX_PI)
	{
		fMoveAngle2 += D3DX_PI * 2.0f;
	}

	move.x += sinf(fAngle2) * 3;
	move.y += cosf(fAngle2) * 3;

	m_pos += move;

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
	CScene2D::SetPosition(m_pos, AVATAR_SIZE, AVATAR_SIZE);
}
//=============================================================================
// 描画処理
//=============================================================================
void CAvatar::Draw(void)
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
////=============================================================================
//// ダメージ処理
////=============================================================================
//void CAvatar::Hit(int nDamage)
//{
//	bool bDeath = false;	// 死んだかどうか
//
//							// 1P残機の取得
//	CRemain * pRemain = CGame::GetRemain();
//
//	// 2P残機の取得
//	CRemain * pRemain2 = CGame::GetRemain2();
//
//	// フェードの取得
//	CFade *pFade = CManager::GetFade();
//
//	m_nRemain -= nDamage;
//
//	if (m_nType == PLAYERTYPE_000)
//	{// プレイヤー1
//		if (m_nRemain == 0)
//		{// 残機0
//			pRemain->AddRemain(-1);
//
//			bDeath = true;
//		}
//		else if (m_nRemain >= 1)
//		{// 残機1以上
//			m_State = PLAYERSTATE_INVICIBLE;
//			m_ItemState = ITEMSTATE_NORMAL;
//			pRemain->AddRemain(-1);
//
//			m_nCounterState = 120;
//		}
//	}
//	else if (m_nType == PLAYERTYPE_001)
//	{// プレイヤー2
//		if (m_nRemain == 0)
//		{// 残機0
//			pRemain2->AddRemain(-1);
//
//			bDeath = true;
//		}
//		else if (m_nRemain >= 1)
//		{// 残機1以上
//			m_State = PLAYERSTATE_INVICIBLE;
//			m_ItemState = ITEMSTATE_NORMAL;
//
//			pRemain2->AddRemain(-1);
//
//			m_nCounterState = 120;
//		}
//	}
//
//	if (m_nType == PLAYERTYPE_000 && m_nType == PLAYERTYPE_001)
//	{
//		if (bDeath == true)
//		{
//			pFade->Set(CManager::MODE_RESULT, pFade->FADE_OUT);
//		}
//	}
//
//	if (bDeath == true)
//	{// プレイヤーが死んだら
//		Uninit();
//	}
//}
////=============================================================================
//// 状態の取得
////=============================================================================
//CAvatar::PLAYERSTATE CAvatar::GetState(void)
//{
//	return m_State;
//}
////=============================================================================
//// 状態の設置
////=============================================================================
//void CAvatar::SetItemState(ITEMSTATE itemstate)
//{
//	m_ItemState = itemstate;
//}
////=============================================================================
//// 残機の取得
////=============================================================================
//int CAvatar::GetRemain(void)
//{
//	return m_nRemain;
//}
////=============================================================================
//// プレイヤーのタイプ取得
////=============================================================================
//CAvatar::AVATARTYPE CAvatar::GetPlayerType(void)
//{
//	return m_nType;
//}
//=============================================================================
// プレイヤーの生成
//=============================================================================
CAvatar * CAvatar::Create(D3DXVECTOR3 pos, AVATARTYPE type)
{
	CAvatar *pAvater = NULL;

	if (pAvater == NULL)
	{
		pAvater = new CAvatar;

		if (pAvater != NULL)
		{
			pAvater->Init(pos, type);
			pAvater->BindTexture(m_apTexture[type]);
		}
	}
	return pAvater;
}
//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CAvatar::Load(void)
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
void CAvatar::Unload(void)
{
	// テクスチャの破棄
	for (int nCntTex = 0; nCntTex < AVATARTYPE_MAX; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}
