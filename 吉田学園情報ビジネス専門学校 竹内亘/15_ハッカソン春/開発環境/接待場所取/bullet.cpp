//=============================================================================
//
// �e���� [bullet.cpp]
// Author : ���R���
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "camera.h"
#include "scene3D.h"
#include "meshField.h"
#include "player.h"
#include "game.h"
#include "enemy.h"
#include "effect3D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_NAME	"data\\MODEL\\sakebottle.x"	// �u���b�N�̃��f����
#define BLOCKSIZE	(15.0f)					// �u���b�N�̃T�C�Y

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPD3DXMESH CBullet::m_pMesh = NULL;		// ���b�V�����i���_���j�ւ̃|�C���^
LPD3DXBUFFER CBullet::m_pBuffMat = NULL;	// �}�e���A�����ւ̃|�C���^
DWORD CBullet::m_nNumMat = 0;			// �}�e���A�����̐�
LPDIRECT3DTEXTURE9 *CBullet::m_pTexture = 0;			// �e�N�X�`�����

//=============================================================================
// �v���C���[�N���X�̃R���X�g���N�^
//=============================================================================
CBullet::CBullet()
{
	// �l���N���A
	m_pVtxBuff = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMatrixIdentity(&m_mtxWorld);		// ���[���h�}�g���b�N�X
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_bHit = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	CBullet *pBullet = NULL;

	if (pBullet == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pBullet = new CBullet;

		if (pBullet != NULL)
		{
			pBullet->SetPosition(pos);
			pBullet->m_pos = pos;
			pBullet->m_move = move;
			pBullet->m_nLife = nLife;
			pBullet->BindModel(m_pBuffMat, m_nNumMat, m_pMesh);
			pBullet->BindMat(m_pTexture);
			pBullet->Init();
		}
	}

	return pBullet;
}

//=============================================================================
// �u���b�N����������
//=============================================================================
HRESULT CBullet::Init(void)
{
	// ����������
	CSceneX::Init();

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_BULLET);

	// �g�嗦�̐ݒ�
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_bHit = false;

	return S_OK;
}

//=============================================================================
// �u���b�N�I������
//=============================================================================
void CBullet::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// �u���b�N�X�V����
//=============================================================================
void CBullet::Update(void)
{
	CollisonBlock(&m_pos, 45.0f);

	// �e�𓮂���
	m_pos += m_move;

	m_rot.x += 0.2f;

	CSceneX::SetPosition(m_pos);
	CSceneX::SetRot(m_rot);

	// �e�̃��C�t�����炷
	m_nLife--;

	if (m_nLife <= 0)
	{//	�e�폜
		m_bHit = true;
	}

	if (m_bHit == true)
	{
		Uninit();
	}
}

//=============================================================================
// �u���b�N�`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}


	// ���_�@���̎������K��	�J�n
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	CSceneX::Draw();

	// ���_�@���̎������K��	�I��
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

}

//=============================================================================
// �u���b�N�Ƃ̓����蔻�菈��
//=============================================================================
bool CBullet::Collision(D3DXVECTOR3 *pos, float fRadius)
{
	bool bHit = false;	// �������Ă��Ȃ����

						// ���S�ƒ��S�̍������߂�
	D3DXVECTOR3 DiffLength = D3DXVECTOR3(pos->x - m_pos.x, pos->y - m_pos.y, pos->z - m_pos.z);

	// ���S���璆�S�̃x�N�g���̒������Z�o
	float distance = sqrtf((DiffLength.x * DiffLength.x) + (DiffLength.y * DiffLength.y) + (DiffLength.z * DiffLength.z));

	if (distance < fRadius + m_VtxMax.x && distance < fRadius + m_VtxMax.y && distance < fRadius + m_VtxMax.z)
	{// ���������a�̘a��菬������Γ������Ă���
		bHit = true;
	}

	return bHit;	// �u���b�N�ɓ������Ă��邩�ǂ�����Ԃ�
}

//=============================================================================
// �u���b�N�̔j��̔���
//=============================================================================
void CBullet::CollisonBlock(D3DXVECTOR3 *pos, float fRadius)
{
	// ���[�h�̎擾
	CManager::MODE mode;
	mode = CManager::GetMode();
	//�G�t�F�N�g�p�֐�
	D3DXVECTOR3 RotRand;
	D3DXVECTOR3 PosRand;
	D3DXVECTOR3 effectmove;
	//�A�C�e���̐����Z�b�g
	CUIEnemy *m_pUIEnemy = CGame::GetUIEnemy ();
	//�T�E���h�����擾
	CSound *pSound = CManager::GetSound(0);
	//�T�E���h�����擾
	CSound *pSound2 = CManager::GetSound(1);

	CScene *pScene = NULL;

	// �擪�̃I�u�W�F�N�g���擾
	pScene = CScene::GetTop(6);

	while (pScene != NULL)
	{// �D�揇�ʂ�3�̃I�u�W�F�N�g��1��1�m���߂�
	 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// ���S�t���O�������Ă��Ȃ�����
			if (pScene->GetObjType() == CScene::OBJTYPE_ENEMY)
			{// �I�u�W�F�N�g�̎�ނ��m���߂�
				if (((CEnemy*)pScene)->Collision(pos, fRadius) == true)
				{
					if (((CEnemy*)pScene)->GetMotionState() != CEnemy::MOTIONSTATE_DAMAGE)
					{
						pSound->PlaySound(pSound->SOUND_LABEL_SE_DAMAGE);
						pSound2->PlaySound(pSound->SOUND_LABEL_SE_BREAK);
						m_pUIEnemy->PlusEnemy(1);
						((CEnemy*)pScene)->SetMotionState(CEnemy::MOTIONSTATE_DAMAGE);
						// �G�l�~�[�폜
						//((CEnemy*)pScene)->Uninit();

						for (int nCnt = 0; nCnt < 10; nCnt++)
						{
							//�����_���Ȓl
							RotRand.x = (float)(rand() % 20 - 10);
							PosRand.y = (float)(rand() % 20);
							PosRand.x = (float)(rand() % 50 - 25);
							//�ړ��ʂ̐ݒ�
							effectmove.x = (float)(rand() % 20 - 10);
							effectmove.y = (float)(rand() % 20 - 10);
							effectmove.z = (float)(rand() % 20 - 10);
							//�G�t�F�N�g�𐶐�
							C3DEffect::Create(D3DXVECTOR3(m_pos.x + PosRand.x, m_pos.y + PosRand.y, m_pos.z + 50), effectmove,
								D3DXVECTOR3(sinf(RotRand.x), sinf(RotRand.x), sinf(RotRand.x)), C3DEffect::EFFECTTYPE_BIN000, 30);
						}

						m_bHit = true;
					}
				}
			}
		}

		// ���̃V�[���ɐi�߂�
		pScene = pSceneNext;
	}
}

//=============================================================================
// �u���b�N�̃��f���ǂݍ��ݏ���
//=============================================================================
HRESULT CBullet::LoadModel(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(BULLET_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	return S_OK;
}

//=============================================================================
// �u���b�N�̃��f���������
//=============================================================================
void CBullet::UnloadModel(void)
{
	// ���b�V���̊J��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// �}�e���A���̊J��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//=============================================================================
// �ʒu�̎擾
//=============================================================================
D3DXVECTOR3 CBullet::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void CBullet::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}