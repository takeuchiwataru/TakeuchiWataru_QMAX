//=============================================================================
//
// ���U���g���� [result.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "input.h"
#include "player.h"
#include "sound.h"

//*********************************************************************
//���U���g�N���X�̒�`
//*********************************************************************
class CResult //��{�N���X
{
public:
	CResult();
	~CResult();
	static CResult *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//�����o�ϐ�
private:
	int						m_nCntTimer;
};

#endif