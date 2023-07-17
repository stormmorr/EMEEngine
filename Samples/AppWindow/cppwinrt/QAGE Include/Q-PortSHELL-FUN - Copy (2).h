/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -QAGE -> PORTSHELL-
	- Minor Component -= Function Prototypes =-
		-Instance of Port Shell Header File-

*/

#ifndef __Q_PortSHELL_FUN__
#define __Q_PortSHELL_FUN__

#if 0	//Speed Boost #01
#define PS_ASM
#endif

#include "Q-FUNC-Datatypes.h"
#include "pMath.h"

//*#include "DigiMass.h"
#include "paralelo3d.h"

namespace GVARS
{

#if defined(WIN32)
	class ClassCache //Class Cache
		{
		public:
			float Cos, Sin;
			pVector pVector1, pResult;
			unsigned int m_ExecMode;
			float ScaleFT;
			int vPort[4];
			unsigned int i, k, l;

			static QpoVec3d campos;
			static QpoVec3d destpos;
			static QpoVec3d transvert;
			static QpoVec3d InVec;
			static QpoVec3d UpVec;
			static QpoVec3d LeftVec;

			static float m_Red;
			static float m_Green;
			static float m_Blue;
			static float m_Alpha;

			bool setExecMode(int i_ExecMode);
		};
#else
	class ClassCache //Class Cache
		{
		public:
			float Cos, Sin;
			pVector pVector1, pResult;
			unsigned int m_ExecMode;
			float ScaleFT;
			int vPort[4];
			unsigned int i, k, l;

			QpoVec3d campos;
			QpoVec3d destpos;
			QpoVec3d transvert;
			QpoVec3d InVec;
			QpoVec3d UpVec;
			QpoVec3d LeftVec;

			float m_Red;
			float m_Green;
			float m_Blue;
			float m_Alpha;

			bool setExecMode(int i_ExecMode);
		};
#endif

class Q_PORTShell
{
public:
	Q_PORTShell();
	~Q_PORTShell() {};

	//	[V]-ECTOR [P]-ROXY [S]-YSTEM

	static void Vec3d_AddScaled(QpoVec3d * vec1, float scale, QpoVec3d * dir, QpoVec3d * result);

	static void Vec3d_Subtract(QpoVec3d * vec1, QpoVec3d * vec2, QpoVec3d * result);

	static float Vec3d_Length(QpoVec3d * vec1);

#ifndef PS_ASM
	static float Vec3d_Normalize(QpoVec3d * V1);
#else
	static void Vec3d_Normalize(QpoVec3d * V1);
#endif

	static float Vec3d_DotProduct(QpoVec3d *V1, QpoVec3d *V2);

	static void Vec3d_CrossProduct(QpoVec3d * vec1, QpoVec3d * vec2, QpoVec3d * result);

	static void Vec3d_Inverse(QpoVec3d * vec1);

	static float Vec3d_DistanceBetween(QpoVec3d * vec1, QpoVec3d * vec2);

	static void Vec3d_New(QpoVec3d * vec1);

	static void Vec3d_Set(QpoVec3d * vec1, float x, float y, float z);

	static void Vec3d_Copy(QpoVec3d * vec1, QpoVec3d * vec2);

	static void Vec3d_Scale(QpoVec3d * vec1, float scale, QpoVec3d * result);

	static void Vec3d_Add(QpoVec3d * vec1, QpoVec3d * vec2, QpoVec3d * result);

	static bool Vec3d_Compare(QpoVec3d *V1, QpoVec3d *V2, float Tolerance);

	static bool Vec3d_IsValid(QpoVec3d *V);

	//[T]RANSFORM [P]ROXY [S]YSTEM

	static void Transform_New(QpoTransform * transform);

	static void Transform_Copy(const QpoTransform *Src, QpoTransform *Dst);

	static void Transform_Print(QpoTransform * transform);

	static bool Transform_TestIdentity(QpoTransform & transform);

	static void Transform_New_XRotation(QpoTransform * transform, float angle);

	static void Transform_New_YRotation(QpoTransform * transform, float angle);

	static void Transform_New_ZRotation(QpoTransform * transform, float angle);

	static void Transform_New_LeftUpIn(QpoTransform * result, QpoVec3d * left, QpoVec3d * up, QpoVec3d * in);

