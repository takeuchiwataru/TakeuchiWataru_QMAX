//=============================================================================
//
// �}�l�[�W���[���� [manager.h]
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

//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CTitle;
class CGame;
class CResult;
class CFade;
class CRanking;
class CTutorial;
class CGameover;

class CDirectInput;
//*****************************************************************************
// �t�@�C���ǂݍ��ݗp
//*****************************************************************************
#define MAX_MODEL		(30)
#define MAX_RANKING		(5)		// �j�ǉ�

//*********************************************************************
//�}�l�[�W���[�N���X�̒�`
//*********************************************************************
class CManager //��{�N���X
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
	static CSound *GetSound(void);

	static CScene3D *GetScene3D(void);
	static CSceneMeshField *GetSceneMeshField(void);

	static CDirectInput *GetJoypad(void);

	// �j�ǉ�
	static int GetRanking(int index);
	static void GetRankingScore(int nScore);

	//�t�@�C���ǂݍ��݊֐�
	void FileLoad(void);						//�t�@�C���ǂݍ���
	char *ReadLine(FILE *pFile, char *pDst);	//1�s�ǂݍ���
	char *GetLineTop(char *pStr);				//�s�̐擪���擾
	int  PopString(char *pStr, char *pDest);	//�s�̍Ō��؂�̂�

#ifdef _DEBUG
	static void CreateSceneDebug(void);
#endif
	//�����o�ϐ�
private:
	static CRenderer *m_pRenderer;		// �����_���[�̃|�C���^
	static CInputKeyboard *m_pInput;	// �C���v�b�g�̃|�C���^
	static CSound		*m_pSound;		// �T�E���h�̃|�C���^
	static CScene3D			*m_Scene3D;
	static CSceneMeshField	*m_MeshField;

	int		m_nNumModel;
	char	m_aFileNameModel[MAX_MODEL][256];
	static	LPD3DXMESH			m_pMeshModel[MAX_MODEL];		//���b�V�����ւ̃|�C���^
	static	LPD3DXBUFFER		m_pBuffMatModel[MAX_MODEL];		//�}�e���A�����ւ̃|�C���^
	static	LPDIRECT3DTEXTURE9	m_pTextureModel[MAX_MODEL];		//�e�N�X�`���ւ̃|�C���^
	static	DWORD				m_nNumMatModel[MAX_MODEL];		//�}�e���A�����̐�

	static int				m_nScore[5];
	static int				m_nGameScore;

	static CTitle			*m_pTitle;
	static CTutorial		*m_pTutorial;
	static CGame			*m_pGame;
	static CResult			*m_pResult;
	static CGameover		*m_pGameover;
	static CRanking			*m_pRanking;

	static MODE				m_mode;
	static CFade			*m_pFade;
	static CDirectInput		*m_pJoyPad;
	static int m_aScore[MAX_RANKING];		//	�j�ǉ�
public:
	static CDebugProc	*m_pDebugProc;

};

#endif