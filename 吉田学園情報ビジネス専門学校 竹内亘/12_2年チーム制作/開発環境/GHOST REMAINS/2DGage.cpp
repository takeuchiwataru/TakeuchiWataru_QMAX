//=============================================================================
//
// 2D�Q�[�W���� [2DGage.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "2DPolygon.h"
#include "2DGage.h"
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
LPDIRECT3DTEXTURE9	C2DGage::m_pTexture[TEXTURE_MAX];		// �e�N�X�`���ւ̃|�C���^

//=============================================================================
// �摜�̓ǂݍ���
//=============================================================================
LPDIRECT3DTEXTURE9	*C2DGage::Load(TEXTURE tex)
{
	if (tex < TEXTURE_MAX)
	{//�͈͊m�F
		if (m_pTexture[tex] == NULL)
		{//�ǂݍ���łȂ��Ȃ�
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			switch (tex)
			{//�ǂݍ���
			case TEX_GAGE:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/GAGE000.jpg", &m_pTexture[tex]);		break;

			}
		}
		return &m_pTexture[tex];
	}
	return NULL;
}
//=============================================================================
// �摜�̉��
//=============================================================================
void	C2DGage::UnLoad(void)
{
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{//�S�摜�j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}
//==================================================================================================//
//    * �Q�[�W�̃Z�b�g�֐� *
//==================================================================================================//
void C2DGage::Set(D3DXVECTOR3 pos, float fLengthMaxX, float flengthMaxY, float *pGage, float *pMaxGage, bool bDirection, STATE state)	//�Q�[�W�Z�b�g����
{
	m_pGage = pGage;			//�Q�[�W�̌��݂̒l�̃A�h���X
	m_pMaxGage = pMaxGage;		//�Q�[�W�̍ő�l�̃A�h���X
	m_bDirection = bDirection;	//�Q�[�W�̌���
	m_state = state;

	if (m_p2D != NULL)
	{//���Ƀ��������g���Ă���Ȃ�
		for (int nCount = 0; nCount < MAX_GAGE; nCount++)
		{//����int���폜
			delete m_p2D[nCount];
		}//�{�̍폜
		delete[] m_p2D;
		m_p2D = NULL;
	}
	m_p2D = new C2D*[MAX_GAGE];
	if (m_p2D != NULL)
	{//�����ł����I
		D3DXCOLOR	col;
		float		fLengthX;

		for (int nCount = 0; nCount < MAX_GAGE; nCount++)
		{//��������]
			col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			m_p2D[nCount] = new C2D;
			m_p2D[nCount]->Init();
			col = GetGageColor(nCount, true);

			//�Z�b�g����
			if (m_p2D != NULL)
			{//�����ł����I
				if (GetStartLength() || nCount == 0)	{ fLengthX = fLengthMaxX; }
				else					{ fLengthX = 0.0f; }
				m_p2D[nCount]->Set(pos, fLengthX, flengthMaxY, D3DX_PI, 0, 1, 1, col);
				m_p2D[nCount]->SetGage(fLengthX, m_bDirection);		//�Q�[�W�^�ɕϊ�
				//m_p2D[nCount]->BindTexture(Load(TEX_GAGE));	//�摜�\��t��
			}
		}
	}
}
//=============================================================================
// �Q�[�W�̏���������
//=============================================================================
HRESULT  C2DGage::Init(void)
{
	return S_OK;
}
//=============================================================================
// �Q�[�W�̏I������
//=============================================================================
void C2DGage::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_GAGE; nCount++)
	{
		m_p2D[nCount]->Uninit();
	}
	delete this;
}

//=============================================================================
// �Q�[�W�̍X�V����
//=============================================================================
void C2DGage::Update(void)
{
	//Life�Q�[�W�̐ݒ�
	if (m_p2D[2] != NULL && m_p2D[1] != NULL)
	{
		float fLengthX_2 = m_p2D[2]->GetfLengthX()[0];
		float fLengthX_1 = m_p2D[1]->GetfLengthX()[0];
		float WKfLength;

		float fGage = m_p2D[0]->GetfLengthX()[0] * ((float)m_pGage[0] / (float)m_pMaxGage[0]);

		//2�̍X�V
		if (fGage < fLengthX_2)
		{ //��_���@��C��
			m_p2D[2]->SetGage(fGage, m_bDirection);
		}
		else if (fGage > fLengthX_2)
		{ //�񕜁@�������
			WKfLength = (fGage - fLengthX_2) * 0.05f;
			if (WKfLength < 0.05f) { WKfLength = 0.05f; }
			fLengthX_2 += WKfLength;
			if (fLengthX_2 > fGage) { fLengthX_2 = fGage; }
			m_p2D[2]->SetGage(fLengthX_2, m_bDirection);
		}

		//1�̍X�V
		if (fGage > fLengthX_1)
		{//�񕜁@��C��
			m_p2D[1]->SetColor(GetGageColor(1, false));
			m_p2D[1]->SetGage(fGage, m_bDirection);
		}
		else if (fGage < fLengthX_1)
		{//��_���@�������
			m_p2D[1]->SetColor(GetGageColor(1, true));
			WKfLength = (fLengthX_1 - fGage) * 0.05f;
			if (WKfLength < 0.05f) { WKfLength = 0.05f; }
			fLengthX_1 -= WKfLength;
			if (fLengthX_1 < fGage) { fLengthX_1 = fGage; }
			m_p2D[1]->SetGage(fLengthX_1, m_bDirection);
		}


	}
}

//=============================================================================
// �Q�[�W�̕`�揈��
//=============================================================================
void C2DGage::Draw(void)
{
	for (int nCount = 0; nCount < MAX_GAGE; nCount++)
	{
		m_p2D[nCount]->Draw();
	}
}
//=============================================================================
// ��Ԃɂ��Q�[�W���̃J���[�Ԃ�����
//=============================================================================
D3DXCOLOR	C2DGage::GetGageColor(int nCntGage, bool bChange)
{
	switch (m_state)
	{
	case STATE_LIFE:
		switch (nCntGage)
		{
		case 0: return D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		case 1: 
			if (bChange) { return D3DXCOLOR(1.0f, 0.1f, 0.02f, 1.0f); }
			else		 { return D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
		case 2: return D3DXCOLOR(0.32f, 1.0f, 0.19f, 1.0f);
		}
		break;
	case STATE_EXP:
		switch (nCntGage)
		{
		case 0: return D3DXCOLOR(0.25f, 0.25f, 0.25f, 1.0f);
		case 1:
			if (bChange) { return D3DXCOLOR(0.85f, 0.0f, 1.0f, 1.0f); }
			else { return D3DXCOLOR(1.0f, 0.98f, 0.02f, 1.0f); }
		case 2: return D3DXCOLOR(0.0f, 0.55f, 1.0f, 1.0f);
		}
		break;
	case STATE_STATUS:
		switch (nCntGage)
		{
		case 0: return D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		case 1:
			if (bChange) { return D3DXCOLOR(1.0f, 0.1f, 0.02f, 1.0f); }
			else { return D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
		case 2: return D3DXCOLOR(0.0f, 0.55f, 1.0f, 1.0f);
		}
		break;
	}

	return D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
}
//=============================================================================
// ��Ԃɂ��Q�[�W�̏����l����
//=============================================================================
bool	C2DGage::GetStartLength(void)
{
	switch (m_state)
	{
	case STATE_LIFE:	return true;
	case STATE_EXP:		return false;
	case STATE_STATUS:	return false;
	}
	return true;
}
