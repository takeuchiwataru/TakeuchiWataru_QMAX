//=============================================================================
//
// �^�C�g������ [title.h]
// Author : �|���j
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "input.h"
#include "player.h"
#include "sound.h"

//*********************************************************************
//�^�C�g���N���X�̒�`
//*********************************************************************
class CTitle //��{�N���X
{
public:
	CTitle();
	~CTitle();
	static CTitle *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayer *GetPlayer(void);

private:
	static CPlayer			*m_pPlayer;
	int						m_nCntTimer;
};

#endif