	static void Transform_Multiply(QpoTransform * transform1, QpoTransform * transform2, QpoTransform * result);

	static void Transform_Translate(QpoTransform * transform, float x, float y, float z);

	static void Transform_GetIn(QpoTransform * transform, QpoVec3d * result);

	static void Transform_GetLeft(QpoTransform * transform, QpoVec3d * result);

	static void Transform_GetRight(QpoTransform * transform, QpoVec3d * result);

	static void Transform_GetUp(QpoTransform * transform, QpoVec3d * result);

	static void Transform_GetIn(pMatrix * matrix, QpoVec3d * result);

	static void Transform_GetLeft(pMatrix * matrix, QpoVec3d * result);

	static void Transform_GetUp(pMatrix * matrix, QpoVec3d * result);

	static void Transform_SetTranslation(QpoTransform * transform, float IncX, float IncY, float IncZ);

	static void Transform_RotateX(QpoTransform * transform, float angle);

	static void Transform_RotateY(QpoTransform * transform, float angle);

	static void Transform_RotateZ(QpoTransform * transform, float angle);

	static void Transform_RotateVector(QpoTransform * transform, QpoVec3d * vec, QpoVec3d * result);

	static void Transform_Mirror(QpoTransform * source, QpoVec3d * planenormal, float planedist, QpoTransform * result);

	static void Transform_Transpose(const QpoTransform *M, QpoTransform *MInv);

	static void Transform_TransposeVector(QpoTransform * transform, QpoVec3d * Vector, QpoVec3d *Result);

	static bool Transform_IsOrthonormal(QpoTransform * transform);

	static bool Transform_IsOrthogonal(QpoTransform * M);

	static bool Transform_IsValid(QpoTransform * transform);

	static void Transform_Orthonormalize(QpoTransform * transform);

	static bool Poly_AddOnce(QpoVertex *Verts, int NumVerts, unsigned int Bitmap, UInt8 TypeFLAGS, UInt8 RendFLAGS, float Scale);

	static QpoPolygon * Poly_Add(QpoVertex *Verts, int NumVerts, unsigned int Bitmap, QInt TypeFLAGS, QInt RendFLAGS, float Scale);

	static void Draw_FillRect(const QpoRect *Rect, const QpoColor *Color);

	static void Body_GetBone(QpoBody * Body, int BoneIndex, const char **BoneName, QpoTransform * Attachment, int * ParBone);

	static void Light_Remove(QpoLight light);

	static QpoLight Light_AddtoWorld(QpoVec3d pos);

	static void Light_SetAttr(QpoLight Light, QpoVec3d *Pos, QpoColor *RGBA, float Radius, bool CastShadow);

	static void Sound_Capture_Start(void);

	static bool Sound_Capture_Progress(void);

	static bool Sound_Init(void);

	static void Sound_Load(QpoSoundDef* f_Stream, const char * Name, const char * File);

	static void Sound_Load_Play(QpoSoundDef* f_Stream, const char * Name, const char * File, float f_Volume);

	static float *Sound_Capture_Get(void);

	static void Sound_Process(void);

	static int Sound_FindSource(void);

	static QpoSound Sound_Play(QpoSoundDef SoundDef, float Volume, float Pan, float Pitch, bool Loop, QpoVec3d * Position);

	static QpoSound Sound_Play_Default(QpoSoundDef SoundDef, float Volume);

	static QpoSound Sound_Play_Effect(QpoSoundDef SoundDef, float Volume, float Pan, float Pitch, bool Loop, QpoVec3d * Position, bool i_RefreshEFX = true);

	static bool Sound_SetEffect(unsigned int i_Source, bool i_Refresh);

	static void Sound_Stop(QpoSound Sound);

	static void Sound_ClearEffect(void);

	static void Sound_Modify(QpoSound Sound, float Volume, float Pan, float Pitch, QpoVec3d * Position, QpoVec3d * Velocity);

	static void Sound_Close(QpoSoundDef Sound);

	static void Sound_Shutdown(void);

	static unsigned int Tex_LoadTexture(unsigned short Flags, const char * File);

	static unsigned int Tex_LoadAlphaTexture(const char * Name, const char * File, int color_key);

	static void Tex_Blit(unsigned int Texture, QpoRect *Brushrect,int x,int y);

