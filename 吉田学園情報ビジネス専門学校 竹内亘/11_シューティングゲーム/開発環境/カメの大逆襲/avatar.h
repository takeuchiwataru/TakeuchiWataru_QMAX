//=============================================================================
//
// �A�o�^�[���� [avatar.h]
// Author : �|���j
//
//=============================================================================
#ifndef _AVATAR_H_
#define _AVATAR_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define AVATAR_SIZE (35)

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CAvatar : public CScene2D
{// �h�������鎞�� : public �`�����ɂ��Ă��
public:
	typedef enum
	{// �v���C���[�̎��
		AVATARTYPE_000 = 0,
		AVATARTYPE_001,
		AVATARTYPE_MAX,
	}AVATARTYPE;

	CAvatar();
	~CAvatar();
	HRESULT Init(D3DXVECTOR3 pos, AVATARTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	// �ÓI�����o�֐�
	static CAvatar * Create(D3DXVECTOR3 pos, AVATARTYPE type);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[AVATARTYPE_MAX];	// ���L�e�N�X�`���̃|�C���^
	AVATARTYPE m_nType;				// �A�o�^�[�̎��
	int m_nSpeed;					// �X�s�[�h
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
};

#endif
