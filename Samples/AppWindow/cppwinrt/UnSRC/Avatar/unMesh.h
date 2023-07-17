/*

    unMesh
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef UNMESH_H
#define UNMESH_H

////////////////////////////////////////////////////////////////////////////////
// Includes ////////////////////////////////////////////////////////////////////

#include "unAvatar.h"
#include "cal3d.h"

//*#include "Body.h"

#ifndef QAGE_POINT
#include "QSharedStruct.h"
#else
#include "../UnSRC/Utility/QSharedStruct-Point.h"
#endif

#include "../Memory/unSegment.h"
#include "../Memory/unIdentManager.h"

//#include "../../DigitalMass/Source/Digi/DigiMass.h"

////////////////////////////////////////////////////////////////////////////////
// Class declaration ///////////////////////////////////////////////////////////

class unMesh
{
public:
	unMesh();
	~unMesh();
	//unMesh(unMesh *i_mesh);
	void acShutdown(void);
	void clone_struct( unAvatar * unavatar );
	void clone_struct_physics( unAvatar * unavatar );

protected:
	QunCoreModel* m_calCoreModel;
	QunModel* m_qunModel;
	QunHardwareModel *m_calHardwareModel;
	unsigned int m_bufferObject[6];

public:
	bool acCreate(std::string i_filename);
	bool acInit();
	void acIdle();
	void acRender();

	//std::vector<DigiClothMesh*> m_Cloth;

protected:
	unsigned int acLoadTexture(const std::string& strFilename);
	bool acSetBuffers();
	bool acParseConfiguration(const std::string& strFilename);

	float m_lodLevel;
	float m_scale;
	int m_vertexCount;
	int m_faceCount;
	int m_meshId[32];
	int m_meshCount;
	int m_textureCount;
	unsigned int m_textureId[32];
};

typedef struct CalCoreKeyframePack
{
public:
	float m_time;
	QunVector m_translation;
	QunQuaternion m_rotation;
} CalCoreKeyframePack;

//typedef ip::allocator<CalCoreKeyframePack, managed_shared_memory::segment_manager> Alloc_KeyFrame;
//typedef ip::vector<CalCoreKeyframePack, Alloc_KeyFrame> UN_Vector_KeyFrame;

typedef struct CalCoreTrackPack
{
public:
	int m_coreBoneId;
	//UN_Vector_KeyFrame *m_UNkeyframes;
} CalCoreTrackPack;

//typedef ip::allocator<CalCoreTrackPack, managed_shared_memory::segment_manager> Alloc_CoreTrack;
//typedef ip::list<CalCoreTrackPack, Alloc_CoreTrack> UN_List_CoreTrack;

typedef struct CalCoreAnimationPack
{
public:
	//UN_List_CoreTrack *m_UNlistCoreTrack;

	float m_duration;
#pragma message("ADD for long scale mass animation database add filename searching and interface tries")
#if 0
	std::string m_name;
	std::string m_filename;
#endif
} CalCoreAnimationPack;

//typedef ip::allocator<CalCoreAnimationPack, managed_shared_memory::segment_manager> Alloc_Animation;
//typedef ip::vector<CalCoreAnimationPack, Alloc_Animation> UN_Vector_Animation;

/**class unDataMesh
{
public:
	unDataMesh();
	virtual ~unDataMesh();
	unDataMesh(unDataMesh *i_mesh);
	void acShutdown(void);
	int acMake(void);

	void clone_struct( unAvatar * unavatar );
	void clone_struct_physics( unAvatar * unavatar );

protected:
	QunCoreModel* m_calCoreModel;
	QunModel* m_qunModel;
	QunHardwareModel *m_calHardwareModel;
	unsigned int m_bufferObject[6];
	unsigned int m_TextureTag;

	UN_Vector_Animation *m_UNvectorAnim;
	UN_Vector_HardMesh *m_HardMesh;

	QSharedStruct<Q_Mesh_Data> Q_Mesh_Data;

public:
	bool acCreate(std::string i_filename);
	bool acInit(int i_NomDataMesh);

	//std::vector<DigiClothMesh*> m_Cloth;

protected:
	unsigned int acLoadTexture(const std::string& strFilename);
	bool acSetBuffers();
	bool acParseConfiguration(const std::string& strFilename);

	float m_lodLevel;
	float m_scale;
	int m_vertexCount;
	int m_faceCount;
	int m_meshId[32];
	int m_meshCount;
	unsigned int m_textureId[32];
	int m_textureCount;

public:
	HANDLE Qfile_VertexBuffer;
	HANDLE Qfile_WeightBuffer;
	HANDLE Qfile_MatrixIndexBuffer;
	HANDLE Qfile_NormalBuffer;
	HANDLE Qfile_TexCoordBuffer;
	HANDLE Qfile_IndexBuffer;

	std::string m_NameIdentVertexBuffer;
	std::string m_NameIdentWeightBuffer;
	std::string m_NameIdentMatrixIndexBuffer;
	std::string m_NameIdentNormalBuffer;
	std::string m_NameIdentTexCoordBuffer;
	std::string m_NameIdentIndexBuffer;
};*/

class unShellMesh
{
public:
	unShellMesh();
	virtual ~unShellMesh();
	unShellMesh(unShellMesh *i_mesh);
	void acShutdown(void);

	void clone_struct( unAvatar * unavatar );
	void clone_struct_physics( unAvatar * unavatar );
	void clone_struct_physics( unAvatar * unavatar, int i_Index );

	void acMake(void);
	void acTransferAnim(unShellMesh *i_ShellMesh);

	//*void acAddParticle(Digi::Vertex i_Vertex);
	//*void acSetBody(float * i_VertexBuffer, int i_VertexCount, QunIndex *i_IndexBuffer, int i_IndexCount);
	//*void acTriParticle(Digi::Vertex i_VertA, Digi::Vertex i_VertB, Digi::Vertex i_VertC);

protected:
	QunCoreModel* m_calCoreModel;
	QunModel* m_qunModel;
	QunHardwareModel *m_calHardwareModel;
	unsigned int m_bufferObject[6];
	unsigned int m_TextureTag;
	//*Body *m_Body;

	//UN_Vector_Animation *m_UNvectorAnim;
	//UN_Vector_HardMesh *m_HardMesh;

	QSharedStruct<Q_Mesh_Data> Q_Mesh_Data;

public:
	bool acCreate(std::string i_filename);
	bool acInit();

	//std::vector<DigiClothMesh*> m_Cloth;

	float m_bodyscale;

protected:
	unsigned int acLoadTexture(const std::string& strFilename);
	bool acSetBuffers();
	bool acParseConfiguration(const std::string& strFilename);

	float m_lodLevel;
	float m_scale;
	int m_vertexCount;
	int m_faceCount;
	int m_meshId[32];
	int m_meshCount;
	unsigned int m_textureId[32];
	int m_textureCount;

public:
	HANDLE Qfile_VertexBuffer;
	HANDLE Qfile_WeightBuffer;
	HANDLE Qfile_MatrixIndexBuffer;
	HANDLE Qfile_NormalBuffer;
	HANDLE Qfile_TexCoordBuffer;
	HANDLE Qfile_IndexBuffer;

	std::string m_NameIdentVertexBuffer;
	std::string m_NameIdentWeightBuffer;
	std::string m_NameIdentMatrixIndexBuffer;
	std::string m_NameIdentNormalBuffer;
	std::string m_NameIdentTexCoordBuffer;
	std::string m_NameIdentIndexBuffer;
};

#endif		//UNMESH_H