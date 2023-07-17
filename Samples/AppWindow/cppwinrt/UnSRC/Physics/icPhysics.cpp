/*

CharacterControl - PhysX Character Control and collision detection
Copyright RageComm (C) 2007 by Max Lawlor
SomptingSOFT Portal www.stss.co.nr

*/

//----------------------------------------------------------------------------//
// Includes                                                                   //
//----------------------------------------------------------------------------//

#include "icPhysics.h"
#include "Loader/icTextureBank.h"
#include "Game.h"

using namespace nvsg;
using namespace nvutil;
using namespace nvmath;

//----------------------------------------------------------------------------//
// Instance                                                                   //
//----------------------------------------------------------------------------//

icPhysics* icPhysics::s_instance = 0;
icPhysics* icPhysics::instance()
{
  return s_instance;
}

//----------------------------------------------------------------------------//
// Constructor                                                                //
//----------------------------------------------------------------------------//

icPhysics::icPhysics() :
gDefaultGravity(0.0f, -9.81f, 0.0f)
{
  assert(s_instance == 0);
  s_instance = this;

  gMyAllocator = NULL;
  gPhysicsSDK = NULL;

  gScene = NULL;

  // Initialise Variables
  gPause = false;
  G = -98.1f;//-50.0f;
  gApplyGravity = true;
  gTimestepMultiplier	= 1.0f;

  gRigidLink		= false;
  gFixedStep		= false;

  gActive = false;
  firstRun = false;
}

//----------------------------------------------------------------------------//
// Destructor                                                                 //
//----------------------------------------------------------------------------//

icPhysics::~icPhysics()
{
  s_instance = 0;
}

#if 0
class Jump
{
public:
  Jump();

  NxF32	mV0;
  NxF32	mJumpTime;
  bool	mJump;

  void	startJump(NxF32 v0);
  void	stopJump();
  NxF32	getHeight(NxF32 elapsedTime);
};

Jump::Jump() :
mJump		(false),
mV0			(0.0f),
mJumpTime	(0.0f)
{
}

void Jump::startJump(NxF32 v0)
{
  if(mJump)	return;
  mJumpTime = 0.0f;
  mV0	= v0;
  mJump = true;
}

void Jump::stopJump()
{
  if(!mJump)	return;
  mJump = false;
}

NxF32 Jump::getHeight(NxF32 elapsedTime)
{
  if(!mJump)	return 0.0f;
  mJumpTime += elapsedTime;
  NxF32 h = G*mJumpTime*mJumpTime + mV0*mJumpTime;
  return (h - gDefaultGravity.y)*elapsedTime;
}

static Jump gJump[NB_CHARACTERS];

static MouseFilter gFilter;
#endif

//----------------------------------------------------------------------------//
// Initialisation                                                             //
//----------------------------------------------------------------------------//
void icPhysics::acInit(void)
{
  gMyAllocator = new UserAllocator;

  bool status = InitCooking();
  if (!status)
  {
    printf("Unable to initialize the cooking library. Please make sure that you have correctly installed the latest version of the AGEIA PhysX SDK.");
    exit(1);
  }

  // Initialize PhysicsSDK
  gPhysicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, gMyAllocator, &gErrorStream);
  if(!gPhysicsSDK) return;

  gPhysicsSDK->setParameter(NX_SKIN_WIDTH, 0.025f);

  gPhysicsSDK->setParameter(NX_VISUALIZATION_SCALE, 1.0f);
  gPhysicsSDK->setParameter(NX_VISUALIZE_COLLISION_SHAPES, 1);

  acCreateScene();

  printf("PhysX AGEIA Initialisation Complete\n");
}

void icPhysics::acInitCCT(void)
{
}

void icPhysics::acCreateScene(void)
{
  if(gPhysicsSDK)
  {
    // Create a scene
    NxSceneDesc sceneDesc;
    sceneDesc.gravity				= gDefaultGravity;
    gScene = gPhysicsSDK->createScene(sceneDesc);

    NxMaterial * defaultMaterial = gScene->getMaterialFromIndex(0); 
    defaultMaterial->setRestitution(0.0f);
    defaultMaterial->setStaticFriction(0.5f);
    defaultMaterial->setDynamicFriction(0.5f);

    //acCreatePhysicsTerrain();
    //acInitCCT();
  }
}

void icPhysics::acReleaseScene(void)
{
  if(gPhysicsSDK)
  {
    if(gScene)
    {
      NxScene* scene = gScene;
      gScene = NULL;

      // Release our objects
      NxU32 nbActors = scene->getNbActors();
      NxActor** actors = scene->getActors();

      gPhysicsSDK->releaseScene(*scene);
    }
  }
}

void icPhysics::acResetScene(void)
{
  acReleaseScene();
  //createScene();
}

void icPhysics::acNxExit(void)
{
  //	releaseCharacterControllers(*gScene);

  /*if(gTerrainData!=NULL)
  {
  delete gTerrainData;
  gTerrainData=NULL;
  }*/

  acReleaseScene();
  gPhysicsSDK->release();

  if(gMyAllocator!=NULL)
  {
    delete gMyAllocator;
    gMyAllocator=NULL;
  }
}

void icPhysics::acFrame(void)
{
  if(!gScene)	return;

  NxF32 elapsedTime = getElapsedTime();
  elapsedTime *= gTimestepMultiplier;
  if(elapsedTime <= 0)
    elapsedTime = 0;

  // Physics code
  if(!gPause)	
  {
    NxVec3 disp = gDefaultGravity;
    if(!gApplyGravity) disp.zero();

    float TimeStep = 1.0f / 60.0f;

    gScene->simulate(elapsedTime);
    gScene->flushStream();
    gScene->fetchResults(NX_RIGID_BODY_FINISHED, true);

    //gScene->unlockQueries();

    NxReal maxTimestep;
    NxTimeStepMethod method;
    NxU32 maxIter;
    NxU32 numSubSteps;
    gScene->getTiming(maxTimestep, maxIter, method, &numSubSteps);
    if (numSubSteps) icCharacterController::updateControllers ();
  }
  // ~Physics code

}