//---------------------------------------------------------------------
//	スコア処理(score.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "UIScore.h"
#include "number.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
//CNumber *CScore::m_apNumber[MAX_SCORE] = {};

//--------------------------------------------
//スコアクラス コンストラクタ
//--------------------------------------------
CScore::CScore(int nPriority) : CScene(nPriority)
{
}

//--------------------------------------------
//スコアクラス デストラクタ
//--------------------------------------------
CScore::~CScore()
{
}

//--------------------------------------------
//オブジェクトの生成
//--------------------------------------------
CScore *CScore::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CScore *pScore;
	pScore = new CScore;
	pScore->m_pos = pos;
	pScore->m_fWidth = fWidth;
	pScore->m_fHeight = fHeight;
	pScore->Init();
	return pScore;
}


//=============================================================================
// スコアの初期化処理
//=============================================================================
HRESULT CScore::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_apNumber[nCnt] == NULL)
		{	//数字の初期化
			m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3((m_pos.x - (m_fWidth * 2) * nCnt), m_pos.y, m_pos.z),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_fWidth, m_fHeight);
		}
	}
	//スコア初期化
	m_nScore = 0;
	//オブジェクトタイプの設定
	CScene::SetObjType(OBJTYPE_SCENE2D);
	return S_OK;
}

//=============================================================================
// スコアの終了処理
//=============================================================================
void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			if (m_apNumber[nCnt]->GetDeath() == false)
			{
				//スコアが作ったナンバーを消す
				m_apNumber[nCnt]->Uninit();
				m_apNumber[nCnt] = NULL;
			}
		}
	}
	//自分を破棄
	Release();
}

//=============================================================================
// スコアの更新処理
//=============================================================================
void CScore::Update(void)
{

}

//=============================================================================
// スコアの描画処理
//=============================================================================
void CScore::Draw(void)
{
	//for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	//{
	//	if (m_apNumber[nCnt] != NULL)
	//	{
	//		m_apNumber[nCnt]->Draw();
	//	}
	//}
}

//=============================================================================
// 数字の設定処理
//=============================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
}

//=============================================================================
// 数字の加算処理
//=============================================================================
void CScore::AddScore(int nValue)
{
	int nAnswer = 0;
	int nDigit = 1;
	//スコア加算
	m_nScore += nValue;

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		//桁数の計算
		nAnswer = m_nScore % (nDigit * 10) / nDigit;
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
// 現在のスコアを返す
//=============================================================================
int CScore::GetScore()
{
	return m_nScore;
}
//=============================================================================
// 色を設定
//=============================================================================
void CScore::SetColor(D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_apNumber[nCnt]->SetColor(col);
	}
}

