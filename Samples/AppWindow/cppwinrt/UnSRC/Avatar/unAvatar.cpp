/*

	unAvatar
	Copyright OSIREM (C) 2007
	WEB - www.osirem.com SVN - svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

/////---- Include Headers ----/////

#if defined(_MSC_VER) && _MSC_VER <= 0x0600
#pragma warning(disable : 4786)
#endif

#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"
#include <stdlib.h>

#include "Q-Includes.h"
#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-WorldEffects.h"
#include "Q-WE-PntSprite.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-WE-CloudControl.h"
#include "Q-Structs.h"
#include "Q-WE-MeleeHits.h"
#include "Q-CORE-Avatar.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"
#include "Q-WE-EnergyMatrix.h"
#include "Q-ENE-EnergyTypes.h"
#include "Q-WE-BulletSystem.h"
#include "Q-AI-NNbot.h"

#include "unAvatar.h"

//*#include "../../DigitalMass/Source/Digi/DigiMass.h"

#if defined(ENABLE_PX_PHYSICS)
#include "../../DigitalMass/Source/Digi/Cloth.h"

#include "PxPhysics.h"
#include "PxCooking.h"
#endif

//*PxReal degToRadians(float a) { return (PxReal)a / 57.29577951308232286465; };

/////---- Constructors ----/////

unAvatar::unAvatar()
{
  m_rebuild = 1;

  m_calCoreModel = new QunCoreModel("dummy");

  m_meshCount = 0;
  m_renderScale = 1.0f;
  m_lodLevel = 1.0f;
  m_animtime = 0;

  // DEBUG-CODE
  Sphere.x = 0.0f;
  Sphere.y = 5.0f;
  Sphere.z = 45.0f;

  AnimNumber = 5;
  m_oldanim = 0;
  SmoothOn = 0;
  m_rotationy = 0;
  m_inx = m_iny = m_inz = 0;
  m_posx = m_posy = m_posz = 0;
  m_BoneStructure = -1;
  m_BoneState = 1;
}

/////---- Copy Constructor ----/////

unAvatar::unAvatar(const unAvatar&)
{
}

/////---- Destructor ----/////

unAvatar::~unAvatar()
{
	delete m_qunModel;
}

//----------------------------------------------------------------------------//
// Get the lod level of the mesh                                             //
//----------------------------------------------------------------------------//

float unAvatar::getLodLevel()
{
  return m_lodLevel;
}

//----------------------------------------------------------------------------//
// Get the render scale of the mesh                                          //
//----------------------------------------------------------------------------//

float unAvatar::getRenderScale()
{
  return m_renderScale;
}

//----------------------------------------------------------------------------//
// Get the animation state of the mesh                                       //
//----------------------------------------------------------------------------//

int unAvatar::getState()
{
  return m_state;
}

//----------------------------------------------------------------------------//
// Render the skeleton of the mesh                                           //
//----------------------------------------------------------------------------//

void unAvatar::acRenderSkeleton()
{
	// draw the bone lines
	float lines[1024][2][3];
	int nrLines;
	nrLines =  m_qunModel->getSkeleton()->getBoneLines(&lines[0][0][0]);
	//nrLines = m_qunModel->getSkeleton()->getBoneLinesStatic(&lines[0][0][0]);

	glLineWidth(3.0f);
	//glColor3f(1.0f, 1.0f, 1.0f);
	////*glBegin(GL_LINES);
	int currLine;
	for(currLine = 0; currLine < nrLines; currLine++)
		{
		//glVertex3f(lines[currLine][0][0], lines[currLine][0][1], lines[currLine][0][2]);
		//glVertex3f(lines[currLine][1][0], lines[currLine][1][1], lines[currLine][1][2]);
		}
	////*glEnd();
	glLineWidth(1.0f);

	// draw the bone points
	float points[1024][3];
	int nrPoints;
	nrPoints =  m_qunModel->getSkeleton()->getBonePoints(&points[0][0]);
	//nrPoints = m_qunModel->getSkeleton()->getBonePointsStatic(&points[0][0]);

	//glPointSize(4.0f);
	////*glBegin(GL_POINTS);
	//glColor3f(0.0f, 0.0f, 1.0f);
	int currPoint;
	for(currPoint = 0; currPoint < nrPoints; currPoint++)
		{
		//glVertex3f(points[currPoint][0], points[currPoint][1], points[currPoint][2]);
		}
	////*glEnd();
	//glPointSize(1.0f);
}

//----------------------------------------------------------------------------//
// Render the bounding boxes of a mesh                                       //
//----------------------------------------------------------------------------//

void unAvatar::renderBoundingBox()
{  
	QunSkeleton *pQunSkeleton = m_qunModel->getSkeleton();

	std::vector<QunBone*> &vectorCoreBone = pQunSkeleton->getVectorBone();

	//glColor3f(0.0f, 1.0f, 0.0f);
	//glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	////*glBegin(GL_LINES);

	for(size_t boneId=0;boneId<vectorCoreBone.size();++boneId)
		{
		QunBoundingBox & calBoundingBox  = vectorCoreBone[boneId]->getBoundingBox();

		QunVector p[8];
		calBoundingBox.computePoints(p);

		//glColor3f(1.0f, 0.20f, 0.25f);

		//glVertex3f(p[0].x,p[0].y,p[0].z);
		//glVertex3f(p[1].x,p[1].y,p[1].z);

		//glVertex3f(p[0].x,p[0].y,p[0].z);
		//glVertex3f(p[2].x,p[2].y,p[2].z);

		//glVertex3f(p[1].x,p[1].y,p[1].z);
		//glVertex3f(p[3].x,p[3].y,p[3].z);

		//glVertex3f(p[2].x,p[2].y,p[2].z);
		//glVertex3f(p[3].x,p[3].y,p[3].z);

		//glVertex3f(p[4].x,p[4].y,p[4].z);
		//glVertex3f(p[5].x,p[5].y,p[5].z);

		//glVertex3f(p[4].x,p[4].y,p[4].z);
		//glVertex3f(p[6].x,p[6].y,p[6].z);

		//glVertex3f(p[5].x,p[5].y,p[5].z);
		//glVertex3f(p[7].x,p[7].y,p[7].z);

		//glVertex3f(p[6].x,p[6].y,p[6].z);
		//glVertex3f(p[7].x,p[7].y,p[7].z);

		//glVertex3f(p[0].x,p[0].y,p[0].z);
		//glVertex3f(p[4].x,p[4].y,p[4].z);

		//glVertex3f(p[1].x,p[1].y,p[1].z);
		//glVertex3f(p[5].x,p[5].y,p[5].z);

		//glVertex3f(p[2].x,p[2].y,p[2].z);
		//glVertex3f(p[6].x,p[6].y,p[6].z);

		//glVertex3f(p[3].x,p[3].y,p[3].z);
		//glVertex3f(p[7].x,p[7].y,p[7].z);  
		}

	////*glEnd();
}

void unAvatar::acRenderMeshSoft(bool bWireframe, bool bLight)
{
  // clear the vertex and face counters
  /*m_vertexCount = 0;
  m_faceCount = 0;

  // clear all the buffers
  glClearColor(0.0f, 0.0f, 0.3f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // set the projection transformation
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, (GLdouble)m_width / (GLdouble)m_height, m_scale * 50.0, m_scale * 1000.0);

  // set the mesh transformation
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // light attributes
  const GLfloat light_ambient[]  = { 0.3f, 0.3f, 0.3f, 1.0f };
  const GLfloat light_diffuse[]  = { 0.52f, 0.5f, 0.5f, 1.0f };
  const GLfloat light_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };

  // setup the light attributes
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

  // set the light position
  GLfloat lightPosition[] = { 0.0f, -1.0f, 1.0f, 1.0f };
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

  // set camera position
  glTranslatef(0.0f, 0.0f, -m_distance * m_scale);
  glRotatef(m_tiltAngle, 1.0f, 0.0f, 0.0f);
  glRotatef(m_twistAngle, 0.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, 0.0f, -90.0f * m_scale);
  glTranslatef(0.0f, 0.0f, m_camheight);*/

  // render the mesh
  //renderModel();

  // get the renderer of the mesh
  QunRenderer *pQunRenderer;
  pQunRenderer = m_qunModel->getRenderer();

  // begin the rendering loop
  if(!pQunRenderer->beginRendering()) return;

  // set wireframe mode if necessary
  if(bWireframe)
  {
   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  // set the global OpenGL states
  glEnable(GL_DEPTH_TEST);
  //glShadeModel(GL_SMOOTH);

  // set the lighting mode if necessary
  if(bLight)
  {
   // glEnable(GL_LIGHTING);
   // glEnable(GL_LIGHT0);
  }

  // we will use vertex arrays, so enable them
 // glEnableClientState(GL_VERTEX_ARRAY);
 // glEnableClientState(GL_NORMAL_ARRAY);

  // get the number of meshes
  int meshCount;
  meshCount = pQunRenderer->getMeshCount();

  // render all meshes of the mesh
  int meshId;
  for(meshId = 0; meshId < meshCount; meshId++)
  {
    // get the number of submeshes
    int submeshCount;
    submeshCount = pQunRenderer->getSubmeshCount(meshId);

    // render all submeshes of the mesh
    int submeshId;
    for(submeshId = 0; submeshId < submeshCount; submeshId++)
    {
      // select mesh and submesh for further data access
      if(pQunRenderer->selectMeshSubmesh(meshId, submeshId))
      {
        unsigned char meshColor[4];
        GLfloat materialColor[4];

        // set the material ambient color
        pQunRenderer->getAmbientColor(&meshColor[0]);
        materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
        //glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);

        // set the material diffuse color
        pQunRenderer->getDiffuseColor(&meshColor[0]);
        materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
        //glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);

        // set the vertex color if we have no lights
        if(!bLight)
        {
          //glColor4fv(materialColor);
        }

        // set the material specular color
        pQunRenderer->getSpecularColor(&meshColor[0]);
        materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
        //glMaterialfv(GL_FRONT, GL_SPECULAR, materialColor);

        // set the material shininess factor
        float shininess;
        shininess = 50.0f; //TODO: pQunRenderer->getShininess();
        //glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

        // get the transformed vertices of the submesh
        static float meshVertices[30000][3];
        int vertexCount;
        vertexCount = pQunRenderer->getVertices(&meshVertices[0][0]);

        // get the transformed normals of the submesh
        static float meshNormals[30000][3];
        pQunRenderer->getNormals(&meshNormals[0][0]);

        // get the texture coordinates of the submesh
        static float meshTextureCoordinates[30000][2];
        int textureCoordinateCount;
        textureCoordinateCount = pQunRenderer->getTextureCoordinates(0, &meshTextureCoordinates[0][0]);

        // get the faces of the submesh
        static QunIndex meshFaces[50000][3];
        int faceCount;
        faceCount = pQunRenderer->getFaces(&meshFaces[0][0]);

        // set the vertex and normal buffers
        //glVertexPointer(3, GL_FLOAT, 0, &meshVertices[0][0]);
        //glNormalPointer(GL_FLOAT, 0, &meshNormals[0][0]);

        // set the texture coordinate buffer and state if necessary
        if((pQunRenderer->getMapCount() > 0) && (textureCoordinateCount > 0))
        {
          glEnable(GL_TEXTURE_2D);
          //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
          //glEnable(GL_COLOR_MATERIAL);

          // set the texture id we stored in the map user data
          glBindTexture(GL_TEXTURE_2D, (unsigned long) pQunRenderer->getMapUserData(0));

          // set the texture coordinate buffer
          //glTexCoordPointer(2, GL_FLOAT, 0, &meshTextureCoordinates[0][0]);
          //glColor3f(1.0f, 1.0f, 1.0f);
        }

        // draw the submesh

        if(sizeof(QunIndex)==2)
          glDrawElements(GL_TRIANGLES, faceCount * 3, GL_UNSIGNED_SHORT, &meshFaces[0][0]);
        else
          glDrawElements(GL_TRIANGLES, faceCount * 3, GL_UNSIGNED_INT, &meshFaces[0][0]);

        // disable the texture coordinate state if necessary
        if((pQunRenderer->getMapCount() > 0) && (textureCoordinateCount > 0))
        {
          //glDisable(GL_COLOR_MATERIAL);
          //glDisableClientState(GL_TEXTURE_COORD_ARRAY);
          //glDisable(GL_TEXTURE_2D);
        }

        // DEBUG-CODE //////////////////////////////////////////////////////////////////
        /*
        //*glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 1.0f);
        int vertexId;
        for(vertexId = 0; vertexId < vertexCount; vertexId++)
        {
        const float scale = 0.3f;
        glVertex3f(meshVertices[vertexId][0], meshVertices[vertexId][1], meshVertices[vertexId][2]);
        glVertex3f(meshVertices[vertexId][0] + meshNormals[vertexId][0] * scale, meshVertices[vertexId][1] + meshNormals[vertexId][1] * scale, meshVertices[vertexId][2] + meshNormals[vertexId][2] * scale);
        }
        //*glEnd();
        */
        ////////////////////////////////////////////////////////////////////////////////
      }
    }
  }

  // clear vertex array state
  //glDisableClientState(GL_NORMAL_ARRAY);
  //glDisableClientState(GL_VERTEX_ARRAY);

  // reset the lighting mode
  if(bLight)
  {
    //glDisable(GL_LIGHTING);
    //glDisable(GL_LIGHT0);
  }

  // reset the global OpenGL states
  glDisable(GL_DEPTH_TEST);

  // reset wireframe mode if necessary
  if(bWireframe)
  {
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  // end the rendering
  pQunRenderer->endRendering();

  /// NVSG Reciever
}

void unAvatar::acRenderMesh(bool bWireframe, bool bLight)
{
#if 0
    glBindProgramARB( GL_VERTEX_PROGRAM_ARB, m_vertexProgramId );

	glEnableVertexAttribArrayARB(0);
	glEnableVertexAttribArrayARB(1);
    glEnableVertexAttribArrayARB(2);
	glEnableVertexAttribArrayARB(3);
    glEnableVertexAttribArrayARB(8);
	
	glEnable(GL_TEXTURE_2D);
	// set global OpenGL states
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);		
	glEnable(GL_VERTEX_PROGRAM_ARB);
	
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[0]);
	glVertexAttribPointerARB(0, 3 , GL_FLOAT, false, 0, NULL);

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[1]);
	glVertexAttribPointerARB(1, 4 , GL_FLOAT, false, 0, NULL);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[2]);
    glVertexAttribPointerARB(2, 3 , GL_FLOAT, false, 0, NULL);

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[3]);

	glVertexAttribPointerARB(3, 4 , GL_FLOAT, false, 0, NULL);

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[4]);
	glVertexAttribPointerARB(8, 2 , GL_FLOAT, false, 0, NULL);

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_bufferObject[5]);

	int hardwareMeshId;

	for(hardwareMeshId=0;hardwareMeshId<m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];	
		float materialColor[4];
		// set the material ambient color
		m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);
		
		// set the material specular color
		m_calHardwareModel->getSpecularColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_SPECULAR, materialColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		int boneId;
		for(boneId = 0; boneId < m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = m_calHardwareModel->getRotationBoneSpace(boneId, m_qunModel->getSkeleton());
			QunVector translationBoneSpace = m_calHardwareModel->getTranslationBoneSpace(boneId, m_qunModel->getSkeleton());

			//printf("Trace translationBoneSpace %f %f %f\n", translationBoneSpace.x, translationBoneSpace.y, translationBoneSpace.z);
			
#if 1
			translationBoneSpace.x += m_posx;
			translationBoneSpace.y += m_posy;
			translationBoneSpace.z += m_posz;
#endif

#if 0
			translationBoneSpace.x += 0;
			translationBoneSpace.y += 0;
			translationBoneSpace.z += 50;
#endif

			//printf("Trace m_posx %f m_posy %f m_posz %f\n", m_posx, m_posy, m_posz);

			QunMatrix rotationMatrix = rotationBoneSpace;

			float transformation[12];

			transformation[0]=rotationMatrix.dxdx;transformation[1]=rotationMatrix.dxdy;transformation[2]=rotationMatrix.dxdz;transformation[3]=translationBoneSpace.x;
			transformation[4]=rotationMatrix.dydx;transformation[5]=rotationMatrix.dydy;transformation[6]=rotationMatrix.dydz;transformation[7]=translationBoneSpace.y;
			transformation[8]=rotationMatrix.dzdx;transformation[9]=rotationMatrix.dzdy;transformation[10]=rotationMatrix.dzdz;transformation[11]=translationBoneSpace.z;
			
			glProgramLocalParameter4fvARB(GL_VERTEX_PROGRAM_ARB,boneId*3,&transformation[0]);
			glProgramLocalParameter4fvARB(GL_VERTEX_PROGRAM_ARB,boneId*3+1,&transformation[4]);
			glProgramLocalParameter4fvARB(GL_VERTEX_PROGRAM_ARB,boneId*3+2,&transformation[8]);			
			
            // set the texture id we stored in the map user data
#pragma message("Server Engine Excludes")
#if defined(WIN32)
            glBindTexture(GL_TEXTURE_2D, (GLuint)m_calHardwareModel->getMapUserData(0));
#endif
			}

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ m_calHardwareModel->getStartIndex()));
		}

    // clear vertex array state

	glDisableVertexAttribArrayARB(0);
	glDisableVertexAttribArrayARB(1);
    glDisableVertexAttribArrayARB(2);
	glDisableVertexAttribArrayARB(3);
    glDisableVertexAttribArrayARB(8);

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    // clear light
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_DEPTH_TEST);
	glDisable(GL_VERTEX_PROGRAM_ARB);

	glBindProgramARB( GL_VERTEX_PROGRAM_ARB, 0 );
