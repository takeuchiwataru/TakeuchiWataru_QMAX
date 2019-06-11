//---------------------------------------------------------------------
//	�I�u�W�F�N�g����(objectBG.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "ball.h"
//#include "manager.h"
#include "game.h"

//#include "scene3D.h"
//#include "model.h"
#include "sceneObject.h"
#include "fade.h"
#include "meshOrbit.h"
#include "UICircle.h"
#include "UIScore.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define PLAYER_TEXTURENAME000			"data\\TEXTURE\\GAME\\Player000.png"	//�e�N�X�`���̃t�@�C����
#define BG_MODEL0000						"data\\MODEL\\golfboal.x"

#define MODEL_SPEED     (5.0f)
#define PLAYER_DEPTH	(15)		// �v���C���[�̕������p
#define PLAYER_HEIGHT	(50.0f)		// �v���C���[�̔w�̍���


//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPD3DXMESH					CBall::m_pMesh[MODELTYPE_MAX] = {};
LPD3DXBUFFER				CBall::m_pBuffMat[MODELTYPE_MAX] = {};
LPDIRECT3DTEXTURE9			CBall::m_pTexture[MODELTYPE_MAX] = {};
DWORD						CBall::m_nNumMat[MODELTYPE_MAX] = {};

//--------------------------------------------
//�I�u�W�F�N�g�N���X �R���X�g���N�^
//--------------------------------------------
CBall::CBall() : CScene(3, CScene::OBJTYPE_BGMODEL)
{
	m_pos = D3DXVECTOR3(0, 0, 0);					//�ʒu
	m_posold = D3DXVECTOR3(0, 0, 0);				//�O��̈ʒu
	m_move = D3DXVECTOR3(0, 0, 0);					//�ړ���
	m_ModelMove = D3DXVECTOR3(0, 0, 0);
	m_rot = D3DXVECTOR3(0, 0, 0);					//����
	D3DXMatrixIdentity(&m_mtxWorld);				//���[���h�}�g���b�N�X
	m_nCollision = 0;
	m_nCount = 0;
	m_Type = CBall::MODELTYPE_BALL;
	m_nTimer = 0;
	m_nTryTimer = 0;
	m_nPlusX = 0;
	m_nPlusZ = 0;
	m_bHit = false;
	m_bendBall = false;
}

//--------------------------------------------
//�I�u�W�F�N�g�N���X �f�X�g���N�^
//--------------------------------------------
CBall::~CBall()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CBall *CBall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, MODELTYPE type, int nCollision)
{
	//�I�u�W�F�N�g�|�C���^
	CBall *pObjectBG;
	pObjectBG = new CBall;
	//�^�C�v�̐ݒ�
	pObjectBG->m_Type = type;

	//�����l���������� pos���
	pObjectBG->m_pos = pos;

	//�I�u�W�F�N�g�̏�����
	pObjectBG->Init();

	//�ړ��ʂ̐ݒ�
	pObjectBG->m_move = move;

	//�R���W�����^�C�v���
	pObjectBG->m_nCollision = nCollision;

	//�I�u�W�F�N�g�̏���Ԃ�
	return pObjectBG;
}

//=============================================================================
// �I�u�W�F�N�g�̏���������
//=============================================================================
HRESULT CBall::Init(void)
{
	//�I�u�W�F�N�g��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_BGMODEL);

	m_rot = D3DXVECTOR3(0, D3DX_PI * 1.0f, 0);
	m_move = D3DXVECTOR3(0, 0, 0);
	m_fDestAngle = D3DX_PI * 1.0f;
	m_fDiffAngle = 0;
	LPDIRECT3DVERTEXBUFFER9 VtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	m_bJump = false;
	m_nTimer = 0;
	m_nPlusX = 0;
	m_nPlusZ = 0;
	m_nTryTimer = 0;
	m_bHit = false;
	m_bendBall = false;


	//���f���𐶐�	�I�t�Z�b�g�ݒ�
	m_pObject = CSceneObject::Create(m_pos, m_rot);
	//���f�������蓖��
	m_pObject->BindModel(m_nNumMat[m_Type], m_pMesh[m_Type], m_pBuffMat[m_Type]);
	//���f���̐e���w��
	m_pObject->SetParent(NULL);

	m_pObject->Setpos(m_pos);

	//�O��
	m_pMeshOrbit = CMeshOrbit::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 5.0f, m_pos.z));
	m_pMeshOrbit->SetMtxParent(&m_mtxWorld);

	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I������
