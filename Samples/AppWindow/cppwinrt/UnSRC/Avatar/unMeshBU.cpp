/*

    unMesh
    Copyright SomptingSOFT/Max Lawlor (C) 2007
	SomptingSOFT Portal www.stss.co.nr

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

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

#include <windows.h>				// Header File For Windows
#include <stdio.h>					// Header File For Standard Input/Output
#include <gl/glew.h>
#include <gl/gl.h>					// Header File For The OpenGL32 Library
#include <gl/glu.h>					// Header File For The GLu32 Library

#pragma message("FIXME:::Consider moving these includes to header file to allow bank storage")
#include "../../DigitalMass/Source/DigiMass.h"
#if 0
#include "../../DigitalMass/Source/Geometry/unTerrainCell.h"
#endif
#include "../../DigitalMass/Source/Cloth.h"

#include "NxPhysics.h"
#include "NxCooking.h"

#if 0
#include "../Utility/datatypes.h"
#endif

int i_TempCounter = 0;

std::string m_MaterialPath = "Avatar//Material//";

////////////////////////////////////////////////////////////////////////////////
// Constructors ////////////////////////////////////////////////////////////////

unMesh::unMesh()
{
  //m_calCoreModel.Acquire("CalPlacemarker");
  //m_calCoreModel = new CalCoreModel();
  //m_calCoreModel.Acquire("CalMeshDummy");
  m_calCoreModel = new CalCoreModel("dummy");

  m_lodLevel = 1.0f;
  m_vertexCount = 0;
  m_faceCount = 0;
}

void unMesh::acAllocate(void)
{
  //m_calCoreModel.Acquire("CalPlacemarker");
  //m_calCoreModel = new CalCoreModel();
  //m_calCoreModel.Acquire("CalMeshDummy");
  //m_calCoreModel = new CalCoreModel("dummy");
}

unMesh::unMesh(unMesh *i_mesh)
{
	int i;
	this->m_calCoreModel = i_mesh->m_calCoreModel;
	this->m_calModel = i_mesh->m_calModel;
	this->m_calHardwareModel = i_mesh->m_calHardwareModel;

	this->m_lodLevel = i_mesh->m_lodLevel;

	for(i=0; i<6; i++)
		this->m_bufferObject[i] = i_mesh->m_bufferObject[i];
}

////////////////////////////////////////////////////////////////////////////////
// Destructor //////////////////////////////////////////////////////////////////

unMesh::~unMesh()
{
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

GLuint unMesh::LoadTexture(const std::string& strFilename)
{
	GLuint textureId=0;

	std::string i_FullFilename = m_MaterialPath + strFilename;

	if(stricmp(strrchr(i_FullFilename.c_str(),'.'),".raw")==0)
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
	else if(stricmp(strrchr(i_FullFilename.c_str(),'.'),".tga")==0)  
		{
		CTga *Tga;
		Tga = new CTga();
		if(Tga->ReadFile(i_FullFilename.c_str())==0)
			{
			Tga->Release();
			printf("ERROR:::unMesh::LoadTexture File not found %s\n", i_FullFilename.c_str());
			for(;;) {}
			return 0;
			}

		if(Tga->Bpp()!=32)
			{
			Tga->Release();
			printf("ERROR:::unMesh::LoadTexture Tga->Bpp() != 32 %s\n", i_FullFilename.c_str());
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
// Create the unMesh ///////////////////////////////////////////////////////////

bool unMesh::acCreate(std::string i_filename)
{
	bool bModelConfiguration;
	bModelConfiguration = false;

	if(!ParseModelConfiguration(i_filename)) return false;
	else bModelConfiguration = true;

	// check if we have successfully loaded a model configuration
	if(!bModelConfiguration)
		{
		std::cerr << "No model configuration file given." << std::endl;
		return false;
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

	//m_calModel.Acquire("mcalMode");
	//m_calModel->acAllocate(m_calCoreModel);
	m_calModel = new CalModel(m_calCoreModel);
	//m_calModel->acAllocate(m_calCoreModel);
	
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
		CalCoreMaterial *pCoreMaterial;
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
			textureId = LoadTexture(strFilename);

			// store the opengl texture id in the user data of the map
			pCoreMaterial->setMapUserData(mapId, (Cal::UserData)textureId);
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
	// set initial animation state
	if(m_calCoreModel->getCoreAnimationCount() > 0)
		{
		m_currentAnimationId = 0;
		m_leftAnimationTime = m_calCoreModel->getCoreAnimation(m_currentAnimationId)->getDuration() - m_blendTime;
		if(m_calCoreModel->getCoreAnimationCount() > 1)
			{
			m_calModel->getMixer()->executeAction(m_currentAnimationId, 0.0f, m_blendTime);
			}
		else
			{
			m_calModel->getMixer()->blendCycle(m_currentAnimationId, 1.0f, 0.0f);
			}
		}
	else
		{
		m_currentAnimationId = -1;
		m_leftAnimationTime = -1.0f;
		}
#endif

	//m_calModel->disableInternalData();

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

	if(!LoadBufferObject())
		{
		std::cerr << "Error loading vertex buffer object." << std::endl;
		return false;
		}

	// Finished
	std::cout << "Initialization Finished" << std::endl;
	std::cout << std::endl;

	return true;
}


bool unMesh::LoadBufferObject()
{
	float *pVertexBuffer = (float*)malloc(30000*3*sizeof(float));
	float *pWeightBuffer = (float*)malloc(30000*4*sizeof(float));
	float *pMatrixIndexBuffer = (float*)malloc(30000*4*sizeof(float));
	float *pNormalBuffer = (float*)malloc(30000*3*sizeof(float));
	float *pTexCoordBuffer = (float*)malloc(30000*2*sizeof(float));
	CalIndex *pIndexBuffer = (CalIndex*)malloc(50000*3*sizeof(CalIndex));

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

	free(pVertexBuffer);
	free(pWeightBuffer);
	free(pNormalBuffer);
	free(pMatrixIndexBuffer);
	free(pIndexBuffer);

	return true;
}

////////////////////////////////////////////////////////////////////////////////
// Close unMesh ////////////////////////////////////////////////////////////////

void unMesh::acShutdown()
{
	delete m_calHardwareModel;
	delete m_calModel;
	delete m_calCoreModel;

	glDeleteBuffersARB(6, m_bufferObject);
}

////////////////////////////////////////////////////////////////////////////////
// Parse the configuration file and load the whole model ///////////////////////

bool unMesh::ParseModelConfiguration(const std::string& strFilename)
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
				CalError::printLastError();
				return false;
				}
			}
		else if(strKey == "animation")
			{
			// load core animation
			std::cout << "Loading animation '" << strData << "'..." << std::endl;
			if(m_calCoreModel->loadCoreAnimation(strData) == -1)
				{
				CalError::printLastError();
				return false;
				}
			}
		else if(strKey == "mesh")
			{
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
			// load core mesh
			std::cout << "Loading physics mesh '" << strData << "'..." << std::endl;
			m_Cloth.push_back(Digi::DigiMassCore::instance()->acCreateClothMesh(strData));
			}
		else if(strKey == "material")
			{
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

void unMesh::clone_struct( unAvatar * unavatar )
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

void unMesh::clone_struct_physics( unAvatar * unavatar )
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