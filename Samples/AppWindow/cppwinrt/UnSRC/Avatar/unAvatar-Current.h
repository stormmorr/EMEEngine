/*

    unAvatar
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef __unAvatar__
#define __unAvatar__

//----------------------------------------------------------------------------//
// Includes                                                                   //
//----------------------------------------------------------------------------//

#include "cal3d.h"
#include "../../Deps/p3d/pMath.h"

#if defined(WIN32)
//#include <glew.h>
#else
//#include <glew.h>
#endif

#include "unMeshAttachment.h"

#include "cal3d/vector.h"
#include "cal3d/quaternion.h"

#include "../Memory/unSegment.h"

#if 0
#include "../../DigitalMass/Source/Mesh/digiMesh.h"
#endif

#define QAGE_INCLUDES 1
#define MAXBONESPERMESH 29

typedef unsigned int GLuint;

//using namespace boost::interprocess;
//namespace ip = boost::interprocess;

//----------------------------------------------------------------------------//
// Class declaration                                                          //
//----------------------------------------------------------------------------//

class ModelData;
struct BoneParams;
class digiBodyMesh;

typedef struct Q_Mesh_Data
{
	int m_VertexCount;
	int m_FaceCount;
	int m_MeshCount;
	unsigned int m_TextureTag;
} Q_Mesh_Data;

typedef struct Q_Hard_Data
{
	int m_StartIndex;
	int m_FaceCount;
	int m_BoneCount;
	unsigned int m_TextureID;
	unsigned int m_IntanceTexture;
	int m_BonesIndices[35];
} Q_Hard_Data;

//typedef ip::allocator<Q_Hard_Data, managed_shared_memory::segment_manager> Alloc_HardMesh;
//typedef ip::vector<Q_Hard_Data, Alloc_HardMesh> UN_Vector_HardMesh;

class unAvatar
{
public:
	unAvatar();
	unAvatar(const unAvatar&);
	virtual ~unAvatar();

// member variables
public:
	int m_state;
	QunCoreModel* m_calCoreModel;
	QunModel* m_qunModel;
	QunHardwareModel* m_calHardwareModel;
	ModelData* modelData;
	int m_animationId[16];
	int m_meshId[32];
	int m_meshCount;
	GLuint m_textureId[32];
	int m_textureCount;
	float m_renderScale;
	float m_lodLevel;
	std::string m_path;
	float m_animtime;

	digiBodyMesh* m_digiBodyMesh;

	/// Player Character Variables
	float m_rotationy;
	float m_inx,m_iny,m_inz;
	int m_vertexCount;
	int m_faceCount;

	int m_BoneStructure;
	int m_BoneState;

#if defined(ENABLE_PX_PHYSICS)
	std::vector<DigiCloth*> m_ClothAttachment;
#endif

// member functions
public:
	float getLodLevel(void);
	void getMotionBlend(float *pMotionBlend);
	float getRenderScale(void);
	int getState(void);
	void acRenderMesh(bool bWireframe, bool bLight);
	void acRenderMeshSoft(bool bWireframe, bool bLight);
	void acRenderSkeleton(void);
	void acRenderMesh_Programs(void);
	void BeginAnim(void);
	void EndAnim(void);
	void BlendAnim(int i_Motion, float i_Time, float i_BlendAmount);
	void BlendAnimMin(int i_Motion, float i_Time, float i_BlendAmount);
	void BlendAnimTorque(int i_Motion, float i_Time, float i_BlendAmount);
	void BlendAnimPhysics(int i_Motion, float i_Time, float i_BlendAmount);
	void BlendAnimPhysicsSurgery(int i_Motion, float i_Time, float i_BlendAmount);
	void BlendAnimPhysicsProp(int i_Motion, float i_Time, float i_BlendAmount);
	void ClearAnimPhysics(void);
	void ApplyAnim(int i_Motion, float i_Time, float i_BlendAmount);
	void Animate_LeftLeg(int i_Motion, float i_Time, float i_BlendAmount);
	void Animate_RightLeg(int i_Motion, float i_Time, float i_BlendAmount);
	void Animate_LeftArm(int i_Motion, float i_Time, float i_BlendAmount);
	void Animate_RightArm(int i_Motion, float i_Time, float i_BlendAmount);
	void Animate_Pivot(int i_Motion, float i_Time, float i_BlendAmount);
	void onUpdate(float elapsedSeconds);
	void setLodLevel(float lodLevel);
	void setMotionBlend(float *pMotionBlend, float delay);
	void setState(int state, float delay);
	void setPosition(float i_x, float i_y, float i_z) { m_posx = i_x; m_posy = i_y; m_posz = i_z; }
	void acSetPose(void);
	void acSetPoseSurgery(void);
	void acSetPoseNew(void);
	void acPrintBonePos(unsigned int i_Index);
	void acPrintBoneAbsPos(unsigned int i_Index);

	void updateMeshes(void);

	/**
	* Update meshes.
	*/
	void update(double deltaTime);

	/**
	* Forced update of meshes, use it when you change bone
	* positions manually and don't run any animations.
	*/
	void update(void);

	/**
	* Blend animation cycle to the specified weight
	* in specified time.
	*/
	void blendCycle(int id, float weight, float delay);

	/**
	* Clear animation cycle in specified amount of time.
	*/
	void clearCycle(int id, float delay);

	//typedef std::vector< Mesh* > MeshesList;
	//typedef std::map< std::string, MeshesList > MeshMap;

	/**
	* Return list of meshes corresponding to specified name.
	*/
	//const MeshesList& getMeshes( const std::string& name ) const throw (std::runtime_error);

	//const MeshMap& getMeshMap() const { return meshes; }

	/**
	* Compiles hardware meshes state sets when accept osgUtil::GLObjectsVisitor.
	*/
	//virtual void accept( osg::NodeVisitor& nv );

	unsigned int m_vertexProgramId;
	unsigned int m_bufferObject[6];

	int AnimNumber;
	int m_oldanim;

	int SmoothOn;

	float m_posx;
	float m_posy;
	float m_posz;

	float angle;
	float m_fpsDuration;
	int m_fpsFrames;
	int m_fps;

	//UN_Vector_HardMesh *m_HardMesh;
	Q_Mesh_Data *m_MeshData;

