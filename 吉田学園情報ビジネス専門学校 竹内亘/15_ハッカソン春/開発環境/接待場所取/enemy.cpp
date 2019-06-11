//---------------------------------------------------------------------
//	�G�l�~�[����(enemy.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "enemy.h"
#include "manager.h"
#include "game.h"
#include "camera.h"
#include "fade.h"
#include "scene3D.h"
#include "meshField.h"
#include "model.h"
#include "objectBG.h"
#include "billboardEnemy.h"
#include "billboardItem.h"
#include "effect.h"
#include "UIGauge.h"
#include "UITime.h"
#include "UILife.h"
#include "UIItem.h"
#include "UIPressEnter.h"
#include "UIFinish.h"
#include "UIStart.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define FILE_NAME						("data\\TEXT\\EnemyMotion.txt")
#define MOVE_ENEMY						(9.5f)		//�ړ���
#define MOVE_ENEMY_DASH					(3.0f)		//�_�b�V�����̉��Z�ړ���
#define FIELD_SIZE						(100.0f)	//�t�B�[���h�̑傫��

#define TIMER_JUMP						(60)		//�S�[�����̃W�����v�܂ł̃^�C�}�[
#define RUN_FRAME						(2.0f)		//�����Ă���Ƃ��̃t���[��������l
#define APPEAR_FRAME					(15)		//���G����
#define COLLISION_SIZE					(0.0f)		//�����蔻��̑傫��

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPD3DXMESH					CEnemy::m_pMeshModel[MAX_PARTS] = {};
LPD3DXBUFFER				CEnemy::m_pBuffMatModel[MAX_PARTS] = {};
LPDIRECT3DTEXTURE9			CEnemy::m_pTextureModel[MAX_PARTS] = {};
DWORD						CEnemy::m_nNumMatModel[MAX_PARTS] = {};
int							CEnemy::m_nNumParts = 0;					//�p�[�c��
CEnemy::MOTION_INFO			CEnemy::m_aMotionInfo[MAX_MOTION];		//���[�V�������
D3DXVECTOR3					CEnemy::m_OffSetPos[MAX_PARTS];			//�I�t�Z�b�g���(���[�V����)
CEnemy::KEY_INFO			*CEnemy::m_pKeyInfo[MAX_MOTION];		//�L�[���ւ̃|�C���^
CEnemy::KEY					CEnemy::m_aKayOffset[MAX_PARTS];		//�I�t�Z�b�g���
int							CEnemy::m_aIndexParent[MAX_PARTS];		//�e�̃C���f�b�N�X

//--------------------------------------------
//�O���[�o���ϐ�
//--------------------------------------------
int g_nNumModelEnemy;
char g_aFileNameModelEnemy[MAX_PARTS][256];

//--------------------------------------------
//�G�l�~�[�N���X �R���X�g���N�^
//--------------------------------------------
CEnemy::CEnemy() : CScene(6, CScene::OBJTYPE_ENEMY)
{
	m_bJump = false;
	m_pos = D3DXVECTOR3(0, 0, 0);					//�ʒu
	m_posold = D3DXVECTOR3(0, 0, 0);				//�O��̈ʒu
	m_move = D3DXVECTOR3(0, 0, 0);					//�ړ���
	m_rot = D3DXVECTOR3(0, 0, 0);					//����
	m_State = ENEMYSTATE_NONE;						//���
	m_nGameEndCnt = 0;								//�J�E���g
	m_nJumpEndTimer = 0;
	m_nStartTimer = 0;
	m_nCntTumble = 0;
	D3DXMatrixIdentity(&m_mtxWorld);				//���[���h�}�g���b�N�X



	m_nKey = 0;							//���݂̃L�[�i���o�[
	m_nCountFlame = 0;					//�t���[����
	m_nCntTimer = 0;
	m_nCntAppear = 0;
	m_MotionState = MOTIONSTATE_NEUTRAL;
	m_DashState = DASHSTATE_NORMAL;
	m_bFinish = false;
	m_bStart = false;
	m_bMotionEnd = false;
}

//--------------------------------------------
//�G�l�~�[�N���X �f�X�g���N�^
//--------------------------------------------
CEnemy::~CEnemy()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLength)
{
	//�G�l�~�[�|�C���^
	CEnemy *pPlayer;
	pPlayer = new CEnemy;
	//�G�l�~�[�̏�����
	pPlayer->Init();
	//�����l����������
	pPlayer->m_pos = pos;
	pPlayer->m_rot = rot;
	pPlayer->m_fDestAngle = rot.y;
	//�G�l�~�[�̏���Ԃ�
	return pPlayer;
}

