//=============================================================================
//
// �T�[�N������ [circle.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _UICIRCLE_H_
#define _UICIRCLE_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_CIRCLE			(2)			//�T�[�N���̐�

//*****************************************************************************
//�@�O���錾
//*****************************************************************************
//class CModel;
class CSceneMeshField;

//*********************************************************************
//�T�[�N���N���X�̒�`
//*********************************************************************
class CCircle : public CScene //�h���N���X
{
public:
	//���f���̎��
	typedef enum
	{
		CIRCLETEX_NORMAL = 0,	//�^�C��
		CIRCLETEX_MAX			//�e�N�X�`���̑���
	}CIRCLETEX;

	CCircle();
	~CCircle();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CCircle *Create(D3DXVECTOR3 pos, float fWidth,float fDepth,D3DXCOLOR col, CIRCLETEX tex, int nSplitX, int nSplitZ);
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	//�����o�ϐ�
	D3DXVECTOR3					m_pos;						//�ʒu
	D3DXVECTOR3					m_posold;					//�O��̈ʒu
	D3DXVECTOR3					m_move;						//�ړ���
	D3DXVECTOR3					m_rot;						//����
	D3DXCOLOR					m_col;						//�F
	float						m_fWidth, m_fDepth;			//�� ���s��
	float						m_fMinusWidth[MAX_CIRCLE],
								m_fMinusDepth[MAX_CIRCLE];
	int							m_nSplitX, m_nSplitZ;		//������
	CIRCLETEX					m_Type;						//�^�C�v

	static LPDIRECT3DTEXTURE9	m_pTexture[CIRCLETEX_MAX];	//�e�N�X�`���ւ̃|�C���^

	CSceneMeshField				*m_pCircle[MAX_CIRCLE];		//�T�[�N���{�̂ւ̃|�C���^
public:
};

#endif