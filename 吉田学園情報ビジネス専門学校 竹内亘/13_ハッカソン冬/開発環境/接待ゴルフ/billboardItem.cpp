//=============================================================================
//
// アイテムビルボード処理 [billboardEnemy.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "billboardItem.h"
#include "manager.h"
#include "scene2D.h"
#include "UIItem.h"
#include "game.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\guarana.png"			//テクスチャのファイル名
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
LPDIRECT3DTEXTURE9			CBillBoardItem::m_pTexture[ITEMTEX_MAX] = {};

//--------------------------------------------
//ビルボード(アイテム)クラス コンストラクタ
//--------------------------------------------
CBillBoardItem::CBillBoardItem()
{
	m_pos = D3DXVECTOR3(0,0,0);				// 位置
	m_move = D3DXVECTOR3(0, 0, 0);			// 移動量
	m_posold = D3DXVECTOR3(0, 0, 0);		// 前回の位置
	m_fSpin = 0;							// 回転
	m_fScale = 0;							// 拡大縮小

	m_Scene2DPos = D3DXVECTOR3(0, 0, 0);
	m_Scene2DMove = D3DXVECTOR3(0, 0, 0);
	m_Scene2DCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

	m_TexType = ITEMTEX_NORMAL;
	m_moveType = ITEMMOVE_NONE;
	m_bGetItem = false;
	m_bCreate2D = false;

	m_pScene2D = NULL;
}

//--------------------------------------------
//ビルボード(アイテム)クラス デストラクタ
//--------------------------------------------
CBillBoardItem::~CBillBoardItem()
{
}

