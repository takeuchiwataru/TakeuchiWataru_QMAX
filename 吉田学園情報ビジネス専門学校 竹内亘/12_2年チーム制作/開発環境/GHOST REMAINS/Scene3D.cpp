//=============================================================================
//
// �|���S������ [Scene3D.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene3D.h"
#include"Renderer.h"
#include "collision.h"
#include "player.h"
#include "manager.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene3D::Init(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	m_pVtxBuff = NULL;
	m_pTex = NULL;

	// ���_���̍쐬
	MakeVertex(pD3DDevice);

	m_DrawType = CScene::DRAW_TYPE_NORMAL;
	m_bBILLBoard = false;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene3D::Uninit(void)
{
	// ���_�o�b�t�@�̊J��;
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CScene::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene3D::Update(void)
{
	if (m_state != STATE_NORMAL)
	{
		switch (m_state)
		{
		case STATE_UVFLOW_1:
			m_fCntState += 0.01f;
		case STATE_UVFLOW_0:
			m_fCntState += 0.02f;
			//UV�̐ݒ�
			VERTEX_3D *pVtx;

			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			pVtx[0].tex = D3DXVECTOR2(0.0f + m_fCntState, 0.0f + m_fCntState);
			pVtx[1].tex = D3DXVECTOR2(1.0f + m_fCntState, 0.0f + m_fCntState);
			pVtx[2].tex = D3DXVECTOR2(0.0f + m_fCntState, 1.0f + m_fCntState);
			pVtx[3].tex = D3DXVECTOR2(1.0f + m_fCntState, 1.0f + m_fCntState);

			//���_�o�b�t�@�̃A�����b�N
			m_pVtxBuff->Unlock();
		case STATE_FADESPIN:
			m_fCntState += 0.05f;
			m_rot.y += D3DX_PI * 0.03f;
			if (m_fCntState >= 1.0f) { Uninit(); return; }
			m_col.a = 1.0f - m_fCntState;//�����x�ύX
			m_length *= 1.0f + ((1.0f - m_fCntState) * 0.25f);
			SetColor(m_col);
			SetSize(m_length);
			break;
		case STATE_FADEIN:
			m_col.a += 0.05f;//�����x�ύX
			if (m_col.a > 1.0f) { m_col.a = 1.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_FADEOUT:
			m_col.a -= m_fCntState;//�����x�ύX
			if (m_col.a <= 0.0f) 
			{ Uninit(); return; }
			SetColor(m_col);
			break;
		case STATE_FADEOUT2:
			m_col.a -= 0.05f;//�����x�ύX
			if (m_col.a < 0.0f) { m_col.a = 0.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_BFLOW_IN:
			if (m_col.a != 1.0f)
			{//�����x������Ȃ��I
				m_col.a += 0.01f;//�����x�ύX
				if (m_col.a >= 1.0f) { m_col.a = 1.0f; }
				SetColor(m_col);
			}
			PlusUV(D3DXVECTOR2(0.002f, 0.001f));
			break;
		case STATE_BFLOW_OUT:
			if (m_col.a != 0.0f)
			{//�����x������Ȃ��I
				m_col.a -= 0.01f;//�����x�ύX
				if (m_col.a <= 0.0f)
				{
					m_col.a = 0.0f;
					m_state = STATE_NORMAL;
					return;
				}
				SetColor(m_col);
			}
			PlusUV(D3DXVECTOR2(0.02f, 0.01f));
			break;
		case STATE_DSTONE:
			m_fCntState += 1.0f;
			if (m_fCntState > 225.0f)
			{
				Uninit();
			}
			if (m_col.a != 1.0f)
			{//�����x������Ȃ��I
				m_col.a += 0.005f;//�����x�ύX
				if (m_col.a >= 1.0f) { m_col.a = 1.0f; }
				SetColor(m_col);
			}
			break;
		}
	}

	//if (CManager::GetPlayer() != NULL)
	//{
	//	 D3DXVECTOR3 &pos = CManager::GetPlayer()->Getpos();
	//	 VERTEX_3D *pVtx;

	//	 //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	//	 m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//	 D3DXVECTOR3 vec = pos - pVtx[0].pos;

	//	 pos.y = ((pVtx[0].nor.x * vec.x) + (pVtx[0].nor.z * vec.z)) / -pVtx[0].nor.y;
	//	 vec = pos - pVtx[0].pos;
	//	pos.y = (pVtx[0].nor.x * vec.x) + (pVtx[0].nor.y * vec.y) + (pVtx[0].nor.z * vec.z);

	//	 //���_�o�b�t�@�̃A�����b�N
	//	 m_pVtxBuff->Unlock();
	//}
	//	 VERTEX_3D *pVtx;
	//	 static float fRotX = 0.0f, fRotY = 0.0f;
	//	 CInputKeyboard *pInputKey = CManager::GetInputKey();

	//	 if (pInputKey->GetPress(DIK_E)) { fRotX += D3DX_PI * 0.01f; }
	//	 if (pInputKey->GetPress(DIK_Q)) { fRotX -= D3DX_PI * 0.01f; }


	////���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//D3DXVECTOR3 vec[4], nor[2];
	//D3DXVECTOR3 Vtx[4];
	//D3DXVECTOR3 vec0, vec1;
	//float		fData;

	//Vtx[0] = pVtx[0].pos;
	//Vtx[1] = pVtx[1].pos;
	//Vtx[2] = pVtx[2].pos;
	//fData = Vtx[0].y; Vtx[0].y -= fData; Vtx[1].y -= fData; Vtx[2].y -= fData;

	//vec[0] = pVtx[1].pos - pVtx[0].pos;
	//vec[1] = pVtx[2].pos - pVtx[0].pos;

	//D3DXVec3Cross(&nor[0], &vec[0], &vec[1]);				//���K���ɂ���

	//D3DXVec3Normalize(&nor[0], &nor[0]);

	//pVtx[0].nor = nor[0];
	//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�@��%.1f�@%.1f�@%.1f\n", nor[0].x, nor[0].y, nor[0].z);

	//	 //���_�o�b�t�@�̃A�����b�N
	//	 m_pVtxBuff->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene3D::Draw(void)
{
	LPDIRECT3DDEVICE9	pD3DDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxView;	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX	mtxWorld;					//���[���h�}�g���b�N�X

	if (CScene::DrawPrepare(m_DrawType, pD3DDevice)) { return; }

	//�A���t�@�e�X�g����(�������ɂ��摜�̐؂��茻�ۂ�L���ɂ���)
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 30);//REF = Reference:�Q��
	pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//FUNC = Function:�@�\ //GREATER = �`���傫��

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	if (m_bBILLBoard)
	{ //�r���{�[�h
		pD3DDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�t�s���ݒ�
		mtxWorld._11 = mtxView._11;
		mtxWorld._12 = mtxView._21;
		mtxWorld._13 = mtxView._31;
		mtxWorld._21 = mtxView._12;
		mtxWorld._22 = mtxView._22;
		mtxWorld._23 = mtxView._32;
		mtxWorld._31 = mtxView._13;
		mtxWorld._32 = mtxView._23;
		mtxWorld._33 = mtxView._33;
	}
	else
	{// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
	}
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pD3DDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	if (m_pTex != NULL)
	{//�e�N�X�`���̐ݒ�
		pD3DDevice->SetTexture(0, m_pTex);
	}//�e�N�X�`���폜

	// �|���S���̕`��
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	pD3DDevice->SetTexture(0, NULL);

	//���؂��薳����
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void CScene3D::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �ݒ�
//=============================================================================
void CScene3D::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length, TEXTURE nType, int nUV, int nUV_X, int nUV_Y, bool bBillBoard, DRAW_TYPE DrawType)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			m_pTex = Load(nType);
			m_col = col;

			m_pos = pos;
			m_rot = rot;
			m_length = length;
			m_DrawType = DrawType;
			m_bBILLBoard = bBillBoard;

			pVtx[0].pos = D3DXVECTOR3(-m_length.x, m_length.y, m_length.z);
			pVtx[1].pos = D3DXVECTOR3(m_length.x, m_length.y, m_length.z);
			pVtx[2].pos = D3DXVECTOR3(-m_length.x, -m_length.y, -m_length.z);
			pVtx[3].pos = D3DXVECTOR3(m_length.x, -m_length.y, -m_length.z);

			//pVtx[0].pos = D3DXVECTOR3(-100.0f, 100.0f, 50.0f);
			//pVtx[1].pos = D3DXVECTOR3(100.0f, 100.0f, 50.0f);
			//pVtx[2].pos = D3DXVECTOR3(-100.0f, -100.0f, -0.0f);
			//pVtx[3].pos = D3DXVECTOR3(100.0f, -100.0f, -0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
			pVtx[1].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
			pVtx[2].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
			pVtx[3].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j

			//UV�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X)				 , (nUV / nUV_X) * (1.0f / nUV_Y));
			pVtx[1].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y));
			pVtx[2].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X)				 , (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));
			pVtx[3].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �F�̐ݒ�
