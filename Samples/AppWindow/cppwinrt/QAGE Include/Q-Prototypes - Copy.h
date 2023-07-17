/*

	Quantum Angel Game Engine Codex
	-static Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Header File Classifications-
	- Minor Component -Internal Function Prototypes-

*/

#ifndef QPROTOTYPES_H
#define QPROTOTYPES_H

using namespace GVARS;

//--------------------------------------------------------------------
// INTERNAL FUNCTION PROTOTYPES
//--------------------------------------------------------------------

static  bool QpoLoadLevel(const char *FileName, const char *G3DMainFS, bool AddWorld );

namespace GVARS
{
class Q_COREFunctions
{
public:

	static void CoreAcquire(bool f_new = false);
	static void CoreRelease(void);

	static void CoreAllocate(void);
	static void CoreDeAllocate(void);

	//static HWND CreateMainWindow(HANDLE hInstance, char *AppName, int32 Width, int32 Height);

	//LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	static void ShutDown(void);
	static void LoadSetupFile(void);

	static void ColldetMelee(int bonenum, float attstt, float cutoff, float stroke, int HitType, int BlowHeight, int NumAttackHits);
	static void ColldetMeleeAI(int bonenum, float attstt, float cutoff, float stroke, int HitType, int BlowHeight, int NumAttackHits, int AIflag);

	static void StructureAInitialize(void);
	static int StructureA(const char* String);

	//~~~FROZEN
	//static void ColldetBullet(int AIflag, QpoVec3d BulletPos, int BullFLAG);
	//static void ColldetBulletAI(int AIflag, QpoVec3d BulletPos, int BullFLAG);
	//FROZEN~~~

	static void RadialDamage(int Team, int AvID, float ExpSize, float ExpDMG, QpoVec3d ExpPos, int DirFlag, QpoVec3d Direction);
	static void ProgressAttackMeM(int AIcounter);

	static void DrawFace(QpoVec3d **Verts);
	static void DrawOrientedBoundBox(QpoVec3d *Pos, QpoVec3d *DX, QpoVec3d *DY, QpoVec3d *DZ);
	static void DrawInVector(QpoTransform XForm, QpoVec3d Pos);
	static void DrawVector(QpoVec3d Pos, QpoVec3d Vector, int Mult);
	static float AnglesToPoint(QpoVec3d *s, QpoVec3d *d, QpoVec3d *a);

	static void COLDET_CupBlast(QpoTransform Limb, float DamageScale);
	static void TrailLineCreate(int AvID, int LengNum, QpoVec3d PosStart, QpoVec3d PosEnd, int BitmapPTR, float Red, float Green, float Blue, int Dir);
	static void FlameTrailCreate(int AvID, int LengNum, QpoVec3d PosStart, QpoVec3d PosEnd, int BitmapPTR, float Red, float Green, float Blue, int Dir);

		//Pin Effect Mesh Initialisation Functions
	static void PEF_CREATE_PinEffectMesh(QpoVec3d StartPos, float Scale, QpoVec3d VecIn, QpoVec3d VecRight, QpoVec3d VecUp);
	static void PEF_CREATE_RingPEFMesh(QpoVec3d StartPos, float Scale, int EffType);
	static void PEF_CREATE_SpherePEFMesh(QpoVec3d StartPos, QpoVec3d Center, float Radius, int EffType);

		//PEF Mesh Altering Routines
	static void PEF_ADDLINE_RingPEFMesh(QpoVec3d StartPos, float Scale, QpoVec3d VecIn, QpoVec3d VecRight, QpoVec3d VecUp, int MeshID);
	static void PEF_ADDLINE_TubePEFMesh(QpoVec3d StartPos, float Scale, QpoVec3d VecIn, QpoVec3d VecRight, QpoVec3d VecUp, int MeshID);