//--------------------------------------------
//ビルボード(アイテム)の生成
//--------------------------------------------
CBillBoardItem *CBillBoardItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, ITEMTEX TexType, ITEMMOVE moveType)
{
	CBillBoardItem *pItem;

	pItem = new CBillBoardItem;

	pItem->m_move = move;
	pItem->m_pos = pos;
	pItem->m_TexType = TexType;
	pItem->m_moveType = moveType;
	pItem->m_fHeight = fHeight;
	pItem->m_fWidth = fWidth;
	pItem->Init();

	return pItem;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBillBoardItem::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pBillBoard = CSceneBillBoard::Create(m_pos, m_fWidth, m_fHeight);
	m_pBillBoard->BindTexture(m_pTexture[m_TexType]);
	m_pBillBoard->Setpos(m_pos);
	//オブジェクト種類の設定
	CScene::SetObjType(CScene::OBJTYPE_BILLBOARDITEM);

	m_fSpin = 0;
	m_fScale = 0;

	m_Scene2DPos = D3DXVECTOR3(0, 0, 0);
	m_Scene2DMove = D3DXVECTOR3(0, 0, 0);

	m_TexType = ITEMTEX_NORMAL;
	m_moveType = ITEMMOVE_NONE;
	m_bGetItem = false;
	m_bCreate2D = false;
	m_pScene2D = NULL;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBillBoardItem::Uninit(void)
{
	if (m_pBillBoard != NULL)
	{
		m_pBillBoard->Uninit();
		m_pBillBoard = NULL;
	}

	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}
	//自分を消す(破棄)
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBillBoardItem::Update(void)
{
	if (m_bGetItem == true && m_bCreate2D == false && m_pBillBoard != NULL)
	{
		if (m_pBillBoard != NULL)
		{
			m_pBillBoard->Uninit();
			m_pBillBoard = NULL;
		}

		m_pScene2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 400, 0), 50, 50);
		m_Scene2DPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 400, 0);
		m_Scene2DPosInit = D3DXVECTOR3(SCREEN_WIDTH / 2, 400, 0);
		//m_Scene2DMove = D3DXVECTOR3(-1.0f, 1.0f, 0);
		m_pScene2D->BindTexture(m_pTexture[0]);
		m_bCreate2D = true;
	}

	if (m_pScene2D != NULL)
	{
		//フラグがtrueの時ホーミングする
		D3DXVECTOR3 m_HomingPos;
		D3DXVECTOR3 m_TargetPos = D3DXVECTOR3(80, 80, 0);
		D3DXVECTOR3 Angle = D3DXVECTOR3(0, 0, 0);
		float fMoveAngle = 0;
		float fDestAngle = 0;
		float fDiffAngle = 0;

		//プレイヤーとエネミーの距離を求める
		m_HomingPos.x = m_TargetPos.x - m_Scene2DPosInit.x;
		m_HomingPos.y = m_TargetPos.y - m_Scene2DPosInit.y;
		//弾とプレイヤーの距離を求める
		Angle.x = m_Scene2DPos.x - m_TargetPos.x;
		Angle.y = m_Scene2DPos.y - m_TargetPos.y;

		//角度を求める
		fMoveAngle = atan2f(m_HomingPos.x, m_HomingPos.y);
		fDestAngle = atan2f(Angle.x, Angle.y);

		fDiffAngle = fDestAngle - fMoveAngle;
		if (fDiffAngle > D3DX_PI)
		{
			fDiffAngle -= D3DX_PI * 2.0f;
		}
		if (fDiffAngle < D3DX_PI)
		{
			fDiffAngle += D3DX_PI * 2.0f;
		}

		fMoveAngle += fDiffAngle * 1.0f;

		if (fMoveAngle > D3DX_PI)
		{
			fMoveAngle -= D3DX_PI * 2.0f;
		}
		if (fMoveAngle < D3DX_PI)
		{
			fMoveAngle += D3DX_PI * 2.0f;
		}

		D3DXVECTOR3 MovePos(0.0f, 0.0f, 0.0f);
		//移動量を設定
		MovePos.x += sinf(fMoveAngle) * 25.0f;
		MovePos.y += cosf(fMoveAngle) * 25.0f;
		m_Scene2DMove = MovePos;

		//目標地点までの値を引いていく
		m_Scene2DPos -= m_Scene2DMove;

		//回転
		m_fSpin += 0.1f;
		//縮小
		m_fScale -= 0.5f;

		if (m_fScale < -40)
		{
			m_fScale = -40;
		}

		//透明度
		m_Scene2DCol.a -= 0.005f;


		//角度が一定値になったとき
		if (m_fSpin > D3DX_PI)
		{
			m_fSpin *= -1;
		}
		else if (m_fSpin < -D3DX_PI)
		{
			m_fSpin *= -1;
		}

		//ポリゴンの更新
		m_pScene2D->SetPos(m_Scene2DPos,m_fSpin,m_fScale, m_Scene2DCol);

#ifdef  _DEBUG
		CDebugProc::Print(1, " 2DITEM位置 : ( %.1f,%.1f,%.1f )\n", m_Scene2DPos.x
			, m_Scene2DPos.y, m_Scene2DPos.z);
#endif

		if (m_TargetPos.x - 10.0f < m_Scene2DPos.x && m_TargetPos.x + 10.0f > m_Scene2DPos.x
			&& m_TargetPos.y - 10.0f < m_Scene2DPos.y && m_TargetPos.y + 10.0f > m_Scene2DPos.y)
		{
			//UIの位置に行ったときに破棄
			m_pScene2D->Uninit();
			m_pScene2D = NULL;
			//アイテムをカウント
			CUIItem *pItem = CGame::GetUIItem();
			pItem->PlusItem(1);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CBillBoardItem::Draw(void)
{

}
//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CBillBoardItem::Load(void)
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
void CBillBoardItem::UnLoad(void)
{
	for (int nCnt = 0; nCnt < ITEMTEX_MAX; nCnt++)
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
bool CBillBoardItem::CollisionBillboardItem(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
	D3DXVECTOR3 WidthMax;
	D3DXVECTOR3 WidthMin;
	WidthMax.x = m_pos.x + m_fWidth;	// 位置込みの横幅
	WidthMax.z = m_pos.z + DEPTH;		// 位置込みの奥行き

	WidthMin.x = m_pos.x - m_fWidth;	// 位置込みの横幅
	WidthMin.z = m_pos.z - DEPTH;		// 位置込みの奥行き


	if (m_bGetItem == false)
	{
		if (pPos->x >= WidthMin.x - PLAYER_DEPTH && pPos->x <= WidthMax.x + PLAYER_DEPTH)
		{// Xの範囲内にいる
			if (pPos->z >= WidthMin.z - PLAYER_DEPTH && pPos->z <= WidthMax.z + PLAYER_DEPTH)
			{// Zの範囲内にいる

				m_bGetItem = true;
				//Uninit();
			}
		}
	}
	return false;
}
