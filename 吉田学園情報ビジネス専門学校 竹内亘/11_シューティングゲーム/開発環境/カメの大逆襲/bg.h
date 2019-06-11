//=============================================================================
//
// �w�i���� [bg.h]
// Author : �|���j
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_TEXTURE_000	"data/TEXTURE/bg001.png"
#define BG_TEXTURE_001	"data/TEXTURE/bg002.png"
#define BG_TEXTURE_002	"data/TEXTURE/bg000.png"
#define MAX_BG_TEXTURE (3)			// �w�i�̃e�N�X�`���̐�
#define MAX_BG (3)					// �w�i�̍ő吔
#define BG_POS_X			(0)		// �w�iX���W
#define BG_POS_Y			(0)		// �w�iY���W
#define BG_POS_X000		(250)		// �Q�[�����̔w�iX���W1
#define BG_POS_X001		(950)		// �Q�[�����̔w�iX���W2
#define BG_WIDTH (SCREEN_WIDTH)		// �w�i�̕�
#define BG_HEIGHT (SCREEN_HEIGHT)	// �w�i�̍���
#define BG_MOVESPEED_000 (0.0005f)	// �w�i1�̃X���C�h�X�s�[�h
#define BG_MOVESPEED_100 (0.0003f)	// �w�i2�̃X���C�h�X�s�[�h
#define BG_MOVESPEED_200 (0.0008f)	// �w�i3�̃X���C�h�X�s�[�h

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CBg : public CScene
{
public:
	CBg();
	~CBg();
	HRESULT Init(D3DXVECTOR3 pos);
	HRESULT InitGame(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CBg * Create(D3DXVECTOR3 pos);
	static CBg * Create2(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG_TEXTURE];	// ���L�e�N�X�`���̃|�C���^
	CScene2D * m_apScene2D[MAX_BG];
	D3DXVECTOR3				m_move;			// �ړ���
	int m_slideSpeed;						// �X���C�h�X�s�[�h
};
#endif