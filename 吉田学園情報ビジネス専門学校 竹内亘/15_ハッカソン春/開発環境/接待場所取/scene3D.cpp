//=============================================================================
//
// �|���S������ [polygon.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "scene3D.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define POLYGON_TEXTURENAME		 "data\\TEXTURE\\field001.jpg"	//�e�N�X�`���̃t�@�C����
#define TEX_POS_X_INIT			(1.0f)							//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)							//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)							//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)							//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)							//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)							//�e�N�X�`�����WV��

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
//LPDIRECT3DVERTEXBUFFER9		CScene3D::m_pVtxBuff = NULL;

//--------------------------------------------
//�V�[��3D�N���X �R���X�g���N�^
//--------------------------------------------
CScene3D::CScene3D() : CScene(4, CScene::OBJTYPE_SCENE3D)
{
	m_pos = D3DXVECTOR3(0,0,0);			//�ʒu
	m_rot = D3DXVECTOR3(0, 0, 0);		//����
	D3DXMatrixIdentity(&m_mtxWorld);	//���[���h�}�g���b�N�X
}

//--------------------------------------------
//�V�[��3D�N���X �f�X�g���N�^
//--------------------------------------------
CScene3D::~CScene3D()
{
}

//=============================================================================
// ��������
//=============================================================================
CScene3D * CScene3D::Create(D3DXVECTOR3 pos,D3DXCOLOR col, float fWidth, float fDepth)
{
	CScene3D *pScene3D;

	pScene3D = new CScene3D;

	pScene3D->m_pos = pos;
	pScene3D->m_col = col;
	pScene3D->m_fWidth = fWidth;
	pScene3D->m_fDepth = fDepth;
	pScene3D->Init();

	return pScene3D;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene3D::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//�@���p
	D3DXVECTOR3 Vec0, Vec1, nor0, nor1;

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, m_pos.y, m_fDepth);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, m_pos.y, m_fDepth);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, m_pos.y, -m_fDepth);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, m_pos.y, -m_fDepth);
	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//���_�J���[
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(TEX_LEFT, TEX_TOP);
	pVtx[1].tex = D3DXVECTOR2(TEX_RIGHT, TEX_TOP);
	pVtx[2].tex = D3DXVECTOR2(TEX_LEFT, TEX_BOT);
	pVtx[3].tex = D3DXVECTOR2(TEX_RIGHT, TEX_BOT);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	CScene::SetObjType(OBJTYPE_SCENE3D);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene3D::Uninit(void)
{
	//����������(�V�[��3D��j��)
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene3D::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene3D::Draw(void)
{
	//���݂̃��[�h���擾
	CManager::MODE mode = CManager::GetMode();
	//�v���C���[���擾
	CPlayer *pPlayer = CGame::GetPlayer();
	//
	D3DXVECTOR3 Kyori = m_pos - pPlayer->GetPos();

	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	if (m_pos.z + 200 > pPlayer->GetPos().z)
	{
		Kyori.z = abs(Kyori.z);
		if (Kyori.z < 10000)
		{

			if (GetObjType() == OBJTYPE_SHADOW)
			{
				//���u�����f�B���O�����Z�����ɐݒ�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

				//�A���t�@�e�X�g(�����F��`�悵�Ȃ��悤��)
				pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
				pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
				pDevice->SetRenderState(D3DRS_ALPHAREF, 90);
			}

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&m_mtxWorld);
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
			D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
			D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
			//���_�t�H�[�}�b�g��ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_pTexture);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0,	//�J�n���钸�_�̃C���f�b�N�X
				2); //�`�悷��v���~�e�B�u��

			if (GetObjType() == OBJTYPE_SHADOW)
			{
				// ���u�����f�B���O�����ɖ߂�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			}

		}
	}
}

//=============================================================================
// �ʒu�ݒ菈��
//=============================================================================
void CScene3D::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, m_pos.y, m_fDepth);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, m_pos.y, m_fDepth);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, m_pos.y,-m_fDepth);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, m_pos.y,-m_fDepth);
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//=============================================================================
// �n�ʂ̍�����Ԃ�
//=============================================================================
float CScene3D::GetHeight(D3DXVECTOR3 pos)
{
	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fGaiseki;
	//�p
	D3DXVECTOR3 VecA, VecB, Vec0, Vec1;
	//�E���̎O�p�`
	Vec0 = pVtx[1].pos - pVtx[2].pos;
	Vec1 = pos - pVtx[2].pos;
	fGaiseki = (Vec0.z * Vec1.x) - (Vec0.x * Vec1.z);

	if (fGaiseki < 0)
	{//�E
		VecA = pos - pVtx[0].pos;
		//VecA��y�����߂�
		m_Height = (-(VecA.x * pVtx[0].nor.x) - (VecA.z * pVtx[0].nor.z)) / pVtx[0].nor.y + pVtx[0].pos.y;
	}
	else if (fGaiseki >= 0)
	{//��
		VecB = pos - pVtx[3].pos;
		//VecA��y�����߂�
		m_Height = (-(VecB.x * pVtx[3].nor.x) - (VecB.z * pVtx[3].nor.z)) / pVtx[3].nor.y + pVtx[3].pos.y;
	}
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return m_Height;
}

//=============================================================================
// �e�N�X�`�������蓖��
//=============================================================================
void CScene3D::BindTexture(LPDIRECT3DTEXTURE9 Texture)
{
	m_pTexture = Texture;
}