//=============================================================================
// �G�l�~�[�̏���������
//=============================================================================
HRESULT CEnemy::Init(void)
{
	//�I�u�W�F�N�g��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_ENEMY);

	//m_rot = D3DXVECTOR3(0, D3DX_PI * 1.0f, 0);
	m_move = D3DXVECTOR3(0, 0, 0);
	//m_fDestAngle = D3DX_PI * 1.0f;
	m_fDiffAngle = 0;							//�G�l�~�[�̌���
	m_bJump = false;							//�W�����v�̏��
	m_bFinish = false;							//�S�[���t���O
	m_bStart = false;							//�X�^�[�g�t���O
	LPDIRECT3DVERTEXBUFFER9 VtxBuff = NULL;		//���_�o�b�t�@�ւ̃|�C���^
	m_State = ENEMYSTATE_NEUTRAL;				//�ŏ��̃��[�V�����̏��
	m_nGameEndCnt = 0;							//�Q�[���I���܂ł̃J�E���g
	m_nJumpEndTimer = 0;						//�Q�[�����I���܂ŃW�����v����^�C�}�[
	m_nStartTimer = 0;							//�X�^�[�g���ɏ����҂��ăX�^�[�g����^�C�}�[
	m_nCntTumble = 0;							//��]�̐��𐔂���
	m_nCntAppear = 0;

	//���[�V�����p�ϐ�
	m_nKey = 0;			//���݂̃L�[
	m_nCountFlame = 0;	//���݂̃t���[��
	m_nMotionType = 0;	//���݂̃��[�V�����^�C�v
	m_nOldMotion = 0;	//�O�̃��[�V����
	m_nCntTimer = 0;	//�^�C�g���J�����̏��


	for (int nIndex = 0; nIndex < g_nNumModelEnemy; nIndex++)
	{
		//���f���𐶐�	�I�t�Z�b�g�ݒ�
		m_apModel[nIndex] = CModel::Create(
			D3DXVECTOR3(m_pos.x + m_aKayOffset[nIndex].fposX,
				m_pos.y + m_aKayOffset[nIndex].fposY,
				m_pos.z + m_aKayOffset[nIndex].fposZ),
			D3DXVECTOR3(m_rot.x + m_aKayOffset[nIndex].frotX,
				m_rot.y + m_aKayOffset[nIndex].frotY,
				m_rot.z + m_aKayOffset[nIndex].frotZ));

		//pos����
		m_OffSetPos[nIndex] = m_apModel[nIndex]->GetPos();

		//���f�������蓖��
		m_apModel[nIndex]->BindModel(m_nNumMatModel[nIndex], m_pMeshModel[nIndex], m_pBuffMatModel[nIndex]);

		if (m_aIndexParent[nIndex] == -1)
		{
			//���f���̐e���w��
			m_apModel[nIndex]->SetParent(NULL);
		}
		else
		{
			//���f���̐e���w��
			m_apModel[nIndex]->SetParent(m_apModel[m_aIndexParent[nIndex]]);
		}
	}
	//���[�V�����̏��
	m_MotionState = MOTIONSTATE_NEUTRAL;
	m_DashState = DASHSTATE_NORMAL;

	m_effectCol = D3DXCOLOR(0, 0, 0, 1);


		//CEnemy::Create(D3DXVECTOR3(pPlayer->GetPos().x, 0, pPlayer->GetPos().z - 200), D3DXVECTOR3(0, D3DX_PI * 1.0f, 0), 10);

	return S_OK;
}

//=============================================================================
// �G�l�~�[�̏I������
//=============================================================================
void CEnemy::Uninit(void)
{
	//for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	//{
	//	if (m_apModel[nCnt] != NULL)
	//	{
	//		m_apModel[nCnt]->Uninit();
	//		delete m_apModel[nCnt];
	//		m_apModel[nCnt] = NULL;
	//	}
	//}

	//for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
	//{
	//	if (m_pKeyInfo[nCnt] != NULL)
	//	{
	//		m_pKeyInfo[nCnt] = NULL;		//�L�[���ւ̃|�C���^
	//	}
	//}

	//����������(�G�l�~�[��j��)
	Release();
}

//=============================================================================
// �G�l�~�[�̍X�V����
//=============================================================================
void CEnemy::Update(void)
{
#if 1
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//�W���C�p�b�h�����擾
	CInputJoypad *pInputJoypad = CManager::GetCInputJoypad();
	//���݂̃��[�h���擾
	CManager::MODE mode = CManager::GetMode();
	//�J�����擾
	CCamera *pCamera = CManager::GetCamera();
	//�T�E���h�����擾
	CSound *pSound = CManager::GetSound(2);

	//�G�t�F�N�g�p�֐�
	D3DXVECTOR3 RotRand;
	D3DXVECTOR3 PosRand;
	D3DXVECTOR3 effectmove;

	//�O��̈ʒu��ۑ�
	m_posold = m_pos;

	switch (mode)
	{
	case CManager::MODE_TITLE:
		break;
	case CManager::MODE_TUTORIAL:
		break;
	case CManager::MODE_GAME:
#if 1
		if (m_State == ENEMYSTATE_NEUTRAL)
		{
			m_State = ENEMYSTATE_NORMAL;
			m_MotionState = MOTIONSTATE_RUN;

		}

		if (m_State == ENEMYSTATE_NORMAL || m_State == ENEMYSTATE_APPEAR)
		{

			if (m_State == ENEMYSTATE_APPEAR)
			{
				m_nCntAppear++;
				if (m_nCntAppear > APPEAR_FRAME)
				{
					m_State = ENEMYSTATE_NORMAL;
					m_nCntAppear = 0;
				}
			}

			if (m_bJump == false && m_MotionState == MOTIONSTATE_RUN)
			{
				//���[�V�����؂�ւ�
				m_nMotionType = 1;
				m_MotionState = MOTIONSTATE_RUN;
			}
			//�����ړ�
			m_move.x += sinf(pCamera->GetCamera().rotCamera.y) * MOVE_ENEMY;
			m_move.z += cosf(pCamera->GetCamera().rotCamera.y) * MOVE_ENEMY;
		}

#endif
		break;

	case CManager::MODE_RESULT:
		break;
	}

	//�����̊���
	m_fDiffAngle = m_fDestAngle - m_rot.y;
	//�p�x�̐ݒ�
	if (m_fDiffAngle > D3DX_PI)
	{
		m_fDiffAngle -= D3DX_PI* 2.0f;
	}
	if (m_fDiffAngle < -D3DX_PI)
	{
		m_fDiffAngle += D3DX_PI* 2.0f;
	}
	m_rot.y += m_fDiffAngle * 0.1f;
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI* 2.0f;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI* 2.0f;
	}

	//�d��
	//m_move.y -= cosf(D3DX_PI * 0) * 0.7f;

	//����
	m_move.x += (0.0f - m_move.x) * 0.5f;
	m_move.z += (0.0f - m_move.z) * 0.5f;
	//�ʒu�X�V
	m_pos += m_move;

	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		if (m_pos.x > 500.0f)
		{
			m_pos.x = 500;
		}
		else if (m_pos.x < -500.0f)
		{
			m_pos.x = -500;
		}
	}

	//���[�V�����X�V
	UpdateMotion();

	//�n�ʂƂ̓����蔻��
	CollisitionGround();
	// �I�u�W�F�N�g�̓����蔻��
	CollisitionObject3D(&m_pos, &m_posold, &m_move);

