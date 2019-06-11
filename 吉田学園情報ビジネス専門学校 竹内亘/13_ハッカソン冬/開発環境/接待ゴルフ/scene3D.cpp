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
//LPDIRECT3DVERTEXBUFFER9		CScene3D::m_pVtxBuffPolygon = NULL;

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
CScene3D * CScene3D::Create(D3DXVECTOR3 pos, float fWidth, float fDepth)
{
	CScene3D *pScene3D;

	pScene3D = new CScene3D;

	pScene3D->m_pos = pos;
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


	//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			POLYGON_TEXTURENAME,
			&m_pTexturePolygon);
	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffPolygon,
		NULL);


	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N
	m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y, m_pos.z + m_fDepth);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y, m_pos.z + m_fDepth);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y, m_pos.z - m_fDepth);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y, m_pos.z - m_fDepth);

	//pVtx[0].pos = D3DXVECTOR3(-m_pos.x, m_pos.y, m_pos.z);
	//pVtx[1].pos = D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z);
	//pVtx[2].pos = D3DXVECTOR3(-m_pos.x, m_pos.y, -m_pos.z);
	//pVtx[3].pos = D3DXVECTOR3(m_pos.x, m_pos.y, -m_pos.z);


	//�@���v�Z�Z�o
	Vec0 = pVtx[0].pos - pVtx[2].pos;
	Vec1 = pVtx[3].pos - pVtx[2].pos;
	// X,Y,Z�̏��Ł�
	nor0.x = (Vec0.y * Vec1.z) - (Vec0.z * Vec1.y);
	nor0.y = (Vec0.z * Vec1.x) - (Vec0.x * Vec1.z);
	nor0.z = (Vec0.x * Vec1.y) - (Vec0.y * Vec1.x);
	//���K��
	D3DXVec3Normalize(&nor0, &nor0);
	pVtx[2].nor = nor0;

	//�@���v�Z�Z�o
	Vec0 = pVtx[3].pos - pVtx[1].pos;
	Vec1 = pVtx[0].pos - pVtx[1].pos;
	//��s�ŏ�����
	//D3DXVec3Cross(&nor1, &Vec0, &Vec1);

	nor1.x = (Vec0.y * Vec1.z) - (Vec0.z * Vec1.y);
	nor1.y = (Vec0.z * Vec1.x) - (Vec0.x * Vec1.z);
	nor1.z = (Vec0.x * Vec1.y) - (Vec0.y * Vec1.x);
	//���K�����Ȃ��Ƃ����Ȃ�
	D3DXVec3Normalize(&nor1, &nor1);
	pVtx[3].nor = nor1;

	//nor0��nor1�̒��Ԓl���Ƃ�
	pVtx[0].nor = (nor0 + nor1) / 2;
	pVtx[1].nor = (nor0 + nor1) / 2;

	//for (int nCnt = 0; nCnt < 4; nCnt++)
	//{
	//	m_aNor[nCnt] = pVtx[nCnt].nor;
	//	m_aPos[nCnt] = pVtx[nCnt].pos;
	//}

	//�@���̐ݒ�
	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(TEX_LEFT, TEX_TOP);
	pVtx[1].tex = D3DXVECTOR2(TEX_RIGHT, TEX_TOP);
	pVtx[2].tex = D3DXVECTOR2(TEX_LEFT, TEX_BOT);
	pVtx[3].tex = D3DXVECTOR2(TEX_RIGHT, TEX_BOT);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuffPolygon->Unlock();

	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	CScene::SetObjType(OBJTYPE_SCENE3D);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene3D::Uninit(void)
{	//�e�N�X�`���̔j��
	if (m_pTexturePolygon != NULL)
	{
		m_pTexturePolygon->Release();
		m_pTexturePolygon = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuffPolygon != NULL)
	{
		m_pVtxBuffPolygon->Release();
		m_pVtxBuffPolygon = NULL;
	}
	//����������(�V�[��3D��j��)
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene3D::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	CScene3D::Setpos(m_pos);

}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene3D::Draw(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

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
	pDevice->SetStreamSource(0, m_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));
	//���_�t�H�[�}�b�g��ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexturePolygon);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,	//�J�n���钸�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��

}

//=============================================================================
// �ʒu�ݒ菈��
//=============================================================================
void CScene3D::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// ���_�擾����
//=============================================================================
//LPDIRECT3DVERTEXBUFFER9 CScene3D::GetVtx(void)
//{
//	return m_pVtxBuffPolygon;
//}

//=============================================================================
// �n�ʂ̍�����Ԃ�
//=============================================================================
float CScene3D::GetHeight(D3DXVECTOR3 pos)
{
	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N
	m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

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
	m_pVtxBuffPolygon->Unlock();

	return m_Height;
}
