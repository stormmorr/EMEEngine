/*

    unMesh
    Copyright SomptingSOFT/Max Lawlor (C) 2007
	SomptingSOFT Portal www.stss.co.nr

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
#include "../UnSRC/Utility/CSharedStruct.h"

////////////////////////////////////////////////////////////////////////////////
// Class declaration ///////////////////////////////////////////////////////////

class unMesh
{
public:
	unMesh();
	virtual ~unMesh();
	unMesh(unMesh *i_mesh);
	void clone_struct( unAvatar * unavatar );
	void clone_struct_physics( unAvatar * unavatar );

protected:
	CalCoreModel* m_calCoreModel;
	CalModel* m_calModel;
	CalHardwareModel *m_calHardwareModel;
	unsigned int m_bufferObject[6];

public:
	void acAllocate(void);
	bool acCreate(std::string i_filename);
	bool acInit();
	void acIdle();
	void acRender();
	void acShutdown();

	std::vector<DigiClothMesh*> m_Cloth;

protected:
	unsigned int LoadTexture(const std::string& strFilename);
	bool LoadBufferObject();
	bool ParseModelConfiguration(const std::string& strFilename);

	float m_lodLevel;
	float m_scale;
	int m_vertexCount;
	int m_faceCount;
	int m_meshId[32];
	int m_meshCount;
	unsigned int m_textureId[32];
	int m_textureCount;
};

#endif		//UNMESH_H