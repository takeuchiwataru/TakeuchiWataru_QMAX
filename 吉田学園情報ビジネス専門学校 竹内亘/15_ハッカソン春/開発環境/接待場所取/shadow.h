//=============================================================================
//
// �V�[��3D���� [scene3D.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"
#include "scene.h"
#include "scene3D.h"

//*********************************************************************
//�V�[��3D�N���X�̒�`
//*********************************************************************
class CShadow : public  CScene3D//�h���N���X
{
public:
	typedef enum
	{
		SHADOWTYPE_NORMAL = 0,
		SHADOWTYPE_BILL,
		SHADOWTYPE_MAX,
	}SHADOWTYPE;
	CShadow();
	~CShadow();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CShadow *Create(D3DXVECTOR3 pos, float fWidth, float fDepth, D3DXCOLOR col,SHADOWTYPE type);
	static HRESULT Load(void);
	static void UnLoad(void);

	//�����o�ϐ�
private:
	LPDIRECT3DVERTEXBUFFER9				m_pVtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
	static LPDIRECT3DTEXTURE9			m_pTexture[SHADOWTYPE_MAX];	//�e�N�X�`���ւ̃|�C���^
	float								m_Height;

	D3DXVECTOR3							m_pos;							//�ʒu
	D3DXVECTOR3							m_rot;							//����
	D3DXCOLOR							m_col;
	D3DXMATRIX							m_mtxWorld;						//���[���h�}�g���b�N�X
	float								m_fWidth, m_fDepth;				//���@���s��

	CScene3D							*m_pScene3D;
	SHADOWTYPE							m_Type;
};

#endif
