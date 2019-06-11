//=============================================================================
//
// アイテム処理 [item.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "item.h"
#include "renderer.h"
#include "manager.h"
#include "bullet.h"
#include "score.h"
#include "input.h"
#include "player.h"
#include "avatar.h"
#include "game.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CItem::m_apTexture[ITEMTYPE_MAX] = {};
//CScore * CItem::m_pScore = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CItem::CItem() :CScene2D(3)
{

}
//=============================================================================
// デストラクタ
//=============================================================================
CItem::~CItem()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, ITEMTYPE type)
{
	CScene2D::Init(pos);

	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_ITEM);

	// 位置の設置
	CScene2D::SetPosition(pos, ITEMSIZE, ITEMSIZE);

	// 情報の初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 3;
	m_nType = type;
	m_nTime = 0;

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CItem::Uninit(void)
{
	//m_pScore = NULL;

	CScene2D::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CItem::Update(void)
{
	bool bUse = false;

	// 位置の取得
	m_pos = CScene2D::GetPosition();

	// スコアの取得
	CScore * pScore = CGame::GetScore();

	// ジョイパッドの取得
	CInputJoyPad *pInputJoyPad = CManager::GetJoyPad();

	CGame * pGame = NULL;

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
					CPlayer::PLAYERTYPE nType;

					CPlayer * pPlayer = (CPlayer*)pScene;
					nType = pPlayer->GetType();

					D3DXVECTOR3 Playerpos;
					D3DXVECTOR3 Playerpos2;

					// プレイヤーの取得
					Playerpos = pScene->GetPosition();

					// プレイヤーの取得
					Playerpos2 = pScene->GetPosition();

					if (m_pos.x >= Playerpos.x - ITEMSIZE && m_pos.x <= Playerpos.x + ITEMSIZE
						&& m_pos.y <= Playerpos.y + ITEMSIZE && m_pos.y >= Playerpos.y - ITEMSIZE)
					{// プレイヤーとアイテムの当たり判定

						bUse = true;

						if (m_nType == CItem::ITEMTYPE_000)
						{// スコア
							pScore->AddScore(500);
						}
						else if (m_nType == CItem::ITEMTYPE_001)
						{// 2way
							pPlayer->SetItemState(CPlayer::ITEMSTATE_ITEM_2WAY);
						}
						else if (m_nType == CItem::ITEMTYPE_002)
						{// スピードUP
							//pPlayer->SetItemState(CPlayer::ITEMSTATE_SPPED_UP);
						}
						else if (m_nType == CItem::ITEMTYPE_003)
						{// 分身
							if (nType == pPlayer->PLAYERTYPE_000)
							{// プレイヤー1
								CAvatar::Create(Playerpos, CAvatar::AVATARTYPE_000);
							}
							else if (nType == pPlayer->PLAYERTYPE_001)
							{// プレイヤー2
								pPlayer->SetItemState(CPlayer::ITEMSTATE_AVATAR);

								CAvatar::Create(Playerpos2, CAvatar::AVATARTYPE_001);
							}
						}
						break;
					}
				}
			}  
		}
	}
	m_pos += m_move;
	m_nTime++;

	if (m_nTime <= 5)
	{
		m_move.y = -1 * 1.1f;
	}
	else if (m_nTime >= 30)
	{
		m_move.y = 1 * 1.2f;
	}


	// 位置の設置
	CScene2D::SetPosition(m_pos, ITEMSIZE, ITEMSIZE);

	if (bUse == true)
	{// アイテムの破棄
		Uninit();
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CItem::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// アイテムの種類取得
//=============================================================================
CItem::ITEMTYPE CItem::GetItemType(void)
{
	return m_nType;
}
//=============================================================================
// アイテムの生成
//=============================================================================
CItem * CItem::Create(D3DXVECTOR3 pos, ITEMTYPE type)
{
	CItem *pItem = NULL;

	if (pItem == NULL)
	{
		pItem = new CItem;

		if (pItem != NULL)
		{
			pItem->Init(pos,type);
			pItem->BindTexture(m_apTexture[type]);
		}
	}
	return pItem;
}
//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CItem::Load(void)
{
	CManager manager;	// インスタンス

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURE_000, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURE_001, &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURE_002, &m_apTexture[2]);
	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURE_003, &m_apTexture[3]);

	return S_OK;
}
//=============================================================================
// テクスチャの破棄
//=============================================================================
void CItem::Unload(void)
{
	// テクスチャの破棄
	for (int nCntTex = 0; nCntTex < ITEMTYPE_MAX; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}
