//---------------------------------------------------------------------
//	�I�u�W�F�N�g����(objectBG.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "objectBG.h"
//#include "manager.h"
#include "game.h"

//#include "scene3D.h"
//#include "model.h"
#include "sceneObject.h"
#include "fade.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define PLAYER_TEXTURENAME000			"data\\TEXTURE\\GAME\\Player000.png"	//�e�N�X�`���̃t�@�C����
#define BG_MODEL0000					"data\\MODEL\\MODELBG\\box000.x"
#define BG_MODEL000						"data\\MODEL\\MODELBG\\building102.x"
#define BG_MODEL001						"data\\MODEL\\MODELBG\\building202.x"
#define BG_MODEL002						"data\\MODEL\\MODELBG\\building302.x"
#define BG_MODEL003						"data\\MODEL\\MODELBG\\building402.x"
#define BG_MODEL004						"data\\MODEL\\MODELBG\\fence000.x"
#define BG_MODEL005						"data\\MODEL\\MODELBG\\tree000.x"
#define BG_MODEL006						"data\\MODEL\\MODELBG\\ana.x"


#define MODEL_SPEED     (5.0f)
#define PLAYER_DEPTH	(15)		// �v���C���[�̕������p
#define PLAYER_HEIGHT	(50.0f)		// �v���C���[�̔w�̍���


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

		//rot.x += 0.01f;
		rot.z += 0.1f;

		m_pObject->Setrot(rot);
		break;
	}


	//�����̊���
	//m_fDiffAngle = m_fDestAngle - m_rot.y;
	////�p�x�̐ݒ�
	//if (m_fDiffAngle > D3DX_PI)
	//{
	//	m_fDiffAngle -= D3DX_PI* 2.0f;
	//}
	//if (m_fDiffAngle < -D3DX_PI)
	//{
	//	m_fDiffAngle += D3DX_PI* 2.0f;
	//}
	//m_rot.y += m_fDiffAngle * 0.1f;
	//if (m_rot.y > D3DX_PI)
	//{
	//	m_rot.y -= D3DX_PI* 2.0f;
	//}
	//if (m_rot.y < -D3DX_PI)
	//{
	//	m_rot.y += D3DX_PI* 2.0f;
	//}

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

	CLight *pLight = CGame::GetLight();

	// ���C�g�𖳌��ɂ���
	pDevice->LightEnable(0, FALSE);
	pDevice->LightEnable(1, FALSE);
	pDevice->LightEnable(2, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//���Z����
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�V���h�E�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);
	//���C�g�̐ݒ�
	VecLight = D3DXVECTOR4(0.0f, 0.0f, 1.0f,0.0f);
	//�e�̈ʒu�ݒ�
	pos = D3DXVECTOR3(0.0f, 0.01f, 0.0f);
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

	if (m_pObject != NULL)
	{
		m_pObject->SetbShadow(true);
		m_pObject->Draw();
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


	if (m_pObject != NULL)
	{
		m_pObject->SetbShadow(false);
		m_pObject->Draw();
	}
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

		if (pPos->x >= ModelMin.x - PLAYER_DEPTH && pPos->x <= ModelMax.x + PLAYER_DEPTH)
		{// Z�͈͓̔��ɂ���
			if (pPos->z >= ModelMin.z - PLAYER_DEPTH && pPos->z <= ModelMax.z + PLAYER_DEPTH)
			{// X�͈͓̔��ɂ���
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

				if (!(pPos->y >= ModelMax.y) && !(pPos->y + PLAYER_HEIGHT <= ModelMin.y))
				{// �I�u�W�F�N�g���Ƃ̓����蔻��
				 CDebugProc::Print(1,"���f���̉E�� : %.1f\n", ModelMax.x);
				 CDebugProc::Print(1, "���f���̍��� : %.1f\n", ModelMin.x);
				 CDebugProc::Print(1, "���f���̉��� : %.1f\n", ModelMax.z);
				 CDebugProc::Print(1, "���f���̎�O�� : %.1f\n", ModelMin.z);
				 CDebugProc::Print(1, "���f���̒��_�� : %.1f\n", ModelMax.y);
				 CDebugProc::Print(1, "���f���̑����� : %.1f\n", ModelMin.y);

					if (ModelMoveType == MOVETYPE_X_MOVE || ModelMoveType == MOVETYPE_ROTATION_Z)
					{// X�ړ��I�u�W�F�N�g
						if (pPosOld->x - (PLAYER_DEPTH - abs(ModelMove.x)) + abs(ModelMove.x) >= ModelMax.x && pPos->x - PLAYER_DEPTH < ModelMax.x)
						{// �E���甲�����ꍇ
							pPos->x = ModelMax.x + (PLAYER_DEPTH - abs(ModelMove.x)) + abs(ModelMove.x);
							//CDebugProc::Print("MOVETYPE_X_MOVE �E\n");
						}
						else if (pPosOld->x + (PLAYER_DEPTH - abs(ModelMove.x)) - abs(ModelMove.x) <= ModelMin.x && pPos->x + PLAYER_DEPTH > ModelMin.x)
						{// �����甲�����ꍇ
							pPos->x = ModelMin.x - (PLAYER_DEPTH - abs(ModelMove.x)) - abs(ModelMove.x);
							//CDebugProc::Print("MOVETYPE_X_MOVE ��\n");
						}

						if (pPosOld->z - PLAYER_DEPTH >= ModelMax.z && pPos->z - PLAYER_DEPTH < ModelMax.z)
						{// �����甲�����ꍇ
							pPos->z = ModelMax.z + PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_X_MOVE ��\n");
						}
						else if (pPosOld->z + PLAYER_DEPTH <= ModelMin.z && pPos->z + PLAYER_DEPTH > ModelMin.z)
						{// ��O���甲�����ꍇ
							pPos->z = ModelMin.z - PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_X_MOVE ��O\n");
						}
					}
					else if (ModelMoveType == MOVETYPE_Z_MOVE || ModelMoveType == MOVETYPE_ROTATION_X)
					{// Z�ړ��I�u�W�F�N�g
						if (pPosOld->x - PLAYER_DEPTH >= ModelMax.x && pPos->x - PLAYER_DEPTH < ModelMax.x)
						{// �E���甲�����ꍇ
							pPos->x = ModelMax.x + PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_X_MOVE �E\n");
						}
						else if (pPosOld->x + PLAYER_DEPTH <= ModelMin.x && pPos->x + PLAYER_DEPTH > ModelMin.x)
						{// �����甲�����ꍇ
							pPos->x = ModelMin.x - PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_X_MOVE ��\n");
						}

						if (pPosOld->z - (PLAYER_DEPTH - abs(ModelMove.z)) + abs(ModelMove.z) >= ModelMax.z && pPos->z - PLAYER_DEPTH < ModelMax.z)
						{// �����甲�����ꍇ
							pPos->z = ModelMax.z + (PLAYER_DEPTH - abs(ModelMove.z)) + abs(ModelMove.z);
							//CDebugProc::Print("MOVETYPE_X_MOVE ��\n");
						}
						else if (pPosOld->z + (PLAYER_DEPTH - abs(ModelMove.z)) - abs(ModelMove.z) <= ModelMin.z && pPos->z + PLAYER_DEPTH > ModelMin.z)
						{// ��O���甲�����ꍇ
							pPos->z = ModelMin.z - (PLAYER_DEPTH - abs(ModelMove.z)) - abs(ModelMove.z);
							//CDebugProc::Print("MOVETYPE_X_MOVE ��O\n");
						}
					}
					else
					{// ���ړ��I�u�W�F�N�g
						if (pPosOld->x - PLAYER_DEPTH >= ModelMax.x && pPos->x - PLAYER_DEPTH < ModelMax.x)
						{// �E���甲�����ꍇ
							pPos->x = ModelMax.x + PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_NOT �E\n");
						}
						else if (pPosOld->x + PLAYER_DEPTH <= ModelMin.x && pPos->x + PLAYER_DEPTH > ModelMin.x)
						{// �����甲�����ꍇ
							pPos->x = ModelMin.x - PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_NOT ��\n");
						}

						if (pPosOld->z - PLAYER_DEPTH >= ModelMax.z && pPos->z - PLAYER_DEPTH < ModelMax.z)
						{// �����甲�����ꍇ
							pPos->z = ModelMax.z + PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_NOT ��\n");
						}
						else if (pPosOld->z + PLAYER_DEPTH <= ModelMin.z && pPos->z + PLAYER_DEPTH > ModelMin.z)
						{// ��O���甲�����ꍇ
							pPos->z = ModelMin.z - PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_NOT ��O\n");
						}
					}
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