//=============================================================================
void CBall::Uninit(void)
{
	m_pMeshOrbit = NULL;
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
void CBall::Update(void)
{
#if 1
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//�R���g���[���[�����擾
	CDirectInput *pInputJoypad = CManager::GetJoypad();

	//�J�������擾
	CCamera *pCamera = CGame::GetCamera();

	// �v���C���[�̏�Ԃ��擾
	CCamera::STATE CameraState;
	CameraState = pCamera->GetState();

	//�ߋ��̈ʒu��ݒ�
	m_posold = m_pos;


	// �ړ��ʂ̏�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�����̑��
	D3DXVECTOR3 rot = m_pObject->Getrot();

	//�W�����v
	if (pInput->GetTrigger(DIK_SPACE) == true && m_bJump == false && CameraState == pCamera->STATE_NORMAL)
	{
		m_move.y += 25.0f;
		//�W�����v�t���O��true��
		m_bJump = true;

		m_nPlusX = rand() % 2;
		m_nPlusZ = rand() % 2;
	}

	else if (pInputJoypad->GetTrigger(pInputJoypad->DIJS_BUTTON_2) == true && m_bJump == false && CameraState == pCamera->STATE_NORMAL)
	{//�ł������̃{�^��
		m_move.y += 25.0f;
		//�W�����v�t���O��true��
		m_bJump = true;

		m_nPlusX = rand() % 2;
		m_nPlusZ = rand() % 2;
	}

 	if (m_bJump == true)
	{
		m_move.x += sinf(pCamera->GetCamera().rotCamera.y) * 30.0f;
		m_move.z += cosf(pCamera->GetCamera().rotCamera.y) * 30.0f;
		m_fDestAngle = (pCamera->GetCamera().rotCamera.y + D3DX_PI * 1.0f);
	}

	if (m_nTryTimer > 300)
	{
		m_nTryTimer = 0;
		m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_bHit = false;
		m_bendBall = false;
		pCamera->SetState(CCamera::STATE_NORMAL);
	}

	if (CameraState != pCamera->STATE_FALL && m_bJump == true)
	{
		m_nTimer++;
	}

	if (m_nTimer > 250 && m_nTimer <= 350 && CameraState == pCamera->STATE_NORMAL)
	{
		pCamera->SetState(CCamera::STATE_NORMAL2);
	}

	if (m_nTimer > 350 && CameraState == pCamera->STATE_NORMAL2)
	{
		m_nTimer = 0;
		pCamera->SetState(CCamera::STATE_FALL);
		m_pos.y += 400.0f;

		if (m_nPlusX == 0)
		{
			m_pos.x += rand() % 300;
		}
		else
		{
			m_pos.x -= rand() % 300;
		}

		if (m_nPlusZ == 0)
		{
			m_pos.z += rand() % 300;
		}
		else
		{
			m_pos.z -= rand() % 150;
		}
	}

	if (CameraState == pCamera->STATE_FALL)
	{
		m_bJump = false;
		m_nTryTimer++;
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
	m_rot.y += m_fDiffAngle * 0.05f;
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI* 2.0f;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI* 2.0f;
	}

	//�d��
	m_move.y -= cosf(D3DX_PI * 0) * 0.1f;

	//����
	m_move.x += (0.0f - m_move.x) * 0.5f;
	m_move.z += (0.0f - m_move.z) * 0.5f;
	//�ʒu�X�V
	m_pos += m_move;

	//�n�ʂƂ̓����蔻��
	CollisitionGround();

	//m_pObject->Setpos(m_pos);
	//m_ModelMove = move;

	if (m_bHit == true && m_bendBall == false)
	{
		m_bendBall = true;
		CScore *pScore = CGame::GetScore();
		pScore->AddScore(1);

	}

#ifdef  _DEBUG
	CDebugProc::Print(1, " �{�[���̈ʒu  : ( %.1f ,%.1f ,%.1f )\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print(1, " �{�[���̃^�C�}�[  : ( %d )\n", m_nTimer);
	CDebugProc::Print(1, " �g���C�^�C�}�[  : ( %d )\n", m_nTryTimer);
#endif
#endif // 0
}

//=============================================================================
// �I�u�W�F�N�g�̕`�揈��
//=============================================================================
void CBall::Draw(void)
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
	VecLight = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.0f);
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
void CBall::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CBall::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

												// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(BG_MODEL0000, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[0], NULL, &m_nNumMat[0], &m_pMesh[0]);

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
void CBall::UnLoad(void)
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
//	���̓����蔻��
//=============================================================================
void CBall::CollisitionGround(void)
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
				//�v���C���[��Hight������
				if (((CSceneMeshField*)pScene)->GetHeightbool(m_pos))
				{
					//�����蔻��
					//m_pos.y = ((CSceneMeshField*)pScene)->GetHeight(m_pos);

					//�W�����v���Ă��Ȃ���Ԃɂ���
					m_bJump = false;
					//���n
					//m_bLand = true;
					//�������Ƃ���move������������
					m_move.y = 0.0f;

					//if (m_bJump == true)
					{
						//CShadow::SetPositionShadow(m_pos);
					}
				}
			}
		}
		//Next�Ɏ���Scene������
		pScene = pSceneNext;
	}
}

//=============================================================================
// �I�u�W�F�N�g�̈ʒu
//=============================================================================
D3DXVECTOR3 CBall::GetPos(void)
{
	return m_pos;
}
//=============================================================================
// �I�u�W�F�N�g�̈ʒu
//=============================================================================
D3DXVECTOR3 CBall::GetMove(void)
{
	return m_move;
}
//=============================================================================
// �I�u�W�F�N�g�̈ʒu
//=============================================================================
D3DXVECTOR3 CBall::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// �I�u�W�F�N�g�̈ʒu
//=============================================================================
int CBall::GetTryTimer(void)
{
	return m_nTryTimer;
}
//===============================================================================
// �����蔻��
//===============================================================================
bool CBall::CollisionObject(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
//	//�������Ă��邩�������ĂȂ���
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
				if (m_pos.y < 10)
				{
					m_bHit = true;
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