//=============================================================================
//
// �G�t�F�N�g���� [effect.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "billboard.h"

//*********************************************************************
//�r���{�[�h�N���X�̒�`
//*********************************************************************
class CEffect : public CSceneBillBoard //�h���N���X
{
public:
	typedef enum
	{
		EFFECTTEX_NORMAL000 = 0,	//�ʏ�
		EFFECTTEX_BUBBLE000,		//�A
		EFFECTTEX_HAHEN000,			//�j��
		EFFECTTEX_HAHEN001,			//�j��2
		EFFECTTEX_SMOKE,			//����
		EFFECTTEX_MAX				//�e�N�X�`���̑���
	}EFFECTTEX;

	CEffect();
	~CEffect();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXCOLOR col,
							float fWidth, float fHeight,int nNumMax,int nLife, EFFECTTEX TexType);
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture[EFFECTTEX_MAX];	// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3					m_pos;						// �ʒu
	D3DXVECTOR3					m_move;						// �ړ���
	D3DXVECTOR3					m_posold;					// �O��̈ʒu
	float						m_fWidth, m_fHeight;		// �� ����
	D3DXMATRIX					m_mtrxWorld;				// ���[���h�}�g���b�N�X
	D3DXCOLOR					m_Col;						// �J���[
	int							m_nNumMax;					// �G�t�F�N�g�̃|���S����
	int							m_nLife;					// �G�t�F�N�g��������܂ł̎���
	float						m_fAlpha;					// �G�t�F�N�g�̓����x
	int							m_nCntTimer;				// �^�C�}�[
	CSceneBillBoard				*m_pBillBoard;

	EFFECTTEX					m_TexType;
};
#endif
