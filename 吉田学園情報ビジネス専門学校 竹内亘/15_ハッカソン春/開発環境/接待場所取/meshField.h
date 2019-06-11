//=============================================================================
//
// ���b�V���t�B�[���h���� [meshFiled.h]
// Author :
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"
#include "scene.h"

//*********************************************************************
//�V�[�����b�V���t�B�[���h�N���X�̒�`
//*********************************************************************
class CSceneMeshField : public CScene //�h���N���X
{
public:
	CSceneMeshField();
	~CSceneMeshField();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSceneMeshField *Create(D3DXVECTOR3 pos, float fWidth, float fDepth, int nSplitX, int nSplitZ);
	void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);
	void Setpos(D3DXVECTOR3 pos);
	bool GetHeightbool(D3DXVECTOR3 &pos);			//�n�ʂƂ̓����蔻��
	void BindTexture(LPDIRECT3DTEXTURE9	Texture);	//TEXTURE�����蓖�Ă�

	void SetHeight(D3DXVECTOR3 pos, float fValue, float fRange);	//�N���̐ݒ�
	void NormalSet(void);

	//�����o�ϐ�
private:
	float								m_fWidth;						// ��
	float								m_fDepth;						// ���s��
	D3DXVECTOR3							m_pos;							// �ʒu
	D3DXVECTOR3							m_rot;							// ����
	D3DXVECTOR3							m_move;							// �ړ���
	LPDIRECT3DVERTEXBUFFER9				m_pVtxBuff = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9					m_pTexture = NULL;	 					// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9				m_pIdxBuffMeshField = NULL;		// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX							m_mtxWorldMeshField;			// ���[���h�}�g���b�N�X
	int									m_nNumVerTexMeshField;			// ���_��
	int									m_nNumIndexMeshField;			// �C���f�b�N�X��
	int									m_nNumPolygonMeshField;			// �|���S����
	float								m_Height;
	D3DXVECTOR3							m_aNor[100000];
	int									m_nSplitX, m_nSplitZ;			// ������
#ifdef  _DEBUG
	int m_nSelectVtx = 0;
#endif
};
#endif
