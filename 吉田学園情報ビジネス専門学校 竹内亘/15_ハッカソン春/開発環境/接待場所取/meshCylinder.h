//=============================================================================
//
// ���b�V���V�����_�[���� [meshCylinderBG.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
class CSceneMeshCylinder : public CScene //�h���N���X
{
public:
	//���f���̎��
	typedef enum
	{
		CYLINDERTYPE_INWARD = 0,		//������
		CYLINDERTYPE_OUTWARD,			//�O����
		CYLINDERTYPE_MAX				//����
	}CYLINDERTYPE;

	CSceneMeshCylinder();
	~CSceneMeshCylinder();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSceneMeshCylinder *Create(D3DXVECTOR3 pos, float fWidth, float fDepth, int nSplitX, int nSplitZ, CYLINDERTYPE typeInOut);
	void Setpos(D3DXVECTOR3 pos);

	void SetRot(D3DXVECTOR3 rot);
	void BindTexture(LPDIRECT3DTEXTURE9	Texture);	//TEXTURE�����蓖�Ă�
	//�����o�ϐ�
private:
	float								m_fWidth;					// ��
	float								m_fDepth;					// ���s��
	D3DXVECTOR3							m_pos;						// �ʒu
	D3DXVECTOR3							m_rot;						// ����
	D3DXVECTOR3							m_move;						// �ړ���
	LPDIRECT3DVERTEXBUFFER9				m_pVtxBuff = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9					m_pTexture = NULL;	 		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9				m_pIdxBuff = NULL;			// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX							m_mtxWorld;					// ���[���h�}�g���b�N�X
	int									m_nNumVerTex;				// ���_��
	int									m_nNumIndex;				// �C���f�b�N�X��
	int									m_nNumPolygon;				// �|���S����
	float								m_Height;					// ����
	D3DXVECTOR3							m_aNor[100000];				// �@��
	int									m_nSplitX, m_nSplitY;		// ������
	CYLINDERTYPE						m_TypeInOut;				// �������O����
};
#endif