//=============================================================================
void	CScene3D::SetColor(D3DXCOLOR col)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_col = col;

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
	pVtx[1].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
	pVtx[2].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
	pVtx[3].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �F�̐ݒ�
//=============================================================================
void	CScene3D::SetSize(D3DXVECTOR3 length)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�l����
	m_length = length;

	pVtx[0].pos = D3DXVECTOR3(-m_length.x, -m_length.y, m_length.z);
	pVtx[1].pos = D3DXVECTOR3(m_length.x, -m_length.y, m_length.z);
	pVtx[2].pos = D3DXVECTOR3(-m_length.x, m_length.y, -m_length.z);
	pVtx[3].pos = D3DXVECTOR3(m_length.x, m_length.y, -m_length.z);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
//==================================================================================================//
//    * ����������UV���W�ύX *
//==================================================================================================//
void CScene3D::SetUV(int nUV, int nUV_X, int nUV_Y)
{
	//Vtx�̕ύX
	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�ݒ�
	pVtx[0].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y));
	pVtx[1].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y));
	pVtx[2].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));
	pVtx[3].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));

	//���_BUFFER���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// UV�p�^�[�����ݒ�
//=============================================================================
void	CScene3D::SetUVPattern(float fUV_X, float fUV_Y)
{
	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

	//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�ݒ�
	//pVtx[0].tex = D3DXVECTOR2((m_pos.x + m_fLengthX) * fUV_X, (m_pos.z - m_fLengthZ) * fUV_Y);
	//pVtx[1].tex = D3DXVECTOR2((m_pos.x - m_fLengthX) * fUV_X, (m_pos.z + m_fLengthZ) * fUV_Y);
	//pVtx[2].tex = D3DXVECTOR2((m_pos.x + m_fLengthX) * fUV_X, (m_pos.z - m_fLengthZ) * fUV_Y);
	//pVtx[3].tex = D3DXVECTOR2((m_pos.x - m_fLengthX) * fUV_X, (m_pos.z + m_fLengthZ) * fUV_Y);

	pVtx[0].tex = D3DXVECTOR2((m_pos.x / m_length.x) * fUV_X, (m_pos.z / m_length.z) * fUV_Y);
	pVtx[1].tex = D3DXVECTOR2(((m_pos.x + m_length.x) / m_length.x) * fUV_X, ((m_pos.z / m_length.z) * fUV_Y));
	pVtx[2].tex = D3DXVECTOR2((m_pos.x / m_length.x) * fUV_X, ((m_pos.z + m_length.z) / m_length.z) * fUV_Y);
	pVtx[3].tex = D3DXVECTOR2(((m_pos.x + m_length.x) / m_length.x) * fUV_X, ((m_pos.z + m_length.z) / m_length.z) * fUV_Y);

	//���_BUFFER���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// UV���Z����
//=============================================================================
void	CScene3D::PlusUV(D3DXVECTOR2 uv)
{
	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�ݒ�
	pVtx[0].tex += uv;
	pVtx[1].tex += uv;
	pVtx[2].tex += uv;
	pVtx[3].tex += uv;

	//���_BUFFER���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �G�t�F�N�g�̐ݒ�
//=============================================================================
void CSceneEffect::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length,TEXTURE nType, 
	int nUV, int nUV_X, int nUV_Y, bool bBillBoard, DRAW_TYPE DrawType, D3DXVECTOR3 *pPos, CScene *pScene)
{
	CScene3D::Set(pos, rot, col, length, nType, nUV, nUV_X, nUV_Y, bBillBoard, DrawType);
	m_pPos = pPos;
	m_pScene = pScene;
}
//=============================================================================
// �G�t�F�N�g�̍X�V
//=============================================================================
void CSceneEffect::Update(void)
{
	if (m_pScene == NULL) { m_pPos = NULL; }
	if (m_pPos != NULL) { GetPosition() = m_pPos[0]; }
	CScene3D::Update();
}
//=============================================================================
// �`�揈��
//=============================================================================
void CSceneEffect::Draw(void)
{
	LPDIRECT3DDEVICE9	pD3DDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	if (CScene::DrawPrepare(GetDrawType(), pD3DDevice)) { return; }

	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DXMATRIX	mtxWorld;		//���[���h�}�g���b�N�X
	D3DXVECTOR3 &m_pos = GetPosition();
	D3DXVECTOR3 &m_rot = GetRotation();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pD3DDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pD3DDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	if (GetTexture() != NULL)
	{//�e�N�X�`���̐ݒ�
		pD3DDevice->SetTexture(0, GetTexture());
	}//�e�N�X�`���폜

	 // �|���S���̕`��
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pD3DDevice->SetTexture(0, NULL);
}
