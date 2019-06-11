//---------------------------------------------------------------------
//	�V�[��2D����(scene2d.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "scene2D.h"
#include "manager.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define POLYGON_TEXTURENAME  "data\\TEXTURE\\akira000.png"	//�e�N�X�`���̃t�@�C����
#define POLYGON_SIZE		(100)							//���_���WX�̈ړ���

//*****************************************************************************
// �O���[�o��
//*****************************************************************************

//--------------------------------------------
//�V�[��2D�N���X �R���X�g���N�^
//--------------------------------------------
CScene2D::CScene2D() : CScene(5,CScene::OBJTYPE_SCENE2D)
{
	//�����o�ϐ�
	m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �V�[��2D�̈ʒu

	m_fSpin = 0;			//��]
	m_fLength = 0;			//�傫��
	m_fScale = 0;			//�g��k��
}

//--------------------------------------------
//�V�[��2D�N���X �f�X�g���N�^
//--------------------------------------------
CScene2D::~CScene2D()
{
}

//--------------------------------------------
//�V�[��2D�̐���
//--------------------------------------------
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CScene2D *pScene2D;

	pScene2D = new CScene2D;

	pScene2D->m_pos = pos;
	pScene2D->m_fWidth = fWidth;
	pScene2D->m_fHeight = fHeight;

	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// �V�[��2D�̏���������
//=============================================================================
HRESULT CScene2D::Init()
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//�g��̒l
	m_fScale = 1.0f;
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_����ݒ�
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_pos.x + sinf(D3DX_PI * -0.75f) * m_fWidth;
	pVtx[0].pos.y = m_pos.y + cosf(D3DX_PI * -0.75f) * m_fHeight;
	pVtx[1].pos.x = m_pos.x + sinf(D3DX_PI * 0.75f) * m_fWidth;
	pVtx[1].pos.y = m_pos.y + cosf(D3DX_PI * 0.75f) * m_fHeight;
	pVtx[2].pos.x = m_pos.x + sinf(D3DX_PI * -0.25f) * m_fWidth;
	pVtx[2].pos.y = m_pos.y + cosf(D3DX_PI * -0.25f) * m_fHeight;
	pVtx[3].pos.x = m_pos.x + sinf(D3DX_PI * 0.25f) * m_fWidth;
	pVtx[3].pos.y = m_pos.y + cosf(D3DX_PI * 0.25f) * m_fHeight;

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//���_
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	CScene::SetObjType(OBJTYPE_SCENE2D);

	return S_OK;
}

//=============================================================================
// �V�[��2D�̏I������
//=============================================================================
void CScene2D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//����������(�V�[��2D��j��)
	Release();
}

//=============================================================================
// �V�[��2D�̍X�V����
//=============================================================================
void CScene2D::Update(void)
{

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

}

//=============================================================================
// �V�[��2D�̕`�揈��
//=============================================================================
void CScene2D::Draw(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �V�[��2D�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,	//�J�n���钸�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��
}

//=============================================================================
//�V�[��2D�e�N�X�`���̐ݒ�
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 Texture)
{
	m_pTexture = Texture;
}

