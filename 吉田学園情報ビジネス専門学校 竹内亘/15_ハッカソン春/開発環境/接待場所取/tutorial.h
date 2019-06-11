//=============================================================================
//
// �`���[�g���A������ [tutorial.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "input.h"
#include "player.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TUTORIALBG			(3)			//�w�i�̐�

//*********************************************************************
//�`���[�g���A���N���X�̒�`
//*********************************************************************
class CTutorial //��{�N���X
{
public:
	CTutorial();
	~CTutorial();
	static CTutorial *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);

	static CPlayer *GetPlayer(void);
	//�����o�ϐ�
private:
	int							m_nType;
	static CPlayer				*m_pPlayer;
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_TUTORIALBG];			// �e�N�X�`���|�C���^
};

#endif