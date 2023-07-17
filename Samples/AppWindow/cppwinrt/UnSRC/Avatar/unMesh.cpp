/*

    unMesh - Mesh
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

#include "tgacal3d.h"

#if 0
#include <windows.h>
#include <stdio.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

// EGL includes
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#endif

//#include "../../DigitalMass/Source/Digi/DigiMass.h"
//#include "../../DigitalMass/Source/Digi/Cloth.h"

//#include "PxPhysics.h"
//#include "PxCooking.h"

//#include "boost/interprocess/managed_shared_memory.hpp"
//#include "boost/interprocess/containers/vector.hpp"
//#include "boost/interprocess/containers/list.hpp"
//#include "boost/interprocess/allocators/allocator.hpp"

std::string m_MaterialPath = "Assets//Avatar//Material//";

////////////////////////////////////////////////////////////////////////////////
// Constructors ////////////////////////////////////////////////////////////////

unMesh::unMesh()
{
  m_calCoreModel = new QunCoreModel("dummy");

  m_lodLevel = 1.0f;
  m_vertexCount = 0;
  m_faceCount = 0;
}

/*unMesh::unMesh(unMesh *i_mesh)
{
	this->m_calCoreModel = i_mesh->m_calCoreModel;
	this->m_qunModel = i_mesh->m_qunModel;
	this->m_calHardwareModel = i_mesh->m_calHardwareModel;

	this->m_lodLevel = i_mesh->m_lodLevel;

	int i;
	for(i=0; i<6; i++)
		this->m_bufferObject[i] = i_mesh->m_bufferObject[i];
}*/

////////////////////////////////////////////////////////////////////////////////
// Destructor //////////////////////////////////////////////////////////////////

unMesh::~unMesh()
{
	////// Clean Renderer Textures
	QunCoreMaterial *pCoreMaterial;
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

	delete m_calCoreModel;
	delete m_qunModel;
	delete m_calHardwareModel;

	//glDeleteBuffersARB(6, m_bufferObject);
}

void unMesh::acShutdown(void)
{
	////// Clean Renderer Textures
	QunCoreMaterial *pCoreMaterial;
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

	delete m_calCoreModel;
	delete m_qunModel;
	delete m_calHardwareModel;

	//glDeleteBuffersARB(6, m_bufferObject);
}

////////////////////////////////////////////////////////////////////////////////
// Load and create a texture from a given file /////////////////////////////////

int readInt( std::ifstream *file )
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

GLuint unMesh::acLoadTexture(const std::string& strFilename)
{
	GLuint textureId=0;

	std::string i_FullFilename = m_MaterialPath + strFilename;

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
		int width = readInt(&file);     
		int height = readInt(&file);     
		int depth = readInt(&file);     

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
			printf("ERROR:::unMesh::acLoadTexture File not found %s\n", i_FullFilename.c_str());
			for(;;) {}
			return 0;
			}

		if(Tga->Bpp()!=32)
			{
			Tga->Release();
			printf("ERROR:::unMesh::acLoadTexture Tga->Bpp() != 32 %s\n", i_FullFilename.c_str());
			return 0;
			}

		//Flip texture
		int width = Tga->GetSizeX();
		int height = Tga->GetSizeY();

#if 0
		int depth = Tga->Bpp() / 8;    
#endif

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
// Create the unMesh ///////////////////////////////////////////////////////////

