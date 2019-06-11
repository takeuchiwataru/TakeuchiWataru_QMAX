//=============================================================================
//
// UI�t�B�j�b�V������ [UIFinish.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _UIFINISH_H_
#define _UIFINISH_H_

#include "main.h"
#include "scene2D.h"

#define MAX_FINISH (1)

//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CNumber;

//*********************************************************************
//UI�t�B�j�b�V���N���X�̒�`
//*********************************************************************
class CUIFinish : public CScene2D  //�h���N���X
{
public:
	CUIFinish();
	~CUIFinish();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUIFinish *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_FINISH];		// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3					m_pos;							// �ʒu
	D3DXVECTOR3					m_move;							// �ړ���
	D3DXVECTOR3					m_posold;						// �O��̈ʒu
	float						m_fWidth, m_fHeight;			// �� ����
	D3DXMATRIX					m_mtrxWorld;					// ���[���h�}�g���b�N�X
	CScene2D					*m_pScene2D[MAX_FINISH];	// 2D�|���S���ւ̃|�C���^
	int							m_nItem;						// �l����
	int							m_nColorFlash;					// �_�ŃJ�E���g
	D3DXCOLOR					m_Col;							// �F
	bool						m_bEnter;						// �����ꂽ���ǂ������
	float						m_fScale;						// �g��k����
	int							m_ScaleCounter;					// �g��k���̃J�E���^�[
};
#endif
