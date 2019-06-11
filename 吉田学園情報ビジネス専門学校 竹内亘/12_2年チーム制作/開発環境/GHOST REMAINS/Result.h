//=============================================================================
//
// ���U���g���� [Result.h]
// Author : �|���j
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "Game.h"
#include "scene.h"
#include "scene2D.h"

class CNumber;
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TIME (2)		// ���A�b
#define MAX_DATA (6)
#define MAX_RANKINGSCORE (5)
#define FILE_NAME ("data//TEXT//Stage.txt")

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CResult
{
public:
	CResult() {};
	~CResult() {};

	HRESULT Init(void);
	void	Update(void);
	void	Uninit(void);
	void	Draw(void);
	int &GetnTime(void) { return m_nTime; }
	int &GetnRankIn(void) { return m_nRankIn; }

	//�X�e�[�W�z�u���̓ǂݍ���
	void LoadObject(void);

private:
	static int m_nTime;
	static int m_nRankIn;
	int m_nTimeEnemy;
	int m_nCntEnemy;

};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CResult_UI : public CScene
{
public:
	CResult_UI() {};
	~CResult_UI() {};

	HRESULT Init(void);
	void	Update(void);
	void	Uninit(void);
	void	Draw(void);
	void	Load(void);
	void	Save(void);

private:
	CNumber *m_pNumber[MAX_TIME];
	int m_aData[MAX_DATA];
};

#endif
