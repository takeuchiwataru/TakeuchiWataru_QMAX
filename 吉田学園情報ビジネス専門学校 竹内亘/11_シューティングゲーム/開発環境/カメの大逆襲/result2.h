//=============================================================================
//
// ���U���g���� [result2.h]
// Author : �|���j
//
//=============================================================================
#ifndef _RESULT2_H_
#define _RESULT2_H_

#include "main.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CResult2
{
public:
	CResult2();
	~CResult2();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static CResult2 * m_pResult;
};

#endif