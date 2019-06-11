//=============================================================================
//
// �����L���O���� [Ranking.h]
// Author : �|���j
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#include "Game.h"
#include "scene.h"
#include "scene2D.h"

class CNumber;
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_RANKING (5)		// �����L���O�̍ő吔
#define MAX_TIME (2)		// ���A�b

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CRanking
{
public:
	CRanking() {};
	~CRanking() {};

	HRESULT Init(void);
	void	Update(void);
	void	Uninit(void);
	void	Draw(void);

	//�X�e�[�W�z�u���̓ǂݍ���
	void LoadObject(void);

private:
	float m_fCntState;
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CRanking_UI : public CScene
{
public:
	CRanking_UI() {};
	~CRanking_UI() {};

	HRESULT Init(void);
	void	Update(void);
	void	Uninit(void);
	void	Draw(void);

private:
	CNumber *m_apNumber[MAX_RANKING][MAX_TIME];
};

#endif
