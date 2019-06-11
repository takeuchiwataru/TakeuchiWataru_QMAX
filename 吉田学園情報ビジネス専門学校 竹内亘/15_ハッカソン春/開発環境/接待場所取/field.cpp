//---------------------------------------------------------------------
//	フィールド処理(field.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "field.h"
#include "meshField.h"
#include "fade.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME000		"data\\TEXTURE\\FIELD\\field002.jpg"	// 地面のテクスチャ名
#define TEXTURE_NAME001		"data\\TEXTURE\\FIELD\\ROAD002.jpg"		// 地面のテクスチャ名
#define TEXTURE_NAME002		"data\\TEXTURE\\FIELD\\field001.jpg"	// 地面のテクスチャ名
#define TEXTURE_NAME003		"data\\TEXTURE\\FIELD\\field004.jpg"	// 地面のテクスチャ名

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9			CField::m_pTexture[FIELDTEX_MAX] = {};

//--------------------------------------------
//フィールドクラス コンストラクタ
//--------------------------------------------
CField::CField() : CScene(3, CScene::OBJTYPE_FIELD)
{
	m_pos = D3DXVECTOR3(0, 0, 0);					//位置
	m_posold = D3DXVECTOR3(0, 0, 0);				//前回の位置
	m_rot = D3DXVECTOR3(0, 0, 0);					//向き
	m_Type = CField::FIELDTEX_NORMAL;
	m_fDepth = 0;
	m_fWidth = 0;
	m_nSplitX = 1;
	m_nSplitZ = 1;

}

//--------------------------------------------
//フィールドクラス デストラクタ
//--------------------------------------------
CField::~CField()
{
}

//--------------------------------------------
//フィールドの生成
//--------------------------------------------
CField *CField::Create(D3DXVECTOR3 pos, float fWidth, float fDepth, FIELDTEX tex, int nSplitX, int nSplitZ)
{
	//フィールドポインタ
	CField *pObjectBG;
	pObjectBG = new CField;
	//タイプの設定
	pObjectBG->m_Type = tex;

	//初期値が入った後 pos代入
	pObjectBG->m_pos = pos;
	pObjectBG->m_fDepth = fDepth;
	pObjectBG->m_fWidth = fWidth;
	pObjectBG->m_nSplitX = nSplitX;
	pObjectBG->m_nSplitZ = nSplitZ;

	//フィールドの初期化
	pObjectBG->Init();

	//フィールドの情報を返す
	return pObjectBG;
}

//=============================================================================
// フィールドの初期化処理
//=============================================================================
HRESULT CField::Init(void)
{
	//フィールド種類の設定
	CScene::SetObjType(CScene::OBJTYPE_FIELD);

	m_move = D3DXVECTOR3(0, 0, 0);
	LPDIRECT3DVERTEXBUFFER9 VtxBuff = NULL;		// 頂点バッファへのポインタ

	//モデルを生成	オフセット設定
	m_pField = CSceneMeshField::Create(m_pos, m_fWidth,m_fDepth,m_nSplitX,m_nSplitZ);
	//モデルを割り当て
	m_pField->BindTexture(m_pTexture[m_Type]);

	return S_OK;
}

//=============================================================================
// フィールドの終了処理
//=============================================================================
void CField::Uninit(void)
{
	if (m_pField != NULL)
	{
		m_pField->Uninit();
		m_pField = NULL;
	}

	//for (int nCnt = 0; nCnt < FIELDTEX_MAX; nCnt++)
	//{
	//	if (m_pTexture[nCnt] != NULL)
	//	{
	//		m_pTexture[nCnt] = NULL;
	//	}
	//}

	//自分を消す(フィールドを破棄)
	Release();
}

//=============================================================================
// フィールドの更新処理
//=============================================================================
void CField::Update(void)
{
}

//=============================================================================
// フィールドの描画処理
//=============================================================================
void CField::Draw(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (m_pField != NULL)
	{
		m_pField->Draw();
	}
}

//=============================================================================
// フィールドの位置設定
//=============================================================================
void CField::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CField::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCnt = 0; nCnt < FIELDTEX_MAX; nCnt++)
	{
		m_pTexture[nCnt] = NULL;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME000, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME001, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME002, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME003, &m_pTexture[3]);

	return S_OK;
}
//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CField::UnLoad(void)
{
	for (int nCnt = 0; nCnt < FIELDTEX_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt] = NULL;
		}
	}
}
