//=============================================================================
//
// �t�F�[�h���� [Fade.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "2DPolygon.h"
#include "Fade.h"
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
LPDIRECT3DTEXTURE9	CFade::m_pTexture[TEXTURE_MAX];		// �e�N�X�`���ւ̃|�C���^

//=============================================================================
// �摜�̓ǂݍ���
//=============================================================================
LPDIRECT3DTEXTURE9	*CFade::Load(TEXTURE tex)
{
	if (tex < TEXTURE_MAX)
	{//�͈͊m�F
		//if (m_pTexture[tex] == NULL)
		//{//�ǂݍ���łȂ��Ȃ�
		//	LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
		//	switch (tex)
		//	{//�ǂݍ���
		//	//case TEX_GAGE:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/GAGE000.jpg", &m_pTexture[tex]);		break;

		//	}
		//}
		//return &m_pTexture[tex];
	}
	return NULL;
}
//=============================================================================
// �摜�̉��
//=============================================================================
void	CFade::UnLoad(void)
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
//    * �Z�b�g�֐� *
//==================================================================================================//
void CFade::Set(void)
{

}
//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT  CFade::Init(STATE state)
{
	switch (state)
	{
	case STATE_OUT:
		if (m_p2DFade == NULL)
		{
			Create(m_p2DFade);
			if (m_p2DFade != NULL)
			{//�t�F�[�h��������
				m_p2DFade->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 1, 1, 0.05f, C2DPolygon::STATE_FADEOUT, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
			}
		}
		break;
	case STATE_NOR_FADE:
		if (m_p2DFade == NULL)
		{
			Create(m_p2DFade);
			if (m_p2DFade != NULL)
			{//�t�F�[�h��������
				m_p2DFade->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 1, 1, 0.05f, C2DPolygon::STATE_FADEIN, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.01f));
			}
		}
		break;
	}
	m_state = STATE_FADE_NOW;
	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CFade::Uninit(void)
{
	if (m_p2DFade != NULL) { m_p2DFade->Uninit(); m_p2DFade = NULL; }
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CFade::Update(void)
{
	if (m_p2DFade != NULL)
	{
		if (m_p2DFade->GetColor()[0].a == 0.0f)
		{
			m_p2DFade->Uninit();
			m_p2DFade = NULL;
			m_state = STATE_FADE_NONE;
		}
		else if (m_p2DFade->GetState()[0] == CScene2D::STATE_NORMAL)
		{//�Z�b�g���[�h�@�t�F�[�h�A�E�g
			CManager::SetMode();
			m_p2DFade->GetState()[0] = C2DPolygon::STATE_FADEOUT;
			//MessageBox(0, "", "", MB_OK);
		}
		else { m_p2DFade->Update(); }
	}
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CFade::Draw(void)
{
	if (m_p2DFade != NULL) { m_p2DFade->Draw(); }
}