#endif
}

//----------------------------------------------------------------------------//
// Set the lod level of the mesh                                             //
//----------------------------------------------------------------------------//

void unAvatar::setLodLevel(float lodLevel)
{
  m_lodLevel = lodLevel;

  // set the new lod level in the cal mesh renderer
  m_qunModel->setLodLevel(m_lodLevel);
}

//----------------------------------------------------------------------------//
// Avatar Update                                                              //
//----------------------------------------------------------------------------//

void unAvatar::BeginAnim(void)
{
	m_qunModel->getMixer()->BeginAnim();
}

void unAvatar::EndAnim(void)
{
	m_qunModel->getMixer()->BeginAnim();
}

void unAvatar::BlendAnim(int i_Motion, float i_Time, float i_BlendAmount)
{
	m_qunModel->getMixer()->BlendAnim(i_Motion, i_Time, i_BlendAmount);
}

void unAvatar::BlendAnimMin(int i_Motion, float i_Time, float i_BlendAmount)
{
	m_qunModel->getMixer()->BlendAnimMin(i_Motion, i_Time, i_BlendAmount);
}

void unAvatar::BlendAnimTorque(int i_Motion, float i_Time, float i_BlendAmount)
{
	m_qunModel->getMixer()->BlendAnimTorque(i_Motion, i_Time, i_BlendAmount, 1);
}

void unAvatar::BlendAnimPhysics(int i_Motion, float i_Time, float i_BlendAmount) 
{
#if defined(ENABLE_PX_PHYSICS)
#if 1
	if(m_BoneStructure != -1)
		{
#if 1
		if(m_BoneState == 0) Digi::DigiMassCore::instance()->acBoneStructureSleepSurgery(m_BoneStructure);
#endif

		// get the skeleton we need to update
		QunSkeleton *pSkeleton;
		pSkeleton = m_qunModel->getSkeleton();

		// clear the skeleton state
#if 0
		pSkeleton->clearState();
#endif

		// get the bone vector of the skeleton
		std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

		// lock the skeleton state
#if 0
		pSkeleton->lockState();
#endif

#if 0
		PxMat33 i_avatarmatrix;
		i_avatarmatrix.createIdentity();
#endif

		if(m_BoneStructure == 0)
			{
			PxMat33 i_avatarmatrix(PxVec3(playerAV[g_Player]->Viewform.m[0][0], playerAV[g_Player]->Viewform.m[1][0], playerAV[g_Player]->Viewform.m[2][0]), PxVec3(playerAV[g_Player]->Viewform.m[0][1], playerAV[g_Player]->Viewform.m[1][1], playerAV[g_Player]->Viewform.m[2][1]), PxVec3(playerAV[g_Player]->Viewform.m[0][2], playerAV[g_Player]->Viewform.m[1][2], playerAV[g_Player]->Viewform.m[2][2]));
			Digi::DigiMassCore::instance()->acBoneStructurePose(m_BoneStructure, vectorBone, i_avatarmatrix, PxVec3(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z));
			}
		else
			{
			PxMat33 i_avatarmatrix(PxVec3(Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[0][0], Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[1][0], Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[2][0]), PxVec3(Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[0][1], Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[1][1], Q_Forge->Forge[0].AV.Xform.Matrix.m[2][1]), PxVec3(Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[0][2], Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[1][2], Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[2][2]));
			Digi::DigiMassCore::instance()->acBoneStructurePose(m_BoneStructure, vectorBone, i_avatarmatrix, PxVec3(Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Translation.x, Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Translation.y, Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Translation.z));
			}

	#pragma message("Update Mass From Shapes ::: PxActor")

		// lock the skeleton state
#if 0
		pSkeleton->lockState();
#endif

		// let the skeleton calculate its final state
#if 0
		pSkeleton->calculateState();
#endif
		}
#endif
#endif
}

void unAvatar::BlendAnimPhysicsSurgery(int i_Motion, float i_Time, float i_BlendAmount) 
{
#if defined(ENABLE_PX_PHYSICS)
#if 1
	if(m_BoneStructure != -1)
		{
#if 1
		if(m_BoneState == 0) Digi::DigiMassCore::instance()->acBoneStructureSleepSurgery(m_BoneStructure);
#endif

		// get the skeleton we need to update
		QunSkeleton *pSkeleton;
		pSkeleton = m_qunModel->getSkeleton();

		// clear the skeleton state
#if 0
		pSkeleton->clearState();
#endif

		// get the bone vector of the skeleton
		std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

		// lock the skeleton state
#if 0
		pSkeleton->lockState();
#endif

#if 0
		PxMat33 i_avatarmatrix;
		i_avatarmatrix.createIdentity();
#endif

		if(m_BoneStructure == 0)
			{
			PxMat33 i_avatarmatrix(PxVec3(playerAV[g_Player]->Viewform.m[0][0], playerAV[g_Player]->Viewform.m[1][0], playerAV[g_Player]->Viewform.m[2][0]), PxVec3(playerAV[g_Player]->Viewform.m[0][1], playerAV[g_Player]->Viewform.m[1][1], playerAV[g_Player]->Viewform.m[2][1]), PxVec3(playerAV[g_Player]->Viewform.m[0][2], playerAV[g_Player]->Viewform.m[1][2], playerAV[g_Player]->Viewform.m[2][2]));
			Digi::DigiMassCore::instance()->acBoneStructurePoseSurgery(m_BoneStructure, vectorBone, i_avatarmatrix, PxVec3(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z));
			}
		else
			{
			PxMat33 i_avatarmatrix(PxVec3(Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[0][0], Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[1][0], Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[2][0]), PxVec3(Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[0][1], Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[1][1], Q_Forge->Forge[0].AV.Xform.Matrix.m[2][1]), PxVec3(Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[0][2], Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[1][2], Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[2][2]));
			Digi::DigiMassCore::instance()->acBoneStructurePoseSurgery(m_BoneStructure, vectorBone, i_avatarmatrix, PxVec3(Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Translation.x, Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Translation.y, Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Translation.z));
			}

	#pragma message("Update Mass From Shapes ::: PxActor")

		// lock the skeleton state
#if 0
		pSkeleton->lockState();
#endif

		// let the skeleton calculate its final state
#if 0
		pSkeleton->calculateState();
#endif
		}
#endif
#endif
}

void unAvatar::BlendAnimPhysicsProp(int i_Motion, float i_Time, float i_BlendAmount) 
{
#if defined(ENABLE_PX_PHYSICS)
#if 1
	if(m_BoneStructure != -1)
		{
#if 1
		if(m_BoneState == 0) Digi::DigiMassCore::instance()->acBoneStructureSleepProp(m_BoneStructure);
#endif

		// get the skeleton we need to update
		QunSkeleton *pSkeleton;
		pSkeleton = m_qunModel->getSkeleton();

		// clear the skeleton state
#if 0
		pSkeleton->clearState();
#endif

		// get the bone vector of the skeleton
		std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

		// lock the skeleton state
#if 0
		pSkeleton->lockState();
#endif

#if 0
		PxMat33 i_avatarmatrix;
		i_avatarmatrix.createIdentity();
#endif

		if(m_BoneStructure == 0)
			{
			PxMat33 i_avatarmatrix(PxVec3(playerAV[g_Player]->Viewform.m[0][0], playerAV[g_Player]->Viewform.m[1][0], playerAV[g_Player]->Viewform.m[2][0]), PxVec3(playerAV[g_Player]->Viewform.m[0][1], playerAV[g_Player]->Viewform.m[1][1], playerAV[g_Player]->Viewform.m[2][1]), PxVec3(playerAV[g_Player]->Viewform.m[0][2], playerAV[g_Player]->Viewform.m[1][2], playerAV[g_Player]->Viewform.m[2][2]));
			Digi::DigiMassCore::instance()->acBoneStructurePoseProp(m_BoneStructure, vectorBone, i_avatarmatrix, PxVec3(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z));
			}
		else
			{
			PxMat33 i_avatarmatrix(PxVec3(Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[0][0], Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[1][0], Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[2][0]), PxVec3(Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[0][1], Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[1][1], Q_Forge->Forge[0].AV.Xform.Matrix.m[2][1]), PxVec3(Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[0][2], Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[1][2], Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[2][2]));
			Digi::DigiMassCore::instance()->acBoneStructurePoseProp(m_BoneStructure, vectorBone, i_avatarmatrix, PxVec3(Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Translation.x, Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Translation.y, Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Translation.z));
			}

	#pragma message("Update Mass From Shapes ::: PxActor")

		// lock the skeleton state
#if 0
		pSkeleton->lockState();
#endif

		// let the skeleton calculate its final state
#if 0
		pSkeleton->calculateState();
#endif
		}
#endif
#endif
}

