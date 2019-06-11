//=============================================================================
//
// 敵ビルボード処理 [billboardEnemy.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "billboardEnemy.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\akira000.png"			//テクスチャのファイル名
#define TEX_POS_X_INIT			(1.0f)									//テクスチャ座標Uの初期位置
#define TEX_POS_Y_INIT			(1.0f)									//テクスチャ座標Vの初期位置
#define TEX_LEFT				(0.0f)									//テクスチャ座標U左
#define TEX_RIGHT				(1.0f)									//テクスチャ座標U右
#define TEX_TOP					(0.0f)									//テクスチャ座標V上
#define TEX_BOT					(1.0f)									//テクスチャ座標V下

#define DEPTH					(30.0f)
#define PLAYER_DEPTH			(1.0f)			//プレイヤーの幅調整用
#define PLAYER_HEIGHT			(10.0f)			//プレイヤーの背の高さ

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9			CBillBoardEnemy::m_pTexture[ENEMYTEX_MAX] = {};

//--------------------------------------------
//ビルボード(敵)クラス コンストラクタ
//--------------------------------------------
CBillBoardEnemy::CBillBoardEnemy()
{
	m_pos = D3DXVECTOR3(0,0,0);						// 位置
	m_move = D3DXVECTOR3(0, 0, 0);					// 移動量
	m_posold = D3DXVECTOR3(0, 0, 0);					// 前回の位置
	m_TexType = ENEMYTEX_HUMAN000;
	m_moveType = ENEMYMOVE_NONE;

}

//--------------------------------------------
//ビルボード(敵)クラス デストラクタ
//--------------------------------------------
CBillBoardEnemy::~CBillBoardEnemy()
{
}

//--------------------------------------------
//ビルボード(敵)の生成
//--------------------------------------------
CBillBoardEnemy *CBillBoardEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, ENEMYTEX TexType, ENEMYMOVE moveType)
{
	CBillBoardEnemy *pEnemy;

	pEnemy = new CBillBoardEnemy;

	pEnemy->m_move = move;
	pEnemy->m_pos = pos;
	pEnemy->m_TexType = TexType;
	pEnemy->m_moveType = moveType;
	pEnemy->m_fHeight = fHeight;
	pEnemy->m_fWidth = fWidth;
	pEnemy->Init();

	return pEnemy;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBillBoardEnemy::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pBillBoard = CSceneBillBoard::Create(m_pos, D3DXVECTOR3(0,0,0), m_fWidth, m_fHeight);
	m_pBillBoard->BindTexture(m_pTexture[m_TexType]);
	m_pBillBoard->Setpos(m_pos);
	//オブジェクト種類の設定
	CScene::SetObjType(CScene::OBJTYPE_BILLBOARDENEMY);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBillBoardEnemy::Uninit(void)
{
	if (m_pBillBoard != NULL)
	{
		m_pBillBoard->Uninit();
		m_pBillBoard = NULL;
	}
	//自分を消す(プレイヤーを破棄)
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBillBoardEnemy::Update(void)
{


}

//=============================================================================
// 描画処理
//=============================================================================
void CBillBoardEnemy::Draw(void)
{
	//if (m_pBillBoard != NULL)
	//{
	//	m_pBillBoard->Draw();
	//}
}
//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CBillBoardEnemy::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME000, &m_pTexture[0]);

	return S_OK;
}
//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CBillBoardEnemy::UnLoad(void)
{
	for (int nCnt = 0; nCnt < ENEMYTEX_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// 当たり判定処理
//=============================================================================
bool CBillBoardEnemy::CollisionBillboardEnemy(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
	D3DXVECTOR3 WidthMax;
	D3DXVECTOR3 WidthMin;
	WidthMax.x = m_pos.x + m_fWidth;	// 位置込みの横幅
	WidthMax.z = m_pos.z + DEPTH;		// 位置込みの奥行き

	WidthMin.x = m_pos.x - m_fWidth;	// 位置込みの横幅
	WidthMin.z = m_pos.z - DEPTH;		// 位置込みの奥行き

	if (pPos->x >= WidthMin.x - PLAYER_DEPTH && pPos->x <= WidthMax.x + PLAYER_DEPTH)
	{// Xの範囲内にいる
		if (pPos->z >= WidthMin.z - PLAYER_DEPTH && pPos->z <= WidthMax.z + PLAYER_DEPTH)
		{// Zの範囲内にいる

		 // 無移動オブジェクト
			if (pPosOld->x - PLAYER_DEPTH >= WidthMax.x && pPos->x - PLAYER_DEPTH < WidthMax.x)
			{// 右から抜けた場合
				pPos->x = WidthMax.x + PLAYER_DEPTH;
			}
			else if (pPosOld->x + PLAYER_DEPTH <= WidthMin.x && pPos->x + PLAYER_DEPTH > WidthMin.x)
			{// 左から抜けた場合
				pPos->x = WidthMin.x - PLAYER_DEPTH;
			}
			if (pPosOld->z - PLAYER_DEPTH >= WidthMax.z && pPos->z - PLAYER_DEPTH < WidthMax.z)
			{// 奥から抜けた場合
				pPos->z = WidthMax.z + PLAYER_DEPTH;
			}
			else if (pPosOld->z + PLAYER_DEPTH <= WidthMin.z && pPos->z + PLAYER_DEPTH > WidthMin.z)
			{// 手前から抜けた場合
				pPos->z = WidthMin.z - PLAYER_DEPTH;
				pMove->z = -100.0f;
			}
		}
	}
	return false;
}
