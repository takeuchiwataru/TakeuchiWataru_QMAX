//=============================================================================
//
// �����֌W���� [Number.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _2DNUMBER_H_
#define _2DNUMBER_H_

#include "main.h"
#include "2DPolygon.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUMBER_UV_X		(10)
#define NUMBER_UV_Y		(1)

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CNumber
{
public:
	typedef enum
	{
		STATE_SCORE = 0,	//�S�Ă��̂܂ܕ\��
		STATE_STATUS,		//�ő吔����̌��͓�����
		STATE_RANKING,
		STATE_TIMER,
		STATE_MAX
	}STATE;

	CNumber() {};
	~CNumber() {};

	void	Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, int nScore, int nDigits, D3DXCOLOR col, STATE state);	//�X�R�A(����)��TEXTURE
	void	SetNumber(int nScore);
	void	AddNumber(int nValue);
	void	SetColor(D3DXCOLOR col);
	int		&GetnNumber(void) { return m_nNumber; }
	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
protected://*****************************************************************************
		  //�ϐ��錾//***********************************************************************
private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	STATE	m_state;		//�\���`��
	int		m_nNumber;		//���l
	int		m_nNum2D;		//�ő包��
	float m_fCntState;
	C2D		**m_p2D;		//�����̃|�C���^
};

#endif