void unAvatar::ClearAnimPhysics(void)
{
#if defined(ENABLE_PX_PHYSICS)
	if(m_BoneStructure != -1)
		{
		Digi::DigiMassCore::instance()->acBoneStructureSleep(m_BoneStructure);

		// get the skeleton we need to update
		QunSkeleton *pSkeleton;
		pSkeleton = m_qunModel->getSkeleton();

		// get the bone vector of the skeleton
		std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

		if(m_BoneStructure == 0)
			{
			PxMat33 i_avatarmatrix;
			i_avatarmatrix.createIdentity();
			Digi::DigiMassCore::instance()->acBoneStructurePose(m_BoneStructure, vectorBone, i_avatarmatrix, PxVec3(0, 0, 0));
			}
		else
			{
			PxMat33 i_avatarmatrix(PxVec3(Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[0][0], Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[1][0], Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[2][0]), PxVec3(Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[0][1], Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[1][1], Q_Forge->Forge[0].AV.Xform.Matrix.m[2][1]), PxVec3(Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[0][2], Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[1][2], Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Matrix.m[2][2]));
			Digi::DigiMassCore::instance()->acBoneStructurePose(m_BoneStructure, vectorBone, i_avatarmatrix, PxVec3(Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Translation.x, Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Translation.y, Q_Forge->Forge[m_BoneStructure-1].AV.Xform.Translation.z));
			}
		}
#endif
}

#if defined(ENABLE_PX_PHYSICS)
QunQuaternion CompResult(PxMat33 i_Matrix, PxMat33 i_AvatarMatrix)
{
#if 0
	PxMat33 i_TransferMatrix, invAvatarMatrix;
	PxVec3 i_Row0, i_Row1, i_Row2;
	PxQuat i_Quat;
	QunQuaternion i_CalQuat;

	invAvatarMatrix = i_AvatarMatrix.getInverse();
	i_Matrix = i_Matrix * invAvatarMatrix;

#if 0
	i_TransferMatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_TransferMatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_TransferMatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));
#endif

	i_Matrix.getRow(0, i_Row0);
	i_Matrix.getRow(1, i_Row1);
	i_Matrix.getRow(2, i_Row2);

	i_TransferMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_TransferMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_TransferMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_TransferMatrix.toQuat(i_Quat);

	i_CalQuat.x = i_Quat.x;
	i_CalQuat.y = i_Quat.y;
	i_CalQuat.z = i_Quat.z;
	i_CalQuat.w = i_Quat.w;
#endif

	QunQuaternion i_CalQuat;

	return i_CalQuat;
}
#endif

void unAvatar::acSetPose(void)
{
#if 0
#if defined(ENABLE_PX_PHYSICS)
	QunVector translation;
	QunQuaternion rotation, i_TransferQuat;
	QunBone *pBone;
	CalCoreBone *pCoreBone;
	QunSkeleton *pSkeleton;
	PxVec3 i_vector, i_VecTrans;
	PxMat33 i_BoneMatrix, i_invAvatarMat;
	PxVec3 i_Row0, i_Row1, i_Row2;
	PxVec3 cal_vec3d;
	PxQuat i_toQuat;
	PxMat33 i_avatarinverse;

	if(m_BoneStructure == 0)
		{
		PxMat33 i_avatarmatrix(PxVec3(playerAV[g_Player]->Viewform.m[0][0], playerAV[g_Player]->Viewform.m[1][0], playerAV[g_Player]->Viewform.m[2][0]), PxVec3(playerAV[g_Player]->Viewform.m[0][1], playerAV[g_Player]->Viewform.m[1][1], playerAV[g_Player]->Viewform.m[2][1]), PxVec3(playerAV[g_Player]->Viewform.m[0][2], playerAV[g_Player]->Viewform.m[1][2], playerAV[g_Player]->Viewform.m[2][2]));
		i_avatarinverse = i_avatarmatrix.getInverse();
		}
	else
		{
#pragma message("Solve: consider AI avatars in flight and change matrix to full rotation equivelant - Search pattern - if(Q_Forge->Forge[i].AirJinkRotFG == 1)")
		PxMat33 i_avatarmatrix(PxVec3(Q_Forge->Forge[m_BoneStructure - 1].AV.Xform.Matrix.m[0][0], Q_Forge->Forge[m_BoneStructure - 1].AV.Xform.Matrix.m[1][0], Q_Forge->Forge[m_BoneStructure - 1].AV.Xform.Matrix.m[2][0]), PxVec3(Q_Forge->Forge[m_BoneStructure - 1].AV.Xform.Matrix.m[0][1], Q_Forge->Forge[m_BoneStructure - 1].AV.Xform.Matrix.m[1][1], Q_Forge->Forge[m_BoneStructure - 1].AV.Xform.Matrix.m[2][1]), PxVec3(Q_Forge->Forge[m_BoneStructure - 1].AV.Xform.Matrix.m[0][2], Q_Forge->Forge[m_BoneStructure - 1].AV.Xform.Matrix.m[1][2], Q_Forge->Forge[m_BoneStructure - 1].AV.Xform.Matrix.m[2][2]));
		i_avatarinverse = i_avatarmatrix.getInverse();
		}

	if(m_BoneState == 1)
		{
		Digi::DigiMassCore::instance()->acBoneStructureWake(m_BoneStructure);
		Digi::DigiMassCore::instance()->acBoneNullVelocity(m_BoneStructure);
		m_BoneState = 0;
		}

	pSkeleton = m_qunModel->getSkeleton();

#if 0// clear the skeleton state
	pSkeleton->clearState();

	pSkeleton->calculateState();
#endif

	// get the bone vector of the skeleton
	std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

#if 0// lock the skeleton state
	pSkeleton->lockState();
#endif

	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	
	PxMat33 i_BoneMatrixTransfer41(Digi::DigiMassCore::instance()->getBoneheadPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer41;
	//i_BoneMatrix = Digi::DigiMassCore::instance()->getBoneheadPose(m_BoneStructure));
	i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

#if 0
	cal_vec3d = Digi::DigiMassCore::instance()->getBoneheadPosition(m_BoneStructure));

	cal_vec3d.x -= playerAV[g_Player]->Xform.Translation.x;
	cal_vec3d.y -= playerAV[g_Player]->Xform.Translation.y;
	cal_vec3d.z -= playerAV[g_Player]->Xform.Translation.z;
#endif

#if 1
	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();
#endif

	pBone = vectorBone[8];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
	
	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer2(Digi::DigiMassCore::instance()->getBonetorsoPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer2; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[3];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));

#if 0
	pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
	i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
	pBone->setRotation(i_TransferQuat);

	pBone = vectorBone[4];

	pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
	i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
	pBone->setRotation(i_TransferQuat);

	pBone = vectorBone[5];

	pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
	i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
	pBone->setRotation(i_TransferQuat);

	pBone = vectorBone[6];

	pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
	i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
	pBone->setRotation(i_TransferQuat);
