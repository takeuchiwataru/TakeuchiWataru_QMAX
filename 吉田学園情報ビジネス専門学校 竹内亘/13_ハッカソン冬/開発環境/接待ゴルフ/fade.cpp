//---------------------------------------------------------------------
// フェード処理 [title.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "fade.h"
#include "manager.h"
#include "scene.h"

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9				CFade::m_pTextureFade = NULL;
LPDIRECT3DVERTEXBUFFER9			CFade::m_pVtxBuffFade = NULL;
CFade::FADE						CFade::m_fade = CFade::FADE_NONE;
CManager::MODE					CFade::m_modeNext = CManager::MODE_TITLE;
D3DXCOLOR						CFade::m_color = D3DXCOLOR(0, 0, 0, 1);
bool							CFade::m_bNextMode = true;
//--------------------------------------------
//フェードクラス コンストラクタ
//--------------------------------------------
CFade::CFade(int nPriority)
{
}

//--------------------------------------------
//フェードクラス デストラクタ
//--------------------------------------------
CFade::~CFade()
{
}

//--------------------------------------------
//オブジェクトの生成
//--------------------------------------------
CFade * CFade::Create(CManager::MODE modeNext)
{
	CFade *pFade;

	pFade = new CFade(7);

	pFade->Init(modeNext);

	return pFade;
}

//=============================================================================
// 初期化処理
//=============================================================================
void CFade::Init(CManager::MODE modeNext)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 値の初期化
	m_fade = FADE_IN;									//フェードイン状態に
	m_modeNext = modeNext;
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//黒い画面に(不透明)

	VERTEX_2D *pVtx;//頂点情報へのポインタ

					//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffFade,
		NULL);

	//頂点情報の生成
	//頂点バッファをロックし頂点データのポインタを取得
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;

	//頂点バッファをアンロックする
	m_pVtxBuffFade->Unlock();

	m_bNextMode = true;
}

//=============================================================================
// フェードクラス 終了処理
//=============================================================================
void CFade::Uninit(void)
{
	// テクスチャの開放
	if (m_pTextureFade != NULL)
	{
		m_pTextureFade->Release();
		m_pTextureFade = NULL;
	}
	// 頂点バッファの開放
	if (m_pVtxBuffFade != NULL)
	{
		m_pVtxBuffFade->Release();
		m_pVtxBuffFade = NULL;
	}
}

//=============================================================================
// フェードクラス 更新処理
//=============================================================================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{//何もしてない状態
		if (m_fade == FADE_IN)
		{//フェードイン
			m_color.a -= 0.02f;			//画面を透明にしていく
			if (m_color.a <= 0.0f)
			{
				m_color.a = 0.0f;		//値を入れなおして初期化
				m_fade = FADE_NONE;		//何もしてない状態
			}
		}
		else if (m_fade == FADE_OUT)
		{//フェードアウト状態
			m_color.a += 0.02f;			//画面を不透明に
			if (m_color.a >= 1.0f)
			{
				m_color.a = 1.0f;		//値を入れなおして初期化
				m_fade = FADE_IN;		//フェードイン状態に
				if (m_bNextMode == true)
				{
					CManager::SetMode(m_modeNext);
				}
				//次のモードへのフラグを立てる
				m_bNextMode = true;
			}
		}
		VERTEX_2D *pVtx;								//頂点情報へのポインタ
		m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);	//頂点バッファをロックし頂点データのポインタを取得
														//頂点カラー
		pVtx[0].col = m_color;
		pVtx[1].col = m_color;
		pVtx[2].col = m_color;
		pVtx[3].col = m_color;
		//頂点バッファをアンロックする
		m_pVtxBuffFade->Unlock();
	}
}

//=============================================================================
// フェードクラス 描画処理
//=============================================================================
void CFade::Draw(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTextureFade);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// フェードの設定
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext)
{
	if (m_fade != FADE_OUT)
	{
		m_fade = FADE_OUT;									//フェードアウト状態に
		m_modeNext = modeNext;
		m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//透明に
	}
}

//=============================================================================
// フェードの取得
//=============================================================================
CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}

//=============================================================================
// フェードインアウトの設定
//=============================================================================
void CFade::SetFadeINOUT(FADE fade,bool bNextMode)
{
	m_fade = fade;
	m_bNextMode = bNextMode;
}
