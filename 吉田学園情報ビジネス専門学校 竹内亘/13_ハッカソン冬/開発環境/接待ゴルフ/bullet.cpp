//=============================================================================
//
// ポリゴン処理 [Bullet.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "bullet.h"
#include "manager.h"
#include "scene3D.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULLET_TEXTURENAME		 "data\\TEXTURE\\bullet000.png"			//テクスチャのファイル名
#define TEX_POS_X_INIT			(1.0f)									//テクスチャ座標Uの初期位置
#define TEX_POS_Y_INIT			(1.0f)									//テクスチャ座標Vの初期位置
#define TEX_LEFT				(0.0f)									//テクスチャ座標U左
#define TEX_RIGHT				(1.0f)									//テクスチャ座標U右
#define TEX_TOP					(0.0f)									//テクスチャ座標V上
#define TEX_BOT					(1.0f)									//テクスチャ座標V下

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9			CBullet::m_pTexture = NULL;

//--------------------------------------------
//シーンバレットクラス コンストラクタ
//--------------------------------------------
CBullet::CBullet()
{
	//メンバ変数

}

//--------------------------------------------
//シーンバレットクラス デストラクタ
//--------------------------------------------
CBullet::~CBullet()
{
}

//--------------------------------------------
//シーンバレットの生成
//--------------------------------------------
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CBullet *pBullet;

	pBullet = new CBullet;

	pBullet->m_Bullet.move = move;
	pBullet->m_Bullet.pos = pos;
	pBullet->Init();

	return pBullet;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBullet::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CSceneBillBoard::Init();
	CSceneBillBoard::BindTexture(m_pTexture);
	CSceneBillBoard::Setpos(m_Bullet.pos);
	//オブジェクト種類の設定
	CScene::SetObjType(CScene::OBJTYPE_BILLBOARD);

	m_Bullet.nLife = 200;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBullet::Uninit(void)
{
	CSceneBillBoard::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBullet::Update(void)
{
	m_Bullet.pos = GetPos();
	m_Bullet.pos.x += m_Bullet.move.x;
	m_Bullet.pos.y += m_Bullet.move.y;
	m_Bullet.pos.z += m_Bullet.move.z;
	m_Bullet.nLife--;

	//CSceneBillBoard::Setpos(m_Bullet.pos);
	CSceneBillBoard::SetBillboard(m_Bullet.pos, 10, 10, 0);

	//弾のライフが尽きたら消える
	if (m_Bullet.nLife <= 0)
	{
		Uninit();
	}
#if 1
	else
	{
	}

#endif

}

//=============================================================================
// 描画処理
//=============================================================================
void CBullet::Draw(void)
{
	CSceneBillBoard::Draw();
}
//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CBullet::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		BULLET_TEXTURENAME,
		&m_pTexture);

	return S_OK;
}
//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CBullet::UnLoad(void)
{
}
