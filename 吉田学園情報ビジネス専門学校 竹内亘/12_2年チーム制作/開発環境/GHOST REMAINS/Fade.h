//=============================================================================
//
// 2DPolygon���� [2DPolygon.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "2DPolygon.h"
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CFade
{
public:
	typedef enum
	{
		TEX_GAGE,
		TEXTURE_MAX
	}TEXTURE;
	typedef enum
	{
		STATE_OUT,		//exe�n�܂�̃t�F�[�h
		STATE_NOR_FADE,	//�ʏ�t�F�[�h
		STATE_FADE_NONE,
		STATE_FADE_NOW,
		STATE_MAX
	}STATE;


	CFade() { m_p2DFade = NULL; };
	~CFade() {};

	void	Set(void);

	HRESULT Init(STATE state);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);
	static	LPDIRECT3DTEXTURE9	*Load(TEXTURE tex);	//�e�N�X�`���̐���
	static void					UnLoad(void);	//�e�N�X�`���̔j��

	STATE &GetState(void) { return m_state; }
protected://*****************************************************************************
		  //�ϐ��錾//***********************************************************************
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTURE_MAX];		// �e�N�X�`���ւ̃|�C���^
private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	STATE		m_state;
	C2DPolygon	*m_p2DFade;
};

#endif