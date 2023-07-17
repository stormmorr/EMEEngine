/*

    unMeshStatic
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef UNSTATICMESH_H
#define UNSTATICMESH_H

//----------------------------------------------------------------------------//
// Includes                                                                   //
//----------------------------------------------------------------------------//

#include <string>
#include <vector>

#include "cal3d.h"

//----------------------------------------------------------------------------//
// Class declaration                                                          //
//----------------------------------------------------------------------------//

#define MESHLOAD_DEFAULT 250

typedef unsigned int GLuint;

class unMeshStatic
{
// member variables
protected:
  float m_lodLevel;
  int maxoctreedepth;
  bool m_flip;

  bool loadCoreMesh(const std::string& strFilename);

// constructors/destructor
public:
	unMeshStatic();
	virtual ~unMeshStatic();
	unMeshStatic(unMeshStatic *i_mesh);

	unsigned int m_bufferObject[6];
	unsigned int m_TextureTag;

// member functions
public:
  bool onCreate(std::string i_filename);
  bool onInit();
  void onIdle();
  void onRender();
  bool acInit();
  bool acSetBuffers(void);
  void acShutdown();
  GLuint LoadTexture(const std::string& strFilename);
  int m_meshCount;
  int m_textureCount;
  int m_vertexCount;
  int m_faceCount;

#if 0
  pArray<pMesh *> m_submesh;
#endif

  QunCoreModel* m_calCoreModel;
  QunModel* m_qunModel;
  QunHardwareModel *m_calHardwareModel;

  std::vector<GLuint> m_texdata;
  std::vector<GLuint> m_texnormdata;

  float m_scale;

protected:
  int readInt(std::ifstream *file);
  GLuint loadTexture(const std::string& strFilename);
  bool parseModelConfiguration(const std::string& strFilename);
  unsigned int acLoadTexture(const std::string& strFilename);
};

typedef struct unMeshStaticInstance
{
  float x;
  float y;
  float z;
  unsigned int m_VectorIndex;
} unMeshStaticInstance;

class unMeshStaticBank
{
public:
	unMeshStaticBank();
	~unMeshStaticBank();

	static unMeshStaticBank* instance();

	unsigned int acAddInstance(unsigned int i_VectorIndex, int i_x, int i_y, int i_z);

	std::vector<unMeshStaticInstance*> m_MeshInstance;

private:
	static unMeshStaticBank* s_instance;
};

#endif		//ICMESH_H

//----------------------------------------------------------------------------//