bool unMesh::acCreate(std::string i_filename)
{
	///////---- Parse Model Configuration File ----///////
	if(!acParseConfiguration(i_filename))
		{
		std::cerr << "unMesh::: No model configuration file given." << std::endl;
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

	m_qunModel = new QunModel(m_calCoreModel);
	
	return true;
}

////////////////////////////////////////////////////////////////////////////////
// Initialize //////////////////////////////////////////////////////////////////

bool unMesh::acInit()
{
	// load all textures and store the opengl texture id in the corresponding map in the material
	int materialId;
	for(materialId = 0; materialId < m_calCoreModel->getCoreMaterialCount(); materialId++)
		{
		// get the core material
		QunCoreMaterial *pCoreMaterial;
		pCoreMaterial = m_calCoreModel->getCoreMaterial(materialId);

		// loop through all maps of the core material
		int mapId;
		for(mapId = 0; mapId < pCoreMaterial->getMapCount(); mapId++)
			{
			// get the filename of the texture
			std::string strFilename;
			strFilename = pCoreMaterial->getMapFilename(mapId);

			// load the texture from the file
			GLuint textureId;
			textureId = acLoadTexture(strFilename);

			// store the opengl texture id in the user data of the map
			pCoreMaterial->setMapUserData(mapId, (Qun::UserData)textureId);
			}
		}

	// attach all meshes to the model
	int meshId;
	for(meshId = 0; meshId < m_calCoreModel->getCoreMeshCount(); meshId++)
		{
		m_qunModel->attachMesh(meshId);
		}

	// set the material set of the whole model
	m_qunModel->setMaterialSet(0);

	//glewInit();

	/*if (!GLEW_ARB_vertex_program)
		{
		std::cerr << "Error ARB_vertex_program OpenGL extension not found." << std::endl;
		return false;
		}

	if (!GLEW_ARB_vertex_buffer_object)
		{
		std::cerr << "Error ARB_vertex_buffer_object OpenGL extension not found." << std::endl;
		return false;
		}*/

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

bool unMesh::acSetBuffers()
{
	float *pVertexBuffer = (float*)malloc(30000*3*sizeof(float));
	float *pWeightBuffer = (float*)malloc(30000*4*sizeof(float));
	float *pMatrixIndexBuffer = (float*)malloc(30000*4*sizeof(float));
	float *pNormalBuffer = (float*)malloc(30000*3*sizeof(float));
	float *pTexCoordBuffer = (float*)malloc(30000*2*sizeof(float));
	QunIndex *pIndexBuffer = (QunIndex*)malloc(50000*3*sizeof(QunIndex));

	if(pVertexBuffer==NULL || pWeightBuffer == NULL
		|| pMatrixIndexBuffer==NULL || pNormalBuffer == NULL
		|| pTexCoordBuffer==NULL || pIndexBuffer == NULL)
		{
		return false;
		}	  

	m_calHardwareModel = new QunHardwareModel(m_calCoreModel);
	m_calHardwareModel->setVertexBuffer((char*)pVertexBuffer,3*sizeof(float));
	m_calHardwareModel->setNormalBuffer((char*)pNormalBuffer,3*sizeof(float));
	m_calHardwareModel->setWeightBuffer((char*)pWeightBuffer,4*sizeof(float));
	m_calHardwareModel->setMatrixIndexBuffer((char*)pMatrixIndexBuffer,4*sizeof(float));
	m_calHardwareModel->setTextureCoordNum(1);
	m_calHardwareModel->setTextureCoordBuffer(0,(char*)pTexCoordBuffer,2*sizeof(float));
	m_calHardwareModel->setIndexBuffer(pIndexBuffer);

	////// Load Hardware Model with maximum 29 Bones //////
	m_calHardwareModel->load( 0, 0, 29);

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
		}

	// We use ARB_vertex_buffer_object extension,
	// it provide better performance

	glGenBuffers(6, m_bufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[0]);
	glBufferData(GL_ARRAY_BUFFER, m_calHardwareModel->getTotalVertexCount() * 3 * sizeof(float), (const void*)pVertexBuffer, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[1]);
	glBufferData(GL_ARRAY_BUFFER, m_calHardwareModel->getTotalVertexCount() * 4 * sizeof(float), (const void*)pWeightBuffer, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[2]);
	glBufferData(GL_ARRAY_BUFFER, m_calHardwareModel->getTotalVertexCount() * 3 * sizeof(float), (const void*)pNormalBuffer, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[3]);
	glBufferData(GL_ARRAY_BUFFER, m_calHardwareModel->getTotalVertexCount() * 4 * sizeof(float), (const void*)pMatrixIndexBuffer, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[4]);
	glBufferData(GL_ARRAY_BUFFER, m_calHardwareModel->getTotalVertexCount() * 2 * sizeof(float), (const void*)pTexCoordBuffer, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferObject[5]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_calHardwareModel->getTotalFaceCount() * 3 * sizeof(QunIndex), (const void*)pIndexBuffer, GL_STATIC_DRAW);

	/**glGenBuffersARB(6, m_bufferObject);

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
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_calHardwareModel->getTotalFaceCount()*3*sizeof(QunIndex),(const void*)pIndexBuffer, GL_STATIC_DRAW_ARB);*/

	free(pVertexBuffer);
	free(pWeightBuffer);
	free(pNormalBuffer);
	free(pMatrixIndexBuffer);
	free(pIndexBuffer);

	return true;
}

////////////////////////////////////////////////////////////////////////////////
// Parse the configuration file and load the whole model ///////////////////////

bool unMesh::acParseConfiguration(const std::string& strFilename)
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

		// handle the model creation
		if(strKey == "scale")
			{
			// set rendering scale factor
			m_scale = atof(strData.c_str());
			}
		else if(strKey == "skeleton")
			{
			// load core skeleton
			std::cout << "Loading skeleton '" << strData << "'..." << std::endl;
			if(!m_calCoreModel->loadCoreSkeleton(strData))
				{
				QunError::printLastError();
				return false;
				}
			}
		else if(strKey == "animation")
			{
			// load core animation
			std::cout << "Loading animation '" << strData << "'..." << std::endl;
			if(m_calCoreModel->loadCoreAnimation(strData) == -1)
				{
				QunError::printLastError();
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
			// load core mesh
			std::cout << "Loading mesh '" << strData << "'..." << std::endl;
			if(m_calCoreModel->loadCoreMesh(strData) == -1)
				{
				QunError::printLastError();
				return false;
				}
			}
		else if(strKey == "physicsmesh")
			{
			// load core mesh
			std::cout << "Loading physics mesh '" << strData << "'..." << std::endl;
			//m_Cloth.push_back(Digi::DigiMassCore::instance()->acCreateClothMesh(strData));
			}
		else if(strKey == "material")
			{
			// load core material
			std::cout << "Loading material '" << strData << "'..." << std::endl;
			if(m_calCoreModel->loadCoreMaterial(strData) == -1)
				{
				printf("ERROR material %s not found\n", strData.c_str());
				QunError::printLastError();
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

	// explicitely close the file
	file.close();

	return true;
}

void unMesh::clone_struct( unAvatar * unavatar )
{
	//Generate Cloned Mesh Structure
	unavatar->m_qunModel = new QunModel(this->m_calCoreModel);
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

	unavatar->m_rebuild = 0;

#pragma message("FIXME:::Add instance meshdata and investigate caching all mesh data")
//unavatar->modelData = new ModelData(unavatar->m_calCoreModel, unavatar->m_qunModel);
}

void unMesh::clone_struct_physics( unAvatar * unavatar )
{
	//Generate Cloned Mesh Structure
	unavatar->m_qunModel = new QunModel(this->m_calCoreModel);
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
	unavatar->m_qunModel->getMixer()->ClearAnim();
#else
	unavatar->BlendAnim(19, 0.3, 1);
#endif

#if 1
	// get the skeleton we need to update
	QunSkeleton *pSkeleton;
	pSkeleton = unavatar->m_qunModel->getSkeleton();

	// clear the skeleton state
#if 0
	pSkeleton->clearState();
#endif

	// get the bone vector of the skeleton
	std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

	//unavatar->m_BoneStructure = Digi::DigiMassCore::instance()->acSkeletonPose(unavatar->m_qunModel->getSkeleton(), vectorBone);

	// lock the skeleton state
	pSkeleton->lockState();

	// let the skeleton calculate its final state
	pSkeleton->calculateState();
#endif

	unavatar->m_rebuild = 0;

#pragma message("FIXME:::Add instance meshdata and investigate caching all mesh data")
//unavatar->modelData = new ModelData(unavatar->m_calCoreModel, unavatar->m_qunModel);
}