#endif

	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer3(Digi::DigiMassCore::instance()->getBonepelvisPose(m_BoneStructure));
	cal_vec3d = Digi::DigiMassCore::instance()->getBonepelvisPosition(m_BoneStructure);
	i_BoneMatrix = i_BoneMatrixTransfer3; i_BoneMatrix = i_avatarinverse * i_BoneMatrix; 

	if(m_BoneStructure == 0)
		{
		cal_vec3d.x -= playerAV[g_Player]->Xform.Translation.x;
		cal_vec3d.y -= playerAV[g_Player]->Xform.Translation.y;
		cal_vec3d.z -= playerAV[g_Player]->Xform.Translation.z;
		}
	else
		{
		cal_vec3d.x -= Q_Forge->Forge[m_BoneStructure - 1].AV.Xform.Translation.x;
		cal_vec3d.y -= Q_Forge->Forge[m_BoneStructure - 1].AV.Xform.Translation.y;
		cal_vec3d.z -= Q_Forge->Forge[m_BoneStructure - 1].AV.Xform.Translation.z;
		}

	cal_vec3d = i_avatarinverse * cal_vec3d;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[2];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));

	pBone = vectorBone[2];

	pBone->setPivotTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));

	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer4(Digi::DigiMassCore::instance()->getBoneleftUpperArmPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer4; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[10];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));

	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer5(Digi::DigiMassCore::instance()->getBonerightUpperArmPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer5; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[29];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
	
	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer6(Digi::DigiMassCore::instance()->getBoneleftForeArmPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer6; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[11];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
	
	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer7(Digi::DigiMassCore::instance()->getBonerightForeArmPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer7; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[30];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
	
	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer8(Digi::DigiMassCore::instance()->getBoneleftHandPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer8; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[12];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));

	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer9(Digi::DigiMassCore::instance()->getBonerightHandPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer9; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[31];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
	
	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer10(Digi::DigiMassCore::instance()->getBoneleftThighPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer10; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[47];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
	
	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer11(Digi::DigiMassCore::instance()->getBonerightThighPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer11; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[51];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
	
	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer12(Digi::DigiMassCore::instance()->getBoneleftCalfPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer12; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[48];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
	
	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer13(Digi::DigiMassCore::instance()->getBonerightCalfPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer13; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[52];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
	
	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer14(Digi::DigiMassCore::instance()->getBoneleftFootPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer14; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[49];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
	
	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer15(Digi::DigiMassCore::instance()->getBonerightFootPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer15; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[53];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
	
	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

#if 0	// lock the skeleton state
	pSkeleton->lockState();
#endif

	// let the skeleton calculate its final state
	pSkeleton->calculateState();
#endif
#endif
}

void unAvatar::acSetPoseSurgery(void)
{
#if 0
#if defined(ENABLE_PX_PHYSICS)
	QunVector translation;
	QunQuaternion rotation, i_TransferQuat;
	QunBone *pBone;
	CalCoreBone *pCoreBone;
	QunSkeleton *pSkeleton;
	PxVec3 i_vector, i_VecTrans;
	PxMat33 i_BoneMatrix, i_invAvatarMat;
	PxVec3 i_Row0, i_Row1, i_Row2;
	PxVec3 cal_vec3d;
	PxQuat i_toQuat;
	PxMat33 i_avatarinverse;

	if(m_BoneStructure == 0)
		{
		PxMat33 i_avatarmatrix(PxVec3(playerAV[g_Player]->Viewform.m[0][0], playerAV[g_Player]->Viewform.m[1][0], playerAV[g_Player]->Viewform.m[2][0]), PxVec3(playerAV[g_Player]->Viewform.m[0][1], playerAV[g_Player]->Viewform.m[1][1], playerAV[g_Player]->Viewform.m[2][1]), PxVec3(playerAV[g_Player]->Viewform.m[0][2], playerAV[g_Player]->Viewform.m[1][2], playerAV[g_Player]->Viewform.m[2][2]));
		i_avatarinverse = i_avatarmatrix.getInverse();
		}
	else
		{
#pragma message("Solve: consider AI avatars in flight and change matrix to full rotation equivelant - Search pattern - if(Q_Forge->Forge[i].AirJinkRotFG == 1)")
		PxMat33 i_avatarmatrix(PxVec3(Q_Forge->Forge[m_BoneStructure - 1].AV.Xform.Matrix.m[0][0], Q_Forge->Forge[m_BoneStructure - 1].AV.Xform.Matrix.m[1][0], Q_Forge->Forge[m_BoneStructure - 1].AV.Xform.Matrix.m[2][0]), PxVec3(Q_Forge->Forge[m_BoneStructure - 1].AV.Xform.Matrix.m[0][1], Q_Forge->Forge[m_BoneStructure - 1].AV.Xform.Matrix.m[1][1], Q_Forge->Forge[m_BoneStructure - 1].AV.Xform.Matrix.m[2][1]), PxVec3(Q_Forge->Forge[m_BoneStructure - 1].AV.Xform.Matrix.m[0][2], Q_Forge->Forge[m_BoneStructure - 1].AV.Xform.Matrix.m[1][2], Q_Forge->Forge[m_BoneStructure - 1].AV.Xform.Matrix.m[2][2]));
		i_avatarinverse = i_avatarmatrix.getInverse();
		}

	if(m_BoneState == 1)
		{
		Digi::DigiMassCore::instance()->acBoneStructureWakeSurgery(m_BoneStructure);
		Digi::DigiMassCore::instance()->acBoneNullVelocity(m_BoneStructure);
		m_BoneState = 0;
		}

	pSkeleton = m_qunModel->getSkeleton();

#if 0// clear the skeleton state
	pSkeleton->clearState();

	pSkeleton->calculateState();
#endif

	// get the bone vector of the skeleton
	std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

#if 0// lock the skeleton state
	pSkeleton->lockState();
#endif

	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer16(Digi::DigiMassCore::instance()->getBoneheadPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer16; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

#if 0
	cal_vec3d = Digi::DigiMassCore::instance()->getBoneheadPosition(m_BoneStructure));

	cal_vec3d.x -= playerAV[g_Player]->Xform.Translation.x;
	cal_vec3d.y -= playerAV[g_Player]->Xform.Translation.y;
	cal_vec3d.z -= playerAV[g_Player]->Xform.Translation.z;
#endif

#if 1
	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();
#endif

	pBone = vectorBone[8];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
	
	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer17(Digi::DigiMassCore::instance()->getBonetorsoPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer17; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[3];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));

#if 0
	pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
	i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
	pBone->setRotation(i_TransferQuat);

	pBone = vectorBone[4];

	pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
	i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
	pBone->setRotation(i_TransferQuat);

	pBone = vectorBone[5];

	pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
	i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
	pBone->setRotation(i_TransferQuat);

	pBone = vectorBone[6];

	pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
	i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
	pBone->setRotation(i_TransferQuat);
#endif

	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer18(Digi::DigiMassCore::instance()->getBonepelvisPose(m_BoneStructure));
	cal_vec3d = Digi::DigiMassCore::instance()->getBonepelvisPosition(m_BoneStructure);
	i_BoneMatrix = i_BoneMatrixTransfer18; i_BoneMatrix = i_avatarinverse * i_BoneMatrix; 

	cal_vec3d.x -= playerAV[g_Player]->Xform.Translation.x;
	cal_vec3d.y -= playerAV[g_Player]->Xform.Translation.y;
	cal_vec3d.z -= playerAV[g_Player]->Xform.Translation.z;

	cal_vec3d = i_avatarinverse * cal_vec3d;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[2];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));

	pBone = vectorBone[2];

	pBone->setPivotTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));

	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer19(Digi::DigiMassCore::instance()->getBoneleftUpperArmPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer19; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[10];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));

	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer20(Digi::DigiMassCore::instance()->getBonerightUpperArmPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer20; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[29];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
	
	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer21(Digi::DigiMassCore::instance()->getBoneleftForeArmPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer21; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[11];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
	
	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer22(Digi::DigiMassCore::instance()->getBonerightForeArmPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer22; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[30];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
	
	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer23(Digi::DigiMassCore::instance()->getBoneleftHandPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer23; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[12];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));

	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer24(Digi::DigiMassCore::instance()->getBonerightHandPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer24; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[31];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
	
	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer25(Digi::DigiMassCore::instance()->getBoneleftThighPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer25; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[47];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
	
	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer26(Digi::DigiMassCore::instance()->getBonerightThighPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer26; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[51];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
	
	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer27(Digi::DigiMassCore::instance()->getBoneleftCalfPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer27; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[48];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
	
	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer28(Digi::DigiMassCore::instance()->getBonerightCalfPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer28; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[52];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
	
	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer29(Digi::DigiMassCore::instance()->getBoneleftFootPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer29; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[49];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
	
	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

	PxMat33 i_BoneMatrixTransfer30(Digi::DigiMassCore::instance()->getBonerightFootPose(m_BoneStructure));
	i_BoneMatrix = i_BoneMatrixTransfer30; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;

	i_BoneMatrix.getRow(0, i_Row0);
	i_BoneMatrix.getRow(1, i_Row1);
	i_BoneMatrix.getRow(2, i_Row2);

	i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
	i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
	i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));

	i_toQuat = i_BoneMatrix.toQuat();
	i_toQuat.normalize();

	pBone = vectorBone[53];

	pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
	
	/////////////////////////////////
	/////////////////////////////////
	/////////////////////////////////

#if 0	// lock the skeleton state
	pSkeleton->lockState();
#endif

	// let the skeleton calculate its final state
	pSkeleton->calculateState();
#endif
#endif
}

void unAvatar::acSetPoseNew(void)
{
#if 0
#if defined(ENABLE_PX_PHYSICS)
	if(m_BoneStructure == 0)
		{
		QunVector translation;
		QunQuaternion rotation, i_TransferQuat;
		QunBone *pBone;
		CalCoreBone *pCoreBone;
		QunSkeleton *pSkeleton;
		PxVec3 i_vector, i_VecTrans;
		PxMat33 i_BoneMatrix, i_invAvatarMat;
		//PxMat33 i_avatarmatrix(PxVec3(playerAV[g_Player]->Viewform.m[0][0], playerAV[g_Player]->Viewform.m[1][0], playerAV[g_Player]->Viewform.m[2][0]), PxVec3(playerAV[g_Player]->Viewform.m[0][1], playerAV[g_Player]->Viewform.m[1][1], playerAV[g_Player]->Viewform.m[2][1]), PxVec3(playerAV[g_Player]->Viewform.m[0][2], playerAV[g_Player]->Viewform.m[1][2], playerAV[g_Player]->Viewform.m[2][2]));
		//i_avatarmatrix.getInverse(i_invAvatarMat);

		/*PxVec3 i_Row0, i_Row1, i_Row2;

		i_invAvatarMat.getRow(0, i_Row0);
		i_invAvatarMat.getRow(1, i_Row1);
		i_invAvatarMat.getRow(2, i_Row2);

		i_invAvatarMat.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
		i_invAvatarMat.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
		i_invAvatarMat.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));*/

		/*i_avatarmatrix.getRow(0, i_VecTrans);
		i_invAvatarMat.setRow(0, PxVec3(i_VecTrans.x * -1, i_VecTrans.y * -1, i_VecTrans.z * -1));

		i_avatarmatrix.getRow(1, i_VecTrans);
		i_invAvatarMat.setRow(1, PxVec3(i_VecTrans.x * -1, i_VecTrans.y * -1, i_VecTrans.z * -1));

		i_avatarmatrix.getRow(2, i_VecTrans);
		i_invAvatarMat.setRow(2, PxVec3(i_VecTrans.x * -1, i_VecTrans.y * -1, i_VecTrans.z * -1));*/

		//i_invAvatarMat = i_avatarmatrix * -1;

		pSkeleton = m_qunModel->getSkeleton();

		// clear the skeleton state
		//pSkeleton->clearState();

		//pSkeleton->calculateState();

		// get the bone vector of the skeleton
		std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

		// lock the skeleton state
		//pSkeleton->lockState();

		PxVec3 i_Row0, i_Row1, i_Row2;
		PxVec3 cal_vec3d;
		PxQuat i_toQuat;
		PxMat33 i_avatarinverse;
		PxMat33 i_avatarmatrix(PxVec3(playerAV[g_Player]->Viewform.m[0][0], playerAV[g_Player]->Viewform.m[1][0], playerAV[g_Player]->Viewform.m[2][0]), PxVec3(playerAV[g_Player]->Viewform.m[0][1], playerAV[g_Player]->Viewform.m[1][1], playerAV[g_Player]->Viewform.m[2][1]), PxVec3(playerAV[g_Player]->Viewform.m[0][2], playerAV[g_Player]->Viewform.m[1][2], playerAV[g_Player]->Viewform.m[2][2]));
		i_avatarinverse = i_avatarmatrix.getInverse();

		PxQuat i_XQuat, i_YQuat, i_ZQuat;
		PxMat33 i_correctmatrix;
		PxReal i_Real = degToRadians(90);
		i_YQuat.toRadiansAndUnitAxis(i_Real, PxVec3(0,1,0));
		i_Real = degToRadians(180);
		i_XQuat.toRadiansAndUnitAxis(i_Real, PxVec3(0, 0, 1));
		i_Real = degToRadians(-90);
		i_ZQuat.toRadiansAndUnitAxis(i_Real, PxVec3(0, 1, 0));

		i_correctmatrix.fromQuat(i_XQuat * i_YQuat);

		PxMat33 i_BoneMatrixTransfer31(Digi::DigiMassCore::instance()->getBoneheadPose(0));
		cal_vec3d = Digi::DigiMassCore::instance()->getBoneheadPosition(0);

		i_BoneMatrix = i_BoneMatrixTransfer31; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;
		//i_BoneMatrix = i_correctmatrix * i_BoneMatrix;

		//i_BoneMatrix.getInverse(i_BoneMatrix);

		i_toQuat = i_BoneMatrix.toQuat();

		i_toQuat.normalize();

#if 0
		rotation.set(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w);

		//pBone->blendState(1, translation, rotation);
		pBone = vectorBone[8];
		pBone->setRotation(rotation);
#endif

#if 0
		cal_vec3d.x -= playerAV[g_Player]->Xform.Translation.x;// + cal_vec3d.y;
		cal_vec3d.y -= playerAV[g_Player]->Xform.Translation.y;
		cal_vec3d.z -= playerAV[g_Player]->Xform.Translation.z;// + cal_vec3d.y;
#endif

#if 0
		cal_vec3d.x = 0;
		cal_vec3d.y = 0;
		cal_vec3d.z = 0;
#endif

		//cal_vec3d = i_avatarinverse * cal_vec3d;
		//cal_vec3d = i_correctmatrix * cal_vec3d;

		//PxMat33 i_convertionmatrix = i_avatarinverse * i_correctmatrix;

		//printf("unTrace i_correctmatrix x %f y %f z %f\n", cal_vec3d.x, cal_vec3d.y, cal_vec3d.z);

		//pBone->setTranslationAbsolute(cal_vec3d, i_avatarinverse, i_correctmatrix);

		/*PxMat33 i_avatarinverse;
		PxMat33 i_avatarmatrix(PxVec3(playerAV[g_Player]->Viewform.m[0][0], playerAV[g_Player]->Viewform.m[1][0], playerAV[g_Player]->Viewform.m[2][0]), PxVec3(playerAV[g_Player]->Viewform.m[0][1], playerAV[g_Player]->Viewform.m[1][1], playerAV[g_Player]->Viewform.m[2][1]), PxVec3(playerAV[g_Player]->Viewform.m[0][2], playerAV[g_Player]->Viewform.m[1][2], playerAV[g_Player]->Viewform.m[2][2]));
		i_avatarinverse = i_avatarmatrix.getInverse();

		PxQuat i_XQuat, i_YQuat, i_ZQuat, i_toQuat;
		PxMat33 i_correctmatrix;
		i_YQuat.toRadiansAndUnitAxis(degToRadians(90, PxVec3(0,1,0));
		i_XQuat.toRadiansAndUnitAxis(degToRadians(180, PxVec3(0, 0, 1));
		i_ZQuat.toRadiansAndUnitAxis(degToRadians(-90, PxVec3(0, 1, 0));

		i_correctmatrix.fromQuat(i_XQuat * i_ZQuat);

		PxMat33 i_BoneMatrixTransfer32(Digi::DigiMassCore::instance()->getBoneheadPose(0);
		i_vector = Digi::DigiMassCore::instance()->getBoneheadPosition(0);

		i_BoneMatrix = i_BoneMatrixTransfer32; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;
		i_BoneMatrix = i_correctmatrix * i_BoneMatrix;

		i_BoneMatrix.getInverse(i_BoneMatrix);

		i_toQuat = i_BoneMatrix.toQuat();

		i_toQuat.normalize();

		rotation.set(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w);

		pBone = vectorBone[8];
		//pBone->setRotation(rotation);

		cal_vec3d.x -= playerAV[g_Player]->Xform.Translation.x;
		cal_vec3d.y -= playerAV[g_Player]->Xform.Translation.y;
		cal_vec3d.z -= playerAV[g_Player]->Xform.Translation.z;

		i_vector = i_avatarinverse * i_vector;

		pBone->setTranslation(QunVector(i_vector.x, i_vector.y, i_vector.z));*/

		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		PxMat33 i_BoneMatrixTransfer33(Digi::DigiMassCore::instance()->getBoneheadPose(0));
		cal_vec3d = Digi::DigiMassCore::instance()->getBoneheadPosition(0);

		cal_vec3d.x -= playerAV[g_Player]->Xform.Translation.x;
		cal_vec3d.y -= playerAV[g_Player]->Xform.Translation.y;
		cal_vec3d.z -= playerAV[g_Player]->Xform.Translation.z;

		i_BoneMatrix = i_BoneMatrixTransfer33; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;
		//i_BoneMatrix = i_correctmatrix * i_BoneMatrix;

#if 1
		i_BoneMatrix.getRow(0, i_Row0);
		i_BoneMatrix.getRow(1, i_Row1);
		i_BoneMatrix.getRow(2, i_Row2);

		i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
		i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
		i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));
#endif

		i_toQuat = i_BoneMatrix.toQuat();
		i_toQuat.normalize();

		//rotation.set(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w);

		pBone = vectorBone[8];

		pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));

		/*pBone->setTranslationAbsolute(cal_vec3d, i_avatarinverse, i_correctmatrix);

		//pBone->setTranslation(cal_vec3d);
		//i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
		//pBone->setRotation(i_TransferQuat);
		
		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		PxMat33 i_BoneMatrixTransfer34(Digi::DigiMassCore::instance()->getBonetorsoPose(0);
		i_vector = Digi::DigiMassCore::instance()->getBonetorsoPosition(0);

		cal_vec3d.x -= playerAV[g_Player]->Xform.Translation.x;
		cal_vec3d.y -= playerAV[g_Player]->Xform.Translation.y;
		cal_vec3d.z -= playerAV[g_Player]->Xform.Translation.z;

		cal_vec3d = i_avatarinverse * cal_vec3d;

		//pBone->setTranslationAbsolute(cal_vec3d, i_avatarinverse, i_correctmatrix);

		/*pBone = vectorBone[3];

		pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
		i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
		pBone->setRotation(i_TransferQuat);

		pBone = vectorBone[4];

		pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
		i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
		pBone->setRotation(i_TransferQuat);

		pBone = vectorBone[5];

		pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
		i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
		pBone->setRotation(i_TransferQuat);

		pBone = vectorBone[6];

		pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
		i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
		pBone->setRotation(i_TransferQuat);*//*
		
		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		PxMat33 i_BoneMatrixTransfer34(Digi::DigiMassCore::instance()->getBonepelvisPose(0);
		cal_vec3d = Digi::DigiMassCore::instance()->getBonepelvisPosition(0);

		cal_vec3d.x -= playerAV[g_Player]->Xform.Translation.x;
		cal_vec3d.y -= playerAV[g_Player]->Xform.Translation.y;
		cal_vec3d.z -= playerAV[g_Player]->Xform.Translation.z;

		cal_vec3d = i_avatarinverse * cal_vec3d;

		pBone = vectorBone[2];

		pBone->setTranslationAbsolute(cal_vec3d, i_avatarinverse, i_correctmatrix);

		//pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
		//i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
		//pBone->setRotation(i_TransferQuat);
		
		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		PxMat33 i_BoneMatrixTransfer1(Digi::DigiMassCore::instance()->getBoneleftUpperArmPose(0);
		cal_vec3d = Digi::DigiMassCore::instance()->getBoneleftUpperArmPosition(0);

		cal_vec3d.x -= playerAV[g_Player]->Xform.Translation.x;
		cal_vec3d.y -= playerAV[g_Player]->Xform.Translation.y;
		cal_vec3d.z -= playerAV[g_Player]->Xform.Translation.z;

		cal_vec3d = i_avatarinverse * cal_vec3d;

		pBone = vectorBone[10];

		pBone->setTranslationAbsolute(cal_vec3d, i_avatarinverse, i_correctmatrix);

		//pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
		//i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
		//pBone->setRotation(i_TransferQuat);
		
		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		PxMat33 i_BoneMatrixTransfer1(Digi::DigiMassCore::instance()->getBonerightUpperArmPose(0);
		cal_vec3d = Digi::DigiMassCore::instance()->getBonerightUpperArmPosition(0);

		cal_vec3d.x -= playerAV[g_Player]->Xform.Translation.x;
		cal_vec3d.y -= playerAV[g_Player]->Xform.Translation.y;
		cal_vec3d.z -= playerAV[g_Player]->Xform.Translation.z;

		cal_vec3d = i_avatarinverse * cal_vec3d;

		pBone = vectorBone[29];

		pBone->setTranslationAbsolute(cal_vec3d, i_avatarinverse, i_correctmatrix);

		//pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
		//i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
		//pBone->setRotation(i_TransferQuat);*/

		PxMat33 i_BoneMatrixTransfer35(Digi::DigiMassCore::instance()->getBoneleftUpperArmPose(0));
		cal_vec3d = Digi::DigiMassCore::instance()->getBoneleftUpperArmPosition(0);

		cal_vec3d.x -= playerAV[g_Player]->Xform.Translation.x;
		cal_vec3d.y -= playerAV[g_Player]->Xform.Translation.y;
		cal_vec3d.z -= playerAV[g_Player]->Xform.Translation.z;

		i_BoneMatrix = i_BoneMatrixTransfer35; i_BoneMatrix = i_avatarinverse * i_BoneMatrix;
		//i_BoneMatrix = i_correctmatrix * i_BoneMatrix;

#if 1
		i_BoneMatrix.getRow(0, i_Row0);
		i_BoneMatrix.getRow(1, i_Row1);
		i_BoneMatrix.getRow(2, i_Row2);

		i_BoneMatrix.setRow(0, PxVec3(i_Row0.x, i_Row1.x, i_Row2.x));
		i_BoneMatrix.setRow(1, PxVec3(i_Row0.y, i_Row1.y, i_Row2.y));
		i_BoneMatrix.setRow(2, PxVec3(i_Row0.z, i_Row1.z, i_Row2.z));
#endif

		i_toQuat = i_BoneMatrix.toQuat();
		i_toQuat.normalize();

		//rotation.set(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w);

		pBone = vectorBone[10];

		pBone->setRotationAbs(QunQuaternion(i_toQuat.x, i_toQuat.y, i_toQuat.z, i_toQuat.w));
		
		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		/*PxMat33 i_BoneMatrixTransfer1(Digi::DigiMassCore::instance()->getBoneleftForeArmPose(0);
		cal_vec3d = Digi::DigiMassCore::instance()->getBoneleftForeArmPosition(0);

		cal_vec3d.x -= playerAV[g_Player]->Xform.Translation.x;
		cal_vec3d.y -= playerAV[g_Player]->Xform.Translation.y;
		cal_vec3d.z -= playerAV[g_Player]->Xform.Translation.z;

		cal_vec3d = i_avatarinverse * cal_vec3d;

		pBone = vectorBone[11];

		pBone->setTranslationAbsolute(cal_vec3d, i_avatarinverse, i_correctmatrix);

		//pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
		//i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
		//pBone->setRotation(i_TransferQuat);
		
		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		PxMat33 i_BoneMatrixTransfer1(Digi::DigiMassCore::instance()->getBonerightForeArmPose(0);
		cal_vec3d = Digi::DigiMassCore::instance()->getBonerightForeArmPosition(0);

		cal_vec3d.x -= playerAV[g_Player]->Xform.Translation.x;
		cal_vec3d.y -= playerAV[g_Player]->Xform.Translation.y;
		cal_vec3d.z -= playerAV[g_Player]->Xform.Translation.z;

		cal_vec3d = i_avatarinverse * cal_vec3d;

		pBone = vectorBone[30];

		pBone->setTranslationAbsolute(cal_vec3d, i_avatarinverse, i_correctmatrix);

		//pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
		//i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
		//pBone->setRotation(i_TransferQuat);
		
		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		PxMat33 i_BoneMatrixTransfer1(Digi::DigiMassCore::instance()->getBoneleftHandPose(0);
		cal_vec3d = Digi::DigiMassCore::instance()->getBoneleftHandPosition(0);

		cal_vec3d.x -= playerAV[g_Player]->Xform.Translation.x;
		cal_vec3d.y -= playerAV[g_Player]->Xform.Translation.y;
		cal_vec3d.z -= playerAV[g_Player]->Xform.Translation.z;

		cal_vec3d = i_avatarinverse * cal_vec3d;

		pBone = vectorBone[12];

		pBone->setTranslationAbsolute(cal_vec3d, i_avatarinverse, i_correctmatrix);

		//pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
		//i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
		//pBone->setRotation(i_TransferQuat);
		
		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		PxMat33 i_BoneMatrixTransfer1(Digi::DigiMassCore::instance()->getBonerightHandPose(0);
		cal_vec3d = Digi::DigiMassCore::instance()->getBonerightHandPosition(0);

		cal_vec3d.x -= playerAV[g_Player]->Xform.Translation.x;
		cal_vec3d.y -= playerAV[g_Player]->Xform.Translation.y;
		cal_vec3d.z -= playerAV[g_Player]->Xform.Translation.z;

		cal_vec3d = i_avatarinverse * cal_vec3d;

		pBone = vectorBone[31];

		pBone->setTranslationAbsolute(cal_vec3d, i_avatarinverse, i_correctmatrix);

		//pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
		//i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
		//pBone->setRotation(i_TransferQuat);
		
		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////*/

		PxMat33 i_BoneMatrixTransfer1(Digi::DigiMassCore::instance()->getBoneleftThighPose(0));
		cal_vec3d = Digi::DigiMassCore::instance()->getBoneleftThighPosition(0);

		cal_vec3d.x -= playerAV[g_Player]->Xform.Translation.x;
		cal_vec3d.y -= playerAV[g_Player]->Xform.Translation.y;
		cal_vec3d.z -= playerAV[g_Player]->Xform.Translation.z;

		cal_vec3d = i_avatarinverse * cal_vec3d;

		pBone = vectorBone[47];

		pBone->setTranslation(QunVector(-2.711, 0.036, 3.054));
		//pBone->setTranslationAbsolute(cal_vec3d, i_avatarinverse, i_correctmatrix);

		//pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
		//i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
		//pBone->setRotation(i_TransferQuat);
		
		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		PxMat33 i_BoneMatrixTransfer36(Digi::DigiMassCore::instance()->getBonerightThighPose(0));
		cal_vec3d = Digi::DigiMassCore::instance()->getBonerightThighPosition(0);

		cal_vec3d.x -= playerAV[g_Player]->Xform.Translation.x;
		cal_vec3d.y -= playerAV[g_Player]->Xform.Translation.y;
		cal_vec3d.z -= playerAV[g_Player]->Xform.Translation.z;

		cal_vec3d = i_avatarinverse * cal_vec3d;

		pBone = vectorBone[51];

		pBone->setTranslation(QunVector(-2.711, 0.036, -3.054));
		//pBone->setTranslationAbsolute(cal_vec3d, i_avatarinverse, i_correctmatrix);

		//pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
		//i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
		//pBone->setRotation(i_TransferQuat);
		
		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////*/

		PxMat33 i_BoneMatrixTransfer37(Digi::DigiMassCore::instance()->getBoneleftCalfPose(0));
		cal_vec3d = Digi::DigiMassCore::instance()->getBoneleftCalfPosition(0);

		cal_vec3d.x -= playerAV[g_Player]->Xform.Translation.x;
		cal_vec3d.y -= playerAV[g_Player]->Xform.Translation.y;
		cal_vec3d.z -= playerAV[g_Player]->Xform.Translation.z;

		cal_vec3d = i_avatarinverse * cal_vec3d;

		pBone = vectorBone[48];

		pBone->setTranslation(QunVector(17.097, 0, 0));
		//pBone->setTranslationAbsolute(cal_vec3d, i_avatarinverse, i_correctmatrix);

		//pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
		//i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
		//pBone->setRotation(i_TransferQuat);
		
		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		PxMat33 i_BoneMatrixTransfer38(Digi::DigiMassCore::instance()->getBonerightCalfPose(0));
		cal_vec3d = Digi::DigiMassCore::instance()->getBonerightCalfPosition(0);

		cal_vec3d.x -= playerAV[g_Player]->Xform.Translation.x;
		cal_vec3d.y -= playerAV[g_Player]->Xform.Translation.y;
		cal_vec3d.z -= playerAV[g_Player]->Xform.Translation.z;

		cal_vec3d = i_avatarinverse * cal_vec3d;

		pBone = vectorBone[52];

		pBone->setTranslation(QunVector(17.065, 0, 0));
		//pBone->setTranslationAbsolute(cal_vec3d, i_avatarinverse, i_correctmatrix);

		//pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
		//i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
		//pBone->setRotation(i_TransferQuat);*/
		
		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		PxMat33 i_BoneMatrixTransfer39(Digi::DigiMassCore::instance()->getBoneleftFootPose(0));
		cal_vec3d = Digi::DigiMassCore::instance()->getBoneleftFootPosition(0);

		cal_vec3d.x -= playerAV[g_Player]->Xform.Translation.x;
		cal_vec3d.y -= playerAV[g_Player]->Xform.Translation.y;
		cal_vec3d.z -= playerAV[g_Player]->Xform.Translation.z;

		cal_vec3d = i_avatarinverse * cal_vec3d;

		pBone = vectorBone[49];

		pBone->setTranslation(QunVector(16.896, 0, 0));
		//pBone->setTranslationAbsolute(cal_vec3d, i_avatarinverse, i_correctmatrix);

		//pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
		//i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
		//pBone->setRotation(i_TransferQuat);
		
		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		PxMat33 i_BoneMatrixTransfer40(Digi::DigiMassCore::instance()->getBonerightFootPose(0));
		cal_vec3d = Digi::DigiMassCore::instance()->getBonerightFootPosition(0);

		cal_vec3d.x -= playerAV[g_Player]->Xform.Translation.x;
		cal_vec3d.y -= playerAV[g_Player]->Xform.Translation.y;
		cal_vec3d.z -= playerAV[g_Player]->Xform.Translation.z;

		cal_vec3d = i_avatarinverse * cal_vec3d;

		pBone = vectorBone[53];

		pBone->setTranslation(QunVector(16.896, 0, 0));
		//pBone->setTranslationAbsolute(cal_vec3d, i_avatarinverse, i_correctmatrix);

		//pBone->setTranslation(QunVector(cal_vec3d.x, cal_vec3d.y, cal_vec3d.z));
		//i_TransferQuat = CompResult(i_BoneMatrix, i_avatarmatrix);
		//pBone->setRotation(i_TransferQuat);
		
		/////////////////////////////////
		/////////////////////////////////
		/////////////////////////////////

		// lock the skeleton state
		pSkeleton->lockState();

		// let the skeleton calculate its final state
		pSkeleton->calculateState();

		pBone = vectorBone[49];
		QunVector i_Leftfoot = pBone->getTranslationAbsolute();
		printf("unTrace i_Leftfoot x %f y %f z %f\n", i_Leftfoot.x, i_Leftfoot.y, i_Leftfoot.z);

		pBone = vectorBone[53];
		QunVector i_Rightfoot = pBone->getTranslationAbsolute();
		printf("unTrace i_Rightfoot x %f y %f z %f\n", i_Rightfoot.x, i_Rightfoot.y, i_Rightfoot.z);
		}
#endif
#endif
}

void unAvatar::acPrintBoneAbsPos(unsigned int i_Index)
{
	QunSkeleton *pSkeleton;
	QunBone *pBone;
	pSkeleton = m_qunModel->getSkeleton();

	std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

	// lock the skeleton state
	pSkeleton->lockState();

	// let the skeleton calculate its final state
	pSkeleton->calculateState();

	pBone = vectorBone[i_Index];
	QunVector i_Vector = pBone->getTranslationAbsolute();
	printf("unTrace acPrintBoneAbsPos Index %i x %f y %f z %f\n", i_Index, i_Vector.x, i_Vector.y, i_Vector.z);
}

void unAvatar::acPrintBonePos(unsigned int i_Index)
{
	QunSkeleton *pSkeleton;
	QunBone *pBone;
	pSkeleton = m_qunModel->getSkeleton();

	std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

	// lock the skeleton state
	pSkeleton->lockState();

	// let the skeleton calculate its final state
	pSkeleton->calculateState();

	pBone = vectorBone[i_Index];
	QunVector i_Vector = pBone->getTranslation();
	printf("unTrace acPrintBonePos Index %i x %f y %f z %f\n", i_Index, i_Vector.x, i_Vector.y, i_Vector.z);
}

void unAvatar::ApplyAnim(int i_Motion, float i_Time, float i_BlendAmount)
{
	m_qunModel->getMixer()->ApplyAnim(i_Motion, i_Time, i_BlendAmount);
}

void unAvatar::Animate_LeftLeg(int i_Motion, float i_Time, float i_BlendAmount)
{
	m_qunModel->getMixer()->AnimateLeftLeg(i_Motion, i_Time, i_BlendAmount);
}

void unAvatar::Animate_RightLeg(int i_Motion, float i_Time, float i_BlendAmount)
{
	m_qunModel->getMixer()->AnimateRightLeg(i_Motion, i_Time, i_BlendAmount);
}

void unAvatar::Animate_LeftArm(int i_Motion, float i_Time, float i_BlendAmount)
{
	m_qunModel->getMixer()->AnimateLeftArm(i_Motion, i_Time, i_BlendAmount);
}

void unAvatar::Animate_RightArm(int i_Motion, float i_Time, float i_BlendAmount)
{
	m_qunModel->getMixer()->AnimateRightArm(i_Motion, i_Time, i_BlendAmount);
}

void unAvatar::Animate_Pivot(int i_Motion, float i_Time, float i_BlendAmount)
{
	m_qunModel->getMixer()->AnimatePivot(i_Motion, i_Time, i_BlendAmount);
}

void unAvatar::acRenderMesh_Programs(void)
{
#if 0
	glBindProgramARB( GL_VERTEX_PROGRAM_ARB, m_vertexProgramId );

	glEnableVertexAttribArrayARB(0);
	glEnableVertexAttribArrayARB(1);
    glEnableVertexAttribArrayARB(2);
	glEnableVertexAttribArrayARB(3);
    glEnableVertexAttribArrayARB(8);

	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	// set global OpenGL states
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);		
	glEnable(GL_VERTEX_PROGRAM_ARB);

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[0]);
	glVertexAttribPointerARB(0, 3 , GL_FLOAT, false, 0, NULL);

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[1]);
	glVertexAttribPointerARB(1, 4 , GL_FLOAT, false, 0, NULL);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[2]);
    glVertexAttribPointerARB(2, 3 , GL_FLOAT, false, 0, NULL);

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[3]);

	glVertexAttribPointerARB(3, 4 , GL_FLOAT, false, 0, NULL);

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[4]);
	glVertexAttribPointerARB(8, 2 , GL_FLOAT, false, 0, NULL);

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_bufferObject[5]);

	//CGpass pass;

	/* Set Cg parameters for the technique's effect. */
