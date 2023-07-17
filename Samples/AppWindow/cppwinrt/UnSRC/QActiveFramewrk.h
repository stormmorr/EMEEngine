/*

	Quantum Angel Game Engine Codex
	-Active Framework -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- ACTIVE / MAIN ENTRY FILE-

*/

#ifndef __QACTIVEFRAMEWORK__
#ifndef __QSERVERFRAMEWORK__
#define __QACTIVEFRAMEWORK__

#pragma message ("###--(Q)ACTIVE FRAMEWORK--###")

#include "../Server/PacketSocketInterface.h"
#include "../Server/PacketPumpInterface.h"
#include "../Server/PacketStackInterface.h"

#include "Avatar/unMesh.h"
#include "Avatar/unMeshStatic.h"
#include "Utility/Mutex.h"

#ifdef OSIRUS_CORE
#include "Osirus/OsirusCore.h"
#endif

#include "Avatar/unPointLocator.h"

#include "Base/UNbase.h"

#include "Render/unVis.h"

#include "Texture/untexturebank.h"

#include <vector>

#pragma message ("-~~THE QUANTUM ANGEL CODEX~~-")

#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

#include "Q-Includes.h"

#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-CORE-Avatar.h"
#include "Q-Prototypes.h"
#include "Q-GlobalHeader.h"
#include "Q-WE-PntSprite.h"
#include "Q-WE-MeleeHits.h"
#include "Q-WE-BulletSystem.h"
#include "Q-WE-EnergyMatrix.h"
#include "Q-WE-CloudControl.h"
#include "Q-ENE-EnergyTypes.h"
#include "Q-OBJ-ObjectTypes.h"
#include "Q-AI-NNbot.h"

#include "Q-NET-ProtoMap.h"

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#if 0
#define USE_CAPSULES 1
#endif

#define TIMESCALE_DEFAULT 0.18f
#define ATTLOCKON_MAX 70.0f

extern int Q_EntryMain(void);

namespace QAGE
{

class QSpawnPoint
{
public:
	QSpawnPoint(int f_Team);
	~QSpawnPoint() {};

	QpoVec3d m_CellCenter;
	QpoVec3d m_RotationVec;
	QpoVec3d m_StRotationVec;

	int m_Count;
	int m_CountSPD;
	int m_CountLimit;
	int m_SpawnLimit;
	int m_Team;

	std::vector<int> m_ForgeAVID;
	int m_AVTEAM[500];

	float m_TeamColorsRED[38];
	float m_TeamColorsGREEN[38];
	float m_TeamColorsBLUE[38];
};

class QSpawnPntController
{
public:
	QSpawnPntController() { m_SpawnON = false; };
	~QSpawnPntController() {};

	bool m_SpawnON;

	std::vector<QSpawnPoint*> m_SpawnPoint;

	void acSpawnFrame(void);
};

class QActiveFramewrk
{
public:
	QActiveFramewrk();
	virtual ~QActiveFramewrk();

	////// QAGE Active FrameWork Functions //////
	void acBanner(void);
	bool acAmpMesh(void);
	bool acAmpInit(void);
	bool acStartInit(void);
	bool acActiveInit(void);
	void acRecieveInit(void);
	void acDataInit(void);
	void acQAInit(void);

	void acRenderFrame(void);
	void acQFrame(void);
	void acWorldFrame(void);
	void acNetFrame(void);

	void acShutdown(void);

	/// singleton instance access
	static QActiveFramewrk* instance();

	/// MeshFactories ///
	std::vector<unMesh*> meshBank;
	std::vector<unShellMesh*> meshShellTemplates;
	std::vector<unMeshStatic*> meshstaticTemplates;
	std::vector<unMeshStatic*> meshVehicleTemplates;

#if 0
	std::vector<unDataMesh*> meshTemplates;
	std::vector<digiDataMesh*> bodymeshTemplates;
	std::vector<digiShellMesh*> meshdigiShellTemplates;
#endif

	int m_NomDataMesh;
	int m_NomDataBodyMesh;

	unMeshStaticBank *m_meshbank;

	unTextureBank *m_texturebank;

	QSpawnPntController *m_QSpawnPntController;

	bool acSpawnAvatar(int f_Index, int f_CharID, int f_BDataID, int f_Team, QpoVec3d f_Position, int f_BoneStructure, int f_SpawnPnt, bool level = true);
	void acRespawnAvatar(int f_Index);
	void acRespawnPlayer(void);

	void acGenerateDataMesh(const char *f_Filename);
	void acGenerateDataBodyMesh(const char *f_Filename);
	void acNamePlateUpdate(void);

	/// Game Inits
	bool m_buildActive;

#ifdef OSIRUS_CORE
	OSI::OsirusCore *f_OsirusCore;
#endif

private:
	double m_lastTime;
	int m_PP_STATE, m_OPP_STATE;

public:
	//*void acPushGuiEvent(GUI::unTreeLink DXID, int EventType, GUI::SubscriberSlot MemberFunction)
	//*	{ m_GUI->vecpane[DXID.KX[0]]->vecbutton[DXID.KX[1]]->m_response->EventID = GuiEvents.size();
	//*	  GuiEvents.push_back(MemberFunction); }

	//*bool acToolPlace(PxVec3 startpos, PxVec3 destpos, int toolIndex, int toolShape);
	//*void acSphereStack(PxVec3 origin, float scale, int toolIndex);
	//*void acSphereSmooth(PxVec3 origin, float scale, int toolIndex);

	/// Construction vars ///
	unPointLocator *trrcursor;
	QpoLightInfo m_BuildLight;

	bool gPickStay;
	float gMouseDepth;

	float mMaxDist;
	int TestKEY1DOWN;
	int TestKEY2DOWN;

	std::vector<int> veccellbuffer;
	int m_cellspan;
	int m_cellspanx;
	int m_cellspany;

	int m_trrCursorType;
	float m_trrCursorAlpha;
	bool m_trrCursorActive;
	bool m_trrLimbCType;

	int m_trrUpdateScale;
	int m_trrUpdate;

	int m_trrToolCutter;
	int m_trrToolLevel;
	int m_trrToolRaise;
	int m_trrToolSmooth;
	int m_trrToolIndex;

	float m_trrToolScale;

	bool m_mouseleft;
	bool m_mouseright;
	bool m_mousemid;
	bool m_mouseleft_limb;
	bool m_mouseright_limb;
	bool m_mousemid_limb;

	unDocumentBank *m_DocumentBank;
	std::map<const char*, unsigned int> m_map_Documents;

	bool m_NetStart;

private:
	static QActiveFramewrk* s_instance;
};

extern bool g_PlayerForgeBoxxed;

};

#endif
#endif