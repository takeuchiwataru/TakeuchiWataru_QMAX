//---------------------------------------------------------------------
//	シーン処理(scene.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "scene.h"
#include "debugproc.h"
#include "manager.h"
#include "fade.h"
#include "pause.h"
//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
CScene *CScene::m_pTop[NUM_PRIORITY] = {};
CScene *CScene::m_pCur[NUM_PRIORITY] = {};
bool    CScene::m_bPause = false;
//--------------------------------------------
//シーンクラス コンストラクタ
//--------------------------------------------
CScene::CScene(int nPriority ,CScene::OBJTYPE ObjType)
{
		//CURがいないとき自分が最初になる
		if (m_pCur[nPriority] == NULL)
		{
			m_pTop[nPriority] = this;
		}
		else
		{
			//最後尾のオブジェクトの次がNULLの時
			if (m_pCur[nPriority]->m_pNext == NULL)
			{
				m_pCur[nPriority]->m_pNext = this;
			}
		}
		m_pDeath = false;
		m_pPrev = m_pCur[nPriority];
		m_pNext = NULL;
		m_nPriority = nPriority;
		m_ObjType = ObjType;
		m_pCur[nPriority] = this;
}

//--------------------------------------------
//シーンクラス デストラクタ
//--------------------------------------------
CScene::~CScene()
{

}

void CScene::Setpos(D3DXVECTOR3 pos)
{
}

//--------------------------------------------
//シーンの基本クラス シーンの総数を取得
//--------------------------------------------
int CScene::GetNumAll(void)
{
	return 0;
}

//--------------------------------------------
//全ての開放処理
//--------------------------------------------
void CScene::ReleaseAll(void)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CScene *pScene = m_pTop[nCntPri];
		CScene *pNext = NULL;

		while (pScene)	//NULLチェック
		{
			//一時保存
			pNext = pScene->m_pNext;
			//破棄
			pScene->Uninit();
			//一時保存を代入
			pScene = pNext;
		}
		//TOPに戻す
		pScene = m_pTop[nCntPri];
		//フラグが立っているオブジェクトを破棄
		while (pScene)	//NULLチェック
		{
			CScene *pSceneNext = pScene->m_pNext;
			//削除処理
			if (pScene->m_pDeath == true)
			{
				pScene->UninitAll();
			}
			//次のオブジェクトのアドレスを代入
			pScene = pSceneNext;
		}
	}
}
//--------------------------------------------
//全ての更新処理
//--------------------------------------------
void CScene::UpdateAll(void)
{
	int nPriModelNum = 0;
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//ジョイパッド情報を取得
	CInputJoypad *pInputJoypad = CManager::GetCInputJoypad();

	//現在のポーズのモードを取得
	CPause::SELECTMODE *PauseMode = CPause::GetPauseMode();

	//フェードしていないときにポーズできる
	if (pInput->GetTrigger(DIK_P) == true && CFade::GetFade() == CFade::FADE_NONE && CManager::GetMode() == CManager::MODE_GAME
		|| pInputJoypad->GetTrigger(CInputJoypad::BUTTON_START) == true && CFade::GetFade() == CFade::FADE_NONE && CManager::GetMode() == CManager::MODE_GAME)
	{
		m_bPause = m_bPause ? false : true;
		CPause::SetPauseBool(m_bPause);
	}

	if (m_bPause == false)
	{
		for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
		{
			CScene *pScene = m_pTop[nCntPri];
			nPriModelNum = 0;
			while (pScene)	//NULLチェック
			{
				//Updateで消えたりするので残しておく
				CScene *pSceneNext = pScene->m_pNext;
				//デスチェック
				if (pScene->m_pDeath == false)
				{
					//更新処理
					pScene->Update();
				}
				//次のオブジェクトのアドレスを代入
				pScene = pSceneNext;
				nPriModelNum++;
			}

			//TOPに戻す
			pScene = m_pTop[nCntPri];
			//フラグが立っているオブジェクトを破棄
			while (pScene)	//NULLチェック
			{
				//Updateで消えたりするので残しておく
				CScene *pSceneNext = pScene->m_pNext;
				//削除処理
				if (pScene->m_pDeath == true)
				{
					pScene->UninitAll();
				}
				//次のオブジェクトのアドレスを代入
				pScene = pSceneNext;
			}
		}
	}
	else
	{
		for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
		{
			CScene *pScene = m_pTop[nCntPri];
			nPriModelNum = 0;

			while (pScene)	//NULLチェック
			{
				//Updateで消えたりするので残しておく
				CScene *pSceneNext = pScene->m_pNext;
				//デスチェック
				if (pScene->m_pDeath == false)
				{
					if (pScene->GetObjType() == OBJTYPE_PAUSE)
					{
						//更新処理
						pScene->Update();
					}
				}
				//次のオブジェクトのアドレスを代入
				pScene = pSceneNext;
				nPriModelNum++;
			}

			//TOPに戻す
			pScene = m_pTop[nCntPri];
			//フラグが立っているオブジェクトを破棄
			while (pScene)	//NULLチェック
			{
				//Updateで消えたりするので残しておく
				CScene *pSceneNext = pScene->m_pNext;
				//削除処理
				if (pScene->m_pDeath == true)
				{
					pScene->UninitAll();
				}
				//次のオブジェクトのアドレスを代入
				pScene = pSceneNext;
			}
		}
	}
}
//--------------------------------------------
//全ての描画処理
//--------------------------------------------
void CScene::DrawAll(void)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CScene *pScene = m_pTop[nCntPri];

		while (pScene)	//NULLチェック
		{
			//Updateで消えたりするので残しておく
			CScene *pSceneNext = pScene->m_pNext;
			//描画処理
			if (pScene->GetObjType() != OBJTYPE_MODEL)
			{
				pScene->Draw();
			}
			//次のオブジェクトのアドレスを代入
			pScene = pSceneNext;
		}
	}
}

