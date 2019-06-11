//=============================================================================
//
// �i���o�[���� [number.h]
// Author : �|���j
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"
//#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUMBER_SIZE (20.0f)
#define RANKINGNUMBER_SIZE (50.0f)
#define SCORE_TEXTURE "data/TEXTURE/number003.png"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CNumber
{
public:
	CNumber();
	~CNumber();
	HRESULT Init(D3DXVECTOR3 pos);
	HRESULT InitRanking(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);

	// �ÓI�����o�֐�
	static CNumber * Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;			// �ʒu
};
#endif