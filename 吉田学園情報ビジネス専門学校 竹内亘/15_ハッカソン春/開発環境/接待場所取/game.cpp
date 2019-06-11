//---------------------------------------------------------------------
// �Q�[������ [game.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "game.h"
#include "scene.h"
#include "scene2D.h"

#include "meshField.h"
#include "field.h"
#include "meshOrbit.h"
#include "meshCylinder.h"

#include "player.h"
#include "enemy.h"

#include "number.h"
#include "UIScore.h"
#include "UITime.h"
#include "UILife.h"
#include "UIItem.h"
#include "UIGauge.h"
#include "UIFinish.h"
#include "UIStart.h"
#include "UIExclamation.h"
#include "UIEnemy.h"

#include "objectBG.h"
#include "billboardEnemy.h"
#include "billboardItem.h"
#include "effect.h"
#include "effect3D.h"
#include "shadow.h"

#include "sound.h"
#include "input.h"
#include "manager.h"
#include "fade.h"

#include "Logo.h"
#include "pause.h"
#include "billboardObject.h"
#include "explosion.h"

#include "block.h"
#include "bullet.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define UIPOS_RIGHT		(1000)
#define UIPOS_LEFT		(280)

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
CPlayer		*CGame::m_pPlayer = NULL;
CUIItem		*CGame::m_pItem = NULL;
CUILife		*CGame::m_pLife = NULL;
CTime		*CGame::m_pTime = NULL;
CUIEnemy	*CGame::m_pUIEnemy = NULL;;

//--------------------------------------------
//�Q�[���N���X �R���X�g���N�^
//--------------------------------------------
CGame::CGame()
{
	m_nFadeCnt = 0;
	m_EnemyCreateCnt = 0;
	m_EnemyNum = 0;
}

//--------------------------------------------
//�Q�[���N���X �f�X�g���N�^
//--------------------------------------------
CGame::~CGame()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CGame *CGame::Create(void)
{
	//�^�C�g���̃|�C���^
	CGame *pGame;
	pGame = new CGame;
	//�^�C�g���̏�����
	pGame->Init();
	//�^�C�g���̏���Ԃ�
	return pGame;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGame::Init(void)
{
	//�J���� ���C�g�̏�����
	CManager::GetCamera()->Init();
	CManager::GetLight()->Init();

	//�e�N�X�`���⃂�f���̓ǂݍ���
	CObjectBG::Load();
	CBillBoardEnemy::Load();
	CBillBoardItem::Load();
	CField::Load();
	CUILife::Load();
	CUIItem::Load();
	CNumber::Load();
	CEffect::Load();
	C3DEffect::Load();
	CPause::Load();
	CUIGauge::Load();
	CShadow::Load();
	CBillBoardObject::Load();
	CUIFinish::Load();
	CUIStart::Load();
	CUIExclamation::Load();
	CEnemy::Load();
	// �u���b�N�̃��f���̓ǂݍ���
	CBlock::LoadModel();
	CBlock::LoadMat();
	// �e
	CBullet::LoadModel();
	CUIEnemy::Load();

	// ���Ђ�Ђ�̓ǂݍ���
	CExplosion::Load();
	//��̐���
	CSceneMeshCylinder::Create(D3DXVECTOR3(0, 18000, 0), 8000.0f, 28000.0f, 10, 1,CSceneMeshCylinder::CYLINDERTYPE_INWARD);

	//�|�[�Y����
	CPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), 150);
	//���b�V���t�B�[���h����
	CSceneMeshField::Create(D3DXVECTOR3(0, 0, 99900), 1000.0f, 100000.0f, 10, 1000);
	CSceneMeshField::Create(D3DXVECTOR3(-1000, 0, 99900), 1000.0f, 100000.0f, 10, 1000);

	//��
	//CField::Create(D3DXVECTOR3(-100, 0.3f, 100000), 200, 101000, CField::FIELDTEX_ROADWAY, 1, 1000);
	//��
	//CField::Create(D3DXVECTOR3(-2000, 0.3f, 100000), 1000, 101000, CField::FIELDTEX_GARDEN, 10, 1000);
	//CField::Create(D3DXVECTOR3(1000, 0.3f, 100000), 1000, 101000, CField::FIELDTEX_GARDEN, 10, 1000);
	//�v���C���[�𐶐�
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0,0,0), D3DXVECTOR3(0, D3DX_PI * 1.0f, 0),10);
	//3D�I�u�W�F�N�g

	for (int nCnt = 1; nCnt < 30; nCnt++)
	{
		CObjectBG::Create(D3DXVECTOR3(-550.0f, 0, (nCnt * 400.0f)), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL003, CObjectBG::MOVETYPE_NONE, 0);
		CObjectBG::Create(D3DXVECTOR3(550.0f, 0, (nCnt * 400.0f)), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL003, CObjectBG::MOVETYPE_NONE, 0);
	}

	for (int nCnt = 30; nCnt < 60; nCnt++)
	{
		CObjectBG::Create(D3DXVECTOR3(-550.0f, 0, (nCnt * 400.0f)), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL002, CObjectBG::MOVETYPE_NONE, 0);
		CObjectBG::Create(D3DXVECTOR3(550.0f, 0, (nCnt * 400.0f)), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL002, CObjectBG::MOVETYPE_NONE, 0);
	}

	for (int nCnt = 60; nCnt < 90; nCnt++)
	{
		CObjectBG::Create(D3DXVECTOR3(-550.0f, 0, (nCnt * 400.0f)), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL001, CObjectBG::MOVETYPE_NONE, 0);
		CObjectBG::Create(D3DXVECTOR3(550.0f, 0, (nCnt * 400.0f)), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL001, CObjectBG::MOVETYPE_NONE, 0);
	}

	//2D UI
	if (m_pLife != NULL)
	{
		m_pLife = NULL;
	}
	//���C�t��UI�𐶐�
	//m_pLife = CUILife::Create(D3DXVECTOR3(900, 70, 0), 50, 50);

	if (m_pItem != NULL)
	{
		m_pItem = NULL;
	}
	//�A�C�e���l������UI�𐶐�
	//m_pItem = CUIItem::Create(D3DXVECTOR3(80, 150, 0), 90, 100);
	//�Q�[�W�𐶐�
	//CUIGauge::Create(D3DXVECTOR3(1100, 680, 0), 100, 300);

	//�X�R�AUI�̐���
	if (m_pTime != NULL)
	{
		m_pTime = NULL;
	}
	//m_pTime = CTime::Create(D3DXVECTOR3(728, 90, 0), 80, 80);

	//�l�̏�����
	m_EnemyCreateCnt = 0;

	m_pUIEnemy = CUIEnemy::Create(D3DXVECTOR3(1000, 90, 0), 100, 100);

	return S_OK;
}

