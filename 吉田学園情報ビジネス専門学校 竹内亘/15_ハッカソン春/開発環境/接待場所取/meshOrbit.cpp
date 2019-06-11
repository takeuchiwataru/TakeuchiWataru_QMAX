//=============================================================================
//
// ���b�V���I�[�r�b�g�������� [meshField.cpp]
// Author :  Meguro Mikiya
//
//=============================================================================
#include "meshOrbit.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHFIELD_TEXTURE_NAME	"data\\TEXTURE\\gradation000.jpg"	// �n�ʂ̃e�N�X�`����
#define MESHFIELD_SIZE_X		(50.0f)							// �n�ʑ傫��
#define MESHFIELD_SIZE_Z		(50.0f)							// �n�ʑ傫��
//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DVERTEXBUFFER9		CMeshOrbit::m_pVtxBuff = NULL;
LPDIRECT3DTEXTURE9			CMeshOrbit::m_pTexture = NULL;

//--------------------------------------------
//�V�[�����b�V���I�[�r�b�g�N���X �R���X�g���N�^
//--------------------------------------------
CMeshOrbit::CMeshOrbit() : CScene(4, CScene::OBJTYPE_MESHFIELD)
{
	m_MeshOrbit = {};				//�V�[��3D�\����
	m_pTexture = NULL;				//�e�N�X�`���ւ̃|�C���^
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nNumVerTex = 0;				// ���_��
	m_nNumPolygon = 0;				// �|���S����
	m_nAlphaMinus = 0;
	m_fAlpha = 1.0f;
	m_aPosVertex[0] = D3DXVECTOR3(0, 0, 0);
	m_aPosVertex[1] = D3DXVECTOR3(0, 0, 0);
}

//--------------------------------------------
//�V�[�����b�V���I�[�r�b�g�N���X�N���X �f�X�g���N�^
//--------------------------------------------
CMeshOrbit::~CMeshOrbit()
{
}

//=============================================================================
// ��������
//=============================================================================
CMeshOrbit * CMeshOrbit::Create(D3DXVECTOR3 pos)
{

	CMeshOrbit *pMeshOrbit;

	pMeshOrbit = new CMeshOrbit;

	pMeshOrbit->m_MeshOrbit.pos = pos;

	pMeshOrbit->Init();

	return pMeshOrbit;
}


//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshOrbit::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

												// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURE_NAME, &m_pTexture);

	// ���_���̍쐬
	MakeVertexMeshOrbit(pDevice);

	// �|���S���̏���ݒ�
	m_MeshOrbit.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_MeshOrbit.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�O�Ղ̏����ʒu
	m_aPosVertex[0] = m_MeshOrbit.pos;
	m_aPosVertex[1] = m_MeshOrbit.pos;
	//�I�t�Z�b�g�̐ݒ�
	m_offSet[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_offSet[1] = D3DXVECTOR3(0.0f, 50.0f, 0.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void  CMeshOrbit::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//����������(���b�V���I�[�r�b�g��j��)
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void  CMeshOrbit::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

						// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtxX = 0, nVtxCounter = 0; nCntVtxX < POLYGON_X + 1; nCntVtxX++)
	{
		// ���_�J���[�̐ݒ�
		pVtx[nCntVtxX + nVtxCounter].col =		D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fAlpha - (nCntVtxX * 0.03f));
		pVtx[nCntVtxX + nVtxCounter + 1].col =	D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fAlpha - (nCntVtxX * 0.01f));
		nVtxCounter += POLYGON_Z;
	}
	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	if (m_nCntAlpha >= 60)
	{
		m_nCntAlpha = 0;
	}

#ifdef _DEBUG
#if 0
	//�C�ӂ̃L�[1
	if (pInput->GetPress(DIK_1) == true)
	{
		m_nAlphaMinus += 1;
	}
	//�C�ӂ̃L�[2
	if (pInput->GetPress(DIK_2) == true)
	{
		m_nAlphaMinus -= 1;
	}

	//�C�ӂ̃L�[1
	if (pInput->GetPress(DIK_3) == true)
	{
		m_fAlpha += 0.01f;
	}
	//�C�ӂ̃L�[2
	if (pInput->GetPress(DIK_4) == true)
	{
		m_fAlpha -= 0.01f;
	}

	CDebugProc::Print(1, " �����x  : ( %d )\n", m_nAlphaMinus);
	CDebugProc::Print(1, " �����x  : ( %.1f )\n", m_fAlpha);

