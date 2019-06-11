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
	static CScene3D *Create(D3DXVECTOR3 pos,float fWidth,float fDepth);
	//static LPDIRECT3DVERTEXBUFFER9 GetVtx(void);
	float GetHeight(D3DXVECTOR3);
	//�����o�ϐ�
private:
	LPDIRECT3DVERTEXBUFFER9				m_pVtxBuffPolygon = NULL;	//���_�o�b�t�@�ւ̃|�C���^
	POLYGON								m_Polygon;					//�V�[��3D�\����
	LPDIRECT3DTEXTURE9					m_pTexturePolygon = NULL;	//�e�N�X�`���ւ̃|�C���^
	float								m_Height;

	D3DXVECTOR3							m_pos;							//�ʒu
	D3DXVECTOR3							m_rot;							//����
	D3DXMATRIX							m_mtxWorld;						//���[���h�}�g���b�N�X
	float								m_fWidth, m_fDepth;				//���@���s��

	//D3DXVECTOR3							m_aNor[4];
	//D3DXVECTOR3							m_aPos[4];
	//D3DXVECTOR3							m_aVec[4];
};

#endif
