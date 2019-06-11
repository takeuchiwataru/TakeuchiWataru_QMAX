//=============================================================================
//
// ���b�V���t�B�[���h���� [meshFiled.h]
// Author :
//
//=============================================================================
#ifndef _MESHORBIT_H_
#define _MESHORBIT_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define POLYGON_X				(100)								// �|���S���̐��iX�j
#define POLYGON_Z				(1)								// �|���S���̐��iZ�j

//*********************************************************************
//�V�[�����b�V���t�B�[���h�N���X�̒�`
//*********************************************************************
class CMeshOrbit : public CScene //�h���N���X
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 rot;	// ����
		D3DXVECTOR3 move;	// �ړ���
	} MESHFIELD;

	CMeshOrbit();
	~CMeshOrbit();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMeshOrbit *Create(D3DXVECTOR3 pos);
	void Setpos(D3DXVECTOR3 pos);
	void SetMtxParent(D3DXMATRIX *pMtx);
	void MakeVertexMeshOrbit(LPDIRECT3DDEVICE9 pDevice);
	static HRESULT Load(void);
	static void UnLoad(void);

	//�����o�ϐ�
private:
	static LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^
	MESHFIELD							m_MeshOrbit;			//�V�[��3D�\����
	static LPDIRECT3DTEXTURE9			m_pTexture;				//�e�N�X�`���ւ̃|�C���^
	D3DXMATRIX							m_mtxWorld;				// ���[���h�}�g���b�N�X
	int									m_nNumVerTex;			// ���_��
	int									m_nNumPolygon;			// �|���S����

	int		m_nCntAlpha;
	int		m_nLife;
	int		m_nAlphaMinus;
	float	m_fAlpha;

	D3DXMATRIX							*m_pMtxParent;										//�e�̃}�g���b�N�X�ւ̃|�C���^
	D3DXVECTOR3							m_aPosVertex[(POLYGON_X + 1) * (POLYGON_Z + 1)];	//�Z�o�������_���W
	D3DXVECTOR3							m_offSet[2];										//���[�̃I�t�Z�b�g
};
#endif
