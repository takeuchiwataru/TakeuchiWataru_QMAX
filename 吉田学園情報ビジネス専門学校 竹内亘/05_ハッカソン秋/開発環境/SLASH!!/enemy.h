//=============================================================================
//
// �G���� [enemy.h]
// Author :Mikiya Meguro
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_ENEMY	(128)	// �G�̍ő吔
#define	ENEMY_DATA	(3)	// �G�̐�
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	//�ʏ���
	ENEMYSTATE_DAMAGE,		//�_���[�W���
	ENEMYSTATE_MAX			//��Ԃ̑���
}ENEMYSTATE;				//�񋓌^

typedef struct
{
		D3DXVECTOR3	pos;			//�ʒu
		D3DXVECTOR3	move;			//�ʒu
		int			nType;			//���
		ENEMYSTATE	state;			//�G�̏��
		int			nCounterState;	//��ԊǗ��̃J�E���^�[
		int			nCounterAnim;	//�A�j���[�V�����J�E���^�[
		int			nPatternAnim;	//�A�j���[�V�����p�^�[��No��������
		bool		bUse;			//�g�p���Ă��邩	
		int			nLife;			//�̗�
		int			nCntWall;		//�ǂɓ��������Ƃ��ɃJ�E���g
		int			nCunterStop;	//�J�E���^�[�����ȏ�ɂȂ�����X�g�b�v
		int			nRandomCnt;		//�����_���ŕς��
		int			nRandomMove;	//�����_���ŕς��ړ���
		float		fMoveEnemyX = 5.0f;
		float		fMoveEnemyY = 1.0f;
		D3DXCOLOR col;				//�J���[
}Enemy;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType);
Enemy *GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);

#endif
