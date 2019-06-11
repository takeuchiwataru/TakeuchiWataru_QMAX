//=============================================================================
//
// UIチュートリアル処理 [2DTUTO.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "2DTuto.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TUTORIALBG000_TEXTURENAME	"data/TEXTURE/TUTORIAL/tutorial.png"	//テクスチャのファイル名
#define TUTORIALBG001_TEXTURENAME	"data/TEXTURE/TUTORIAL/tutorial001.jpg"	//テクスチャのファイル名
#define TUTORIALBG002_TEXTURENAME	"data/TEXTURE/TUTORIAL/GameStart000.png"	//テクスチャのファイル名

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9			C2DTUTO::m_pTexture[MAX_2DTUTO] = {};

//--------------------------------------------
//UIチュートリアルクラス コンストラクタ
//--------------------------------------------
C2DTUTO::C2DTUTO()
{
	m_pos = D3DXVECTOR3(0,0,0);						// 位置
	m_move = D3DXVECTOR3(0, 0, 0);					// 移動量
	m_posold = D3DXVECTOR3(0, 0, 0);				// 前回の位置

}

//--------------------------------------------
//UIチュートリアルクラス デストラクタ
//--------------------------------------------
C2DTUTO::~C2DTUTO()
{
}

//--------------------------------------------
//UIチュートリアルの生成
//--------------------------------------------
C2DTUTO *C2DTUTO::Create(D3DXVECTOR3 pos,float fWidth, float fHeight)
{
	C2DTUTO *pScene2D;

	pScene2D = new C2DTUTO;

	pScene2D->m_pos = pos;
	pScene2D->m_fHeight = fHeight;
	pScene2D->m_fWidth = fWidth;
	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT C2DTUTO::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT /2, m_pos.z), SCREEN_WIDTH / 1.4f,SCREEN_HEIGHT / 1.4f);
	m_pScene2D[0]->BindTexture(m_pTexture[0]);
	//オブジェクト種類の設定
	m_pScene2D[0]->SetObjType(CScene::OBJTYPE_SCENE2D);

	//m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(230.0f, 470.0f, m_pos.z), 320, 160);
	//m_pScene2D[1]->BindTexture(m_pTexture[1]);
	////オブジェクト種類の設定
	//m_pScene2D[1]->SetObjType(CScene::OBJTYPE_SCENE2D);

	//m_pScene2D[2] = CScene2D::Create(D3DXVECTOR3(920.0f, 70.0f, m_pos.z), 500, 100);
	//m_pScene2D[2]->BindTexture(m_pTexture[2]);
	////オブジェクト種類の設定
	//m_pScene2D[2]->SetObjType(CScene::OBJTYPE_SCENE2D);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void C2DTUTO::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_2DTUTO; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			m_pScene2D[nCnt]->Uninit();
			m_pScene2D[nCnt] = NULL;
		}
	}
	//自分を消す(プレイヤーを破棄)
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void C2DTUTO::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void C2DTUTO::Draw(void)
{

}
//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT C2DTUTO::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCnt = 0; nCnt < MAX_2DTUTO; nCnt++)
	{
		m_pTexture[nCnt] = NULL;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TUTORIALBG000_TEXTURENAME, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TUTORIALBG001_TEXTURENAME, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TUTORIALBG002_TEXTURENAME, &m_pTexture[2]);

	return S_OK;
}
//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void C2DTUTO::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_2DTUTO; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