#if 0
	CGGLenum GLMatrix;

	CG_GL_MATRIX_IDENTITY
	CG_GL_MATRIX_TRANSPOSE
	CG_GL_MATRIX_INVERSE
	CG_GL_MATRIX_INVERSE_TRANSPOSE

	CG_GL_MODELVIEW_MATRIX
	CG_GL_PROJECTION_MATRIX
	CG_GL_TEXTURE_MATRIX
	CG_GL_MODELVIEW_PROJECTION_MATRIX

	CG_GL_VERTEX
	CG_GL_FRAGMENT
	CG_GL_GEOMETRY
#endif

#if 0
    //*cgGLSetStateMatrixParameter(theViewer.ninjaprogram->vecParameter[0], CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
    //*cgGLSetStateMatrixParameter(theViewer.ninjaprogram->vecParameter[1], CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_INVERSE_TRANSPOSE);
    //*cgGLSetStateMatrixParameter(theViewer.ninjaprogram->vecParameter[2], CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);

	////*cgGLSetStateMatrixParameter(theViewer.ninjaprogram->vecParameter[0], CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
	////*cgGLSetStateMatrixParameter(theViewer.ninjaprogram->vecParameter[1], CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
	////*cgGLSetStateMatrixParameter(theViewer.ninjaprogram->vecParameter[2], CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);

	//*cgGLSetStateMatrixParameter(theViewer.ninjaprogram->vecParameter[3], CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
	//*cgGLSetStateMatrixParameter(theViewer.ninjaprogram->vecParameter[4], CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_INVERSE_TRANSPOSE);

	////*cgGLSetMatrix

	//*cgGLSetParameter1f(theViewer.ninjaprogram->vecParameter[5], 1.0f);
	//*cgGLSetParameter3f(theViewer.ninjaprogram->vecParameter[6], 1.0f, 1.0f, 1.0f);
