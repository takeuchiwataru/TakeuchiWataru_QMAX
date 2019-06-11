//=============================================================================
//
// �r���{�[�h���� [Billboard.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "billboard.h"
#include "manager.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BILLBOARD_TEXTURENAME000	 "data\\TEXTURE\\BILLBOARD\\tree000.png"		//�e�N�X�`���̃t�@�C����
#define TEX_POS_X_INIT				(1.0f)								//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT				(1.0f)								//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT					(0.0f)								//�e�N�X�`�����WU��
#define TEX_RIGHT					(1.0f)								//�e�N�X�`�����WU�E
#define TEX_TOP						(0.0f)								//�e�N�X�`�����WV��
#define TEX_BOT						(1.0f)								//�e�N�X�`�����WV��

//--------------------------------------------
//�V�[���r���{�[�h�N���X �R���X�g���N�^
//--------------------------------------------
CSceneBillBoard::CSceneBillBoard() : CScene(5, CScene::OBJTYPE_BILLBOARD)
{
	//�����o�ϐ�
	m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

	m_fWidth = 0;
	m_fHeight = 0;
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtrxWorld);

}

//--------------------------------------------
//�V�[���r���{�[�h�N���X �f�X�g���N�^
//--------------------------------------------
CSceneBillBoard::~CSceneBillBoard()
{
}

//--------------------------------------------
//�V�[���r���{�[�h�̐���
//--------------------------------------------
CSceneBillBoard *CSceneBillBoard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight)
{
	CSceneBillBoard *pBillBoard;

	pBillBoard = new CSceneBillBoard;

	//�l�̑��
	pBillBoard->m_pos = pos;
	pBillBoard->m_move = move;
	pBillBoard->m_fHeight = fHeight;
	pBillBoard->m_fWidth = fWidth;

	pBillBoard->Init();

	return pBillBoard;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSceneBillBoard::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	////�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	BILLBOARD_TEXTURENAME000,
	//	&m_pTexture);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W (�T�C�Y�������߂�)
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, 0.0f, 0.0f);

	//�@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(TEX_LEFT, TEX_TOP);
	pVtx[1].tex = D3DXVECTOR2(TEX_RIGHT, TEX_TOP);
	pVtx[2].tex = D3DXVECTOR2(TEX_LEFT, TEX_BOT);
	pVtx[3].tex = D3DXVECTOR2(TEX_RIGHT, TEX_BOT);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	CScene::SetObjType(OBJTYPE_BILLBOARD);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSceneBillBoard::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//����������(�V�[��2D��j��)
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CSceneBillBoard::Update(void)
{
	//�ʒu�X�V
	m_pos += m_move;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CSceneBillBoard::Draw(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 Kyori = m_pos - pPlayer->GetPos();
	Kyori.z = abs(Kyori.z);

	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX  mtxView, mtxTrans;				//�v�Z�p�}�g���b�N�X

	//���݂̃��[�h���擾
	CManager::MODE mode = CManager::GetMode();
	switch (mode)
	{
	case CManager::MODE_GAME:
		if (m_pos.z + 200 > pPlayer->GetPos().z)
		{
			if (Kyori.z < 10000)
			{


				//�A���t�@�e�X�g(�����F��`�悵�Ȃ��悤��)
				pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
				pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
				pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

				if (GetObjType() == OBJTYPE_EFFECTADD)
				{
					//�����_�[�X�e�[�g�̐ݒ�����ɖ߂�
					pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

					//Z�o�b�t�@�̐ݒ�
					pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
					//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
					// ���u�����f�B���O�����Z�����ɐݒ�
					pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
					pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
					pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				}

				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&m_mtrxWorld);
				D3DXMatrixIdentity(&mtxView);
				D3DXMatrixIdentity(&mtxTrans);

				//�r���[�}�g���b�N�X���擾
				pDevice->GetTransform(D3DTS_VIEW, &mtxView);

				//�t�s���ݒ�
				m_mtrxWorld._11 = mtxView._11;
				m_mtrxWorld._12 = mtxView._21;
				m_mtrxWorld._13 = mtxView._31;
				m_mtrxWorld._21 = mtxView._12;
				m_mtrxWorld._22 = mtxView._22;
				m_mtrxWorld._23 = mtxView._32;
				m_mtrxWorld._31 = mtxView._13;
				m_mtrxWorld._32 = mtxView._23;
				m_mtrxWorld._33 = mtxView._33;

				// �ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

				D3DXMatrixMultiply(&m_mtrxWorld, &m_mtrxWorld, &mtxTrans);
				// ���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &m_mtrxWorld);
				//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
				pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
				//���_�t�H�[�}�b�g��ݒ�
				pDevice->SetFVF(FVF_VERTEX_3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, m_pTexture);
				// �r���{�[�h�̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
					0,	//�J�n���钸�_�̃C���f�b�N�X
					2); //�`�悷��v���~�e�B�u��

				//�����_�[�X�e�[�g�̐ݒ�����ɖ߂�
				pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

				if (GetObjType() == OBJTYPE_EFFECTADD)
				{
					//Z�o�b�t�@���f�t�H���g�̐ݒ�ɖ߂�
					pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
					pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
					// ���u�����f�B���O�����ɖ߂�
					pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
					pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
					pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				}
			}
		}
		break;
	case CManager::MODE_TITLE:

		//�A���t�@�e�X�g(�����F��`�悵�Ȃ��悤��)
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		if (GetObjType() == OBJTYPE_EFFECTADD)
		{
			//�����_�[�X�e�[�g�̐ݒ�����ɖ߂�
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

			//Z�o�b�t�@�̐ݒ�
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			// ���u�����f�B���O�����Z�����ɐݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtrxWorld);
		D3DXMatrixIdentity(&mtxView);
		D3DXMatrixIdentity(&mtxTrans);

		//�r���[�}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�t�s���ݒ�
		m_mtrxWorld._11 = mtxView._11;
		m_mtrxWorld._12 = mtxView._21;
		m_mtrxWorld._13 = mtxView._31;
		m_mtrxWorld._21 = mtxView._12;
		m_mtrxWorld._22 = mtxView._22;
		m_mtrxWorld._23 = mtxView._32;
		m_mtrxWorld._31 = mtxView._13;
		m_mtrxWorld._32 = mtxView._23;
		m_mtrxWorld._33 = mtxView._33;

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

		D3DXMatrixMultiply(&m_mtrxWorld, &m_mtrxWorld, &mtxTrans);
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtrxWorld);
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
		//���_�t�H�[�}�b�g��ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);
		// �r���{�[�h�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,	//�J�n���钸�_�̃C���f�b�N�X
			2); //�`�悷��v���~�e�B�u��

				//�����_�[�X�e�[�g�̐ݒ�����ɖ߂�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		if (GetObjType() == OBJTYPE_EFFECTADD)
		{
			//Z�o�b�t�@���f�t�H���g�̐ݒ�ɖ߂�
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			// ���u�����f�B���O�����ɖ߂�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
		break;
	case CManager::MODE_TUTORIAL:

		//�A���t�@�e�X�g(�����F��`�悵�Ȃ��悤��)
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 150);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		if (GetObjType() == OBJTYPE_EFFECTADD)
		{
			//�����_�[�X�e�[�g�̐ݒ�����ɖ߂�
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

			//Z�o�b�t�@�̐ݒ�
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			// ���u�����f�B���O�����Z�����ɐݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtrxWorld);
		D3DXMatrixIdentity(&mtxView);
		D3DXMatrixIdentity(&mtxTrans);

		//�r���[�}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�t�s���ݒ�
		m_mtrxWorld._11 = mtxView._11;
		m_mtrxWorld._12 = mtxView._21;
		m_mtrxWorld._13 = mtxView._31;
		m_mtrxWorld._21 = mtxView._12;
		m_mtrxWorld._22 = mtxView._22;
		m_mtrxWorld._23 = mtxView._32;
		m_mtrxWorld._31 = mtxView._13;
		m_mtrxWorld._32 = mtxView._23;
		m_mtrxWorld._33 = mtxView._33;

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

		D3DXMatrixMultiply(&m_mtrxWorld, &m_mtrxWorld, &mtxTrans);
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtrxWorld);
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
		//���_�t�H�[�}�b�g��ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);
		// �r���{�[�h�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,	//�J�n���钸�_�̃C���f�b�N�X
			2); //�`�悷��v���~�e�B�u��

				//�����_�[�X�e�[�g�̐ݒ�����ɖ߂�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		if (GetObjType() == OBJTYPE_EFFECTADD)
		{
			//Z�o�b�t�@���f�t�H���g�̐ݒ�ɖ߂�
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			// ���u�����f�B���O�����ɖ߂�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
		break;
	}
}

