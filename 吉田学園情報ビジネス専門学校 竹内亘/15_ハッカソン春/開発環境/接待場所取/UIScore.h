//=============================================================================
//
// �X�R�A���� [score.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _UISCORE_H_
#define _UISCORE_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CNumber;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SCORE	(6)		// �X�R�A�̌���

//*********************************************************************
//�X�R�A�N���X�̒�`
//*********************************************************************
class CScore : public CScene //�h���N���X
{
public:
	CScore(int nPriority = 6);
	~CScore();
	static CScore *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);		//�X�R�A����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetScore(int nScore);
	void AddScore(int nValue);
	int GetScore();
	void SetColor(D3DXCOLOR col);

private:
	//�����o�ϐ�
	CNumber			*m_apNumber[MAX_SCORE];
	D3DXVECTOR3		m_pos;
	float			m_fLength;
	float			m_fWidth, m_fHeight;	// ������

	int				m_nScore;
};

#endif