public:		// Cloth Simulation
	struct
		{
		float x, y, z;
		} Sphere;

	int m_rebuild;

	void adjustSphere(float x, float y, float z) { Sphere.x += x; Sphere.y += y; Sphere.z += z; };

	std::vector<unMeshAttachment*> m_Socket;

	bool addAttachment(UInt16 i_Type, UInt16 i_BoneID);

#if defined(ENABLE_PX_PHYSICS)
	void addClothAttachment(DigiClothMesh *i_ClothMesh, float i_x, float i_y, float i_z);
#endif

protected:
	std::vector< BoneParams > m_bones;

public:
	void GLrenderMesh(bool bWireframe, bool bLight);
	void renderBoundingBox();
};

//----------------------------------------------------------------------------//

struct BoneParams
{
    BoneParams()
        : bone( 0 )
        , deformed( false )
        , changed( false )
		{}
    
    QunBone*	bone;
    pMatrix		rotation;
    pVector		translation;
    bool		deformed;
    bool		changed;
};

///////////////////////////
/////// Model data ////////

class ModelData
{
public:
    ModelData(QunCoreModel* cm, QunModel* m);
    ~ModelData();

    /**
     * Perform skeleton and BoneParams arrays update.
     * Return true, if something was changed, false otherwise.
     */
    bool update(float deltaTime);

    /**
     * Forced update of bone matrices, use it when you change
     * bone positions manually.
     */
    bool update(void);

    QunMixer* getQunMixer() { return qunMixer; }

