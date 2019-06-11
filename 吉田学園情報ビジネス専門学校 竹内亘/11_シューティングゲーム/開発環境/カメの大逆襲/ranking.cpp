//=============================================================================
//
// �����L���O���� [ranking.cpp]
// Author : �|���j
//
//=============================================================================
#include "ranking.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "logo.h"
#include "number.h"
#include "score.h"
#include "bg.h"
#include "rankingrank.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CScore * CRanking::m_apScore[MAX_RANKING] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRanking::CRanking()
{
	m_nTime = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRanking::~CRanking()
{

}
//=============================================================================
// ����������
//=============================================================================
void CRanking::Init(void)
{
	int aScore[MAX_RANKING] = {};

	m_nTime = 0;

	// �w�i�̃e�N�X�`���ǂݍ���
	CBg::Load();

	// �i���o�[�e�N�X�`���̓ǂݍ���
	CNumber::Load();

	// �����L���O�����N�̓ǂݍ���
	CRankingRank::Load();

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		if (m_apScore[nCntRanking] == NULL)
		{
			aScore[nCntRanking] = CManager::GetRanking(nCntRanking);

			// �X�R�A�̐���
			m_apScore[nCntRanking] = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, 170.0f + nCntRanking * 100.0f, 0));
			m_apScore[nCntRanking]->AddScore(aScore[nCntRanking]);
		}
	}

	// �w�i�N���X�̐���
	CBg::Create(D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f));

	// �����L���O�����N�̐���
	CRankingRank::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2, 0.0f));

	//// �����L���O���S�̓ǂݍ���
	//CRankingLogo::Load();

	//// �����L���O���S�̐���
	//CRankingLogo::Create(D3DXVECTOR3(250, 100, 0.0f));
}
//=============================================================================
// �I������
//=============================================================================
void CRanking::Uninit(void)
{
	// �S�ĉ��
	CScene::ReleseAll();

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		m_apScore[nCntRanking] = NULL;
	}

	// �i���o�[�̃e�N�X�`���j��
	CNumber::Unload();

	// �w�i�̃e�N�X�`���j��
	CBg::Unload();

	// �����L���O�����N�e�N�X�`���̔j��
	CRankingRank::Unload();

	//// �����L���O���S�̔j��
	//CRankingLogo::Unload();
}
//=============================================================================
// �X�V����
//=============================================================================
void CRanking::Update(void)
{
	m_nTime++;

	// �L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �W���C�p�b�h(XInput)�̎擾
	CXInputJoyPad *pXInputJoyPad = CManager::GetXInputJoyPad();

	// �t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_A, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_A, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_B, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_B, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_X, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_X, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_Y, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_Y, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_START, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_START, 1) == true && pFade->FADE_NONE)
	{// ���������ꂽ��
		pFade->Set(CManager::MODE_TITLE, pFade->FADE_OUT);
	}

	if (m_nTime % 300 == 0)
	{// ��莞�Ԃ�������
		pFade->Set(CManager::MODE_TITLE, pFade->FADE_OUT);
	}

	///*�f�o�b�O�p*/
	//if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	//{
	//	CManager::SetMode(CManager::MODE_TITLE);
	//}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CRanking::Draw(void)
{

}
