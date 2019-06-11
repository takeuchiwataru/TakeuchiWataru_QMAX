//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "Effect.h"
#include "Scene3D.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �ݒ菈��
//=============================================================================
void	CLineEffect::Set(float *fPosX, float *fPosY, float *fPosZ, D3DXVECTOR3 pos,
	D3DXVECTOR3 *rot, float fDistance, float fInterval, int nLife, bool *bDelete)
{
	if (fPosX == NULL || fPosY == NULL || fPosZ == NULL) { Uninit(); return; }
	m_pPos[0] = fPosX; m_pPos[1] = fPosY; m_pPos[2] = fPosZ;
	m_posold = pos;
	m_rot = rot;
	m_fDistance = fDistance;
	m_fInterval = fInterval;
	m_nLife = nLife;
	m_bDelete = bDelete;
	SetEffect();
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CLineEffect::Init(void)
{
	m_fDistance = 0.0f;
	m_fInterval = 1.0f;
	m_fLength = 0.0f;

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CLineEffect::Update(void)
{
	//if (m_bDelete != NULL) { Uninit(); return; }
	//else
	{//�܂������鎞�łȂ�
		m_nLife--;
		if (m_nLife <= 0)
		{//������0
			EndEffect();
			Uninit(); return;
		}
		MoveSet(ChangePos());
	}
	//m_posold = D3DXVECTOR3(m_pPos[0][0], m_pPos[1][0], m_pPos[2][0]);
}
//=============================================================================
// �ʒu�v�Z����
//=============================================================================
D3DXVECTOR3	CLineEffect::ChangePos(void)
{
	for (int nCount = 0; nCount < 3; nCount++)
	{
		if (m_pPos[nCount] == NULL)
		{//�ǂꂩ��ł������Ă��Ȃ��Ȃ�
			return m_posold;
		}
	}

	//�|�C���^�ɒl�������Ă���Ȃ�
	//rot���g���Čv�Z


	return D3DXVECTOR3(m_pPos[0][0], m_pPos[1][0], m_pPos[2][0]);
}
//=============================================================================
// �ړ��ʂɂ���ăZ�b�g����
//=============================================================================
void CLineEffect::MoveSet(D3DXVECTOR3 &pos)
{
	D3DXVECTOR3 posold = m_posold;
	float fLengthX, fLengthZ, fLengthY;
	int	  nCount;

	fLengthX = pos.x - m_posold.x; fLengthX *= fLengthX;
	fLengthY = pos.y - m_posold.y; fLengthY *= fLengthY;
	fLengthZ = pos.z - m_posold.z; fLengthZ *= fLengthZ;

	m_fLength += sqrtf(fLengthX + fLengthY + fLengthZ);	//Move�ʌv�Z
	nCount = (int)(m_fLength / m_fInterval);
	m_fLength = (float)((int)(m_fLength * 100.0f) % (int)(m_fInterval * 100.0f)) * 0.01f;
	for (int nCnt = 0; nCnt < nCount; nCnt++)
	{//��������������葱����
		m_posold += D3DXVECTOR3(pos.x - posold.x, pos.y - posold.y, pos.z - posold.z) / (float)nCount;
		SetEffect();
	}
}
//=============================================================================
// �^�C�v���Ƃ̃G�t�F�N�g�Z�b�g����
//=============================================================================
void CLineEffect::SetEffect()
{
	CScene3D *p3D;

	if (SceneCreate(p3D, 3))
	{
		p3D->Set(m_posold, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			D3DXVECTOR3(1.0f, 0.0f, 1.0f), CScene::TEX_MAX, 0, 1, 1, true, CScene::DRAW_TYPE_NORMAL);
		p3D->GetState() = CScene3D::STATE_FADEOUT;
		p3D->GetfCntState() = 0.05f;
	}
}
//=============================================================================
// �J�n���^�C�v���Ƃ̃G�t�F�N�g�Z�b�g����
//=============================================================================
void StartEffect(void)
{

}
//=============================================================================
// �I�����^�C�v���Ƃ̃G�t�F�N�g�Z�b�g����
//=============================================================================
void CLineEffect::EndEffect(void)
{

}
