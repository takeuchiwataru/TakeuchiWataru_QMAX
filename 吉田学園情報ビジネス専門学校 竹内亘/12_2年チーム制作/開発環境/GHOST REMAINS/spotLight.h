//=============================================================================
//
// �X�|�b�g���C�g���� [spotLight.h]
// Author : ���R���
//
//=============================================================================
#ifndef _SPOTLIGHT_H_
#define _SPOTLIGHT_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TITLE_LIGHT (5)

//========================================
// �N���X�̒�`
//========================================
//=====================
// ���C�g�N���X
//=====================
class CSpotLight
{
public:
	CSpotLight();		// �R���X�g���N�^
	~CSpotLight();		// �f�X�g���N�^

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Set(void);

private:
	static D3DLIGHT9 m_light[MAX_TITLE_LIGHT];	// ���C�g�̏��
	D3DXVECTOR3 m_pos;
	int m_nCntTime;
	bool m_bLight;
	int m_nCountLighting;
};

#endif
