//=============================================================================
//
// �v���C���[����(�e�q�֌W�Ȃ�) [player2.cpp]
// Author : �|���j
//
//=============================================================================
#include "player2.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"
#include "meshWall.h"
#include "item2.h"
#include "model.h"
#include "enemy2.h"
#include "life.h"
#include "fade.h"
#include "game.h"
#include "effect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_NAME "data/MODEL/houki2.x"	// ���f����
#define MOVE_SPEED (1.0f)					// �v���C���[�̓����X�s�[�h
#define	MAX_MODEL (10)						// �ǂݍ��ރ��f���̐�

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXMESH g_pMeshPlayer2 = NULL;				// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatPlayer2 = NULL;			// �}�e���A�����ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePlayer2 = NULL;	// �e�N�X�`���ւ̃|�C���^
DWORD g_nNumMatPlayer2 = 0;						// �}�e���A�����̐�
//D3DXVECTOR3 g_posModel;						// �ʒu
//D3DXVECTOR3 g_rotModel;						// ����
//D3DXMATRIX g_mtxWorldModel;					// ���[���h�}�g���b�N�X
Player2 g_Player2;								// ���f���̏��

//=============================================================================
// ����������
//=============================================================================
void InitPlayer2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(PLAYER_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer2,
		NULL,
		&g_nNumMatPlayer2,
		&g_pMeshPlayer2);

	// �v���C���[�̏�����
	g_Player2.pos = D3DXVECTOR3(300.0f, 50.0f, 0.0f);
	g_Player2.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player2.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player2.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player2.nIdexShadow = SetShadow(g_Player2.pos, g_Player2.rot);
	g_Player2.nLife = 5;
	g_Player2.state = PLAYERSTATE2_APPEAR;
	g_Player2.nCounterState = 120;
	g_Player2.VtxMinModel = D3DXVECTOR3(10000, 10000, 10000);
	g_Player2.VtxMaxModel = D3DXVECTOR3(-10000, -10000, -10000);
	g_Player2.bDisp = true;

	int nNumVtex;					// ���_��
	DWORD sizeFvF;					// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^

	// ���_�����擾
	nNumVtex = g_pMeshPlayer2->GetNumVertices();

	// ���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFvF = D3DXGetFVFVertexSize(g_pMeshPlayer2->GetFVF());

	// ���_�o�b�t�@�����b�N
	g_pMeshPlayer2->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (g_Player2.VtxMinModel.x >= vtx.x)
		{
			g_Player2.VtxMinModel.x = vtx.x;
		}
		if (g_Player2.VtxMinModel.y >= vtx.y)
		{
			g_Player2.VtxMinModel.y = vtx.y;
		}
		if (g_Player2.VtxMinModel.z >= vtx.z)
		{
			g_Player2.VtxMinModel.z = vtx.z;
		}

		if (g_Player2.VtxMaxModel.x <= vtx.x)
		{
			g_Player2.VtxMaxModel.x = vtx.x;
		}
		if (g_Player2.VtxMaxModel.y <= vtx.y)
		{
			g_Player2.VtxMaxModel.y = vtx.y;
		}
		if (g_Player2.VtxMaxModel.z <= vtx.z)
		{
			g_Player2.VtxMaxModel.z = vtx.z;
		}
		pVtxBuff += sizeFvF;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pMeshPlayer2->UnlockVertexBuffer();
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer2(void)
{
	// ���b�V���̊J��
	if (g_pMeshPlayer2 != NULL)
	{
		g_pMeshPlayer2->Release();
		g_pMeshPlayer2 = NULL;
	}

	// �}�e���A���̊J��
	if (g_pBuffMatPlayer2 != NULL)
	{
		g_pBuffMatPlayer2->Release();
		g_pBuffMatPlayer2 = NULL;
	}

	// �e�N�X�`���̉��
	if (g_pTexturePlayer2 != NULL)
	{
		g_pTexturePlayer2->Release();
		g_pTexturePlayer2 = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer2(void)
{
	// �ߋ��̈ʒu���擾
	g_Player2.posOld = g_Player2.pos;

	float fDiffAngle; // ����

	// �J�����̎擾
	Camera *pCamera;
	pCamera = GetCamera();

	switch (g_Player2.state)
	{
	case  PLAYERSTATE2_APPEAR:
		g_Player2.nCounterState--;
		if (g_Player2.nCounterState <= 0)
		{// ������x���Ԃ��o������
			g_Player2.state = PLAYERSTATE2_NORMAL;
		}
		break;

	case PLAYERSTATE2_NORMAL:
		break;

	case PLAYERSTATE2_DAMEGE:
		g_Player2.nCounterState--;
		if (g_Player2.nCounterState <= 0)
		{// ������x���Ԃ��o������
			g_Player2.state = PLAYERSTATE2_NORMAL;
		}
		break;

	case PLAYERSTATE2_DEATH:
		g_Player2.nCounterState--;
		if (g_Player2.nCounterState <= 0)
		{// ������x���Ԃ��o������

			SetGameState(GAMESTATE_GAMEOVER);
			g_Player2.state = PLAYERSTATE2_MAX;
		}
		break;

	}

	if (GetKeyboardPress(DIK_UP) == true || GetKeyboardPress(DIK_W) == true)
	{// ������������ or W����������
		if (GetKeyboardPress(DIK_RIGHT) == true || GetKeyboardPress(DIK_D) == true)
		{// �����Ɂ����������� or D����������
			g_Player2.move.x -= sinf(pCamera->rot.y - D3DX_PI * 0.75f) * MOVE_SPEED;
			g_Player2.move.z -= cosf(pCamera->rot.y - D3DX_PI * 0.75f) * MOVE_SPEED;

			fDiffAngle = (pCamera->rot.y - (D3DX_PI * 0.75f)) - g_Player2.rot.y;
			if (fDiffAngle > D3DX_PI)
			{
				fDiffAngle -= D3DX_PI * 2.0f;
			}
			else if (fDiffAngle < -D3DX_PI)
			{
				fDiffAngle += D3DX_PI * 2.0f;
			}

			g_Player2.rot.y += fDiffAngle * 0.3f;

			if (g_Player2.rot.y > D3DX_PI)
			{
				g_Player2.rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_Player2.rot.y < -D3DX_PI)
			{
				g_Player2.rot.y += D3DX_PI * 2.0f;
			}
		}
		else if (GetKeyboardPress(DIK_LEFT) == true || GetKeyboardPress(DIK_A) == true)
		{// �����Ɂ����������� or A����������
			g_Player2.move.x -= sinf(pCamera->rot.y + D3DX_PI * 0.75f) * MOVE_SPEED;
			g_Player2.move.z -= cosf(pCamera->rot.y + D3DX_PI * 0.75f) * MOVE_SPEED;

			fDiffAngle = (pCamera->rot.y + (D3DX_PI * 0.75f)) - g_Player2.rot.y;
			if (fDiffAngle > D3DX_PI)
			{
				fDiffAngle -= D3DX_PI * 2.0f;
			}
			else if (fDiffAngle < -D3DX_PI)
			{
				fDiffAngle += D3DX_PI * 2.0f;
			}

			g_Player2.rot.y += fDiffAngle * 0.3f;

			if (g_Player2.rot.y > D3DX_PI)
			{
				g_Player2.rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_Player2.rot.y < -D3DX_PI)
			{
				g_Player2.rot.y += D3DX_PI * 2.0f;
			}
		}
		else
		{
			g_Player2.move.x -= sinf((D3DX_PI * 1.0f) + pCamera->rot.y) * MOVE_SPEED;
			g_Player2.move.z -= cosf((D3DX_PI * 1.0f) + pCamera->rot.y) * MOVE_SPEED;

			fDiffAngle = (pCamera->rot.y - (D3DX_PI * 1.0f)) - g_Player2.rot.y;
			if (fDiffAngle > D3DX_PI)
			{
				fDiffAngle -= D3DX_PI * 2.0f;
			}
			else if (fDiffAngle < -D3DX_PI)
			{
				fDiffAngle += D3DX_PI * 2.0f;
			}

			g_Player2.rot.y += fDiffAngle * 0.3f;

			if (g_Player2.rot.y > D3DX_PI)
			{
				g_Player2.rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_Player2.rot.y < -D3DX_PI)
			{
				g_Player2.rot.y += D3DX_PI * 2.0f;
			}
		}
		SetEffect(D3DXVECTOR3(g_Player2.pos.x, g_Player2.pos.y - 40, g_Player2.pos.z), 10.0f, 5);
	}
	else if (GetKeyboardPress(DIK_DOWN) == true || GetKeyboardPress(DIK_S) == true)
	{// ������������ or S����������
		if (GetKeyboardPress(DIK_RIGHT) == true || GetKeyboardPress(DIK_D) == true)
		{// �����Ɂ����������� or D����������
			g_Player2.move.x -= sinf(pCamera->rot.y - D3DX_PI * 0.25f) * MOVE_SPEED;
			g_Player2.move.z -= cosf(pCamera->rot.y - D3DX_PI * 0.25f) * MOVE_SPEED;

			fDiffAngle = (pCamera->rot.y - (D3DX_PI * 0.25f)) - g_Player2.rot.y;
			if (fDiffAngle > D3DX_PI)
			{
				fDiffAngle -= D3DX_PI * 2.0f;
			}
			else if (fDiffAngle < -D3DX_PI)
			{
				fDiffAngle += D3DX_PI * 2.0f;
			}

			g_Player2.rot.y += fDiffAngle * 0.3f;

			if (g_Player2.rot.y > D3DX_PI)
			{
				g_Player2.rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_Player2.rot.y < -D3DX_PI)
			{
				g_Player2.rot.y += D3DX_PI * 2.0f;
			}
		}
		else if (GetKeyboardPress(DIK_LEFT) == true || GetKeyboardPress(DIK_A) == true)
		{// �����Ɂ����������� or A����������
			g_Player2.move.x -= sinf(pCamera->rot.y + D3DX_PI * 0.25f) * MOVE_SPEED;
			g_Player2.move.z -= cosf(pCamera->rot.y + D3DX_PI * 0.25f) * MOVE_SPEED;

			fDiffAngle = (pCamera->rot.y + (D3DX_PI * 0.25f)) - g_Player2.rot.y;
			if (fDiffAngle > D3DX_PI)
			{
				fDiffAngle -= D3DX_PI * 2.0f;
			}
			else if (fDiffAngle < -D3DX_PI)
			{
				fDiffAngle += D3DX_PI * 2.0f;
			}

			g_Player2.rot.y += fDiffAngle * 0.3f;

			if (g_Player2.rot.y > D3DX_PI)
			{
				g_Player2.rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_Player2.rot.y < -D3DX_PI)
			{
				g_Player2.rot.y += D3DX_PI * 2.0f;
			}
		}
		else
		{
			g_Player2.move.x -= sinf((D3DX_PI * 0.0f) + pCamera->rot.y) * MOVE_SPEED;
			g_Player2.move.z -= cosf((D3DX_PI * 0.0f) + pCamera->rot.y) * MOVE_SPEED;

			fDiffAngle = (pCamera->rot.y - (D3DX_PI * 0.0f)) - g_Player2.rot.y;
			if (fDiffAngle > D3DX_PI)
			{
				fDiffAngle -= D3DX_PI * 2.0f;
			}
			else if (fDiffAngle < -D3DX_PI)
			{
				fDiffAngle += D3DX_PI * 2.0f;
			}

			g_Player2.rot.y += fDiffAngle * 0.3f;

			if (g_Player2.rot.y > D3DX_PI)
			{
				g_Player2.rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_Player2.rot.y < -D3DX_PI)
			{
				g_Player2.rot.y += D3DX_PI * 2.0f;
			}
		}
		SetEffect(D3DXVECTOR3(g_Player2.pos.x, g_Player2.pos.y - 40, g_Player2.pos.z), 10.0f, 5);
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true || GetKeyboardPress(DIK_D) == true)
	{// ������������ or D����������
		g_Player2.move.x += sinf((D3DX_PI * 0.5f) + pCamera->rot.y) * MOVE_SPEED;
		g_Player2.move.z += cosf((D3DX_PI * 0.5f) + pCamera->rot.y)* MOVE_SPEED;

		fDiffAngle = (pCamera->rot.y - (D3DX_PI * 0.5f)) - g_Player2.rot.y;
		if (fDiffAngle > D3DX_PI)
		{
			fDiffAngle -= D3DX_PI * 2.0f;
		}
		else if (fDiffAngle < -D3DX_PI)
		{
			fDiffAngle += D3DX_PI * 2.0f;
		}

		g_Player2.rot.y += fDiffAngle * 0.3f;

		if (g_Player2.rot.y > D3DX_PI)
		{
			g_Player2.rot.y -= D3DX_PI * 2.0f;
		}
		else if (g_Player2.rot.y < -D3DX_PI)
		{
			g_Player2.rot.y += D3DX_PI * 2.0f;
		}
		SetEffect(D3DXVECTOR3(g_Player2.pos.x, g_Player2.pos.y - 40, g_Player2.pos.z), 10.0f, 5);
	}
	else if (GetKeyboardPress(DIK_LEFT) == true || GetKeyboardPress(DIK_A) == true)
	{// ������������ or A����������
		g_Player2.move.x += sinf((D3DX_PI * -0.5f) + pCamera->rot.y) * MOVE_SPEED;
		g_Player2.move.z += cosf((D3DX_PI * -0.5f) + pCamera->rot.y) * MOVE_SPEED;

		fDiffAngle = (pCamera->rot.y - (D3DX_PI * -0.5f)) - g_Player2.rot.y;
		if (fDiffAngle > D3DX_PI)
		{
			fDiffAngle -= D3DX_PI * 2.0f;
		}
		else if (fDiffAngle < -D3DX_PI)
		{
			fDiffAngle += D3DX_PI * 2.0f;
		}

		g_Player2.rot.y += fDiffAngle * 0.3f;

		if (g_Player2.rot.y > D3DX_PI)
		{
			g_Player2.rot.y -= D3DX_PI * 2.0f;
		}
		else if (g_Player2.rot.y < -D3DX_PI)
		{
			g_Player2.rot.y += D3DX_PI * 2.0f;
		}
		SetEffect(D3DXVECTOR3(g_Player2.pos.x, g_Player2.pos.y - 40, g_Player2.pos.z), 10.0f, 5);
	}

	//if (GetKeyboardTrigger(DIK_SPACE) == true)
	//{// �e�̔���
	//	SetBullet(D3DXVECTOR3(g_Player2.pos.x,g_Player2.pos.y + 20, g_Player2.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f) * D3DX_PI,
	//		D3DXVECTOR3(sinf(g_Player2.rot.y) * -D3DX_PI, 0.0f, cosf(g_Player2.rot.y) * -D3DX_PI));
	//}

	// ���b�V���E�H�[���̎擾
	MeshWall *pMeshWall;
	pMeshWall = GetMeshWall();

	// �ǂƂ̓����蔻��
	if (g_Player2.pos.z > 720)
	{ 
		g_Player2.pos.z = 720;
	}
	else if (g_Player2.pos.z < -20)
	{
		g_Player2.pos.z = -20;
	}
	else if (g_Player2.pos.x > 720)
	{
		g_Player2.pos.x = 720;
	}
	else if (g_Player2.pos.x < -20)
	{
		g_Player2.pos.x = -20;
	}
	else
	{
		g_Player2.move;
	}

	// �ق����U��
	g_Player2.rot.z += 0.05f;
	if (g_Player2.rot.z > 0.5)
	{
		g_Player2.rot.z -= 1.0;
	}
	else if (g_Player2.rot.z < -0.5)
	{
		g_Player2.rot.z += 1.0;
	}

	// ����
	g_Player2.pos += g_Player2.move;
	g_Player2.move.x += (0.0f - g_Player2.move.x) * 0.2f;
	g_Player2.move.z += (0.0f - g_Player2.move.z) * 0.2f;

	//�A�C�e���Ƃ̓����蔻��
	if (CollisionItem2(&g_Player2.pos, &g_Player2.posOld, &g_Player2.move) == true)
	{
		g_Player2.bDisp = false;			//�g�p���ĂȂ�
	}
	else
	{
		if (g_Player2.bDisp == false)
		{
			g_Player2.bDisp = true;		//�g�p���Ă�
		}
	}

	// �G�Ƃ̓����蔻��
	if (CollisionEnemy2(&g_Player2.pos, &g_Player2.posOld, &g_Player2.move) == true)
	{
		g_Player2.bDisp = false;			//�g�p���ĂȂ�
	}
	else
	{
		if (g_Player2.bDisp == false)
		{
			g_Player2.bDisp = true;		//�g�p���Ă�
		}
	}

	// ���f���Ƃ̓����蔻��
	if (CollisionModel(&g_Player2.pos, &g_Player2.posOld, &g_Player2.move) == true)
	{
		g_Player2.bDisp = false;			//�g�p���ĂȂ�
	}
	else
	{
		if (g_Player2.bDisp == false)
		{
			g_Player2.bDisp = true;		//�g�p���Ă�
		}
	}

	SetPositionShadow(g_Player2.nIdexShadow, D3DXVECTOR3(g_Player2.pos.x,g_Player2.pos.y -50,g_Player2.pos.z));
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxParent;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player2.mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player2.rot.y, g_Player2.rot.x, g_Player2.rot.z);
	D3DXMatrixMultiply(&g_Player2.mtxWorld, &g_Player2.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Player2.pos.x, g_Player2.pos.y, g_Player2.pos.z);
	D3DXMatrixMultiply(&g_Player2.mtxWorld, &g_Player2.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Player2.mtxWorld);

	// X�t�@�C���`��
	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer2->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer2; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		pDevice->SetTexture(0, g_pTexturePlayer2);

		// ���f��(�p�[�c)�̕`��
		g_pMeshPlayer2->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �v���C���[�̃_���[�W����
//=============================================================================
void HitPlayer(int nDamage)
{
	g_Player2.nLife -= nDamage;

	if (g_Player2.nLife <= 0)
	{// �v���C���[�̃��C�t��0�ɂȂ�����
		if (g_Player2.bDisp == true)
		{
			g_Player2.bDisp = false;
			SetGameState(GAMESTATE_END);
		}
		else
		{
			g_Player2.state = PLAYERSTATE2_DAMEGE;
			g_Player2.nCounterState = 120;
		}
	}
	CutLife(1);
}

//=============================================================================
// �v���C���[�̓����蔻�菈��
//=============================================================================
bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove)
{
	bool bHit = false;		// �����������ǂ���

	if (g_Player2.bDisp == true)
	{// �v���C���[���g���Ă���
		if (pPos->x >= g_Player2.pos.x + g_Player2.VtxMinModel.x &&
			pPos->x <= g_Player2.pos.x + g_Player2.VtxMaxModel.x)
		{// Z�ʂ̔���
			if (pPosold->z <= g_Player2.pos.z + g_Player2.VtxMinModel.z &&
				pPos->z >= g_Player2.pos.z + g_Player2.VtxMinModel.z)
			{// ��O�̔���
				pPos->z = pPosold->z;
			}
			else if (pPosold->z >= g_Player2.pos.z + (g_Player2.VtxMaxModel.z) &&
				pPos->z <= g_Player2.pos.z + (g_Player2.VtxMaxModel.z))
			{// ���̔���
				pPos->z = pPosold->z;
			}
		}
		if (pPos->z >= g_Player2.pos.z + g_Player2.VtxMinModel.z &&
			pPos->z <= g_Player2.pos.z + g_Player2.VtxMaxModel.z)
		{// X�ʂ̔���
			if (pPosold->x >= g_Player2.pos.x + g_Player2.VtxMaxModel.x &&
				pPos->x <= g_Player2.pos.x + g_Player2.VtxMaxModel.x)
			{// �E�ʂ̔���
				pPos->x = pPosold->x;
			}
			else if (pPosold->x <= g_Player2.pos.x + (g_Player2.VtxMinModel.x) &&
				pPos->x >= g_Player2.pos.x + (g_Player2.VtxMinModel.x))
			{// ���ʂ̔���
				pPos->x = pPosold->x;
			}
		}

	}
	return bHit;
}

//=============================================================================
// �v���C���[�̎擾
//=============================================================================
Player2 *GetPlayer2(void)
{
	return &g_Player2;
}
