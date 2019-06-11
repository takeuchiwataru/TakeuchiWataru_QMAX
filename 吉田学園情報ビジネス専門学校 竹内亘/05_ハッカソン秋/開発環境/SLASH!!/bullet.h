//=============================================================================
//
// �e���� [bullet.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_BULLET				(2560)									//�e�̍ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	BULLETTYPE_PLAYER = 0,	//�v���C���[���
	BULLETTYPE_ENEMY,		//�G�l�~�[���
	BULLETTYPE_BOSS,		//�{�X���
	BULLETTYPE_MAX			//��Ԃ̑���
}BULLETTYPE;				//�񋓌^

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	BULLETTYPE type;	//�e�̎��
	int nLife;			//����
	bool bUse;			//�g�p���Ă��邩�ǂ���
	D3DXCOLOR col;		//�J���[
}Bullet;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type);
Bullet *GetBullet(void);
#endif