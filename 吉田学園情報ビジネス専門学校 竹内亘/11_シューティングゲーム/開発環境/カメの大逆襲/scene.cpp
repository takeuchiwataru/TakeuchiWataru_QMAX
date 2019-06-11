//=============================================================================
//
// オブジェクト処理 [scene.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "scene.h"
#include "renderer.h"
#include "scene2D.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
CScene * CScene::m_apScene[NUM_PRIORITY][MAX_SCENE] = {};
int CScene::m_nNumAll = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CScene::CScene(int nPriority)
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if (m_apScene[nPriority][nCntScene] == NULL)
		{
			m_apScene[nPriority][nCntScene] = this;

			m_nID = nCntScene;			// 自分自身の番号設定
			m_nPriority = nPriority;	// 優先順位の設定
			m_objType = CScene::OBJTYPE_NONE;
			m_nNumAll++;
			break;
		}
	}
}
//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene()
{

}
//=============================================================================
// オブジェクトの種類設定
//=============================================================================
void CScene::SetObjType(OBJTYPE ObjType)
{
	m_objType = ObjType;
}
//=============================================================================
// オブジェクトの種類取得
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}
//=============================================================================
// 
//=============================================================================
CScene *CScene::GetScene(int nPriority,int nIdx)
{
	return m_apScene[nPriority][nIdx];
}
////=============================================================================
//// 
////=============================================================================
//CScene *CScene::GetScene(void)
//{
//	return;
//}
//=============================================================================
// 全て解放
//=============================================================================
void CScene::ReleseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				m_apScene[nCntPriority][nCntScene]->Uninit();

				delete m_apScene[nCntPriority][nCntScene];
				m_apScene[nCntPriority][nCntScene] = {};
			}
		}
	}
}
//=============================================================================
// 全て更新
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				m_apScene[nCntPriority][nCntScene]->Update();
			}
		}
	}
}
//=============================================================================
// 全て描画
//=============================================================================
void CScene::DrawAll()
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				m_apScene[nCntPriority][nCntScene]->Draw();
			}
		}
	}
}
//=============================================================================
// オブジェクトの破棄
//=============================================================================
void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		//delete[] m_apScene[m_nID];
		//m_apScene[m_nID] = NULL;		// ダメ!

		int nID;					// 保存用
		nID = m_nID;				// 保存	// m_nIDが不定になる前に保存する

		int nPriority;				// 優先順位の保存用
		nPriority = m_nPriority;	// 保存

		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
	}
}
