/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Q-Network-
	- Minor Component -Function Prototypes-

*/

#ifndef QNETPROTOMAP_H
#define QNETPROTOMAP_H

using namespace GVARS;

//--------------------------------------------------------------------
// INCLUDES
//--------------------------------------------------------------------

#include <string>
#include <vector>

#include "../Server/BitTransfer.h"

//--------------------------------------------------------------------
// DECLARATIONS
//--------------------------------------------------------------------

#define QAA_NET_ARRAY_MAX 2500

//--------------------------------------------------------------------
// INTERNAL FUNCTION PROTOTYPES
//--------------------------------------------------------------------

namespace QAGE { class QActiveFramewrk; }

namespace GVARS
{
	//Enhanced Q-Network functionality
class Q_Network
{
public:
	//Q_Network();
	void Initialize(void);

	//###- Tape Buffer -###
	void CreateTapeBuffer(const char *i_Filename);
	void FinalizeTapeBuffer(void);

	void OpenTapeBuffer(const char *i_Filename);
	void CloseTapeBuffer(void);

	//###- Client and Server -###
	void TransmitWorld(float i_Time, int f_ClientVectorID);
	void ServerTransmitWorld(float i_Time);
	void RecieveWorld(float Time, int f_ClientVectorID);
	void ServerRecieveWorld(float Time, unsigned short i_SysIndex);

	bool acStartNetplayer(int f_VecID, int f_AvatarID, int f_CDATAID, int f_BDATAID, int f_TEAM);
	bool acResetNetplayer(int f_VecID, int f_AvatarID, int f_CDATAID, int f_BDATAID, int f_TEAM);

	//###- Recordings -###
	void RecordWorld(float i_Time);
	void PlayWorld(float Time);

	///////// Buffer Printing /////////

	inline void Buffer_FillAngle(QpoVec3d *i_Value)
		{
		fprintf(m_stream, "%f %f %f ", i_Value->x, i_Value->y, i_Value->z);
		}

	inline void Buffer_FillByte(int i_Int)
		{
		fprintf(m_stream, "%i ", i_Int);
		}

	inline void Buffer_FillInteger(int i_Int)
		{
		fprintf(m_stream, "%i ", i_Int);
		}

	inline void Buffer_FillFloat(float i_Value)
		{
		fprintf(m_stream, "%f ", i_Value);
		}

	///////// BitTransfer Printing /////////

	inline void BitTransfer_FillAngle(QpoVec3d *i_Value)
		{
		m_transfer->acPushAlloc(i_Value->x);
		m_transfer->acPushAlloc(i_Value->y);
		m_transfer->acPushAlloc(i_Value->z);
		}

	inline void BitTransfer_FillByte(int i_Int)
		{
		m_transfer->acPushAlloc(i_Int);
		}

	inline void BitTransfer_FillInteger(int i_Int)
		{
		m_transfer->acPushAlloc(i_Int);
		}

	inline void BitTransfer_FillFloat(float i_Value)
		{
		m_transfer->acPushAlloc(i_Value);
		}	

	///////// Buffer Scanning /////////

	void Buffer_GetAngle(QpoVec3d *i_Value)
		{
		fscanf(m_stream, "%f %f %f ", &i_Value->x, &i_Value->y, &i_Value->z);
		}

	void Buffer_GetByte(int *i_Int)
		{
		fscanf(m_stream, "%i ", i_Int);
		}

	void Buffer_GetInteger(int *i_Int)
		{
		fscanf(m_stream, "%i ", i_Int);
		}

	void Buffer_GetFloat(float *i_Value)
		{
		fscanf(m_stream, "%f ", i_Value);
		}

	void Buffer_GetByteDiscard(void)
		{
		int* i_Int = new int();
		fscanf(m_stream, "%i ", i_Int);
		delete i_Int;
		}

	///////// BitTransfer Scanning /////////

	void BitTransfer_GetAngle(QpoVec3d *i_Value)
		{
		m_transfer->acRead(i_Value->x);
		m_transfer->acRead(i_Value->y);
		m_transfer->acRead(i_Value->z);
		}

