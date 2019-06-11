//=============================================================================
//
// 残機処理 [remain.h]
// Author : 竹内亘
//
//=============================================================================
#include "remain.h"
#include "number.h"
#include "renderer.h"
#include "manager.h"
#include "scene2D.h"
#include "player.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
//int CRemain::m_nRemain = 0;
//CNumber * CRemain::m_apNumber[MAX_REMAIN] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CRemain::CRemain()
{
	m_nRemain = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CRemain::~CRemain()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRemain::Init(D3DXVECTOR3 pos)
{
	int nRemain;

	for (int nCount = 0; nCount < MAX_REMAIN; nCount++)
	{
		m_apNumber[nCount] = new CNumber;

		//m_apNumber[nCount]->Create(D3DXVECTOR3(pos.x + (SCORE_INTERVAL_SIZE * nCount), pos.y, pos.z));// 謎
		m_apNumber[nCount]->Init(D3DXVECTOR3(pos.x - (REMAIN_INTERVAL_SIZE * nCount), pos.y, pos.z));
	}

	m_nRemain = 0;

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			CScene2D *pScene;

			// Sceneの取得
			pScene = (CScene2D*)CScene::GetScene(nCntPriority, nCntScene);

			if (pScene != NULL)
			{
				CScene::OBJTYPE objType;

				// オブジェクトの取得
				objType = pScene->GetObjType();

				if (objType == CScene::OBJTYPE_PLAYER)
				{// プレイヤーだったら
					CPlayer * pPlayer = (CPlayer*)pScene;

					nRemain = pPlayer->GetRemain();

					break;
				}
			}
		}
	}
	
	AddRemain(nRemain);

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CRemain::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_REMAIN; nCount++)
	{
		m_apNumber[nCount]->Uninit();
	}

	// オブジェクト(自分自身)の破棄
	Release();
}
//=============================================================================
// 更新処理
//=============================================================================
void CRemain::Update(void)
{
	for (int nCount = 0; nCount < MAX_REMAIN; nCount++)
	{
		m_apNumber[nCount]->Update();
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CRemain::Draw(void)
{
	for (int nCount = 0; nCount < MAX_REMAIN; nCount++)
	{
		m_apNumber[nCount]->Draw();
	}
}
////=============================================================================
//// 残機の設置
////=============================================================================
//void CRemain::SetScore(int nScore)
//{
//	m_nRemain = nScore;
//}
////=============================================================================
//// 残機の取得
////=============================================================================
//int CRemain::GetScore(void)
//{
//	return m_nRemain;
//}
//=============================================================================
// 残機の加算
//=============================================================================
void CRemain::AddRemain(int nValue)
{
	m_nRemain += nValue;

	int nAnswer = 1;
	int nRemain;

	for (int nCount = 0; nCount < MAX_REMAIN; nCount++)
	{
		nRemain = m_nRemain % (nAnswer * 10) / nAnswer;
		m_apNumber[nCount]->SetNumber(nRemain);
		nAnswer *= 10;
	}
}
//=============================================================================
// 残機の生成
//=============================================================================
CRemain * CRemain::Create(D3DXVECTOR3 pos)
{
	CRemain *pRemain = NULL;

	if (pRemain == NULL)
	{
		pRemain = new CRemain;

		if (pRemain != NULL)
		{
			pRemain->Init(pos);
		}
	}
	return pRemain;
}