//#ifdef  _DEBUG
//	CDebugProc::Print(1, " �G�l�~�[�̈ʒu  : ( %.1f ,%.1f ,%.1f )\n", m_pos.x, m_pos.y, m_pos.z);
//	CDebugProc::Print(1, " Num�L�[  : (%d)\n", m_nKey);
//	CDebugProc::Print(1, " m_nCountFlame  : (%d)\n", m_nCountFlame);
//	CDebugProc::Print(1, " m_nMotionType  : (%d)\n", m_nMotionType);
//	CDebugProc::Print(1, " m_MotionState  : (%d)\n", m_MotionState);
//	CDebugProc::Print(1, " m_bMotionEnd   : (%s)\n", m_bMotionEnd ? "true" : "false");
//
//#endif
#endif
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		//�v���C���[���擾
		CPlayer *pPlayer = CGame::GetPlayer();
		//���ɍs�����Ƃ�����
		if (pPlayer->GetPos().z - 500 > m_pos.z)
		{
			Uninit();
		}
	}
}

//=============================================================================
// �G�l�~�[�̕`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�e�̕`�揈��
	D3DXMATRIX	mtxShadow;
	D3DXPLANE	planeField;
	D3DXVECTOR4 VecLight;
	D3DXVECTOR3 pos, normal;

	CLight *pLight = CManager::GetLight();

	//���Z����
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���C�g�𖳌��ɂ���
	pDevice->LightEnable(0, FALSE);
	pDevice->LightEnable(1, FALSE);
	pDevice->LightEnable(2, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�V���h�E�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);
	//���C�g�̐ݒ�
	VecLight = D3DXVECTOR4(0.0f, 1.0f, -1.0f, 0.0f);
	//�e�̈ʒu�ݒ�
	pos = D3DXVECTOR3(0.0f, 1.5f, 0.0f);
	//�@���̐ݒ�
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//���ʂ��쐬
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	//�e�}�g���b�N�X�̐ݒ�
	D3DXMatrixShadow(&mtxShadow, &VecLight, &planeField);
	//���[���h�}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->m_bShadow = true;
			m_apModel[nCnt]->Draw();
		}
	}

	//�����_�[�X�e�C�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
	pDevice->LightEnable(1, TRUE);
	pDevice->LightEnable(2, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->m_bShadow = false;
			m_apModel[nCnt]->Draw();
		}
	}
}

//=============================================================================
// �G�l�~�[�̈ʒu�ݒ�
//=============================================================================
void CEnemy::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CEnemy::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		m_pMeshModel[nCnt] = NULL;
		m_pBuffMatModel[nCnt] = NULL;
		m_pTextureModel[nCnt] = NULL;
		m_nNumMatModel[nCnt] = NULL;
	}

	for (int nCnt = 0; nCnt < MAX_MOTION; nCnt++)
	{
		m_pKeyInfo[nCnt] = NULL;		//�L�[���ւ̃|�C���^
	}

	//�G�l�~�[���̓ǂݍ���
	FileLoad();

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j������
//=============================================================================
void CEnemy::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		// ���b�V���̊J��
		if (m_pMeshModel[nCnt] != NULL)
		{
			m_pMeshModel[nCnt]->Release();
			m_pMeshModel[nCnt] = NULL;
		}
		// �}�e���A���̊J��
		if (m_pBuffMatModel[nCnt] != NULL)
		{
			m_pBuffMatModel[nCnt]->Release();
			m_pBuffMatModel[nCnt] = NULL;
		}

		//�e�N�X�`���̔j��
		if (m_pTextureModel[nCnt] != NULL)
		{
			m_pTextureModel[nCnt]->Release();
			m_pTextureModel[nCnt] = NULL;
		}
	}
}

//=============================================================================
// �u���b�N�Ƃ̓����蔻�菈��
//=============================================================================
bool CEnemy::Collision(D3DXVECTOR3 *pos, float fRadius)
{
	bool bHit = false;	// �������Ă��Ȃ����

						// ���S�ƒ��S�̍������߂�
	D3DXVECTOR3 DiffLength = D3DXVECTOR3(pos->x - m_pos.x, pos->y - m_pos.y - 20.0f, pos->z - m_pos.z);

	// ���S���璆�S�̃x�N�g���̒������Z�o
	float distance = sqrtf((DiffLength.x * DiffLength.x) + (DiffLength.y * DiffLength.y) + (DiffLength.z * DiffLength.z));

	if (distance < fRadius + COLLISION_SIZE && distance < fRadius + COLLISION_SIZE && distance < fRadius + COLLISION_SIZE)
	{// ���������a�̘a��菬������Γ������Ă���
		bHit = true;
	}

	return bHit;	// �u���b�N�ɓ������Ă��邩�ǂ�����Ԃ�
}

//=============================================================================
// �G�l�~�[�̃_���[�W
//=============================================================================
void CEnemy::HitDamage(int nDamage)
{

}
//=============================================================================
// �G�l�~�[�̈ʒu
//=============================================================================
D3DXVECTOR3 CEnemy::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �G�l�~�[�̉�]
//=============================================================================
D3DXVECTOR3 CEnemy::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// �G�l�~�[�̈ړ�
//=============================================================================
D3DXVECTOR3 CEnemy::GetMove(void)
{
	return m_move;
}

