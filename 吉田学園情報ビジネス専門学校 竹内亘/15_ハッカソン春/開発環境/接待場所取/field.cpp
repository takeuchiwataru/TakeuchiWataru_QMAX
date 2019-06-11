//---------------------------------------------------------------------
//	�t�B�[���h����(field.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "field.h"
#include "meshField.h"
#include "fade.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME000		"data\\TEXTURE\\FIELD\\field002.jpg"	// �n�ʂ̃e�N�X�`����
#define TEXTURE_NAME001		"data\\TEXTURE\\FIELD\\ROAD002.jpg"		// �n�ʂ̃e�N�X�`����
#define TEXTURE_NAME002		"data\\TEXTURE\\FIELD\\field001.jpg"	// �n�ʂ̃e�N�X�`����
#define TEXTURE_NAME003		"data\\TEXTURE\\FIELD\\field004.jpg"	// �n�ʂ̃e�N�X�`����

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9			CField::m_pTexture[FIELDTEX_MAX] = {};

//--------------------------------------------
//�t�B�[���h�N���X �R���X�g���N�^
//--------------------------------------------
CField::CField() : CScene(3, CScene::OBJTYPE_FIELD)
{
	m_pos = D3DXVECTOR3(0, 0, 0);					//�ʒu
	m_posold = D3DXVECTOR3(0, 0, 0);				//�O��̈ʒu
	m_rot = D3DXVECTOR3(0, 0, 0);					//����
	m_Type = CField::FIELDTEX_NORMAL;
	m_fDepth = 0;
	m_fWidth = 0;
	m_nSplitX = 1;
	m_nSplitZ = 1;

}

//--------------------------------------------
//�t�B�[���h�N���X �f�X�g���N�^
//--------------------------------------------
CField::~CField()
{
}

//--------------------------------------------
//�t�B�[���h�̐���
//--------------------------------------------
CField *CField::Create(D3DXVECTOR3 pos, float fWidth, float fDepth, FIELDTEX tex, int nSplitX, int nSplitZ)
{
	//�t�B�[���h�|�C���^
	CField *pObjectBG;
	pObjectBG = new CField;
	//�^�C�v�̐ݒ�
	pObjectBG->m_Type = tex;

	//�����l���������� pos���
	pObjectBG->m_pos = pos;
	pObjectBG->m_fDepth = fDepth;
	pObjectBG->m_fWidth = fWidth;
	pObjectBG->m_nSplitX = nSplitX;
	pObjectBG->m_nSplitZ = nSplitZ;

	//�t�B�[���h�̏�����
	pObjectBG->Init();

	//�t�B�[���h�̏���Ԃ�
	return pObjectBG;
}

//=============================================================================
// �t�B�[���h�̏���������
//=============================================================================
HRESULT CField::Init(void)
{
	//�t�B�[���h��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_FIELD);

	m_move = D3DXVECTOR3(0, 0, 0);
	LPDIRECT3DVERTEXBUFFER9 VtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

	//���f���𐶐�	�I�t�Z�b�g�ݒ�
	m_pField = CSceneMeshField::Create(m_pos, m_fWidth,m_fDepth,m_nSplitX,m_nSplitZ);
	//���f�������蓖��
	m_pField->BindTexture(m_pTexture[m_Type]);

	return S_OK;
}

//=============================================================================
// �t�B�[���h�̏I������
//=============================================================================
void CField::Uninit(void)
{
	if (m_pField != NULL)
	{
		m_pField->Uninit();
		m_pField = NULL;
	}

	//for (int nCnt = 0; nCnt < FIELDTEX_MAX; nCnt++)
	//{
	//	if (m_pTexture[nCnt] != NULL)
	//	{
	//		m_pTexture[nCnt] = NULL;
	//	}
	//}

	//����������(�t�B�[���h��j��)
	Release();
}

//=============================================================================
// �t�B�[���h�̍X�V����
//=============================================================================
void CField::Update(void)
{
}

//=============================================================================
// �t�B�[���h�̕`�揈��
//=============================================================================
void CField::Draw(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (m_pField != NULL)
	{
		m_pField->Draw();
	}
}

//=============================================================================
// �t�B�[���h�̈ʒu�ݒ�
//=============================================================================
void CField::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CField::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCnt = 0; nCnt < FIELDTEX_MAX; nCnt++)
	{
		m_pTexture[nCnt] = NULL;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME000, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME001, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME002, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME003, &m_pTexture[3]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CField::UnLoad(void)
{
	for (int nCnt = 0; nCnt < FIELDTEX_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt] = NULL;
		}
	}
}