		//Pin Effect Mesh Control Functions
	static void PEF_CONTROL_FaceRippleMesh(int MeshID);
	static void PEF_CONTROL_RingRippleMesh(int MeshID);
	//static void PEF_CONTROL_RingRippleMesh2(int MeshID);
	static void PEF_CONTROL_RingShieldSphere(int MeshID);
	static void PEF_CONTROL_EnergyWake(int MeshID);

	static unsigned int acLoadTexture(int f_Int, std::string f_File);
	static unsigned int acLoadTextureAlpha(std::string f_Path, std::string f_Filename, int f_Int);
	static void InitTextures(void);
	static void CloseTextures(void);

	void LoadCharacterData(void);
	void LoadCharacterDataLegacy(void);
	void ResetCharacterData(void);
	void StartCharacterData(void);
	int ShowCharacterDialog(void);
	void CreateAngelData(void);
	Q_CharacterDATA *QShell_LoadCharUpdate(void);
	void WriteCharacterData(void);
	void WriteNEWCharacterData(Q_CharacterDATA WDATA);
	void WriteNEWCharacterDataV2(Q_CharacterDATA *WDATA, bool f_Allways = false);
	void WriteNEWCharacterDataV3(Q_CharacterDATA *WDATA);

	void addItem(Q_CharacterDATA *WDATA, int f_CharArray, int f_ItemArray);

	Q_ItemRef CreatePlayerItem(float VICTIMLVL, int f_TYPE = -1, float f_SPEC = -1);
	Q_ItemRef CreateAvatarItem(int CharDataID, float VICTIMLVL);

	Q_ItemRef New_New_New_CreatePlayerItem(float VICTIMLVL);

	int GetItemFACTORY(const char *ItemREF);

	//###

	static void QAEFFcontrolPLAYER(int QA_EFF_TYPE, float QA_EFF_INTENSITY, int QA_EFF_COL00RED, int QA_EFF_COL00GREEN, int QA_EFF_COL00BLUE, int QA_EFF_COL00ALPHA);
	static void QAEFFcontrolAI(int AIcounter, int QA_EFF_TYPE, float QA_EFF_INTENSITY, int QA_EFF_COL00RED, int QA_EFF_COL00GREEN, int QA_EFF_COL00BLUE, int QA_EFF_COL00ALPHA);

	static void ActivateItems(void);
	static void DeactivateItems(void);
	static void ActivateItemsAI(int AIcounter);
	static void DeactivateItemsAI(int AIcounter);

	static void DigitizeNumber(float Input);

	static bool AddDecal(QpoVec3d impact, QpoVec3d normal, float Scale, int DTYPE);
	static void AddTrailPNT(int ParentTRAIL, QpoVec3d Pos, QpoColor Color1, QpoColor Color2, QpoVec3d DriftVec, int Type);

		//AI Control Routines
	static void AIClericBrain(int AIcount);
	static bool AIFighterBrain(int AIcount);
	//static void AISoldierBrain(int AIcount);
	static void AICore(int AIcount);
	static void AICoreMB(int AIcount);
	static void Input(void);
	static void InputPK(void);

	static void AIFighterHeart(int AIcount);
	static void AIChemicalCalc(int AIcount);

	static void NNbotCONTROL(void);

		//Player Control Routines
	static void PLCore(void);
	static void PLCore_PushMouse(void);
	static void PLCore_PushKey(void);
	static void PLCoreMB(void);

	static void ShowLine(QpoVec3d *Start, QpoVec3d *End, QpoVec3d *CamPos, float width, unsigned int BitmapPtr, float alpha, float red, float green, float blue, int Flags);
	static void DrawRectFromVec3ds(QpoVec3d *vec1, QpoVec3d *vec2, QpoVec3d *vec3, QpoVec3d *vec4, unsigned int bmpPtr, float alpha, float red, float green, float blue, int Flags);
	//static void UpdateALL(void);

	//static void ReadMeMPathways(void);
	//static void WriteMeMPathways(void);
	static void PlayerSpawnNNbot(QpoVec3d PointOrigin);
	static void AISpawnNNbot(int AIcounter, QpoVec3d PointOrigin);

