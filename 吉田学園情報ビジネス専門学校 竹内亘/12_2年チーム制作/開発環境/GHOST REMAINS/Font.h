//=============================================================================
//
// 2DPolygon���� [2DPolygon.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _FONT_H_
#define _FONT_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// �}�N���̒�`
//*****************************************************************************
#define FONT_PRIORITY		(4)
#define MAX_FONT_TYPE		(8)

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CFont : public CScene
{
public:
	typedef enum
	{//�����̏��
		STATE_NONE = 0,
		STATE_UP,		//���
		STATE_FADE,	//�o���������
		STATE_ENDOUT,	//������
		STATE_FADEOUT,	//������
		STATE_FADEOUT2,	//������NONE��
		STATE_MAX,		//�ő�l

	}STATE;
	CFont(int nPrioryity = FONT_PRIORITY) : CScene::CScene(nPrioryity) {};
	~CFont() {};

	static void	Load(int nID);
	static void	UnLoad(void);
	void	Set(RECT rect, D3DXCOLOR col, char *aStr, int nType, int nFormat, int nMaxFont, bool bShadow, STATE state);
	void	SetFont(char *aStr, int nMaxFont);	//���������̂ݕύX

	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);

	STATE	&GetState(void)		{ return m_state; }
	float	&GetfCntState(void) { return m_fCntState; }
	bool	&GetbDisplay(void)	{ return m_bDisplay; }
	D3DXCOLOR &GetCollar(void)  { return m_col; }
protected://*****************************************************************************
		  //�ϐ��錾//***********************************************************************

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	static	LPD3DXFONT			m_pFont[MAX_FONT_TYPE];			// �t�H���g�ւ̃|�C���^
	STATE		m_state;		//�����̏��
	D3DXCOLOR	m_col;		//�J���[
	RECT		m_rect;		//�����̕\���͈�
	int			m_nType;		//�t�H���g�̃^�C�v
	int			m_nFormat;	//�\���ꏊ
	float		m_fCntState;	//��ԊǗ��p
	int			m_nMaxFont;	//�\������ő吔
	int			m_nCntTime;	//�\���̂��߂̃J�E���g
	char		m_aStr[84];	//�����̗�
	bool		m_bDisplay;	//�\����\��
	bool		m_bshadow;	//�e�̗L��

};
#endif