//=============================================================================
// �r���{�[�h�̈ʒu�ݒ菈��
//=============================================================================
void CSceneBillBoard::Setpos(D3DXVECTOR3 pos)
{
	// �V�[���r���{�[�h�̈ʒu��ݒ�
	m_pos = pos;
}

void CSceneBillBoard::Set(float fWidth, float fHeight)
{

}

//=============================================================================
// �r���{�[�h�̐ݒ菈��
//=============================================================================
void CSceneBillBoard::SetBillboard(D3DXVECTOR3 pos, float fHeight, float fWidth)
{
	VERTEX_3D *pVtx;//���_���ւ̃|�C���^
					//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	m_pos = pos;

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(-fWidth, fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(fWidth, fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-fWidth, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(fWidth, 0.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}


//=============================================================================
//�r���{�[�h�e�N�X�`���̐ݒ�
//=============================================================================
void CSceneBillBoard::BindTexture(LPDIRECT3DTEXTURE9 Texture)
{
	m_pTexture = Texture;
}

//=============================================================================
//�r���{�[�h�ʒu�擾
//=============================================================================
D3DXVECTOR3 CSceneBillBoard::GetPos(void)
{
	return m_pos;
}

//=============================================================================
//�r���{�[�h�F�ݒ�
//=============================================================================
void CSceneBillBoard::SetCol(D3DXCOLOR col)
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
//�r���{�[�h���_�擾
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 CSceneBillBoard::GetVtx(void)
{
	return m_pVtxBuff;
}
