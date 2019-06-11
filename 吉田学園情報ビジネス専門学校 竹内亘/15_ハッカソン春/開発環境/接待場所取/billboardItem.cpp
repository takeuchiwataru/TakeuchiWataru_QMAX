//=============================================================================
//
// �A�C�e���r���{�[�h���� [billboardEnemy.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "billboardItem.h"
#include "manager.h"
#include "scene2D.h"
#include "UIItem.h"
#include "game.h"
#include "effect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\BILLBOARD\\CAN2D.png"			//�e�N�X�`���̃t�@�C����
#define TEX_POS_X_INIT			(1.0f)									//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)									//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)									//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)									//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)									//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)									//�e�N�X�`�����WV��

#define DEPTH					(30.0f)
#define PLAYER_DEPTH			(10.0f)			//�v���C���[�̕������p
#define PLAYER_HEIGHT			(10.0f)			//�v���C���[�̔w�̍���

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9			CBillBoardItem::m_pTexture[ITEMTEX_MAX] = {};

//--------------------------------------------
//�r���{�[�h(�A�C�e��)�N���X �R���X�g���N�^
//--------------------------------------------
CBillBoardItem::CBillBoardItem()
{
	m_pos = D3DXVECTOR3(0,0,0);				// �ʒu
	m_move = D3DXVECTOR3(0, 0, 0);			// �ړ���
	m_posold = D3DXVECTOR3(0, 0, 0);		// �O��̈ʒu
	m_fSpin = 0;							// ��]
	m_fScale = 0;							// �g��k��

	m_Scene2DPos = D3DXVECTOR3(0, 0, 0);
	m_Scene2DMove = D3DXVECTOR3(0, 0, 0);
	m_Scene2DCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

	m_TexType = ITEMTEX_NORMAL;
	m_bGetItem = false;
	m_bCreate2D = false;
	m_pScene2D = NULL;

}

//--------------------------------------------
//�r���{�[�h(�A�C�e��)�N���X �f�X�g���N�^
//--------------------------------------------
CBillBoardItem::~CBillBoardItem()
{
}