//=============================================================================
//	�G�l�~�[�̃��[�V�����̏�Ԃ��擾
//=============================================================================
CEnemy::MOTIONSTATE CEnemy::GetMotionState(void)
{
	return m_MotionState;
}

//=============================================================================
//	�G�l�~�[�̃��[�V�����̏�Ԃ�ݒ�
//=============================================================================
void CEnemy::SetMotionState(MOTIONSTATE MotionState)
{
	//���[�V�����؂�ւ�
	m_nCountFlame = 0;
	m_nKey = 0;
	m_bMotionEnd = false;
	m_MotionState = MotionState;
	m_nMotionType = (int)MotionState;

	if (m_MotionState == MOTIONSTATE_DAMAGE)
	{
		m_State = ENEMYSTATE_DAMAGE;
	}
}

//=============================================================================
//	�G�l�~�[�̏�Ԃ��擾
//=============================================================================
CEnemy::ENEMYSTATE CEnemy::GetPlayerState(void)
{
	return m_State;
}

//=============================================================================
//	�G�l�~�[�̃p�[�c�����擾
//=============================================================================
CModel *CEnemy::GetapModel(int nIdx)
{
	return m_apModel[nIdx];
}

//=============================================================================
//	���̓����蔻��
//=============================================================================
void CEnemy::CollisitionGround(void)
{
	CScene *pScene;

	//�v���C�I���e�B�[�`�F�b�N
	pScene = CScene::GetTop(3);

	//�W�����v��false��
	//m_bJump = false;

	//NULL�`�F�b�N
	while (pScene != NULL)
	{
		//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//�^�C�v�����b�V����������
			if (pScene->GetObjType() == OBJTYPE_MESHFIELD)
			{
				//�G�l�~�[��Hight������
				if (((CSceneMeshField*)pScene)->GetHeightbool(m_pos))
				{
					//�W�����v���Ă��Ȃ���Ԃɂ���
					m_bJump = false;
					//�������Ƃ���move������������
					m_move.y = 0.0f;
				}
			}
		}
		//Next�Ɏ���Scene������
		pScene = pSceneNext;
	}
}

//=============================================================================
//	�I�u�W�F�N�g�̓����蔻��
//=============================================================================
void CEnemy::CollisitionObject3D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	CScene *pScene;

	//�v���C�I���e�B�[�`�F�b�N
	pScene = CScene::GetTop(3);

	//�ϐ��錾
	bool bLand = false;

	//bLand�̏���������
	m_bLand = false;

	//NULL�`�F�b�N
	while (pScene != NULL)
	{
		//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//�^�C�v���I�u�W�F�N�g��������
			if (pScene->GetObjType() == OBJTYPE_BGMODEL)
			{
				//�I�u�W�F�N�g�̂����锻��
				bLand = ((CObjectBG*)pScene)->CollisionObject(pPos, pPosOld, pMove);
				//���n�����L����
				if (bLand)
				{
					m_bJump = false;
					m_bLand = bLand;
				}
			}
		}

		//Next�Ɏ���Scene������
		pScene = pSceneNext;
	}
}


