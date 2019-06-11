//=============================================================================
//
// UIアイテム処理 [UIItem.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "UIItem.h"
#include "manager.h"
#include "number.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ITEMTEXTURENAME000			 "data\\TEXTURE\\guarana.png"			//テクスチャのファイル名

#define POS_WIDTH		(120)
#define POS_HEIGHT		(15)
//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9			CUIItem::m_pTexture[1] = {};

//--------------------------------------------
//UIアイテムクラス コンストラクタ
//--------------------------------------------
CUIItem::CUIItem()
{
	m_pos = D3DXVECTOR3(0,0,0);						// 位置
	m_move = D3DXVECTOR3(0, 0, 0);					// 移動量
	m_posold = D3DXVECTOR3(0, 0, 0);					// 前回の位置
	m_nItem = 0;
}

//--------------------------------------------
//UIアイテムクラス デストラクタ
//--------------------------------------------
CUIItem::~CUIItem()
{
}

//--------------------------------------------
//UIアイテムの生成
//--------------------------------------------
CUIItem *CUIItem::Create(D3DXVECTOR3 pos,float fWidth, float fHeight)
{
	CUIItem *pScene2D;

	pScene2D = new CUIItem;

	pScene2D->m_pos = pos;
	pScene2D->m_fHeight = fHeight;
	pScene2D->m_fWidth = fWidth;
	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CUIItem::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		m_pScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3((m_pos.x + (m_fWidth + 25)* nCnt), m_pos.y, m_pos.z), m_fWidth, m_fHeight);
		m_pScene2D[nCnt]->BindTexture(m_pTexture[0]);
		//ポリゴンの更新
		m_pScene2D[nCnt]->SetPos(m_pScene2D[nCnt]->Getpos() , 3.0f, 0, D3DXCOLOR(1,1,1,1));

		//オブジェクト種類の設定
		m_pScene2D[nCnt]->SetObjType(CScene::OBJTYPE_SCENE2D);
	}

	for (int nCnt = 0; nCnt < MAX_ITEMNUM; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}

	float fWidth = m_fWidth / 2;
	float fHeight = m_fHeight / 2;

	for (int nCnt = 0; nCnt < MAX_ITEMNUM; nCnt++)
	{
		if (m_apNumber[nCnt] == NULL)
		{	//数字の初期化
			m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(((m_pos.x + POS_WIDTH)- (fWidth + fWidth)* nCnt)
				, m_pos.y + POS_HEIGHT, m_pos.z),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fWidth, fHeight);
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CUIItem::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			m_pScene2D[nCnt]->Uninit();
			m_pScene2D[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < MAX_ITEMNUM; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			if (m_apNumber[nCnt]->GetDeath() == false)
			{
				//UIアイテムが作ったナンバーを消す
				m_apNumber[nCnt]->Uninit();
				m_apNumber[nCnt] = NULL;
			}
		}
	}

	//自分を消す(プレイヤーを破棄)
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CUIItem::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CUIItem::Draw(void)
{
	//for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	//{
	//	if (m_pScene2D[nCnt] != NULL)
	//	{
	//		m_pScene2D[nCnt]->Draw();
	//	}
	//}
}
//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CUIItem::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, ITEMTEXTURENAME000, &m_pTexture[0]);

	return S_OK;
}
//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CUIItem::UnLoad(void)
{
	for (int nCnt = 0; nCnt < 1; nCnt++)
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
// 加算処理
//=============================================================================
void CUIItem::PlusItem(int nAddItem)
{
	int nAnswer = 0;
	int nDigit = 1;

	m_nItem += nAddItem;

	for (int nCnt = 0; nCnt < MAX_ITEMNUM; nCnt++)
	{
		//桁数の計算
		nAnswer = m_nItem % (nDigit * 10) / nDigit;
		//その桁の数字をセット
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->SetNumber(nAnswer);
		}
		//次の桁へ
		nDigit *= 10;
	}
}
