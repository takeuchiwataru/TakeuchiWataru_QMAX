//=============================================================================
//
// �����_�����O���� [renderer.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"
#include "debugproc.h"

//*********************************************************************
//�����_�����O�N���X�̒�`
//*********************************************************************
class CRenderer //��{�N���X
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void);

#ifdef _DEBUG
	void DrawFPS(void);
#endif
	//�����o�ϐ�
	LPDIRECT3D9				m_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)

#ifdef _DEBUG
	LPD3DXFONT				m_pFont = NULL;			// �t�H���g�ւ̃|�C���^
#endif
};

#endif