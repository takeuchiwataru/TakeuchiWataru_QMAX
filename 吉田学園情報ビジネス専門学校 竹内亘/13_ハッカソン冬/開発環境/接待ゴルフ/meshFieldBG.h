//=============================================================================
//
// ���b�V���t�B�[���hBG���� [meshFiledBG.h]
// Author :
//
//=============================================================================
#ifndef _MESHFIELDBG_H_
#define _MESHFIELDBG_H_

#include "main.h"
#include "scene.h"

//*********************************************************************
//�V�[�����b�V���t�B�[���h�N���X�̒�`
//*********************************************************************
class CSceneMeshFieldBG : public CScene //�h���N���X
{
public:
	typedef struct
	{
		D3DXVECTOR3 rot;	// ����
		D3DXVECTOR3 move;	// �ړ���
	} MESHFIELD;

	CSceneMeshFieldBG();
	~CSceneMeshFieldBG();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSceneMeshFieldBG *Create(D3DXVECTOR3 pos, float fWidth, float fDepth, int nSplitX, int nSplitZ);
	void Setpos(D3DXVECTOR3 pos);
	static LPDIRECT3DVERTEXBUFFER9 GetVtx(void);
	float GetHeight(D3DXVECTOR3);
	void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);
	void SetHeight(D3DXVECTOR3 pos, float fValue, float fRange);
	void SaveHeight(void);											//�t�@�C���̃Z�[�u
	void LoadHeight(void);											//�t�@�C���̃��[�h
	void NormalSet(void);


	//�����o�ϐ�
private:
	LPDIRECT3DVERTEXBUFFER9				m_pVtxBuff;					//���_�o�b�t�@�ւ̃|�C���^
	MESHFIELD							m_MeshFiled;				//�V�[��3D�\����
	LPDIRECT3DTEXTURE9					m_pTexture = NULL;			//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9				m_pIdxBuffMeshField = NULL;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX							m_mtxWorldMeshField;		// ���[���h�}�g���b�N�X
	int									m_nNumVerTexMeshField;		// ���_��
	int									m_nNumIndexMeshField;		// �C���f�b�N�X��
	int									m_nNumPolygonMeshField;		// �|���S����
	float								m_Height;
	D3DXVECTOR3							m_aNor[100000];
	D3DXVECTOR3							m_Pos;						// �ʒu
	float								m_fWidth;					// ��
	float								m_fDepth;					// ���s��
	int									m_nSplitX, m_nSplitZ;		// ������

#ifdef  _DEBUG
	int m_nSelectVtx = 0;
#endif
};
#endif
