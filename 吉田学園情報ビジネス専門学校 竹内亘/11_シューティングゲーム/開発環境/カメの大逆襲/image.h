//=============================================================================
//
// �摜���� [image.cpp]
// Author : �|���j
//
//=============================================================================
#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// �摜�N���X�̒�`
//*****************************************************************************
class CImage : public CLogo
{
public:
	typedef enum
	{// �t���[���̎��
		IMAGE_REMAIN000,
		IMAGE_REMAIN001,
		IMAGE_TUTORIAL,
		IMAGE_TUTORIAL002,
		IMAGE_MAX,
	}IMAGE;

	CImage();
	~CImage();
	HRESULT Init(D3DXVECTOR3 pos, IMAGE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CImage * Create(D3DXVECTOR3 pos, IMAGE type);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[IMAGE_MAX];	// ���L�e�N�X�`���̃|�C���^
	IMAGE m_nType;										// ���U���g�̎��
};

#endif
