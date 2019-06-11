//=============================================================================
//
// �I�u�W�F�N�g2D���� [scene2D.cpp]
// Author : �|���j
//
//=============================================================================
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(int nPriority):CScene(nPriority)
{
	m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

	m_fAdd = 1.0f;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos)
{
	CManager manager;	// �C���X�^���X

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// �|���S���̈ʒu��ݒ�
	//m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = pos;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_����ݒ�
	VERTEX_2D * pVtx;					// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �ʒu
	pVtx[0].pos = D3DXVECTOR3(m_pos.x -POLIGON_SIZE, m_pos.y -POLIGON_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x +POLIGON_SIZE, m_pos.y -POLIGON_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x -POLIGON_SIZE, m_pos.y +POLIGON_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x +POLIGON_SIZE, m_pos.y +POLIGON_SIZE, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �F
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CScene2D::InitAnim(D3DXVECTOR3 pos)
{
	CManager manager;	// �C���X�^���X

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	m_pos = pos;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_����ݒ�
	VERTEX_2D * pVtx;					// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �ʒu
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - POLIGON_SIZE, m_pos.y - POLIGON_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + POLIGON_SIZE, m_pos.y - POLIGON_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - POLIGON_SIZE, m_pos.y + POLIGON_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + POLIGON_SIZE, m_pos.y + POLIGON_SIZE, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �F
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CScene2D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �I�u�W�F�N�g(�������g)�̔j��
	Release();
}
//=============================================================================
// �X�V����
//=============================================================================
void CScene2D::Update(void)
{
	////if (g_bDelete == false)
	////{// �f�o�b�O�p
	////	Uninit();

	////	bDelete = true;
	////}

	//// �L�[�{�[�h�̎擾
	//CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	//m_rot -= 0.09f;
	//m_fLength += m_fAdd;
	////m_fLength += 0.5f;

	//// ���_����ݒ�
	//VERTEX_2D * pVtx;					// ���_���ւ̃|�C���^

	//// ���_�o�b�t�@�����b�N
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//// ��]
	//if (m_rot > D3DX_PI)
	//{
	//	m_rot -= D3DX_PI * 2.0f;
	//}
	//else if (m_rot < -D3DX_PI)
	//{
	//	m_rot += D3DX_PI * 2.0f;
	//}

	//// �g��Ək��
	//if (m_fLength > 250)
	//{
	//	m_fAdd -= 1.0f;
	//}
	//else if (m_fLength < 0)
	//{
	//	m_fAdd += 1.0f;
	//}

	//pVtx[0].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.75f - m_rot) * m_fLength, m_pos.y + cosf(-D3DX_PI * 0.75f - m_rot) * m_fLength, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.75f - m_rot) * m_fLength, m_pos.y + cosf(D3DX_PI * 0.75f - m_rot) * m_fLength, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(m_pos.x + sinf(-D3DX_PI * 0.25f - m_rot) * m_fLength, m_pos.y + cosf(-D3DX_PI * 0.25f - m_rot) * m_fLength, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(m_pos.x + sinf(D3DX_PI * 0.25f - m_rot) * m_fLength, m_pos.y + cosf(D3DX_PI * 0.25f - m_rot) * m_fLength, 0.0f);

	//// ���_�o�b�t�@���A�����b�N
	//m_pVtxBuff->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void CScene2D::Draw(void)
{
	CManager manager;	//�C���X�^���X

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);
	
	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

////=============================================================================
//// ����
////=============================================================================
//CScene2D * CScene2D::Create(D3DXVECTOR3 pos)
//{
//	CScene2D *pScene2D = NULL;
//
//	if (pScene2D == NULL)
//	{
//		pScene2D = new CScene2D;
//
//		if (pScene2D != NULL)
//		{
//			pScene2D->Init(pos);
//			pScene2D->m_pos = pos;
//		}
//	}
//	return pScene2D;
//}
//=============================================================================
// �ʒu�̐ݒu
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos, float fwidth, float fheight)
{
	m_pos = pos;

	// ���_����ݒ�
	VERTEX_2D * pVtx;					// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fwidth, m_pos.y - fheight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fwidth, m_pos.y - fheight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fwidth, m_pos.y + fheight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fwidth, m_pos.y + fheight, 0.0f);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �ʒu�̎擾
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}
//=============================================================================
// �ړ��̎擾
//=============================================================================
D3DXVECTOR3 CScene2D::GetMove(void)
{
	return m_move;
}
//=============================================================================
// �e�N�X�`���̊��蓖��
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
//=============================================================================
// �����̃A�j���[�V�����ݒu
//=============================================================================
void CScene2D::SetExplosion(int nPatternAnim)
{
	// ���_����ݒ�
	VERTEX_2D * pVtx;					// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.125f * nPatternAnim, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.125f * nPatternAnim + 0.125f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.125f * nPatternAnim, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.125f * nPatternAnim + 0.125f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 2�p�^�[���A�j���[�V�����ݒu
//=============================================================================
void CScene2D::SetPattern2(int nPatternAnim)
{
	// ���_����ݒ�
	VERTEX_2D * pVtx;					// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.5f * nPatternAnim + 0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f * nPatternAnim + 0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.5f * nPatternAnim + 0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.5f * nPatternAnim + 0.5f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �G�t�F�N�g�̐ݒu
//=============================================================================
void CScene2D::SetEffect(float fRadius)
{
	// ���_����ݒ�
	VERTEX_2D * pVtx;					// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fRadius, m_pos.y - fRadius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fRadius, m_pos.y - fRadius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fRadius, m_pos.y + fRadius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fRadius, m_pos.y + fRadius, 0.0f);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �p�[�e�B�N���̐ݒu
//=============================================================================
void CScene2D::SetParticle(int nRadius, D3DXVECTOR3 pos)
{
	D3DXCOLOR Col;

	if (nRadius < 1) nRadius = 1;

	float fRadius = (rand() % nRadius + 1) * 1.0f;
	int nNumber = rand() % 3 + 1;

	if (nNumber == 1) { Col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f); }
	if (nNumber == 2) { Col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f); }
	if (nNumber == 3) { Col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f); }

	m_pos = pos;

	// ���_����ݒ�
	VERTEX_2D * pVtx;					// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fRadius, m_pos.y - fRadius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fRadius, m_pos.y - fRadius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fRadius, m_pos.y + fRadius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fRadius, m_pos.y + fRadius, 0.0f);

	pVtx[0].col = D3DXCOLOR(Col.r, Col.g, Col.b, Col.a);
	pVtx[1].col = D3DXCOLOR(Col.r, Col.g, Col.b, Col.a);
	pVtx[2].col = D3DXCOLOR(Col.r, Col.g, Col.b, Col.a);
	pVtx[3].col = D3DXCOLOR(Col.r, Col.g, Col.b, Col.a);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �J���[�̐ݒu
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR col)
{
	m_col = col;

	// ���_����ݒ�
	VERTEX_2D * pVtx;					// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
//=============================================================================
// ���_�o�b�t�@�̎擾
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 CScene2D::GetVtxBuff(void)
{
	return m_pVtxBuff;
}