	static int Q_LineLineintersect(QpoVec3d p1,QpoVec3d p2,QpoVec3d p3,QpoVec3d p4,QpoVec3d *pa,QpoVec3d *pb/*,double *mua, double *mub*/);

		//### PHYSICS SYSTEM ###
	static QpoVec3d PHY_BounceVector(QpoVec3d TraVec, QpoVec3d Normal);

		//### AI Functions ###
	static bool AIFunctionsScannerCheck(int AIcounter);

	static void CONTROL_PlayerMuzzleFlash(void);
	static void CONTROL_AvatarMuzzleFlash(int AIcounter);

	static void CONTROL_PlayerPowerFlight(void);
	static void CONTROL_AvatarPowerFlight(int SCRAM);

	//static bool ShowOptionsDialog(HINSTANCE hInstance);

	static void CONTROL_PlayerGraphicsControl(void);
	static void CONTROL_PlayerClericShieldControl(void);
	static void CONTROL_AvatarClericShieldControl(int SCRAM);
	static void CONTROL_Jinks(void);
	static void InitSounds(void);
	static void InitSoundsNum(void);
	static std::string acGetSound(int f_Index);
	static void acSendSound(int f_Index);
	static void CloseSounds(void);
	static void World_Event_Engine(void);

	static void PlayerJumpEffect(void);
	static void AvatarJumpEffect(int AIcounter);
	static void PlayerJinkBlast(void);
	static void AvatarJinkBlast(int AIcounter);
	static void PlayerJinkRushCloud(void);
	static void CloudManagement(void);
	static void PntSpriteManagement(void);

	static void ReadMeMPathways(void);
	static void WriteMeMPathways(void);
	static void FileGen(void);

};

static Q_COREFunctions Q;

//##### EFFECTS CONTROL FUNCTIONS
class Q_EFFCon
{
public:

	static void TrailLine_PlayerFrame(int Count);

	static void TrailLine_AvatarFrame(int Avatar, int Count);

	static void VaporTrail_ControlFrame(int Count);

	static void BMSentry_ControlFrame(int Count);

	static void Building_ControlFrame(int Count);

	static void ClericPlasma_ServerFrame(int Count);

	static void ClericPlasma_ClientFrame(int Count);

	static void PntSprite_ControlFrame(int Count);

	static void MeleeHit_ControlServer(int Count);

	static void MeleeHit_ControlClient(int Count);

	static void BulletHit_ControlServer(int Count);

	static void BulletHit_ControlClient(int Count);

	static void SEnergy_Renzou_ServerFrame(int Count);

	static void SEnergy_Renzou_ClientFrame(int Count);

	static void SEnergy_PowerBlade_ServerFrame(int Count);

	static void SEnergy_PowerBlade_ClientFrame(int Count);

	static void LEnergy_ServerFrame(int Count);

	static void LEnergy_ClientFrame(int Count);

	static void Explosion_ServerFrame(int Count);

	static void Explosion_ClientFrame(int Count);

	static void Cartridge_ControlFrame(int Count);

	static void Cloud_ControlFrame(int Count);

	static void Spark_SparkFrame(int Count);

	static void PowerFlash_ControlFrame(int Count);

	static void HSpark_ServerFrame(int Count);

	static void HSpark_ClientFrame(int Count);

	static void Spike_ControlFrame(int Count);

	static bool Bullet_ServerFrame(int Count);

	static bool Bullet_ClientFrame(int Count);

	static void Spark_BloodFrame(int Count);

	static void ClericSpell_ClientFrame(int Count);

	static void ClericSpell_ServerFrame(int Count);

	static void WindWake_PlayerFrame(void);

	static void WindWake_AvatarFrame(int Count);

	static void TexTriEffect_PlayerFrame(int Count);

	static void TexTriEffect_AvatarFrame(int Avatar, int Count);

	static void PinEffectMesh_ControlFrame(int Count);

};

static Q_EFFCon Q_EFFCon;

};

#pragma message ("###  Core Internal Function Prototypes  [Q-Prototypes.h]")

#endif