/*

    unDataMesh
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

//----------------------------------------------------------------------------//
// Includes                                                                   //
//----------------------------------------------------------------------------//

#if defined(_MSC_VER) && _MSC_VER <= 0x0600
#pragma warning(disable : 4786)
#endif

#include "unAvatar.h"
#include "unMesh.h"

#include "cal3d/coretrack.h"
#include "cal3d/corekeyframe.h"

#include "tgacal3d.h"

#include <windows.h>				// Header File For Windows
#include <stdio.h>					// Header File For Standard Input/Output

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

// EGL includes
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>

//*#include "../../DigitalMass/Source/Digi/DigiMass.h"
//*#include "../../DigitalMass/Source/Digi/Cloth.h"

//*#include "PxPhysics.h"
//*#include "PxCooking.h"

#include "boost/interprocess/managed_shared_memory.hpp"
#include "boost/interprocess/containers/vector.hpp"
#include "boost/interprocess/containers/list.hpp"
#include "boost/interprocess/allocators/allocator.hpp"

int ext_NomDataMesh = 0;

std::string m_dmMaterialPath = "Avatar//Material//";

////////////////////////////////////////////////////////////////////////////////
// Constructors ////////////////////////////////////////////////////////////////

unDataMesh::unDataMesh()
{
  m_calCoreModel = new CalCoreModel("dummy");

  m_lodLevel = 1.0f;
  m_vertexCount = 0;
  m_faceCount = 0;
}

unDataMesh::unDataMesh(unDataMesh *i_mesh)
{
	int i;
	this->m_calCoreModel = i_mesh->m_calCoreModel;
	this->m_calModel = i_mesh->m_calModel;
	this->m_calHardwareModel = i_mesh->m_calHardwareModel;

	this->m_lodLevel = i_mesh->m_lodLevel;

	for(i=0; i<6; i++) this->m_bufferObject[i] = i_mesh->m_bufferObject[i];
}

////////////////////////////////////////////////////////////////////////////////
// Destructor //////////////////////////////////////////////////////////////////

unDataMesh::~unDataMesh()
{
#if 0
	////// Clean Renderer Textures
	CalCoreMaterial *pCoreMaterial;
	int mapId;
	unsigned int i_Mapid;
	int materialId;
	for(materialId = 0; materialId < m_calCoreModel->getCoreMaterialCount(); materialId++)
		{
		pCoreMaterial = m_calCoreModel->getCoreMaterial(materialId);
		
		for(mapId = 0; mapId < pCoreMaterial->getMapCount(); mapId++)
			{
			i_Mapid = (unsigned int)pCoreMaterial->getMapUserData(mapId);

			glDeleteTextures(1, &i_Mapid);
			}
		}
#endif

	delete m_calCoreModel;
	delete m_calModel;
	delete m_calHardwareModel;

	glDeleteBuffersARB(6, m_bufferObject);
}

void unDataMesh::acShutdown(void)
{
#if 0
	////// Clean Renderer Textures
	CalCoreMaterial *pCoreMaterial;
	int mapId;
	unsigned int i_Mapid;
	int materialId;
	for(materialId = 0; materialId < m_calCoreModel->getCoreMaterialCount(); materialId++)
		{
		pCoreMaterial = m_calCoreModel->getCoreMaterial(materialId);
		
		for(mapId = 0; mapId < pCoreMaterial->getMapCount(); mapId++)
			{
			i_Mapid = (unsigned int)pCoreMaterial->getMapUserData(mapId);

			glDeleteTextures(1, &i_Mapid);
			}
		}

	glDeleteBuffersARB(6, m_bufferObject);
#endif

	delete m_calCoreModel;
	delete m_calModel;
	delete m_calHardwareModel;
}

////////////////////////////////////////////////////////////////////////////////
// Load and create a texture from a given file /////////////////////////////////

int dmreadInt( std::ifstream *file )
{
	int x = 0;

	for ( int i = 0; i < 32; i+=8 ) 
		{
		char c;
		file->read ( &c, 1 );
		x += c << i;
 		}

 	return x;
}

GLuint unDataMesh::acLoadTexture(const std::string& strFilename)
{
	GLuint textureId=0;

	std::string i_FullFilename = m_dmMaterialPath + strFilename;

	if(_stricmp(strrchr(i_FullFilename.c_str(),'.'),".raw")==0)
		{
		// open the texture file
		std::ifstream file;
		file.open(i_FullFilename.c_str(), std::ios::in | std::ios::binary);
		if(!file)
			{
			std::cerr << "Texture file '" << i_FullFilename << "' not found." << std::endl;
			return 0;
			}

		 // load the dimension of the texture
		int width = dmreadInt(&file);     
		int height = dmreadInt(&file);     
		int depth = dmreadInt(&file);     

		// allocate a temporary buffer to load the texture to
		unsigned char *pBuffer;
		pBuffer = new unsigned char[2 * width * height * depth];
		if(pBuffer == 0)
			{
			std::cerr << "Memory allocation for texture '" << i_FullFilename << "' failed." << std::endl;
			return 0;
			}

		// load the texture
		file.read((char *)pBuffer, width * height * depth);

		// explicitely close the file
		file.close();

		// flip texture around y-axis (-> opengl-style)
		int y;
		for(y = 0; y < height; y++)
			{
			memcpy(&pBuffer[(height + y) * width * depth], &pBuffer[(height - y - 1) * width * depth], width * depth);
			}
	     
		// generate texture
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	     
		glTexImage2D(GL_TEXTURE_2D, 0, (depth == 3) ? GL_RGB : GL_RGBA, width, height, 0, (depth == 3) ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, &pBuffer[width * height * depth]);
		// free the allocated memory

		delete [] pBuffer;
		}
	else if(_stricmp(strrchr(i_FullFilename.c_str(),'.'),".tga")==0)  
		{
		CTga *Tga;
		Tga = new CTga();
		if(Tga->ReadFile(i_FullFilename.c_str())==0)
			{
			Tga->Release();
			printf("ERROR:::unDataMesh::acacacLoadTexture File not found %s\n", i_FullFilename.c_str());
			for(;;) {}
			return 0;
			}

		if(Tga->Bpp()!=32)
			{
			Tga->Release();
			printf("ERROR:::unDataMesh::acacacLoadTexture Tga->Bpp() != 32 %s\n", i_FullFilename.c_str());
			return 0;
			}

		//Flip texture
		int width = Tga->GetSizeX();
		int height = Tga->GetSizeY();
		//int depth = Tga->Bpp() / 8;    

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glGenTextures(1, &textureId);

		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA , GL_UNSIGNED_BYTE, (char*)Tga->GetPointer() );

		Tga->Release();
		}

	return textureId;
}

////////////////////////////////////////////////////////////////////////////////
// Create the unDataMesh ///////////////////////////////////////////////////////////

bool unDataMesh::acCreate(std::string i_filename)
{
	///////---- Parse Model Configuration File ----///////
	if(!acParseConfiguration(i_filename))
		{
		std::cerr << "unDataMesh::: No model configuration file given." << std::endl;
		for(;;) {}
		}

	// make one material thread for each material
	// NOTE: this is not the right way to do it, but this viewer can't do the right
	// mapping without further information on the model etc., so this is the only
	// thing we can do here.
	int materialId;
	for(materialId = 0; materialId < m_calCoreModel->getCoreMaterialCount(); materialId++)
		{
		// create the a material thread
		m_calCoreModel->createCoreMaterialThread(materialId);

		// initialize the material thread
		m_calCoreModel->setCoreMaterialId(materialId, 0, materialId);
		}

	m_calModel = new CalModel(m_calCoreModel);
	
	return true;
}

////////////////////////////////////////////////////////////////////////////////
// Initialize //////////////////////////////////////////////////////////////////

bool unDataMesh::acInit(int i_NomDataMesh)
{
	ext_NomDataMesh = i_NomDataMesh;

	// load all textures and store the opengl texture id in the corresponding map in the material
	bool i_TextureTag = true;
	int i_TextureID = 0;

	int materialId;
	for(materialId = 0; materialId < m_calCoreModel->getCoreMaterialCount(); materialId++)
		{
		// get the core material
		CalCoreMaterial *pCoreMaterial;
		pCoreMaterial = m_calCoreModel->getCoreMaterial(materialId);

		// loop through all maps of the core material
		int mapId;
		for(mapId = 0; mapId < pCoreMaterial->getMapCount(); mapId++)
			{
			// store the opengl texture id in the user data of the map
			pCoreMaterial->setMapUserData(mapId, (Cal::UserData)i_TextureID);

			if(i_TextureTag)
				{
				m_TextureTag = i_TextureID;
				i_TextureTag = false;
				}

			i_TextureID++;
			}
		}

	// attach all meshes to the model
	int meshId;
	for(meshId = 0; meshId < m_calCoreModel->getCoreMeshCount(); meshId++)
		{
		m_calModel->attachMesh(meshId);
		}

	// set the material set of the whole model
	m_calModel->setMaterialSet(0);

#if 0
	glewInit();

	if (!GLEW_ARB_vertex_program)
		{
		std::cerr << "Error ARB_vertex_program OpenGL extension not found." << std::endl;
		return false;
		}

	if (!GLEW_ARB_vertex_buffer_object)
		{
		std::cerr << "Error ARB_vertex_buffer_object OpenGL extension not found." << std::endl;
		return false;
		}
#endif

	if(!acSetBuffers())
		{
		std::cerr << "Error loading vertex buffer object." << std::endl;
		return false;
		}

	// Finished
	std::cout << "Initialization Finished" << std::endl;
	std::cout << std::endl;

	return true;
}

bool unDataMesh::acSetBuffers()
{
	std::string i_NameQFile = "Qfile_";
	std::string i_NameDataMesh = "DataMesh";
	std::string i_NameVertexBuffer = "_VertexBuffer";
	std::string i_NameWeightBuffer = "_WeightBuffer";
	std::string i_NameMatrixIndexBuffer = "_MatrixIndexBuffer";
	std::string i_NameNormalBuffer = "_NormalBuffer";
	std::string i_NameTexCoordBuffer = "_TexCoordBuffer";
	std::string i_NameIndexBuffer = "_IndexBuffer";

	char casecntbuf[100];
	itoa(ext_NomDataMesh, casecntbuf, 10);
	ext_NomDataMesh++;
	std::string i_NameNom = casecntbuf;

	m_NameIdentVertexBuffer = i_NameQFile + i_NameDataMesh + i_NameNom + i_NameVertexBuffer;
	m_NameIdentWeightBuffer = i_NameQFile + i_NameDataMesh + i_NameNom + i_NameWeightBuffer;
	m_NameIdentMatrixIndexBuffer = i_NameQFile + i_NameDataMesh + i_NameNom + i_NameMatrixIndexBuffer;
	m_NameIdentNormalBuffer = i_NameQFile + i_NameDataMesh + i_NameNom + i_NameNormalBuffer;
	m_NameIdentTexCoordBuffer = i_NameQFile + i_NameDataMesh + i_NameNom + i_NameTexCoordBuffer;
	m_NameIdentIndexBuffer = i_NameQFile + i_NameDataMesh + i_NameNom + i_NameIndexBuffer;

	char *i_NameArrayVertexBuffer = (char *)m_NameIdentVertexBuffer.c_str();
	char *i_NameArrayWeightBuffer = (char *)m_NameIdentWeightBuffer.c_str();
	char *i_NameArrayMatrixIndexBuffer = (char *)m_NameIdentMatrixIndexBuffer.c_str();
	char *i_NameArrayNormalBuffer = (char *)m_NameIdentNormalBuffer.c_str();
	char *i_NameArrayTexCoordBuffer = (char *)m_NameIdentTexCoordBuffer.c_str();
	char *i_NameArrayIndexBuffer = (char *)m_NameIdentIndexBuffer.c_str();

	/**Qfile_VertexBuffer = CreateFileMapping (INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 30000*3*sizeof(float), i_NameArrayVertexBuffer);
	Qfile_WeightBuffer = CreateFileMapping (INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 30000*4*sizeof(float), i_NameArrayWeightBuffer);
	Qfile_MatrixIndexBuffer = CreateFileMapping (INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 30000*4*sizeof(float), i_NameArrayMatrixIndexBuffer);
	Qfile_NormalBuffer = CreateFileMapping (INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 30000*3*sizeof(float), i_NameArrayNormalBuffer);
	Qfile_TexCoordBuffer = CreateFileMapping (INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 30000*2*sizeof(float), i_NameArrayTexCoordBuffer);
	Qfile_IndexBuffer = CreateFileMapping (INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 50000*3*sizeof(CalIndex), i_NameArrayIndexBuffer);*/

	if (Qfile_VertexBuffer == NULL)
		{
		int err = GetLastError();
		printf("ERROR:::unDataMesh could not create file mapping handle Qfile_VertexBuffer\n");
		for(;;) {};
		}

	if (Qfile_WeightBuffer == NULL)
		{
		int err = GetLastError();
		printf("ERROR:::unDataMesh could not create file mapping handle Qfile_WeightBuffer\n");
		for(;;) {};
		}

	if (Qfile_MatrixIndexBuffer == NULL)
		{
		int err = GetLastError();
		printf("ERROR:::unDataMesh could not create file mapping handle Qfile_MatrixIndexBuffer\n");
		for(;;) {};
		}

	if (Qfile_NormalBuffer == NULL)
		{
		int err = GetLastError();
		printf("ERROR:::unDataMesh could not create file mapping handle Qfile_NormalBuffer\n");
		for(;;) {};
		}

	if (Qfile_TexCoordBuffer == NULL)
		{
		int err = GetLastError();
		printf("ERROR:::unDataMesh could not create file mapping handle Qfile_TexCoordBuffer\n");
		for(;;) {};
		}

	if (Qfile_IndexBuffer == NULL)
		{
		int err = GetLastError();
		printf("ERROR:::unDataMesh could not create file mapping handle Qfile_IndexBuffer\n");
		for(;;) {};
		}

	SetNamedSecurityInfo(i_NameArrayVertexBuffer, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION, 0, 0, (PACL) NULL, NULL);
	SetNamedSecurityInfo(i_NameArrayWeightBuffer, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION, 0, 0, (PACL) NULL, NULL);
	SetNamedSecurityInfo(i_NameArrayMatrixIndexBuffer, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION, 0, 0, (PACL) NULL, NULL);
	SetNamedSecurityInfo(i_NameArrayNormalBuffer, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION, 0, 0, (PACL) NULL, NULL);
	SetNamedSecurityInfo(i_NameArrayTexCoordBuffer, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION, 0, 0, (PACL) NULL, NULL);
	SetNamedSecurityInfo(i_NameArrayIndexBuffer, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION, 0, 0, (PACL) NULL, NULL);

	float *pVertexBuffer = (float*)MapViewOfFile(Qfile_VertexBuffer, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
	float *pWeightBuffer = (float*)MapViewOfFile(Qfile_WeightBuffer, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
	float *pMatrixIndexBuffer = (float*)MapViewOfFile(Qfile_MatrixIndexBuffer, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
	float *pNormalBuffer = (float*)MapViewOfFile(Qfile_NormalBuffer, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
	float *pTexCoordBuffer = (float*)MapViewOfFile(Qfile_TexCoordBuffer, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
	CalIndex *pIndexBuffer = (CalIndex*)MapViewOfFile(Qfile_IndexBuffer, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);

	::new(pVertexBuffer) float;
	::new(pWeightBuffer) float;
	::new(pMatrixIndexBuffer) float;
	::new(pNormalBuffer) float;
	::new(pTexCoordBuffer) float;
	::new(pIndexBuffer) CalIndex;

	if (pVertexBuffer == NULL)
		{
		CloseHandle(Qfile_VertexBuffer);
		printf("ERROR:::unDataMesh initialization pVertexBuffer\n");
		for(;;) {};
		}

	if (pWeightBuffer == NULL)
		{
		CloseHandle(Qfile_WeightBuffer);
		printf("ERROR:::unDataMesh initialization pWeightBuffer\n");
		for(;;) {};
		}

	if (pMatrixIndexBuffer == NULL)
		{
		CloseHandle(Qfile_MatrixIndexBuffer);
		printf("ERROR:::unDataMesh initialization pMatrixIndexBuffer\n");
		for(;;) {};
		}

	if (pNormalBuffer == NULL)
		{
		CloseHandle(Qfile_NormalBuffer);
		printf("ERROR:::unDataMesh initialization pNormalBuffer\n");
		for(;;) {};
		}

	if (pTexCoordBuffer == NULL)
		{
		CloseHandle(Qfile_TexCoordBuffer);
		printf("ERROR:::unDataMesh initialization pTexCoordBuffer\n");
		for(;;) {};
		}

	if (pIndexBuffer == NULL)
		{
		CloseHandle(Qfile_IndexBuffer);
		printf("ERROR:::unDataMesh initialization pIndexBuffer\n");
		for(;;) {};
		}

	if(pVertexBuffer==NULL || pWeightBuffer == NULL
		|| pMatrixIndexBuffer==NULL || pNormalBuffer == NULL
		|| pTexCoordBuffer==NULL || pIndexBuffer == NULL)
		{
		return false;
		}	  

	m_calHardwareModel = new CalHardwareModel(m_calCoreModel);
	m_calHardwareModel->setVertexBuffer((char*)pVertexBuffer,3*sizeof(float));
	m_calHardwareModel->setNormalBuffer((char*)pNormalBuffer,3*sizeof(float));
	m_calHardwareModel->setWeightBuffer((char*)pWeightBuffer,4*sizeof(float));
	m_calHardwareModel->setMatrixIndexBuffer((char*)pMatrixIndexBuffer,4*sizeof(float));
	m_calHardwareModel->setTextureCoordNum(1);
	m_calHardwareModel->setTextureCoordBuffer(0,(char*)pTexCoordBuffer,2*sizeof(float));
	m_calHardwareModel->setIndexBuffer(pIndexBuffer);

	////// Load Hardware Model with maximum 29 Bones //////
	m_calHardwareModel->load( 0, 0, 29);

#if 1
	//const Alloc_HardMesh alloc_hardmesh (m_unSegment->get_segment_manager());

	Alloc_HardMesh alloc_hardmesh (m_unSegment->get_segment_manager());

	std::string i_Ident = acIdentGen("UNHardMesh");
	m_HardMesh = m_unSegment->construct<UN_Vector_HardMesh>(i_Ident.c_str())(alloc_hardmesh);

	// the index index in pIndexBuffer are relative to the begining of the hardware mesh,
	// we make them relative to the begining of the buffer.

	int meshId;
	for(meshId = 0; meshId < m_calHardwareModel->getHardwareMeshCount(); meshId++)
		{
		m_calHardwareModel->selectHardwareMesh(meshId);

		int faceId;
		for(faceId = 0; faceId < m_calHardwareModel->getFaceCount(); faceId++)
			{
			pIndexBuffer[faceId*3+ m_calHardwareModel->getStartIndex()]+=m_calHardwareModel->getBaseVertexIndex();
			pIndexBuffer[faceId*3+1+ m_calHardwareModel->getStartIndex()]+=m_calHardwareModel->getBaseVertexIndex();
			pIndexBuffer[faceId*3+2+ m_calHardwareModel->getStartIndex()]+=m_calHardwareModel->getBaseVertexIndex();
			}

		Q_Hard_Data *i_HardMesh = new Q_Hard_Data;
		i_HardMesh->m_StartIndex = m_calHardwareModel->getStartIndex();
		i_HardMesh->m_FaceCount = m_calHardwareModel->getFaceCount();
		i_HardMesh->m_BoneCount = m_calHardwareModel->getBoneCount();
		i_HardMesh->m_TextureID = (GLuint)m_calHardwareModel->getMapUserData(0);

		for(int i_IterBone = 0; i_IterBone < m_calHardwareModel->getBoneCount(); i_IterBone++)
			{
			i_HardMesh->m_BonesIndices[i_IterBone] = m_calHardwareModel->m_vectorHardwareMesh[meshId].m_vectorBonesIndices[i_IterBone];
			}

		m_HardMesh->push_back(*i_HardMesh);
		}

	// We use ARB_vertex_buffer_object extension,
	// it provide better performance

#if 0
	glGenBuffersARB(6, m_bufferObject);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[0]);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, m_calHardwareModel->getTotalVertexCount()*3*sizeof(float),(const void*)pVertexBuffer, GL_STATIC_DRAW_ARB);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[1]);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, m_calHardwareModel->getTotalVertexCount()*4*sizeof(float),(const void*)pWeightBuffer, GL_STATIC_DRAW_ARB);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[2]);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, m_calHardwareModel->getTotalVertexCount()*3*sizeof(float),(const void*)pNormalBuffer, GL_STATIC_DRAW_ARB);
  
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[3]);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, m_calHardwareModel->getTotalVertexCount()*4*sizeof(float),(const void*)pMatrixIndexBuffer, GL_STATIC_DRAW_ARB);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[4]);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, m_calHardwareModel->getTotalVertexCount()*2*sizeof(float),(const void*)pTexCoordBuffer, GL_STATIC_DRAW_ARB);

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_bufferObject[5]);
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_calHardwareModel->getTotalFaceCount()*3*sizeof(CalIndex),(const void*)pIndexBuffer, GL_STATIC_DRAW_ARB);
#endif

	std::string i_IdentMD = acIdentGen("Q_Mesh_Data");
	Q_Mesh_Data.Acquire((char *)i_IdentMD.c_str());
	Q_Mesh_Data->m_VertexCount = m_calHardwareModel->getTotalVertexCount();
	Q_Mesh_Data->m_FaceCount = m_calHardwareModel->getTotalFaceCount();
	Q_Mesh_Data->m_MeshCount = m_calHardwareModel->getHardwareMeshCount();
	Q_Mesh_Data->m_TextureTag = m_TextureTag;

	printf("Q_Mesh_Data->m_VertexCount %i\n", Q_Mesh_Data->m_VertexCount);

