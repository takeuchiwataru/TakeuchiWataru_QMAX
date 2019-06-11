//=============================================================================
//
// �����L���O�X�R�A���� [rankingscore.h]
// Author : �|���j
//
//=============================================================================
#ifndef _RANKINGSCORE_H_
#define _RANKINGSCORE_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_RANKINGSCORE (8)		// �ő包��
#define SCORE_INTERVAL_SIZE_X (80)	// �X�R�A�ԊuX
#define SCORE_INTERVAL_SIZE_Y (110)	// �X�R�A�ԊuY
#define MAX_RANKING (5)				// �����L���O��

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CRankingScore : public CScene
{
public:
	typedef enum
	{//�����L���O�X�R�A�̏��
		RANKINGSCORESTATE_NONE = 0, // �X�V����Ă��Ȃ����
		RANKINGSCORESTATE_UPDATE,   // �X�V���ꂽ���
		RANKINGSCORESTATE_MAX
	}RANKINGSCORESTATE;

	CRankingScore();
	~CRankingScore();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetRankingScore(int nScore);

	// �ÓI�����o�֐�
	static CRankingScore * Create(D3DXVECTOR3 pos);

private:
	static CNumber * m_apNumber[MAX_RANKINGSCORE][MAX_RANKING];
	int m_nRankingScore;					// �X�R�A
	D3DXVECTOR3				m_pos;			// �ʒu

	D3DXCOLOR m_aCol[MAX_RANKING];			// �F
	RANKINGSCORESTATE m_State[MAX_RANKING];	// ���
	int m_CounterCol;						// �F��؂�ւ���^�C�~���O


};
#endif