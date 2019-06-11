//=============================================================================
//
// �f�o�b�O�v���V�[�W������ [debugproc.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#include "main.h"
//#include "varargs.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_CHAR	(20480)
//*********************************************************************
//���C�g�N���X�̒�`
//*********************************************************************
class CDebugProc //��{�N���X
{
public:
	CDebugProc();
	~CDebugProc();
	void Init(void);
	void Uninit(void);
	void Update(void);
	static void Print(int Num, char *fmt, ...);
	static void Draw(void);
	//�����o�ϐ�
private:
	static LPD3DXFONT	m_pFont;			// �t�H���g�ւ̃|�C���^
	static char			m_aStr[MAX_CHAR];
};

#endif
