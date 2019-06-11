//---------------------------------------------------------------------
//	�I�u�W�F�N�g����(objectBG.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "objectBG.h"
#include "manager.h"
#include "game.h"
#include "tutorial.h"

#include "sceneObject.h"
#include "fade.h"
#include "player.h"
#include "effect.h"
#include "effect3D.h"
#include "shadow.h"
#include "billboardItem.h"

#include "UILife.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_MODEL0000					"data\\MODEL\\MODELBG\\Truck00.x"
#define BG_MODEL000						"data\\MODEL\\MODELBG\\bluesheet.x"
#define BG_MODEL001						"data\\MODEL\\MODELBG\\sakuratree.x"
#define BG_MODEL002						"data\\MODEL\\MODELBG\\sakuratree001.x"
#define BG_MODEL003						"data\\MODEL\\MODELBG\\sakuratree002.x"
#define BG_MODEL004						"data\\MODEL\\MODELBG\\fence000.x"
#define BG_MODEL005						"data\\MODEL\\MODELBG\\tree000.x"
#define BG_MODEL006						"data\\MODEL\\MODELBG\\Truck01.x"
#define BG_MODEL007						"data\\MODEL\\MODELBG\\Finish00.x"

#define MODEL_SPEED     (5.0f)
#define PLAYER_DEPTH	(18)		// �v���C���[�̕������p
#define PLAYER_HEIGHT	(50.0f)		// �v���C���[�̔w�̍���

#define MAX_EFFECT_BILL  (15)
#define MAX_EFFECT_FENCE (5)
#define MAX_EFFECT_TREE  (7)
#define MAX_EFFECT_TRUCK (10)
#define MAX_ITEM_DROP	 (30)

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPD3DXMESH					CObjectBG::m_pMesh[MODELTYPE_MAX] = {};
LPD3DXBUFFER				CObjectBG::m_pBuffMat[MODELTYPE_MAX] = {};
LPDIRECT3DTEXTURE9			CObjectBG::m_pTexture[MODELTYPE_MAX] = {};
DWORD						CObjectBG::m_nNumMat[MODELTYPE_MAX] = {};

//--------------------------------------------
//�I�u�W�F�N�g�N���X �R���X�g���N�^
//--------------------------------------------
CObjectBG::CObjectBG() : CScene(3, CScene::OBJTYPE_BGMODEL)
{
	m_pos = D3DXVECTOR3(0, 0, 0);					//�ʒu
	m_posold = D3DXVECTOR3(0, 0, 0);				//�O��̈ʒu
	m_move = D3DXVECTOR3(0, 0, 0);					//�ړ���
	m_ModelMove = D3DXVECTOR3(0, 0, 0);
	m_rot = D3DXVECTOR3(0, 0, 0);					//����
	D3DXMatrixIdentity(&m_mtxWorld);				//���[���h�}�g���b�N�X
	m_nCollision = 0;
	m_nCount = 0;
	m_Type = CObjectBG::MODELTYPE_BILL000;
	m_nMoveType = MOVETYPE_NONE;
}

//--------------------------------------------
//�I�u�W�F�N�g�N���X �f�X�g���N�^
//--------------------------------------------
CObjectBG::~CObjectBG()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CObjectBG *CObjectBG::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, MODELTYPE type, MOVETYPE nMovetype, int nCollision)
{
	//�I�u�W�F�N�g�|�C���^
	CObjectBG *pObjectBG;
	pObjectBG = new CObjectBG;
	//�^�C�v�̐ݒ�
	pObjectBG->m_Type = type;

	//�����l���������� pos���
	pObjectBG->m_pos = pos;

	//�I�u�W�F�N�g�̏�����
	pObjectBG->Init();

	//�ړ��ʂ̐ݒ�
	pObjectBG->m_move = move;
	//�ړ������̐ݒ�
	pObjectBG->m_nMoveType = nMovetype;

	//�R���W�����^�C�v���
	pObjectBG->m_nCollision = nCollision;

	//�I�u�W�F�N�g�̏���Ԃ�
	return pObjectBG;
}

