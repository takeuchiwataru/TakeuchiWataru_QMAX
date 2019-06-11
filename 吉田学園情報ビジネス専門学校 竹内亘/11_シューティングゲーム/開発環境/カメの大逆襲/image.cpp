//=============================================================================
//
// 画像処理 [image.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "image.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CImage::m_apTexture[IMAGE_MAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CImage::CImage() :CLogo(3)
{

}
//=============================================================================
// デストラクタ
//=============================================================================
CImage::~CImage()
{

}
//=============================================================================
// フレーム初期化処理
//=============================================================================
HRESULT CImage::Init(D3DXVECTOR3 pos, IMAGE type)
{
	CLogo::Init(pos);

	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_IMAGE);

	m_nType = type;

	// 位置の設置
	if (m_nType == IMAGE_TUTORIAL)
	{
		CLogo::SetPosition(pos, 150, 150);
	}
	else if (m_nType == IMAGE_TUTORIAL002)
	{
		CLogo::SetPosition(pos, 170, 50);
	}
	else
	{
		CLogo::SetPosition(pos, 50, 50);
	}

	return S_OK;
}
//=============================================================================
// フレーム終了処理
//=============================================================================
void CImage::Uninit(void)
{
	CLogo::Uninit();
}
//=============================================================================
// フレーム更新処理
//=============================================================================
void CImage::Update(void)
{

}
//=============================================================================
// フレーム描画処理
//=============================================================================
void CImage::Draw(void)
{
	CLogo::Draw();
}
////=============================================================================
//// 種類の取得
////=============================================================================
//CImage::IMAGE CImage::GetType(void)
//{
//	return m_nType;
//}

//=============================================================================
// 生成
//=============================================================================
CImage * CImage::Create(D3DXVECTOR3 pos, IMAGE type)
{
	CImage *pFrame = NULL;

	if (pFrame == NULL)
	{
		pFrame = new CImage;

		if (pFrame != NULL)
		{
			pFrame->Init(pos, type);
			pFrame->BindTexture(m_apTexture[type]);
		}
	}
	return pFrame;
}
//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CImage::Load(void)
{
	CManager manager;	// インスタンス

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, IMAGE_TEXTURE000, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, IMAGE_TEXTURE001, &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, IMAGE_TEXTURE002, &m_apTexture[2]);
	D3DXCreateTextureFromFile(pDevice, IMAGE_TEXTURE003, &m_apTexture[3]);

	return S_OK;
}
//=============================================================================
// テクスチャの破棄
//=============================================================================
void CImage::Unload(void)
{
	for (int nCntTex = 0; nCntTex < IMAGE_MAX; nCntTex++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}