#if 0
	free(pVertexBuffer);
	free(pWeightBuffer);
	free(pNormalBuffer);
	free(pMatrixIndexBuffer);
	free(pIndexBuffer);
#endif
#endif
	return true;
}

////////////////////////////////////////////////////////////////////////////////
// Parse the configuration file and load the whole model ///////////////////////

bool unDataMesh::acParseConfiguration(const std::string& strFilename)
{
	// open the model configuration file
	std::ifstream file;
	file.open(strFilename.c_str(), std::ios::in | std::ios::binary);
	if(!file)
		{
		std::cerr << "Failed to open model configuration file '" << strFilename << "'." << std::endl;
		return false;
		}

	// parse all lines from the model configuration file
	int line;
	for(line = 1; ; line++)
		{
		// read the next model configuration line
		std::string strBuffer;
		std::getline(file, strBuffer);

		// stop if we reached the end of file
		if(file.eof()) break;

		// check if an error happend while reading from the file
		if(!file)
			{
			std::cerr << "Error while reading from the model configuration file '" << strFilename << "'." << std::endl;
			return false;
			}

		// find the first non-whitespace character
		std::string::size_type pos;
		pos = strBuffer.find_first_not_of(" \t");

		// check for empty lines
		if((pos == std::string::npos) || (strBuffer[pos] == '\n') || (strBuffer[pos] == '\r') || (strBuffer[pos] == 0)) continue;

		// check for comment lines
		if(strBuffer[pos] == '#') continue;

		// get the key
		std::string strKey;
		strKey = strBuffer.substr(pos, strBuffer.find_first_of(" =\t\n\r", pos) - pos);
		pos += strKey.size();

		// get the '=' character
		pos = strBuffer.find_first_not_of(" \t", pos);
		if((pos == std::string::npos) || (strBuffer[pos] != '='))
			{
			std::cerr << strFilename << "(" << line << "): Invalid syntax." << std::endl;
			return false;
			}

		// find the first non-whitespace character after the '=' character
		pos = strBuffer.find_first_not_of(" \t", pos + 1);

		// get the data
		std::string strData;
		strData = strBuffer.substr(pos, strBuffer.find_first_of("\n\r", pos) - pos);

		TCHAR szDirectory[255] = "";
		if(!::GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory))
			{
			printf("GetDirectoryERROR Cant find current directory\n");
			for(;;) {}
			}

		std::string f_Path = szDirectory;
		f_Path = f_Path + "\\Avatar\\";

		// handle the model creation
		if(strKey == "scale")
			{
			// set rendering scale factor
			m_scale = atof(strData.c_str());
			}
		else if(strKey == "skeleton")
			{
			strData = f_Path + strData;

			// load core skeleton
			std::cout << "Loading skeleton '" << strData << "'..." << std::endl;
			if(!m_calCoreModel->loadCoreSkeleton(strData))
				{
				CalError::printLastError();
				return false;
				}
			}
		else if(strKey == "animation")
			{
			strData = f_Path + strData;

			// load core animation
			std::cout << "Loading animation '" << strData << "'..." << std::endl;
			if(m_calCoreModel->loadCoreAnimation(strData) == -1)
				{
				CalError::printLastError();
				return false;
				}
			}
		else if(strKey == "offset")
			{
			// load core animation
			std::cout << "Setting Position Correction '" << strData << "'..." << std::endl;
			
			int i_convint = atoi(strData.c_str());
			m_calCoreModel->setOffSetMesh(i_convint);
			}

		else if(strKey == "offsetptrX")
			{
			// load core animation
			std::cout << "Setting Position '" << strData << "'..." << std::endl;
		
			m_calCoreModel->setOffSetX(atof(strData.c_str()));
			}

		else if(strKey == "offsetptrY")
			{
			// load core animation
			std::cout << "Setting Position '" << strData << "'..." << std::endl;
			
			m_calCoreModel->setOffSetY(atof(strData.c_str()));
			}

		else if(strKey == "offsetptrZ")
			{
			// load core animation
			std::cout << "Setting Position '" << strData << "'..." << std::endl;
			
			m_calCoreModel->m_OffSetZ.push_back(atof(strData.c_str()));
			}
		else if(strKey == "mesh")
			{
			strData = f_Path + strData;

			// load core mesh
			std::cout << "Loading mesh '" << strData << "'..." << std::endl;
			if(m_calCoreModel->loadCoreMesh(strData) == -1)
				{
				CalError::printLastError();
				return false;
				}
			}
		else if(strKey == "physicsmesh")
			{
			strData = f_Path + strData;

			// load core mesh
			std::cout << "Loading physics mesh '" << strData << "'..." << std::endl;
			//m_Cloth.push_back(Digi::DigiMassCore::instance()->acCreateClothMesh(strData));
			}
		else if(strKey == "material")
			{
			strData = f_Path + strData;

			// load core material
			std::cout << "Loading material '" << strData << "'..." << std::endl;
			if(m_calCoreModel->loadCoreMaterial(strData) == -1)
				{
				printf("ERROR material %s not found\n", strData.c_str());
				CalError::printLastError();
				return false;
				}
			}
		else
			{
			// everything else triggers an error message, but is ignored
			std::cerr << strFilename << "(" << line << "): Invalid syntax." << std::endl;
			}
		}

	m_calCoreModel->getCoreSkeleton()->calculateBoundingBoxes(m_calCoreModel);
	//m_calCoreModel->getCoreSkeleton()->calculateBoundingBoxes(m_calCoreModel);

	// explicitely close the file
	file.close();

	return true;
}

