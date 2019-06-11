//=============================================================================
//
// マネージャー処理 [manager.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "input.h"
#include "sound.h"
#include "light.h"
#include "camera.h"
#include "debugproc.h"
#include "sceneX.h"
#include "scene3D.h"
#include "meshField.h"
#include "ranking.h"

//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CTitle;
class CGame;
class CResult;
class CFade;
class CRanking;
class CTutorial;
class CGameover;
//*****************************************************************************
// ファイル読み込み用
//*****************************************************************************
#define MAX_MODEL		(30)
#define MAX_SOUND		(3)
//*********************************************************************
//マネージャークラスの定義
//*********************************************************************
class CManager //基本クラス
{
public:
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_GAMEOVER,
		MODE_RANKING,
		MODE_MAX
	}MODE;

	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFade *GetFade(void);
	static void SetMode(MODE mode);
	static MODE GetMode(void);

	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static CInputJoypad *GetCInputJoypad(void);
	static CSound *GetSound(int nNum);

	static CCamera *GetCamera(void);
	static CLight *GetLight(void);

	static CScene3D *GetScene3D(void);
	static CSceneMeshField *GetSceneMeshField(void);

	static void RankingScore(int nScore);
	static int *GetRankingScore(int nidx);
	static void SetGameScore(int nScore);
	static int *GetGameScore();

	static int *GetGameItem();
	static int *GetGameTime();


#ifdef _DEBUG
	static void CreateSceneDebug(void);
#endif
	//メンバ変数
private:
	static CRenderer		*m_pRenderer;			// レンダラーのポインタ
	static CInputKeyboard	*m_pInput;				// インプットのポインタ
	static CInputJoypad		*m_pInputJoypad;		// ジョイパッドのポインタ
	static CSound			*m_pSound[MAX_SOUND];	// サウンドのポインタ
	static CScene3D			*m_Scene3D;
	static CSceneMeshField	*m_MeshField;

	int		m_nNumModel;
	char	m_aFileNameModel[MAX_MODEL][256];
	static	LPD3DXMESH			m_pMeshModel[MAX_MODEL];		//メッシュ情報へのポインタ
	static	LPD3DXBUFFER		m_pBuffMatModel[MAX_MODEL];		//マテリアル情報へのポインタ
	static	LPDIRECT3DTEXTURE9	m_pTextureModel[MAX_MODEL];		//テクスチャへのポインタ
	static	DWORD				m_nNumMatModel[MAX_MODEL];		//マテリアル情報の数

	static int				m_nScore[MAX_RANKING];
	static int				m_nGameScore;
	static int				m_nItemNum;
	static int				m_nTime;

	static CTitle			*m_pTitle;
	static CTutorial		*m_pTutorial;
	static CGame			*m_pGame;
	static CResult			*m_pResult;
	static CGameover		*m_pGameover;
	static CRanking			*m_pRanking;

	static MODE				m_mode;
	static CFade			*m_pFade;

	static CCamera			*m_pCamera;		// カメラのポインタ
	static CLight			*m_pLight;		// ライトのポインタ

	static int				m_nTitle;
public:
	static CDebugProc	*m_pDebugProc;

};

#endif