	static void Tex_RemoveE(unsigned int Texture);

	static void Tex_RemoveW(unsigned int Texture);

	static void Tex_Delete(unsigned int Texture);

	static bool CheckLineBox(QpoVec3d B1, QpoVec3d B2, QpoVec3d L1, QpoVec3d L2, QpoVec3d* Hit);

	static bool GetIntersection(float fDst1, float fDst2, QpoVec3d P1, QpoVec3d P2, QpoVec3d* Hit);

	static bool InBox(QpoVec3d* Hit, QpoVec3d B1, QpoVec3d B2, int Axis);

	static bool Collision_Make_DMGSphere(QpoVec3d *Center, float f_Radius, float f_Power);

	static bool Collision_RayTest(QpoVec3d *Mins, QpoVec3d *Maxs, QpoVec3d *Back, QpoVec3d *Front, int UserFlags, bool Collision, bool *Context, QpoCollision *Col);

	static bool Collision_RayTest_Avatar(QpoVec3d *Mins, QpoVec3d *Maxs, QpoVec3d *Front, QpoVec3d *Back, int UserFlags, bool Collision, bool *Context, QpoCollision *Col, int f_AvID, bool f_Impactor = false);

	static bool Collision_RayTest_Projectile(QpoVec3d *Mins, QpoVec3d *Maxs, QpoVec3d *Front, QpoVec3d *Back, int UserFlags, bool Collision, bool *Context, QpoCollision *Col);

	static void Avatar_BlendPose(QpoAvatar Avatar, int Motion, float Time, QpoTransform * Transform, float BlendAmount);

	static void Avatar_SetPosePM(QpoAvatar Avatar, QpoMotion Motion, float Count, bool Unknown);

	static void Avatar_SetPose_LeftLeg(QpoAvatar Avatar, QpoMotion Motion, float Count, bool Unknown);

	static void Avatar_SetPose_RightLeg(QpoAvatar Avatar, QpoMotion Motion, float Count, bool Unknown);

	static void Avatar_SetPose_LeftArm(QpoAvatar Avatar, QpoMotion Motion, float Count, bool Unknown);

	static void Avatar_SetPivot(QpoAvatar Avatar, QpoMotion Motion, float Count, bool Unknown);

	static void Avatar_SetPose_RightArm(QpoAvatar Avatar, QpoMotion Motion, float Count, bool Unknown);

	static void Avatar_SetPoseAP(QpoAvatar * Avatar, QpoMotion Motion, float Count, QpoTransform * transform);

	static void Avatar_AddtoWorld(QpoAvatar * Avatar, Uint32 UserFlags);

	static void Avatar_Attach(QpoAvatar * Slave, const char *SlaveBoneName, QpoAvatar * Master, const char *MasterBoneName, QpoTransform * attachment);

	static void Avatar_SetBoneAttach(QpoAvatar * Avatar, const char *BoneName, QpoTransform * Transform);

	static void Avatar_Detach(QpoAvatar * Slave);

	static void Avatar_Remove(QpoAvatar * Avatar);

	static void Avatar_SetExtBox(QpoAvatar * Avatar, QpoExtBox * ExtBox, const char *BoneAnchor);

	//static void Qpo_Avatar_SetEnviroAttr(Q_Forge->Forge[AVATARCNT].AV.Avatar, &_->AvatarEnviro );

	//static void Qpo_Avatar_Destroy(&Q_Forge->Forge[0].AV.Avatar);

	//static void Qpo_Avatar_SetStaticLightAttr( Q_Forge->Forge[AVATARCNT].AV.Avatar, true, true, 10 );

	static void Avatar_SetScale(QpoAvatar * Avatar, float ScaleX, float ScaleY, float ScaleZ);

	static void Avatar_SetAlpha(QpoAvatar * Avatar, float Alpha);

	static void Avatar_GetTex(QpoAvatar * Avatar, int Num, unsigned int Texture, float * Red, float * Green, float * Blue);

	static void Avatar_SetTex(QpoAvatar * Avatar, int Num, unsigned int Texture, float * Red, float * Green, float * Blue);

	static void Mesh_GetTex(QpoInstanceFlags * Avatar, int Num, unsigned int Texture, float * Red, float * Green, float * Blue);

