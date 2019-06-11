//=============================================================================
//
// �|���S������ [Bullet.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "bullet.h"
#include "manager.h"
#include "scene3D.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_TEXTURENAME		 "data\\TEXTURE\\bullet000.png"			//�e�N�X�`���̃t�@�C����
#define TEX_POS_X_INIT			(1.0f)									//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)									//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)									//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)									//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)									//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)									//�e�N�X�`�����WV��

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9			CBullet::m_pTexture = NULL;

//--------------------------------------------
//�V�[���o���b�g�N���X �R���X�g���N�^
//--------------------------------------------
CBullet::CBullet()
{
	//�����o�ϐ�

}

//--------------------------------------------
//�V�[���o���b�g�N���X �f�X�g���N�^
//--------------------------------------------
CBullet::~CBullet()
{
}

//--------------------------------------------
//�V�[���o���b�g�̐���
//--------------------------------------------
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CBullet *pBullet;

	pBullet = new CBullet;

	pBullet->m_Bullet.move = move;
	pBullet->m_Bullet.pos = pos;
	pBullet->Init();

	return pBullet;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBullet::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CSceneBillBoard::Init();
	CSceneBillBoard::BindTexture(m_pTexture);
	CSceneBillBoard::Setpos(m_Bullet.pos);
	//�I�u�W�F�N�g��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_BILLBOARD);

	m_Bullet.nLife = 200;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBullet::Uninit(void)
{
	CSceneBillBoard::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBullet::Update(void)
{
	m_Bullet.pos = GetPos();
	m_Bullet.pos.x += m_Bullet.move.x;
	m_Bullet.pos.y += m_Bullet.move.y;
	m_Bullet.pos.z += m_Bullet.move.z;
	m_Bullet.nLife--;

	//CSceneBillBoard::Setpos(m_Bullet.pos);
	CSceneBillBoard::SetBillboard(m_Bullet.pos, 10, 10, 0);

	//�e�̃��C�t���s�����������
	if (m_Bullet.nLife <= 0)
	{
		Uninit();
	}
#if 1
	else
	{
	}

#endif

}

//=============================================================================
// �`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	CSceneBillBoard::Draw();
}
//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CBullet::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		BULLET_TEXTURENAME,
		&m_pTexture);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CBullet::UnLoad(void)
{
}