//=============================================================================
// �G�l�~�[�̃��[�V����
//=============================================================================
void CEnemy::UpdateMotion(void)
{
	//�T�E���h�����擾
	//CSound *pSound = CManager::GetSound();
	CSound *pSound = CManager::GetSound(2);

	//���[�V����
	KEY *pKey, *pNextKey;
	float fRateMotion;
	float fDiffMotion;
	float fPlusData;
	float fMinusData;
	float fPlusPos;
	float fMinusPos;

	D3DXVECTOR3 rotmotion;
	D3DXVECTOR3 posmotion;
	D3DXVECTOR3 BodyRot;

	//�G�t�F�N�g�p�֐�
	D3DXVECTOR3 RotRand;
	D3DXVECTOR3 PosRand;
	D3DXVECTOR3 effectmove;


	//�L�[���ő吔������Ȃ��悤��
	if (m_aMotionInfo[m_nMotionType].nNumKey <= m_nKey)
	{
		m_nKey = 0;
	}

	//���[�V�����X�V
	for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
	{
		if (m_apModel[nCntParts] != NULL)
		{
			//���݂̃L�[���擾
			pKey = &m_pKeyInfo[m_nMotionType][m_nKey].aKey[nCntParts];
			//���̃L�[���擾
			pNextKey = &m_pKeyInfo[m_nMotionType][(m_nKey + 1) % m_aMotionInfo[m_nMotionType].nNumKey].aKey[nCntParts];
			//�����Ԃ̎��̓��[�V�����̃t���[�������炷
			if (m_DashState == DASHSTATE_DASH && m_MotionState == MOTIONSTATE_RUN)
			{
				//���݂̃L�[���玟�̃L�[�ւ̍Đ��t���[�����ɂ����郂�[�V�����J�E���^�[�̑��Βl���Z�o
				fRateMotion = (float)m_nCountFlame / (float)(m_pKeyInfo[m_nMotionType][m_nKey].nFrame / 2.0f);
			}
			else
			{
				//���݂̃L�[���玟�̃L�[�ւ̍Đ��t���[�����ɂ����郂�[�V�����J�E���^�[�̑��Βl���Z�o
				fRateMotion = (float)m_nCountFlame / (float)m_pKeyInfo[m_nMotionType][m_nKey].nFrame;
			}
			//ROT

			if (nCntParts == 0)
			{
				fPlusData = pNextKey->frotX + pKey->frotX;
				fMinusData = pNextKey->frotX - pKey->frotX;
				fPlusPos;
				fMinusPos;

				//�l���o��(��Βl)
				fPlusData = abs(fPlusData);
				fMinusData = abs(fMinusData);
				//�����������ق�
				if (fPlusData < fMinusData)
				{	//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
					fDiffMotion = pNextKey->frotX + pKey->frotX;
					//���Βl���������g���Ċe�v�f�̒l���Z�o
					rotmotion.x = pKey->frotX + (fDiffMotion * fRateMotion);
				}
				else
				{	//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
					fDiffMotion = pNextKey->frotX - pKey->frotX;
					//���Βl���������g���Ċe�v�f�̒l���Z�o
					rotmotion.x = pKey->frotX + (fDiffMotion * fRateMotion);
				}

				fPlusData = pNextKey->frotY + pKey->frotY;
				fMinusData = pNextKey->frotY - pKey->frotY;
				//�l���o��(��Βl)
				fPlusData = abs(fPlusData);
				fMinusData = abs(fMinusData);
				//�����������ق�
				if (fPlusData < fMinusData)
				{	//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
					fDiffMotion = pNextKey->frotY + pKey->frotY;
					//���Βl���������g���Ċe�v�f�̒l���Z�o
					rotmotion.y = pKey->frotY + (fDiffMotion * fRateMotion);
				}
				else
				{	//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
					fDiffMotion = pNextKey->frotY - pKey->frotY;
					//���Βl���������g���Ċe�v�f�̒l���Z�o
					rotmotion.y = pKey->frotY + (fDiffMotion * fRateMotion);
				}

				fPlusData = pNextKey->frotZ + pKey->frotZ;
				fMinusData = pNextKey->frotZ - pKey->frotZ;
				//�l���o��(��Βl)
				fPlusData = abs(fPlusData);
				fMinusData = abs(fMinusData);
				//�����������ق�
				if (fPlusData < fMinusData)
				{	//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
					fDiffMotion = pNextKey->frotZ + pKey->frotZ;
					//���Βl���������g���Ċe�v�f�̒l���Z�o
					rotmotion.z = pKey->frotZ + (fDiffMotion * fRateMotion);
				}
				else
				{	//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
					fDiffMotion = pNextKey->frotZ - pKey->frotZ;
					//���Βl���������g���Ċe�v�f�̒l���Z�o
					rotmotion.z = pKey->frotZ + (fDiffMotion * fRateMotion);
				}

				//POS
				//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->fposX - pKey->fposX;
				//���Βl���������g���Ċe�v�f�̒l���Z�o
				posmotion.x = pKey->fposX + (fDiffMotion * fRateMotion);
				//POS
				//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->fposY - pKey->fposY;
				//���Βl���������g���Ċe�v�f�̒l���Z�o
				posmotion.y = pKey->fposY + (fDiffMotion * fRateMotion);
				//POS
				//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->fposZ - pKey->fposZ;
				//���Βl���������g���Ċe�v�f�̒l���Z�o
				posmotion.z = pKey->fposZ + (fDiffMotion * fRateMotion);
			}
			else
			{
				//ROT
				//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->frotX - pKey->frotX;
				//���Βl���������g���Ċe�v�f�̒l���Z�o
				rotmotion.x = pKey->frotX + (fDiffMotion * fRateMotion);
				//POS
				//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->fposX - pKey->fposX;
				//���Βl���������g���Ċe�v�f�̒l���Z�o
				posmotion.x = pKey->fposX + (fDiffMotion * fRateMotion);

				//ROT
				//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->frotY - pKey->frotY;
				//���Βl���������g���Ċe�v�f�̒l���Z�o
				rotmotion.y = pKey->frotY + (fDiffMotion * fRateMotion);
				//POS
				//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->fposY - pKey->fposY;
				//���Βl���������g���Ċe�v�f�̒l���Z�o
				posmotion.y = pKey->fposY + (fDiffMotion * fRateMotion);

				//ROT
				//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->frotZ - pKey->frotZ;
				//���Βl���������g���Ċe�v�f�̒l���Z�o
				rotmotion.z = pKey->frotZ + (fDiffMotion * fRateMotion);
				//POS
				//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
				fDiffMotion = pNextKey->fposZ - pKey->fposZ;
				//���Βl���������g���Ċe�v�f�̒l���Z�o
				posmotion.z = pKey->fposZ + (fDiffMotion * fRateMotion);
			}
			//�p�[�c�𓮂���
			m_apModel[nCntParts]->Setrot(rotmotion);
			//�I�t�Z�b�g�̈ʒu��ݒ�
			m_apModel[nCntParts]->Setpos(D3DXVECTOR3(m_OffSetPos[nCntParts].x + posmotion.x,
				m_OffSetPos[nCntParts].y + posmotion.y,
				m_OffSetPos[nCntParts].z + posmotion.z));
		}
	}

	//���[�v�̔���
	switch (m_aMotionInfo[m_nMotionType].bLoop)
	{
	case true:
		//���[�v����
		//�t���[����i�߂�
		m_nCountFlame++;

		RotRand.x = (float)(rand() % 100);
		RotRand.y = (float)(rand() % 100);
		effectmove.x = sinf(RotRand.y + 1) * 0.5f;
		effectmove.y = sinf(RotRand.y + 1) * 0.1f;
		effectmove.z = RotRand.x * -0.05f;

		m_effectCol = D3DXCOLOR(1, 1, 1, 1);

		//�L�[�̍X�V
		if (m_DashState == DASHSTATE_DASH)
		{
			if (m_nCountFlame >= m_pKeyInfo[m_nMotionType][m_nKey].nFrame / 2.0f)
			{
				if (m_aMotionInfo[m_nMotionType].nNumKey - 1 == m_nKey)
				{
					m_nKey = 0;
				}
				else
				{
					m_nKey += 1;
				}
				m_nCountFlame = 0;
			}
		}
		else
		{
			if (m_nCountFlame >= m_pKeyInfo[m_nMotionType][m_nKey].nFrame)
			{
				if (m_aMotionInfo[m_nMotionType].nNumKey - 1 == m_nKey)
				{
					//�L�[�̏�����
					m_nKey = 0;
				}
				else
				{
					//�L�[�̍X�V
					m_nKey += 1;
				}
				m_nCountFlame = 0;
			}
		}

		break;
	case false:
		//���[�v���Ȃ�
		if (m_aMotionInfo[m_nMotionType].nNumKey - 1 > m_nKey)
		{//�t���[����i�߂�
			m_nCountFlame++;
		}
		else if (m_aMotionInfo[m_nMotionType].nNumKey - 1 == m_nKey)
		{
			m_bMotionEnd = true;
			if (m_MotionState == MOTIONSTATE_DAMAGE)
			{

			}

		}
		//�L�[�̍X�V
		if (m_nCountFlame >= m_pKeyInfo[m_nMotionType][m_nKey].nFrame)
		{
			if (m_aMotionInfo[m_nMotionType].nNumKey > m_nKey)
			{
				m_nKey += 1;
			}
			m_nCountFlame = 0;
		}

		break;
	}

}

