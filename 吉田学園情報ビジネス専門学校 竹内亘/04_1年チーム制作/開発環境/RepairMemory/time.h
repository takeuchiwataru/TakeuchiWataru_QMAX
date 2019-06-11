//=============================================================================
//
// �w�i���� [time.h]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"

//=============================================================================
// ���Ԃ̏��
//=============================================================================
typedef enum
{
	TIMESTATE_NONE = 0,
	TIMESTATE_STOP,
	TIMESTATE_END,
	TIMESTATE_NORMAL,
	TIMESTATE_START,
	TIMESTATE_ADD,
	TIMESTATE_RESET,
	TIMESTATE_MAX
}TIME;

//=============================================================================
// ���Ԃ̍\���̂̒�`
//=============================================================================
typedef struct
{
	int		nTime;		// ��������
	TIME	TimeState;	// ��Ԑݒ�
}Time;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);

void CntDownTime(void);
Time *GetTime(void);
void SetTimeState(TIME state);
#endif