#endif

#if 0
	"WorldXf");
	"WorldITXf");
	"WvpXf");

	"ShadowViewProjXf");
	"ViewIXf");
	"ShadBias");
	"SpotLamp0Pos");
#endif

#if 0
	//cgSetParameter3fv(bumpprogram->vecParameter[1], eyePosition);
	//cgSetParameter3fv(bumpprogram->vecParameter[2], myLightPosition);
	////*cgGLSetStateMatrixParameter(theViewer.ninjaprogram->vecParameter[0], CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);

	/* Iterate through rendering passes for technique (even though bumpdemo.cgfx has just one pass). */
	pass = cgGetFirstPass(theViewer.ninjaprogram->vecTechnique[0]);
#endif

	//while (pass)
	//	{
	//	cgSetPassState(pass);

		for(int hardwareMeshId=0;hardwareMeshId<m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
			{
			m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

			unsigned char meshColor[4];
			float materialColor[4];
			// set the material ambient color
			m_calHardwareModel->getAmbientColor(&meshColor[0]);
			materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
			glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);

			// set the material diffuse color
			m_calHardwareModel->getDiffuseColor(&meshColor[0]);
			materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
			glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);

			// set the material specular color
			m_calHardwareModel->getSpecularColor(&meshColor[0]);
			materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
			glMaterialfv(GL_FRONT, GL_SPECULAR, materialColor);

			// set the material shininess factor
			float shininess;
			shininess = 50.0f; //m_calHardwareModel->getShininess();
			glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

			int boneId;
			for(boneId = 0; boneId < m_calHardwareModel->getBoneCount(); boneId++)
				{
				QunQuaternion rotationBoneSpace = m_calHardwareModel->getRotationBoneSpace(boneId, m_qunModel->getSkeleton());
				QunVector translationBoneSpace = m_calHardwareModel->getTranslationBoneSpace(boneId, m_qunModel->getSkeleton());

				QunMatrix rotationMatrix = rotationBoneSpace;

				float transformation[12];

				transformation[0]=rotationMatrix.dxdx;transformation[1]=rotationMatrix.dxdy;transformation[2]=rotationMatrix.dxdz;transformation[3]=translationBoneSpace.x;
				transformation[4]=rotationMatrix.dydx;transformation[5]=rotationMatrix.dydy;transformation[6]=rotationMatrix.dydz;transformation[7]=translationBoneSpace.y;
				transformation[8]=rotationMatrix.dzdx;transformation[9]=rotationMatrix.dzdy;transformation[10]=rotationMatrix.dzdz;transformation[11]=translationBoneSpace.z;

				glProgramLocalParameter4fvARB(GL_VERTEX_PROGRAM_ARB,boneId*3,&transformation[0]);
				glProgramLocalParameter4fvARB(GL_VERTEX_PROGRAM_ARB,boneId*3+1,&transformation[4]);
				glProgramLocalParameter4fvARB(GL_VERTEX_PROGRAM_ARB,boneId*3+2,&transformation[8]);			

				// set the texture id we stored in the map user data
#pragma message("Server Engine Excludes")
#if defined(WIN32)
				glBindTexture(GL_TEXTURE_2D, (GLuint)m_calHardwareModel->getMapUserData(0));
#endif
				}

			if(sizeof(QunIndex)==2)
				glDrawElements(GL_TRIANGLES, m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ m_calHardwareModel->getStartIndex()));
			else
				glDrawElements(GL_TRIANGLES, m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ m_calHardwareModel->getStartIndex()));
			}

		//cgResetPassState(pass);
		//pass = cgGetNextPass(pass);
		//}

    // clear vertex array state
	glDisableVertexAttribArrayARB(0);
	glDisableVertexAttribArrayARB(1);
    glDisableVertexAttribArrayARB(2);
	glDisableVertexAttribArrayARB(3);
    glDisableVertexAttribArrayARB(8);

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    // clear light
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_DEPTH_TEST);
	glDisable(GL_VERTEX_PROGRAM_ARB);

	glBindProgramARB( GL_VERTEX_PROGRAM_ARB, 0 );
#endif
}

void unAvatar::update( double deltaTime ) 
{
    if ( modelData->update( deltaTime ) == true )
		{
        updateMeshes();
		}
}

void unAvatar::update() 
{
    if ( modelData->update() == true )
		{
        updateMeshes();
		}
}

void unAvatar::updateMeshes(void)
{
#if 0
    for(std::vector< Mesh* >::iterator
              u    = updatableMeshes.begin(),
              uEnd = updatableMeshes.end();
          u < uEnd; ++u )
		{
        (*u)->update();
		}

    for(RigidTransformsMap::iterator
              t    = rigidTransforms.begin(),
              tEnd = rigidTransforms.end();
          t != tEnd; ++t )
		{
        if ( modelData->getBoneParams( t->first ).changed )
			{
            t->second.first->setMatrix( modelData->getBoneMatrix( t->first ) );
			}
		}
#endif
}

void unAvatar::blendCycle(int id, float weight, float delay)
{
    modelData->getQunMixer()->blendCycle(id, weight, delay);
}

void unAvatar::clearCycle(int id, float delay)
{
    modelData->getQunMixer()->clearCycle( id, delay );
}

bool unAvatar::addAttachment(UInt16 i_Type, UInt16 i_BoneID)
{
	unMeshAttachment *i_MeshAttachment = new unMeshAttachment(i_Type, i_BoneID);

	m_Socket.push_back(i_MeshAttachment);

	return true;
}

#if defined(ENABLE_PX_PHYSICS)
void unAvatar::addClothAttachment(DigiClothMesh *i_ClothMesh, float i_x, float i_y, float i_z)
{
	///////// Create Cloth Attachment //////////
	m_ClothAttachment.push_back(Digi::DigiMassCore::instance()->acCloneCloth(i_ClothMesh, i_x, i_y, i_z));
}
#endif

/*const CoreModel* unAvatar::getCoreModel() const
{
    return modelData->getCoreModel();
}*/

/*const Model::MeshesList& Model::getMeshes(const std::string& name) const throw (std::runtime_error)
{
    MeshMap::const_iterator i = meshes.find( name );

    if ( i != meshes.end() )
		{
        return i->second;
		}
    else
		{
        throw std::runtime_error( "Model::getMeshes - can't find mesh \"" + name + "\"" );
		}
}*/

