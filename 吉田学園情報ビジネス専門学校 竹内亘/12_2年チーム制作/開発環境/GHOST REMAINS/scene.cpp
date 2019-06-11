//=============================================================================
//
// レンダリング処理 [renderer.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "SceneModel.h"
#include "Font.h"
#include "motion.h"

#include "2DPolygon.h"
#include "2DGage.h"
#include "3DPolygon.h"

#include "collision.h"
#include "renderer.h"
#include "camera.h"
#include "light.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CScene	*CScene::m_pTop[MAX_SCENE] = {};					// 現在の描画状態
CScene	*CScene::m_pCur[MAX_SCENE] = {};					// 現在の描画状態
int		CScene::m_nNumAll[MAX_SCENE] = {0, 0, 0, 0, 0, 0, 0, 0};	// 生成数
int		CScene::m_nDraw = 0;					// 現在の描画状態
int		CScene::m_nCntStart = 0;				// 現在の描画状態
bool	CScene::m_bPause = false;				//ポーズの有無
LPDIRECT3DTEXTURE9	CScene::m_pTexture[TEX_MAX] = {};		// テクスチャへのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CScene::CScene(int nPrioryity)
{
	//前に今のオブジェを入れる
	if (m_pCur[nPrioryity] != NULL) { m_pCur[nPrioryity]->GetpNext() = this; }	//前がいる
	else							{ m_pTop[nPrioryity] = this; }				//自分先頭
	
	//今に前のオブジェを入れる
	m_pPrev = m_pCur[nPrioryity];
	m_pNext = NULL;

	//今にこのオブジェを入れる
	m_pCur[nPrioryity] = this;
	m_nPriority = nPrioryity;
	m_nNumAll[nPrioryity]++;

	//何にも部類されないオブジェタイプに
	SetObjType(OBJTYPE_NONE);
	m_bDeath = false;
}
//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene(void) {}

