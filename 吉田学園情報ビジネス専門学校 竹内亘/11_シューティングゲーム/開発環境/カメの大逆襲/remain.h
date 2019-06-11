//=============================================================================
//
// �c�@���� [remain.h]
// Author : �|���j
//
//=============================================================================
#ifndef _REMAIN_H_
#define _REMAIN_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_REMAIN (2)				// �ő包��
#define REMAIN_INTERVAL_SIZE (35)	// �X�R�A�Ԋu

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CRemain : public CScene
{
public:
	CRemain();
	~CRemain();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//void SetScore(int nScore);
	//int GetRemain(void);

	// �ÓI�����o�֐�
	static CRemain * Create(D3DXVECTOR3 pos);
	void AddRemain(int nValue);


private:
	CNumber * m_apNumber[MAX_REMAIN];
	int m_nRemain;
	D3DXVECTOR3	m_pos;			// �ʒu

};
#endif