void unDataMesh::clone_struct( unAvatar * unavatar )
{
	//Generate Cloned Mesh Structure
	unavatar->m_calModel = new CalModel(this->m_calCoreModel);
	unavatar->m_calHardwareModel = this->m_calHardwareModel;

	int i;
	for(i=0; i<6; i++)
		unavatar->m_bufferObject[i] = this->m_bufferObject[i];

	for(i=0; i<32; i++)
		unavatar->m_meshId[i] = this->m_meshId[i];

	for(i=0; i<32; i++)
		unavatar->m_textureId[i] = this->m_textureId[i];

	unavatar->m_meshCount = this->m_meshCount;
	unavatar->m_textureCount = this->m_textureCount;
	unavatar->m_lodLevel = this->m_lodLevel;

#pragma message("FIXME:::Add instance meshdata and investigate caching all mesh data")
//unavatar->modelData = new ModelData(unavatar->m_calCoreModel, unavatar->m_calModel);
}

void unDataMesh::clone_struct_physics( unAvatar * unavatar )
{
	//Generate Cloned Mesh Structure
	unavatar->m_calModel = new CalModel(this->m_calCoreModel);
	unavatar->m_calHardwareModel = this->m_calHardwareModel;

	int i;
	for(i=0; i<6; i++)
		unavatar->m_bufferObject[i] = this->m_bufferObject[i];

	for(i=0; i<32; i++)
		unavatar->m_meshId[i] = this->m_meshId[i];

	for(i=0; i<32; i++)
		unavatar->m_textureId[i] = this->m_textureId[i];

	unavatar->m_meshCount = this->m_meshCount;
	unavatar->m_textureCount = this->m_textureCount;
	unavatar->m_lodLevel = this->m_lodLevel;

#if 1
	unavatar->m_calModel->getMixer()->ClearAnim();
#else
	unavatar->BlendAnim(19, 0.3, 1);
#endif

	// get the skeleton we need to update
	CalSkeleton *pSkeleton;
	pSkeleton = unavatar->m_calModel->getSkeleton();

	// clear the skeleton state
#if 0
	pSkeleton->clearState();
#endif

	// get the bone vector of the skeleton
	std::vector<CalBone *>& vectorBone = pSkeleton->getVectorBone();

	unavatar->m_BoneStructure = Digi::DigiMassCore::instance()->acSkeletonPose(unavatar->m_calModel->getSkeleton(), vectorBone);

	// lock the skeleton state
	pSkeleton->lockState();

	// let the skeleton calculate its final state
	pSkeleton->calculateState();

#pragma message("FIXME:::Add instance meshdata and investigate caching all mesh data")
//unavatar->modelData = new ModelData(unavatar->m_calCoreModel, unavatar->m_calModel);
}

