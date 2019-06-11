//---------------------------------------------------------------------
// �|�[�Y���� [pause.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "pause.h"
#include "scene.h"
#include "scene2D.h"
#include "input.h"
#include "manager.h"
#include "fade.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_CONTINUE		"data\\TEXTURE\\PAUSE\\pause000.png"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RETRY			"data\\TEXTURE\\PAUSE\\pause001.png"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_QUIT			"data\\TEXTURE\\PAUSE\\pause002.png"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define PAUSEBG_TEXTURENAME		"data\\TEXTURE\\PAUSE\\pause.png"				//  �ǂݍ��ރe�N�X�`���t�@�C����

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9 CPause::m_pTexture[MAX_PAUSEMENU] = {};
LPDIRECT3DTEXTURE9 CPause::m_pTextureBG = NULL;
CPause::SELECTMODE CPause::m_SelectMode = CPause::SELECTMODE_NONE;
bool CPause::m_bPause = false;

//--------------------------------------------
//�|�[�Y�N���X �R���X�g���N�^
//--------------------------------------------
CPause::CPause(int nPriority) : CScene(7)
{
}

//--------------------------------------------
//�|�[�Y�N���X �f�X�g���N�^
//--------------------------------------------
CPause::~CPause()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CPause *CPause::Create(D3DXVECTOR3 pos, float m_fWidth)
{
	//�|�[�Y�̃|�C���^
	CPause *pPause;
	pPause = new CPause;

	pPause->m_InitPos = pos;
	pPause->m_fWidth = m_fWidth;
	pPause->m_fHeight = m_fWidth;
	//�|�[�Y�̏�����
	pPause->Init();
	//�|�[�Y�̏���Ԃ�
	return pPause;
}


//=============================================================================
// ����������
//=============================================================================
HRESULT CPause::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		m_apPolygon[nCnt] = NULL;
	}

	//BG�̏�����
	m_apPolygonBG = CScene2D::Create(D3DXVECTOR3(m_InitPos.x, m_InitPos.y, m_InitPos.z), m_fWidth * 4, m_fHeight * 3,6);
	m_apPolygonBG->BindTexture(m_pTextureBG);
	m_apPolygonBG->SetbDraw(false);

	for (int nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		if (m_apPolygon[nCnt] == NULL)
		{	//�|���S���̏�����
			m_Pos[nCnt] = m_InitPos;
			m_Pos[nCnt].y = m_InitPos.y - m_fWidth;
			//�ʒu�����炷
			m_Pos[nCnt].y = m_Pos[nCnt].y + (m_fWidth * nCnt);
			m_apPolygon[nCnt] = CScene2D::Create(D3DXVECTOR3(m_Pos[nCnt].x, m_Pos[nCnt].y, m_Pos[nCnt].z), m_fWidth * 2, m_fHeight * 1.4f,6);
			m_apPolygon[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apPolygon[nCnt]->SetbDraw(false);
		}
	}

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;
	//���_�o�b�t�@���擾
	m_pVtxBuff = m_apPolygonBG->GetVtx();
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 0.6f, 0.0f, 0.8f);
	pVtx[1].col = D3DXCOLOR(1.0f, 0.6f, 0.0f, 0.8f);
	pVtx[2].col = D3DXCOLOR(1.0f, 0.6f, 0.0f, 0.8f);
	pVtx[3].col = D3DXCOLOR(1.0f, 0.6f, 0.0f, 0.8f);
	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�l�̏�����
	m_nSelect = 0;
	m_TexMove = D3DXVECTOR3(0, 0, 0);
	m_aPauseMenu[m_nSelect].select = SELECTTYPE_SELECT;
	m_aPauseMenu[1].select = SELECTTYPE_NONE;
	m_aPauseMenu[2].select = SELECTTYPE_NONE;
	m_bPause = false;
	//�I�u�W�F�N�g��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_PAUSE);

	return S_OK;
}

//=============================================================================
// �|�[�Y�N���X �I������
//=============================================================================
void CPause::Uninit(void)
{

	//������j��
	Release();
}

//=============================================================================
// �|�[�Y�N���X �X�V����
//=============================================================================
void CPause::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//�W���C�p�b�h�����擾
	CInputJoypad *pInputJoypad = CManager::GetCInputJoypad();
	//�T�E���h�����擾
	CSound *pSound = CManager::GetSound(0);

	//�\���ؑ�
	for (int nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		m_apPolygon[nCnt]->SetbDraw(m_bPause);
	}
	m_apPolygonBG->SetbDraw(m_bPause);

#ifdef  _DEBUG
	if (pInput->GetTrigger(DIK_O) == true)
	{//TRUE�Ȃ�FALSE FALSE�Ȃ�TRUE
		m_bPause = m_bPause ? false : true;
	}
