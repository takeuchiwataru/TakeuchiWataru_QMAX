//---------------------------------------------------------------------
//	�i���o�[����(number.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "number.h"
#include "manager.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUMBER_TEXTURENAME  "data\\TEXTURE\\UI\\number001.png"		//�e�N�X�`���̃t�@�C����
#define NUMBER_SIZE			(15)									//���_���WX�̈ړ���

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9 CNumber ::m_pTexture = NULL;

//--------------------------------------------
//�i���o�[�N���X �R���X�g���N�^
//--------------------------------------------
CNumber::CNumber()
{
	m_pos = D3DXVECTOR3(0,0,0);
	m_col = D3DXCOLOR(0,0,0,0);
	m_fWidth = 0;	// ��
	m_fHeight = 0;	// ����
	m_fScale = 0;	// �g��
	m_nNumber = 0;	// ���l
}

//--------------------------------------------
//�i���o�[�N���X �f�X�g���N�^
//--------------------------------------------
CNumber::~CNumber()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CNumber *CNumber::Create(D3DXVECTOR3 pos,D3DXCOLOR col, float fWidth, float fHeight)
{
	CNumber *pNumber;

	pNumber = new CNumber;

	pNumber->m_pos = pos;
	pNumber->m_col = col;
	pNumber->m_fWidth = fWidth;
	pNumber->m_fHeight = fHeight;
	pNumber->Init();

	return pNumber;
}


//=============================================================================
// �����̏���������
//=============================================================================
HRESULT CNumber::Init(void)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

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

	//���_���W

	pVtx[0].pos.x = m_pos.x + sinf(D3DX_PI * -0.75f) *  (m_fWidth + m_fScale);
	pVtx[0].pos.y = m_pos.y + cosf(D3DX_PI * -0.75f) *  (m_fHeight + m_fScale);
	pVtx[1].pos.x = m_pos.x + sinf(D3DX_PI * 0.75f) *  (m_fWidth + m_fScale);
	pVtx[1].pos.y = m_pos.y + cosf(D3DX_PI * 0.75f) *  (m_fHeight + m_fScale);
	pVtx[2].pos.x = m_pos.x + sinf(D3DX_PI * -0.25f) *  (m_fWidth + m_fScale);
	pVtx[2].pos.y = m_pos.y + cosf(D3DX_PI * -0.25f) *  (m_fHeight + m_fScale);
	pVtx[3].pos.x = m_pos.x + sinf(D3DX_PI * 0.25f) *  (m_fWidth + m_fScale);
	pVtx[3].pos.y = m_pos.y + cosf(D3DX_PI * 0.25f) *  (m_fHeight + m_fScale);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
	//���_
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	CScene::SetObjType(OBJTYPE_SCENE2D);

	//�l�̏�����
	m_fScale = 0;	// �g��
	m_nNumber = 0;	// ���l

	return S_OK;
}

//=============================================================================
// �����̏I������
//=============================================================================
void CNumber::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//����������(�I�u�W�F�N�g��j��)
	Release();
}

//=============================================================================
// �����̍X�V����
//=============================================================================
void CNumber::Update(void)
{

}

//=============================================================================
// �����̕`�揈��
//=============================================================================
void CNumber::Draw(void)
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

	// �����̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,	//�J�n���钸�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��
}

//=============================================================================
// �����̐ݒ菈��
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	m_nNumber = nNumber;

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f + (nNumber * 0.1f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + (nNumber * 0.1f), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (nNumber * 0.1f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (nNumber * 0.1f), 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}


//=============================================================================
// �����̎擾����
//=============================================================================
int CNumber::GetNumber(void)
{
	return m_nNumber;
}


//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CNumber::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		NUMBER_TEXTURENAME,
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j������
//=============================================================================
void CNumber::UnLoad(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//=============================================================================
// �J���[�̃Z�b�g
//=============================================================================
void CNumber::SetColor(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_����ݒ�
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

void CNumber::SetScale(float scale)
{
	//�g��l
	m_fScale = scale;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_pos.x + sinf(D3DX_PI * -0.75f) *  (m_fWidth + m_fScale);
	pVtx[0].pos.y = m_pos.y + cosf(D3DX_PI * -0.75f) *  (m_fHeight + m_fScale);
	pVtx[1].pos.x = m_pos.x + sinf(D3DX_PI * 0.75f) *  (m_fWidth + m_fScale);
	pVtx[1].pos.y = m_pos.y + cosf(D3DX_PI * 0.75f) *  (m_fHeight + m_fScale);
	pVtx[2].pos.x = m_pos.x + sinf(D3DX_PI * -0.25f) *  (m_fWidth + m_fScale);
	pVtx[2].pos.y = m_pos.y + cosf(D3DX_PI * -0.25f) *  (m_fHeight + m_fScale);
	pVtx[3].pos.x = m_pos.x + sinf(D3DX_PI * 0.25f) *  (m_fWidth + m_fScale);
	pVtx[3].pos.y = m_pos.y + cosf(D3DX_PI * 0.25f) *  (m_fHeight + m_fScale);
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}
