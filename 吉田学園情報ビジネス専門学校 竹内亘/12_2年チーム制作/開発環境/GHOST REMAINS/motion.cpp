//=============================================================================
//
// ���[�V�������� [motion.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS			//Fire Wall�˔j
#include <stdio.h>						//�C���N���h�t�@�C��
#include "main.h"
#include "motion.h"
#include "SceneModel.h"
#include "mesh.h"
#include "camera.h"
#include "player.h"
#include "Game.h"
#include "sound.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CCharacter::MODEL_PARTS		*CCharacter::m_partsAll[CCharParts::PARTS_MAX] = {};	//�p�[�c���
int							CMotion::m_nNumMotion = 0;				//���[�V������
CMotion						**CMotion::m_pMotion = NULL;				//���[�V�������

//=============================================================================
// ���[�V�����̏�����
//=============================================================================
void	CMotion::Load(void)
{
	FILE *pFile;
	char aStr[8][32];
	m_nNumMotion = 0;
	int nNumMotion = 0;
	m_pMotion = NULL;

	//���[�V�����̓ǂݍ���----------------------------------------------------------
	int nCntMotion[3];
	CKey *pKey;
	CAtkKey *pAtkKey;
	COneMotion *pMotion;

	pFile = fopen("data/TEXT/motion.txt", "r");

	if (pFile != NULL)//Load
	{//����
		fscanf(pFile, "%d", &nCntMotion[0]);//�t�@�C����
		m_nNumMotion = nCntMotion[0];
		m_pMotion = new CMotion*[m_nNumMotion];	//���[�V�����S�̌�����
		for (int nCntP = 0; nCntP < m_nNumMotion; nCntP++) { m_pMotion[nCntP] = new CMotion; }

		for (int nCntChar = 0; nCntChar < nCntMotion[0]; nCntChar++)
		{
			fscanf(pFile, "%s", &aStr[nCntChar][0]);//�t�@�C����
			CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "%s �ǂݍ���\n", &aStr[nCntChar][0]);
		}

		fclose(pFile);
	}
	else
	{//���s
		MessageBox(0, "���[�V����", "motion.txt�����I", MB_OK);
	}

	for (int nCntChar = 0; nCntChar < nCntMotion[0]; nCntChar++)
	{
		pFile = fopen(&aStr[nCntChar][0], "r");
		if (pFile != NULL)//Load
		{//���[�V�����t�@�C��Load
			fscanf(pFile, "%d %d\n", &nNumMotion, &m_pMotion[nCntChar]->m_nMaxParts);//���[�V������ �p�[�c��
			//����
			m_pMotion[nCntChar]->GetOneMotion() = new COneMotion[nNumMotion];

			for (int nCnt0 = 0; nCnt0 < nNumMotion; nCnt0++)
			{//���[�V��������]
				pMotion = &m_pMotion[nCntChar]->GetOneMotion()[nCnt0];
				fscanf(pFile, "%d", &pMotion->GetnMaxKey());

				//�L�[����
				pMotion->GetKey() = new CKey*[pMotion->GetnMaxKey()];

				//�L�[TYPE����
				pMotion->GetType() = new CKey::TYPE[pMotion->GetnMaxKey()];

				fscanf(pFile, "%d %d %d %d %d %d %d %d\n", 
					&pMotion->GetnNorBranch(),
					&pMotion->GetnLandBranch(),
					&pMotion->GetnStartCancel(0),
					&pMotion->GetnStartCancel(1),
					&pMotion->GetnEndCancel(0),
					&pMotion->GetnEndCancel(1),
					&pMotion->GetnOtherCancel(0),
					&pMotion->GetnOtherCancel(1)
				);

				for (int nCnt1 = 0; nCnt1 < pMotion->GetnMaxKey(); nCnt1++)
				{//�L�[����]
					pKey = pMotion->GetKey()[nCnt1];

					fscanf(pFile, "%d", &pMotion->GetType()[nCnt1]);//���[�V������ �p�[�c��

					switch (pMotion->GetType()[nCnt1])
					{//�L�[TYPE�@�����������ǒ��g�����ĂȂ�
					case CKey::TYPE_NORMAL: pMotion->GetKey()[nCnt1] = new CKey;  break;
					case CKey::TYPE_ATTACK: pMotion->GetKey()[nCnt1] = new CAtkKey;  break;
					}
					pKey = pMotion->GetKey()[nCnt1];

					fscanf(pFile, "%d %d %d %d %f %f\n",
						&pKey->GetnMoveType(),
						&pKey->GetnFloating(),
						&pKey->GetnFrame(),
						&pKey->GetnMaxEffect(),
						&pKey->GetfMove(),
						&pKey->GetfSlip()
					);//���[�V������ �p�[�c��

					  //�G�t�F�N�g�g����
					pKey->GetpEffect() = new int[pKey->GetnMaxEffect()];

					  //�p�x�g����
					pKey->GetpRot() = new D3DXVECTOR3[m_pMotion[nCntChar]->m_nMaxParts];

					fscanf(pFile, "%f %f %f\n", &pKey->GetMove().x,
						&pKey->GetMove().y,
						&pKey->GetMove().z);
					for (int nCnt2 = 0; nCnt2 < m_pMotion[nCntChar]->m_nMaxParts; nCnt2++)
					{//�p�[�c����]
						fscanf(pFile, "%f %f %f\n", &pKey->GetpRot()[nCnt2].x,
							&pKey->GetpRot()[nCnt2].y,
							&pKey->GetpRot()[nCnt2].z);
					}
					{//�p�[�c����]
						fscanf(pFile, "%f %f %f\n", &pKey->GetPos().x,
							&pKey->GetPos().y,
							&pKey->GetPos().z);
					}

					for (int nCount = 0; nCount < pKey->GetnMaxEffect(); nCount++)
					{//�p�[�c����]
						fscanf(pFile, "%d ", &pKey->GetpEffect()[nCount]);
					}

					if (pMotion->GetType()[nCnt1] == CKey::TYPE_ATTACK)
					{
						pAtkKey = (CAtkKey*)pKey;
						fscanf(pFile, "%d %d %d %d %d\n", 
							&pAtkKey->GetnAtkType(),
							&pAtkKey->GetnAtkParts(),
							&pAtkKey->GetnCntAtk(),
							&pAtkKey->GetnHitFrame(0),
							&pAtkKey->GetnHitFrame(1));

						fscanf(pFile, "%f %f\n", &pAtkKey->GetfRange(),
							&pAtkKey->GetfAtkplus()
						);
					}
				}
			}
			fclose(pFile);
		}
		else
		{//���s
			MessageBox(0, "���[�V�����f�[�^", "������!?", MB_OK);
		}
	}
	CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "���[�V�����ǂݍ��݊��� �ǂݍ��񂾃��[�V������:%d\n", m_nNumMotion);
}
//=============================================================================
// ���[�V�����̑S�I��
//=============================================================================
void CMotion::UnLoad(void)
{
	if (m_pMotion != NULL)
	{//���[�V�������ǂݍ��܂�Ă���Ȃ�
		for (int nCount = 0; nCount < m_nNumMotion; nCount++)
		{//�������ꂽ���[�V��������]
			if (m_pMotion[nCount] != NULL)
			{//���[�V��������������Ă���Ή��
				m_pMotion[nCount]->Uninit();
			}
		}//������
		m_nNumMotion = 0;
		delete[] m_pMotion;
		m_pMotion = NULL;
	}
}
//=============================================================================
// ���[�V�����̏I��
//=============================================================================
void CMotion::Uninit(void)
{
	if (m_OneMotion != NULL)
	{//���[�V�����̂���������Ă����
		for (int nCount = 0; nCount < m_nMaxMotion; nCount++)
		{//���[�V��������]
			m_OneMotion[nCount].Uninit();
		}//������
		m_nMaxMotion = 0;
		delete[] m_OneMotion;
		m_OneMotion = NULL;
	}
}
//=============================================================================
// ��̃��[�V�����I��
//=============================================================================
void COneMotion::Uninit(void)
{
	if (m_Key != NULL)
	{//�L�[����������Ă����
		for (int nCount = 0; nCount < m_nMaxKey; nCount++)
		{//�L�[����]
			if (m_Key[nCount] != NULL)
			{//��������Ă���΍폜
				m_Key[nCount]->Uninit();
			}
		}//������
		m_nMaxKey = 0;
		delete[] m_Key;
		m_Key = NULL;
	}
}
//=============================================================================
// �L�[�̏I��
//=============================================================================
void CKey::Uninit(void)
{
	if (m_pRot != NULL)
	{//�p�x����������Ă����
		delete[] m_pRot;		//1���������΂�����
		m_pRot = NULL;
	}
	if (m_pEffect != NULL)
	{//���ʂ���������Ă����
		delete[] m_pEffect;		//1���������΂�����
		m_pEffect = NULL;
	}
}

