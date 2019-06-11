//=============================================================================
//
// �^�C������ [UITime.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _UITIME_H_
#define _UITIME_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CNumber;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TIME	(3)		// �^�C���̌���

//*********************************************************************
//�^�C���N���X�̒�`
//*********************************************************************
class CTime : public CScene //�h���N���X
{
public:
	CTime(int nPriority = 6);
	~CTime();
	static CTime *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);		//�^�C������
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTime(int nTime);
	void AddTime(int nValue);
	int GetTime();
	void SetColor(D3DXCOLOR col);

private:
	//�����o�ϐ�
	CNumber			*m_apNumber[MAX_TIME];
	D3DXVECTOR3		m_pos;
	float			m_fLength;
	float			m_fWidth, m_fHeight;	// ������
	int				m_nTime;				// ��������
	int				m_nTimerCnt;			// �^�C�}�[�p�J�E���g
	int				m_nColorFlash;			// �_�ŃJ�E���g
	int				m_nFadeCnt;				// �t�F�[�h�܂ł̃J�E���g
};

#endif