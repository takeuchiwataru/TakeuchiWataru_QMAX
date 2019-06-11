//=============================================================================
//
// �r���{�[�h�̏��� [billboard.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"
#include "scene.h"

//*********************************************************************
//�r���{�[�h�N���X�̒�`
//*********************************************************************
class CSceneBillBoard : public CScene //�h���N���X
{
public:
	CSceneBillBoard();
	~CSceneBillBoard();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	void Set(float fWidth, float fHeight);
	void SetBillboard(D3DXVECTOR3 pos, float fHeight, float fWidth);
	static CSceneBillBoard *Create(D3DXVECTOR3 pos, D3DXVECTOR3	move, float fWidth, float fHeight);
	void BindTexture(LPDIRECT3DTEXTURE9	Texture);	//TEXTURE�����蓖�Ă�
	D3DXVECTOR3 GetPos(void);
	void SetCol(D3DXCOLOR col);
	LPDIRECT3DVERTEXBUFFER9 GetVtx(void);

private:
	//�����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;			//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;			// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				m_pos;						// �|���S���̈ʒu
	D3DXVECTOR3				m_move;						// �ړ���
	float					m_fWidth, m_fHeight;		// ��,����
	D3DXMATRIX				m_mtrxWorld;				// ���[���h�}�g���b�N�X

};

#endif