//=============================================================================
//
// ���U���g���� [result.h]
// Author : �|���j
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CResult
{
public:
	CResult();
	~CResult();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static CResult * m_pResult;
};

#endif