//=============================================================================
//�V�[��2D�ʒu�ݒ�
//=============================================================================
void CScene2D::SetPos(D3DXVECTOR3 pos, float fSpin, float fScale, D3DXCOLOR col)
{
	m_pos = pos;
	m_fSpin = fSpin;

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//�g��̒l
	m_fScale = fScale;

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

#if 1
	pVtx[0].pos.x = m_pos.x + sinf(D3DX_PI * -0.75f + m_fSpin) *  (m_fWidth  + m_fScale);
	pVtx[0].pos.y = m_pos.y + cosf(D3DX_PI * -0.75f + m_fSpin) *  (m_fHeight + m_fScale);
	pVtx[1].pos.x = m_pos.x + sinf(D3DX_PI * 0.75f  + m_fSpin) *  (m_fWidth  + m_fScale);
	pVtx[1].pos.y = m_pos.y + cosf(D3DX_PI * 0.75f  + m_fSpin) *  (m_fHeight + m_fScale);
	pVtx[2].pos.x = m_pos.x + sinf(D3DX_PI * -0.25f + m_fSpin) *  (m_fWidth  + m_fScale);
	pVtx[2].pos.y = m_pos.y + cosf(D3DX_PI * -0.25f + m_fSpin) *  (m_fHeight + m_fScale);
	pVtx[3].pos.x = m_pos.x + sinf(D3DX_PI * 0.25f  + m_fSpin) *  (m_fWidth  + m_fScale);
	pVtx[3].pos.y = m_pos.y + cosf(D3DX_PI * 0.25f  + m_fSpin) *  (m_fHeight + m_fScale);
#endif

#if 0
	pVtx[0].pos.x = m_pos.x + sinf(D3DX_PI * -0.75f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[0].pos.y = m_pos.y + cosf(D3DX_PI * -0.75f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[1].pos.x = m_pos.x + sinf(D3DX_PI * 0.75f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[1].pos.y = m_pos.y + cosf(D3DX_PI * 0.75f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[2].pos.x = m_pos.x + sinf(D3DX_PI * -0.25f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[2].pos.y = m_pos.y + cosf(D3DX_PI * -0.25f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[3].pos.x = m_pos.x + sinf(D3DX_PI * 0.25f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[3].pos.y = m_pos.y + cosf(D3DX_PI * 0.25f + m_fSpin) *  (m_fWidth + m_fScale);
#endif

#if 0
	pVtx[0].pos.x = m_pos.x + sinf(D3DX_PI * -0.75f) * m_fWidth;
	pVtx[0].pos.y = m_pos.y + cosf(D3DX_PI * -0.75f) * m_fHeight;
	pVtx[1].pos.x = m_pos.x + sinf(D3DX_PI * 0.75f) * m_fWidth;
	pVtx[1].pos.y = m_pos.y + cosf(D3DX_PI * 0.75f) * m_fHeight;
	pVtx[2].pos.x = m_pos.x + sinf(D3DX_PI * -0.25f) * m_fWidth;
	pVtx[2].pos.y = m_pos.y + cosf(D3DX_PI * -0.25f) * m_fHeight;
	pVtx[3].pos.x = m_pos.x + sinf(D3DX_PI * 0.25f) * m_fWidth;
	pVtx[3].pos.y = m_pos.y + cosf(D3DX_PI * 0.25f) * m_fHeight;
#endif

	//���_�J���[
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;


	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//=============================================================================
//�V�[��2D��]�ݒ�
//=============================================================================
void CScene2D::SetRot(float fSpin)
{
	m_fSpin = fSpin;

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
#if 1
	pVtx[0].pos.x = m_pos.x + sinf(D3DX_PI * -0.75f + m_fSpin) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(D3DX_PI * -0.75f + m_fSpin) *  m_fLength;
	pVtx[1].pos.x = m_pos.x + sinf(D3DX_PI * 0.75f + m_fSpin) *  m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(D3DX_PI * 0.75f + m_fSpin) *  m_fLength;
	pVtx[2].pos.x = m_pos.x + sinf(D3DX_PI * -0.25f + m_fSpin) *  m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(D3DX_PI * -0.25f + m_fSpin) *  m_fLength;
	pVtx[3].pos.x = m_pos.x + sinf(D3DX_PI * 0.25f + m_fSpin) *  m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(D3DX_PI * 0.25f + m_fSpin) *  m_fLength;
#endif
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//=============================================================================
//�V�[��2D�ʒu���擾
//=============================================================================
D3DXVECTOR3 CScene2D::Getpos(void)
{
	return m_pos;
}
//=============================================================================
//�F�̐ݒ�
//=============================================================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	m_Col = col;

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[
	pVtx[0].col = m_Col;
	pVtx[1].col = m_Col;
	pVtx[2].col = m_Col;
	pVtx[3].col = m_Col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}