	static void Mesh_SetTex(QpoInstanceFlags * Avatar, int Num, unsigned int Texture, float * Red, float * Green, float * Blue);

	static void Avatar_ClearPose(QpoAvatar Avatar, QpoTransform * ShieldActorXform);

	static void Avatar_SetLighting(QpoAvatar * Avatar, bool, QpoVec3d * Vec1, float, float, float, float, float, float, bool, int, bool, bool);

	static void Avatar_GetBoneTransform(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone);

	static void Avatar_GetBoneTransformMP(QpoAvatarFlags f_AV, const char * String, QpoTransform * Bone);

	static void AvatarView_GetBoneTransform(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone, bool IsPlayer);

	static void AvatarView_GetBoneTransform_PntSprite(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone);

	static void WeaponView_GetBoneTransform(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone);

	static void Avatar_GetTransformAvatar(QpoAvatarFlags * f_AV, const char * String, QpoTransform * Bone, int AIcounters, bool f_IsPlayer);

	static void Avatar_WeaponView_GetBoneTransform(int i_AvatarIndex, const char * String, QpoTransform * Bone);

	static void Avatar_GetWeaponTransform_s(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone, bool f_IsPlayer);

	static void Avatar_GetWeaponTransform_old(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone);

	static void Avatar_GetWeaponTransform(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone);

	static void Avatar_RenderWeaponTransform(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone);	

	static void Avatar_GetJointTransform(QpoPose Pose, int BoneNum, QpoTransform * BoneTransform);

	static void Avatar_SetJointTransform(QpoPose Pose, int BoneNum, QpoTransform * BoneTransform);

	//static void Avatar_GetExtBox(QpoAvatarFlags i_AvatarFlags, QpoAvExtBox * i_BoneBox);

	static QpoMotion Avatar_GetMotionByName(QpoAvatar_Def * Avatar_Def, const char *Name);

	/// Check if two avatars are not equal
	friend bool operator != (const QpoAvatar& a1, const QpoAvatar& a2)
		{
		/*if (m1.m11 != m2.m11 || m1.m12 != m2.m12 || m1.m13 != m2.m13) return true;
		if (m1.m21 != m2.m21 || m1.m22 != m2.m22 || m1.m23 != m2.m23) return true;
		if (m1.m31 != m2.m31 || m1.m32 != m2.m32 || m1.m33 != m2.m33) return true;*/

		//WritableObject<icAvatar> avatar1 (a1.Mesh);
		//WritableObject<icAvatar> avatar2 (a2.Mesh);

		/*if(avatar1 == avatar2 &&
		a1.Pose == a2.Pose &&
		a1.IDflag == a2.IDflag &&
		a1.Visible == a2.Visible) return true;
		else*/ return false;
		}

	friend bool operator!= (const QpoAvatar a1, const int a2)
		{
		/*if (m1.m11 != m2.m11 || m1.m12 != m2.m12 || m1.m13 != m2.m13) return true;
		if (m1.m21 != m2.m21 || m1.m22 != m2.m22 || m1.m23 != m2.m23) return true;
		if (m1.m31 != m2.m31 || m1.m32 != m2.m32 || m1.m33 != m2.m33) return true;*/

		//WritableObject<icAvatar> avatar1 (a1.Mesh);

		/*if(2 == a2 &&
		a1.Pose == a2 &&
		a1.IDflag == a2 &&
		a1.Visible == a2) return true;
		else*/ return false;
		}

	static void Player_SetMatrix(void);

	static QpoFog * Fog_AddtoWorld(void);

	static void Fog_RemovefromWorld(QpoFog * fog);

	static void Fog_SetAttr(QpoFog * fog, QpoVec3d * pos, QpoColor * color, float LightBrightness, float VolumeBrightness, float VolumeRadius);

	//static QpoFog Qpo->Fog_AddtoWorld(World);

	//static void Qpo->Fog_RemovefromWorld(World, player[g_Player]->EnergyArchitect.Fogobj);

	//static void Qpo->Fog_SetAttr(player[g_Player]->EnergyArchitect.Fogobj, &player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation, &player[g_Player]->EnergyArchitect.FogColour, 50, Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Fog.Scale, 20000);

	//static void Qpo_Engine_SetViewFogAttr(Engine, true, 60, 60, 60, VisClipDist - 50,VisClipDist);