//=============================================================================
// �Q�[���N���X �I������
//=============================================================================
void CGame::Uninit(void)
{
	// �|�����G�̐��������o��
	SaveNumEnemy();
	//�e�N�X�`���⃂�f���̔j��
	CObjectBG::UnLoad();
	CBillBoardEnemy::UnLoad();
	CBillBoardItem::UnLoad();
	CField::UnLoad();
	CUILife::UnLoad();
	CUIItem::UnLoad();
	CNumber::UnLoad();
	CEffect::UnLoad();
	C3DEffect::UnLoad();
	CPause::UnLoad();
	CUIGauge::UnLoad();
	CShadow::UnLoad();
	CBillBoardObject::UnLoad();
	CUIFinish::UnLoad();
	CUIStart::UnLoad();
	CUIExclamation::UnLoad();
	CEnemy::UnLoad();
	CUIEnemy::UnLoad();

	// �e
	CBullet::UnloadModel();

	CBlock::UnloadModel();		// �u���b�N
								// �}�e���A���̉��
	CBlock::UnloadMat();		// �u���b�N

								// ���Ђ�Ђ�̔j��
	CExplosion::Unload();


	if (m_pLife != NULL)
	{
		//m_pLife->Uninit();
		m_pLife = NULL;
	}
	if (m_pItem != NULL)
	{
		//m_pItem->Uninit();
		m_pItem = NULL;
	}
	if (m_pTime != NULL)
	{
		//m_pTime->Uninit();
		m_pTime = NULL;
	}

	m_pUIEnemy = NULL;

	//�I�u�W�F�N�g�N���X�̔j��
	CScene::ReleaseAll();
}

//=============================================================================
// �Q�[���N���X �X�V����
//=============================================================================
void CGame::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

		//m_nFadeCnt++;
		//�؂�ւ�����
		//if (m_nFadeCnt > 20 && CFade::GetFade() == CFade::FADE_NONE)
		//{
		//	CFade::SetFade(CManager::MODE_GAME);
		//}
		//CFade::SetFade(CManager::MODE_RESULT);

	//�G�̐���
	bool m_bPause = CPause::GetPauseBool();

	if (m_bPause == false)
	{
		m_EnemyCreateCnt++;
		SetEnemySpawn();
	}



#ifdef  _DEBUG
		if (pInput->GetTrigger(DIK_E) == true && CFade::GetFade() == CFade::FADE_NONE
			/*|| pInputJoypad->GetTrigger(CInputJoypad::BUTTON_A) == true && CFade::GetFade() == CFade::FADE_NONE*/)
		{
			//�A�C�e���̐����Z�b�g
			//int *pnItem = CManager::GetGameItem();
			//*pnItem = m_pItem->GetItemNum();

			//�A�C�e���̐����Z�b�g
			//int *pnTime = CManager::GetGameTime();
			//*pnTime = m_pTime->GetTime();

			//CFade::SetFade(CManager::MODE_RESULT);
		}

		//CFade::SetFade(CManager::MODE_GAME);

	CDebugProc::Print(1, "	�Q�[��\n");
