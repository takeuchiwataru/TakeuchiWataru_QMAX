//=============================================================================
//
// �|���S������ [Scene3D.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene.h"
#include"SceneModel.h"
#include "SceneAnim3D.h"
#include"mesh.h"
#include"Font.h"
#include"Renderer.h"
#include "manager.h"
#include "camera.h"
#include "sound.h"
#include "player.h"
#include "enemy.h"
#include "Game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CSceneModel::MODEL_DRAW *CSceneModel::m_Model_Draw[MODEL_MAX] = {};	//���f���ւ̃|�C���^
bool CSceneObjct::m_bSwitch[MAX_SWITCH];	//�X�C�b�`

//==================================================================================================//
//    * ���f�������֐� *
//==================================================================================================//
void	CSceneModel::LoadModel(MODEL model, LPDIRECT3DTEXTURE9 &tex)
{
	if (model < MODEL_MAX)
	{//�͈͊m�F
		switch (model)
		{
		case MODEL_FENCE: tex = Load(TEX_Fence);		break;
		case MODEL_BOX: tex = Load(TEX_Fence);			break;
		case MODEL_STONE: tex = Load(TEX_Stone);		break;
		case MODEL_STONE_S: tex = Load(TEX_Stone);		break;
		case MODEL_STEEL: tex = Load(TEX_Steel);		break;
		case MODEL_STEEL_B: tex = Load(TEX_Steel);		break;
		case MODEL_BROCK: tex = Load(TEX_Brock);		break;
		case MODEL_DFIELD: tex = Load(TEX_DBlock);		break;
		case MODEL_MFIELD: tex = Load(TEX_MBlock);		break;
		case MODEL_MFIELD2: tex = Load(TEX_MBlock);		break;
		case MODEL_SPEAR: tex = Load(TEX_Spear);		break;
		case MODEL_BUTTON: tex = Load(TEX_Button);		break;
		case MODEL_WARP: tex = Load(TEX_Button);		break;
		case MODEL_NOLOOK: tex = Load(TEX_Button);		break;
		case MODEL_BUTTONFLOR: tex = Load(TEX_Button);	break;
		case MODEL_DROP_STONE: tex = Load(TEX_DropStone);	break;
		}

		if (m_Model_Draw[model] == NULL)
		{//�ǂݍ���łȂ��Ȃ�
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			m_Model_Draw[model] = new MODEL_DRAW;
			switch (model)
			{//�ǂݍ���
			case MODEL_FENCE:
				D3DXLoadMeshFromX("data/MODEL/OBJECT/Fence.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_BOX:
				D3DXLoadMeshFromX("data/MODEL/OBJECT/Box.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break; 
			case MODEL_STONE:
				D3DXLoadMeshFromX("data/MODEL/OBJECT/stone.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_STONE_S:
				D3DXLoadMeshFromX("data/MODEL/OBJECT/stone_S.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_STEEL:
				D3DXLoadMeshFromX("data/MODEL/OBJECT/steel.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_STEEL_B:
				D3DXLoadMeshFromX("data/MODEL/OBJECT/steel_block.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_BROCK:
				D3DXLoadMeshFromX("data/MODEL/StageObject/Brock.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_DFIELD:
				D3DXLoadMeshFromX("data/MODEL/StageObject/DropField000.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_MFIELD:
				D3DXLoadMeshFromX("data/MODEL/StageObject/MoveField000.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_MFIELD2:
				D3DXLoadMeshFromX("data/MODEL/StageObject/MoveField001.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_SPEAR:
				D3DXLoadMeshFromX("data/MODEL/StageObject/Spear002.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_BUTTON:
				D3DXLoadMeshFromX("data/MODEL/StageObject/buttun.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_BUTTONFLOR:
				D3DXLoadMeshFromX("data/MODEL/StageObject/buttnflor.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_DROP_STONE:
				D3DXLoadMeshFromX("data/MODEL/StageObject/DropStone.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_GOAL:
				D3DXLoadMeshFromX("data/MODEL/StageObject/Goal.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_WARP:
				D3DXLoadMeshFromX("data/MODEL/StageObject/buttun_Warp.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_NOLOOK:
				D3DXLoadMeshFromX("data/MODEL/StageObject/buttun_NoLook.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			}
		}
	}
}
//==================================================================================================//
//    * ���f�������֐� *
//==================================================================================================//
void	CSceneModel::UnLoadModel(void)
{
	for (int nCount = 0; nCount < MODEL_MAX; nCount++)
	{
		if (m_Model_Draw[nCount] != NULL)
		{
			// ���b�V���̊J��
			if (m_Model_Draw[nCount]->MeshModel != NULL)
			{
				m_Model_Draw[nCount]->MeshModel->Release();
				m_Model_Draw[nCount]->MeshModel = NULL;
			}

			// �}�e���A���̊J��
			if (m_Model_Draw[nCount]->pBuffMatModel != NULL)
			{
				m_Model_Draw[nCount]->pBuffMatModel->Release();
				m_Model_Draw[nCount]->pBuffMatModel = NULL;
			}
			delete m_Model_Draw[nCount]; m_Model_Draw[nCount] = NULL;
		}
	}
}
//=============================================================================
// ����������
//=============================================================================
HRESULT	CSceneModel::Init(void)
{
	m_DrawType = CScene::DRAW_TYPE_NORMAL;
	m_pTex = NULL;
	m_fCntState = 0.0f;
	m_Model = MODEL_MAX;

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void	CSceneModel::Update(void)
{
	switch (m_state)
	{
	case STATE_FADEIN:	//���񂾂񖾂邭
		m_col.a += 0.03f;
		if (m_col.a >= 1.0f) { m_col.a = 1.0f; m_state = STATE_NORMAL; }
		break;
	case STATE_FADEOUT:	//���񂾂�Â�
		m_col.a -= 0.03f;
		if (m_col.a <= 0.0f) { Uninit(); return; }
		break;
	case STATE_FADE:	//���񂾂񖾂邭->�Â��Ȃ������
		m_col.a += 0.03f;
		if (m_col.a >= 1.0f) { m_col.a = 1.0f; m_state = STATE_FADEOUT; }
		break;
		
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void	CSceneModel::Draw(void)
{
	if (m_Model != MODEL_MAX)
	{
		D3DXVECTOR3 length;
		GetLength(m_Model, length);
		if (CManager::GetCamera()->DrawCamera(m_pos, powf(length.x, 2) + powf(length.z, 2)))
		{
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			D3DXMATRIX			mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
			D3DMATERIAL9		matDef;					//���݂̃}�e���A���ۑ��p
			D3DXMATERIAL		*pMat;					//�}�e���A���f�[�^�ւ̃|�C���^
			D3DXMATRIX			mtxWorld;		//���[���h�}�g���b�N�X

			if (CScene::DrawPrepare(m_DrawType, pD3DDevice)) { return; }

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

			// ���݂̃}�e���A�����擾
			pD3DDevice->GetMaterial(&matDef);
			pMat = (D3DXMATERIAL*)m_Model_Draw[m_Model]->pBuffMatModel->GetBufferPointer();

			if (m_pTex != NULL)
			{//�e�N�X�`���̐ݒ�
				pD3DDevice->SetTexture(0, m_pTex);
			}

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			for (int nCountData = 0; nCountData < (int)m_Model_Draw[m_Model]->nNumMatModel; nCountData++)
			{
				// �}�e���A���̐ݒ�
				pMat = (D3DXMATERIAL*)m_Model_Draw[m_Model]->pBuffMatModel->GetBufferPointer();
				//pMat[nCountData].MatD3D.Diffuse = m_col; //�����x�ݒ�
				pD3DDevice->SetMaterial(&pMat[nCountData].MatD3D);
				// ���f��(�p�[�c)�̕`��
				m_Model_Draw[m_Model]->MeshModel->DrawSubset(nCountData);
			}

			// �}�e���A�����f�t�H���g�ɖ߂�
			pD3DDevice->SetMaterial(&matDef);
			pD3DDevice->SetTexture(0, NULL);
		}
	}
}
//=============================================================================
// �ݒ菈��
//=============================================================================
void	CSceneModel::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL model, DRAW_TYPE DrawType, bool bHit)
{
	m_pos = pos;
	m_rot = rot;
	m_col = col;
	m_Model = model;
	m_DrawType = DrawType;
	
	//���f���̂����蔻��̗L��
	CScene::SetObjType(OBJTYPE_OBJ);
	if(!bHit){ CScene::SetObjType(OBJTYPE_OBJ_NO); }

	//���f���Ɖ摜����
	LoadModel(m_Model, m_pTex);
}
//=============================================================================
// ���f���̑傫�����l��
//=============================================================================
void	CSceneModel::GetLength(MODEL model, D3DXVECTOR3 &length)
{
	switch (model)
	{
	case MODEL_FENCE:	length = D3DXVECTOR3(10.0f, 50.0f, 50.0f);		return;
	case MODEL_BOX:		length = D3DXVECTOR3(30.0f, 30.0f, 30.0f);		return;
	case MODEL_STONE:	length = D3DXVECTOR3(100.0f, 400.0f, 100.0f);	return;
	case MODEL_STONE_S:	length = D3DXVECTOR3(25.0f, 35.0f, 25.0f);		return;
	case MODEL_STEEL:	length = D3DXVECTOR3(35.0f, 20.0f, 65.0f);		return;
	case MODEL_STEEL_B:	length = D3DXVECTOR3(100.0f, 100.0f, 100.0f);	return;
	case MODEL_SPEAR:	length = D3DXVECTOR3(101.0f, 40.0f, 101.0f);	return;
	case MODEL_MFIELD:	length = D3DXVECTOR3(50.0f, 10.0f, 50.0f);		return;
	case MODEL_MFIELD2:	length = D3DXVECTOR3(90.0f, 10.0f, 50.0f);		return;
	case MODEL_DFIELD:	length = D3DXVECTOR3(100.0f, 10.0f, 100.0f);	return;
	case MODEL_BROCK:	length = D3DXVECTOR3(100.0f, 70.0f, 100.0f);	return;

	}
	length = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
// �Z�b�g���̍������l��
//=============================================================================
float	CSceneModel::GetHeight(MODEL model)
{
	switch (model)
	{
	case MODEL_FENCE:
	case MODEL_BOX:
	case MODEL_STONE:
	case MODEL_STONE_S:
	case MODEL_STEEL:
	case MODEL_STEEL_B:
		return 0.0f;
	}
	return 0.0f;
}
//=============================================================================
// �ݒ菈��
//=============================================================================
void	CSceneObjct::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL model, bool bHit, USE use, D3DXVECTOR3 speed, float fPlusRot, int nReturn, int nStop, int nCntReturn, int nNumber)
{
	CSceneModel::Set(pos, rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), model, CScene::DRAW_TYPE_NORMAL, bHit);
	m_use = use;
	m_speed = speed;
	m_speed.y = 0.0f;
	m_fPlusRot = fPlusRot;
	m_nReturn = nReturn;
	m_nStop = nStop;
	m_move = D3DXVECTOR3(0.0f, speed.y, 0.0f);
	m_nCntStop = -nCntReturn;

	m_nCntReturn = 0;
	m_nNumber = nNumber;
	if (GetModel() == MODEL_DROP_STONE) { GetDrawType() = CScene::DRAW_TYPE_NO; }
}
//=============================================================================
// ����������
//=============================================================================
HRESULT	CSceneObjct::Init(void)
{
	CSceneModel::Init();
	m_nNumber = 0;
	SetObjType(OBJTYPE_OBJ_NO);
	return S_OK;
}
//=============================================================================
// �X�V����
//=============================================================================
void	CSceneObjct::Update(void)
{
	if (m_bSwitch[m_nNumber] || GetModel() == MODEL_BUTTON)
	{
		D3DXCOLOR &col = GetColor();
		CSceneModel::STATE &state = GetState();
		float &fRot = GetRotation().y;

		switch (state)
		{
		case STATE_FADEIN:	//���񂾂񖾂邭
			col.a += 0.03f;
			if (col.a >= 1.0f) { col.a = 1.0f; state = CSceneModel::STATE_NORMAL; }
			break;
		case STATE_FADEOUT:	//���񂾂�Â�
			col.a -= 0.03f;
			if (col.a <= 0.0f) { Uninit(); return; }
			break;
		case STATE_FADE:	//���񂾂񖾂邭->�Â��Ȃ������
			col.a += 0.03f;
			if (col.a >= 1.0f) { col.a = 1.0f; state = CSceneModel::STATE_FADEOUT; }
			break;
		}

		if (m_nCntStop > 0)
		{
			m_nCntStop++;
			if (m_nCntStop > m_nStop) { m_nCntStop = 0; }
			m_move.x = 0.0f;
			m_move.z = 0.0f;

		}
		else
		{
			m_rotold = GetRotation();
			m_posold = GetPosition();

			if (m_fPlusRot != 0.0f)
			{//��]��
				fRot += m_fPlusRot;
				m_move += D3DXVECTOR3(sinf(fRot), 0.0f, cosf(fRot)) * m_speed.x;
				m_move.x *= 0.3f;
				m_move.z *= 0.3f;

				GetPosition() += m_move;
			}
			else
			{
				m_nCntReturn++;
				if (m_nReturn > 0 && m_nCntReturn > m_nReturn)
				{
					if (0 < m_nStop) { m_nCntStop = 1; };
					m_nCntReturn = 0;
					m_speed *= -1;
					m_move.y *= -1;
					if (CManager::GetMode() == CManager::MODE_GAME)
					{
						if (GetModel() == MODEL_SPEAR) { CManager::GetSound()->Play(CSound::LABEL_SE_SPEAR); }
					}
				}
				m_move += D3DXVECTOR3(sinf(fRot), 0.0f, cosf(fRot)) * -m_speed.z;
				m_move.y += m_speed.y;

				m_move.x *= 0.3f;
				m_move.z *= 0.3f;

				GetPosition() += m_move;
			}
		}

		if (CManager::GetMode() != CManager::MODE_GAME) { return; }

		if (GetModel() == MODEL_SPEAR)
		{
			D3DXVECTOR3 &pos = CManager::GetPlayer()->Getpos();
			D3DXVECTOR3 &m_pos = GetPosition();

			if (m_pos.y + 50.0f > pos.y && m_pos.y - 80.0f < pos.y)
			{//Y�͈͓�
				if (m_pos.x + 100.0f > pos.x && m_pos.x - 100.0f < pos.x &&
					m_pos.z + 100.0f > pos.z && m_pos.z - 100.0f < pos.z)
				{
					CManager::GetPlayer()->SetCancelMotion(CCharacter::MOTION_LAND + 1);
					CManager::GetGame()->SetState(CGame::STATE_OVER);
				}
			}
		}
		if (GetModel() == MODEL_WARP)
		{
			if (!CEnemy::GetbWarp())
			{
				D3DXVECTOR3 &pos = CManager::GetPlayer()->Getpos();
				D3DXVECTOR3 &m_pos = GetPosition();
				if (m_pos.x + 50.0f > pos.x && m_pos.x - 50.0f < pos.x &&
					m_pos.z + 50.0f > pos.z && m_pos.z - 50.0f < pos.z)
				{
					CEnemy::GetbWarp() = true;//����true
					CManager::GetSound()->Play(CSound::LABEL_SE_SWICH);
					CManager::GetSound()->Play(CSound::LABEL_SE_APPIROBJ);
					CFont *pFont;
					if (SceneCreate(pFont, 5))
					{
						pFont->Set(RECT{ 0, 0, 1280, 720 }, D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), "���_���s�ӑł����l�����܂���", 0, DT_CENTER, 0, true, CFont::STATE_ENDOUT);
						pFont->GetfCntState() = 0.01f;
					}
				}
			}
			else { GetPosition().y -= 0.75f; }
		}
		if (GetModel() == MODEL_NOLOOK)
		{
			if (!CEnemy::GetbLook())
			{
				D3DXVECTOR3 &pos = CManager::GetPlayer()->Getpos();
				D3DXVECTOR3 &m_pos = GetPosition();
				if (m_pos.x + 50.0f > pos.x && m_pos.x - 50.0f < pos.x &&
					m_pos.z + 50.0f > pos.z && m_pos.z - 50.0f < pos.z)
				{
					CEnemy::GetbLook() = true;//����true
					CManager::GetSound()->Play(CSound::LABEL_SE_SWICH);
					CManager::GetSound()->Play(CSound::LABEL_SE_APPIROBJ);
					CFont *pFont;
					if (SceneCreate(pFont, 5))
					{
						pFont->Set(RECT{ 0, 25, 1280, 720 }, D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), "���_���B�����l�����܂���", 0, DT_CENTER, 0, true, CFont::STATE_ENDOUT);
						pFont->GetfCntState() = 0.01f;
					}
				}
			}
			else { GetPosition().y -= 0.75f; }
		}

		if (GetModel() == MODEL_BUTTON)
		{
			if (!m_bSwitch[m_nNumber])
			{
				D3DXVECTOR3 &pos = CManager::GetPlayer()->Getpos();
				D3DXVECTOR3 &m_pos = GetPosition();
				if (m_pos.x + 50.0f > pos.x && m_pos.x - 50.0f < pos.x &&
					m_pos.z + 50.0f > pos.z && m_pos.z - 50.0f < pos.z)
				{
					m_bSwitch[m_nNumber] = true;//����true
					CManager::GetSound()->Play(CSound::LABEL_SE_SWICH);
					CManager::GetSound()->Play(CSound::LABEL_SE_APPIROBJ);
				}
			}
			else
			{//������
				GetPosition().y -= 0.75f;
			}
		}
		if (GetModel() == MODEL_DROP_STONE)
		{
			if (GetDrawType() == CScene::DRAW_TYPE_NO)
			{
				D3DXVECTOR3 &pos = CManager::GetPlayer()->Getpos();
				D3DXVECTOR3 &m_pos = GetPosition();
				if (m_pos.x + 300.0f > pos.x && m_pos.x - 300.0f < pos.x &&
					m_pos.z + 300.0f > pos.z && m_pos.z - 300.0f < pos.z)
				{
					GetDrawType() = CScene::DRAW_TYPE_NORMAL;
					CScene3D *p3D;
					if (SceneCreate(p3D, 6))
					{
						p3D->Set(D3DXVECTOR3(m_pos.x, 500.0f, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(320.0f, 0.0f, 320.0f),
							CScene::TEX_Shadow, 0, 1, 1, false, CScene::DRAW_TYPE_ZSUBTRACT);
						p3D->GetState() = CScene3D::STATE_DSTONE;
					}
					CManager::GetCamera()->SetnQuake(120, 0.000005f);
					CManager::GetSound()->Play(CSound::LABEL_SE_DropBrock);
				}
			}
			else
			{
				GetPosition().y -= 3.0f;
				D3DXVECTOR3 &pos = CManager::GetPlayer()->Getpos();
				D3DXVECTOR3 &m_pos = GetPosition();
				if (m_pos.y + 200.0f > pos.y && m_pos.y - 200.0f < pos.y)
				{
					float fDistance = powf(m_pos.x - pos.x, 2) + powf(m_pos.z - pos.z, 2);//����
					if (fDistance <= 200.0f * 200.0f)
					{//�͈͓��Ȃ�
						CManager::GetPlayer()->SetCancelMotion(CCharacter::MOTION_LAND + 1);
						CManager::GetGame()->SetState(CGame::STATE_OVER);
					}
				}
				if (GetPosition().y <= 450.0f)
				{
					CSceneAnim3D *pAnim;
					CManager::GetCamera()->SetnQuake(180, 0.000025f);
					CManager::GetSound()->Play(CSound::LABEL_SE_DropBrock);
					Uninit();
					if (SceneCreate(pAnim, 4))
					{
						pAnim->Set(GetPosition(),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(1000.0f, 1000.0f, 1.0f), CScene::TEX_Fire, true,
							CScene::DRAW_TYPE_ADD, 0, 8, 1, 10, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL);
					}
					if (SceneCreate(pAnim, 4))
					{
						pAnim->Set(GetPosition(),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(1200.0f, 1200.0f, 1.0f), CScene::TEX_Fire, true,
							CScene::DRAW_TYPE_MULTIPLY, 0, 8, 1, 12, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL);
					}
				}
			}
		}
		if (GetModel() == MODEL_GOAL)
		{
			D3DXVECTOR3 &pos = CManager::GetPlayer()->Getpos();
			D3DXVECTOR3 &m_pos = GetPosition();
			if (m_pos.x + 180.0f > pos.x && m_pos.x - 180.0f < pos.x &&
				m_pos.z + 150.0f > pos.z && m_pos.z - 150.0f < pos.z)
			{
				CManager::GetPlayer()->GetnNumMotion(1) = CCharacter::MOTION_LAND + 3;
				CManager::GetGame()->SetState(CGame::STATE_CLEAR);
			}
		}
	}
}
//=============================================================================
// �I�u�W�F���Ƃ̕`�揈��
//=============================================================================
void	CSceneObjct::Draw(void)
{
	if (m_bSwitch[m_nNumber] || GetModel() == MODEL_BUTTON) { CSceneModel::Draw(); }
}
//=============================================================================
// �I�u�W�F���Ƃ̏I������
//=============================================================================
void	CSceneObjct::DropUninit(void)
{
	//float fRand;

	//switch (m_use)
	//{
	//case USE_DROP:		if (rand() % 8 == 0) { DropItem(GetPosition()[0], 100, 15); } break;
	//case USE_DROP10:	if (!DropExplosion()) { return; }
	//case USE_DROP00:	DropItem(GetPosition()[0], 25, 10); break;
	//case USE_DROP11:	if (!DropExplosion()) { return; }
	//case USE_DROP01:	fRand = (rand() % (int)(D3DX_PI * 200.0f)) * 0.01f; for (int nCount = 0; nCount < 2; nCount++)
	//{ DropItem(GetPosition()[0] + D3DXVECTOR3(sinf(fRand + D3DX_PI * nCount), 0.0f, cosf(fRand + D3DX_PI * nCount)) * 5.0f, 6, 10); } break;
	//case USE_DROP12:	if (!DropExplosion()) { return; }
	//case USE_DROP02:	fRand = (rand() % (int)(D3DX_PI * 200.0f)) * 0.01f; for (int nCount = 0; nCount < 3; nCount++)
	//{ DropItem(GetPosition()[0] + D3DXVECTOR3(sinf(fRand + (D3DX_PI * 2 / 3) * nCount), 0.0f, cosf(fRand + (D3DX_PI * 2 / 3) * nCount)) * 5.0f, 8, 15); } break;
	//}
	CSceneModel::Uninit();
}
//=============================================================================
// �����h���b�v
//=============================================================================
bool	CSceneObjct::DropExplosion(void)
{
	if (GetColor().g <= 0.0f)
	{//����
		return true;
	}
	else
	{//�҂�
		if (GetColor().g > 0.1f) { GetColor() = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f); }
	}
	return false;
}
//=============================================================================
//�A�C�e���h���b�v�֐�
//=============================================================================
void	CSceneObjct::DropItem(D3DXVECTOR3 &pos, int nPercent, int nLucky)
{

}
//=============================================================================
//�����蔻�� �I�u�W�F�N�g��T��
//=============================================================================
CScene	*CSceneObjct::CollisionAll(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, int &nCntHit, bool &bJump, bool bReflection)
{
	CScene *pSceneR = NULL;
	CScene *pSceneS = NULL;
	int nCount = nCntHit;
	CScene *pScene = CScene::GetTop(MODEL_PRIORITY);
	while (pScene != NULL)
	{//�I���܂�
		if (pScene->GetObjType() == OBJTYPE_OBJ)
		{//���b�V������
			if (m_bSwitch[((CSceneObjct*)pScene)->m_nNumber])
			{//���g�̃X�C�b�`��true�Ȃ�
				pSceneS = ((CSceneObjct*)pScene)->Collision(pos, posold, move, length, FNor, nCntHit, bJump, bReflection);
				if (pSceneS != NULL) 
				{ pSceneR = pSceneS; }
			}
		}
		pScene = pScene->GetpNext();
		//if (nCount != nCntHit && nCntHit < 3) { pScene = CScene::GetTop(MODEL_PRIORITY); nCount = nCntHit; }
	}

	return pSceneR;
}
//=============================================================================
//�����蔻��
//=============================================================================
CScene	*CSceneObjct::Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, int &nCntHit, bool &bJump, bool bReflection)
{
	CScene *pScene = NULL;
	D3DXVECTOR3 lengthX; GetLength(GetModel(), lengthX);	//���f���̕��l��
	D3DXVECTOR3 m_pos = GetPosition();
	float fDistance = powf(lengthX.x, 2) + powf(lengthX.z, 2);	//���_���璸�_�܂ł̋����l��
	if (powf(m_pos.x - pos.x, 2) + powf(m_pos.z - pos.z, 2) < fDistance * 2.0f)
	{//�͈͓��Ȃ�
		fDistance = sqrtf(fDistance);
		int  nHit;
		float fHeight = pos.y;
		float fWKLength = 0.0f;
		float m_frot = GetRotation().y;
		float fRot = atan2f(lengthX.x, lengthX.z);			//���_�̊p�x�����߂�
		D3DXVECTOR3 WKnor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 WKpos = pos;
		D3DXVECTOR3 Vtx[8];										//����p8���_�p��
		bool bJudge = false;

		//����, �E��, ����, �E���̏�
		Vtx[2] = D3DXVECTOR3(sinf(m_frot - fRot), 0.0f, cosf(m_frot - fRot)) * fDistance + m_pos;
		Vtx[3] = D3DXVECTOR3(sinf(m_frot + fRot), 0.0f, cosf(m_frot + fRot)) * fDistance + m_pos;
		Vtx[1] = D3DXVECTOR3(sinf(m_frot + fRot + D3DX_PI), 0.0f, cosf(m_frot + fRot + D3DX_PI)) * fDistance + m_pos;
		Vtx[0] = D3DXVECTOR3(sinf(m_frot - fRot + D3DX_PI), 0.0f, cosf(m_frot - fRot + D3DX_PI)) * fDistance + m_pos;

		Vtx[6] = Vtx[2] + D3DXVECTOR3(sinf(m_frot + D3DX_PI * -0.25f), 0.0f, cosf(m_frot + D3DX_PI * -0.25f)) * (length.x);
		Vtx[7] = Vtx[3] + D3DXVECTOR3(sinf(m_frot + D3DX_PI * 0.25f), 0.0f, cosf(m_frot + D3DX_PI * 0.25f)) * (length.x);
		Vtx[5] = Vtx[1] + D3DXVECTOR3(sinf(m_frot + D3DX_PI * -0.75f), 0.0f, cosf(m_frot + D3DX_PI * -0.75f)) * (length.x);
		Vtx[4] = Vtx[0] + D3DXVECTOR3(sinf(m_frot + D3DX_PI * 0.75f), 0.0f, cosf(m_frot + D3DX_PI * 0.75f)) * (length.x);
		//�V��
		if (CMesh::FieldCheck(Vtx[6], Vtx[7], Vtx[5], Vtx[4], WKpos))
		{//�͈͓�
			fHeight = CMesh::FieldCollision(Vtx[2], Vtx[3], Vtx[1], Vtx[0], WKpos, pos, WKnor);
			if (fHeight - lengthX.y - length.y < pos.y && fHeight - lengthX.y - length.y >= posold.y) { pos.y = fHeight - lengthX.y - length.y; }
			else
			{
				//��
				CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "����\\n");
				if (fHeight + lengthX.y > pos.y - (bJump ? 10.0f : 0.0f) && fHeight + lengthX.y <= posold.y)
				{
					if (GetModel() != MODEL_SPEAR)
					{
						if (GetModel() == MODEL_DFIELD) { m_speed.y = -0.05f; }//�����鏰�Ȃ�
						pos.y = fHeight + lengthX.y;
						FNor = WKnor;
						move.y = 0.0f;
						pScene = this;
						bJump = true;
						bJudge = true;
						CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�i���o�[�F%d\n", m_nNumber);
						if (m_bSwitch[m_nNumber]) { CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�X�C�b�` true\n"); }

					}
				}
			}
		}
		//if (!bJudge)
		{
			if (GetModel() != MODEL_SPEAR || m_nCntStop > 0)
			{
			for (int nCount = 0; nCount < 4; nCount++)
			{//4��������
				//��
				nHit = CMesh::WallCollision(Vtx[nCount % 4], Vtx[(nCount + 1) % 4], WKpos, posold, move, length.x, nCntHit, bReflection);
				if (nHit != 0)
				{//XZ�œ�������
				 //�O�ςłx�`�F�b�N
					float fDistance2[2];
					float fAngle[3];
					float fPlus = 75.0f;

					fDistance2[0] = sqrtf(powf((WKpos.x - posold.x), 2) + powf((WKpos.z - posold.z), 2));	//�I�u�W�F
					fDistance2[1] = sqrtf(powf((pos.x - posold.x), 2) + powf((pos.z - posold.z), 2));		//�Ώ�

					if (GetModel() == MODEL_BROCK) { fPlus = 700.0f; }

					fAngle[0] = atan2f(fDistance2[0], (m_pos.y + lengthX.y - 90.0f) - (pos.y - (bReflection ? length.y : 0.0f)));
					fAngle[1] = atan2f(fDistance2[0], (m_pos.y - lengthX.y - fPlus) - (pos.y + (bReflection ? length.y : 0.0f)));
					fAngle[2] = 1.57f;
					if (CMesh::AngleCheck(fAngle[2], fAngle[0]) > 0 && CMesh::AngleCheck(fAngle[2], fAngle[1]) < 0)
					{//Y�͈͓�
						pos.x = WKpos.x;
						pos.z = WKpos.z;

					}
					else
					{//Y�͈͊O�ׂ̈��̃I�u�W�F�N�g�͖���
						nCntHit = 10; break;
					}
					//if (m_pos.y + lengthX.y > pos.y && m_pos.y - lengthX.y - fPlus < pos.y)
					//{
					//	pos.x = WKpos.x;
					//	pos.z = WKpos.z;
					//}
					bJudge = false;
				}
				if (nHit == 2) { break; }
			}
		}	
		}
	}//if(�͈͓��Ȃ�)

	return pScene;
}
//=============================================================================
//�����蔻�� �I�u�W�F��������
//=============================================================================
void	CSceneObjct::CollisionAllR(void)
{
	CScene *pScene = CScene::GetTop(MODEL_PRIORITY);
	CScene *pScene2;

	while (pScene != NULL)
	{//�I���܂�
		if (pScene->GetObjType() == OBJTYPE_OBJ)
		{//�I�u�W�F����
			pScene2 = CScene::GetTop(CHAR_PRIORITY);
			while (pScene2 != NULL)
			{//�I���܂�
				((CSceneObjct*)pScene)->CollisionR(pScene2);
				pScene2 = pScene2->GetpNext();
			}
		}
		pScene = pScene->GetpNext();
	}

	while (pScene != NULL)
	{//�I���܂�
		if (pScene->GetObjType() == OBJTYPE_PLAYER)
		{//
		}
		pScene = pScene->GetpNext();
	}
}
//=============================================================================
//�����蔻�� �I�u�W�F��������
//=============================================================================
void	CSceneObjct::CollisionR(CScene *pScene)
{
	D3DXVECTOR3 lengthX; GetLength(GetModel(), lengthX);	//���f���̕��l��
	D3DXVECTOR3 length;
	D3DXVECTOR3 &m_pos = GetPosition();
	D3DXVECTOR3 *pos = NULL;
	
	if (GetModel() != MODEL_MFIELD2 && GetModel() != MODEL_MFIELD) { return; }

	switch (pScene->GetObjType())
	{
	case CScene::OBJTYPE_PLAYER:
		pos = &((CPlayer*)pScene)->Getpos();
		break;
	}

	if (pos != NULL)
	{
		float &fRot = GetRotation().y;
		length.z = sinf(fRot) * lengthX.x + cosf(fRot) *lengthX.z;
		length.x = cosf(fRot) * lengthX.x + sinf(fRot) *lengthX.z;
		length.y = lengthX.y;
		if (m_pos.x + length.x > pos[0].x && m_pos.x - length.x < pos[0].x &&
			m_pos.z + length.z > pos[0].z && m_pos.z - length.z < pos[0].z)
		{
			if (m_pos.y + length.y > pos[0].y && m_posold.y + length.y - 10.0f <= pos[0].y)
			{//�� ���݂��߂荞��ł��� && �O�͂߂荞��łȂ�����
				pos[0].y = m_pos.y + length.y;
				switch (pScene->GetObjType())
				{
				case CScene::OBJTYPE_PLAYER:
					((CPlayer*)pScene)->Land();
					break;
				}
			}
		}
	}
}
//=============================================================================
//�����蔻��
//=============================================================================
void	CSceneObjct::SetObjField(void)
{
	bool bLand = false;
	CScene *pScene = CScene::GetTop(MODEL_PRIORITY);
	D3DXVECTOR3 WKpos, pos, posold, nor, length;
	bool bJump = true;
	length = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//while (pScene != NULL)
	//{//�I���܂�
	//	if (pScene->GetObjType() == OBJTYPE_OBJ)
	//	{//���b�V������
	//		pos = ((CSceneObjct*)pScene)->GetPosition();
	//		posold = pos;
	//		pos.y = -10000.0f;
	//		posold.y = 10000.0f;
	//		CMesh::MeshCollisionField(pos, posold, WKpos, length, nor, bJump);
	//		switch (((CSceneObjct*)pScene)->GetModel())
	//		{
	//		case MODEL_STONE:	pos.y -= 50.0f; break;
	//		case MODEL_FENCE:
	//		case MODEL_BOX:
	//		case MODEL_STONE_S:
	//		case MODEL_STEEL:
	//		case MODEL_STEEL_B:
	//			break;
	//		}
	//		((CSceneObjct*)pScene)->GetPosition().y = pos.y;

	//	}
	//	pScene = pScene->GetpNext();
	//}
}
//=============================================================================
//�X�C�b�`�̏�����
//=============================================================================
void	CSceneObjct::InitSwitch(bool bMode)
{
	m_bSwitch[0] = true;

	for (int nCount = 1; nCount < MAX_SWITCH; nCount++)
	{
		m_bSwitch[nCount] = (bMode ? true : false);
	}
}