//=============================================================================
// �I�u�W�F�N�g�̏���������
//=============================================================================
HRESULT CObjectBG::Init(void)
{
	//�I�u�W�F�N�g��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_BGMODEL);

	m_rot = D3DXVECTOR3(0, D3DX_PI * 1.0f, 0);
	m_move = D3DXVECTOR3(0, 0, 0);
	m_fDestAngle = D3DX_PI * 1.0f;
	m_fDiffAngle = 0;
	LPDIRECT3DVERTEXBUFFER9 VtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

	//���f���𐶐�	�I�t�Z�b�g�ݒ�
	m_pObject = CSceneObject::Create(m_pos, m_rot);
	//���f�������蓖��
	m_pObject->BindModel(m_nNumMat[m_Type], m_pMesh[m_Type], m_pBuffMat[m_Type]);
	//���f���̐e���w��
	m_pObject->SetParent(NULL);

	m_pObject->Setpos(m_pos);

	//�e��ݒ�
	m_pShadow = NULL;

	switch (m_Type)
	{
	case MODELTYPE_BILL000:
		break;
	case MODELTYPE_BILL001:
		break;
	case MODELTYPE_BILL002:
		break;
	case MODELTYPE_BILL003:
		//m_pShadow = CShadow::Create(D3DXVECTOR3(m_pos.x - 50, 1.0f, m_pos.z + 50), 100, 120, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f),CShadow::SHADOWTYPE_BILL);
		break;
	case MODELTYPE_FENCE000:
		m_pShadow = CShadow::Create(D3DXVECTOR3(m_pos.x, 0.5f, m_pos.z), 50, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f), CShadow::SHADOWTYPE_NORMAL);
		break;
	case MODELTYPE_TREE000:
		m_pShadow = CShadow::Create(D3DXVECTOR3(m_pos.x, 0.5f, m_pos.z), 50, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f), CShadow::SHADOWTYPE_NORMAL);
		break;
	case MODELTYPE_TRUCK000:
		m_pShadow = CShadow::Create(D3DXVECTOR3(m_pos.x, 0.5f, m_pos.z), 50, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f), CShadow::SHADOWTYPE_NORMAL);
		break;
	}



	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I������
