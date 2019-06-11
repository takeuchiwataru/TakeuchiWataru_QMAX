//=============================================================================
//
// �X�R�A���� [score.h]
// Author : �|���j
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SCORE (8)				// �ő包��
#define SCORE_INTERVAL_SIZE (35)	// �X�R�A�Ԋu

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CScore : public CScene
{
public:
	CScore();
	~CScore();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//void SetScore(int nScore);
	int GetScore(void);
	void AddScore(int nValue);

	// �ÓI�����o�֐�
	static CScore * Create(D3DXVECTOR3 pos);

private:
	CNumber * m_apNumber[MAX_SCORE];
	int m_nScore;
	D3DXVECTOR3				m_pos;			// �ʒu
};
#endif