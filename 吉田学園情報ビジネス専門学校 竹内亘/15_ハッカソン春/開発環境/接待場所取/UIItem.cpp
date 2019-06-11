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
#define TEXTURENAME000			 "data\\TEXTURE\\UI\\CAN2D.png"			//テクスチャのファイル名
#define TEXTURENAME001			 "data\\TEXTURE\\UI\\ITEMLOGO.png"		//テクスチャのファイル名

#define POS_WIDTH		(180)
#define POS_HEIGHT		(20)
//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9			CUIItem::m_pTexture[MAX_ITEM2D] = {};

//--------------------------------------------
//UIアイテムクラス コンストラクタ
//--------------------------------------------
CUIItem::CUIItem()
{
	m_pos = D3DXVECTOR3(0,0,0);						// 位置
	m_move = D3DXVECTOR3(0, 0, 0);					// 移動量
	m_posold = D3DXVECTOR3(0, 0, 0);				// 前回の位置
	m_nItem = 0;
	m_bGetItem = false;
	m_fScale = 0;
	m_ScaleCounter = 0;
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
	//NULLを代入
	for (int nCnt = 0; nCnt < MAX_ITEM2D; nCnt++)
	{
		m_pScene2D[nCnt] = NULL;
	}

	//生成
	m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3((m_pos.x), m_pos.y, m_pos.z), m_fWidth, m_fHeight);
	m_pScene2D[0]->BindTexture(m_pTexture[0]);
	//ポリゴンの更新
	m_pScene2D[0]->SetPos(m_pScene2D[0]->Getpos(), 3.0f, 0, D3DXCOLOR(1, 1, 1, 1));
	//オブジェクト種類の設定
	m_pScene2D[0]->SetObjType(CScene::OBJTYPE_SCENE2D);

	//生成
	m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(m_pos.x + 120, m_pos.y - 80, m_pos.z), 160, 80,5);
	m_pScene2D[1]->BindTexture(m_pTexture[1]);
	//オブジェクト種類の設定
	m_pScene2D[1]->SetObjType(CScene::OBJTYPE_SCENE2D);

	//NULLを代入
	for (int nCnt = 0; nCnt < MAX_ITEMNUM; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}

	float fWidth = m_fWidth / 2;
	float fHeight = m_fHeight / 2;

	//生成
	for (int nCnt = 0; nCnt < MAX_ITEMNUM; nCnt++)
	{
		if (m_apNumber[nCnt] == NULL)
		{	//数字の初期化
			m_apNumber[nCnt] = CNumber::Create(
				D3DXVECTOR3(((m_pos.x + POS_WIDTH) - (fWidth + fWidth / 5)* nCnt), m_pos.y + POS_HEIGHT, m_pos.z),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fWidth, fHeight);
		}
	}

	//値の初期化
	m_bGetItem = false;
	m_ScaleCounter = 0;
	m_fScale = 0;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CUIItem::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_ITEM2D; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			if (m_pScene2D[nCnt]->GetDeath() == false)
			{
				m_pScene2D[nCnt]->Uninit();
				m_pScene2D[nCnt] = NULL;
			}
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
	//自分を消す(2Dを破棄)
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CUIItem::Update(void)
{
	//アイテム獲得した
	if (m_bGetItem == true)
	{	//カウンター加算
		m_ScaleCounter++;
		if (m_ScaleCounter <= 5)
		{
			//拡大
			m_fScale += 15;
			m_pScene2D[0]->SetScale(m_fScale);
			//m_pScene2D[1]->SetScale(m_fScale);
			for (int nCnt = 0; nCnt < MAX_ITEMNUM; nCnt++)
			{
				if (m_apNumber[nCnt] != NULL)
				{
					m_apNumber[nCnt]->SetScale(m_fScale);
				}
			}
		}
		else if (m_ScaleCounter >= 6 && m_ScaleCounter < 10)
		{
			//縮小
			m_fScale -= 15;
			m_pScene2D[0]->SetScale(m_fScale);
			//m_pScene2D[1]->SetScale(m_fScale);
			for (int nCnt = 0; nCnt < MAX_ITEMNUM; nCnt++)
			{
				if (m_apNumber[nCnt] != NULL)
				{
					m_apNumber[nCnt]->SetScale(m_fScale);
				}
			}
		}
		else if (m_ScaleCounter == 10)
		{
			//初期化
			m_fScale = 0;
			m_pScene2D[0]->SetScale(m_fScale);
			//m_pScene2D[1]->SetScale(m_fScale);
			for (int nCnt = 0; nCnt < MAX_ITEMNUM; nCnt++)
			{
				if (m_apNumber[nCnt] != NULL)
				{
					m_apNumber[nCnt]->SetScale(m_fScale);
				}
			}
			m_ScaleCounter = 0;
			m_bGetItem = false;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CUIItem::Draw(void)
{
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
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME000, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME001, &m_pTexture[1]);

	return S_OK;
}
//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CUIItem::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_ITEM2D; nCnt++)
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

//=============================================================================
// アイテムの数を返す処理
//=============================================================================
int CUIItem::GetItemNum(void)
{
	return m_nItem;
}
//=============================================================================
// アイテムの獲得のフラグ設定
//=============================================================================
void CUIItem::SetItemBool(bool bGetItem)
{
	m_bGetItem = bGetItem;
}
