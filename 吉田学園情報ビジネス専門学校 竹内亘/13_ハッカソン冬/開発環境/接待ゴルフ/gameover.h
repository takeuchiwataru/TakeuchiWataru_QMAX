//=============================================================================
//
// �Q�[���I�[�o�[���� [gameover.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

#include "main.h"
#include "input.h"
#include "player.h"
#include "sound.h"

//*********************************************************************
//�`���[�g���A���N���X�̒�`
//*********************************************************************
class CGameover //��{�N���X
{
public:
	CGameover();
	~CGameover();
	static CGameover *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//�����o�ϐ�
private:
	int						m_nCntTimer;

};

#endif