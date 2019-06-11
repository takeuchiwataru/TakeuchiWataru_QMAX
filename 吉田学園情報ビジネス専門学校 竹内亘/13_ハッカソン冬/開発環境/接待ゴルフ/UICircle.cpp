//---------------------------------------------------------------------
//	サークル処理(Circle.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "UICircle.h"
#include "meshField.h"
#include "fade.h"
#include "game.h"
#include "ball.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
//#define TEXTURE_NAME001		"data\\TEXTURE\\ROAD002.jpg"	// 地面のテクスチャ名
#define TEXTURE_NAME002		"data\\TEXTURE\\Circle000.png"	// 地面のテクスチャ名
//#define TEXTURE_NAME003		"data\\TEXTURE\\Circle004.jpg"	// 地面のテクスチャ名

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9			CCircle::m_pTexture[CIRCLETEX_MAX] = {};

//--------------------------------------------
//サークルクラス コンストラクタ
//--------------------------------------------
CCircle::CCircle() : CScene(3, CScene::OBJTYPE_FIELD)
{
	m_pos = D3DXVECTOR3(0, 0, 0);					//位置
	m_posold = D3DXVECTOR3(0, 0, 0);				//前回の位置
	m_rot = D3DXVECTOR3(0, 0, 0);					//向き
	m_col = D3DXCOLOR(1, 1, 1, 1);					//色
	m_Type = CCircle::CIRCLETEX_NORMAL;
	m_fDepth = 0;
	m_fWidth = 0;
	m_fMinusWidth[MAX_CIRCLE] = { 0 };
	m_fMinusDepth[MAX_CIRCLE] = { 0 };
	m_nSplitX = 1;
	m_nSplitZ = 1;

}

//--------------------------------------------
//サークルクラス デストラクタ
//--------------------------------------------
CCircle::~CCircle()
{
}

//--------------------------------------------
//サークルの生成
//--------------------------------------------
CCircle *CCircle::Create(D3DXVECTOR3 pos, float fWidth, float fDepth, D3DXCOLOR col, CIRCLETEX tex, int nSplitX, int nSplitZ)
{
	//サークルポインタ
	CCircle *pObjectBG;
	pObjectBG = new CCircle;
	//タイプの設定
	pObjectBG->m_Type = tex;

	//初期値が入った後 pos代入
	pObjectBG->m_pos = pos;
	pObjectBG->m_fDepth = fDepth;
	pObjectBG->m_fWidth = fWidth;
	pObjectBG->m_nSplitX = nSplitX;
	pObjectBG->m_nSplitZ = nSplitZ;

	//サークルの初期化
	pObjectBG->Init();

	//サークルの情報を返す
	return pObjectBG;
}

//=============================================================================
// サークルの初期化処理
//=============================================================================
HRESULT CCircle::Init(void)
{
	//サークル種類の設定
	CScene::SetObjType(CScene::OBJTYPE_FIELD);

	m_move = D3DXVECTOR3(0, 0, 0);
	LPDIRECT3DVERTEXBUFFER9 VtxBuff = NULL;		// 頂点バッファへのポインタ

												//モデルを生成	オフセット設定
	m_pCircle[0] = CSceneMeshField::Create(m_pos, m_fWidth, m_fDepth, m_nSplitX, m_nSplitZ);
	//テクスチャを割り当て
	m_pCircle[0]->BindTexture(m_pTexture[m_Type]);
	//色を割り当て
	m_pCircle[0]->SetColor(D3DXCOLOR(1, 1, 0, 0.7f));

	//モデルを生成	オフセット設定
	m_pCircle[1] = CSceneMeshField::Create(D3DXVECTOR3(m_pos.x + m_fWidth / 4, m_pos.y + 0.2f, m_pos.z - m_fDepth / 4),
		m_fWidth / 2, m_fDepth / 2, m_nSplitX, m_nSplitZ);
	//テクスチャを割り当て
	m_pCircle[1]->BindTexture(m_pTexture[m_Type]);
	//色を割り当て
	m_pCircle[1]->SetColor(D3DXCOLOR(1, 0, 0, 0.7f));

	for (int nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
	{
		m_fMinusWidth[nCnt] = 0;
		m_fMinusDepth[nCnt] = 0;
	}
	return S_OK;
}

//=============================================================================
// サークルの終了処理
//=============================================================================
void CCircle::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
	{
		if (m_pCircle[nCnt] != NULL)
		{
			m_pCircle[nCnt]->Uninit();
			m_pCircle[nCnt] = NULL;
		}
	}

	//自分を消す(サークルを破棄)
	Release();
}

