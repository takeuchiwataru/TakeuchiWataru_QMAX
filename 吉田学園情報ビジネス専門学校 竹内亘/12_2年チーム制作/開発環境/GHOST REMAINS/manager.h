//=============================================================================
//
// マネージャー処理 [Manager.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "input.h"
#include "Fade.h"
#include "DebugLog.h"
class CSound;
class CTitle;
class CGame;
class CSelect;
class CPractice;
class CCamera;
class CPlayer;
class CLight;
class CSpotLight;
class CRanking;
class CResult;
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CManager
{
public:
	typedef enum
	{
		MODE_TITLE,
		MODE_SELECT,
		MODE_PRACTICE,
		MODE_GAME,
		MODE_RESULT,
		MODE_RANKING,
		MODE_MAX
	}MODE;

	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);
	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CInputKeyboard *GetInputKey(void) { return m_pInputKey; }
	static CInputJoyPad *&GetInputJoyPad(int nID) { return m_pJoyPad[nID]; }
	//static CScenePlayer *&GetPlayer(int nID)	{ return m_pPlayer[nID]; }
	//static CScenePlayer *&GetRandPlayer(void);
	//static CScenePlayer *&GetNearPlayer(D3DXVECTOR3 pos);
	//static CScenePlayer *&GetNearPlayer(D3DXVECTOR3 pos, float &fDistance);

	static void SetFade(MODE mode, int nEndCount);
	static void SetMode(void);
	static CDebugLog *&GetDLog(void) { return m_pDebugLog; }
	static MODE &GetMode(void) { return m_mode; }
	static CFade &GetFade(void) { return m_Fade; }
	static int	&GetEndCount(void) { return m_nEndCount; }
	static CSound *&GetSound(void) { return m_pSound; }
	static CGame *&GetGame(void) { return m_pGame; }
	static CCamera *&GetCamera(void) { return m_pCamera; }
	static CLight *&GetLight(void) { return m_pLight; }
	static CSpotLight *&GetpSpotLight(void) { return m_pSpotLight; }

	static CPlayer *&GetPlayer(void) { return pPlayer; }
	static CResult *&GetResult(void) { return m_pResult; }

private://*****************************************************************************
		//変数宣言//***********************************************************************
	static CRenderer		*m_pRenderer;
	static CInputKeyboard	*m_pInputKey;
	static CInputJoyPad		*m_pJoyPad[JOYPAD_MAX];
	//static CScenePlayer		*m_pPlayer[MAX_PLAYER];
	static CCamera			*m_pCamera;		//カメラ
	static CLight			*m_pLight;		//ライト
	static CSpotLight		*m_pSpotLight;	//スポットライト

	static CDebugLog		*m_pDebugLog;	//デバックログ
	static MODE				m_mode;			//モード
	static MODE				m_NextMode;		//次のモード
	static CFade			m_Fade;			//フェード本体
	static CSound			*m_pSound;		// サウンドクラスのポインタ
	static int				m_nEndCount;	//フェードまでのカウント

	static CTitle			*m_pTitle;		//タイトル処理
	static CSelect			*m_pSelect;		//セレクト処理
	static CGame			*m_pGame;		//ゲーム処理
	static CPractice		*m_pPractice;	//練習処理
	static CRanking			*m_pRanking;			//練習
	static CResult			*m_pResult;			//練習
	static int				nCntTime;		//時間カウント

	static CPlayer			*pPlayer;		//プレイヤーのポインタ
};

#endif
