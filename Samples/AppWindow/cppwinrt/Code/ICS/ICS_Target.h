/*

Target.h - Class Target osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef ICS_TARGET_H
#define ICS_TARGET_H

#include <vector>
#include <math.h>
#include <chrono>

#include "Include/Cube.h"

#include "ICS_Collection.h"

#include "Code/Cube/qcom.h"

#include "ICS_Types.h"

using namespace Cube;
using namespace std;

   /////////////////
  // ICS Defines //
 /////////////////

#define ICS_MAINHEIGHTSTART 15.0f
#define ICS_MAINSCALE 40.0f
#define ICS_MAINHEIGHTFINISH ICS_MAINSCALE + ICS_MAINHEIGHTSTART
#define ICS_MAINDIV 10

#define ICS_NANO_AMOUNT 0.0001f

#define ICS_INITIAL_SEED_MULL 332.13268
#define ICS_REPEATER_MULL 34128.1893

#define ICS_SIZE_LOWER_BOUND 0.5f
#define ICS_SIZE_UPPER_BOUND 1.75f
#define ICS_MOVE_BOUND 3.0f

#define ICS_ADVANCE 0.045f
#define ICS_MAGNITUDE 500.0f
#define ICS_MAGNITUDE_DOUBLE 50000.0f
#define ICS_MIDPOINT 13.5f
#define ICS_START 28.0f
#define ICS_COMPLETE 28.0f
#define ICS_FRAME_MIN ICS_START
#define ICS_FRAME_MAX ICS_FRAME_MIN + ICS_COMPLETE
#define ICS_FRAME ICS_FRAME_MAX - ICS_FRAME_MIN

#define ICS_TIMECHECKPOINT_SECONDS 5000

#define ICS_DEFAULT_QUADRANT_SIZE 150.0f
#define ICS_DEFAULT_TUN_DIV_FLOAT (((ICS_DEFAULT_QUADRANT_SIZE - ICS_MAINSCALE) / ICS_MAINSCALE) + 1.0f)
#define ICS_DEFAULT_TUN_SCALE_DIV (int)(ICS_DEFAULT_TUN_DIV_FLOAT * ((float)ICS_MAINDIV + 1.0f))
#define ICS_DEFAULT_DEPTH_SCALE_DIV (ICS_MAINDIV + 1)

#define ICS_SPHERE_DEFAULT 1.6f

#if 0
#define ICS_LARGE_SIZE 1
#endif

#if 0
#define ICS_EFFICIENCY_DRIVE 1
#endif

#if 0
#define ICS_LONG_POINT_TIME 1
#endif

namespace ecoin
{
	extern Cube::BiVector g_ICS_SchemaRef[15];

	extern void ag_ICS_EcoinSecure_Break_Assert(int f_A, int f_B);

	template<class _Ty>
	std::shared_ptr<_Ty> ag_ICS_reference_NameObject(std::string f_Name);

	extern int g_CountLM;

	class ICS_CountControl
	{
	public:
		ICS_CountControl() = default;

		ICS_CountControl(float f_Upper, float f_Lower, int f_TimeCheckPoint, float f_QuadrantScale, int f_MixFactor)
			{
			m_UpperBounds = f_Upper;
			m_LowerBounds = f_Lower;
			m_BoundsScale = m_UpperBounds - m_LowerBounds;
			m_QuadrantScale = f_QuadrantScale;
			m_TimeCheckPoint = f_TimeCheckPoint;

			acSeed(((m_TimeCheckPoint + 1) + (f_MixFactor)) * ICS_INITIAL_SEED_MULL);
			}

		void acSeed(float co)
			{
			m_Seed = co;
			}

		float acRepeater(void)
			{
			float f_result = frac(sin(m_Seed * ICS_REPEATER_MULL));

			acSeed(f_result);

			return f_result;
			}

		float acCount(float f_Scale)
			{
			return acRepeater() * f_Scale;
			}

		float acBoundsCount(void)
			{
			return (acRepeater() * m_BoundsScale) + m_LowerBounds;
			}

		float m_Seed;
		float m_Start_Quadrant;
		float m_Tun_Quadrant;
		float m_QuadrantScale;
		float m_UpperBounds;
		float m_LowerBounds;
		float m_BoundsScale;
		int m_TimeCheckPoint;
	};

	extern std::shared_ptr<ICS_CountControl> g_CountController;

	class ICS_Sphere
	{
	public:
		ICS_Sphere() = default;

		ICS_Sphere(std::shared_ptr<BiVector> f_Pos, float f_Radius)
			{
			m_Center = std::make_shared<BiVector>(f_Pos->m_X, f_Pos->m_Y, f_Pos->m_Z);
			m_Motion = std::make_shared<BiVector>(g_CountController->acCount(2.0f) - 1.0f, g_CountController->acCount(2.0f) - 1.0f, g_CountController->acCount(2.0f) - 1.0f);
			m_Radius = f_Radius;
			}

		void acSize(void)
			{
			m_Radius *= g_CountController->acBoundsCount();
			}

		void acMove(void)
			{
			m_Center->acSet(m_Center->m_X + (g_CountController->acCount(ICS_MOVE_BOUND) - (ICS_MOVE_BOUND / 2.0f)), m_Center->m_Y + (g_CountController->acCount(ICS_MOVE_BOUND) - (ICS_MOVE_BOUND / 2.0f)), m_Center->m_Z + (g_CountController->acCount(ICS_MOVE_BOUND) - (ICS_MOVE_BOUND / 2.0f)));

			acBox();
			}

		void acBox(void)
			{
			if(m_Center->m_X < 0.0f)
				{
				m_Center->m_X += (ICS_MOVE_BOUND / 2.0f);
				}

			if(m_Center->m_X > g_CountController->m_QuadrantScale)
				{
				m_Center->m_X -= (ICS_MOVE_BOUND / 2.0f);
				}

			if(m_Center->m_Y < ICS_MAINHEIGHTSTART)
				{
				m_Center->m_Y += (ICS_MOVE_BOUND / 2.0f);
				}

			if(m_Center->m_Y > ICS_MAINSCALE)
				{
				m_Center->m_Y -= (ICS_MOVE_BOUND / 2.0f);
				}

			if(m_Center->m_Z < 0.0f)
				{
				m_Center->m_Z += (ICS_MOVE_BOUND / 2.0f);
				}

			if(m_Center->m_Z > ICS_MAINSCALE)
				{
				m_Center->m_Z -= (ICS_MOVE_BOUND / 2.0f);
				}
			}

		void acTravel(long long f_HighPrecisionTime)
			{
			m_Center->acSet(m_Center->m_X + (m_Motion->m_X * (f_HighPrecisionTime * ICS_NANO_AMOUNT)), m_Center->m_Y + (m_Motion->m_Y * (f_HighPrecisionTime * ICS_NANO_AMOUNT)), m_Center->m_Z + (m_Motion->m_Z * (f_HighPrecisionTime * ICS_NANO_AMOUNT)));

			bool f_Scan = true;
			while(f_Scan == true)
				{
				//Preset falsify
				f_Scan = false;

				if(m_Center->m_X < 0.0f)
					{
					m_Center->m_X += g_CountController->m_QuadrantScale;

					f_Scan = true;
					}

				if(m_Center->m_X > g_CountController->m_Tun_Quadrant)
					{
					m_Center->m_X -= g_CountController->m_QuadrantScale;

					f_Scan = true;
					}

				if(m_Center->m_Y < ICS_MAINHEIGHTSTART)
					{
					m_Center->m_Y += (ICS_MAINSCALE - ICS_MAINHEIGHTSTART);

					f_Scan = true;
					}

				if(m_Center->m_Y > ICS_MAINSCALE)
					{
					m_Center->m_Y -= (ICS_MAINSCALE - ICS_MAINHEIGHTSTART);

					f_Scan = true;
					}

				if(m_Center->m_Z < 0.0f)
					{
					m_Center->m_Z += ICS_MAINSCALE;

					f_Scan = true;
					}

				if(m_Center->m_Z > ICS_MAINSCALE)
					{
					m_Center->m_Z -= ICS_MAINSCALE;

					f_Scan = true;
					}
				}
			}

		std::shared_ptr<BiVector> m_Center;
		std::shared_ptr<BiVector> m_Motion;

		float m_Radius;
	};

	class ICS_LibraryID
	{
	public:
		//Default Constructor
		ICS_LibraryID()
			{
			m_TimeCheckPoint = 0;
			m_HighPrecisionTime = 0;

			m_Resultant = std::ag_Make_Smart_Pointer<ICS_Resultant>();
			}

		//Hesh Constructor
		ICS_LibraryID(std::shared_ptr<Cube::CubeHESH> f_Hesh);

		std::shared_ptr<Cube::CubeHESH> acSaveHesh(void);

		//Time Position Preparation
		int m_TimeCheckPoint;
		long long m_HighPrecisionTime;

		int m_MainstreamID;

		//Final Position
		std::Smart_Ptr<ICS_Resultant> m_Resultant;
	};

	class ICS_Mainstream
	{
	public:
		ICS_Mainstream();
		ICS_Mainstream(float f_QuadrantScale);
		ICS_Mainstream(int f_TimeCheckPoint, float f_QuadrantScale, bool f_Compress = true);
		ICS_Mainstream(int f_TimeCheckPoint, float f_QuadrantScale, float f_DepthScale, float f_TunScale, std::Smart_Ptr<ICS_CheckPointPassword> f_CP_Password);
		
		void acPrepare(int f_TimeCheckPoint, float f_QuadrantScale, bool f_Compress = true, int f_DepthScaleDivision = ICS_DEFAULT_DEPTH_SCALE_DIV, int f_TunScaleDivision = ICS_DEFAULT_TUN_SCALE_DIV);
		void acPlay_Until(long long f_HighPrecisionTime);

		float acProvideConnection(void);
		double acProvideConnectionDouble(void);

		void acStartSpheres(void);
		void acPositionLocation(std::Smart_Ptr<ICS_LibraryID> f_LibraryID);
		void acStartStream(std::Smart_Ptr<ICS_LibraryID> f_LibraryID);

		void acSaveCloud(void);

		std::string acHash(void);

		int m_DepthScaleDivision;
		int m_TunScaleDivision;

		float m_QuadrantScale;

		int m_TimeCheckPoint;
		int m_MaxCheckPoint;
		int m_SphereIndex;
		int m_MainstreamID;

		long long m_StartTime;

		std::string m_owner;

		std::shared_ptr<BiVector> m_Pos;
		std::shared_ptr<BiVector> m_WritePosition;
		std::shared_ptr<BiVector> m_StartNearGround;
		std::shared_ptr<BiVector> m_StartFarGround;

		std::vector<std::shared_ptr<ICS_Sphere>> m_vec_Sphere;

		std::Smart_Ptr<ICS_CheckPointPassword> m_CP_Password;
	};

	//Generate New Mainstream
	extern std::Smart_Ptr<ICS_Mainstream> ag_MainstreamNew(void);

	//Request Compression Mainstream
	extern std::Smart_Ptr<ICS_Mainstream> ag_RequestMainstream(int f_TimeCheckPoint, int f_MainstreamID);

	extern void Compressor(std::shared_ptr<Qcom> f_com);

}; //end ecoin::classTarget namespace

#endif