//=============================================================================
// �p�[�c�̓ǂݍ��� ��
//=============================================================================
void CCharacter::Load(CCharParts::PARTS parts)
{
	if (m_partsAll[parts] != NULL)
	{
		int nLength = (int)strlen(&m_partsAll[parts]->aText[0]);		//�������m�F

		if (nLength > 1)
		{
			D3DXLoadMeshFromX(&m_partsAll[parts]->aText[0],
				D3DXMESH_SYSTEMMEM, CManager::GetRenderer()->GetDevice(), NULL, &m_partsAll[parts]->pBuffMatModel, NULL, &m_partsAll[parts]->nNumMatModel, &m_partsAll[parts]->MeshModel);
			strcpy(&m_partsAll[parts]->aText[0], "");

			//�e�N�X�`���m�F
			CScene::Load(m_partsAll[parts]->tex);
		}
	}
}
//=============================================================================
// �p�[�c�̓ǂݍ��� ������
//=============================================================================
void CCharacter::Load(void)
{
	FILE	*pFile;
	int		nNumParts = 0;
	//int nLength;		//�������m�F

	pFile = fopen("data/TEXT/model.txt", "r");

	if (pFile != NULL)//Load
	{//����
		for (int nCountData = 0; nCountData < CCharParts::PARTS_MAX; nCountData++)
		{// X�t�@�C���̓ǂݍ���
			if (m_partsAll[nCountData] == NULL) { m_partsAll[nCountData] = new CCharacter::MODEL_PARTS; }
			//nLength = (int)strlen(&m_partsAll[nCountData]->aText[0]);
			//if (nLength < 5)
			{
				fscanf(pFile, "%s\n", &m_partsAll[nCountData]->aText[0]);	//�t�@�C����
				fscanf(pFile, "%d\n", &m_partsAll[nCountData]->tex);		//�摜
				fscanf(pFile, "%f %f %f", &m_partsAll[nCountData]->addPos.x, &m_partsAll[nCountData]->addPos.y, &m_partsAll[nCountData]->addPos.z);//�ꏊ
				if (m_partsAll[nCountData]->tex != -1) { m_partsAll[nCountData]->tex = (CScene::TEXTURE)((int)TEX_CHAR + (int)m_partsAll[nCountData]->tex); }
			}
		}
		fclose(pFile);
	}
}
//=============================================================================
// �p�[�c�̏I��
//=============================================================================
void CCharacter::UnLoad(void)
{
	for (int nCount = 0; nCount < CCharParts::PARTS_MAX; nCount++)
	{//�p�[�c�����
		if (m_partsAll[nCount] != NULL)
		{//�p�[�c����������Ă���Ή��
				// ���b�V���̊J��
			if (m_partsAll[nCount]->MeshModel != NULL)
			{
				m_partsAll[nCount]->MeshModel->Release();
				m_partsAll[nCount]->MeshModel = NULL;
			}

			// �}�e���A���̊J��
			if (m_partsAll[nCount]->pBuffMatModel != NULL)
			{
				m_partsAll[nCount]->pBuffMatModel->Release();
				m_partsAll[nCount]->pBuffMatModel = NULL;
			}
			delete m_partsAll[nCount];
			m_partsAll[nCount] = NULL;
		}
	}
}
//=============================================================================
// �L�����N�^�[�̏�����
//=============================================================================
HRESULT CCharacter::Init(void)
{
	m_addpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_addPosmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_length = D3DXVECTOR3(30.0f, 85.0f, 30.0f);
	m_FNor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nMaxParts = 0;
	m_pParts = NULL;
	m_Type = CMotion::TYPE_MAX;
	m_bJump = false;
	m_DrawType = CScene::DRAW_TYPE_NORMAL;
	m_fFramePlus = 1.0f;
	m_fInitFrame = 0.0f;
	m_fSpeed = 3.0f;
	m_fCola = 1.0f;
	m_fRot = D3DX_PI * -0.5f;
	return S_OK;
}
//=============================================================================
// �L�����N�^�[�̏I��
//=============================================================================
void CCharacter::Uninit(void)
{
	if (m_pParts != NULL) { delete[] m_pParts; m_pParts = NULL; }
	CScene::Uninit();
}
//=============================================================================
// �L�����N�^�[�̍X�V
//=============================================================================
void CCharacter::Update(bool bMove)
{
	CScene *pScene = NULL;
	D3DXVECTOR3 Vec2;
	float fTilt;
	float fRot;
	float fFrameP;
	bool bSpin = false;
	bool bLand = false;
	fFrameP = m_fFramePlus + m_fFramePlus2;

	if (m_bJump == true)
	{
		Vec2 = D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y));
		fTilt = (m_FNor.x * Vec2.x) + (m_FNor.y * Vec2.y) + (m_FNor.z * Vec2.z) /
			(sqrtf(powf(m_FNor.x, 2) + powf(m_FNor.y, 2) + powf(m_FNor.z, 2)) * sqrtf(powf(Vec2.x, 2) + powf(Vec2.y, 2) + powf(Vec2.z, 2)));
		fRot = acosf(fTilt);
		fTilt = (fTilt * -1.0f) * 2.0f;
		CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�X�� %f\n", fTilt);
		CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�p�x %f\n", fRot);
		//if (fTilt < 0.8f && fTilt < 1.2f) { fTilt = 0.0f; }
		//else { fTilt *= fTilt; }
	}

	if (m_nNumMotion[0] <= MOTION_LAND)
	{//�ړ������Ƀ��f���̌��������킹��
		float fRotPoor = m_fRot - m_rot.y;
		if (fRotPoor > D3DX_PI) { fRotPoor -= D3DX_PI * 2.0f; }
		else if (fRotPoor < -D3DX_PI) { fRotPoor += D3DX_PI * 2.0f; }
		m_rot.y += fRotPoor * 0.125f;
		if (m_rot.y > D3DX_PI) { m_rot.y -= D3DX_PI * 2; }
		if (m_rot.y < -D3DX_PI) { m_rot.y += D3DX_PI * 2; }
	}

	//if (CManager::GetInputKey()->GetTrigger(DIK_Z)) { CCharacter::ResetMotion(); }
	//if (CManager::GetInputKey()->GetTrigger(DIK_B)) { m_fFramePlus = 0.0f; }
	//if (CManager::GetInputKey()->GetTrigger(DIK_N)) { SetPlusFrame(1.0f, 120.0f); }

	//���[�V�����L�����Z���̍X�V
	CancelUpdate();
	CMotion		*pMotion = CMotion::GetMotion(m_Type);
	COneMotion	*pOneMotion = &CMotion::GetMotion(m_Type)->GetOneMotion()[m_nNumMotion[0]];
	CKey		*pKey = pOneMotion->GetKey()[m_nNumMotion[2]];
	CKey		*pKeyold;

	if (bMove)
	{//�ړ�
		if (m_nNumMotion[1] == -1 && m_bJump)
		{//���[�V�����̗\�񂪂Ȃ�
			COneMotion *pMotion = &CMotion::GetMotion(m_Type)->GetOneMotion()[m_nNumMotion[0]];
			if (pMotion->GetnOtherCancel(0) < m_fMotionFrame && m_fMotionFrame < pMotion->GetnOtherCancel(1))
			{
				m_nNumMotion[1] = MOTION_WALK;
			}
		}
		m_move += D3DXVECTOR3(sinf(m_fRot), 0.0f, cosf(m_fRot)) * -((m_fSpeed + (m_bJump ? fTilt : 0.0f)) * pKey->GetfMove() * fFrameP);
	}
	else if (m_nNumMotion[1] == -1)
	{//�ړ�����
		if (m_nNumMotion[0] == MOTION_WALK)
		{//�����Ȃ�@���ɍ��킹�ăj���[�g������
			if (m_nNumMotion[2] % 2 == 0 && m_fFrame <= 1.0f) { m_nNumMotion[1] = MOTION_NEUTRAL; }
		}
	}

	//���[�V����
	if (m_Type != CMotion::TYPE_MAX)
	{
		D3DXVECTOR3 Move;
		while (1)
		{
			if (m_fFrame < (float)pKey->GetnFrame())
			{//�t���[�����͈͓��Ȃ�
				m_move.x += (0.0f - m_move.x) * (0.3f * pKey->GetfSlip());
				m_move.z += (0.0f - m_move.z) * (0.3f * pKey->GetfSlip());
				SetEffect(pKey);	//�L�[����

				//�ړ��l���Z�L���t���[���Ȃ�
				if (m_fFrame < (float)pKey->GetnMoveType() * fFrameP)
				{
					float fRot = m_rot.y;
					Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					Move += D3DXVECTOR3(sinf(fRot), 0.0f, cosf(fRot)) * -pKey->GetMove().z;
					Move += D3DXVECTOR3(sinf(fRot + D3DX_PI * 0.5f), 0.0f, cosf(fRot + D3DX_PI * 0.5f)) * -pKey->GetMove().x;
					Move += Move * ((fFrameP - 1.0f) * 0.35f);
					float fWKData = (float)pKey->GetnMoveType() / fFrameP;
					if (fWKData < 1.0f) { fWKData = 1.0f; }
					else if (fWKData > fFrameP) { fWKData = fFrameP; }
					Move.y += pKey->GetMove().y * fWKData;

					if (pKey->GetMove().y > 0.0f)
					{
						m_bJump = false;
					}
					m_move += Move;
				}

				m_addpos += m_addPosmove * fFrameP;		//�{�̂̈ړ�
				for (int nCntModel = 0; nCntModel < m_nMaxParts; nCntModel++)
				{//�ۑ����ꂽmove��������
				 //rot�̈ړ��l���Z
					m_pParts[nCntModel]->Getaddrot() += m_pParts[nCntModel]->GetaddRotmove() * fFrameP;
					//���b�g�m�F
					if (m_pParts[nCntModel]->Getaddrot().x > D3DX_PI) { m_pParts[nCntModel]->Getaddrot().x -= D3DX_PI * 2; }
					else if (m_pParts[nCntModel]->Getaddrot().x < -D3DX_PI) { m_pParts[nCntModel]->Getaddrot().x += D3DX_PI * 2; }
					if (m_pParts[nCntModel]->Getaddrot().y > D3DX_PI) { m_pParts[nCntModel]->Getaddrot().y -= D3DX_PI * 2; }
					else if (m_pParts[nCntModel]->Getaddrot().y < -D3DX_PI) { m_pParts[nCntModel]->Getaddrot().y += D3DX_PI * 2; }
					if (m_pParts[nCntModel]->Getaddrot().z > D3DX_PI) { m_pParts[nCntModel]->Getaddrot().z -= D3DX_PI * 2; }
					else if (m_pParts[nCntModel]->Getaddrot().z < -D3DX_PI) { m_pParts[nCntModel]->Getaddrot().z += D3DX_PI * 2; }
				}
				//�i���̃t���[��
				m_fFrame += fFrameP / FRAME_SPEED;//�t���[���̐i�s
				m_fMotionFrame += fFrameP / FRAME_SPEED; //���[�V�����S�̃t���[���̐i�s
				break;
			}
			else
			{//�L�[�̏I��
				m_fFrame = 0.0f;	//�t���[���̏�����
				SetRotMotion();
				m_nNumMotion[2]++;		//�L�[�̐i��

				if (m_nNumMotion[2] >= pOneMotion->GetnMaxKey())
				{//���̃��[�V�������I��
					m_fRot = m_rot.y;	//���ȉ�]�h�~
					if (pOneMotion->GetnNorBranch() > -1)
					{
						m_fMotionFrame = 0.0f;		//�S�t���[���̏�����
						m_nNumMotion[2] = 0;		//�L�[�̏�����
						if (m_nNumMotion[0] != pOneMotion->GetnNorBranch())
						{//���[�v����Ȃ����
							m_nNumMotion[0] = pOneMotion->GetnNorBranch();	//���̃��[�V�����̕t�^
							//if (m_nNumMotion[0] == MOTION_NEUTRAL && !GetbJump())
							//{//�󒆃j���[�g������
							//	m_nNumMotion[0] = MOTION_S_NEUTRAL;
							//}	//�j���[�g�����Ȃ�
								//if (g_model_Info[nCount].set.nNumMotion[1] == MOTION_GETUP) { g_model_Info[nCount].set.nAirTime = 90; }	//�N���オ��Ȃ�
						}
						else
						{
							m_nNumMotion[0] = pOneMotion->GetnNorBranch();
							//if (g_model_Info[nCount].set.nNumMotion[1] == 0 || g_model_Info[nCount].set.nNumMotion[1] == MOTION_AIR)
							//{
							//	g_model_Info[nCount].set.state = MODEL_STATE_NONE;
							//}	//�j���[�g�����Ȃ�
						}	//���̃��[�V�����̕t�^}
						m_nNumMotion[3] = m_nNumMotion[0]; //���̃��[�V�����Ɍ��݂̃��[�V����������
					}
					else
					{//���̃L�[�ݒ肪����Ă��Ȃ��Ȃ炻�̂܂ܕ��u
						m_fMotionFrame -= pOneMotion->GetKey()[pOneMotion->GetnMaxKey() - 1]->GetnFrame();	//���[�V�����t���[����߂�
						m_nNumMotion[2]--;																	//�L�[��߂�
						m_fFrame = 0.0f;
					}
				}
				pOneMotion = &CMotion::GetMotion(m_Type)->GetOneMotion()[m_nNumMotion[0]];
				pKeyold = pKey;
				pKey = pOneMotion->GetKey()[m_nNumMotion[2]];

				m_addPosmove = (pKey->GetPos() - m_addpos) / (float)pKey->GetnFrame() / FRAME_SPEED;
				for (int nCntModel = 0; nCntModel < m_nMaxParts; nCntModel++)
				{//move���v�Z���đ��
					m_pParts[nCntModel]->Getaddrot() = pKeyold->GetpRot()[nCntModel];
					m_pParts[nCntModel]->GetaddRotmove() = (pKey->GetpRot()[nCntModel] - m_pParts[nCntModel]->Getaddrot()) / FRAME_SPEED;

					//�p�x�m�F
					if (m_pParts[nCntModel]->GetaddRotmove().x > D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().x -= D3DX_PI * 2; }
					else if (m_pParts[nCntModel]->GetaddRotmove().x < -D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().x += D3DX_PI * 2; }
					if (m_pParts[nCntModel]->GetaddRotmove().y > D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().y -= D3DX_PI * 2; }
					else if (m_pParts[nCntModel]->GetaddRotmove().y < -D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().y += D3DX_PI * 2; }
					if (m_pParts[nCntModel]->GetaddRotmove().z > D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().z -= D3DX_PI * 2; }
					else if (m_pParts[nCntModel]->GetaddRotmove().z < -D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().z += D3DX_PI * 2; }

					m_pParts[nCntModel]->GetaddRotmove() /= (float)pKey->GetnFrame();
				}
			}//�L�[�I��
		}//�X�Vwhile
		m_fFramePlus += (1.0f - m_fFramePlus) * 0.1f;
		m_fInitFrame -= m_fFramePlus / FRAME_SPEED;
		if (m_fInitFrame < 0.0f)
		{//���Ԍo�߂���������
			m_fInitFrame = 0.0f;
			m_fFramePlus2 += (0.0f - m_fFramePlus2) * 0.05f;
		}
	}

	//�ʒu���̍X�V
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		m_posold = m_pos;
		m_pos += m_move;
		if (pKey->GetnFloating() < 2 && GetObjType() != CScene::OBJTYPE_ENEMY) { m_move.y -= 0.3f; }
	}

	int		nCount = 0;
	//CMesh::MeshCollisionWall(m_pos, m_posold, m_move, m_length, m_FNor, nCount, m_bJump, false);	//���b�V����
	
	if (GetObjType() != CScene::OBJTYPE_ENEMY)
	{
		CMesh::MeshCollisionCeiling(m_pos, m_posold, m_length);											//���b�V������
		pScene = CSceneObjct::CollisionAll(m_pos, m_posold, m_move, m_length, m_FNor, nCount, m_bJump, true);	//�I�u�W�F�N�g
		CMesh::MeshCollisionWall(m_pos, m_posold, m_move, m_length, m_FNor, nCount, m_bJump, false);	//���b�V����
		//CMesh::MeshCollisionField(m_pos, m_posold, m_move, m_length, m_FNor, bLand);					//���b�V����
	}
	else { CCharacter::CollisionAll(m_pos, m_posold, m_length.x, this); }

	if (!m_bJump && bLand && pKey->GetnFloating() == 0)
	{//���n
		SetCancelMotion(pOneMotion->GetnLandBranch());
		m_move.y = 0.0f;
		m_bJump = true;
	}

	if (pScene != NULL)
	{//�����ɏ���Ă���
		D3DXVECTOR3 move;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		float		fDistance;
		float		fAngle;
		float		fPosY;
		switch (pScene->GetObjType())
		{
		case OBJTYPE_OBJ:
			move = ((CSceneObjct*)pScene)->GetMove();
			pos = ((CSceneObjct*)pScene)->GetPosold();
			rot = ((CSceneObjct*)pScene)->GetRotation() - ((CSceneObjct*)pScene)->GetRotOld();
			if (move.y < 0) { move.y = 0.0f; }
			fDistance = sqrtf(powf(pos.x - m_pos.x, 2) + powf(pos.z - m_pos.z, 2));
			fAngle = atan2f(m_pos.x - pos.x, m_pos.z - pos.z);
			fPosY = m_pos.y;
			m_pos = pos + D3DXVECTOR3(sinf(fAngle + rot.y), 0.0f, cosf(fAngle + rot.y)) * fDistance;
			m_pos.y = fPosY;
			m_pos += move;
			m_rot.y += rot.y;
			if (m_pScene == NULL) 
			{ SetCancelMotion(pOneMotion->GetnLandBranch()); m_bJump = true; }
			m_pScene = pScene;
			break;
		}
	}
	else { m_pScene = NULL; }

	if (m_pShadow != NULL)
	{
		m_pShadow->GetPosition().x = m_pos.x;
		m_pShadow->GetPosition().z = m_pos.z;

		if (m_bJump) { m_pShadow->GetPosition().y = m_pos.y - 2.0f; }
		else
		{
			if (m_pShadow->GetPosition().y > m_pos.y) { m_pShadow->GetPosition().y = m_pos.y - 2.0f; }
		}
		if (GetObjType() == CScene::OBJTYPE_ENEMY) { m_pShadow->GetPosition() = m_pos; }

	}

	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "P�t���[���F%.3f\n", fFrameP);
	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "���[�V���� ���݁F%d�@���F%d �L�[�F%d �t���[���F%.1f\n", m_nNumMotion[0], m_nNumMotion[1], m_nNumMotion[2], m_fFrame);
	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�@�� %.1f�@%.1f�@%.1f\n", m_FNor.x, m_FNor.y, m_FNor.z);
}
//=============================================================================
// ���n����
//=============================================================================
void	CCharacter::Land(void)
{
	if (!m_bJump)
	{
		COneMotion *pOneMotion = &CMotion::GetMotion(m_Type)->GetOneMotion()[m_nNumMotion[0]];

		SetCancelMotion(pOneMotion->GetnLandBranch());
		m_bJump = true;
	}
		m_move.y = 0.0f;
}
//=============================================================================
// �L�����N�^�[�̕`��
//=============================================================================
void CCharacter::Draw(void)
{
	if (CManager::GetCamera()->DrawCamera(m_pos, powf(m_length.x, 2) + powf(m_length.z, 2)))
	{
		LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
		D3DXMATRIX			mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
		D3DMATERIAL9		matDef;					//���݂̃}�e���A���ۑ��p
		D3DXMATERIAL		*pMat;					//�}�e���A���f�[�^�ւ̃|�C���^
		D3DXVECTOR3			pos, rot;

		if (CScene::DrawPrepare(m_DrawType, pDevice)) { return; };

		for (int nCntModel = 0; nCntModel < m_nMaxParts; nCntModel++)
		{//�p�[�c��������]

		 // ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&m_pParts[nCntModel]->GetmtxWorld());

			if (m_pParts[nCntModel]->GetnParent() >= 0)
			{//�q���Ȃ���Z�����
				pos = m_partsAll[m_pParts[nCntModel]->GetParts()]->addPos;
				rot = m_pParts[nCntModel]->Getaddrot();
			}
			else
			{//�e�Ȃ��Ȃ猴�_����
				pos = m_pos + m_addpos;
				pos += D3DXVECTOR3(sinf(m_rot.y) * m_partsAll[m_pParts[nCntModel]->GetParts()]->addPos.z
					, m_partsAll[m_pParts[nCntModel]->GetParts()]->addPos.y
					, cosf(m_rot.y) * m_partsAll[m_pParts[nCntModel]->GetParts()]->addPos.z);
				rot = m_pParts[nCntModel]->Getaddrot() + m_rot;
			}

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
			D3DXMatrixMultiply(&m_pParts[nCntModel]->GetmtxWorld(), &m_pParts[nCntModel]->GetmtxWorld(), &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
			D3DXMatrixMultiply(&m_pParts[nCntModel]->GetmtxWorld(), &m_pParts[nCntModel]->GetmtxWorld(), &mtxTrans);

			if (m_pParts[nCntModel]->GetnParent() >= 0)
			{//�e�̈ʒu�Ɗp�x���v���X
				D3DXMatrixMultiply(&m_pParts[nCntModel]->GetmtxWorld(), &m_pParts[nCntModel]->GetmtxWorld(), &m_pParts[m_pParts[nCntModel]->GetnParent()]->GetmtxWorld());
			}

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &m_pParts[nCntModel]->GetmtxWorld());

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);
			pMat = (D3DXMATERIAL*)m_partsAll[m_pParts[nCntModel]->GetParts()]->pBuffMatModel->GetBufferPointer();
			//�e�N�X�`���̐ݒ�
			//if (GetTexture(m_partsAll[m_pParts[nCntModel]->GetParts()]->tex) != NULL)
			//{//�e�N�X�`���̐ݒ�
			//	pDevice->SetTexture(0, GetTexture(m_partsAll[m_pParts[nCntModel]->GetParts()]->tex));
			//}//�e�N�X�`���폜

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			for (int nCountData = 0; nCountData < (int)m_partsAll[m_pParts[nCntModel]->GetParts()]->nNumMatModel; nCountData++)
			{
				// �}�e���A���̐ݒ�
				pMat = (D3DXMATERIAL*)m_partsAll[m_pParts[nCntModel]->GetParts()]->pBuffMatModel->GetBufferPointer();
				pMat[nCountData].MatD3D.Diffuse.a = m_fCola; //�����x�ݒ�

				pDevice->SetMaterial(&pMat[nCountData].MatD3D);

				// ���f��(�p�[�c)�̕`��
				m_partsAll[m_pParts[nCntModel]->GetParts()]->MeshModel->DrawSubset(nCountData);
			}

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
			pDevice->SetTexture(0, NULL);

		}
	}//�͈͓��Ȃ�`��
}
//=============================================================================
// ���[�V�����̃L�����Z���X�V
//=============================================================================
void CCharacter::CancelUpdate(void)
{
	if (m_nNumMotion[1] != -1 && m_nNumMotion[0] != m_nNumMotion[1])
	{//�\�񂪓����Ă��� && ���݂̃��[�V�����łȂ�
		COneMotion *pMotion = &CMotion::GetMotion(m_Type)->GetOneMotion()[m_nNumMotion[0]];
		bool bCancel = false;
		bool bStart = false;

		if (pMotion->GetnOtherCancel(0) < m_fFrame && m_fFrame < pMotion->GetnOtherCancel(1))
		{//�L�����Z���\
			//CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "�L�����Z���I\n");

			bCancel = true;
		}
		//else if (MOTION_ATTACK <= m_nNumMotion[1])
		//{//�\�񂪍U�����[�V�����Ȃ�
		//	if ((pMotion->GetnStartCancel(0) < m_fFrame && m_fFrame < pMotion->GetnStartCancel(1)) ||
		//		(pMotion->GetnEndCancel(0) < m_fFrame && m_fFrame < pMotion->GetnEndCancel(1)))
		//	{//�L�����Z���\
		//		bCancel = true;
		//		bStart = true;		//�X�^�[�g�L�����Z���K�p
		//	}
		//}

		if (bCancel)
		{//�L�����Z�����\
			SetCancelMotion(m_nNumMotion[1]);	//���[�V�����̃L�����Z��
			m_nNumMotion[1] = -1;				//�����[�V����������
			m_nCancelFrame = -1;				//���[�V�����L�����Z���ێ��t���[��������
		}
	}
	{//���e���ێ�
		m_nCancelFrame--;
		if (m_nCancelFrame < 0) { m_nNumMotion[1] = -1; m_nCancelFrame = 0; }//�����[�V����������
	}
}
//=============================================================================
// ���[�V�����̃L�����Z���ݒ�
//=============================================================================
void CCharacter::SetCancelMotion(int nNumber)
{
	if (m_nNumMotion[0] == MOTION_WALK && m_nNumMotion[1] == MOTION_NEUTRAL) { m_nLeg = m_nNumMotion[2]; }

	m_nNumMotion[3] = m_nNumMotion[0];	//�O���[�V�������
	m_nNumMotion[0] = nNumber;			//���[�V�����̃L�����Z��
	m_nNumMotion[2] = 0;
	m_nNumMotion[1] = -1;				//�����[�V�����̏�����
	m_fFrame = 0.0f;			//�t���[����������
	m_fMotionFrame = 0.0f;		//���[�V�����S�̃t���[����������

	if (m_nNumMotion[0] == MOTION_WALK) { m_nNumMotion[2] = m_nLeg; }		//�����Ȃ�O��̓r������

	COneMotion *pMotion = &CMotion::GetMotion(m_Type)->GetOneMotion()[m_nNumMotion[0]];
	CKey *pKey = pMotion->GetKey()[0];

	m_addPosmove = (pKey->GetPos() - m_addpos) / (float)pKey->GetnFrame() / FRAME_SPEED;
	for (int nCntModel = 0; nCntModel < m_nMaxParts; nCntModel++)
	{//move���v�Z���đ��
		m_pParts[nCntModel]->GetaddRotmove() = (pKey->GetpRot()[nCntModel] - m_pParts[nCntModel]->Getaddrot()) / FRAME_SPEED;

		//�p�x�m�F
		if (m_pParts[nCntModel]->GetaddRotmove().x > D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().x -= D3DX_PI * 2; }
		else if (m_pParts[nCntModel]->GetaddRotmove().x < -D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().x += D3DX_PI * 2; }
		if (m_pParts[nCntModel]->GetaddRotmove().y > D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().y -= D3DX_PI * 2; }
		else if (m_pParts[nCntModel]->GetaddRotmove().y < -D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().y += D3DX_PI * 2; }
		if (m_pParts[nCntModel]->GetaddRotmove().z > D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().z -= D3DX_PI * 2; }
		else if (m_pParts[nCntModel]->GetaddRotmove().z < -D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().z += D3DX_PI * 2; }

		m_pParts[nCntModel]->GetaddRotmove() /= (float)pKey->GetnFrame();
	}
}
//=============================================================================
// ���[�V�����̃��Z�b�g
//=============================================================================
void CCharacter::ResetMotion(void)
{
	m_nNumMotion[0] = 0;
	m_nNumMotion[1] = -1;
	m_nNumMotion[2] = 0;
	m_nNumMotion[3] = 0;
	m_fFrame = 99999.0f;
	SetRotMotion();
}
//=============================================================================
// ���݂̃L�[�Ɋp�x�����S�ɍ��킹��
//=============================================================================
void CCharacter::SetRotMotion(void)
{
	CKey *pKey = CMotion::GetMotion(m_Type)->GetOneMotion()[m_nNumMotion[0]].GetKey()[m_nNumMotion[2]];
	for (int nCntModel = 0; nCntModel < m_nMaxParts; nCntModel++)
	{//move���v�Z���đ��
		m_pParts[nCntModel]->Getaddrot() = pKey->GetpRot()[nCntModel];
	}
}
//=============================================================================
// �t���[���̐i�s���x�ݒ�
//=============================================================================
void CCharacter::SetPlusFrame(float fPFrame, float fCount)
{
	m_fFramePlus2 = fPFrame;
	m_fInitFrame = fCount;
}
//=============================================================================
//	�L�[���̌���
//=============================================================================
void CCharacter::SetEffect(CKey *&pKey)
{
	for (int nCount = 0; nCount < pKey->GetnMaxEffect(); nCount++)
	{
		switch (pKey->GetpEffect()[nCount])
		{
		case 0:	if (m_fFrame == 0.0f) { CManager::GetSound()->Play(CSound::LABEL_SE_WALK); } break;	//
		case 1:	if (m_fFrame == 0.0f) { CManager::GetSound()->Play(CSound::LABEL_SE_JUMP); } break;	//
		case 2:	if (m_fFrame == 0.0f) { CManager::GetSound()->Play(CSound::LABEL_SE_LAND); } break;	//

		}
	}
}
//=============================================================================
//	�S�L�����̂����蔻��
//=============================================================================
void CCharacter::CollisionAll(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, float &fLength, CScene *pChar)	//�L�������m�̂����蔻��
{
	if (CManager::GetMode() != CManager::MODE_GAME) { return; }

	CScene *pScene;

	pScene = CScene::GetTop(CHAR_PRIORITY);
	while (pScene != NULL)
	{//�I���܂�
		if (pScene->GetObjType() == OBJTYPE_ENEMY || pScene->GetObjType() == OBJTYPE_PLAYER)
		{//���b�V������
			if (pChar != pScene)
			{//�����łȂ��Ȃ�
				((CCharacter*)pScene)->Collision(pos, posold, fLength);
			}
		}
		pScene = pScene->GetpNext();
	}
}
//=============================================================================
//	�L�������m�̂����蔻��
//=============================================================================
void CCharacter::Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, float &fLength)
{
	float fDistance, fAngle;

	//�U�����Ȃ�Y����

	//���S�ђʑ΍�

	//�~�`�͈͓��Ȃ�
	fDistance = powf(m_pos.x - pos.x, 2) + powf(m_pos.z - pos.z, 2);
	if (fDistance < powf(fLength + m_length.x, 2))
	{//���g���猩���p�x�ň��l����
		fAngle = atan2f(pos.x - m_pos.x, pos.z - m_pos.z);
		pos = D3DXVECTOR3(m_pos.x, pos.y, m_pos.z) + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)) * (fLength + m_length.x);

		float &fRot = CManager::GetPlayer()->Getrot().y;
		fRot = atan2f(pos.x - m_pos.x, pos.z - m_pos.z) + D3DX_PI;
		CManager::GetPlayer()->SetCancelMotion(CCharacter::MOTION_LAND + 1);
		CManager::GetPlayer()->Getmove() += D3DXVECTOR3(sinf(fRot), 0.0f, cosf(fRot)) * 30.0f;
		CManager::GetPlayer()->Getmove().y = 5.0f;
		CManager::GetGame()->SetState(CGame::STATE_OVER);

	}
}
//=============================================================================
// �L�����N�^�[�̐ݒ�
//=============================================================================
void CCharacter::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE type)
{
	m_pos = pos; m_posold = pos;
	m_rot = rot;
	m_fRot = rot.y;
	m_Type = type;
	m_pShadow = NULL;
	if (GetObjType() != CScene::OBJTYPE_ENEMY)
	{
		CScene3D *p3D;
		if (SceneCreate(p3D, 6))
		{
			p3D->Set(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(20.0f, 0.0f, 20.0f),
				CScene::TEX_Shadow, 0, 1, 1, false, CScene::DRAW_TYPE_ZSUBTRACT);
			m_pShadow = p3D;
		}
	}

	switch (type)
	{
	case CMotion::TYPE_BOX_Sword:	CCharParts::SetPlayer(m_pParts, m_nMaxParts);	break;
	case CMotion::TYPE_ENEMY:	CCharParts::SetEnemy(m_pParts, m_nMaxParts);	break;

	}
	
}
//=============================================================================
// �p�[�c�̐ݒ�
//=============================================================================
void CCharParts::SetParts(PARTS parts, int nPair)
{
	m_type = parts;
	m_nParent = nPair;
	CCharacter::Load(m_type);
}
//=============================================================================
// �L�����N�^�[�̐ݒ�
//=============================================================================
void CCharParts::SetPlayer(CCharParts **&Parts, int &nMaxParts)
{
	nMaxParts = 15;

	if (Parts == NULL) 
	{ 
		Parts = new CCharParts*[nMaxParts];
		for (int nCount = 0; nCount < nMaxParts; nCount++)
		{
			Parts[nCount] = new CCharParts;
		}
	}
	
	for (int nCount = 0; nCount < nMaxParts; nCount++)
	{
		Parts[nCount]->GetaddRotmove() = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Parts[nCount]->Getaddrot() = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	}
	Parts[0]->SetParts(PLAYER_hara, -1);
	Parts[1]->SetParts(PLAYER_hip, 0);
	Parts[2]->SetParts(PLAYER_head, 0);
	Parts[3]->SetParts(PLAYER_armUL, 0);
	Parts[4]->SetParts(PLAYER_armDL, 3);
	Parts[5]->SetParts(PLAYER_handL, 4);
	Parts[6]->SetParts(PLAYER_armUR, 0);
	Parts[7]->SetParts(PLAYER_armDR, 6);
	Parts[8]->SetParts(PLAYER_handR, 7);
	Parts[9]->SetParts(PLAYER_legUL, 1);
	Parts[10]->SetParts(PLAYER_legDL, 9);
	Parts[11]->SetParts(PLAYER_footL, 10);
	Parts[12]->SetParts(PLAYER_legUR, 1);
	Parts[13]->SetParts(PLAYER_legDR, 12);
	Parts[14]->SetParts(PLAYER_footR, 13);
}
//=============================================================================
// �G�̐ݒ�
//=============================================================================
void CCharParts::SetEnemy(CCharParts **&Parts, int &nMaxParts)
{
	nMaxParts = 1;

	if (Parts == NULL)
	{
		Parts = new CCharParts*[nMaxParts];
		for (int nCount = 0; nCount < nMaxParts; nCount++)
		{
			Parts[nCount] = new CCharParts;
		}
	}

	for (int nCount = 0; nCount < nMaxParts; nCount++)
	{
		Parts[nCount]->GetaddRotmove() = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Parts[nCount]->Getaddrot() = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	Parts[0]->SetParts(ENEMY, -1);
}