#endif

#ifdef  _DEBUG
	CDebugProc::Print(1, " Num�L�[  : (%d)\n", m_EnemyNum);
#endif


}
//=============================================================================
// �Q�[���N���X �`�揈��
//=============================================================================
void CGame::Draw(void)
{
}


#if 1
//=============================================================================
// �}�l�[�W���[�N���X �J�������擾
//=============================================================================
//CCamera *CGame::GetCamera(void)
//{
//	return m_pCamera;
//}

//=============================================================================
// �}�l�[�W���[�N���X ���C�g���擾
//=============================================================================
//CLight *CGame::GetLight(void)
//{
//	return m_pLight;
//}

#endif
//=============================================================================
// �Q�[���N���X �v���C���[���擾
//=============================================================================
CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//=============================================================================
// �Q�[���N���X �T�E���h���擾
//=============================================================================
//CSound *CGame::GetSound(void)
//{
//	return m_pSound;
//}

//=============================================================================
// �Q�[���N���X �A�C�e�����擾
//=============================================================================
CUIItem * CGame::GetUIItem(void)
{
	return m_pItem;
}

//=============================================================================
// �Q�[���N���X �^�C�����擾
//=============================================================================
CTime * CGame::GetUITime(void)
{
	return m_pTime;
}

//=============================================================================
// �|�����G�̐����Z�[�u
//=============================================================================
void CGame::SaveNumEnemy(void)
{
	FILE *pFile;

	// �t�@�C�����J��
	pFile = fopen(NUMENEMY_FILE, "w");

	if (pFile != NULL)
	{// �t�@�C�����J������
	 // ���f���̑���
		fprintf(pFile, "%d\n", m_pUIEnemy->GetEnemyNum());
		// �t�@�C�������
		fclose(pFile);
	}
	else
	{// �t�@�C�����J���Ȃ�������
		printf("�J���܂���ł���\n");
	}
}

//=============================================================================
// �Q�[���N���X ���C�t���擾
//=============================================================================
CUILife * CGame::GetUILife(void)
{
	return m_pLife;
}

//=============================================================================
// �Q�[���N���X ���C�t���擾
//=============================================================================
CUIEnemy * CGame::GetUIEnemy(void)
{
	return m_pUIEnemy;
}

//=============================================================================
// �Q�[���N���X �G�l�~�[�z�u
//=============================================================================
void CGame::SetEnemySpawn()
{

	if (m_EnemyCreateCnt == 250)
	{
		//�G�l�~�[�̐���
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		m_EnemyNum++;
	}
	else if (m_EnemyCreateCnt == 370)
	{
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		m_EnemyNum++;
	}
	else if (m_EnemyCreateCnt == 490)
	{
		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
		m_EnemyNum++;
	}
	else if (m_EnemyCreateCnt == 570)
	{
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		m_EnemyNum++;
	}
	else if (m_EnemyCreateCnt == 660)
	{
		m_EnemyNum++;
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
	}
	else if (m_EnemyCreateCnt == 780)
	{
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 880)
	{
		m_EnemyNum++;
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
	}
	else if (m_EnemyCreateCnt == 1080)
	{
		m_EnemyNum++;
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
	}
	else if (m_EnemyCreateCnt == 1180)
	{
		m_EnemyNum++;
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
	}
	else if (m_EnemyCreateCnt == 1280)
	{
		m_EnemyNum++;
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
	}
	else if (m_EnemyCreateCnt == 1380)
	{
		m_EnemyNum++;
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
	}
	else if (m_EnemyCreateCnt == 1580)
	{
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 1650)
	{
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 1700)
	{
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}

	else if (m_EnemyCreateCnt == 1880)
	{
		m_EnemyNum++;
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
	}
	else if (m_EnemyCreateCnt == 2180)
	{
		m_EnemyNum++;
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
	}
	else if (m_EnemyCreateCnt == 2250)
	{
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 2350)
	{
		m_EnemyNum++;
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
	}
	else if (m_EnemyCreateCnt == 2380)
	{
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 2420)
	{
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 2580)
	{
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
	}
	else if (m_EnemyCreateCnt == 2650)
	{
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 2720)
	{
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 2850)
	{
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
	}

	else if (m_EnemyCreateCnt == 2950)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3020)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3030)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3050)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}

	else if (m_EnemyCreateCnt == 3090)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3130)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3210)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3190)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3250)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3280)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3300)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3310)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3340)
	{
		m_EnemyNum++;
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3360)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3370)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3400)
	{
		// ���Ђ�Ђ�
		CExplosion::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3410)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3430)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3450)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}

	else if (m_EnemyCreateCnt == 3460)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3490)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3520)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3540)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3560)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3580)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3660)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3680)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3700)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3720)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3740)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3760)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3780)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3800)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3820)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3840)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3860)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3880)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3900)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3920)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3940)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3960)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
}
