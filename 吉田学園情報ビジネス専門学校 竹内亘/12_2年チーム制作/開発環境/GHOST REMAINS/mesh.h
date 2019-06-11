//=============================================================================
//
// ���b�V������ [mesh.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _MESH_H_
#define _MESH_H_

#include "main.h"
#include "scene.h"
#include "motion.h"
//*****************************************************************************
// �}�N���̒�`
//*****************************************************************************
#define WALL_PLUS					(2.0f)		//�ǂ̔���̃v���X�l
#define MESH_PRIORITY				(0)			//���b�V���̗D�揇��

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CMesh : public CScene
{
public:
	typedef enum
	{
		TYPE_FIELD,		//�n��
		TYPE_WALL,		//��
		TYPE_CEILING,	//�V��
		TYPE_MAX
	}TYPE;
	CMesh(int nPrioryity = 0) : CScene::CScene(nPrioryity) {};
	~CMesh() {};

	void	Set(TYPE type, D3DXVECTOR3 pos, int nVertical, int nCorss, bool bMesh);	//�Z�b�g����
	void	SetNor(void);	//�@���̃Z�b�g����

	void	SetWall(D3DXVECTOR3 *vtx);							//�ǃZ�b�g����
	bool	SetField(int *nDig, int nMaxDig, float *fHeight, bool bRoom);	//���Z�b�g����
	void	UpField(int *nMap, float fHeight);	//���v���X����
	HRESULT Init(void);
	void	Update(void);
	void	Uninit(void);
	void	Draw(void);

	void		BindTexture(LPDIRECT3DTEXTURE9 pTex) { m_pTex = pTex; }

	static void MeshCollisionCeiling(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &length);
	static bool MeshCollisionField(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, bool &bJump);
	static void MeshCollisionWall(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, int &nCntHit, bool &bJump, bool bReflection);
	static float FieldCollision(D3DXVECTOR3 &FposUL, D3DXVECTOR3 &FposUR, D3DXVECTOR3 &FposDL, D3DXVECTOR3 &FposDR, D3DXVECTOR3 WKpos, D3DXVECTOR3& pos, D3DXVECTOR3 &FNor);
	static int WallCollision(D3DXVECTOR3 Wall0, D3DXVECTOR3 Wall1, D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, float& fLength, int &nCntHit, bool &bReflection);
	static bool FieldCheck(D3DXVECTOR3 &FposUL, D3DXVECTOR3 &FposUR, D3DXVECTOR3 &FposDL, D3DXVECTOR3 &FposDR, D3DXVECTOR3& pos);
	static int AngleCheck(float fAngle0, float fAngle1);
	void MeshCeling(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, float& fLength);
	bool MeshField(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &FNor, float& fLength, bool &bJump);
	void MeshWall(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, float& fLength, int &nCntHit, bool &bReflection);

	float &GetfUV_X(void) { return m_fUV_X; }
	float &GetfUV_Y(void) { return m_fUV_Y; }
	CScene::DRAW_TYPE		&GetDrawType(void) { return m_DrawType; }

private://*****************************************************************************
	void WallPlus(D3DXVECTOR3& pos0, D3DXVECTOR3 &pos1, float& fLengthX, float& fLengthZ);
	void PlusNor(VERTEX_3D *pVtx, VERTEX_3D *pVtxL, VERTEX_3D *pVtxR);	//�@���̃Z�b�g����

		//�ϐ��錾//***********************************************************************
	CScene::DRAW_TYPE		m_DrawType;			// �`�悷����@(���Z�����Ȃ�)
	TYPE					m_Type;			//�^�C�v
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;		//�C���f�b�N�X�o�b�t�@�̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTex;		//�摜
	D3DXVECTOR3				m_pos;			//�ʒu
	D3DXVECTOR3				m_rot;			//����
	float					m_fUV_X;
	float					m_fUV_Y;
	int						m_nVertical;	//�c�̕�����
	int						m_nCross;		//���̕�����
	int						m_nNumVertex;	//���_��
	int						m_nNumIdx;		//�C���f�b�N�X��
	int						m_nNumPolygon;	//�|���S����
	bool					m_bMesh;		//�����Ă���ʂ��������O����(����肩�E��肩)
};

#endif