//=============================================================================
// 画像の読み込み
//=============================================================================
LPDIRECT3DTEXTURE9	&CScene::Load(TEXTURE tex)
{
	if (tex < TEX_MAX)
	{//範囲確認
		if (m_pTexture[tex] == NULL)
		{//読み込んでないなら
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			switch (tex)
			{//読み込み 
			case TEX_Title:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/TITLE/title.png", &m_pTexture[tex]);		break;
			case TEX_TUTORIAL:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/TUTORIAL/tutorial01.png", &m_pTexture[tex]);		break;
			case TEX_Wall:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/DUNGEON/Wall.jpg", &m_pTexture[tex]);	break; 
			case TEX_Field:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/DUNGEON/lava.jpg", &m_pTexture[tex]);	break;
			case TEX_Fence:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/fence.jpg", &m_pTexture[tex]);		break;
			case TEX_Stone:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/998_stone_.jpg", &m_pTexture[tex]);	break;
			case TEX_Steel:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/Steel000.jpg", &m_pTexture[tex]);		break; 
			case TEX_Brock:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/brick.jpg", &m_pTexture[tex]);		break;
			case TEX_DBlock:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/stone_1.jpg", &m_pTexture[tex]);		break;
			case TEX_MBlock:	D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/stone_0.jpg", &m_pTexture[tex]);		break;
			case TEX_Spear:		D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/Spear000.jpg", &m_pTexture[tex]);		break;
			case TEX_Fire:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/GAME/pipo-btleffect024.png", &m_pTexture[tex]);		break;
			case TEX_Button:    D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/button.jpg", &m_pTexture[tex]);		break;
			case TEX_DropStone: D3DXCreateTextureFromFile(pD3DDevice, "data/MODEL/TEXTURE/DropStone.jpg", &m_pTexture[tex]);	break;
			case TEX_Shadow: D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/GAME/shadow000.jpg", &m_pTexture[tex]);	break;
				
			case TEX_ResaltLogo:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/RESULT/resultlogo.png", &m_pTexture[tex]);			break;
			case TEX_RankingLogo:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/RANKING/rankinglogo.png", &m_pTexture[tex]);		break;
			case TEX_RankingRank:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/RANKING/ranking_rank.png", &m_pTexture[tex]);		break;
			case TEX_RankingMinute:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/minute.png", &m_pTexture[tex]);			break;
			case TEX_RankingSecond:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/second.png", &m_pTexture[tex]);			break;
			case TEX_PressEnter:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/pressenter.png", &m_pTexture[tex]);			break; 
			case TEX_Number:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/number000.png", &m_pTexture[tex]);			break;
			case TEX_Pause:			D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/pause.png", &m_pTexture[tex]);			break;
			case TEX_TutorialLogo:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/TUTORIAL/tutorial.png", &m_pTexture[tex]);			break;
			}
		}
		return m_pTexture[tex];
	}
	return m_pTexture[0];
}
//=============================================================================
// 画像の解放
//=============================================================================
void	CScene::UnLoad(void)
{
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{//全画像破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//==================================================================================================//
//    * 全解放関数 *
//==================================================================================================//
void CScene::ReleaseAll(void)
{
	CSceneModel::UnLoadModel();	//Modelの削除
	CCharacter::UnLoad();		//キャラパーツの削除
	CMotion::UnLoad();			//モーションの削除
	CFont::UnLoad();			//文字の終了
	UnLoad();

	BreakObject();

	//if (CManager::GetCamera() != NULL) { CManager::GetCamera()->Uninit(); }
	//if (CManager::GetLight() != NULL) { CManager::GetLight()->Uninit(); }

}

//=============================================================================
// 更新処理
//=============================================================================
void  CScene::UpdateAll(void)
{
	CScene *pScene = NULL;
	CScene *pNext = NULL;

	//生成数表示
	CManager::GetDLog()->Update();
	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "生成数\n 零：%d,  壱：%d,  弐：%d,  参：%d,  四：%d,  伍：%d,  六：%d,  七：%d\n"
		, m_nNumAll[0], m_nNumAll[1], m_nNumAll[2], m_nNumAll[3], m_nNumAll[4], m_nNumAll[5], m_nNumAll[6], m_nNumAll[7]);

	for (int nCntScene = (m_bPause ? MAX_SCENE - 1 : m_nCntStart); nCntScene < MAX_SCENE; nCntScene++)
	{//優先順位分回る
		pScene = m_pTop[nCntScene];
			while (pScene != NULL)
			{//NULLになるまで繰り返す
				pNext = pScene->GetpNext();	//Update中に消える可能性があるから
				if (!pScene->m_bDeath) { pScene->Update(); }
				pScene = pNext;
			}
	}
	CCollision::CollisionAll();
}
//=============================================================================
// 描画処理
//=============================================================================
void  CScene::DrawAll(LPDIRECT3DDEVICE9 &pDevice)
{
	CScene *pScene = NULL;
	CScene *pNext = NULL;
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{//優先順位分回る
		pScene = m_pTop[nCntScene];
		while (pScene != NULL)
		{//NULLになるまで繰り返す
			pNext = pScene->GetpNext();	//Draw中に消えるかもしれないから
			pScene->Draw();
			pScene = pNext;
		}
	}
}
//==================================================================================================//
//    * 終了関数 *
//==================================================================================================//
void	CScene::UninitAll(void)
{
	CScene *pScene = NULL;
	CScene *pNext = NULL;
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{//優先順位分回る
		pScene = m_pTop[nCntScene];
		while (pScene != NULL)
		{//NULLになるまで繰り返す
			pNext = pScene->GetpNext();	//Draw中に消えるかもしれないから
			if (pScene->m_bDeath) { pScene->Release(); }
			pScene = pNext;
		}
	}
}
//==================================================================================================//
//    * 描画準備関数 *
//==================================================================================================//
bool CScene::DrawPrepare(CScene::DRAW_TYPE DrawType, LPDIRECT3DDEVICE9 &pD3DDevice)
{
	if (DrawType == DRAW_TYPE_NO) { return true; }

	if (m_nDraw / 10 != DrawType / 10)
	{//現在のZテストと描画方法が違うなら
		if (DrawType >= CScene::DRAW_TYPE_ZNORMAL)
		{// Zテスト解除
			pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		}
		else
		{// Zテスト始動
			pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
		}
	}
	if (m_nDraw % 10 != DrawType % 10)
	{//現在の合成方法が違うなら
		switch (DrawType % 10)
		{//ほんとは3行あることを忘れてはいけない...
		case CScene::DRAW_TYPE_NORMAL:// 通常
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			break;
		case CScene::DRAW_TYPE_ADD:// αブレンディングを加算合成に設定
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
		case CScene::DRAW_TYPE_SUBTRACT:// 減算
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
		case CScene::DRAW_TYPE_MULTIPLY:
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO | D3DBLEND_ONE);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTCOLOR);
			break;
		case CScene::DRAW_TYPE_OVERLAY:
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO | D3DBLEND_ONE);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
		}
	}
	m_nDraw = DrawType;	//描画方法の代入

	return false;
}
//==================================================================================================//
//    * 自分削除関数 *
//==================================================================================================//
void CScene::Release()
{
	//前のやつに自分の次を託す
	if (m_pPrev != NULL) { m_pPrev->GetpNext() = m_pNext; }	//遺言書
	else				 { m_pTop[m_nPriority] = m_pNext; }	//先頭交代

	//次のやつに自分が消えたことを伝える
	if (m_pNext != NULL) { m_pNext->GetpPrev() = m_pPrev; }	//次と前をつなげる
	else				 { m_pCur[m_nPriority] = m_pPrev; } //最後尾交代

	//自分の削除
	m_nNumAll[m_nPriority]--;
	delete this;
}
//=============================================================================
//	全オブジェクトを破壊
//=============================================================================
void CScene::BreakObject(void)
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{//優先順位分回る
		while (m_pTop[nCntScene] != NULL)
		{//NULLになるまで繰り返す
			m_pTop[nCntScene]->Uninit();
			m_pTop[nCntScene]->Release();
		}
	}
}
//=============================================================================
//	指定したオブジェクトを破壊
//=============================================================================
void CScene::BreakObject(OBJTYPE obj)
{
	CScene *pNext = NULL;
	CScene *pTarget = NULL;
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{//優先順位分回る
		pNext = m_pTop[nCntScene];
		while (pNext != NULL)
		{//NULLになるまで繰り返す
			pTarget = pNext;
			pNext = pNext->GetpNext();

			if (pTarget->GetObjType() == obj)
			{//オブジェタイプがかぶっているなら削除
				pTarget->Uninit();
				pTarget->SetObjType(OBJTYPE_NONE);
			}
		}
	}
}
//=============================================================================
// シーンを返す
//=============================================================================
CScene *CScene::GetTop(int nPrioryity)
{
	return m_pTop[nPrioryity];
}

