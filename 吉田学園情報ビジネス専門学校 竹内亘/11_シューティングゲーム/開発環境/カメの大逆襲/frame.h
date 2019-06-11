//=============================================================================
//
// �t���[������ [logo.cpp]
// Author : �|���j
//
//=============================================================================
#ifndef _FRAME_H_
#define _FRAME_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// �t���[���N���X�̒�`
//*****************************************************************************
class CFrame : public CLogo
{
public:
	typedef enum
	{// �t���[���̎��
		FRAME_LIFE,
		FRAME_SCORE,
		FRAME_MAX,
	}FRAME;

	CFrame();
	~CFrame();
	HRESULT Init(D3DXVECTOR3 pos, FRAME type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CFrame * Create(D3DXVECTOR3 pos, FRAME type);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[FRAME_MAX];	// ���L�e�N�X�`���̃|�C���^
	FRAME m_nType;										// ���U���g�̎��
};

#endif
