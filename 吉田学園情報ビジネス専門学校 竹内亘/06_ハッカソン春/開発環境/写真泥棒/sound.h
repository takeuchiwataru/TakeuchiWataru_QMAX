//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*************************************
// �T�E���h�t�@�C��
//*************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,
	SOUND_LABEL_BGM001,
	SOUND_LABEL_BGM002,
	SOUND_LABEL_BGM003,
	SOUND_LABEL_BGM004,
	SOUND_LABEL_SE_DECIDE,
	SOUND_LABEL_SE_SELECT,
	SOUND_LABEL_SE_DASH,
	SOUND_LABEL_SE_JUMP,
	SOUND_LABEL_SE_SHUTTER,
	SOUND_LABEL_SE_GROUND,
	SOUND_LABEL_MAX
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
