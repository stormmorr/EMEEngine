/*

    unMeshStatic
    Copyright OSIREM (C) 2007
	WEB - www.osirem.com  svn://62.44.82.8/unification

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

#include "unMeshStatic.h"

#include "cal3d.h"

#include "tgacal3d.h"

#include <fstream>

#if 0
#include "tgacal3d.h"

#include <windows.h>				// Header File For Windows
#include <stdio.h>					// Header File For Standard Input/Output

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

// EGL includes
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#endif

#include "../Utility/unConsole.h"

std::string m_TruePath = "Assets//Mesh//";

extern std::string m_MaterialPath;

//----------------------------------------------------------------------------//
// Constructors                                                               //
//----------------------------------------------------------------------------//

unMeshStatic::unMeshStatic()
{
  m_lodLevel = 1.0f;
  m_vertexCount = 0;
  m_faceCount = 0;
  maxoctreedepth = 5;
  m_scale = 1;
  m_flip = false;
}

unMeshStatic::unMeshStatic(unMeshStatic *i_mesh)
{

}

//----------------------------------------------------------------------------//
// Destructor                                                                 //
//----------------------------------------------------------------------------//

unMeshStatic::~unMeshStatic()
{
}

//----------------------------------------------------------------------------//
// Mesh Loading
//----------------------------------------------------------------------------//

int readIntStatic( std::ifstream *file )
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

bool unMeshStatic::loadCoreMesh(const std::string& strFilename)
{
  // open the file
  std::string i_FullFilename = m_TruePath + strFilename;
  std::ifstream file;
  file.open(i_FullFilename.c_str(), std::ios::in | std::ios::binary);

  // make sure it opened properly
  if(!file)
	{
	printf("ERROR:::Load Static Mesh:::File not found %s\n", i_FullFilename.c_str());
    return false;
	}

  //make a new stream data source and use it to load the mesh
  QunStreamSource streamSrc( file );

  // check if this is a valid file
  char magic[4];
  if(!streamSrc.readBytes(&magic[0], 4) || (memcmp(&magic[0], Qun::MESH_FILE_MAGIC, 4) != 0))
    {
	printf("ERROR:::Load Static Mesh:::Invalid file format\n");
    return false;
	}

  // check if the version is compatible with the library
  int version;
  if(!streamSrc.readInteger(version) || (version < Qun::EARLIEST_COMPATIBLE_FILE_VERSION) || (version > Qun::CURRENT_FILE_VERSION))
    {
	printf("ERROR:::Load Static Mesh:::Incompatible file version\n");
    return false;
	}

  // get the number of submeshes
  int submeshCount;
  if(!streamSrc.readInteger(submeshCount))
    {
	printf("ERROR:::Load Static Mesh:::Invalid file format\n");
    return false;
	}

  // load all core submeshes
  for(int submeshId = 0; submeshId < submeshCount; ++submeshId)
    {
    // load the core submesh
	//pMesh *i_mesh;
	//i_mesh = new pMesh;
	
	//i_mesh->load_cal3d(i_FullFilename, streamSrc, maxoctreedepth, m_scale, m_flip);

	//i_mesh->nmat = m_texdata.size() / 2;
	//i_mesh->set_nummat(i_mesh->nmat);

	int matcounter = 0;
	for( unsigned int i = 0; i < 0/*i_mesh->nmat*/; i++ )
		{
		//i_mesh->mat[i].diffuse = pVector(1,1,1);
		//i_mesh->mat[i].specular = pVector(1,1,1);
		//i_mesh->mat[i].selfillum = pVector(1,1,1);
		//i_mesh->mat[i].skincolor = pVector(1,1,1);
		//i_mesh->mat[i].opacity = 1;
		//i_mesh->mat[i].reflection = 1;
		//i_mesh->mat[i].refraction = 1;
		//i_mesh->mat[i].bump = 1;
		//i_mesh->mat[i].envscale = 1;
		//i_mesh->mat[i].flags = 1;

		//i_mesh->mat[i].texname.read(fp);
		//i_mesh->mat[i].texnormalname.read(fp);
		//i_mesh->mat[i].texselfillumname.read(fp);

		//i_mesh->mat[i].texid = m_texdata[matcounter];
		//i_mesh->mat[i].texnormalid = m_texdata[matcounter + 1];
		//i_mesh->mat[i].texselfillumid=-1;

#if 0
		if (ver>=P3D_FILEVER+7)
			{
			int i,j;
			pRenderPass rp;
			fp.read(&j,sizeof(int));
			for( i=0;i<j;i++ )
				{
				rp.read(fp,ver);
				passes.add(rp);
				}
			}
#endif

		matcounter += 2;
		}

	//m_submesh.add(i_mesh);
    }

  //close the file
  file.close();

  return true;
}