#endif

	//�|�[�Y��
	if (m_bPause == true)
	{
		//�I������
		if (pInput->GetTrigger(DIK_DOWN) == true || pInput->GetTrigger(DIK_S) == true
			|| pInputJoypad->GetTrigger(CInputJoypad::POV_DOWN) == true
			|| pInputJoypad->GetTrigger(CInputJoypad::STICK_L_DOWN) == true)
		{
			pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT);
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_NONE;
			m_nSelect = (m_nSelect + 1) % 3;
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_SELECT;
		}
		else if (pInput->GetTrigger(DIK_UP) == true || pInput->GetTrigger(DIK_W) == true
			|| pInputJoypad->GetTrigger(CInputJoypad::POV_UP) == true
			|| pInputJoypad->GetTrigger(CInputJoypad::STICK_L_UP) == true)
		{
			pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT);
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_NONE;
			m_nSelect = (m_nSelect + 2) % 3;
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_SELECT;
		}
		//�G���^�[�L�[
		if (pInput->GetTrigger(DIK_RETURN) == true || pInputJoypad->GetPress(CInputJoypad::BUTTON_A) == true)
		{
			pSound->PlaySound(pSound->SOUND_LABEL_SE_CANCEL);
			if (m_nSelect == 0)
			{
				m_SelectMode = SELECTMODE_CONTINUE;
			}
			else if (m_nSelect == 1)
			{
				m_SelectMode = SELECTMODE_RETRY;
			}
			else if (m_nSelect == 2)
			{
				m_SelectMode = SELECTMODE_QUIT;
			}

			switch (m_SelectMode)
			{
			case SELECTMODE_CONTINUE:
				m_bPause = false;
				SetbPause(m_bPause);
				break;
			case SELECTMODE_RETRY:
				m_bPause = false;
				CFade::SetFade(CManager::MODE_GAME);
				SetbPause(m_bPause);
				break;
			case SELECTMODE_QUIT:
				m_bPause = false;
				CFade::SetFade(CManager::MODE_TITLE);
				SetbPause(m_bPause);
				break;
			}
		}

		//P�L�[�ŃL�����Z��
		if (pInput->GetTrigger(DIK_P) == true || pInputJoypad->GetTrigger(CInputJoypad::BUTTON_START) == true)
		{
			m_nSelect = 0;
			m_aPauseMenu[m_nSelect].select = SELECTTYPE_SELECT;
			m_aPauseMenu[1].select = SELECTTYPE_NONE;
			m_aPauseMenu[2].select = SELECTTYPE_NONE;
		}

		//�F�ς�
		for (int nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
		{
			if (m_aPauseMenu[nCnt].select == SELECTTYPE_SELECT)
			{//�I�𒆂̐F
				m_aPauseMenu[nCnt].col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f);
			}
			else
			{//���I���̐F
				m_aPauseMenu[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}

			//���_���ւ̃|�C���^
			VERTEX_2D *pVtx;
			//���_�o�b�t�@���擾
			m_pVtxBuff = m_apPolygon[nCnt]->GetVtx();
			//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
			//���_�J���[
			pVtx[0].col = m_aPauseMenu[nCnt].col;
			pVtx[1].col = m_aPauseMenu[nCnt].col;
			pVtx[2].col = m_aPauseMenu[nCnt].col;
			pVtx[3].col = m_aPauseMenu[nCnt].col;
			// ���_�o�b�t�@���A�����b�N����
			m_pVtxBuff->Unlock();
		}

		//���_���ւ̃|�C���^
		VERTEX_2D *pVtx;
		//���_�o�b�t�@���擾
		m_pVtxBuff = m_apPolygonBG->GetVtx();
		//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		//���_�e�N�X�`��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// �|�[�Y�N���X �`�揈��
//=============================================================================
void CPause::Draw(void)
{
}

//=============================================================================
// �|�[�Y�N���X�@�I���������[�h���擾
//=============================================================================
CPause::SELECTMODE * CPause::GetPauseMode(void)
{
	return &m_SelectMode;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CPause::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CONTINUE,
		&m_pTexture[0]);

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_RETRY,
		&m_pTexture[1]);

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_QUIT,
		&m_pTexture[2]);

	// �e�N�X�`���̐��� [BG]
	D3DXCreateTextureFromFile(pDevice,
		PAUSEBG_TEXTURENAME,
		&m_pTextureBG);
	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j������
//=============================================================================
void CPause::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_PAUSEMENU; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}

	if (m_pTextureBG != NULL)
	{
		m_pTextureBG->Release();
		m_pTextureBG = NULL;
	}
}
//=============================================================================
// �|�[�Y�̏�Ԃ��擾
//=============================================================================
bool CPause::GetPauseBool(void)
{
	return m_bPause;
}

//=============================================================================
// �|�[�Y�̏�Ԃ�ݒ�
//=============================================================================
void CPause::SetPauseBool(bool PauseBool)
{
	m_bPause = PauseBool;
}

