//=============================================================================
//
// �|���S������ [flontpolygon.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "flontpolygon.h"
#include "xobject.h"
#include "time.h"
#include "main.h"
#include "input.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_FLONTPOLYGON	(64)			//�ǂ݂��ރe�N�X�`���̍ő吔
#define TITLEANIM_UV_U		(0.1f)
#define TITLEANIM_UV_V		(0.08333f)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureFlontPolygon[FLONTPOLYGONTEXTURE_MAX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFlontPolygon = NULL;			//���_�o�b�t�@�ւ̃|�C���^
FlontPolygon			g_FlontPolygon[MAX_FLONTPOLYGON];		//���ݒ�
int						g_nMaxFlontPolygon;
int						g_nPointerIdx;
bool					g_bDeletePartsTexture;

//=============================================================================
// �X�^�[�g�{�^������������
//=============================================================================
void InitFlontPolygon(void)
{
	//�ϐ��錾
//	int		nCntTex;
	int     nCntFlontPolygon;

	g_nPointerIdx = 99;
	g_bDeletePartsTexture = false;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��̏�����
	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_FLONTPOLYGON; nCntFlontPolygon++)
	{
		g_FlontPolygon[nCntFlontPolygon].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���S���W
		g_FlontPolygon[nCntFlontPolygon].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F
		g_FlontPolygon[nCntFlontPolygon].fHeight = 0.0f;								//����
		g_FlontPolygon[nCntFlontPolygon].fWidth = 0.0f;								//��
		g_FlontPolygon[nCntFlontPolygon].nCntAnim = 0;								//�A�j���[�V�����J�E���g
		g_FlontPolygon[nCntFlontPolygon].nCntPattrn= 0;								//�A�j���[�V�����p�^�[��
		g_FlontPolygon[nCntFlontPolygon].nTexNum = 0;								//�e�N�X�`���̔ԍ�
		g_FlontPolygon[nCntFlontPolygon].nCntPolygon = 0;							//�g�p�ԍ�
		g_FlontPolygon[nCntFlontPolygon].bUse = false;								//�g�p���Ă��Ȃ���Ԃɂ���
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\game_over.png",	&g_pTextureFlontPolygon[0]);	//�Q�[���I�[�o�[���S
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\UI2.png",		&g_pTextureFlontPolygon[1]);	//�t�H���g�w�i
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\player3.png",	&g_pTextureFlontPolygon[2]);	//��l����摜
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy02.png",	&g_pTextureFlontPolygon[3]);	//��摜
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy04.png",	&g_pTextureFlontPolygon[4]);	//��摜
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy03.png",	&g_pTextureFlontPolygon[5]);	//��摜
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item000.png",	&g_pTextureFlontPolygon[6]);	//���ԂP
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item002.png",	&g_pTextureFlontPolygon[7]);	//���ԂQ
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item002.png",	&g_pTextureFlontPolygon[8]);	//���ԂR
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item003.png",	&g_pTextureFlontPolygon[9]);	//���ԂS
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\watch00.png",	&g_pTextureFlontPolygon[10]);	//���v�P�i�g�j
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\watch02.png",	&g_pTextureFlontPolygon[11]);	//���v�Q�i�`�F�[���j
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\watch02.png",	&g_pTextureFlontPolygon[12]);	//���v�R�i��M�j
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\orugoru00.png",	&g_pTextureFlontPolygon[13]);	//�I���S�[���P
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\orugoru01.png",	&g_pTextureFlontPolygon[14]);	//�I���S�[���Q
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\orugoru02.png",	&g_pTextureFlontPolygon[15]);	//�I���S�[���R�i�ؔ��j
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\sen.png",		&g_pTextureFlontPolygon[16]);	//�����̐�

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\paper.png", &g_pTextureFlontPolygon[17]);		//���j���[�g
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item000.png", &g_pTextureFlontPolygon[18]);		//���i
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item001.png", &g_pTextureFlontPolygon[19]);		//���i
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item002.png", &g_pTextureFlontPolygon[20]);		//���i
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item003.png", &g_pTextureFlontPolygon[21]);		//���i
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item000.png", &g_pTextureFlontPolygon[22]);		//���i
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item001.png", &g_pTextureFlontPolygon[23]);		//���i
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item002.png", &g_pTextureFlontPolygon[24]);		//���i
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item003.png", &g_pTextureFlontPolygon[25]);		//���i
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\zenmai000.png", &g_pTextureFlontPolygon[26]);	//���i
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\orugoru001.png", &g_pTextureFlontPolygon[27]);	//���i
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\orugoru000.png", &g_pTextureFlontPolygon[28]);	//���i
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\parts000.png", &g_pTextureFlontPolygon[29]);		//���i�傫��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\parts001.png", &g_pTextureFlontPolygon[30]);		//���i�傫��

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\pazzlein.png", &g_pTextureFlontPolygon[31]);		//����
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\pazzlestart.png", &g_pTextureFlontPolygon[32]);	//����
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\pazzleend.png", &g_pTextureFlontPolygon[33]);	//����

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\stamp_A.png", &g_pTextureFlontPolygon[34]);		//�X�^���vA
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\stamp_B.png", &g_pTextureFlontPolygon[35]);		//�X�^���vB
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\stamp_C.png", &g_pTextureFlontPolygon[36]);		//�X�^���vC
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\stamp_D.png", &g_pTextureFlontPolygon[37]);		//�X�^���vD

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\parts_Oclock.jpg", &g_pTextureFlontPolygon[38]);		//�T���p�[�cQ1
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\parts_MusicBox.jpg", &g_pTextureFlontPolygon[39]);	//�T���p�[�cQ2
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\parts_doll.jpg", &g_pTextureFlontPolygon[40]);		//�T���p�[�cQ3

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\pointer.png", &g_pTextureFlontPolygon[41]);		//�|�C���^�[

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\rank_A.png", &g_pTextureFlontPolygon[42]);		//�����NA
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\rank_B.png", &g_pTextureFlontPolygon[43]);		//�����NB
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\rank_C.png", &g_pTextureFlontPolygon[44]);		//�����NC
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\rank_D.png", &g_pTextureFlontPolygon[45]);		//�����ND

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\result000.png", &g_pTextureFlontPolygon[46]);		//

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial000.png", &g_pTextureFlontPolygon[47]);		//
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial001.png", &g_pTextureFlontPolygon[48]);		//
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial002.png", &g_pTextureFlontPolygon[49]);		//

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FLONTPOLYGON,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffFlontPolygon,
								NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFlontPolygon->Lock(0, 0, (void**)&pVtx, 0);
	
	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_FLONTPOLYGON; nCntFlontPolygon++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(250.0f, 100.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(750.0f, 100.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(250.0f, 200.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(750.0f, 200.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFlontPolygon->Unlock();
}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitFlontPolygon(void)
{
	//�ϐ��錾
	int nCntTex;

	//�e�N�X�`���̔j��
	for (nCntTex = 0; nCntTex < FLONTPOLYGONTEXTURE_MAX; nCntTex++)
	{
		if (g_pTextureFlontPolygon[nCntTex] != NULL)
		{
			g_pTextureFlontPolygon[nCntTex]->Release();
			g_pTextureFlontPolygon[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffFlontPolygon != NULL)
	{
		g_pVtxBuffFlontPolygon->Release();
		g_pVtxBuffFlontPolygon = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateFlontPolygon(void)
{
	//�ϐ��錾
	int nCntFlontPolygon;

	MODE mode = GetMode();

	PAZZLENUM PazzleNum = *GetPazzleNum();
	bool bChangeMoveObj = false;
	DIMOUSESTATE2 pMouse = GetMousePointer();
	//POINT po;
	DIJOYSTATE pStick = GetStick();

	Time *pTime = GetTime();

	int nPazzle = 0;

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFlontPolygon->Lock(0, 0, (void**)&pVtx, 0);
	
	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_FLONTPOLYGON; nCntFlontPolygon++)
	{
		if (g_FlontPolygon[nCntFlontPolygon].bUse == true)
		{
			if (g_FlontPolygon[nCntFlontPolygon].nTexNum >= FLONTPOLYGONTEXTURE_MENU_1 &&
				g_FlontPolygon[nCntFlontPolygon].nTexNum <= FLONTPOLYGONTEXTURE_MENU_MB2)
			{
				if (PazzleNum.modelNum[nPazzle] > 0)
				{
					if (/*GetMouseTrigger(0) == true && */ (GetKeyboardTrigger(DIK_LSHIFT) == true || GetKeyboardTrigger(DIK_RSHIFT) == true || GetButtonTrigger(0) == true) && bChangeMoveObj == false && g_FlontPolygon[g_nPointerIdx].bUse == true &&
						g_FlontPolygon[nCntFlontPolygon].pos.x - (g_FlontPolygon[nCntFlontPolygon].fWidth / 2) < g_FlontPolygon[g_nPointerIdx].pos.x && g_FlontPolygon[nCntFlontPolygon].pos.x + (g_FlontPolygon[nCntFlontPolygon].fWidth / 2) > g_FlontPolygon[g_nPointerIdx].pos.x &&
						g_FlontPolygon[nCntFlontPolygon].pos.y - (g_FlontPolygon[nCntFlontPolygon].fHeight / 2) < g_FlontPolygon[g_nPointerIdx].pos.y && g_FlontPolygon[nCntFlontPolygon].pos.y + (g_FlontPolygon[nCntFlontPolygon].fHeight / 2) > g_FlontPolygon[g_nPointerIdx].pos.y)
					{
						SetMovePazzelObj(nPazzle);
						bChangeMoveObj = true;
					}
				}
				else
				{
					g_FlontPolygon[nCntFlontPolygon].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				}
	
				nPazzle++;
			}
			else if (g_FlontPolygon[nCntFlontPolygon].nTexNum >= FLONTPOLYGONTEXTURE_PAZZLE_IN &&
				g_FlontPolygon[nCntFlontPolygon].nTexNum <= FLONTPOLYGONTEXTURE_PAZZLE_END)
			{
				g_FlontPolygon[nCntFlontPolygon].pos.x -= 9.0f;

				if (g_FlontPolygon[nCntFlontPolygon].pos.x < -SCREEN_WIDTH)
				{
					DeleteFlontPolygon(nCntFlontPolygon);
				}
				if (g_FlontPolygon[nCntFlontPolygon].pos.x <= SCREEN_WIDTH / 4 && g_FlontPolygon[nCntFlontPolygon].nTexNum == FLONTPOLYGONTEXTURE_PAZZLE_START)
				{
					SetTimeState(TIMESTATE_NORMAL);
				}
			}
			else if (g_FlontPolygon[nCntFlontPolygon].nTexNum >= FLONTPOLYGONTEXTURE_QUESTSTAMP_A &&
				g_FlontPolygon[nCntFlontPolygon].nTexNum <= FLONTPOLYGONTEXTURE_QUESTSTAMP_D)
			{
				if (mode == MODE_GAMECLEAR)
				{
					if (g_FlontPolygon[nCntFlontPolygon].fWidth <= 300 &&
						g_FlontPolygon[nCntFlontPolygon].fHeight <= 300)
					{
						g_FlontPolygon[nCntFlontPolygon].fWidth = 300;
						g_FlontPolygon[nCntFlontPolygon].fHeight = 300;

					}
					else
					{
						g_FlontPolygon[nCntFlontPolygon].fWidth -= 300 / 4;
						g_FlontPolygon[nCntFlontPolygon].fHeight -= 300 / 4;
					}
				}
				else
				{
					if (g_FlontPolygon[nCntFlontPolygon].fWidth <= 500 &&
						g_FlontPolygon[nCntFlontPolygon].fHeight <= 500)
					{
						g_FlontPolygon[nCntFlontPolygon].fWidth = 500;
						g_FlontPolygon[nCntFlontPolygon].fHeight = 500;

					}
					else
					{
						g_FlontPolygon[nCntFlontPolygon].fWidth -= 500 / 4;
						g_FlontPolygon[nCntFlontPolygon].fHeight -= 500 / 4;
					}
				}
			}
			else if (g_FlontPolygon[nCntFlontPolygon].nTexNum == FLONTPOLYGONTEXTURE_QUESTCLEAR)
			{
				if (g_FlontPolygon[nCntFlontPolygon].col.a < 0.5f)
				{
					g_FlontPolygon[nCntFlontPolygon].col.a += 0.015f;
				}
				else
				{
					g_FlontPolygon[nCntFlontPolygon].col.a = 0.5f;
				}
			}
			else if (g_FlontPolygon[nCntFlontPolygon].nTexNum >= FLONTPOLYGONTEXTURE_PARTS_WIN_CLOCK &&
				g_FlontPolygon[nCntFlontPolygon].nTexNum <= FLONTPOLYGONTEXTURE_PARTS_WIN_DOLL)
			{
				if (g_FlontPolygon[nCntFlontPolygon].fWidth >= 900 &&
					g_FlontPolygon[nCntFlontPolygon].fHeight >= 600)
				{
					g_FlontPolygon[nCntFlontPolygon].fWidth = 900;
					g_FlontPolygon[nCntFlontPolygon].fHeight = 600;

					if (GetKeyboardTrigger(DIK_RETURN) == true || GetButtonTrigger(2) == true)
					{
						DeleteFlontPolygon(nCntFlontPolygon);
					}
				}
				else
				{
					g_FlontPolygon[nCntFlontPolygon].fWidth += 900 / 12;
					g_FlontPolygon[nCntFlontPolygon].fHeight += 600 / 12;
				}
			}
			else if (g_FlontPolygon[nCntFlontPolygon].nTexNum == FLONTPOLYGONTEXTURE_POINTER)
			{
				if (pTime->TimeState == TIMESTATE_NORMAL)
				{
					if (GetKeyboardPress(DIK_UP) == true || pStick.rgdwPOV[0] == 0 || pStick.rgdwPOV[0] == 4500 || pStick.rgdwPOV[0] == 31500 || pStick.lY < -300)
					{
						g_FlontPolygon[nCntFlontPolygon].pos.y -= 6.0f;
					}
					if (GetKeyboardPress(DIK_DOWN) == true || pStick.rgdwPOV[0] == 18000 || pStick.rgdwPOV[0] == 22500 || pStick.rgdwPOV[0] == 13500 || pStick.lY > 300)
					{
						g_FlontPolygon[nCntFlontPolygon].pos.y += 6.0f;
					}
					if (GetKeyboardPress(DIK_LEFT) == true || pStick.rgdwPOV[0] == 27000 || pStick.rgdwPOV[0] == 31500 || pStick.rgdwPOV[0] == 22500 || pStick.lX < -300)
					{
						g_FlontPolygon[nCntFlontPolygon].pos.x -= 6.0f;
					}
					if (GetKeyboardPress(DIK_RIGHT) == true || pStick.rgdwPOV[0] == 9000 || pStick.rgdwPOV[0] == 13500 || pStick.rgdwPOV[0] == 4500 || pStick.lX > 300)
					{
						g_FlontPolygon[nCntFlontPolygon].pos.x += 6.0f;
					}
					{
						/*if (g_FlontPolygon[nCntFlontPolygon].pos.x < 50.0f)
						{
							g_FlontPolygon[nCntFlontPolygon].pos.x = 50.0f;
						}*/

						if (g_FlontPolygon[nCntFlontPolygon].pos.x < (SCREEN_WIDTH - 240) + 50.0f)
						{
							g_FlontPolygon[nCntFlontPolygon].pos.x = (SCREEN_WIDTH - 240) + 50.0f;
						}

						if (g_FlontPolygon[nCntFlontPolygon].pos.x > SCREEN_WIDTH - 50.0f)
						{
							g_FlontPolygon[nCntFlontPolygon].pos.x = SCREEN_WIDTH - 50.0f;
						}

						/*if (g_FlontPolygon[nCntFlontPolygon].pos.y < 50.0f)
						{
							g_FlontPolygon[nCntFlontPolygon].pos.y = 50.0f;
						}*/

						if (g_FlontPolygon[nCntFlontPolygon].pos.y < 200.0f)
						{
							g_FlontPolygon[nCntFlontPolygon].pos.y = 200.0f;
						}

						if (g_FlontPolygon[nCntFlontPolygon].pos.y > SCREEN_HEIGHT - 50.0f)
						{
							g_FlontPolygon[nCntFlontPolygon].pos.y = SCREEN_HEIGHT - 50.0f;
						}
					}
				}
			}
			else if (g_FlontPolygon[nCntFlontPolygon].nTexNum >= FLONTPOLYGONTEXTURE_CLEAR_RANK_A &&
				g_FlontPolygon[nCntFlontPolygon].nTexNum <= FLONTPOLYGONTEXTURE_CLEAR_RANK_D)
			{
				if (g_FlontPolygon[nCntFlontPolygon].fWidth <= 1000 &&
					g_FlontPolygon[nCntFlontPolygon].fHeight <= 400)
				{
					g_FlontPolygon[nCntFlontPolygon].fWidth = 1000;
					g_FlontPolygon[nCntFlontPolygon].fHeight = 400;

				}
				else
				{
					g_FlontPolygon[nCntFlontPolygon].fWidth -= 1000 / 4;
					g_FlontPolygon[nCntFlontPolygon].fHeight -= 400 / 4;
				}
			}

			//���_���W�̐ݒ�
			pVtx[nCntFlontPolygon * 4].pos = D3DXVECTOR3(g_FlontPolygon[nCntFlontPolygon].pos.x - (g_FlontPolygon[nCntFlontPolygon].fWidth / 2), g_FlontPolygon[nCntFlontPolygon].pos.y - (g_FlontPolygon[nCntFlontPolygon].fHeight / 2), 0.0f);
			pVtx[nCntFlontPolygon * 4 + 1].pos = D3DXVECTOR3(g_FlontPolygon[nCntFlontPolygon].pos.x + (g_FlontPolygon[nCntFlontPolygon].fWidth / 2), g_FlontPolygon[nCntFlontPolygon].pos.y - (g_FlontPolygon[nCntFlontPolygon].fHeight / 2), 0.0f);
			pVtx[nCntFlontPolygon * 4 + 2].pos = D3DXVECTOR3(g_FlontPolygon[nCntFlontPolygon].pos.x - (g_FlontPolygon[nCntFlontPolygon].fWidth / 2), g_FlontPolygon[nCntFlontPolygon].pos.y + (g_FlontPolygon[nCntFlontPolygon].fHeight / 2), 0.0f);
			pVtx[nCntFlontPolygon * 4 + 3].pos = D3DXVECTOR3(g_FlontPolygon[nCntFlontPolygon].pos.x + (g_FlontPolygon[nCntFlontPolygon].fWidth / 2), g_FlontPolygon[nCntFlontPolygon].pos.y + (g_FlontPolygon[nCntFlontPolygon].fHeight / 2), 0.0f);
			//���_�J���[�̐ݒ�
			pVtx[nCntFlontPolygon * 4].col = g_FlontPolygon[nCntFlontPolygon].col;
			pVtx[nCntFlontPolygon * 4 + 1].col = g_FlontPolygon[nCntFlontPolygon].col;
			pVtx[nCntFlontPolygon * 4 + 2].col = g_FlontPolygon[nCntFlontPolygon].col;
			pVtx[nCntFlontPolygon * 4 + 3].col = g_FlontPolygon[nCntFlontPolygon].col;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFlontPolygon->Unlock();
}

//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawFlontPolygon(void)
{
	//�ϐ��錾
	int nCntFlontPolygon;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFlontPolygon, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_FLONTPOLYGON; nCntFlontPolygon++)
	{
		if (g_FlontPolygon[nCntFlontPolygon].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			if (g_FlontPolygon[nCntFlontPolygon].nTexNum < FLONTPOLYGONTEXTURE_MAX)
			{
				pDevice->SetTexture(0, g_pTextureFlontPolygon[g_FlontPolygon[nCntFlontPolygon].nTexNum]);
			}
			else
			{
				pDevice->SetTexture(0, NULL);
			}

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
								   nCntFlontPolygon * 4,	//�J�n���钸�_�̃C���f�b�N�X
								   2);						//�v���~�e�B�u�̐�
		}
	}
}

//=============================================================================
// ���ݒ�
//=============================================================================
int SetFlontPolygon(int nTexNum, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight)
{
	//�ϐ��錾
	int nCntFlontPolygon;
	int nNumIndx = 0;
	float fHalfWidth = 0;		//��
	float fHalfHight = 0;		//����

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFlontPolygon->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_FLONTPOLYGON; nCntFlontPolygon++)
	{
		if (g_FlontPolygon[nCntFlontPolygon].bUse == false)
		{
			g_FlontPolygon[nCntFlontPolygon].pos = pos;				//���S���W
			g_FlontPolygon[nCntFlontPolygon].fHeight = fHeight;		//����
			g_FlontPolygon[nCntFlontPolygon].fWidth = fWidth;		//��
			g_FlontPolygon[nCntFlontPolygon].col = col;				//�F
			g_FlontPolygon[nCntFlontPolygon].nCntAnim = 0;			//�A�j���[�V�����J�E���g
			g_FlontPolygon[nCntFlontPolygon].nCntPattrn = 0;		//�A�j���[�V�����p�^�[��

			//���ƍ�����ݒ肷��
			fHalfWidth = g_FlontPolygon[nCntFlontPolygon].fWidth * 0.5f;
			fHalfHight = g_FlontPolygon[nCntFlontPolygon].fHeight * 0.5f;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(pos.x - fHalfWidth, pos.y - fHalfHight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pos.x + fHalfWidth, pos.y - fHalfHight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pos.x - fHalfWidth, pos.y + fHalfHight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pos.x + fHalfWidth, pos.y + fHalfHight, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
		
			g_FlontPolygon[nCntFlontPolygon].nTexNum = nTexNum;		//�e�N�X�`���̔ԍ�

			if (g_FlontPolygon[nCntFlontPolygon].nTexNum == FLONTPOLYGONTEXTURE_PARTS_WIN_CLOCK ||
				g_FlontPolygon[nCntFlontPolygon].nTexNum == FLONTPOLYGONTEXTURE_PARTS_WIN_MUSICBOX ||
				g_FlontPolygon[nCntFlontPolygon].nTexNum == FLONTPOLYGONTEXTURE_PARTS_WIN_DOLL)
			{
				g_bDeletePartsTexture = true;
			}

			if (g_FlontPolygon[nCntFlontPolygon].nTexNum == FLONTPOLYGONTEXTURE_POINTER)
			{
				g_nPointerIdx = nCntFlontPolygon;
			}

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			
			g_FlontPolygon[nCntFlontPolygon].bUse = true;			//�g�p���Ă����Ԃɂ���
			nNumIndx = nCntFlontPolygon;
			break;
		}

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFlontPolygon->Unlock();

	return nNumIndx;
}

//=============================================================================
// �|���S�������ׂď���
//=============================================================================
void DeleteAllFlontPolygon(void)
{
	//�ϐ��錾
	int nCntFlontPolygon;

	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_FLONTPOLYGON; nCntFlontPolygon++)
	{
		if (g_FlontPolygon[nCntFlontPolygon].bUse == true)
		{
			g_FlontPolygon[nCntFlontPolygon].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���

			if (g_FlontPolygon[nCntFlontPolygon].nTexNum == FLONTPOLYGONTEXTURE_POINTER)
			{
				g_nPointerIdx = 99;
			}
		}
	}

	g_bDeletePartsTexture = false;
}

//=============================================================================
// ����̃|���S��������
//=============================================================================
void DeleteFlontPolygon(int nIndx)
{
	if (g_FlontPolygon[nIndx].bUse == true)
	{
		if (g_FlontPolygon[nIndx].nTexNum == FLONTPOLYGONTEXTURE_PARTS_WIN_CLOCK ||
			g_FlontPolygon[nIndx].nTexNum == FLONTPOLYGONTEXTURE_PARTS_WIN_MUSICBOX ||
			g_FlontPolygon[nIndx].nTexNum == FLONTPOLYGONTEXTURE_PARTS_WIN_DOLL)
		{
			g_bDeletePartsTexture = false;
		}

		if (g_FlontPolygon[nIndx].nTexNum == FLONTPOLYGONTEXTURE_POINTER)
		{
			g_nPointerIdx = 99;
		}

		g_FlontPolygon[nIndx].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
	}
}
void DeleteFlontPolygonA(int nTexNum)
{
	int nCntFlontPolygon;

	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_FLONTPOLYGON; nCntFlontPolygon++)
	{
		if (g_FlontPolygon[nCntFlontPolygon].bUse == true && g_FlontPolygon[nCntFlontPolygon].nTexNum == nTexNum)
		{
			g_FlontPolygon[nCntFlontPolygon].bUse = false;
			break;
		}
	}
}

//=============================================================================
// �����擾
//=============================================================================
FlontPolygon * GetFlontPolygon(void)
{
	return &g_FlontPolygon[0];
}

//=============================================================================
// �����擾
//=============================================================================
bool DeletePartsTexture(void)
{
	return g_bDeletePartsTexture;
}