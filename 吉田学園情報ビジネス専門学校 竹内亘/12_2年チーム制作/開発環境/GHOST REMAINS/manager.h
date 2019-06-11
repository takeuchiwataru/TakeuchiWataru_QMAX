//=============================================================================
//
// �}�l�[�W���[���� [Manager.h]
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
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X�̒�`
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
		//�ϐ��錾//***********************************************************************
	static CRenderer		*m_pRenderer;
	static CInputKeyboard	*m_pInputKey;
	static CInputJoyPad		*m_pJoyPad[JOYPAD_MAX];
	//static CScenePlayer		*m_pPlayer[MAX_PLAYER];
	static CCamera			*m_pCamera;		//�J����
	static CLight			*m_pLight;		//���C�g
	static CSpotLight		*m_pSpotLight;	//�X�|�b�g���C�g

	static CDebugLog		*m_pDebugLog;	//�f�o�b�N���O
	static MODE				m_mode;			//���[�h
	static MODE				m_NextMode;		//���̃��[�h
	static CFade			m_Fade;			//�t�F�[�h�{��
	static CSound			*m_pSound;		// �T�E���h�N���X�̃|�C���^
	static int				m_nEndCount;	//�t�F�[�h�܂ł̃J�E���g

	static CTitle			*m_pTitle;		//�^�C�g������
	static CSelect			*m_pSelect;		//�Z���N�g����
	static CGame			*m_pGame;		//�Q�[������
	static CPractice		*m_pPractice;	//���K����
	static CRanking			*m_pRanking;			//���K
	static CResult			*m_pResult;			//���K
	static int				nCntTime;		//���ԃJ�E���g

	static CPlayer			*pPlayer;		//�v���C���[�̃|�C���^
};

#endif