	void BitTransfer_GetByte(int *i_Int)
		{
		m_transfer->acRead(i_Int);
		}

	void BitTransfer_GetInteger(int *i_Int)
		{
		m_transfer->acRead(i_Int);
		}

	void BitTransfer_GetFloat(float *i_Value)
		{
		m_transfer->acRead(i_Value);
		}

	void BitTransfer_GetAngle(QpoVec3d i_Value)
		{
		m_transfer->acRead(i_Value.x);
		m_transfer->acRead(i_Value.y);
		m_transfer->acRead(i_Value.z);
		}

	void BitTransfer_GetByte(int i_Int)
		{
		m_transfer->acRead(i_Int);
		}

	void BitTransfer_GetInteger(int i_Int)
		{
		m_transfer->acRead(i_Int);
		}

	void BitTransfer_GetFloat(float i_Value)
		{
		m_transfer->acRead(i_Value);
		}

	void BitTransfer_GetAngleDiscard(void)
		{
		QpoVec3d i_Value;
		m_transfer->acRead(i_Value.x);
		m_transfer->acRead(i_Value.y);
		m_transfer->acRead(i_Value.z);
		}

	void BitTransfer_GetFloatDiscard(void)
		{
		float i_Value;
		m_transfer->acRead(i_Value);
		}

	void BitTransfer_GetByteDiscard(void)
		{
		int i_Value;
		m_transfer->acRead(i_Value);
		}
	
	FILE				*m_stream;
	BitTransfer			*m_transfer;
	bool				m_Recording;
	bool				m_Playing;

	int					Int_Aposestate;
	int					Int_Mflash;
	int					Int_SpecLvlRESET;
	float				Float_PowerFactor;
	float				Float_Health;
	QpoVec3d			m_ValueQPO;
	int					m_ValueINT;
	float				m_ValueFLT;

	std::string			m_CurrTape;
	bool				m_TapeLoaded;

	int ses_Counter;
	int m_Recieve;

	std::vector<int>	ses_Q_Bullet_Live;
	std::vector<int>	ses_Q_Bullet_Live_STR;

	std::vector<int>	ses_Q_BulletHit_Live;
	std::vector<int>	ses_Q_BulletHit_Live_STR;

	std::vector<int>	ses_Q_MeleeHit_Live;
	std::vector<int>	ses_Q_MeleeHit_Live_STR;

	std::vector<int>	ses_Q_SEnergy_Live;
	std::vector<int>	ses_Q_SEnergy_Live_STR;

	std::vector<int>	ses_Q_LEnergy_Live;
	std::vector<int>	ses_Q_LEnergy_Live_STR;

	std::vector<int>	ses_Q_Explosion_Live;
	std::vector<int>	ses_Q_Explosion_Live_STR;

	QAGE::QActiveFramewrk* m_QActiveFramework;

	std::vector<int> m_vec_HitReactionGB;
	std::vector<int> m_vec_ServerHitReactionGB;

	int			m_HighVectorID;
	int			m_HitReactionGB;

	int			mf_pnt;
	int			mf_pntSTR;
	int			mf_DestID;
	int			mf_scan;

	int			m_NETNomWorldAvatars;

	int			m_NomBulletSTR;

	int			m_NomAI;
	int			m_Own;
	int			m_Live;
	int			m_AVID;
	float		m_Energy;
	float		m_EnergyGAIN;
	float		m_Armour;
	float		m_ArmourGAIN;
	float		m_Health;
	float		m_HealthGAIN;
	float		m_PowerBank;
	float		m_PowerBankGAIN;

	int			m_VectorSelfID;
	bool		m_Start;
	bool		m_StartData;

	int			wb_helly;
	int			wb_aero;
	int			wb_jet;

	int			m_NomHitGB;
};

extern Q_Network QNetwork;

};

#pragma message ("###  Q-Network  [Q-NET-ProtoMap.h]")

#endif