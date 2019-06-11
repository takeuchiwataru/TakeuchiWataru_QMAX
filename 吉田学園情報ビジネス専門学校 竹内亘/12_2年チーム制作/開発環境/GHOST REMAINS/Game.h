//=============================================================================
//
// �Q�[������ [Game.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
#define MAX_GAME_PAUSE		(5)
#define GAME_PAUSE_INTERVAL	(100.0f)
#define GAME_PAUSE_LOGOX	(150.0f)
#define GAME_PAUSE_LOGOY	(50.0f)


//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CGame
{
public:
	typedef enum
	{
		STATE_NONE,		//�ʏ�
		STATE_CLEAR,	//�N���A
		STATE_OVER,		//�Q�[���I�[�o�[
		STATE_MAX
	}STATE;
	CGame()		{ for (int nCount = 0; nCount < MAX_GAME_PAUSE; nCount++) { m_pScene2D[nCount] = NULL; } };
	~CGame()	{};

	HRESULT Init(void);
	void	Update(void);
	void	Uninit(void);
	void	SetState(STATE state);
	void	Pause(void);
	STATE	&GetState(void) { return m_state; }

	static bool &GetbDuo(void) { return m_bDuo; }

private://*****************************************************************************
	void LoadObject(void);
		//�ϐ��錾//***********************************************************************
	static	bool	m_bDuo;	//2�l�v���C���ǂ���
	STATE	m_state;
	int		m_nCntTime;
	float	m_fCntState;
	int		m_nSelect;
	CScene2D *m_pScene2D[MAX_GAME_PAUSE];
};

#endif