//--------------------------------------------
//全消去処理
//--------------------------------------------
void CScene::UninitAll(void)
{
	//NULL　チェック
		if (this != NULL)
		{
			if (m_pNext != NULL)
			{
				if (m_pPrev != NULL)
				{
					//次のオブジェクトへのポインタがあるとき前のポインタのpNextに自分のpNextを代入
					m_pPrev->m_pNext = m_pNext;
					//次のポインタのpPrevに自分のpPrevを代入
					m_pNext->m_pPrev = m_pPrev;
				}
				else if (m_pPrev == NULL)
				{
					m_pNext->m_pPrev = NULL;
					//自分がTopだったら次のオブジェクトがTopになる
					m_pTop[m_nPriority] = m_pNext;
				}
			}
			else if (m_pNext == NULL)
			{
				if (m_pPrev != NULL)
				{
					//次へのポインタがない時にはNULLを入れる
					m_pPrev->m_pNext = NULL;
					//次がNULLの時は自分が最後尾だから自分を破棄する前に最後尾を上書き
					m_pCur[m_nPriority] = m_pPrev;
				}
				else if (m_pPrev == NULL)
				{
					m_pCur[m_nPriority] = NULL;
					m_pTop[m_nPriority] = NULL;
				}
			}
			//破棄
			delete this;
			/**this = {};*/
		}
}

//--------------------------------------------
//オブジェクトタイプ設定処理
//--------------------------------------------
void CScene::SetObjType(OBJTYPE ObjType)
{
	m_ObjType = ObjType;
}
//--------------------------------------------
//オブジェクトタイプ取得処理
//--------------------------------------------
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_ObjType;
}

//--------------------------------------------
//優先順位の設定
//--------------------------------------------
void CScene::SetPriority(int nPriority)
{
	m_nPriority = nPriority;
}

//--------------------------------------------
//現在の先頭アドレスを返す処理
//--------------------------------------------
CScene *& CScene::GetTop(int nPriority)
{
	return m_pTop[nPriority];
}

//--------------------------------------------
//ポーズの設定処理
//--------------------------------------------
void CScene::SetbPause(bool bPause)
{
	m_bPause = bPause;
}

//--------------------------------------------
//死亡フラグ建設処理
//--------------------------------------------
void CScene::Release(void)
{
	m_pDeath = true;
}