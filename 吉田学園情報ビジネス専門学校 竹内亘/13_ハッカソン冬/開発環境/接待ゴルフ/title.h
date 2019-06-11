//=============================================================================
//
// �^�C�g������ [title.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "input.h"
#include "player.h"
#include "sound.h"
//#include "score.h"
//#include "gold.h"
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

private:
	int						m_nCntTimer;

};

#endif