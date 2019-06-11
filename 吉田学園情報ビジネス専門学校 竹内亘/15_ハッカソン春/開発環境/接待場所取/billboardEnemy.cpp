//=============================================================================
//
// �G�r���{�[�h���� [billboardEnemy.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "billboardEnemy.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\akira000.png"			//�e�N�X�`���̃t�@�C����
#define TEX_POS_X_INIT			(1.0f)									//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)									//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)									//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)									//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)									//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)									//�e�N�X�`�����WV��

#define DEPTH					(30.0f)
#define PLAYER_DEPTH			(1.0f)			//�v���C���[�̕������p
#define PLAYER_HEIGHT			(10.0f)			//�v���C���[�̔w�̍���

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9			CBillBoardEnemy::m_pTexture[ENEMYTEX_MAX] = {};

//--------------------------------------------
//�r���{�[�h(�G)�N���X �R���X�g���N�^
//--------------------------------------------
CBillBoardEnemy::CBillBoardEnemy()
{
	m_pos = D3DXVECTOR3(0,0,0);						// �ʒu
	m_move = D3DXVECTOR3(0, 0, 0);					// �ړ���
	m_posold = D3DXVECTOR3(0, 0, 0);					// �O��̈ʒu
	m_TexType = ENEMYTEX_HUMAN000;
	m_moveType = ENEMYMOVE_NONE;

}

//--------------------------------------------
//�r���{�[�h(�G)�N���X �f�X�g���N�^
//--------------------------------------------
CBillBoardEnemy::~CBillBoardEnemy()
{
}

//--------------------------------------------
//�r���{�[�h(�G)�̐���
//--------------------------------------------
CBillBoardEnemy *CBillBoardEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, ENEMYTEX TexType, ENEMYMOVE moveType)
{
	CBillBoardEnemy *pEnemy;

	pEnemy = new CBillBoardEnemy;

	pEnemy->m_move = move;
	pEnemy->m_pos = pos;
	pEnemy->m_TexType = TexType;
	pEnemy->m_moveType = moveType;
	pEnemy->m_fHeight = fHeight;
	pEnemy->m_fWidth = fWidth;
	pEnemy->Init();

	return pEnemy;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBillBoardEnemy::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pBillBoard = CSceneBillBoard::Create(m_pos, D3DXVECTOR3(0,0,0), m_fWidth, m_fHeight);
	m_pBillBoard->BindTexture(m_pTexture[m_TexType]);
	m_pBillBoard->Setpos(m_pos);
	//�I�u�W�F�N�g��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_BILLBOARDENEMY);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBillBoardEnemy::Uninit(void)
{
	if (m_pBillBoard != NULL)
	{
		m_pBillBoard->Uninit();
		m_pBillBoard = NULL;
	}
	//����������(�v���C���[��j��)
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBillBoardEnemy::Update(void)
{


}

//=============================================================================
// �`�揈��
//=============================================================================
void CBillBoardEnemy::Draw(void)
{
	//if (m_pBillBoard != NULL)
	//{
	//	m_pBillBoard->Draw();
	//}
}
//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CBillBoardEnemy::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME000, &m_pTexture[0]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CBillBoardEnemy::UnLoad(void)
{
	for (int nCnt = 0; nCnt < ENEMYTEX_MAX; nCnt++)
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
bool CBillBoardEnemy::CollisionBillboardEnemy(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
	D3DXVECTOR3 WidthMax;
	D3DXVECTOR3 WidthMin;
	WidthMax.x = m_pos.x + m_fWidth;	// �ʒu���݂̉���
	WidthMax.z = m_pos.z + DEPTH;		// �ʒu���݂̉��s��

	WidthMin.x = m_pos.x - m_fWidth;	// �ʒu���݂̉���
	WidthMin.z = m_pos.z - DEPTH;		// �ʒu���݂̉��s��

	if (pPos->x >= WidthMin.x - PLAYER_DEPTH && pPos->x <= WidthMax.x + PLAYER_DEPTH)
	{// X�͈͓̔��ɂ���
		if (pPos->z >= WidthMin.z - PLAYER_DEPTH && pPos->z <= WidthMax.z + PLAYER_DEPTH)
		{// Z�͈͓̔��ɂ���

		 // ���ړ��I�u�W�F�N�g
			if (pPosOld->x - PLAYER_DEPTH >= WidthMax.x && pPos->x - PLAYER_DEPTH < WidthMax.x)
			{// �E���甲�����ꍇ
				pPos->x = WidthMax.x + PLAYER_DEPTH;
			}
			else if (pPosOld->x + PLAYER_DEPTH <= WidthMin.x && pPos->x + PLAYER_DEPTH > WidthMin.x)
			{// �����甲�����ꍇ
				pPos->x = WidthMin.x - PLAYER_DEPTH;
			}
			if (pPosOld->z - PLAYER_DEPTH >= WidthMax.z && pPos->z - PLAYER_DEPTH < WidthMax.z)
			{// �����甲�����ꍇ
				pPos->z = WidthMax.z + PLAYER_DEPTH;
			}
			else if (pPosOld->z + PLAYER_DEPTH <= WidthMin.z && pPos->z + PLAYER_DEPTH > WidthMin.z)
			{// ��O���甲�����ꍇ
				pPos->z = WidthMin.z - PLAYER_DEPTH;
				pMove->z = -100.0f;
			}
		}
	}
	return false;
}