    /**
     * Get rotation[9] and translation[3] ready for glUniform[Matrix]3fv.
     * Remark that you must pass not local bone index in mesh,
     * but bone id (using MeshData::getBoneId(index)).
     */
    void getBoneRotationTranslation(int boneId, GLfloat* rotation, GLfloat* translation) const
		{
        const BoneParams& b = bones[ boneId ];
        memcpy( rotation   , &b.rotation.m[0], 9 * sizeof( GLfloat ) );
		memcpy( translation, &b.translation.x, 3 * sizeof( GLfloat ) );
		}

    pMatrix getBoneMatrix(int boneId) const
		{
        const BoneParams& b = bones[ boneId ];
		pMatrix i_matrix;
        i_matrix.mf[0] = b.rotation.mf[0];
		i_matrix.mf[1] = b.rotation.mf[1];
		i_matrix.mf[2] = b.rotation.mf[2];
		i_matrix.mf[3] = 0.0;
        i_matrix.mf[4] = b.rotation.mf[3];
		i_matrix.mf[5] = b.rotation.mf[4];
		i_matrix.mf[6] = b.rotation.mf[5];
		i_matrix.mf[7] = 0.0;
        i_matrix.mf[8] = b.rotation.mf[6];
		i_matrix.mf[9] = b.rotation.mf[7];
		i_matrix.mf[10] = b.rotation.mf[8];
		i_matrix.mf[11] = 0.0;
        i_matrix.mf[12] = b.translation.x;
		i_matrix.mf[13] = b.translation.y;
		i_matrix.mf[14] = b.translation.z;
		i_matrix.mf[15] = 1.0;
		return i_matrix;
		}

    /**
     * Get bone parameters. Remark that we have
     * (skeleton bones count + 1) bones, since we add fake
     * non-moving bone for unrigged vertices.
     */
    const BoneParams& getBoneParams(int boneId) const
		{
        return bones[ boneId ];
		}

    //const QunCoreModel* getQunCoreModel() const { return QunCoreModel; }
    //QunModel*  getQunModel() { return qunModel; }

    /**
     * Returns associated model, throws error if the model was deleted.
     */
    //unAvatar* getModel() throw (std::runtime_error);

private:
    //osg::ref_ptr< QunCoreModel >   QunCoreModel;
    //osg::observer_ptr< Model >  model;

	unAvatar *model;
	QunCoreModel *CoreModel;
	QunModel *qunModel;
    QunMixer *qunMixer;

	typedef std::vector< BoneParams > BoneParamsVector;
    BoneParamsVector bones;
};

#if 0
class HardwareMesh : public Mesh
{
public:
   
    osg::Object* cloneType() const;
    osg::Object* clone( const osg::CopyOp& ) const;
    virtual bool isSameKindAs(const osg::Object* obj) const { return dynamic_cast<const HardwareMesh *>(obj)!=NULL; }
    virtual const char* libraryName() const { return "osgCal"; }
    virtual const char* className() const { return "HardwareMesh"; }

    HardwareMesh( ModelData*      modelData,
                  const CoreMesh* mesh );


    virtual void drawImplementation( osg::RenderInfo& renderInfo ) const;
    /**
     * Real draw implementation called from HardwareMesh & MeshDepth.
     * They differ in only in state sets so pass it explicitly.
     */
    void drawImplementation( osg::RenderInfo&     renderInfo,
                             const osg::StateSet* stateSet) const;

    virtual void compileGLObjects(osg::RenderInfo& renderInfo) const;

    virtual void update();

    /**
     * For compiling all statesets when Model accepts osgUtil::GLObjectsVisitor.
     */
    virtual void accept( osgUtil::GLObjectsVisitor* glv );

private:

    // TODO: merge MeshDepth & HardwareMesh into one
    // class and move all shared part into other structure.
    
    /**
     * Draw implementation part which resides in the display
     * list.
     * It performs all the drawing related calls except
     * rotation/translation uniforms setup (which is mesh dependent).
     */
    void innerDrawImplementation( osg::RenderInfo& renderInfo,
                                  GLuint           displayList = 0 ) const;

    virtual void onParametersChanged( const MeshParameters* previousDs );
};
#endif

#endif