//=============================================================================
//
// �I�u�W�F�N�g�r���{�[�h���� [billboardEnemy.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "billboardObject.h"
#include "manager.h"
#include "scene2D.h"
#include "game.h"
#include "effect.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\BILLBOARD\\tree000.png"	//�e�N�X�`���̃t�@�C����
#define TEXTURENAME001			 "data\\TEXTURE\\TITLE\\title.png"			//�e�N�X�`���̃t�@�C����
#define TEXTURENAME002			 "data\\TEXTURE\\BILLBOARD\\CAN2D.png"		//�e�N�X�`���̃t�@�C����

#define TEX_POS_X_INIT			(1.0f)									//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)									//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)									//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)									//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)									//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)									//�e�N�X�`�����WV��

#define DEPTH					(30.0f)
#define PLAYER_DEPTH			(5.0f)			//�v���C���[�̕������p
#define PLAYER_HEIGHT			(10.0f)			//�v���C���[�̔w�̍���

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9			CBillBoardObject::m_pTexture[TEXTYPE_MAX] = {};

//--------------------------------------------
//�r���{�[�h(�I�u�W�F�N�g)�N���X �R���X�g���N�^
//--------------------------------------------
CBillBoardObject::CBillBoardObject()
{
	m_pos = D3DXVECTOR3(0,0,0);				// �ʒu
	m_move = D3DXVECTOR3(0, 0, 0);			// �ړ���
	m_posold = D3DXVECTOR3(0, 0, 0);		// �O��̈ʒu
	m_fSpin = 0;							// ��]
	m_fScale = 0;							// �g��k��

}

//--------------------------------------------
//�r���{�[�h(�I�u�W�F�N�g)�N���X �f�X�g���N�^
//--------------------------------------------
CBillBoardObject::~CBillBoardObject()
{
}

//--------------------------------------------
//�r���{�[�h(�I�u�W�F�N�g)�̐���
//--------------------------------------------
CBillBoardObject *CBillBoardObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, TEXTYPE TexType)
{
	CBillBoardObject *pObject;

	pObject = new CBillBoardObject;

	pObject->m_move = move;
	pObject->m_pos = pos;
	pObject->m_TexType = TexType;
	pObject->m_fHeight = fHeight;
	pObject->m_fWidth = fWidth;
	pObject->Init();

	return pObject;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBillBoardObject::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pBillBoard = NULL;
	m_pBillBoard = CSceneBillBoard::Create(m_pos, D3DXVECTOR3(0, 0, 0), m_fWidth, m_fHeight);
	m_pBillBoard->BindTexture(m_pTexture[m_TexType]);
	m_pBillBoard->Setpos(m_pos);
	//�I�u�W�F�N�g��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_BILLBOARDOBJECT);

	m_fSpin = 0;
	m_fScale = 0;

	switch (m_TexType)
	{
	case TEXTYPE_TREE:
		//CShadow::Create(D3DXVECTOR3(m_pos.x, 1.0f, m_pos.z), 50, 50);
		break;
	case TEXTYPE_TITLE:
		CShadow::Create(D3DXVECTOR3(m_pos.x, 1.0f, m_pos.z), 100, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f), CShadow::SHADOWTYPE_NORMAL);
		break;
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBillBoardObject::Uninit(void)
{
	if (m_pBillBoard != NULL)
	{
		m_pBillBoard->Uninit();
		m_pBillBoard = NULL;
	}

	for (int nCnt = 0; nCnt < TEXTYPE_MAX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
	//����������(�j��)
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBillBoardObject::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CBillBoardObject::Draw(void)
{

}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CBillBoardObject::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCnt = 0; nCnt < TEXTYPE_MAX; nCnt++)
	{
		m_pTexture[nCnt] = NULL;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME000, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME001, &m_pTexture[1]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CBillBoardObject::UnLoad(void)
{
	for (int nCnt = 0; nCnt < TEXTYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// �����蔻�菈��
//=============================================================================
bool CBillBoardObject::CollisionBillboardObject(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
	D3DXVECTOR3 WidthMax;
	D3DXVECTOR3 WidthMin;
	WidthMax.x = m_pos.x + m_fWidth;	// �ʒu���݂̉���
	WidthMax.z = m_pos.z + DEPTH;		// �ʒu���݂̉��s��

	WidthMin.x = m_pos.x - m_fWidth;	// �ʒu���݂̉���
	WidthMin.z = m_pos.z - DEPTH;		// �ʒu���݂̉��s��


	if (pPos->x >= WidthMin.x - PLAYER_DEPTH && pPos->x <= WidthMax.x + PLAYER_DEPTH)
	{// X�͈͓̔��ɂ���
		if (pPos->z >= WidthMin.z - PLAYER_DEPTH && pPos->z <= WidthMax.z + PLAYER_DEPTH)
		{// Z�͈͓̔��ɂ���
		}
	}

	return false;
}
