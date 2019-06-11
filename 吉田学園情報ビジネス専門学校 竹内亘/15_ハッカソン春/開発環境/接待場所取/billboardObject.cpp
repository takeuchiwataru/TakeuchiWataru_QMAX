//=============================================================================
//
// オブジェクトビルボード処理 [billboardEnemy.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "billboardObject.h"
#include "manager.h"
#include "scene2D.h"
#include "game.h"
#include "effect.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\BILLBOARD\\tree000.png"	//テクスチャのファイル名
#define TEXTURENAME001			 "data\\TEXTURE\\TITLE\\title.png"			//テクスチャのファイル名
#define TEXTURENAME002			 "data\\TEXTURE\\BILLBOARD\\CAN2D.png"		//テクスチャのファイル名

#define TEX_POS_X_INIT			(1.0f)									//テクスチャ座標Uの初期位置
#define TEX_POS_Y_INIT			(1.0f)									//テクスチャ座標Vの初期位置
#define TEX_LEFT				(0.0f)									//テクスチャ座標U左
#define TEX_RIGHT				(1.0f)									//テクスチャ座標U右
#define TEX_TOP					(0.0f)									//テクスチャ座標V上
#define TEX_BOT					(1.0f)									//テクスチャ座標V下

#define DEPTH					(30.0f)
#define PLAYER_DEPTH			(5.0f)			//プレイヤーの幅調整用
#define PLAYER_HEIGHT			(10.0f)			//プレイヤーの背の高さ

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9			CBillBoardObject::m_pTexture[TEXTYPE_MAX] = {};

//--------------------------------------------
//ビルボード(オブジェクト)クラス コンストラクタ
//--------------------------------------------
CBillBoardObject::CBillBoardObject()
{
	m_pos = D3DXVECTOR3(0,0,0);				// 位置
	m_move = D3DXVECTOR3(0, 0, 0);			// 移動量
	m_posold = D3DXVECTOR3(0, 0, 0);		// 前回の位置
	m_fSpin = 0;							// 回転
	m_fScale = 0;							// 拡大縮小

}

//--------------------------------------------
//ビルボード(オブジェクト)クラス デストラクタ
//--------------------------------------------
CBillBoardObject::~CBillBoardObject()
{
}

//--------------------------------------------
//ビルボード(オブジェクト)の生成
//--------------------------------------------
CBillBoardObject *CBillBoardObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, TEXTYPE TexType)
{
	CBillBoardObject *pObject;

	pObject = new CBillBoardObject;

	pObject->m_move = move;
	pObject->m_pos = pos;
	pObject->m_TexType = TexType;
	pObject->m_fHeight = fHeight;
	pObject->m_fWidth = fWidth;
	pObject->Init();

	return pObject;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBillBoardObject::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pBillBoard = NULL;
	m_pBillBoard = CSceneBillBoard::Create(m_pos, D3DXVECTOR3(0, 0, 0), m_fWidth, m_fHeight);
	m_pBillBoard->BindTexture(m_pTexture[m_TexType]);
	m_pBillBoard->Setpos(m_pos);
	//オブジェクト種類の設定
	CScene::SetObjType(CScene::OBJTYPE_BILLBOARDOBJECT);

	m_fSpin = 0;
	m_fScale = 0;

	switch (m_TexType)
	{
	case TEXTYPE_TREE:
		//CShadow::Create(D3DXVECTOR3(m_pos.x, 1.0f, m_pos.z), 50, 50);
		break;
	case TEXTYPE_TITLE:
		CShadow::Create(D3DXVECTOR3(m_pos.x, 1.0f, m_pos.z), 100, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f), CShadow::SHADOWTYPE_NORMAL);
		break;
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBillBoardObject::Uninit(void)
{
	if (m_pBillBoard != NULL)
	{
		m_pBillBoard->Uninit();
		m_pBillBoard = NULL;
	}

	for (int nCnt = 0; nCnt < TEXTYPE_MAX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
	//自分を消す(破棄)
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBillBoardObject::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CBillBoardObject::Draw(void)
{

}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CBillBoardObject::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCnt = 0; nCnt < TEXTYPE_MAX; nCnt++)
	{
		m_pTexture[nCnt] = NULL;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME000, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME001, &m_pTexture[1]);

	return S_OK;
}

//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CBillBoardObject::UnLoad(void)
{
	for (int nCnt = 0; nCnt < TEXTYPE_MAX; nCnt++)
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
bool CBillBoardObject::CollisionBillboardObject(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
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
		}
	}

	return false;
}
