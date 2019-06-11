//=============================================================================
//
// �V�[��3D���� [scene3D.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "main.h"
#include "scene.h"

//*********************************************************************
//�V�[��3D�N���X�̒�`
//*********************************************************************
class CScene3D : public CScene //�h���N���X
{
public:
	typedef struct
	{

	}POLYGON;

	CScene3D();
	~CScene3D();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CScene3D *Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fDepth);
	float GetHeight(D3DXVECTOR3);
	void BindTexture(LPDIRECT3DTEXTURE9	Texture);


	//�����o�ϐ�
private:
	LPDIRECT3DVERTEXBUFFER9				m_pVtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9					m_pTexture = NULL;	//�e�N�X�`���ւ̃|�C���^
	float								m_Height;

	D3DXVECTOR3							m_pos;							//�ʒu
	D3DXVECTOR3							m_rot;							//����
	D3DXCOLOR							m_col;							//�F
	D3DXMATRIX							m_mtxWorld;						//���[���h�}�g���b�N�X
	float								m_fWidth, m_fDepth;				//���@���s��
};

#endif
