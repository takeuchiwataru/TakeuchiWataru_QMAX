//=============================================================================
//
// ���f������ [model.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
#include "scene.h"

//*********************************************************************
//���f���N���X�̒�`
//*********************************************************************
class CModel : public CScene //�h���N���X
{
public:
	typedef struct
	{
		DWORD nNumMat = 0;						//�}�e���A�����̐�
		D3DXVECTOR3 pos;						//�ʒu
		D3DXVECTOR3 rot;						//����
		float fShadow;							//�e�̑傫��
		int nIdxShadow;							//�e�̃C���f�b�N�X
		int nType;								//���f���̎��
		bool bUse;								//�g�p���Ă��邩
	} MODEL;

	CModel();
	~CModel();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	void Setrot(D3DXVECTOR3 rot);
	MODEL *GetModel(void);
	bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin/*, MODEL **pModel*/);
	void SetModel(D3DXVECTOR3 pos, int nType);
	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void BindModel(DWORD nNumMat, LPD3DXMESH Mesh, LPD3DXBUFFER Buff);	//TEXTURE�����蓖�Ă�
	void SetParent(CModel *pModel);
	D3DXMATRIX GetMtxWorld(void);
	void SetMtxWorld(D3DXMATRIX MtxWorld);

	D3DXVECTOR3 VtxMin(void) { return m_VtxMinModel; }
	D3DXVECTOR3 VtxMax(void) { return m_VtxMaxModel; }

	D3DXVECTOR3 Getrot(void);
	D3DXVECTOR3 GetPos(void) { return m_aModel.pos; }

	//�����o�ϐ�
private:
	LPD3DXMESH				m_pMeshModel;			//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER			m_pBuffMatModel;		//�}�e���A�����ւ̃|�C���^
	LPDIRECT3DTEXTURE9		*m_pTextureModel;		//�e�N�X�`���ւ̃|�C���^
	DWORD					m_nNumMatModel = 0;		//�}�e���A�����̐�
	MODEL					m_aModel;				//���f�����
	D3DXVECTOR3				m_VtxMinModel, m_VtxMaxModel;		//���f���̍ŏ��l�A�ő�l
	D3DXMATRIX				m_mtxWorld;				//���[���h�}�g���b�N�X
	CModel					*m_pParent;				//�e���f���ւ̃|�C���^
public:
	bool					m_bShadow;

};


#endif