//=============================================================================
//
// UI�Q�[�W���� [UIGauge.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _UIGAUGE_H_
#define _UIGAUGE_H_

#include "main.h"
#include "scene2D.h"

#define MAX_GAUGE (3)
//*********************************************************************
//UI�Q�[�W�N���X�̒�`
//*********************************************************************
class CUIGauge : public CScene2D  //�h���N���X
{
public:
	typedef enum
	{
		GAUGESTATE_NORMAL = 0,	//�ʏ�
		GAUGESTATE_MAXGAUGE,	//�Q�[�W���ő�
	}GAUGESTATE;

	CUIGauge();
	~CUIGauge();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUIGauge *Create(D3DXVECTOR3 pos,float fWidth, float fHeight);
	static HRESULT Load(void);
	static void UnLoad(void);
	static void SetGauge(float fGauge);
	static GAUGESTATE GetGaugeState(void);

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_GAUGE];		// �e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_pTextureLogo;				// LOGO�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3					m_pos;						// �ʒu
	D3DXVECTOR3					m_move;						// �ړ���
	D3DXVECTOR3					m_posold;					// �O��̈ʒu
	float						m_fWidth, m_fHeight;		// �� ����
	static float				m_fVtxHeight;				// ���_�̍���
	D3DXMATRIX					m_mtrxWorld;				// ���[���h�}�g���b�N�X
	CScene2D					*m_pScene2D[MAX_GAUGE];
	static GAUGESTATE			m_State;
};
#endif