GLuint unMeshStatic::LoadTexture(const std::string& strFilename)
{
	GLuint textureId=0;

	std::string i_FullFilename = m_TruePath + strFilename;

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
		int width = readIntStatic(&file);     
		int height = readIntStatic(&file);     
		int depth = readIntStatic(&file);     

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
			printf("ERROR:::unMeshStatic::LoadTexture File not found %s\n", i_FullFilename.c_str());
			for(;;) {}
			return 0;
			}

		if(Tga->Bpp()!=32)
			{
			Tga->Release();
			printf("ERROR:::unMeshStatic::LoadTexture Tga->Bpp() != 32 %s\n", i_FullFilename.c_str());
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

//----------------------------------------------------------------------------//
// Create the unMeshStatic														  //
//----------------------------------------------------------------------------//

bool unMeshStatic::onCreate(std::string i_filename)
{
  bool bModelConfiguration;
  bModelConfiguration = false;

  if(!parseModelConfiguration(i_filename)) return false;
  else bModelConfiguration = true;


  // make one material thread for each material
  // NOTE: this is not the right way to do it, but this viewer can't do the right
  // mapping without further information on the model etc., so this is the only
  // thing we can do here.
#if 0
  int materialId;
  for(materialId = 0; materialId < m_calCoreModel->getCoreMaterialCount(); materialId++)
  {
    // create the a material thread
    m_calCoreModel->createCoreMaterialThread(materialId);

    // initialize the material thread
    m_calCoreModel->setCoreMaterialId(materialId, 0, materialId);
  }

  m_qunModel = new QunModel(m_calCoreModel);
#endif

  return true;
}

//----------------------------------------------------------------------------//
// Shut the unMeshStatic down                                                       //
//----------------------------------------------------------------------------//

void unMeshStatic::acShutdown()
{
	int i_iter;
	for(i_iter = 0; i_iter < m_texdata.size(); i_iter++)
		{
		glDeleteTextures(1, &m_texdata[i_iter]);
		}

	//for(i_iter = 0; i_iter < m_submesh.num; i_iter++)
	//	{
	//	m_submesh[i_iter]->reset();
	//	}
}

//----------------------------------------------------------------------------//
// Parse the configuration file and load the whole model                      //
//----------------------------------------------------------------------------//

bool unMeshStatic::parseModelConfiguration(const std::string& strFilename)
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
	if(strKey == "flip")
    {
      // set rendering scale factor
      m_flip = atoi(strData.c_str());
	  m_flip = true;
    }
    else if(strKey == "scale")
    {
      // set rendering scale factor
      m_scale = atof(strData.c_str());
    }
#if 0	//FIXME: Add skeleton loading and skeleton
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
#endif
    else if(strKey == "mesh")
    {
      // load core mesh
      std::cout << "MeshStatic::: Loading mesh '" << strData << "'..." << std::endl;
	  if(m_calCoreModel->loadCoreMesh(strData) == -1)
	  {
		  QunError::printLastError();
		  return false;
	  }
    }
    else if(strKey == "material")
    {
      // load core material
	  std::cout << "ERROR:: Loading Cal3d material not yet implemented '" << strData << "'..." << std::endl;
      return false;
    }
	else if(strKey == "clearmaterial")
    {
      // load core material
	  printf("clear material bank\n");
	  m_texdata.clear();
    }
	else if(strKey == "meshmaterial")
    {
      // load core material
	  std::cout << "MeshStatic::: Loading material '" << strData << "'..." << std::endl;
	  // load the texture from the file
	  m_texdata.push_back(LoadTexture(strData));
    }
	else if(strKey == "meshnormmaterial")
    {
      // load core material
	  std::cout << "MeshStatic::: Loading material '" << strData << "'..." << std::endl;
	  // load the texture from the file
	  m_texnormdata.push_back(LoadTexture(strData));
    }
    else
    {
      // everything else triggers an error message, but is ignored
      std::cerr << strFilename << "(" << line << "): Invalid syntax." << std::endl;
    }
  }

  // explicitely close the file
  file.close();

  return true;
}

bool unMeshStatic::acInit(void)
{
	// load all textures and store the opengl texture id in the corresponding map in the material
	int materialId;
	for(materialId = 0; materialId < m_calCoreModel->getCoreMaterialCount(); materialId++)
		{
		// get the core material
		QunCoreMaterial *qunCoreMaterial;
		qunCoreMaterial = m_calCoreModel->getCoreMaterial(materialId);

		// loop through all maps of the core material
		int mapId;
		for(mapId = 0; mapId < qunCoreMaterial->getMapCount(); mapId++)
			{
			// get the filename of the texture
			std::string strFilename;
			strFilename = qunCoreMaterial->getMapFilename(mapId);

			// load the texture from the file
			GLuint textureId;
			textureId = acLoadTexture(strFilename);

			// store the opengl texture id in the user data of the map
			qunCoreMaterial->setMapUserData(mapId, (Qun::UserData)textureId);
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

int readInto( std::ifstream *file )
{
	int x = 0;

	for(int i = 0; i < 32; i+=8) 
		{
		char c;
		file->read ( &c, 1 );
		x += c << i;
 		}

 	return x;
}

GLuint unMeshStatic::acLoadTexture(const std::string& strFilename)
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
		int width = readInto(&file);     
		int height = readInto(&file);     
		int depth = readInto(&file);     

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

bool unMeshStatic::acSetBuffers(void)
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

unsigned int unMeshStaticBank::acAddInstance(unsigned int i_VectorIndex, int i_x, int i_y, int i_z)
{
	unMeshStaticInstance *i_Instance = new unMeshStaticInstance();
	i_Instance->x = i_x;
	i_Instance->y = i_y;
	i_Instance->z = i_z;
	m_MeshInstance.push_back(i_Instance);
	return m_MeshInstance.size() - 2;
}

unMeshStaticBank* unMeshStaticBank::s_instance = 0;
unMeshStaticBank* unMeshStaticBank::instance()
{
  return s_instance;
}

unMeshStaticBank::unMeshStaticBank()
{
}

//----------------------------------------------------------------------------//