/*void Model::accept(osg::NodeVisitor& nv)
{
    osgUtil::GLObjectsVisitor* glv = dynamic_cast< osgUtil::GLObjectsVisitor* >( &nv );

    if ( glv )
		{
        osg::notify( osg::INFO )
            << "compiling shaders and display lists" << std::endl;

        // -- Compile shaders --
        for(std::vector< Mesh* >::iterator
                  h    = updatableMeshes.begin(),
                  hEnd = updatableMeshes.end();
              h != hEnd; ++h )
			{
            (*h)->accept( glv );
			}

        for(std::vector< Mesh* >::iterator
                  h    = nonUpdatableMeshes.begin(),
                  hEnd = nonUpdatableMeshes.end();
              h != hEnd; ++h )
			{
            (*h)->accept( glv ); // <- is it needed, they don't change state set
			}
    }

    osg::Group::accept( nv );        
}*/

//////////////////////////
/////// ModelData ////////

ModelData::ModelData(QunCoreModel* cm, QunModel* m)
{
    //qunModel = new QunModel( coreModel->getQunCoreModel() );
    //qunModel->update( 0 );
    //qunMixer = (QunMixer*)qunModel->getAbstractMixer();
	//qunModel = new QunModel( cm->getQunCoreModel() );

	//unAvatar *model;
	qunModel = m;
	CoreModel = cm;
    //QunMixer *qunMixer;

    const std::vector< QunBone* >& vectorBone = qunModel->getSkeleton()->getVectorBone();

    bones.resize( vectorBone.size() + 1 );
    // last bone is always no rotation/translation and used for
    // unrigged vertices.

    std::vector< QunBone* >::const_iterator b = vectorBone.begin();        
    for ( BoneParamsVector::iterator
              bp = bones.begin(),
              bpEnd = bones.end() - 1;
          bp < bpEnd; ++bp, ++b )
		{
        bp->bone = *b;
		}
}

ModelData::~ModelData()
{
    delete qunModel;
}

/*Model* ModelData::getModel() throw (std::runtime_error)
{
    if ( model.valid() )
		{
        return model.get();
		}
    else
		{
        throw std::runtime_error( "ModelData::getModel() -- model was already deleted" );
		}
}*/

inline float square( float x )
{
    return x*x;
}

bool ModelData::update(float deltaTime)
{
    // -- Update qunMixer & skeleton --
    if ( //qunMixer->getAnimationVector().size() == <total animations count>
         qunMixer->getAnimationActionList().size() == 0 &&
         qunMixer->getAnimationCycle().size() == 0 )
		{
        return false; // no animations, nothing to update
		}

    qunMixer->updateAnimation( deltaTime ); 
    qunMixer->updateSkeleton();

    return update();
}

bool ModelData::update(void)
{
    // -- Update bone parameters --
    bool anythingChanged = false;
    for ( BoneParamsVector::iterator
              b    = bones.begin(),
              bEnd = bones.end() - 1;
          b < bEnd; ++b )
		{
        const QunQuaternion& rotation = b->bone->getRotationBoneSpace();
        const QunVector&     translation = b->bone->getTranslationBoneSpace();
        const QunMatrix&     rm = b->bone->getTransformMatrix();

        pMatrix r;

		r.mf[0] = rm.dxdx;
		r.mf[1] = rm.dydx;
		r.mf[2] = rm.dzdx;
		r.mf[3] = 0.0;
        r.mf[4] = rm.dxdy;
		r.mf[5] = rm.dydy;
		r.mf[6] = rm.dzdy;
		r.mf[7] = 0.0;
        r.mf[8] = rm.dxdz;
		r.mf[9] = rm.dydz;
		r.mf[10] = rm.dzdz;
		r.mf[11] = 0.0;
        r.mf[12] = 0;
		r.mf[13] = 0;
		r.mf[14] = 0;
		r.mf[15] = 1.0;

        const pVector t( translation.x, translation.y, translation.z );

        // -- Check for deformed --
        b->deformed =
            // cal3d reports nonzero translations for non-animated models
            // and non zero quaternions (seems like some FP round-off error). 
            // So we must check for deformations using some epsilon value.
            // Problem:
            //   * It is cal3d that must return correct values, no epsilons
            // But nevertheless we use this to reduce CPU load.

            t.length() > /*boundingBox.radius() **/ 1e-5 // usually 1e-6 .. 1e-7
            ||
            pVector( rotation.x,
                        rotation.y,
                        rotation.z ).length() > 1e-6 // usually 1e-7 .. 1e-8
            ;

        // -- Check for changes --
        float s = 0;

        s += square( r.mf[0] - b->rotation.mf[0] );
		s += square( r.mf[1] - b->rotation.mf[1] );
		s += square( r.mf[2] - b->rotation.mf[2] );

		s += square( r.mf[4] - b->rotation.mf[4] );
		s += square( r.mf[5] - b->rotation.mf[5] );
		s += square( r.mf[6] - b->rotation.mf[6] );

		s += square( r.mf[8] - b->rotation.mf[8] );
		s += square( r.mf[9] - b->rotation.mf[9] );
		s += square( r.mf[10] - b->rotation.mf[10] );

        s += ( t - b->translation ).length2();

        if ( s < 1e-7 ) // usually 1e-11..1e-12
			{
            b->changed = false;
			}
        else
			{
            b->changed = true;
            anythingChanged = true;
            b->rotation = r;
            b->translation = t;
			}

//         std::cout << "bone: " << b->bone->getCoreBone()->getName() << std::endl
//                   << "quaternion: "
//                   << rotation.x << ' '
//                   << rotation.y << ' '
//                   << rotation.z << ' '
//                   << rotation.w << std::endl
//                   << "translation: "
//                   << t.x() << ' ' << t.y() << ' ' << t.z()
//                   << "; len = " << t.length()
//                   << "; s = " << s // << std::endl
//                   << "; changed = " << b->changed // << std::endl
//                   << "; deformed = " << b->deformed // << std::endl
// //                  << "len / bbox.radius = " << translation.length() / boundingBox.radius()
//                   << std::endl;
    }

    return anythingChanged;
}


#if 0
HardwareMesh::HardwareMesh( ModelData*      _modelData,
                            const CoreMesh* _mesh )
    : Mesh( _modelData, _mesh )
{   
    setUseDisplayList( false );
    setSupportsDisplayList( false );
    // ^ no display lists since we create them manually
    
    setUseVertexBufferObjects( false ); // false is default

    if ( mesh->data->rigid )
    {
        setVertexArray( mesh->data->vertexBuffer.get() );
    }
    else
    {
        setVertexArray( (VertexBuffer*)mesh->data->vertexBuffer->clone( osg::CopyOp::DEEP_COPY_ALL ) );
    }

    addPrimitiveSet( mesh->data->indexBuffer.get() ); // DrawElementsUInt

    boundingBox = mesh->data->boundingBox;

    onParametersChanged( MeshParameters::defaults() );
}

#if 0
void HardwareMesh::onParametersChanged( const MeshParameters* previousDs )
{
    setStateSet( mesh->data->rigid ? mesh->stateSets->staticStateSet.get() : mesh->stateSets->stateSet.get() );
//    setStateSet( mesh->stateSets->staticStateSet.get() );
    // Initially we use static (not skinning) state set. It will
    // changed to skinning (in update() method when some animation
    // starts.

    // -- Add or remove depth mesh --
    if ( !(mesh->stateSets->staticStateSet.get()->getRenderingHint()
           & osg::StateSet::TRANSPARENT_BIN) ) // no depth meshes for transparent materials
    {
        if ( mesh->parameters->useDepthFirstMesh
             &&
             !previousDs->useDepthFirstMesh )
        {
//            std::cout << "Adding depth mesh to " << mesh->data->name << std::endl;
            depthMesh = new DepthMesh( this );
            modelData->getModel()->addDepthMesh( depthMesh.get() );
        }
        else if ( !mesh->parameters->useDepthFirstMesh
                  &&
                  previousDs->useDepthFirstMesh )
        {
//            std::cout << "Removing depth mesh from " << mesh->data->name << std::endl;
            modelData->getModel()->removeDepthMesh( depthMesh.get() );
            depthMesh = 0;
        }        
    }    
}
#endif

static
const osg::Program::PerContextProgram*
getProgram( osg::State& state,
            const osg::StateSet* stateSet )
{
    const osg::Program* stateProgram =
        static_cast< const osg::Program* >
        ( stateSet->getAttribute( osg::StateAttribute::PROGRAM ) );
//        ( state.getLastAppliedAttribute( osg::StateAttribute::PROGRAM ) ); <- don't work in display lists

    if ( stateProgram == 0 )
    {
        throw std::runtime_error( "HardwareMesh::drawImplementation(): can't get program (shader compilation failed?" );
    }

    return stateProgram->getPCP( state.getContextID() );
}

void HardwareMesh::drawImplementation( osg::RenderInfo& renderInfo, const osg::StateSet* stateSet ) const
{
    osg::State& state = *renderInfo.getState();

    const osg::Program::PerContextProgram* program = getProgram( state, stateSet );
    const osg::GL2Extensions* gl2extensions = osg::GL2Extensions::Get( state.getContextID(), true );

    // -- Setup rotation/translation uniforms --
//    if ( deformed )
    if ( mesh->data->rigid == false )
    {
        // -- Calculate and bind rotation/translation uniforms --
        GLint rotationMatricesAttrib = program->getUniformLocation( "rotationMatrices" );
        if ( rotationMatricesAttrib < 0 )
        {
            rotationMatricesAttrib = program->getUniformLocation( "rotationMatrices[0]" );
            // Why the hell on ATI it has uniforms for each
            // elements? (nVidia has only one uniform for the whole array)
        }
    
        GLint translationVectorsAttrib = program->getUniformLocation( "translationVectors" );
        if ( translationVectorsAttrib < 0 )
        {
            translationVectorsAttrib = program->getUniformLocation( "translationVectors[0]" );
        }

        if ( rotationMatricesAttrib < 0 || translationVectorsAttrib < 0 )
        {
            throw std::runtime_error( "no rotation/translation uniforms in deformed mesh?" );
        }

        static const std::vector< osg::Matrix3 > noRotation( 31 );
        static const std::vector< osg::Vec3f >   noTranslation( 31 );

        int boneCount = mesh->data->getBonesCount();

        if ( deformed )
        {
            GLfloat rotationMatrices[31][9];
            GLfloat translationVectors[31][3];

            for( int boneIndex = 0; boneIndex < boneCount; boneIndex++ )
            {
                modelData->getBoneRotationTranslation( mesh->data->getBoneId( boneIndex ),
                                                       &rotationMatrices[boneIndex][0],
                                                       &translationVectors[boneIndex][0] );
            }

            gl2extensions->glUniformMatrix3fv( rotationMatricesAttrib,
                                               boneCount, GL_FALSE,
                                               &rotationMatrices[0][0] );
            gl2extensions->glUniform3fv( translationVectorsAttrib,
                                         boneCount,
                                         &translationVectors[0][0] );
        }
        else
        {
            gl2extensions->glUniformMatrix3fv( rotationMatricesAttrib,
                                               boneCount, GL_FALSE,
                                               (const GLfloat*)&noRotation.front() );
            gl2extensions->glUniform3fv( translationVectorsAttrib,
                                         boneCount,
                                         (const GLfloat*)&noTranslation.front() );
        }
    }

    // -- Create display list if not yet exists --
    unsigned int contextID = renderInfo.getContextID();

    mesh->displayLists->mutex.lock();
    GLuint& dl = mesh->displayLists->lists[ contextID ];

    if( dl != 0 )
    {
        mesh->displayLists->mutex.unlock();
    }
    else
    {
        dl = generateDisplayList( contextID, getGLObjectSizeHint() );

        innerDrawImplementation( renderInfo, dl );
        mesh->displayLists->mutex.unlock();

        mesh->displayLists->checkAllDisplayListsCompiled( mesh->data.get() );
    }

    // -- Call display list --
    bool transparent = stateSet->getRenderingHint() & osg::StateSet::TRANSPARENT_BIN;
    GLint frontFacing = program->getUniformLocation( "frontFacing" );

    if ( transparent )
    {
        glCullFace( GL_FRONT ); // first draw only back faces
        gl2extensions->glUniform1f( frontFacing, 0.0 );
        glCallList( dl );
        glCullFace( GL_BACK ); // then draw only front faces
        gl2extensions->glUniform1f( frontFacing, 1.0 );
        glCallList( dl );
    }
    else if ( frontFacing >= 0 )
    {
        // first draw only front faces
        gl2extensions->glUniform1f( frontFacing, 1.0 );
        glCallList( dl );
        // then draw only back faces
        glCullFace( GL_FRONT ); 
        gl2extensions->glUniform1f( frontFacing, 0.0 );
        glCallList( dl );
        glCullFace( GL_BACK ); // restore backfacing mode
    }
    else
    {
        glCallList( dl );
    }

//     // get mesh material to restore glColor after glDrawElements call
//     const osg::Material* material = static_cast< const osg::Material* >
//         ( state.getLastAppliedAttribute( osg::StateAttribute::MATERIAL ) );
//     if ( material ) glColor4fv( material->getDiffuse( osg::Material::FRONT ).ptr() );
    // ^ seems that material color restoring is not needed when
    // glDrawElements call is placed into display list
}