	//static void Qpo->Engine_SetGamma(gama);

	//static void Qpo->Engine_ScreenShot(Engine, ScreenShot);

	static void GUI_Printf(int x,int y, const char *String, ...);

	//static void Qpo_Camera_SetFarClipPlane(Camera, true, VisClipDist);

	//static void Qpo->Camera_SetAttr(Camera, 2 - player[g_Player]->WeaponZoomFACT, &TempRect1);

	//static void Qpo->Camera_SetTransform(Camera, &player[g_Player]->ViewXForm);

	//static void Qpo->Camera_GetClippingRect(Camera, &TempRect1);

	static void Player_GetBoneBoundingBox(const char *BoneName, QpoVector *Corner, QpoVec3d *DX, QpoVec3d *DY, QpoVec3d *DZ);

	static void Avatar_GetBoneBoundingBox(unsigned int i_AVIndex, const char *BoneName, QpoVector *Corner, QpoVec3d *DX, QpoVec3d *DY, QpoVec3d *DZ);

	static void Player_GetBoneBoxes(const char *BoneName, QpoVector *Corner, QpoVec3d *DX, QpoVec3d *DY, QpoVec3d *DZ, QpoVectorBox *i_ExtBox);

	static void Avatar_GetBoneBoxes(unsigned int i_AVIndex, const char *BoneName, QpoVector *Corner, QpoVec3d *DX, QpoVec3d *DY, QpoVec3d *DZ, QpoVectorBox *i_ExtBox);

	static void Player_RenderBoneBoundingBox(const char *BoneName);

	static void Avatar_RenderBoneBoundingBox(unsigned int i_AVIndex, const char *BoneName);

	static void Player_RenderBoundingBoxes(void);

	static void Avatar_RenderBoundingBoxes(unsigned int i_AVIndex);

	static void Mesh_SetScale(QpoInstanceFlags * i_Instance, float newScaleX, float newScaleY, float newScaleZ);

	static void Mesh_SetAlpha(QpoInstanceFlags * i_Instance, float Alpha);

	static void Engine_ScreenShot(const char *FileName);

	static void Camera_SetTransform(int/*Camera*/camera, QpoTransform * transform, QpoVec3d Position);

	static void Camera_GetClippingRect(int/*Camera*/camera, QpoRect * rect);

	static void Camera_SetAttr(int/*Camera*/camera, float FOV, QpoRect * rect);

	static void Camera_SetFOV(int/*Camera*/camera, float FOV);

	static void Camera_Set(void);

	static void Camera_SetPlayer(void);

	static void Camera_SetAvatar(unsigned int i_AVIndex);

	static void Engine_SetGamma(float gama);

	static void Box_ComputeGlobalFrameAxes(QpoBox* Box);

	static void Box_Set(QpoBox* Box, float xScale, float yScale, float zScale, const QpoTransform* Transform);

	static void Box_SetXForm(QpoBox* Box, const QpoTransform* Transform);

	static bool Box_DetectCollisionBetween(QpoBox* Box1, QpoBox* Box2);

	static void Box_Render(QpoBox i_Box);

	static bool Player_ExtBox_intersect(unsigned int i_AVIndex);

	static bool Avatar_Player_ExtBox_intersect(unsigned int i_AVIndex);

	static bool Player_Player_ExtBox_intersect(unsigned int i_PLIndex);

	static bool Avatar_ExtBox_intersect(unsigned int i_AVIndex1, unsigned int i_AVIndex2);

	static bool Collision_Player_Intersect(unsigned int i_AVIndex);

	static bool Collision_Avatar_Player_Intersect(unsigned int i_AVIndex);

	static bool Collision_Avatar_Intersect(unsigned int i_AVIndex1, unsigned int i_AVIndex2);

	static void resetExecMode(void);

	///// Code Playback Functions /////
	inline void Pause(void) { for (;;) {} };

	///// Class Cache /////
	ClassCache m_CC;
};

#define QNOMAI 405

extern Q_PORTShell* Qpo;

extern bool ag_PortShell_Initialisation(void);

};

namespace QAGE
{
extern bool g_PlayerForgeBoxxed;
}

#pragma message ("***  Primary Internal Porting Function Prototypes  [Q-PortSHELL-FUN.h]")

#endif