//=============================================================================
// �t�@�C���ǂݍ���
//=============================================================================
void CEnemy::FileLoad(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�t�@�C���ǂݍ��ݗp�ϐ�
	FILE *pFile;		//�t�@�C���|�C���^
	char *pStrcur;		//���݂̐擪�̕�����
	char aLine[256];	//������
	char aStr[256];		//�ꎞ�ۑ�������
	int nIndex = 0;		//���݂̃C���f�b�N�X
	int nWord = 0;		//�|�b�v�ŕԂ��ꂽ�l��ێ�
	//int	m_nNumParts;					//�p�[�c��
	//int	aIndexParent[MAX_PARTS];		//�e�̃C���f�b�N�X
	//KEY	m_aKayOffset[MAX_PARTS];		//�I�t�Z�b�g���


	D3DXVECTOR3 ParentPos;	//�e�̈ʒu�����擾
#if 1
	//�t�@�C�����J�� �ǂݍ���
	pFile = fopen(FILE_NAME, "r");
	//NULL�`�F�b�N
	if (pFile != NULL)
	{
		for (int nCntMotion = 0; nCntMotion < MAX_MOTION; nCntMotion++)
		{
			//������̐擪��ݒ�
			pStrcur = ReadLine(pFile, &aLine[0]);
			//����������o��
			strcpy(aStr, pStrcur);

			//������̃f�[�^ ��r���镶���� ��r���镶����
			if (memcmp(pStrcur, "NUM_MODEL = ", strlen("NUM_MODEL = ")) == 0)
			{
				//���o��
				pStrcur += strlen("NUM_MODEL = ");
				//������̐擪��ݒ�
				strcpy(aStr, pStrcur);
				//�����񔲂��o��
				g_nNumModelEnemy = atoi(pStrcur);

				for (int nCntModel = 0; nCntModel < g_nNumModelEnemy; nCntModel++)
				{
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
					//����������߂�
					strcpy(aStr, pStrcur);
					if (memcmp(pStrcur, "MODEL_FILENAME = ", strlen("MODEL_FILENAME = ")) == 0)
					{
						//���o��
						pStrcur += strlen("MODEL_FILENAME = ");

						//�������ݒ�
						strcpy(aStr, pStrcur);

						//�K�v�ȕ�����̍Ō�̕����܂ł̕������𐔂���
						int nNullNum = PopString(pStrcur, &aStr[0]);

						//����������߂�
						strcpy(aStr, pStrcur);

						//�Ō�̕�����NULL����������
						aStr[nNullNum - 1] = '\0';

						//�Ώۂ̕����񂩂甲���o��
						strcpy(&g_aFileNameModelEnemy[nCntModel][0], aStr);

						// X�t�@�C���̓ǂݍ���
						D3DXLoadMeshFromX(&g_aFileNameModelEnemy[nCntModel][0],
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&m_pBuffMatModel[nCntModel],
							NULL,
							&m_nNumMatModel[nCntModel],
							&m_pMeshModel[nCntModel]);
					}
				}
				//������̐擪��ݒ�
				pStrcur = ReadLine(pFile, &aLine[0]);
				//����������o��
				strcpy(aStr, pStrcur);
			}


			//������̃f�[�^ ��r���镶���� ��r���镶����
			if (memcmp(pStrcur, "CHARACTERSET", 12) == 0)
			{
				while (1)
				{
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
					//����������o��
					strcpy(aStr, pStrcur);
					if (memcmp(pStrcur, "NUM_PARTS = ", strlen("NUM_PARTS = ")) == 0)
					{
						//���o��
						pStrcur += strlen("NUM_PARTS = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);
						//�����񔲂��o��
						m_nNumParts = atoi(pStrcur);
					}
					if (memcmp(pStrcur, "PARTSSET", strlen("PARTSSET")) == 0)
					{
						while (1)
						{
							//������̐擪��ݒ�
							pStrcur = ReadLine(pFile, &aLine[0]);

							//INDEX��ǂݍ���
							if (memcmp(pStrcur, "INDEX = ", strlen("INDEX = ")) == 0)
							{
								//���o��
								pStrcur += strlen("INDEX = ");
								//������̐擪��ݒ�
								strcpy(aStr, pStrcur);
								//�����񔲂��o��
								nIndex = atoi(pStrcur);
							}
							//PARENT��ǂݍ���
							if (memcmp(pStrcur, "PARENT = ", strlen("PARENT = ")) == 0)
							{
								//���o��
								pStrcur += strlen("PARENT = ");
								//������̐擪��ݒ�
								strcpy(aStr, pStrcur);
								//�����񔲂��o��
								m_aIndexParent[nIndex] = atoi(pStrcur);
							}
							//POS��ǂݍ���
							if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
							{
								//���o��
								pStrcur += strlen("POS = ");
								//������̐擪��ݒ�
								strcpy(aStr, pStrcur);

								//��������Ԃ��Ă��炤
								nWord = PopString(pStrcur, &aStr[0]);
								//������ϊ�
								m_aKayOffset[nIndex].fposX = (float)atof(pStrcur);
								//���������i�߂�
								pStrcur += nWord;

								//��������Ԃ��Ă��炤
								nWord = PopString(pStrcur, &aStr[0]);
								//������ϊ�
								m_aKayOffset[nIndex].fposY = (float)atof(pStrcur);
								//���������i�߂�
								pStrcur += nWord;

								//��������Ԃ��Ă��炤
								nWord = PopString(pStrcur, &aStr[0]);
								//������ϊ�
								m_aKayOffset[nIndex].fposZ = (float)atof(pStrcur);

							}
							//ROT��ǂݍ���
							if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
							{
								//���o��
								pStrcur += strlen("ROT = ");
								//������̐擪��ݒ�
								strcpy(aStr, pStrcur);

								//��������Ԃ��Ă��炤
								nWord = PopString(pStrcur, &aStr[0]);
								//������ϊ�
								m_aKayOffset[nIndex].frotX = (float)atof(pStrcur);

								//���������i�߂�
								pStrcur += nWord;
								//��������Ԃ��Ă��炤
								nWord = PopString(pStrcur, &aStr[0]);
								//������ϊ�
								m_aKayOffset[nIndex].frotY = (float)atof(pStrcur);

								//���������i�߂�
								pStrcur += nWord;
								//��������Ԃ��Ă��炤
								nWord = PopString(pStrcur, &aStr[0]);
								//������ϊ�
								//rotFile[nIndex].z = (float)atof(pStrcur);
								m_aKayOffset[nIndex].frotZ = (float)atof(pStrcur);


							}
							//�p�[�c�Z�b�g�I��
							else if (memcmp(pStrcur, "END_PARTSSET", strlen("END_PARTSSET")) == 0)
							{

								////���f���𐶐�	�I�t�Z�b�g�ݒ�
								//m_apModel[nIndex] = CModel::Create(
								//	D3DXVECTOR3(m_pos.x + m_aKayOffset[nIndex].fposX,
								//		m_pos.y + m_aKayOffset[nIndex].fposY,
								//		m_pos.z + m_aKayOffset[nIndex].fposZ),
								//	D3DXVECTOR3(m_rot.x + m_aKayOffset[nIndex].frotX,
								//		m_rot.y + m_aKayOffset[nIndex].frotY,
								//		m_rot.z + m_aKayOffset[nIndex].frotZ));

								////pos����
								//m_OffSetPos[nIndex] = m_apModel[nIndex]->GetPos();

								////���f�������蓖��
								//m_apModel[nIndex]->BindModel(m_nNumMatModel[nIndex], m_pMeshModel[nIndex], m_pBuffMatModel[nIndex]);

								//if (aIndexParent[nIndex] == -1)
								//{
								//	//���f���̐e���w��
								//	m_apModel[nIndex]->SetParent(NULL);
								//}
								//else
								//{
								//	//���f���̐e���w��
								//	m_apModel[nIndex]->SetParent(m_apModel[aIndexParent[nIndex]]);
								//}

								break;
							}
						}
					}
					//�L�����N�^�[�Z�b�g�I��
					else if (memcmp(pStrcur, "END_CHARACTERSET", strlen("END_CHARACTERSET")) == 0)
					{
						break;
					}
				}
				//������̐擪��ݒ�
				pStrcur = ReadLine(pFile, &aLine[0]);
				//����������o��
				strcpy(aStr, pStrcur);
			}

			//���[�V�����ǂݍ���
			if (memcmp(pStrcur, "MOTIONSET", strlen("MOTIONSET")) == 0)
			{
				//���o��
				pStrcur += strlen("MOTIONSET");

				while (1)
				{
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
					//����������o��
					strcpy(aStr, pStrcur);

					if (memcmp(pStrcur, "LOOP = ", strlen("LOOP = ")) == 0)
					{
						//���o��
						pStrcur += strlen("LOOP = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);

						switch (atoi(pStrcur))
						{
						case 0:
							//�����񔲂��o��
							m_aMotionInfo[nCntMotion].bLoop = false;
							break;
						case 1:
							//�����񔲂��o��
							m_aMotionInfo[nCntMotion].bLoop = true;
							break;
						}
						//������̐擪��ݒ�
						pStrcur = ReadLine(pFile, &aLine[0]);
					}

					if (memcmp(pStrcur, "NUM_KEY = ", strlen("NUM_KEY = ")) == 0)
					{
						//���o��
						pStrcur += strlen("NUM_KEY = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);
						//�����񔲂��o��
						m_aMotionInfo[nCntMotion].nNumKey = atoi(pStrcur);

						//������̐擪��ݒ�
						pStrcur = ReadLine(pFile, &aLine[0]);
						//����������o��
						strcpy(aStr, pStrcur);
					}

					//�L�[�̐ݒ�
					for (int nCntKey = 0; nCntKey < m_aMotionInfo[nCntMotion].nNumKey;)
					{
						if (memcmp(pStrcur, "KEYSET", strlen("KEYSET")) == 0)
						{
							//���o��
							pStrcur += strlen("KEYSET");
							//������̐擪��ݒ�
							strcpy(aStr, pStrcur);
							//������̐擪��ݒ�
							pStrcur = ReadLine(pFile, &aLine[0]);

							if (memcmp(pStrcur, "FRAME = ", strlen("FRAME = ")) == 0)
							{
								//���o��
								pStrcur += strlen("FRAME = ");

								m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].nFrame = atoi(pStrcur);

								//������̐擪��ݒ�
								strcpy(aStr, pStrcur);
								//������̐擪��ݒ�
								pStrcur = ReadLine(pFile, &aLine[0]);
							}

							//�p�[�c����
							for (int nCntParts = 0; nCntParts < m_nNumParts;)
							{
								if (memcmp(pStrcur, "KEY", strlen("KEY")) == 0)
								{
									//������̐擪��ݒ�
									pStrcur = ReadLine(pFile, &aLine[0]);

									if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
									{
										//���o��
										pStrcur += strlen("POS = ");
										//������̐擪��ݒ�
										strcpy(aStr, pStrcur);

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.X���
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposX = (float)atof(pStrcur);
										//���������i�߂�
										pStrcur += nWord;

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.Y���
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposY = (float)atof(pStrcur);
										//���������i�߂�
										pStrcur += nWord;

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.Z���
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposZ = (float)atof(pStrcur);
										//������̐擪��ݒ�
										pStrcur = ReadLine(pFile, &aLine[0]);
									}
									//ROT��ǂݍ���
									if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
									{
										//���o��
										pStrcur += strlen("ROT = ");
										//������̐擪��ݒ�
										strcpy(aStr, pStrcur);

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//RotX
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotX = (float)atof(pStrcur);
										//���������i�߂�
										pStrcur += nWord;

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//RotY
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotY = (float)atof(pStrcur);
										//���������i�߂�
										pStrcur += nWord;

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//RotZ
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotZ = (float)atof(pStrcur);

										//������̐擪��ݒ�
										pStrcur = ReadLine(pFile, &aLine[0]);
									}
									if (memcmp(pStrcur, "END_KEY", strlen("END_KEY")) == 0)
									{
										//���o��
										pStrcur += strlen("END_KEY");
										//������̐擪��ݒ�
										strcpy(aStr, pStrcur);
										//������̐擪��ݒ�
										pStrcur = ReadLine(pFile, &aLine[0]);
										//�p�[�c�̃J�E���g��i�߂�
										nCntParts++;
									}
								}
								else
								{
									//������̐擪��ݒ�
									pStrcur = ReadLine(pFile, &aLine[0]);
								}
							}
							if (memcmp(pStrcur, "END_KEYSET", strlen("END_KEYSET")) == 0)
							{
								//������̐擪��ݒ�
								pStrcur = ReadLine(pFile, &aLine[0]);
								//�J�E���g��i�߂�
								nCntKey++;
							}
						}
						else
						{
							//������̐擪��ݒ�
							pStrcur = ReadLine(pFile, &aLine[0]);
						}

					}
					if (memcmp(pStrcur, "END_MOTIONSET", strlen("END_MOTIONSET")) == 0)
					{
						//���[�V�����̏����Z�b�g
						m_pKeyInfo[nCntMotion] = &m_aMotionInfo[nCntMotion].aKayInfo[0];
						break;
					}
				}
			}
			//�X�N���v�g�̏I���
			if (memcmp(pStrcur, "END_SCRIPT	", strlen("END_SCRIPT")) == 0)
			{
				break;
			}
		}
	}
	else
	{	//�t�@�C�����J���Ȃ�����
		printf("�t�@�C�����J���܂���ł���\n");
	}
	//�t�@�C�������
	fclose(pFile);
#endif

}

//=============================================================================
//�@�t�@�C���ǂݍ��ݖ�������r��
//=============================================================================
char *CEnemy::ReadLine(FILE *pFile, char *pDst)
{
	while (1)
	{
		//�P�s���ǂݍ���
		fgets(&pDst[0], 256, pFile);

		//������̃f�[�^ ��r���镶���� ��r���镶����
		if (memcmp(pDst, "#", strlen("#")) == 0)
		{
			pDst += strlen("\n");
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pDst, "\t", strlen("\t")) == 0)
		{
			pDst += strlen("\t");
			while (1)
			{
				if (memcmp(pDst, "\t", strlen("\t")) == 0)
				{
					pDst += strlen("\t");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pDst, " ", strlen(" ")) == 0)
		{
			pDst += strlen(" ");
			while (1)
			{
				if (memcmp(pDst, " ", strlen(" ")) == 0)
				{
					pDst += strlen(" ");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pDst, "\n", strlen("\n")) == 0)
		{
			pDst += strlen("\n");
		}
		else
		{
			break;
		}
	}
	return pDst;
}

//=============================================================================
//�@�t�@�C���ǂݍ��ݐ擪��r��
//=============================================================================
char * CEnemy::GetLineTop(char * pStr)
{
	while (1)
	{
		//������̃f�[�^ ��r���镶���� ��r���镶����
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{
			pStr += strlen(" ");
			while (1)
			{
				if (memcmp(pStr, " ", strlen(" ")) == 0)
				{
					pStr += strlen(" ");
				}
				else
				{
					break;
				}
				break;
			}
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{
			pStr += strlen("\t");
			while (1)
			{
				if (memcmp(pStr, "\t", strlen("\t")) == 0)
				{
					pStr += strlen("\t");
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	return pStr;
}

//=============================================================================
//�@��������Ԃ�
//=============================================================================
int CEnemy::PopString(char * pStr, char * pDest)
{
	int nWord = 0;

	while (1)
	{	//���o��
		pStr += 1;
		nWord += 1;
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{	//���o��
			pStr = "\0";
			nWord += 1;
			break;
		}
		if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{	//���o��
			pStr = "\0";
			nWord += strlen("\t");
			break;
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pStr, "\n", strlen("\n")) == 0)
		{
			//���o��
			nWord += strlen("\n");
			break;
		}
	}
	strcpy(pDest, pStr);
	//������̐���Ԃ�
	return nWord;
}
