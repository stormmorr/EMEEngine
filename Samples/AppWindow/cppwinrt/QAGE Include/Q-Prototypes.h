/*

	Quantum Angel Game Engine Codex
	-Library -

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

bool QpoLoadLevel(const char *FileName, const char *G3DMainFS, bool AddWorld );

namespace GVARS
{

class Q_COREFunctions
{
public:
	Q_COREFunctions() {};
	~Q_COREFunctions() {};

	void CoreAcquire(bool f_new = false);
	void CoreRelease(void);

	void CoreAllocate(void);
	void CoreDeAllocate(void);

	//HWND CreateMainWindow(HANDLE hInstance, char *AppName, int32 Width, int32 Height);

	//LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	void ShutDown(void);
	void LoadSetupFile(void);

	void ColldetMelee(int bonenum, float attstt, float cutoff, float stroke, int HitType, int BlowHeight, int NumAttackHits);
	void ColldetMeleeAI(int bonenum, float attstt, float cutoff, float stroke, int HitType, int BlowHeight, int NumAttackHits, int AIflag);

	void StructureAInitialize(void);
	int StructureA(const char* String);

	//~~~FROZEN
	//void ColldetBullet(int AIflag, QpoVec3d BulletPos, int BullFLAG);
	//void ColldetBulletAI(int AIflag, QpoVec3d BulletPos, int BullFLAG);
	//FROZEN~~~

	void RadialDamage(int Team, int AvID, float ExpSize, float ExpDMG, QpoVec3d ExpPos, int DirFlag, QpoVec3d Direction);
	void ProgressAttackMeM(int AIcounter);

	void DrawFace(QpoVec3d **Verts);
	void DrawOrientedBoundBox(QpoVec3d *Pos, QpoVec3d *DX, QpoVec3d *DY, QpoVec3d *DZ);
	void DrawInVector(QpoTransform XForm, QpoVec3d Pos);
	void DrawVector(QpoVec3d Pos, QpoVec3d Vector, int Mult);
	float AnglesToPoint(QpoVec3d *s, QpoVec3d *d, QpoVec3d *a);

	void COLDET_CupBlast(QpoTransform Limb, float DamageScale);
	void TrailLineCreate(int AvID, int LengNum, QpoVec3d PosStart, QpoVec3d PosEnd, int BitmapPTR, float Red, float Green, float Blue, int Dir);
	void FlameTrailCreate(int AvID, int LengNum, QpoVec3d PosStart, QpoVec3d PosEnd, int BitmapPTR, float Red, float Green, float Blue, int Dir);

		//Pin Effect Mesh Initialisation Functions
	void PEF_CREATE_PinEffectMesh(QpoVec3d StartPos, float Scale, QpoVec3d VecIn, QpoVec3d VecRight, QpoVec3d VecUp);
	void PEF_CREATE_RingPEFMesh(QpoVec3d StartPos, float Scale, int EffType);
	void PEF_CREATE_SpherePEFMesh(QpoVec3d StartPos, QpoVec3d Center, float Radius, int EffType);

		//PEF Mesh Altering Routines
	void PEF_ADDLINE_RingPEFMesh(QpoVec3d StartPos, float Scale, QpoVec3d VecIn, QpoVec3d VecRight, QpoVec3d VecUp, int MeshID);
	void PEF_ADDLINE_TubePEFMesh(QpoVec3d StartPos, float Scale, QpoVec3d VecIn, QpoVec3d VecRight, QpoVec3d VecUp, int MeshID);

		//Pin Effect Mesh Control Functions
	void PEF_CONTROL_FaceRippleMesh(int MeshID);
	void PEF_CONTROL_RingRippleMesh(int MeshID);
	//void PEF_CONTROL_RingRippleMesh2(int MeshID);
	void PEF_CONTROL_RingShieldSphere(int MeshID);
	void PEF_CONTROL_EnergyWake(int MeshID);

	unsigned int acLoadTexture(int f_Int, std::string f_File);
	unsigned int acLoadTextureAlpha(std::string f_Path, std::string f_Filename, int f_Int);
	void InitTextures(void);
	void CloseTextures(void);

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

	void QAEFFcontrolPLAYER(int QA_EFF_TYPE, float QA_EFF_INTENSITY, int QA_EFF_COL00RED, int QA_EFF_COL00GREEN, int QA_EFF_COL00BLUE, int QA_EFF_COL00ALPHA);
	void QAEFFcontrolAI(int AIcounter, int QA_EFF_TYPE, float QA_EFF_INTENSITY, int QA_EFF_COL00RED, int QA_EFF_COL00GREEN, int QA_EFF_COL00BLUE, int QA_EFF_COL00ALPHA);

	void ActivateItems(void);
	void DeactivateItems(void);
	void ActivateItemsAI(int AIcounter);
	void DeactivateItemsAI(int AIcounter);

	void DigitizeNumber(float Input);

	bool AddDecal(QpoVec3d impact, QpoVec3d normal, float Scale, int DTYPE);
	void AddTrailPNT(int ParentTRAIL, QpoVec3d Pos, QpoColor Color1, QpoColor Color2, QpoVec3d DriftVec, int Type);

		//AI Control Routines
	void AIClericBrain(int AIcount);
	bool AIFighterBrain(int AIcount);
	//void AISoldierBrain(int AIcount);
	void AICore(int AIcount);
	void AICoreMB(int AIcount);
	void AICore_Controller(int f_AVID, float f_Force_Power);
	void Input(void);
	void InputPK(void);

	void AIFighterHeart(int AIcount);
	void AIChemicalCalc(int AIcount);

	void NNbotCONTROL(void);

		//Player Control Routines
	void PLCore(void);
	void PLCore_PushMouse(void);
	void PLCore_PushKey(void);
	void PLCore_PushKey_Controller(float f_Force_Power);
	void PLCore_PushKey_AttackSwitch_P1(void);
	void PLCore_PushKey_AttackSwitch_P1_5(void);
	void PLCore_PushKey_AttackSwitch_P2(void);
	void PLCore_PushKey_AttackSwitch_P3(void);
	void PLCore_PushKey_AttackSwitch_P4(void);
	void PLCoreMB(void);

	void ShowLine(QpoVec3d *Start, QpoVec3d *End, QpoVec3d *CamPos, float width, unsigned int BitmapPtr, float alpha, float red, float green, float blue, int Flags);
	void DrawRectFromVec3ds(QpoVec3d *vec1, QpoVec3d *vec2, QpoVec3d *vec3, QpoVec3d *vec4, unsigned int bmpPtr, float alpha, float red, float green, float blue, int Flags);
	//void UpdateALL(void);

	//void ReadMeMPathways(void);
	//void WriteMeMPathways(void);
	void PlayerSpawnNNbot(QpoVec3d PointOrigin);
	void AISpawnNNbot(int AIcounter, QpoVec3d PointOrigin);

	int Q_LineLineintersect(QpoVec3d p1,QpoVec3d p2,QpoVec3d p3,QpoVec3d p4,QpoVec3d *pa,QpoVec3d *pb/*,double *mua, double *mub*/);

		//### PHYSICS SYSTEM ###
	QpoVec3d PHY_BounceVector(QpoVec3d TraVec, QpoVec3d Normal);

		//### AI Functions ###
	bool AIFunctionsScannerCheck(int AIcounter);

	void CONTROL_PlayerMuzzleFlash(void);
	void CONTROL_AvatarMuzzleFlash(int AIcounter);

	void CONTROL_PlayerPowerFlight(void);
	void CONTROL_AvatarPowerFlight(int SCRAM);

	//bool ShowOptionsDialog(HINSTANCE hInstance);

	void CONTROL_PlayerGraphicsControl(void);
	void CONTROL_PlayerClericShieldControl(void);
	void CONTROL_AvatarClericShieldControl(int SCRAM);
	void CONTROL_Jinks(void);
	void InterfaceSounds(void);
	void InitSounds(void);
	void InitSoundsNum(void);
	std::string acGetSound(int f_Index);
	void acSendSound(int f_Index);
	void CloseSounds(void);
	void World_Event_Engine(void);

	void PlayerJumpEffect(void);
	void AvatarJumpEffect(int AIcounter);
	void PlayerJinkBlast(void);
	void AvatarJinkBlast(int AIcounter);
	void PlayerJinkRushCloud(void);
	void CloudManagement(void);
	void PntSpriteManagement(void);

	void ReadMeMPathways(void);
	void WriteMeMPathways(void);
	void FileGen(void);

};