#if 0
	CDebugProc::Print(1, " �I�[�r�b�g[0]  : ( %.1f ,%.1f ,%.1f )\n", m_aPosVertex[0].x, m_aPosVertex[0].y, m_aPosVertex[0].z);
	CDebugProc::Print(1, " �I�[�r�b�g[1]  : ( %.1f ,%.1f ,%.1f )\n", m_aPosVertex[1].x, m_aPosVertex[1].y, m_aPosVertex[1].z);
	CDebugProc::Print(1, " �I�[�r�b�g[2]  : ( %.1f ,%.1f ,%.1f )\n", m_aPosVertex[2].x, m_aPosVertex[2].y, m_aPosVertex[2].z);
	CDebugProc::Print(1, " �I�[�r�b�g[3]  : ( %.1f ,%.1f ,%.1f )\n", m_aPosVertex[3].x, m_aPosVertex[3].y, m_aPosVertex[3].z);
	CDebugProc::Print(1, " �I�[�r�b�g[4]  : ( %.1f ,%.1f ,%.1f )\n", m_aPosVertex[4].x, m_aPosVertex[4].y, m_aPosVertex[4].z);
	CDebugProc::Print(1, " �I�[�r�b�g[5]  : ( %.1f ,%.1f ,%.1f )\n", m_aPosVertex[5].x, m_aPosVertex[5].y, m_aPosVertex[5].z);
	CDebugProc::Print(1, " �I�[�r�b�g[6]  : ( %.1f ,%.1f ,%.1f )\n", m_aPosVertex[6].x, m_aPosVertex[6].y, m_aPosVertex[6].z);
	CDebugProc::Print(1, " �I�[�r�b�g[7]  : ( %.1f ,%.1f ,%.1f )\n", m_aPosVertex[7].x, m_aPosVertex[7].y, m_aPosVertex[7].z);
	CDebugProc::Print(1, " �I�[�r�b�g[8]  : ( %.1f ,%.1f ,%.1f )\n", m_aPosVertex[8].x, m_aPosVertex[8].y, m_aPosVertex[8].z);
	CDebugProc::Print(1, " �I�[�r�b�g[9]  : ( %.1f ,%.1f ,%.1f )\n", m_aPosVertex[9].x, m_aPosVertex[9].y, m_aPosVertex[9].z);
#endif
#endif
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void  CMeshOrbit::Draw(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent;

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//����ς�
	for (int nCnt = m_nNumVerTex - 3; nCnt >= 0; nCnt--)
	{
		m_aPosVertex[nCnt + 2] = m_aPosVertex[nCnt];
		pVtx[nCnt + 2].pos = m_aPosVertex[nCnt + 2];
	}

	//�}�g���b�N�X�Ƃ������킹��
	D3DXVec3TransformCoord(&m_aPosVertex[0], &m_offSet[0], m_pMtxParent);
	pVtx[0].pos = m_aPosVertex[0];

	D3DXVec3TransformCoord(&m_aPosVertex[1], &m_offSet[1], m_pMtxParent);
	pVtx[1].pos = m_aPosVertex[1];
	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//�J�����O�̐ݒ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);
	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0,m_nNumPolygon);
	//�J�����O�̐ݒ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	//�f�t�H���g�̏ꍇFALSE�ɂȂ��Ă��邩��TRUE�ɂ���
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void CMeshOrbit::MakeVertexMeshOrbit(LPDIRECT3DDEVICE9 pDevice)
{
	int nVtxCounter = 0;
	int nIdxCounter = 0;

	int nCntVtxX;

	// ���_��
	m_nNumVerTex = (POLYGON_X + 1) * (POLYGON_Z + 1);

	// �|���S����
	m_nNumPolygon = (POLYGON_X + 1) * (POLYGON_Z + 1) + (2 * (POLYGON_Z - 1)) + (POLYGON_X + 1) * (POLYGON_Z - 1) - 2;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVerTex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntVtxX = 0; nCntVtxX < POLYGON_X + 1; nCntVtxX++)
	{
		// ���_���W�̐ݒ�

		pVtx[nCntVtxX + nVtxCounter].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[nCntVtxX + nVtxCounter + 1].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);

		// �@���̐ݒ�
		pVtx[nCntVtxX + nVtxCounter].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCntVtxX + nVtxCounter + 1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// ���_�J���[�̐ݒ�
		pVtx[nCntVtxX + nVtxCounter].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntVtxX + nVtxCounter + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		// �e�N�X�`�����W�̐ݒ�
		pVtx[nCntVtxX + nVtxCounter].tex = D3DXVECTOR2(0.0f + (nCntVtxX * (1.0f / POLYGON_X)), 0.0f);
		pVtx[nCntVtxX + nVtxCounter + 1].tex = D3DXVECTOR2(0.0f + (nCntVtxX * (1.0f / POLYGON_X)), 1.0f);

		nVtxCounter += POLYGON_Z;
	}
	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CMeshOrbit::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURE_NAME, &m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CMeshOrbit::UnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �ʒu�ݒ菈��
//=============================================================================
void CMeshOrbit::Setpos(D3DXVECTOR3 pos)
{
}

//=============================================================================
// �e��ݒ�
//=============================================================================
void CMeshOrbit::SetMtxParent(D3DXMATRIX * pMtx)
{
	m_pMtxParent = pMtx;
}
