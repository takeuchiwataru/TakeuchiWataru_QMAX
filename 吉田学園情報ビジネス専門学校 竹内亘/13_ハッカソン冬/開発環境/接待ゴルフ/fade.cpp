//---------------------------------------------------------------------
// �t�F�[�h���� [title.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "fade.h"
#include "manager.h"
#include "scene.h"

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9				CFade::m_pTextureFade = NULL;
LPDIRECT3DVERTEXBUFFER9			CFade::m_pVtxBuffFade = NULL;
CFade::FADE						CFade::m_fade = CFade::FADE_NONE;
CManager::MODE					CFade::m_modeNext = CManager::MODE_TITLE;
D3DXCOLOR						CFade::m_color = D3DXCOLOR(0, 0, 0, 1);
bool							CFade::m_bNextMode = true;
//--------------------------------------------
//�t�F�[�h�N���X �R���X�g���N�^
//--------------------------------------------
CFade::CFade(int nPriority)
{
}

//--------------------------------------------
//�t�F�[�h�N���X �f�X�g���N�^
//--------------------------------------------
CFade::~CFade()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CFade * CFade::Create(CManager::MODE modeNext)
{
	CFade *pFade;

	pFade = new CFade(7);

	pFade->Init(modeNext);

	return pFade;
}

//=============================================================================
// ����������
//=============================================================================
void CFade::Init(CManager::MODE modeNext)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �l�̏�����
	m_fade = FADE_IN;									//�t�F�[�h�C����Ԃ�
	m_modeNext = modeNext;
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//������ʂ�(�s����)

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

					//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffFade,
		NULL);

	//���_���̐���
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuffFade->Unlock();

	m_bNextMode = true;
}

//=============================================================================
// �t�F�[�h�N���X �I������
//=============================================================================
void CFade::Uninit(void)
{
	// �e�N�X�`���̊J��
	if (m_pTextureFade != NULL)
	{
		m_pTextureFade->Release();
		m_pTextureFade = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuffFade != NULL)
	{
		m_pVtxBuffFade->Release();
		m_pVtxBuffFade = NULL;
	}
}

//=============================================================================
// �t�F�[�h�N���X �X�V����
//=============================================================================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{//�������ĂȂ����
		if (m_fade == FADE_IN)
		{//�t�F�[�h�C��
			m_color.a -= 0.02f;			//��ʂ𓧖��ɂ��Ă���
			if (m_color.a <= 0.0f)
			{
				m_color.a = 0.0f;		//�l�����Ȃ����ď�����
				m_fade = FADE_NONE;		//�������ĂȂ����
			}
		}
		else if (m_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g���
			m_color.a += 0.02f;			//��ʂ�s������
			if (m_color.a >= 1.0f)
			{
				m_color.a = 1.0f;		//�l�����Ȃ����ď�����
				m_fade = FADE_IN;		//�t�F�[�h�C����Ԃ�
				if (m_bNextMode == true)
				{
					CManager::SetMode(m_modeNext);
				}
				//���̃��[�h�ւ̃t���O�𗧂Ă�
				m_bNextMode = true;
			}
		}
		VERTEX_2D *pVtx;								//���_���ւ̃|�C���^
		m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
														//���_�J���[
		pVtx[0].col = m_color;
		pVtx[1].col = m_color;
		pVtx[2].col = m_color;
		pVtx[3].col = m_color;
		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuffFade->Unlock();
	}
}

//=============================================================================
// �t�F�[�h�N���X �`�揈��
//=============================================================================
void CFade::Draw(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureFade);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext)
{
	if (m_fade != FADE_OUT)
	{
		m_fade = FADE_OUT;									//�t�F�[�h�A�E�g��Ԃ�
		m_modeNext = modeNext;
		m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//������
	}
}

//=============================================================================
// �t�F�[�h�̎擾
//=============================================================================
CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}

//=============================================================================
// �t�F�[�h�C���A�E�g�̐ݒ�
//=============================================================================
void CFade::SetFadeINOUT(FADE fade,bool bNextMode)
{
	m_fade = fade;
	m_bNextMode = bNextMode;
}