void
HardwareMesh::compileGLObjects(osg::RenderInfo& renderInfo) const
{
//    osg::notify( osg::INFO )
//     std::cout
//         << "HardwareMesh::compileGLObjects for " << mesh->data->name << std::endl;
    Geometry::compileGLObjects( renderInfo );

    unsigned int contextID = renderInfo.getContextID();

    mesh->displayLists->mutex.lock();
    
    GLuint& dl = mesh->displayLists->lists[ contextID ];

    if( dl == 0 )
    {
        dl = generateDisplayList( contextID, getGLObjectSizeHint() );

        innerDrawImplementation( renderInfo, dl );
        mesh->displayLists->mutex.unlock();

        mesh->displayLists->checkAllDisplayListsCompiled( mesh->data.get() );
    }
    else
    {        
        mesh->displayLists->mutex.unlock();
    }
}

void HardwareMesh::accept( osgUtil::GLObjectsVisitor* glv )
{
    //osg::notify( osg::INFO )
//     std::cout
//         << "HardwareMesh::accept( osgUtil::GLObjectsVisitor* glv ) for "
//         << mesh->data->name << std::endl;
    if ( !mesh->data->rigid )
    {
        glv->apply( *mesh->stateSets->stateSet.get() );
    }
    else
    {
        glv->apply( *mesh->stateSets->staticStateSet.get() );
    }

    if ( depthMesh.valid() )
    {
        if ( !mesh->data->rigid )
        {
            glv->apply( *mesh->stateSets->depthOnly.get() );
        }
        else
        {
            glv->apply( *mesh->stateSets->staticDepthOnly.get() );            
        }
    }
}

void HardwareMesh::innerDrawImplementation(osg::RenderInfo& renderInfo, GLuint displayList ) const
{
#define glError()                                                       \
    {                                                                   \
        GLenum err = glGetError();                                      \
        while (err != GL_NO_ERROR) {                                    \
            fprintf(stderr, "glError: %s caught at %s:%u\n",            \
                    (char *)gluErrorString(err), __FILE__, __LINE__);   \
            err = glGetError();                                         \
        }                                                               \
    }

    osg::State& state = *renderInfo.getState();
    
    state.disableAllVertexArrays();

    // -- Setup vertex arrays --
#ifdef OSG_CAL_BYTE_BUFFERS
    #define NORMAL_TYPE         GL_BYTE
#else
    #define NORMAL_TYPE         GL_FLOAT
#endif
    state.setNormalPointer( NORMAL_TYPE, 0,
                            mesh->data->normalBuffer->getDataPointer() );

    if ( mesh->data->texCoordBuffer.valid() )
    {
        state.setTexCoordPointer( 0, 2, GL_FLOAT, 0,
                                  mesh->data->texCoordBuffer->getDataPointer() );
    }

    if ( mesh->data->tangentAndHandednessBuffer.valid() )
    {
//         state.setTexCoordPointer( 1, 4, GL_HALF_FLOAT_ARB/*GL_SHORT*//*NORMAL_TYPE*/, 0,
//                                   mesh->data->tangentAndHandednessBuffer->getDataPointer() );
        state.setTexCoordPointer( 1, 4, NORMAL_TYPE, 0,
                                  mesh->data->tangentAndHandednessBuffer->getDataPointer() );
    }
    
    GLushort* weightBuffer = NULL;

    if ( mesh->data->weightBuffer.valid() )
    {
//         weightBuffer = new GLushort[ mesh->data->weightBuffer->size() * 4 ];

//         GLushort* w = weightBuffer;
//         const GLfloat* wsrc = (const GLfloat*)mesh->data->weightBuffer->getDataPointer();
//         const GLfloat* wend = wsrc + mesh->data->weightBuffer->size() * 4;
//         while ( wsrc < wend )
//         {
//             *w++ = floatToHalf( *wsrc++ );
//         }
        
//         state.setTexCoordPointer( 2, mesh->data->maxBonesInfluence, GL_HALF_FLOAT_ARB, 4*2,
//                                   weightBuffer );
        state.setTexCoordPointer( 2, mesh->data->maxBonesInfluence, GL_FLOAT, 4*4,
                                  mesh->data->weightBuffer->getDataPointer() );
    }

    GLshort* matrixIndexBuffer = NULL;

    if ( mesh->data->matrixIndexBuffer.valid() )
    {
        matrixIndexBuffer = new GLshort[ mesh->data->matrixIndexBuffer->size() * 4 ];

        GLshort* mi = matrixIndexBuffer;
        const GLbyte* m   = (const GLbyte*)mesh->data->matrixIndexBuffer->getDataPointer();
        const GLbyte* end = m + mesh->data->matrixIndexBuffer->size() * 4;
        while ( m < end )
        {
            *mi++ = *m++;
        }
        
        state.setTexCoordPointer( 3, mesh->data->maxBonesInfluence, GL_SHORT, 4*2,
                                  matrixIndexBuffer );
//         state.setColorPointer( 4, GL_UNSIGNED_BYTE, 0,
//                                mesh->data->matrixIndexBuffer->getDataPointer() );
        // GL_UNSIGNED_BYTE only supported in ColorPointer not the TexCoord
        // but with color we need to multiply color by 255.0 in shader
        // and get slighlty less performance (~1%). So we create
        // GLshort data here. Hope the driver will convert it to bytes
        // when compiling display list.
    }

    state.setVertexPointer( 3, GL_FLOAT, 0,
                            mesh->data->vertexBuffer->getDataPointer() );

    // -- Draw our indexed triangles --
    if ( displayList != 0 )
    {
//         std::cout << "compiling display list for " << mesh->data->name << std::endl;
        glNewList( displayList, GL_COMPILE );
    }

    mesh->data->indexBuffer->draw( state, false );
//     // no visible speedup when using glDrawRangeElements
//     glDrawRangeElements(
//         GL_TRIANGLES,
//         0,
//         mesh->data->vertexBuffer->size(),
//         mesh->data->indexBuffer->size(),
//         GL_UNSIGNED_INT,                                                
//         (GLuint *)mesh->data->indexBuffer->getDataPointer() );          

    if ( displayList != 0 )
        //*glEndList();
    
    //glError();
    state.disableAllVertexArrays();

    delete[] matrixIndexBuffer;
    delete[] weightBuffer;
}

static inline osg::Vec3f mul3( const pMatrix m, const pVector& v)
{
	return pVector(m.m[0][0]*v.x + m.m[1][0]*v.y + m.m[2][0]*v.z,
                       m.m[0][1)*v.x + m.m[1][1]*v.y + m.m[2][1]*v.z,
                       m.m[0][2]*v.x + m.m[1][2]*v.y + m.m[2][2]*v.z);
}

void HardwareMesh::update(void)
{
    // -- Setup rotation matrices & translation vertices --
    typedef std::pair< osg::Matrix3, osg::Vec3f > RTPair;
    float rotationTranslationMatricesData[ 31 * sizeof (RTPair) / sizeof ( float ) ];
    // we make data to not init matrices & vertex since we always set
    // them to correct data
    RTPair* rotationTranslationMatrices = (RTPair*)(void*)&rotationTranslationMatricesData;

    deformed = false;
    bool changed = false;

    for( int boneIndex = 0; boneIndex < mesh->data->getBonesCount(); boneIndex++ )
    {
        int boneId = mesh->data->getBoneId( boneIndex );
        const ModelData::BoneParams& bp = modelData->getBoneParams( boneId );

        deformed |= bp.deformed;
        changed  |= bp.changed;

        RTPair& rt = rotationTranslationMatrices[ boneIndex ];

        rt.first  = bp.rotation;
        rt.second = bp.translation;
    }

    // -- Check for deformation state and select state set type --
//     if ( deformed )
//     {
//         setStateSet( mesh->stateSets->stateSet.get() );
//     }
//     else
//     {
//         setStateSet( mesh->stateSets->staticStateSet.get() );
//         // for undeformed meshes we use static state set which not
//         // perform vertex, normal, binormal and tangent deformations
//         // in vertex shader
//     }

    // -- Update depthMesh --
    if ( depthMesh.valid() )
    {
        depthMesh->update( deformed, changed );
    }

    // -- Check changes --
    if ( !changed )
    {
//        std::cout << "didn't changed" << std::endl;
        return; // no changes
    }

    rotationTranslationMatrices[ 30 ] = // last always identity (see #68)
        std::make_pair( osg::Matrix3( 1, 0, 0,
                                      0, 1, 0,
                                      0, 0, 1 ),
                        osg::Vec3( 0, 0, 0 ) );

    // -- Scan indexes --
    boundingBox = osg::BoundingBox();
    
    VertexBuffer&               vb  = *(VertexBuffer*)getVertexArray();
    const VertexBuffer&         svb = *mesh->data->vertexBuffer.get();
    const WeightBuffer&         wb  = *mesh->data->weightBuffer.get();
    const MatrixIndexBuffer&    mib = *mesh->data->matrixIndexBuffer.get();
   
    osg::Vec3f*        v  = &vb.front();      /* dest vector */   
    const osg::Vec3f*  sv = &svb.front();     /* source vector */   
    const osg::Vec4f*  w  = &wb.front();      /* weights */         
    const MatrixIndexBuffer::value_type*
                       mi = &mib.front();     /* bone indexes */
    osg::Vec3f*        vEnd = v + vb.size();  /* dest vector end */   
    
#define ITERATE( _f )                           \
    while ( v < vEnd )                          \
    {                                           \
        _f;                                     \
                                                \
        boundingBox.expandBy( *v );             \
        ++v;                                    \
        ++sv;                                   \
        ++w;                                    \
        ++mi;                                   \
    }

    #define x() r()
    #define y() g()
    #define z() b()
    #define w() a()

#define PROCESS_X( _process_y )                                         \
    if ( mi->x() != 30 )                                                \
        /* we have no zero weight vertices they all bound to 30th bone */ \
    {                                                                   \
        const osg::Matrix3& rm = rotationTranslationMatrices[mi->x()].first; \
        const osg::Vec3f&   tv = rotationTranslationMatrices[mi->x()].second; \
        *v = (mul3(rm, *sv) + tv) * w->x();                             \
                                                                        \
        _process_y;                                                     \
    }                                                                   \
    else                                                                \
    {                                                                   \
        *v = *sv;                                                       \
    }                                                                   

    // Strange, but multiplying each matrix on source vector works
    // faster than accumulating matrix and multiply at the end (as in
    // shader)
    //
    // Not strange:
    // mul3            9*  6+
    // mul3 + tv       9*  9+
    // (mul3 + tv)*w  12*  9+
    // v += ..        12* 12+ (-3 for first)
    // x4 48* 45+
    //
    // +=rm,+=tv      12* 12+ (-12 for first)
    // (mul3 + tv)*w  12*  9+
    // x4 60* 45+
    // accumulation of matrix is more expensive than multiplicating
    //
    //
    // And it seems that memory access (even for accumulating matix)
    // is really expensive (commenting of branches in accumulating code
    // doesn't change speed at all)

#define PROCESS_Y( _process_z )                                         \
    if ( w->y() )                                                   \
    {                                                                   \
        const osg::Matrix3& rm = rotationTranslationMatrices[mi->y()].first; \
        const osg::Vec3f&   tv = rotationTranslationMatrices[mi->y()].second; \
        *v += (mul3(rm, *sv) + tv) * w->y();                            \
                                                                        \
        _process_z;                                                     \
    }                                                                   

#define PROCESS_Z( _process_w )                                         \
    if ( w->z() )                                                       \
    {                                                                   \
        const osg::Matrix3& rm = rotationTranslationMatrices[mi->z()].first; \
        const osg::Vec3f&   tv = rotationTranslationMatrices[mi->z()].second; \
        *v += (mul3(rm, *sv) + tv) * w->z();                            \
                                                                        \
        _process_w;                                                     \
    }

#define PROCESS_W()                                                     \
    if ( w->w() )                                                       \
    {                                                                   \
        const osg::Matrix3& rm = rotationTranslationMatrices[mi->w()].first; \
        const osg::Vec3f&   tv = rotationTranslationMatrices[mi->w()].second; \
        *v += (mul3(rm, *sv) + tv) * w->w();                            \
    }

#define STOP

    switch ( mesh->data->maxBonesInfluence )
    {
        case 1:
	  //#pragma omp parallel for -
	  // w/o      - 1.5s
	  // 1thread  - 1.7s
	  // 2threads - 2.1s => no win here
            ITERATE( PROCESS_X( STOP ) );
            break;

        case 2:
	  //#pragma omp parallel for						
            ITERATE( PROCESS_X( PROCESS_Y ( STOP ) ) );
            break;

        case 3:
	  //#pragma omp parallel for					       
            ITERATE( PROCESS_X( PROCESS_Y ( PROCESS_Z( STOP ) ) ) );
            break;

        case 4:
	  //#pragma omp parallel for						
            ITERATE( PROCESS_X( PROCESS_Y ( PROCESS_Z( PROCESS_W() ) ) ) );
            break;

        default:
            throw std::runtime_error( "maxBonesInfluence > 4 ???" );            
    }

    dirtyBound();
}
#endif