//=============================================================================
//
// �����_�����O���� [Scene2D.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//==================================================================================================//
//    * ���͊֐� *
//==================================================================================================//
void CScene2D::Set(D3DXVECTOR3 pos, float fLengthX, float fLengthY, float fRot, int nUV, int nUV_X, int nUV_Y, float fCntState, STATE state, D3DXCOLOR col, TEXTURE Texture)
{
	m_pos = pos;
	m_col = col;
	
	m_pTex = Load(Texture);
	m_fLengthX = fLengthX;
	m_fLengthY = fLengthY;
	m_fCntState = fCntState;
	m_state = state;
	m_DrawType = CScene::DRAW_TYPE_NORMAL;

	//Vtx�̕ύX
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (sinf(fRot) * m_fLengthY) + (cosf(fRot) * m_fLengthX), m_pos.y - (sinf(fRot) * m_fLengthX) + (cosf(fRot) * m_fLengthY), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (sinf(fRot) * m_fLengthY) - (cosf(fRot) * m_fLengthX), m_pos.y + (sinf(fRot) * m_fLengthX) + (cosf(fRot) * m_fLengthY), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (sinf(fRot) * m_fLengthY) + (cosf(fRot) * m_fLengthX), m_pos.y - (sinf(fRot) * m_fLengthX) - (cosf(fRot) * m_fLengthY), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x - (sinf(fRot) * m_fLengthY) - (cosf(fRot) * m_fLengthX), m_pos.y + (sinf(fRot) * m_fLengthX) - (cosf(fRot) * m_fLengthY), 0.0f);

	//�J���[�ݒ�
	pVtx[0].col = col;	// A = �����x
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//�e�N�X�`�����W�ݒ�
	pVtx[0].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y));
	pVtx[1].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y));
	pVtx[2].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));
	pVtx[3].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));

	//���_BUFFER���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT  CScene2D::Init(void)
{
	// �|���S���̈ʒu��ݒ�
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	m_fLengthX = 50;
	m_fLengthY = 50;
	CManager::GetRenderer();

	LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
	// ���_�o�b�t�@�̐���
	pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,		//�m�ۂ���BUFFER�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,				//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
	float fRot = 0.0f;
							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_BUFFER���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CScene2D::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{// ���_�o�b�t�@�̔j��
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CScene::Uninit();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CScene2D::Update(void)
{
	if (m_state != STATE_NORMAL)
	{
		float fWKstate;

		switch (m_state)
		{
		case STATE_FADEOUT2:
			m_col.a -= m_fCntState;
			if (m_col.a <= 0.0f) { m_col.a = 0.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_SLIDE_OUT1:
			m_pos.y += powf(m_col.a * 5.0f, 2);
			SetPosition(m_pos);
			m_col.a -= m_fCntState;
			if (m_col.a <= 0.0f) { Uninit(); return; }
			SetColor(m_col);
			break;
		case STATE_SLIDE_OUT2:
			m_pos.y -= powf(m_col.a * 5.0f, 2);
			SetPosition(m_pos);
			m_col.a -= m_fCntState;
			if (m_col.a <= 0.0f) { Uninit(); return; }
			SetColor(m_col);
			break;
		case STATE_FADEOUT:
			m_col.a -= m_fCntState;
			if (m_col.a <= 0.0f) 
			{ Uninit(); return; }
			SetColor(m_col);
			break;
		case STATE_SLIDE_IN:
			m_pos.x += (1.0f - m_col.a) * 30.0f;
			SetPosition(m_pos);
		case STATE_FADEIN:
			m_col.a += m_fCntState;
			if (m_col.a >= 1.0f) { m_col.a = 1.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_FADEIN5:
			m_col.a += m_fCntState;
			if (m_col.a >= 0.5f) { m_col.a = 0.5f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_FADE:
			m_col.a += m_fCntState;
			if (m_col.a >= 1.0f) { m_col.a = 1.0f; m_state = STATE_FADEOUT; }
			SetColor(m_col);
			break;
		case STATE_FLOW0: PlusUV(D3DXVECTOR2(0.0005f, 0.0005f)); break;
		case STATE_FLOW1: PlusUV(D3DXVECTOR2(0.00075f, 0.0005f)); break;
		case STATE_FLOW2: PlusUV(D3DXVECTOR2(0.0f, 0.0005f)); break;
		case STATE_FLASH:
			m_fCntState = m_fCntState + 1.0f;
			fWKstate = m_fCntState * 0.01f;
			SetColor(D3DXCOLOR(fWKstate, fWKstate, fWKstate, 1.0f));
			if (m_fCntState >= 100.0f) { m_state = STATE_FLASH2; m_fCntState = 100.0f; }
			break;
		case STATE_FLASH2:
			m_fCntState = m_fCntState - 1.5f;
			fWKstate = m_fCntState * 0.01f;
			SetColor(D3DXCOLOR(fWKstate, fWKstate, fWKstate, 1.0f));
			if (m_fCntState <= 25.0f) { m_state = STATE_FLASH; m_fCntState = 25.0f; }
			break;
		case STATE_BIG:
			if (m_fCntState < 120.0f)
			{
				m_fCntState += 4.0f;
				SetPosition2(m_fCntState * 0.01f);
			}
			break;
		case STATE_SMALL:
			if (m_fCntState > 80.0f)
			{
				m_fCntState -= 4.0f;
				SetPosition2(m_fCntState * 0.01f);
			}
			break;
		case STATE_COL_FLOW:
			if (m_fCntState > m_fLengthX)
			{//����������Ȃ�
				m_fLengthX += 5.0f;
				if (m_fCntState <= m_fLengthX)
				{//��������v����
					m_fLengthX = m_fCntState;
				}
				SetGageUV(m_fCntState);
				SetGage(m_fLengthX, true);
				SetSideAlpha(-1.0f, 0.0f, 1);
			}
			else
			{//�����\��
				SetSideAlpha(0.1f, 0.0f, 1);
			}

			break;
		}
	}
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();

	//�`����@�ݒ�
	if (CScene::DrawPrepare(m_DrawType, pD3DDevice)) { return; }

	//���_BUFFER���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	pD3DDevice->SetFVF(FVF_VERTEX_2D);	// ���_�t�H�[�}�b�g�̐ݒ�

										//�e�N�X�`���̐ݒ�
	if (m_pTex != NULL)
	{//�e�N�X�`���̐ݒ�
		pD3DDevice->SetTexture(0, m_pTex);
	}//�e�N�X�`���폜

	//�|���S���̕`��
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	pD3DDevice->SetTexture(0, NULL);

	//switch (m_state)
	//{
	//case STATE_ZCLEAR://�y�o�b�t�@�̃N���A
	//	CManager::GetRenderer()->GetDevice()->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(100, 0, 0, 0), 1.0f, 0);
	//	break;
	//}
}
//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// ���_���̐ݒ�
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;
	float fRot = D3DX_PI;
	m_pos = pos;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (sinf(fRot) * m_fLengthY) + (cosf(fRot) * m_fLengthX), m_pos.y - (sinf(fRot) * m_fLengthX) + (cosf(fRot) * m_fLengthY), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (sinf(fRot) * m_fLengthY) - (cosf(fRot) * m_fLengthX), m_pos.y + (sinf(fRot) * m_fLengthX) + (cosf(fRot) * m_fLengthY), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (sinf(fRot) * m_fLengthY) + (cosf(fRot) * m_fLengthX), m_pos.y - (sinf(fRot) * m_fLengthX) - (cosf(fRot) * m_fLengthY), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x - (sinf(fRot) * m_fLengthY) - (cosf(fRot) * m_fLengthX), m_pos.y + (sinf(fRot) * m_fLengthX) - (cosf(fRot) * m_fLengthY), 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// ���_�{���̐ݒ�
//=============================================================================
void CScene2D::SetPosition2(float fSize)
{
	VERTEX_2D *pVtx;
	float fLengthX = m_fLengthX * fSize;
	float fLengthY = m_fLengthY * fSize;
	float fRot = D3DX_PI;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (sinf(fRot) * fLengthY) + (cosf(fRot) * fLengthX), m_pos.y - (sinf(fRot) * fLengthX) + (cosf(fRot) * fLengthY), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (sinf(fRot) * fLengthY) - (cosf(fRot) * fLengthX), m_pos.y + (sinf(fRot) * fLengthX) + (cosf(fRot) * fLengthY), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (sinf(fRot) * fLengthY) + (cosf(fRot) * fLengthX), m_pos.y - (sinf(fRot) * fLengthX) - (cosf(fRot) * fLengthY), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x - (sinf(fRot) * fLengthY) - (cosf(fRot) * fLengthX), m_pos.y + (sinf(fRot) * fLengthX) - (cosf(fRot) * fLengthY), 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//==================================================================================================//
//    * ����������UV���W�ύX *
//==================================================================================================//
void CScene2D::SetUV(int nUV, int nUV_X, int nUV_Y)
{
	//Vtx�̕ύX
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

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
//==================================================================================================//
//    * UV���Q�[�W�^�ɕύX *
//==================================================================================================//
void	CScene2D::SetGageUV(float fMaxLengthX)
{
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((m_fLengthX / fMaxLengthX), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((m_fLengthX / fMaxLengthX), 1.0f);


	//���_BUFFER���A�����b�N����
	m_pVtxBuff->Unlock();
}
//==================================================================================================//
//    * �Q�[�W�^�ɕύX *
//==================================================================================================//
void CScene2D::SetGage(float fLengthX, bool bDirection)
{
	//Vtx�̕ύX
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	m_fLengthX = fLengthX;

	//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3((bDirection ? 0.0f : -fLengthX), -m_fLengthY, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3((bDirection ? fLengthX : 0.0f), -m_fLengthY, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3((bDirection ? 0.0f : -fLengthX), m_fLengthY, 0.0f) + m_pos;
	pVtx[3].pos = D3DXVECTOR3((bDirection ? fLengthX : 0.0f), m_fLengthY, 0.0f) + m_pos;

	//���_BUFFER���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// ���_���̐ݒ�
//=============================================================================
void CScene2D::PlusUV(D3DXVECTOR2 fUV)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].tex += fUV;
	pVtx[1].tex += fUV;
	pVtx[2].tex += fUV;
	pVtx[3].tex += fUV;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// ���_�J���[�����x(���E)�̐ݒ�
//=============================================================================
void	CScene2D::SetSideAlpha(float fCol, float fMinCol, int nID)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	D3DXCOLOR col = pVtx[0 + nID].col;
	col.a += fCol;
	if (col.a >= 1.0f) { col.a = 1.0f; }
	if (col.a <= fMinCol) { col.a = fMinCol; }

	pVtx[0 + nID].col = col;
	pVtx[2 + nID].col = col;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �A�j���[�V�����|���S���̐ݒ�
//=============================================================================
void	CSceneAnim2D::Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, float fRot, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed,
	float fCntState, STATE state, CSceneAnim3D::ANIMATION animation, D3DXCOLOR col, CScene2D::TEXTURE Texture)
{
	CScene2D::Set(pos, fLengthX, flengthY, fRot, nPtnAnim, nPtnWide, nPtnHeight, fCntState, state, col, Texture);
	m_animation = animation;
	m_nCntAnim = 0;
	m_nPtnAnim = nPtnAnim;
	m_nPtnWide = nPtnWide;
	m_nPtnHeight = nPtnHeight;
	m_nPtnSpeed = nPtnSpeed;
}
//=============================================================================
// �A�j���[�V�����|���S���̍X�V����
//=============================================================================
void	CSceneAnim2D::Update(void)
{
	m_nCntAnim++;
	if (m_nCntAnim % m_nPtnSpeed == 0)
	{//UV�ύX
		m_nPtnAnim++;
		if (m_nPtnAnim >= m_nPtnWide * m_nPtnHeight)
		{//�摜�͈̔͊O
			if (m_animation == CSceneAnim3D::ANIMATION_LOOP) { m_nPtnAnim = 0; }
			else { Uninit(); return; }
		}//�A�j���[�V�����X�V
		SetUV(m_nPtnAnim, m_nPtnWide, m_nPtnHeight);
	}

	CScene2D::Update();
}