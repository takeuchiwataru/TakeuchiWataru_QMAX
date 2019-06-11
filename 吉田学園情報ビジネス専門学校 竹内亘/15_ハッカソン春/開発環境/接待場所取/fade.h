//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "manager.h"
//*****************************************************************************
//�@�O���錾
//*****************************************************************************

//*********************************************************************
//�t�F�[�h�N���X�̒�`
//*********************************************************************
class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,		// �������Ă��Ȃ����
		FADE_IN,			// �t�F�[�h�C�����
		FADE_OUT,			// �t�F�[�h�A�E�g���
		FADE_MAX
	} FADE;

	CFade(int nPriority = 7);
	~CFade();
	static CFade *Create(CManager::MODE modeNext);
	void Init(CManager::MODE modeNext);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetFade(CManager::MODE modeNext);
	static FADE GetFade(void);
	static void SetFadeINOUT(FADE fade, bool bNextMode);

	//�����o�ϐ�
private:
	static LPDIRECT3DTEXTURE9				m_pTextureFade;		// �e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DVERTEXBUFFER9			m_pVtxBuffFade;		// ���_�o�b�t�@�ւ̃|�C���^
	static FADE								m_fade;				// �t�F�[�h���
	static CManager::MODE					m_modeNext;			// ���̃��[�h
	static D3DXCOLOR						m_color;			// �t�F�[�h�F
	static bool								m_bNextMode;
};

#endif