//=============================================================================
void CObjectBG::Uninit(void)
{
	if (m_pObject != NULL)
	{
		m_pObject->Uninit();
		delete m_pObject;
		m_pObject = NULL;
	}
	if (m_pShadow != NULL)
	{
		m_pShadow->Uninit();
		//delete m_pShadow;
		m_pShadow = NULL;
	}
	//����������(�I�u�W�F�N�g��j��)
	Release();
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V����
//=============================================================================
void CObjectBG::Update(void)
{
#if 1

	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//�J�������擾
	//CCamera *pCamera = CManager::GetCamera();
	//�ߋ��̈ʒu��ݒ�
	m_posold = m_pos;


	// �ړ��ʂ̏�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�����̑��
	D3DXVECTOR3 rot = m_pObject->Getrot();

	// MOVETYPE�̐ݒ�
	MOVETYPE MoveType = m_nMoveType;


	switch (m_nMoveType)
	{
	case MOVETYPE_X_MOVE:
		// X���ړ�
		if (m_nCount <= 120)
		{
			move.x += m_move.x;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.x -= m_move.x;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;
		break;

	case MOVETYPE_Y_MOVE:
		// Y���ړ�
		if (m_nCount <= 120)
		{
			move.y += m_move.y;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.y -= m_move.y;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;
		break;

	case MOVETYPE_Z_MOVE:
		// Z���ړ�
		if (m_nCount <= 120)
		{
			move.z += m_move.z;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.z -= m_move.z;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;

		break;

	case MOVETYPE_ROTATION_X:
		// X���ŉ�]���Ȃ���Z���ړ�
		if (m_nCount <= 120)
		{
			move.z += m_move.z;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.z -= m_move.z;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;

		rot.x += 0.1f;
		//rot.z += 0.01f;

		m_pObject->Setrot(rot);
		break;

	case MOVETYPE_ROTATION_Z:
		// Z���ŉ�]���Ȃ���X���ړ�
		if (m_nCount <= 120)
		{
			move.x += m_move.x;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.x -= m_move.x;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;
		rot.z += 0.1f;

		m_pObject->Setrot(rot);
		break;
	}

	//����
	move.x += (0.0f - move.x) * 0.5f;
	move.z += (0.0f - move.z) * 0.5f;
	//�ʒu�X�V
	m_pos += move;

	m_pObject->Setpos(m_pos);
	m_ModelMove = move;

#endif // 0
}

//=============================================================================
// �I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CObjectBG::Draw(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();

	D3DXVECTOR3 Kyori = m_pos - pPlayer->GetPos();

	//if (m_pos.z + 200 > pPlayer->GetPos().z)
	//{
	//	Kyori.z = abs(Kyori.z);
	//	if (Kyori.z < 10000)
	//	{
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
			////�e�̕`�揈��
			//D3DXMATRIX	mtxShadow;
			//D3DXPLANE	planeField;
			//D3DXVECTOR4 VecLight;
			//D3DXVECTOR3 pos, normal;
			////���C�g���擾
			//CLight *pLight = CManager::GetLight();

			//// ���C�g�𖳌��ɂ���
			//pDevice->LightEnable(0, FALSE);
			//pDevice->LightEnable(1, FALSE);
			//pDevice->LightEnable(2, FALSE);
			//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			////���Z����
			//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			////�V���h�E�}�g���b�N�X�̏�����
			//D3DXMatrixIdentity(&mtxShadow);
			////���C�g�̐ݒ�
			//VecLight = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.0f);
			////�e�̈ʒu�ݒ�
			//pos = D3DXVECTOR3(0.0f, 0.01f, 0.0f);
			////�@���̐ݒ�
			//normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			////���ʂ��쐬
			//D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
			////�e�}�g���b�N�X�̐ݒ�
			//D3DXMatrixShadow(&mtxShadow, &VecLight, &planeField);
			////���[���h�}�g���b�N�X�Ɗ|�����킹��
			//D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);
			////���[���h�}�g���b�N�X�̐ݒ�
			//pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

			//if (m_pObject != NULL)
			//{
			//	m_pObject->SetbShadow(true);
			//	m_pObject->Draw();
			//}
			////�����_�[�X�e�C�g�����ɖ߂�
			//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			//// ���C�g��L���ɂ���
			//pDevice->LightEnable(0, TRUE);
			//pDevice->LightEnable(1, TRUE);
			//pDevice->LightEnable(2, TRUE);
			//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);


			if (m_pObject != NULL)
			{
				m_pObject->SetbShadow(false);
				m_pObject->Draw();
			}
		//}
	//}
}

//=============================================================================
// �I�u�W�F�N�g�̈ʒu�ݒ�
//=============================================================================
void CObjectBG::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CObjectBG::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(BG_MODEL000, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[0], NULL, &m_nNumMat[0], &m_pMesh[0]);
	D3DXLoadMeshFromX(BG_MODEL001, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[1], NULL, &m_nNumMat[1], &m_pMesh[1]);
	D3DXLoadMeshFromX(BG_MODEL002, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[2], NULL, &m_nNumMat[2], &m_pMesh[2]);
	D3DXLoadMeshFromX(BG_MODEL003, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[3], NULL, &m_nNumMat[3], &m_pMesh[3]);
	D3DXLoadMeshFromX(BG_MODEL004, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[4], NULL, &m_nNumMat[4], &m_pMesh[4]);
	D3DXLoadMeshFromX(BG_MODEL005, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[5], NULL, &m_nNumMat[5], &m_pMesh[5]);
	D3DXLoadMeshFromX(BG_MODEL006, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[6], NULL, &m_nNumMat[6], &m_pMesh[6]);
	D3DXLoadMeshFromX(BG_MODEL007, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[7], NULL, &m_nNumMat[7], &m_pMesh[7]);

	//�e�N�X�`���̓ǂݍ���
	for (int nCnt = 0; nCnt < MODELTYPE_MAX; nCnt++)
	{
		//�}�e���A����񂩂�e�N�X�`���̎擾
		pMat = (D3DXMATERIAL*)m_pBuffMat[nCnt]->GetBufferPointer();

		//�}�e���A���̐���
		for (int nCntMatTex = 0; nCntMatTex < (int)m_nNumMat[nCnt]; nCntMatTex++)
		{
			if (pMat[nCntMatTex].pTextureFilename != NULL)
			{
				// �e�N�X�`���̐ݒ�
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
					pMat[nCntMatTex].pTextureFilename,	// �t�@�C���̖��O
					&m_pTexture[nCnt]);					// �e�N�X�`���ւ̃|�C���^
			}
		}
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j������
//=============================================================================
void CObjectBG::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MODELTYPE_MAX; nCnt++)
	{
		// ���b�V���̊J��
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();
			m_pMesh[nCnt] = NULL;
		}
		// �}�e���A���̊J��
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();
			m_pBuffMat[nCnt] = NULL;
		}

		//�e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
//=============================================================================
// �I�u�W�F�N�g�̈ʒu
//=============================================================================
D3DXVECTOR3 CObjectBG::GetPos(void)
{
	return m_pos;
}


//===============================================================================
// �����蔻��
//===============================================================================
bool CObjectBG::CollisionObject(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
	//�������Ă��邩�������ĂȂ���
	bool bLand = false;
	int nCollision = m_nCollision;
	CManager::MODE pMode = CManager::GetMode();
	CPlayer *pPlayer = CGame::GetPlayer();

	//�G�t�F�N�g�p�֐�
	D3DXVECTOR3 RotRand;
	D3DXVECTOR3 PosRand;
	D3DXVECTOR3 effectmove;

	//�T�E���h
	CSound *pSound = CManager::GetSound(0);
	float fPlayerDepth; //�v���C���[�̑傫��
	fPlayerDepth = 0;

#if 1
	switch (m_nCollision)
	{
	case 1:

		// �e����̎擾
		D3DXVECTOR3 ModelPos = m_pos;	// �ʒu
		D3DXVECTOR3 ModelMove = m_ModelMove;	// �ړ���
		MOVETYPE ModelMoveType = m_nMoveType;	// �����̃^�C�v

		D3DXVECTOR3 VtxMax = m_pObject->VtxMax();	// ���f���̍ő�l
		D3DXVECTOR3 VtxMin = m_pObject->VtxMin();	// ���f���̍ŏ��l

		D3DXVECTOR3 ModelMax = m_pObject->GetPos() + m_pObject->VtxMax();	// �ʒu���݂̍ő�l
		D3DXVECTOR3 ModelMin = m_pObject->GetPos() + m_pObject->VtxMin();	// �ʒu���݂̍ŏ��l

		// �ړ��ʂ̕ێ�
		if (ModelMove.x == 0.0f)
		{
			ModelMove.x = m_ModelMove.x;
		}

		if (ModelMove.y == 0.0f)
		{
			ModelMove.y = m_ModelMove.y;
		}

		if (ModelMove.z == 0.0f)
		{
			ModelMove.z = m_ModelMove.z;
		}

		//��]���ɓ����蔻������Ɋg��
		if (pPlayer->GetMotionState() == CPlayer::MOTIONSTATE_TUMBLE)
		{
			fPlayerDepth = 20;
		}

		if (m_Type == MODELTYPE_TREE000)
		{
			ModelMax.x -= 30.0f;
			ModelMax.z -= 30.0f;

			ModelMin.x += 30.0f;
			ModelMin.z += 30.0f;
		}

		if (pPos->x >= ModelMin.x - PLAYER_DEPTH - fPlayerDepth && pPos->x <= ModelMax.x + PLAYER_DEPTH + fPlayerDepth)
		{// X�͈͓̔��ɂ���
			if (pPos->z >= ModelMin.z - PLAYER_DEPTH && pPos->z <= ModelMax.z + PLAYER_DEPTH)
			{// Z�͈͓̔��ɂ���
				if (pPosOld->y >= ModelMax.y && pPos->y <= ModelMax.y)
				{// �I�u�W�F�N�g�̏ォ�瓖����ꍇ
					pPos->y = ModelMax.y + abs(ModelMove.y);
					pMove->y = 0.0f;

					if (ModelMove.x != 0.0f)
					{// X�ړ�����
						pPos->x += ModelMove.x;
					}

					if (ModelMove.z != 0.0f)
					{// Z�ړ�����
						pPos->z += ModelMove.z;
					}

					bLand = true;
				}
				else if (pPosOld->y + PLAYER_HEIGHT <= ModelMin.y && pPos->y + PLAYER_HEIGHT >= ModelMin.y)
				{// �I�u�W�F�N�g�̉����瓖����ꍇ
					pPos->y = ModelMin.y - PLAYER_HEIGHT;
					pMove->y = 0.0f;
				}

				// Y�͈͓̔��ɂ���
				if (!(pPos->y >= ModelMax.y) && !(pPos->y + PLAYER_HEIGHT <= ModelMin.y))
				{
					//���[�V�����̏�Ԃ�����ƃW�����v�̎�
					if (pPlayer->GetMotionState() == pPlayer->MOTIONSTATE_RUN
						|| pPlayer->GetMotionState() == pPlayer->MOTIONSTATE_JUMP)
					{	//���G�ȊO�̎�
						if (pPlayer->GetPlayerState() != CPlayer::PLAYERSTATE_APPEAR)
						{
							CUILife *pLife = CGame::GetUILife();
							pLife->MinusLife(1);
							pPlayer->SetMotionState(CPlayer::MOTIONSTATE_DAMAGE);
						}
					}
					//�v���C���[���]���肩�W�F�b�g�Ȃ�j��
					//�r��
					if (m_Type == CObjectBG::MODELTYPE_BILL000 || m_Type == CObjectBG::MODELTYPE_BILL001
						|| m_Type == CObjectBG::MODELTYPE_BILL002 || m_Type == CObjectBG::MODELTYPE_BILL003)
					{
						pSound->PlaySound(pSound->SOUND_LABEL_SE_HIT00);

						for (int nCnt = 0; nCnt < MAX_EFFECT_BILL; nCnt++)
						{
							//�����_���Ȓl
							RotRand.x = (float)(rand() % 50 - 25);
							RotRand.y = (float)(rand() % 100 + 50);
							PosRand.x = (float)(rand() % 100 - 50);
							//�ړ��ʂ̐ݒ�
							effectmove.x = (float)(rand() % 20 - 10);
							effectmove.y = (float)(rand() % 20 - 10);
							effectmove.z = (float)(rand() % 20 - 10);

							//�G�t�F�N�g�𐶐�
							CEffect::Create(D3DXVECTOR3(m_pos.x + PosRand.x, m_pos.y, m_pos.z + 150), effectmove, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
								40, 40, 1, 50, CEffect::EFFECTTEX_HAHEN000);

							PosRand.x = (float)(rand() % 200 - 100);
							C3DEffect::Create(D3DXVECTOR3(m_pos.x + PosRand.x, m_pos.y + RotRand.y, m_pos.z + 150), effectmove,
								D3DXVECTOR3(sinf(RotRand.x), sinf(RotRand.x), sinf(RotRand.x)), (C3DEffect::EFFECTTYPE)m_Type, 60);
						}
					}
					//�t�F���X
					if (m_Type == CObjectBG::MODELTYPE_FENCE000)
					{
						pSound->PlaySound(pSound->SOUND_LABEL_SE_HIT02);


						if (pPlayer->GetMotionState() == pPlayer->MOTIONSTATE_JET)
						{
							for (int nCnt = 0; nCnt < MAX_EFFECT_FENCE; nCnt++)
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
								C3DEffect::Create(D3DXVECTOR3(m_pos.x + PosRand.x, m_pos.y + PosRand.y, m_pos.z + 150), effectmove,
									D3DXVECTOR3(sinf(RotRand.x), sinf(RotRand.x), sinf(RotRand.x)), (C3DEffect::EFFECTTYPE)m_Type, 30);
							}
						}
						else
						{
							//���G�ȊO�̎�
							if (pPlayer->GetPlayerState() != CPlayer::PLAYERSTATE_APPEAR)
							{
								if (pPlayer->GetPlayerState() != CPlayer::PLAYERSTATE_DAMAGE)
								{
									CUILife *pLife = CGame::GetUILife();
									pLife->MinusLife(1);
									pPlayer->SetMotionState(CPlayer::MOTIONSTATE_DAMAGE);
								}
								for (int nCnt = 0; nCnt < MAX_EFFECT_FENCE; nCnt++)
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
									C3DEffect::Create(D3DXVECTOR3(m_pos.x + PosRand.x, m_pos.y + PosRand.y, m_pos.z + 150), effectmove,
										D3DXVECTOR3(sinf(RotRand.x), sinf(RotRand.x), sinf(RotRand.x)), (C3DEffect::EFFECTTYPE)m_Type, 30);
								}
							}
						}
					}
					//��
					if (m_Type == CObjectBG::MODELTYPE_TREE000)
					{
						pSound->PlaySound(pSound->SOUND_LABEL_SE_HIT01);
						for (int nCnt = 0; nCnt < MAX_EFFECT_TREE; nCnt++)
						{
							//�����_���Ȓl
							RotRand.x = (float)(rand() % 20 - 10);
							PosRand.y = (float)(rand() % 20 + 20);
							PosRand.x = (float)(rand() % 50 - 25);
							//�ړ��ʂ̐ݒ�
							effectmove.x = (float)(rand() % 10 - 5);
							effectmove.y = (float)(rand() % 10);
							effectmove.z = (float)(rand() % 20 - 10);
							//�G�t�F�N�g�𐶐�
							C3DEffect::Create(D3DXVECTOR3(m_pos.x + PosRand.x, m_pos.y + PosRand.y, m_pos.z + 150), effectmove,
								D3DXVECTOR3(sinf(RotRand.x), sinf(RotRand.x), sinf(RotRand.x)), (C3DEffect::EFFECTTYPE)m_Type, 30);

							//�����_���Ȓl
							RotRand.x = (float)(rand() % 20 - 10);
							PosRand.y = (float)(rand() % 50 + 100);
							PosRand.x = (float)(rand() % 50 - 25);

							effectmove.y = (float)(rand() % 50 + 10) / 10.0f;

							//�G�t�F�N�g�𐶐�
							C3DEffect::Create(D3DXVECTOR3(m_pos.x + PosRand.x, m_pos.y + PosRand.y, m_pos.z + 150), effectmove,
								D3DXVECTOR3(sinf(RotRand.x), sinf(RotRand.x), sinf(RotRand.x)), C3DEffect::EFFECTTYPE_LEAF000, 30);
						}
					}
					//�g���b�N
					if (m_Type == CObjectBG::MODELTYPE_TRUCK000)
					{
						pSound->PlaySound(pSound->SOUND_LABEL_SE_HIT00);
						for (int nCnt = 0; nCnt < MAX_EFFECT_TRUCK; nCnt++)
						{
							//�����_���Ȓl
							RotRand.x = (float)(rand() % 50 - 25);
							PosRand.y = (float)(rand() % 20 + 20);
							PosRand.x = (float)(rand() % 50 - 25);
							//�ړ��ʂ̐ݒ�
							effectmove.x = (float)(rand() % 50 - 25);
							effectmove.y = (float)(rand() % 10);
							effectmove.z = (float)(rand() % 20 - 10);
							//�����_���Ȓl
							RotRand.x = (float)(rand() % 20 - 10);
							PosRand.y = (float)(rand() % 50 + 100);
							PosRand.x = (float)(rand() % 50 - 25);
							effectmove.y = (float)(rand() % 50 + 10) / 10.0f;
							//�G�t�F�N�g�𐶐�
							C3DEffect::Create(D3DXVECTOR3(m_pos.x + PosRand.x, m_pos.y + PosRand.y, m_pos.z + 150), effectmove,
								D3DXVECTOR3(sinf(RotRand.x), sinf(RotRand.x), sinf(RotRand.x)), C3DEffect::EFFECTTYPE_TRUCK000, 30);
						}
						//�A�C�e���̌�
						for (int nCnt = 0; nCnt < MAX_ITEM_DROP; nCnt++)
						{
							//�����_���Ȓl
							RotRand.x = (float)(rand() % 50 - 25);

							//�A�C�e��
							CBillBoardItem::Create(D3DXVECTOR3(m_pos.x + RotRand.x, m_pos.y, (m_pos.z - 100) + (15 * nCnt)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, 30, CBillBoardItem::ITEMTEX_NORMAL);
						}
					}

					Uninit();
					break;
				}
			}
		}
		// �ʒu�̑��
		m_pObject->Setpos(ModelPos);
		// �ړ��ʂ̑��
		m_ModelMove = ModelMove;

		break;
	}
#endif
	return bLand;
}