//=============================================================================
// サークルの更新処理
//=============================================================================
void CCircle::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	//カメラを取得
	CBall *pBall = CGame::GetBall();

	//カメラを取得
	CCamera *pCamera = CGame::GetCamera();

	// プレイヤーの状態を取得
	CCamera::STATE CameraState;
	CameraState = pCamera->GetState();

	if (CameraState == CCamera::STATE_FALL)
	{

		m_fMinusWidth[0] += 1.7f;
		m_fMinusDepth[0] += 1.7f;
		m_fMinusWidth[1] += 1.0f;
		m_fMinusDepth[1] += 1.0f;

		//大きい円
		if (m_pCircle[0] != NULL)
		{
			//0以下にならないように
			if (m_fMinusWidth[0] > 300.0f)
			{
				m_fMinusWidth[0] = 300.0f;
			}
			m_pCircle[0]->SetWidthDepth(m_fWidth - m_fMinusWidth[0], m_fDepth - m_fMinusDepth[0]);
			m_pCircle[0]->Setpos(D3DXVECTOR3(pBall->GetPos().x + m_fMinusWidth[0] / 2 - 150.0f,m_pos.y, pBall->GetPos().z - m_fMinusDepth[0] / 2 + 150.0f));
		}
		//小さい円
		if (m_pCircle[1] != NULL)
		{
			//0以下にならないように
			if (m_fMinusWidth[1] > 150.0f)
			{
				m_fMinusWidth[1] = 150.0f;
			}
			m_pCircle[1]->SetWidthDepth((m_fWidth / 2) - m_fMinusWidth[1], (m_fDepth / 2) - m_fMinusDepth[1]);
			m_pCircle[1]->Setpos(D3DXVECTOR3((pBall->GetPos().x + m_fWidth / 4) + m_fMinusWidth[1] / 2 - 150.0f, m_pos.y + 0.2f, (pBall->GetPos().z - m_fDepth / 4) - m_fMinusDepth[1] / 2 + 150.0f));
		}
	}

	if (pBall->GetTryTimer() > 300)
	{
		Init();
	}
}

//=============================================================================
// サークルの描画処理
//=============================================================================
void CCircle::Draw(void)
{
	//カメラを取得
	CCamera *pCamera = CGame::GetCamera();

	// プレイヤーの状態を取得
	CCamera::STATE CameraState;
	CameraState = pCamera->GetState();

	if (CameraState == CCamera::STATE_FALL)
	{
		//デバイスを取得
		CRenderer *pRenderer = CManager::GetRenderer();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

		//アルファテスト(透明色を描画しないように)
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


		for (int nCnt = 0; nCnt < MAX_CIRCLE; nCnt++)
		{
			if (m_pCircle[nCnt] != NULL)
			{
			//	m_pCircle[nCnt]->Draw();
			}
		}
		//レンダーステートの設定を元に戻す
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}

//=============================================================================
// サークルの位置設定
//=============================================================================
void CCircle::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CCircle::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME002, &m_pTexture[0]);

	return S_OK;
}
//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CCircle::UnLoad(void)
{
	for (int nCnt = 0; nCnt < CIRCLETEX_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