extern Q_COREFunctions Q;

//##### EFFECTS CONTROL FUNCTIONS
class Q_EFFCon
{
public:
	Q_EFFCon() {};
	~Q_EFFCon() {};

	void TrailLine_PlayerFrame(int Count);

	void TrailLine_AvatarFrame(int Avatar, int Count);

	void VaporTrail_ControlFrame(int Count);

	void BMSentry_ControlFrame(int Count);

	void Building_ControlFrame(int Count);

	void ClericPlasma_ServerFrame(int Count);

	void ClericPlasma_ClientFrame(int Count);

	void PntSprite_ControlFrame(int Count);

	void MeleeHit_ControlServer(int Count);

	void MeleeHit_ControlClient(int Count);

	void BulletHit_ControlServer(int Count);

	void BulletHit_ControlClient(int Count);

	void SEnergy_Renzou_ServerFrame(int Count);

	void SEnergy_Renzou_ClientFrame(int Count);

	void SEnergy_PowerBlade_ServerFrame(int Count);

	void SEnergy_PowerBlade_ClientFrame(int Count);

	void LEnergy_ServerFrame(int Count);

	void LEnergy_ClientFrame(int Count);

	void Explosion_ServerFrame(int Count);

	void Explosion_ClientFrame(int Count);

	void Cartridge_ControlFrame(int Count);

	void Cloud_ControlFrame(int Count);

	void Spark_SparkFrame(int Count);

	void PowerFlash_ControlFrame(int Count);

	void HSpark_ServerFrame(int Count);

	void HSpark_ClientFrame(int Count);

	void Spike_ControlFrame(int Count);

	bool Bullet_ServerFrame(int Count);

	bool Bullet_ClientFrame(int Count);

	void Spark_BloodFrame(int Count);

	void ClericSpell_ClientFrame(int Count);

	void ClericSpell_ServerFrame(int Count);

	void WindWake_PlayerFrame(void);

	void WindWake_AvatarFrame(int Count);

	void TexTriEffect_PlayerFrame(int Count);

	void TexTriEffect_AvatarFrame(int Avatar, int Count);

	void PinEffectMesh_ControlFrame(int Count);

};

extern Q_EFFCon Q_EFFControl;

};

#pragma message ("###  Core Internal Function Prototypes  [Q-Prototypes.h]")

#endif