//--------------------------------------------
//�r���{�[�h(�A�C�e��)�̐���
//--------------------------------------------
CBillBoardItem *CBillBoardItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, ITEMTEX TexType)
{
	CBillBoardItem *pItem;

	pItem = new CBillBoardItem;

	pItem->m_move = move;
	pItem->m_pos = pos;
	pItem->m_TexType = TexType;
	pItem->m_fHeight = fHeight;
	pItem->m_fWidth = fWidth;
	pItem->Init();

	return pItem;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBillBoardItem::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�r���{�[�h�𐶐�
	m_pBillBoard = CSceneBillBoard::Create(m_pos, D3DXVECTOR3(0, 0, 0), m_fWidth, m_fHeight);
	m_pBillBoard->BindTexture(m_pTexture[m_TexType]);
	m_pBillBoard->Setpos(m_pos);
	//�e�̐���
	m_pShadow = CShadow::Create(D3DXVECTOR3(m_pos.x, 1.0f, m_pos.z), 20, 10, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), CShadow::SHADOWTYPE_NORMAL);
	//�I�u�W�F�N�g��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_BILLBOARDITEM);
	//�l�̏�����
	m_fSpin = 0;
	m_fScale = 0;
	m_Scene2DPos = D3DXVECTOR3(0, 0, 0);
	m_Scene2DMove = D3DXVECTOR3(0, 0, 0);
	m_TexType = ITEMTEX_NORMAL;
	m_bGetItem = false;
	m_bCreate2D = false;
	m_pScene2D = NULL;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBillBoardItem::Uninit(void)
{
	if (m_pBillBoard != NULL)
	{
		m_pBillBoard->Uninit();
		m_pBillBoard = NULL;
	}

	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

	if (m_pShadow != NULL)
	{
		m_pShadow = NULL;
	}

	//����������(�j��)
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBillBoardItem::Update(void)
{
	if (m_bGetItem == true && m_bCreate2D == false && m_pBillBoard != NULL)
	{
		//�r���{�[�h�̔j��
		if (m_pBillBoard != NULL)
		{
			m_pBillBoard->Uninit();
			m_pBillBoard = NULL;
		}
		//�e�̔j��
		if (m_pShadow != NULL)
		{
			m_pShadow->Uninit();
			m_pShadow = NULL;
		}
		//2D�|���S���𐶐�
		m_pScene2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 400, 0), 50, 50);
		m_Scene2DPos = D3DXVECTOR3(SCREEN_WIDTH / 2, 400, 0);
		m_Scene2DPosInit = D3DXVECTOR3(SCREEN_WIDTH / 2, 400, 0);
		//m_Scene2DMove = D3DXVECTOR3(-1.0f, 1.0f, 0);
		m_pScene2D->BindTexture(m_pTexture[0]);
		m_bCreate2D = true;

	}

	if (m_pScene2D != NULL)
	{
		//�t���O��true�̎��z�[�~���O����
		D3DXVECTOR3 m_HomingPos;
		D3DXVECTOR3 m_TargetPos = D3DXVECTOR3(80, 150, 0);
		D3DXVECTOR3 Angle = D3DXVECTOR3(0, 0, 0);
		float fMoveAngle = 0;
		float fDestAngle = 0;
		float fDiffAngle = 0;

		//�v���C���[�ƃG�l�~�[�̋��������߂�
		m_HomingPos.x = m_TargetPos.x - m_Scene2DPosInit.x;
		m_HomingPos.y = m_TargetPos.y - m_Scene2DPosInit.y;
		//�e�ƃv���C���[�̋��������߂�
		Angle.x = m_Scene2DPos.x - m_TargetPos.x;
		Angle.y = m_Scene2DPos.y - m_TargetPos.y;

		//�p�x�����߂�
		fMoveAngle = atan2f(m_HomingPos.x, m_HomingPos.y);
		fDestAngle = atan2f(Angle.x, Angle.y);

		fDiffAngle = fDestAngle - fMoveAngle;
		if (fDiffAngle > D3DX_PI)
		{
			fDiffAngle -= D3DX_PI * 2.0f;
		}
		if (fDiffAngle < D3DX_PI)
		{
			fDiffAngle += D3DX_PI * 2.0f;
		}

		fMoveAngle += fDiffAngle * 1.0f;

		if (fMoveAngle > D3DX_PI)
		{
			fMoveAngle -= D3DX_PI * 2.0f;
		}
		if (fMoveAngle < D3DX_PI)
		{
			fMoveAngle += D3DX_PI * 2.0f;
		}

		D3DXVECTOR3 MovePos(0.0f, 0.0f, 0.0f);
		//�ړ��ʂ�ݒ�
		MovePos.x += sinf(fMoveAngle) * 25.0f;
		MovePos.y += cosf(fMoveAngle) * 25.0f;
		m_Scene2DMove = MovePos;

		//�ڕW�n�_�܂ł̒l�������Ă���
		m_Scene2DPos -= m_Scene2DMove;

		//��]
		m_fSpin += 0.1f;
		//�k��
		m_fScale -= 0.5f;

		if (m_fScale < -40)
		{
			m_fScale = -40;
		}

		//�����x
		m_Scene2DCol.a -= 0.005f;


		//�p�x�����l�ɂȂ����Ƃ�
		if (m_fSpin > D3DX_PI)
		{
			m_fSpin *= -1;
		}
		else if (m_fSpin < -D3DX_PI)
		{
			m_fSpin *= -1;
		}

		//�|���S���̍X�V
		m_pScene2D->SetPos(m_Scene2DPos,m_fSpin,m_fScale, m_Scene2DCol);

#ifdef  _DEBUG
		CDebugProc::Print(1, " 2DITEM�ʒu : ( %.1f,%.1f,%.1f )\n", m_Scene2DPos.x
			, m_Scene2DPos.y, m_Scene2DPos.z);
#endif

		if (m_TargetPos.x - 20.0f < m_Scene2DPos.x && m_TargetPos.x + 20.0f > m_Scene2DPos.x
			&& m_TargetPos.y - 20.0f < m_Scene2DPos.y && m_TargetPos.y + 20.0f > m_Scene2DPos.y)
		{
			//UI�̈ʒu�ɍs�����Ƃ��ɔj��
			m_pScene2D->Uninit();
			m_pScene2D = NULL;
			//�A�C�e�����J�E���g
			CUIItem *pItem = CGame::GetUIItem();
			pItem->PlusItem(1);
			pItem->SetItemBool(true);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBillBoardItem::Draw(void)
{

}
//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CBillBoardItem::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCnt = 0; nCnt < ITEMTEX_MAX; nCnt++)
	{	//�e�N�X�`���̏�����
		m_pTexture[nCnt] = NULL;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME000, &m_pTexture[0]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CBillBoardItem::UnLoad(void)
{
	for (int nCnt = 0; nCnt < ITEMTEX_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// �����蔻�菈��
//=============================================================================
bool CBillBoardItem::CollisionBillboardItem(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
	//�v���C���[���擾
	CPlayer *pPlayer = CGame::GetPlayer();
	float fPlayerDepth; //�v���C���[�̑傫��
	fPlayerDepth = 0;

	D3DXVECTOR3 WidthMax;
	D3DXVECTOR3 WidthMin;
	WidthMax.x = m_pos.x + m_fWidth;	// �ʒu���݂̉���
	WidthMax.z = m_pos.z + DEPTH;		// �ʒu���݂̉��s��

	WidthMin.x = m_pos.x - m_fWidth;	// �ʒu���݂̉���
	WidthMin.z = m_pos.z - DEPTH;		// �ʒu���݂̉��s��

										//��]���ɓ����蔻������Ɋg��
	if (pPlayer->GetMotionState() == CPlayer::MOTIONSTATE_TUMBLE)
	{
		fPlayerDepth = 20;
	}

	if (m_bGetItem == false)
	{
		if (pPos->x >= WidthMin.x - PLAYER_DEPTH - fPlayerDepth&& pPos->x <= WidthMax.x + PLAYER_DEPTH + fPlayerDepth)
		{// X�͈͓̔��ɂ���
			if (pPos->z >= WidthMin.z - PLAYER_DEPTH && pPos->z <= WidthMax.z + PLAYER_DEPTH)
			{// Z�͈͓̔��ɂ���
			 //�T�E���h�����擾
				CSound *pSound = CManager::GetSound(0);
				pSound->PlaySound(pSound->SOUND_LABEL_SE_ITEMGET);
				m_bGetItem = true;
				//Uninit();
			}
		}
	}
	return false;
}