int unDataMesh::acMake(void)
{
	const Alloc_Animation alloc_animation (m_unSegment->get_segment_manager());
	const Alloc_CoreTrack alloc_track (m_unSegment->get_segment_manager());
	const Alloc_KeyFrame alloc_keyframe (m_unSegment->get_segment_manager());

	std::string i_Ident = acIdentGen("UNAnimation");
	m_UNvectorAnim = m_unSegment->construct<UN_Vector_Animation>(i_Ident.c_str())(alloc_animation);

	for(int i_iteranim = 0; i_iteranim < m_calCoreModel->m_vectorCoreAnimation.size(); i_iteranim++)
		{
		CalCoreAnimationPack i_Animation;

		std::string i_IdentTrack = acIdentGen("Track", true);
		i_Animation.m_UNlistCoreTrack = m_unSegment->construct<UN_List_CoreTrack>(i_IdentTrack.c_str())(alloc_track);

		std::list<CalCoreTrack*>::iterator trackiterator;

		trackiterator = m_calCoreModel->m_vectorCoreAnimation[i_iteranim]->m_listCoreTrack.begin();

		while(trackiterator != m_calCoreModel->m_vectorCoreAnimation[i_iteranim]->m_listCoreTrack.end())
			{
			CalCoreTrackPack i_Track;

			i_Track.m_coreBoneId = (*trackiterator)->getCoreBoneId();

			std::string i_IdentKeyFrame = acIdentGen("KeyFrame", true);
			i_Track.m_UNkeyframes = m_unSegment->construct<UN_Vector_KeyFrame>(i_IdentKeyFrame.c_str())(alloc_keyframe);

			for(int i_iterkey = 0; i_iterkey < (*trackiterator)->m_keyframes.size(); i_iterkey++)
				{
				CalCoreKeyframe *i_SourceKeyframe = (*trackiterator)->m_keyframes[i_iterkey];
				CalCoreKeyframePack i_Keyframe;

				i_Keyframe.m_time = i_SourceKeyframe->m_time;
				i_Keyframe.m_translation = i_SourceKeyframe->m_translation;
				i_Keyframe.m_rotation = i_SourceKeyframe->m_rotation;

				i_Track.m_UNkeyframes->push_back(i_Keyframe);
				}

			i_Animation.m_UNlistCoreTrack->push_back(i_Track);
			trackiterator++;
			}

		CalCoreAnimation *i_SourceAnim = m_calCoreModel->m_vectorCoreAnimation[i_iteranim].get();

		i_Animation.m_duration = i_SourceAnim->m_duration;

#if 0
		i_Animation.m_name = i_SourceAnim->m_name;
		i_Animation.m_filename = i_SourceAnim->m_filename;
#endif

#if 0	// Not Needed
		std::list<CalCoreTrack *> m_listCoreTrack;
		UN_List_CoreTrack *m_UNlistCoreTrack;
		std::vector<CallbackRecord> m_listCallbacks;
#endif

		m_UNvectorAnim->push_back(i_Animation);
		}

	return ext_NomDataMesh;
}