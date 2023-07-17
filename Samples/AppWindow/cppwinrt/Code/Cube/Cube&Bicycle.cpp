/*

Cube&Bicycle - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "DirectXMath.h"

#include <math.h>

#include "Include/Cube.h"

#include "../Code/Work/Contract.h"
#include "../Code/Work/Schedular.h"

#include <vector>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>

#include "Wallet/Wallet.h"

#include "base58.h"

using namespace Cube;
using namespace ecoin;

DirectX::XMVECTOR g_Origin;
std::shared_ptr<BiMeshContainer> g_MeshContainer;

int g_ID = 0;

char* g_addrfield[60];
char* g_heshfield[60];
char* g_cubefield[60];
char* g_adifield[60];
char* g_sharefield[60];
char* g_blockfield[60];
char* g_jobfield[60];
char* g_jobvarfield[60];
char* g_transfield[60];
char* g_eventfield[60];
char* g_reffield[60];
char* g_chancefield[60];
char* g_txinsyncfield[60];
char* g_txoutsyncfield[60];
char* g_syncfield[60];

int g_HeshFieldCount;
int g_CubeFieldCount = 55;
int g_BlockFieldCount;
int g_TransFieldCount;

ULONGLONG g_TimeStamp;

std::random_device g_engine;

std::shared_ptr<CubeHESH> g_HESH_caddy;
bool g_GenerateCaddy = true;

double g_AverageSaleValue = 0;
double g_EcoinDifficulty = 0;

int g_JobID = 0;
int g_BlockType = -1;

std::shared_ptr<CubeHESH> g_TargetedHesh;

int g_TabSelected = 0;
int g_codeON = 0;
std::string g_codeCMD;
int g_codemode = 0;
int g_curr_SelectionEnd = 0;
int g_curr_SelectionStart = 0;

winrt::hstring g_curr_Selection;

std::string g_Tab[9];

namespace Cube
{
	 /////////////////
	// Cube Global //
	std::shared_ptr<_Cag> Cag;

	std::vector<std::shared_ptr<Cube::CubeTransaction>> g_vec_Successfull_TX;
	std::shared_ptr<CubeHESH> g_TargetedHesh;

	Cube::float3 g_RandomSeed;
	int g_Fingat = CUBE_TRI_SHOT_A;
	float g_Float = 0.1f;
	float g_swit = 0.75f;

	matrix g_model;
	matrix g_view;
	matrix g_projection;

	BiVector g_eye;
	BiVector g_at;

	std::shared_ptr<Cube::CubeHeshExporter> g_CubeHeshExport;
	std::vector<std::shared_ptr<BicycleContainer>> g_BicycleContainer;
	Cube::float3 g_offsetVec;

	bool m_TapeStatus = false;

	void seedrand(int f_Seed)
		{
		srand(f_Seed);
		}

	int randTape(void)
		{
		return (int)rand();
		}

	float randomTape(void)
		{
		return (float)rand() / 32767;
		}

	void TapeOn(void)
		{
		m_TapeStatus = true;
		}
	
	void TapeOff(void)
		{
		m_TapeStatus = false;
		}

	int randomFac(void)
		{
		float f_Rand_Max = RAND_MAX;
		float f_Result = (float)Cube::random() * (float)f_Rand_Max;
		int f_Int = f_Result;
		return f_Int;
		}

	float random(void)
		{
		unsigned int f_x = g_engine();

		float f_xy = (float)((float)f_x / (float)UINT_MAX);

		return f_xy;
		}

	float ag_RVC(void)
		{
		float f_qr = random() - 0.5f;

		if(f_qr >= 0)
			{
			f_qr += 0.2;
			}
		else
			{
			f_qr -= 0.2;
			}

		f_qr *= 8.0f;

		return f_qr;
		}

	std::shared_ptr<Cube::CubeKEY> ChooseKEY(int f_Count)
		{
		int f_Index = Cube::randomFac() % g_BicycleContainer[0]->vec_Key.size();

		std::shared_ptr<Cube::CubeKEY> f_KEY = g_BicycleContainer[0]->vec_Key[f_Index];

		return f_KEY;
		}

	void BicycleContainer::ac_IsOK(void)
		{
		int f_StorePos = 0;
		for(int f_Jet = 0; f_Jet < g_BicycleContainer[0]->vec_Key.size(); f_Jet++)
			{
			std::shared_ptr<Cube::CubeKEY> f_Key = g_BicycleContainer[0]->vec_Key[f_Jet];

			bool f_GradePass = true;

			if(f_Key->m_Link->vec_Vertex.size() != 8)
				{
				f_GradePass = false;
				}

			if(f_Key->m_Link->vec_Color.size() != 8)
				{
				f_GradePass = false;
				}

			if(!f_GradePass)
				{
				for(int f_Veh = f_Jet; f_Veh < g_BicycleContainer[0]->vec_Key.size() - 1; f_Veh++)
					{
					g_BicycleContainer[0]->vec_Key[f_Veh] = g_BicycleContainer[0]->vec_Key[f_Veh + 1];
					}

				g_BicycleContainer[0]->vec_Key.pop_back();
				}
			}
		}

	  /////////////////////////
	 /// START Cube Miner  ///
	/////////////////////////

	float frac(float f_Float)
		{
		float f_Result = 0.0f;

		f_Result = f_Float - truncf(f_Float);

		return f_Result;
		}

	float dot(Cube::float3 f_A, Cube::float3 f_B)
		{
		float f_Result;
		f_Result = (f_A.x * f_B.x) + (f_A.y * f_B.y) + (f_A.z * f_B.z);
		return f_Result;
		}
	
	PixelShaderInput visualminer(VertexShaderInput input)
		{
		PixelShaderInput output;

#if 0
		Cube::float3 f_Rand = Cube::float3(CUBE_RAND3);

		//float f_A = random() * 3.142 * ((atan2(random(), 1 - (random() + random()) * ((max(random(), random()) * random() * random()) * 3.142) + ((atan2(random(), random() + 3.142)))) * random()));

		float f_A = Cube::frac(sin(Cube::dot((Cube::float3)f_Rand, Cube::float3(12.9898, 78.233, 45.5432))) * 43758.5453);
		f_Rand = Cube::float3(CUBE_RAND3);

		float f_B = Cube::frac(sin(Cube::dot((Cube::float3)f_Rand, Cube::float3(12.9898, 78.233, 45.5432))) * 43758.5453);
		f_Rand = Cube::float3(CUBE_RAND3);

		float f_C = Cube::frac(sin(Cube::dot((Cube::float3)f_Rand, Cube::float3(12.9898, 78.233, 45.5432))) * 43758.5453);
		f_Rand = Cube::float3(CUBE_RAND3);

		Cube::float4 pos = Cube::float4(input.pos.x, input.pos.y, input.pos.z, 1.0f);

		// Transform the vertex position into projected space.
		//pos = g_model * pos;
		//pos = g_view * pos;
		//pos = g_projection * pos;

		f_Rand = Cube::float3(CUBE_RAND3);
		float f_A2 = Cube::frac(sin(Cube::dot(f_Rand, Cube::float3(12.9898, 78.233, 45.5432))) * 43758.5453);
		f_Rand = Cube::float3(CUBE_RAND3);
		float f_B2 = Cube::frac(sin(Cube::dot(f_Rand, Cube::float3(12.9898, 78.233, 45.5432))) * 43758.5453);
		f_Rand = Cube::float3(CUBE_RAND3);
		float f_C2 = Cube::frac(sin(Cube::dot(f_Rand, Cube::float3(12.9898, 78.233, 45.5432))) * 43758.5453);

		// Pass the color through without modification.
		output.color = Cube::float3(input.color.r * sin(f_B * f_C) * 5, input.color.g * sin(f_C * f_A) * 5, input.color.b * sin(f_B * f_B) * 5);

		//output.pos = Cube::float4(pos.x * f_C2 * 0.5, pos.y * f_B2 * 0.5, pos.z * f_A2 * 0.5, pos.w);

		output.pos = Cube::float4(pos.x + g_offsetVec.x, pos.y + g_offsetVec.y, pos.z + g_offsetVec.z, pos.w);
#else

		output.pos.x = input.pos.x;
		output.pos.y = input.pos.y;
		output.pos.z = input.pos.z;

#endif

#if 0
		output.color.r = input.color.r;
		output.color.g = input.color.g;
		output.color.b = input.color.b;

		if(g_Contract)
			{
			output = g_Contract->getWork(input);
			}
#endif

		return output;
		}

	Carriage agRun_visualminer(float f_X, float f_Y, float f_Z)
		{
		Carriage f_Result;
		PixelShaderInput f_OUT;
		VertexShaderInput f_IN;

		f_IN.pos.x = f_X;
		f_IN.pos.y = f_Y;
		f_IN.pos.z = f_Z;

#if 0
		f_IN.color.r = 0.0f;
		f_IN.color.g = 0.0f;
		f_IN.color.b = 0.0f;
#endif

		f_OUT = Cube::visualminer(f_IN);

		f_Result.m_X = f_OUT.pos.x;
		f_Result.m_Y = f_OUT.pos.y;
		f_Result.m_Z = f_OUT.pos.z;

		return f_Result;
		}

	void agSet_offsetvec(Cube::float3 f_Vector)
		{
		g_offsetVec = f_Vector;
		}

	void CubeKEY::acPush(int f_Type)
		{
		switch(f_Type)
			{
			case CUBE_LOG_PUSHBACK:
				{
				int f_Children = nom_Child;
				while (f_Children > 0)
					{
					m_Link->avPushBack(-1);
					vec_Log.push_back(CUBE_LOG_PUSHBACK);

#ifdef CUBE_LAYER
					vec_Child[f_Children]->acPush(CUBE_LOG_PUSHBACK);
#endif

					f_Children--;
					}
				}break;

			case CUBE_LOG_PULLFORD:
				{
				int f_Children = nom_Child;
				while (f_Children > 0)
					{
					m_Link->avPushBack(1);
					vec_Log.push_back(CUBE_LOG_PULLFORD);

#ifdef CUBE_LAYER
					vec_Child[f_Children]->acPush(CUBE_LOG_PULLFORD);
#endif

					f_Children--;
					}
				}break;

			case CUBE_LOG_GROW:
				{
				int f_Children = nom_Child;
				while (f_Children > 0)
					{
					m_Link->avGrow((Cube::random() + 1) * 5.0);
					vec_Log.push_back(CUBE_LOG_GROW);

#ifdef CUBE_LAYER
					vec_Child[f_Children]->acPush(CUBE_LOG_GROW);
#endif

					f_Children--;
					}
				}break;

			case CUBE_LOG_SHRINK:
				{
				int f_Children = nom_Child;
				while (f_Children > 0)
					{
					m_Link->avGrow(Cube::random());
					vec_Log.push_back(CUBE_LOG_SHRINK);

#ifdef CUBE_LAYER
					vec_Child[f_Children]->acPush(CUBE_LOG_SHRINK);
#endif

					f_Children--;
					}
				}break;
			}
		}

	void BicycleContainer::avStage(void)
		{
		unsigned int f_Puck = 0;
		while(f_Puck < CUBE_PUCK_BASE)
			{ /////////
			 /////////
			// Rand
			int f_RandBase = (Cube::randomFac() % 50);

			int f_RandAlpha = (Cube::randomFac() % vec_Key.size());
			int f_RandBeta = (Cube::randomFac() % vec_Key.size());
			int f_RandGamma = (Cube::randomFac() % vec_Key.size());
			int f_RandDelta = (Cube::randomFac() % vec_Key.size());

			if(f_RandBase >= 30)
				{
				vec_Key[f_RandAlpha]->acPush(CUBE_LOG_PUSHBACK);
				vec_Key[f_RandBeta]->acPush(CUBE_LOG_PULLFORD);
				vec_Key[f_RandGamma]->acPush(CUBE_LOG_GROW);
				vec_Key[f_RandDelta]->acPush(CUBE_LOG_SHRINK);
				}
			else
				{
				if(f_RandBase >= 0)
					{
					ag_AttachCube(vec_Key[f_RandAlpha], vec_Key[f_RandBeta], 0.2);
					ag_AttachCube(vec_Key[f_RandGamma], vec_Key[f_RandDelta], 0.2);
					ag_AttachCube(vec_Key[f_RandGamma], vec_Key[f_RandBeta], 0.2);
					}
				}

			if(f_RandBase >= 45)
				{
				f_Puck++;
				}
			}
		}

	void CubeBicycle::avGrow(float f_Amount)
		{
		for(int f_Count = 0; f_Count < vec_Vertex.size(); f_Count++)
			{
			vec_Vertex[f_Count]->m_X *= f_Amount;
			vec_Vertex[f_Count]->m_Y *= f_Amount;
			vec_Vertex[f_Count]->m_Z *= f_Amount;
			}
		}
		
	void CubeBicycle::avTranslate(Cube::BiVector f_Vector)
		{
		for(int f_Count = 0; f_Count < vec_Vertex.size(); f_Count++)
			{
			vec_Vertex[f_Count]->m_X += f_Vector.m_X;
			vec_Vertex[f_Count]->m_Y += f_Vector.m_Y;
			vec_Vertex[f_Count]->m_Z += f_Vector.m_Z;
			}
		}

	void CubeBicycle::avPushBack(int f_Step)
		{
		if(f_Step >= 0)
			{
			for(int f_Count = 0; f_Count < vec_Vertex.size(); f_Count++)
				{
				vec_Vertex[f_Count]->m_X += g_at.m_X - g_eye.m_X;
				vec_Vertex[f_Count]->m_Y += g_at.m_Y - g_eye.m_Y;
				vec_Vertex[f_Count]->m_Z += g_at.m_Z - g_eye.m_Z;
				}
			}
		else
			{
			for(int f_Count = 0; f_Count < vec_Vertex.size(); f_Count++)
				{
				vec_Vertex[f_Count]->m_X -= g_at.m_X - g_eye.m_X;
				vec_Vertex[f_Count]->m_Y -= g_at.m_Y - g_eye.m_Y;
				vec_Vertex[f_Count]->m_Z -= g_at.m_Z - g_eye.m_Z;
				}
			}
		}

	CubeKEY::CubeKEY(void)
		{
		std::string f_ref_CurrentPath = "CubeKEY::CubeKEY";

		m_aabb = std::make_shared<aabb>();

		m_Link = nullptr;
		m_Served = false;
		vec_Log.clear();
		vec_Child.clear();
		vec_Parent.clear();
		nom_Child = 0;
		nom_Parent = 0;

#ifndef OSI_MEM_APP
		ac_Push(nom_Child, f_ref_CurrentPath + g_ref_Div + "nom_Child");
		ac_Push(nom_Parent, f_ref_CurrentPath + g_ref_Div + "nom_Parent");
		ac_Push(vec_Log, f_ref_CurrentPath + g_ref_Div + "vec_Log");
		ac_Push(m_Served, f_ref_CurrentPath + g_ref_Div + "m_Served");
#endif
		}

	void BiMesh::acMark(int f_Type)
		{
		m_InteractionType = f_Type;
		}

	void BiSphere::acPushRadius(float f_Length)
		{
		if(f_Length > m_Dist)
			{
			m_Dist = f_Length;
			}
		}

	void BiMeshContainer::acClearInteractions(void)
		{
		for(int f_Count = 0; f_Count < m_vec_Sphere.size(); f_Count++)
			{
			BiSphere* f_Sphere = m_vec_Sphere[f_Count];

			f_Sphere->m_Mesh->m_InteractionType = 0;
			}
		}

	void BiMeshContainer::acInteract(float f_MouseX, float f_MouseY)
		{
		float pointX, pointY;
		DirectX::XMMATRIX projectionMatrix, viewMatrix, inverseViewMatrix, worldMatrix, translateMatrix, inverseWorldMatrix;
		DirectX::XMVECTOR direction, origin;
		DirectX::XMVECTOR f_Det;
		bool intersect, result;

#ifdef GENERIC_BUILD
		// Get the origin of the picking ray which is the position of the camera.
#if 1
		BiVector f_Origin(g_Origin.m128_f32[0] + (((2.0f * (float)f_MouseX) / (float)1366.0f) - 1.0f),
						  g_Origin.m128_f32[1] + ((((2.0f * (float)f_MouseY) / (float)768.0f) - 1.0f) * -1.0f),
						  g_Origin.m128_f32[2]);
#else
		BiVector f_Origin(g_Origin.m128_f32[0] + (((4.0f * (float)f_MouseX) / (float)1920.0f) - 2.0f),
						  (g_Origin.m128_f32[1] + ((((2.0f * (float)f_MouseY) / (float)1080.0f) - 1.0f) * -1.0f)) - 0.4f,
						  g_Origin.m128_f32[2]);
#endif
		BiVector f_Direction(g_viewIn.m128_f32[0] + (((2.0f * (float)f_MouseX) / (float)1366.0f) - 1.0f),
							 g_viewIn.m128_f32[1] + ((((2.0f * (float)f_MouseY) / (float)768.0f) - 1.0f) * -1.0f),
							 g_viewIn.m128_f32[2]);

		g_OriginBi = f_Origin;
		g_DirectionBi = f_Direction;

			// Normalize the ray direction.
		float f_DirDist = f_Direction.acLength();

		f_Direction.acNormalize();

		acClearInteractions();

		int f_One = -5.0f;
		float f_Length = 500000.0f;
		bool f_lngResult = false;
		for(int f_Count = 0; f_Count < m_vec_Sphere.size(); f_Count++)
			{
			bool f_Result = false;
			BiSphere* f_Sphere = m_vec_Sphere[f_Count];

			BiVector f_Pos = f_Sphere->m_Pos;
			BiVector f_VecTo = f_Pos - f_Origin;
			float f_ToLength = f_VecTo.acLength();
			BiVector f_VecToNew(f_Origin.m_X + (f_Direction.m_X * f_ToLength), f_Origin.m_Y + (f_Direction.m_Y * f_ToLength), f_Origin.m_Z + (f_Direction.m_Z * f_ToLength));
			BiVector f_VecDist = f_VecToNew - f_Pos;
			float f_DistLength = f_VecDist.acLength();

			if(f_DistLength <= f_Sphere->m_Dist)
				{
				f_Result = true;
				}

			if(f_Result)
				{
				if(f_Sphere->m_Dist <= f_Length)
					{
					f_Length = f_Sphere->m_Dist;
					f_One = f_Count;
					}

				f_lngResult = f_Result;
				}
			}

		if(f_lngResult)
			{
			m_vec_Sphere[f_One]->m_Mesh->acMark(GEN_INT_TYPE_PRESS);
			}
#endif
		}

#if 1
	bool BiSphere::RaySphereIntersect(DirectX::XMVECTOR rayOrigin, DirectX::XMVECTOR rayDirection)
		{
		float a, b, c;
		float discriminant = 0.0f;

#ifdef GENERIC_BUILD
		// Calculate the a, b, and c coefficients.
		a = (rayDirection.m128_f32[0] * rayDirection.m128_f32[0]) + (rayDirection.m128_f32[1] * rayDirection.m128_f32[1]) + (rayDirection.m128_f32[2] * rayDirection.m128_f32[2]);
		b = ((rayDirection.m128_f32[0] * rayOrigin.m128_f32[0]) + (rayDirection.m128_f32[1] * rayOrigin.m128_f32[1]) + (rayDirection.m128_f32[2] * rayOrigin.m128_f32[2])) * 2.0f;
		c = ((rayOrigin.m128_f32[0] * rayOrigin.m128_f32[0]) + (rayOrigin.m128_f32[1] * rayOrigin.m128_f32[1]) + (rayOrigin.m128_f32[2] * rayOrigin.m128_f32[2])) - (m_Dist * m_Dist);


		// Find the discriminant.
		discriminant = (b * b) - (4 * a * c);
#endif
		// if discriminant is negative the picking ray missed the sphere, otherwise it intersected the sphere.
		if (discriminant < 0.0f)
			{
			return false;
			}

		return true;
		}
#endif

	void BiMeshCore::acPrepare(float f_Time)
		{
		//.
		}

	void BiMeshCore::acProcess(float f_Time)
		{
		switch(m_Type)
			{
			case CUBE_COM_TYPE_COMPONENT:
				{
				switch(m_Type)
					{
					case CUBE_COM_FACTORY_ADSR:
						{
						for(int f_Count = 0; f_Count < m_MidiInput[0].m_vec_NoteOn.size(); f_Count++)
							{
							  ////////////
							 // BiNote
							//
							BiNote* f_Note = m_MidiInput[0].m_vec_NoteOn[f_Count];

							 /////////////
							// Controls
							float f_Attack = (float)m_Input[0];
							float f_Decay = (float)m_Input[1];
							float f_Sustain = (float)m_Input[2];
							float f_Release = (float)m_Input[3];

							float f_MidHeight = (float)m_Input[4];

							float f_Amp = 0.0f;

							float f_NoteLength = f_Note->m_TimeEnd - f_Note->m_TimeStart;
							float f_NotePlayed = f_Time - f_Note->m_TimeStart;
							float f_Percent = f_NotePlayed / f_NoteLength;

							if(f_Percent >= 0 && f_Percent < f_Attack)
								{
								f_Amp = (f_Percent / f_Attack);
								}
							else if(f_Percent >= f_Attack && f_Percent < f_Decay)
								{
								f_Amp = ((1 - ((f_Percent - f_Attack) / (f_Decay - f_Attack))) * (1.0f - f_MidHeight)) + f_MidHeight;
								}
							else if(f_Percent >= f_Decay && f_Percent < f_Sustain)
								{
								f_Amp = f_MidHeight;
								}
							else if(f_Percent >= f_Sustain && f_Percent < f_Release)
								{
								f_Amp = ((1 - ((f_Percent - f_Sustain) / (f_Release - f_Sustain))) * f_MidHeight);
								}

							m_VoltOutput[0].m_vec_Volt[f_Count] = f_Amp;
							}
						}break;

					case CUBE_COM_FACTORY_OSCILLATOR:
						{
						for(int f_Count = 0; f_Count < m_MidiInput[0].m_vec_NoteOn.size(); f_Count++)
							{
							  ////////////
							 // BiNote
							//
							BiNote* f_Note = m_MidiInput[0].m_vec_NoteOn[f_Count];

							 /////////////
							// Controls
							float f_Attack = (float)m_Input[0];
							float f_Decay = (float)m_Input[1];
							float f_Sustain = (float)m_Input[2];
							float f_Release = (float)m_Input[3];

							float f_MidHeight = (float)m_Input[4];

							float f_Amp = 0.0f;

							float f_NoteLength = f_Note->m_TimeEnd - f_Note->m_TimeStart;
							float f_NotePlayed = f_Time - f_Note->m_TimeStart;
							float f_Percent = f_NotePlayed / f_NoteLength;

							if(f_Percent >= 0 && f_Percent < f_Attack)
								{
								f_Amp = (f_Percent / f_Attack);
								}
							else if(f_Percent >= f_Attack && f_Percent < f_Decay)
								{
								f_Amp = ((1 - ((f_Percent - f_Attack) / (f_Decay - f_Attack))) * (1.0f - f_MidHeight)) + f_MidHeight;
								}
							else if(f_Percent >= f_Decay && f_Percent < f_Sustain)
								{
								f_Amp = f_MidHeight;
								}
							else if(f_Percent >= f_Sustain && f_Percent < f_Release)
								{
								f_Amp = ((1 - ((f_Percent - f_Sustain) / (f_Release - f_Sustain))) * f_MidHeight);
								}

							m_VoltOutput[0].m_vec_Volt[f_Count] = f_Amp;
							}
						}break;
					}
				}break;
			}
		}

	bool ag_hex2bin(unsigned char *p, const char *hexstr, size_t len)
		{
		char hex_byte[3];
		char *ep;

		hex_byte[2] = '\0';

		while(*hexstr && len)
			{
			if(!hexstr[1])
				{
				printf("hex2bin str truncated");
				return false;
				}

			hex_byte[0] = hexstr[0];
			hex_byte[1] = hexstr[1];

			*p = (unsigned char)strtol(hex_byte, &ep, 16);

			if(*ep)
				{
				printf("hex2bin failed on '%s'", hex_byte);
				return false;
				}

			p++;
			hexstr += 2;
			len--;
			}

		return (len == 0 && *hexstr == 0) ? true : false;
		}

	void ag_bin2hex(char *s, std::vector<unsigned int> p, size_t len)
		{
		int i;
		for(i = 0; i < len; i++)
			{
			sprintf(s + (i * 2), "%02x", p[i]);
			}
		}

	void ag_bin2hex(char *s, std::vector<unsigned char> p, size_t len)
		{
		int i;
		for(i = 0; i < len; i++)
			{
			sprintf(s + (i * 2), "%02x", p[i]);
			}
		}
	
	void ag_bin2hex(char *s, float p)
		{ sprintf(s, "%02x", p); }

	char *phex(const void *p, size_t n)
		{
		const unsigned char *cp = (unsigned char*)p;     /* Access as bytes. */
		char *s = (char*)malloc(2*n + 1);       /* 2*n hex digits, plus NUL. */
		size_t k;

			/*
			* Just in case - if allocation failed.
			*/
		if(s == NULL)
			return s;

		for(k = 0; k < n; ++k)
			{
			/*
			* Convert one byte of data into two hex-digit characters.
			*/
			sprintf(s + 2*k, "%02X", cp[k]);
			}

			/*
			* Terminate the string with a NUL character.
			*/
		s[2*n] = '\0';

		return s;
		}

  //////////////////////////////////////////////////////////////////////////
 // Cube TX
//
bool _Cag::ag_VerifyTXIN(std::shared_ptr<CubeTXIN> f_txin, float f_amount)
{
	//trace source of wealth
	std::shared_ptr<CubeTransaction> f_PrevTX = Cag->ag_get_TXfromvout(f_txin->m_vout);

	if(!f_PrevTX)
		{
		return false;
		}
	else
		{
		if(!f_PrevTX->isValid())
			{
			return false;
			}
		}

	bool f_find = false;
	for(int f_Z = 0; f_Z < f_PrevTX->m_txout.size(); f_Z++)
		{
		std::shared_ptr<CubeTXOUT> f_txout = f_PrevTX->m_txout[f_Z];

		if(f_txout->m_Flag == 1)
			{
			f_find = true;

			if(f_txout->m_owneramt < f_amount)
				{
				return false;
				}
			}
		}

	if(f_find == false)
		{
		return false;
		}
	else
		{
		return true;
		}
}

std::shared_ptr<ShareContainerExt> _Cag::ag_SelectPeerGraphExt(int f_JobID, int f_ServLay, int f_ShareID, int f_ShareOffset, int f_PEER, bool f_MainMutex)
{
	std::string f_ref_CurrentPath = "ag_SelectPeerGraphExt";

	ag_StatusLive(f_ref_CurrentPath, "f_ShareContainerExt");
	std::shared_ptr<ShareContainerExt> f_ShareContainer = std::make_shared_reflect<ShareContainerExt>();

	   ////////////
	  // Rewards
	 // Full Count
	// Tier Based Payment Rewards
	char* peerselectquery = ag_ClearChar(512);
	::sprintf(peerselectquery, "Call acPeerSelect(%i, %i, %i, %i, '%s')", g_PEER + 1, g_CurrentShareOffset + 1, f_ShareID, g_JobID, g_Wallet->GetAdr().c_str());
	g_SafeL[f_ServLay]->acSelectCommand(peerselectquery, 2, false, f_MainMutex);
	delete peerselectquery;

	int f_ShareCNT = 0;

	if(g_Schedular[f_ServLay]->acEntry(0)[0].at(0) == '0')
		{
		f_ShareCNT = 0;
		}
	else
		{
		f_ShareCNT = g_Schedular[f_ServLay]->acEntrySize();
		}

	if(f_ShareCNT > 0)
		{
		f_ShareContainer->m_espo_Owner = g_Schedular[f_ServLay]->acEntry(0)[0];
		f_ShareContainer->m_espo_Date = g_Schedular[f_ServLay]->acEntry(0)[1];
		f_ShareContainer->m_espo_ShareOffset = atoi(g_Schedular[f_ServLay]->acEntry(0)[2].c_str());
		f_ShareContainer->m_espo_Peer = atoi(g_Schedular[f_ServLay]->acEntry(0)[3].c_str());
		f_ShareContainer->m_espo_ID = atoi(g_Schedular[f_ServLay]->acEntry(0)[4].c_str());
		f_ShareContainer->m_espo_Score = atof(g_Schedular[f_ServLay]->acEntry(0)[5].c_str());
		f_ShareContainer->m_espo_Amount = atof(g_Schedular[f_ServLay]->acEntry(0)[6].c_str());
		f_ShareContainer->m_espo_ECN_Amount = atof(g_Schedular[f_ServLay]->acEntry(0)[7].c_str());
		f_ShareContainer->m_espo_ScoreSum = atof(g_Schedular[f_ServLay]->acEntry(0)[8].c_str());
		f_ShareContainer->m_espo_PeerCount = atoi(g_Schedular[f_ServLay]->acEntry(0)[9].c_str());
		f_ShareContainer->m_espo_SharesOnPeerCount = atoi(g_Schedular[f_ServLay]->acEntry(0)[10].c_str());
		f_ShareContainer->m_espo_TotalShares = atoi(g_Schedular[f_ServLay]->acEntry(0)[11].c_str());
		f_ShareContainer->m_espo_TotalSharesOwnPeer = atoi(g_Schedular[f_ServLay]->acEntry(0)[12].c_str());
		f_ShareContainer->m_espo_OwnPeerIndex = atoi(g_Schedular[f_ServLay]->acEntry(0)[13].c_str());
		}

	return f_ShareContainer;
}

#define ECOIN_PRO_CAP std::string("\n")

void _Cag::ag_Upload_Procedures(bool f_ResetProc)
{
	 /////////////////////////////////////////////////
	// First Conditionally Reset All procedures
	if(f_ResetProc == true)
		{
		std::string f_ResetString = "DELIMITER $$" + ECOIN_PRO_CAP +
			"DROP PROCEDURE IF EXISTS `acTopUpPeerBalance`$$" + ECOIN_PRO_CAP +
			"DROP PROCEDURE IF EXISTS `acPeerBalance`$$" + ECOIN_PRO_CAP +
			"DROP PROCEDURE IF EXISTS `acPeerSelect`$$" + ECOIN_PRO_CAP +
			"DELIMITER ;" + ECOIN_PRO_CAP;

		char* resetquery = ag_ClearChar(3000);

		sprintf(resetquery, "%s", f_ResetString.c_str());

		g_SafeL[0]->acSelectCommand(resetquery, false, false);

		delete resetquery;
		}

	std::string f_TopUpBalanceString = "DELIMITER $$" + ECOIN_PRO_CAP +
		"CREATE PROCEDURE IF NOT EXISTS `acTopUpPeerBalance`(`last_shareid` INTEGER(11), `last_jobid` INTEGER(11))" + ECOIN_PRO_CAP +
		"BEGIN" + ECOIN_PRO_CAP +
		"SET @lastid := `last_shareid`;" + ECOIN_PRO_CAP +
		"SET @lastjobid := `last_jobid`;" + ECOIN_PRO_CAP +
		"SET @lastowner := 'G';" + ECOIN_PRO_CAP +
		"SET @nextpeerid := 0;" + ECOIN_PRO_CAP +
		"SET @nextorderpull := 0;" + ECOIN_PRO_CAP +
		"SET @nextsumscore := 0;" + ECOIN_PRO_CAP +
		"SELECT owner INTO @lastowner FROM share WHERE id = @lastid;" + ECOIN_PRO_CAP +
		"SELECT IFNULL(MAX(peerid), 1), IFNULL(MAX(orderpull) + 1, 1), SUM(score) INTO @nextpeerid, @nextorderpull, @nextsumscore FROM share WHERE jobid = @lastjobid AND score > 0.0 AND owner = @lastowner;" + ECOIN_PRO_CAP +
		"UPDATE share SET scoresum := @nextsumscore WHERE owner = @lastowner;" + ECOIN_PRO_CAP +
		"UPDATE share SET peerid := @nextpeerid, orderpull := @nextorderpull WHERE id = @lastid;" + ECOIN_PRO_CAP +
		"END$$" + ECOIN_PRO_CAP +
		"DELIMITER ;" + ECOIN_PRO_CAP;

	char* querybalance = ag_ClearChar(6000);

	sprintf(querybalance, "%s", f_TopUpBalanceString.c_str());

	g_SafeL[0]->acSelectCommand(querybalance, false, false);

	delete querybalance;

	std::string f_PeerBalanceString = "DELIMITER $$" + ECOIN_PRO_CAP +
		"CREATE PROCEDURE IF NOT EXISTS `acPeerBalance`(`last_jobid` INTEGER(11))" + ECOIN_PRO_CAP +
		"BEGIN" + ECOIN_PRO_CAP +
		"SET @lastjobid := `last_jobid`;" + ECOIN_PRO_CAP +
		"SET @jobowner := 'G';" + ECOIN_PRO_CAP +
		"SET @scoresum := 0;" + ECOIN_PRO_CAP +
		"SET @peerid := 1;" + ECOIN_PRO_CAP +
		"SET @orderpull := 1;" + ECOIN_PRO_CAP +
		"SET @shareid := 0;" + ECOIN_PRO_CAP +
		"SET @stackowner := 'G';" + ECOIN_PRO_CAP +
		"UPDATE share SET scoresum := 0.0, peerid := 0, orderpull := 0 WHERE jobid = @lastjobid;" + ECOIN_PRO_CAP +
		"SELECT COALESCE(owner, 'G'), id INTO @jobowner, @shareid FROM share WHERE ((jobid = @lastjobid) AND (score > 0.0)) AND ((scoresum = 0.0) AND (orderpull = 0)) LIMIT 1;" + ECOIN_PRO_CAP +
		"WHILE (@shareid > 0) DO" + ECOIN_PRO_CAP +
		"SELECT SUM(score) INTO @scoresum FROM share WHERE ((jobid = @lastjobid) AND (score > 0.0)) AND (owner = @jobowner);" + ECOIN_PRO_CAP +
		"UPDATE share SET scoresum := @scoresum WHERE id = @shareid;" + ECOIN_PRO_CAP +
		"SET @shareid := 0;" + ECOIN_PRO_CAP +
		"SELECT COALESCE(owner, 'G'), id INTO @jobowner, @shareid FROM share WHERE ((jobid = @lastjobid) AND (score > 0.0)) AND ((scoresum = 0.0) AND (orderpull = 0)) LIMIT 1;" + ECOIN_PRO_CAP +
		"END WHILE;" + ECOIN_PRO_CAP +
		"SELECT COALESCE(owner, 'G'), id INTO @jobowner, @shareid FROM share WHERE ((jobid = @lastjobid) AND (score > 0.0)) AND ((peerid = 0) AND (orderpull = 0)) ORDER BY scoresum DESC LIMIT 1;" + ECOIN_PRO_CAP +
		"WHILE (@shareid > 0) DO" + ECOIN_PRO_CAP +
		"SELECT IFNULL(MAX(peerid), 0) INTO @peerid FROM share WHERE ((jobid = @lastjobid) AND (score > 0.0)) AND (owner = @jobowner);" + ECOIN_PRO_CAP +
		"SELECT IFNULL(MAX(peerid) + 1, @peerid), 1 INTO @peerid, @orderpull FROM share WHERE ((jobid = @lastjobid) AND (score > 0.0)) AND (@stackowner != @jobowner) AND (@peerid = 0);" + ECOIN_PRO_CAP +
		"SELECT IFNULL(MAX(orderpull) + 1, 1) INTO @orderpull FROM share WHERE ((jobid = @lastjobid) AND (score > 0.0) AND (owner = @jobowner));" + ECOIN_PRO_CAP +
		"UPDATE share SET peerid := @peerid, orderpull := @orderpull WHERE id = @shareid;" + ECOIN_PRO_CAP +
		"SET @shareid := 0;" + ECOIN_PRO_CAP +
		"SET @stackowner := @jobowner;" + ECOIN_PRO_CAP +
		"SELECT COALESCE(owner, 'G'), id INTO @jobowner, @shareid FROM share WHERE ((jobid = @lastjobid) AND (score > 0.0)) AND ((peerid = 0) AND (orderpull = 0)) ORDER BY scoresum DESC LIMIT 1;" + ECOIN_PRO_CAP +
		"END WHILE;" + ECOIN_PRO_CAP +
		"END$$" + ECOIN_PRO_CAP +
		"DELIMITER ;" + ECOIN_PRO_CAP;

	char* querypeerbalance = ag_ClearChar(6000);

	sprintf(querypeerbalance, "%s", f_PeerBalanceString.c_str());

	g_SafeL[0]->acSelectCommand(querypeerbalance, false, false);

	delete querypeerbalance;

	std::string f_SelectString = "DELIMITER $$" + ECOIN_PRO_CAP +
		"CREATE PROCEDURE IF NOT EXISTS `acPeerSelect`(`peer_limit` INTEGER(11), `row_limit` INTEGER(11), `last_jobid` INTEGER(11), `ownerin` VARCHAR(64))" + ECOIN_PRO_CAP +
		"BEGIN" + ECOIN_PRO_CAP +
		"SET @lastjobid := `last_jobid`;" + ECOIN_PRO_CAP +
		"SET @peer_limit := `peer_limit`;" + ECOIN_PRO_CAP +
		"SET @row_limit := `row_limit`;" + ECOIN_PRO_CAP +
		"SET @peer_count := 0;" + ECOIN_PRO_CAP +
		"SET @row_count := 0;" + ECOIN_PRO_CAP +
		"SET @total_row_count := 0;" + ECOIN_PRO_CAP +
		"SET @total_own_count := 0;" + ECOIN_PRO_CAP +
		"SET @ownowner := `ownerin`;" + ECOIN_PRO_CAP +
		"SET @ownpeerindex := 0;" + ECOIN_PRO_CAP +
		"SELECT IFNULL(MAX(peerid), `peer_limit`) INTO @peer_limit FROM share WHERE(@peer_limit >= peerid) AND((jobid = @lastjobid) AND(score > 0.0));" + ECOIN_PRO_CAP +
		"SELECT IFNULL(MAX(orderpull), `row_limit`) INTO @row_limit FROM share WHERE(peerid = @peer_limit) AND(@row_limit >= orderpull) AND((jobid = @lastjobid) AND(score > 0.0));" + ECOIN_PRO_CAP +
		"SELECT COUNT(id) INTO @row_count FROM share WHERE(peerid = @peer_limit) AND((jobid = @lastjobid) AND(score > 0.0));" + ECOIN_PRO_CAP +
		"SELECT COUNT(id), MAX(peerid) + 1 INTO @total_row_count, @peer_count FROM share WHERE((jobid = @lastjobid) AND(score > 0.0));" + ECOIN_PRO_CAP +
		"SELECT COUNT(id), MAX(peerid) INTO @total_own_count, @ownpeerindex FROM share WHERE((jobid = @lastjobid) AND(score > 0.0)) AND(owner = @ownowner);" + ECOIN_PRO_CAP +
		"SELECT owner, dated, @row_limit, @peer_limit, id, score, pledge, ecnpledge, scoresum, @peer_count, @row_count, @total_row_count, @total_own_count, @ownpeerindex FROM share WHERE((peerid = @peer_limit) AND(orderpull = @row_limit)) AND((jobid = @lastjobid) AND(score > 0.0));" + ECOIN_PRO_CAP +
		"END$$" + ECOIN_PRO_CAP +
		"DELIMITER ;" + ECOIN_PRO_CAP;

	char* queryselect = ag_ClearChar(6000);

	sprintf(queryselect, "%s", f_SelectString.c_str());

	g_SafeL[0]->acSelectCommand(queryselect, false, false);

	delete queryselect;

	//FOLLOWING PROCEDURE BUILD LIST
#if 0
	DELIMITER $$

	DROP PROCEDURE IF EXISTS `acPeerBalance`$$

	CREATE PROCEDURE IF NOT EXISTS `acPeerBalance`(`last_jobid` INTEGER(11))
	BEGIN
	SET @lastjobid := `last_jobid`;
	SET @jobowner := 'G';
	SET @scoresum := 0;
	SET @peerid := 1;
	SET @orderpull := 1;
	SET @shareid := 0;
	SET @stackowner := 'G';
	UPDATE share SET scoresum := 0.0, peerid := 0, orderpull := 0 WHERE jobid = @lastjobid;
	SELECT COALESCE(owner, 'G'), id INTO @jobowner, @shareid FROM share WHERE ((jobid = @lastjobid) AND (score > 0.0)) AND ((scoresum = 0.0) AND (orderpull = 0)) LIMIT 1;
	WHILE (@shareid > 0) DO
	SELECT SUM(score) INTO @scoresum FROM share WHERE ((jobid = @lastjobid) AND (score > 0.0)) AND (owner = @jobowner);
	UPDATE share SET scoresum := @scoresum WHERE id = @shareid;
	SET @shareid := 0;
	SELECT COALESCE(owner, 'G'), id INTO @jobowner, @shareid FROM share WHERE ((jobid = @lastjobid) AND (score > 0.0)) AND ((scoresum = 0.0) AND (orderpull = 0)) LIMIT 1;
	END WHILE;
	SELECT COALESCE(owner, 'G'), id INTO @jobowner, @shareid FROM share WHERE ((jobid = @lastjobid) AND (score > 0.0)) AND ((peerid = 0) AND (orderpull = 0)) ORDER BY scoresum DESC LIMIT 1;
	WHILE (@shareid > 0) DO
	SELECT IFNULL(MAX(peerid), 0) INTO @peerid FROM share WHERE ((jobid = @lastjobid) AND (score > 0.0)) AND (owner = @jobowner);
	SELECT IFNULL(MAX(peerid) + 1, @peerid), 1 INTO @peerid, @orderpull FROM share WHERE ((jobid = @lastjobid) AND (score > 0.0)) AND (@stackowner != @jobowner) AND (@peerid = 0);
	SELECT IFNULL(MAX(orderpull) + 1, 1) INTO @orderpull FROM share WHERE ((jobid = @lastjobid) AND (score > 0.0) AND (owner = @jobowner));
	UPDATE share SET peerid := @peerid, orderpull := @orderpull WHERE id = @shareid;
	SET @shareid := 0;
	SET @stackowner := @jobowner;
	SELECT COALESCE(owner, 'G'), id INTO @jobowner, @shareid FROM share WHERE ((jobid = @lastjobid) AND (score > 0.0)) AND ((peerid = 0) AND (orderpull = 0)) ORDER BY scoresum DESC LIMIT 1;
	END WHILE;
	END$$

	DROP PROCEDURE IF EXISTS `acTopUpPeerBalance`$$

	CREATE PROCEDURE IF NOT EXISTS `acTopUpPeerBalance`(`last_shareid` INTEGER(11), `last_jobid` INTEGER(11))
	BEGIN
	SET @lastid := `last_shareid`;
	SET @lastjobid := `last_jobid`;
	SET @lastowner := "G";
	SET @nextpeerid := 0;
	SET @nextorderpull := 0;
	SET @nextsumscore := 0;
	SELECT owner INTO @lastowner FROM share WHERE id = @lastid;
	SELECT IFNULL(MAX(peerid), 1), IFNULL(MAX(orderpull) + 1, 1), SUM(score) INTO @nextpeerid, @nextorderpull, @nextsumscore FROM share WHERE jobid = @lastjobid AND score > 0.0 AND owner = @lastowner;
	UPDATE share SET scoresum := @nextsumscore WHERE owner = @lastowner;
	UPDATE share SET peerid := @nextpeerid, orderpull := @nextorderpull WHERE id = @lastid;
	END$$

	DROP PROCEDURE IF EXISTS `acPeerSelect`$$

	CREATE PROCEDURE IF NOT EXISTS `acPeerSelect`(`peer_limit` INTEGER(11), `row_limit` INTEGER(11), `last_jobid` INTEGER(11), `ownerin` VARCHAR(64))
	BEGIN
	SET @lastjobid := `last_jobid`;
	SET @peer_limit := `peer_limit`;
	SET @row_limit := `row_limit`;
	SET @peer_count := 0;
	SET @row_count := 0;
	SET @total_row_count := 0;
	SET @total_own_count := 0;
	SET @ownowner := `ownerin`;
	SET @ownpeerindex := 0;
	SELECT IFNULL(MAX(peerid), `peer_limit`) INTO @peer_limit FROM share WHERE (@peer_limit >= peerid) AND ((jobid = @lastjobid) AND (score > 0.0));
	SELECT IFNULL(MAX(orderpull), `row_limit`) INTO @row_limit FROM share WHERE (peerid = @peer_limit) AND (@row_limit >= orderpull) AND ((jobid = @lastjobid) AND (score > 0.0));
	SELECT COUNT(id) INTO @row_count FROM share WHERE (peerid = @peer_limit) AND ((jobid = @lastjobid) AND (score > 0.0));
	SELECT COUNT(id), MAX(peerid) + 1 INTO @total_row_count, @peer_count FROM share WHERE ((jobid = @lastjobid) AND (score > 0.0));
	SELECT COUNT(id), MAX(peerid) INTO @total_own_count, @ownpeerindex FROM share WHERE ((jobid = @lastjobid) AND (score > 0.0)) AND (owner = @ownowner);
	SELECT owner, dated, @row_limit, @peer_limit, id, score, pledge, ecnpledge, scoresum, @peer_count, @row_count, @total_row_count, @total_own_count, @ownpeerindex FROM share WHERE ((peerid = @peer_limit) AND (orderpull = @row_limit)) AND ((jobid = @lastjobid) AND (score > 0.0));
	END$$

	DELIMITER ;

	DELIMITER $$

	DROP PROCEDURE IF EXISTS `acTopUpPeerBalanceAdvance`$$

	CREATE PROCEDURE IF NOT EXISTS `acTopUpPeerBalanceAdvance`(`last_shareid` INTEGER(11), `last_jobid` INTEGER(11))
	BEGIN
	SET @lastid := `last_shareid`;
	SET @lastjobid := `last_jobid`;
	SET @lastowner := 'G';
	SET @lastorderpull := 0;
	SET @nextpeerid := 1;
	SET @nextsumscore := 0;
	SET @lowerpeerid := 0;
	SET @lowerpeerowner := 'G';
	SELECT owner INTO @lastowner FROM share WHERE id = @lastid;
	SELECT IFNULL(MAX(orderpull + 1), 1) INTO @lastorderpull FROM share WHERE((jobid = @lastjobid) AND(owner = @lastowner) AND(id != @lastid));
	SELECT IFNULL(MAX(peerid), 1), SUM(score) INTO @nextpeerid, @nextsumscore FROM share WHERE((jobid = @lastjobid) AND(owner = @lastowner));
	SELECT IFNULL(MAX(peerid), @nextpeerid), @nextpeerid, COALESCE(MAX(owner), 'G') INTO @nextpeerid, @lowerpeerid, @lowerpeerowner FROM share WHERE(jobid = @lastjobid) AND((peerid < @nextpeerid) AND(@nextsumscore > scoresum));
	UPDATE share SET scoresum := @nextsumscore WHERE((owner = @lastowner) AND(jobid = @lastjobid));
	UPDATE share SET orderpull := @lastorderpull WHERE(id = @lastid);
	UPDATE share SET peerid := @nextpeerid WHERE(@nextpeerid != 0) AND((owner = @lastowner) AND(jobid = @lastjobid));
	UPDATE share SET peerid := @lowerpeerid WHERE(@lowerpeerid != 0) AND(@nextpeerid != @lowerpeerid) AND((owner = @lowerpeerowner) AND(jobid = @lastjobid));
	SELECT @lastid, @nextsumscore, @nextpeerid, @lastorderpull, @lowerpeerid, @lowerpeerowner;
	END$$

	DELIMITER;

	CALL acTopUpPeerBalanceAdvance(813, 1);
#endif
}

  /////////////////////////////////////////////////////////////////
 // 
// allow for default pledge block and full trust rewards block
float _Cag::ag_CalcOwnerGenesisTX(std::string f_Owner, int f_ShareID, std::shared_ptr<Cube::CubeTransaction> f_TX)
{
	 ////////////////
	// Win Amount //
	float f_Amount = 0.0f;

	char* txquery = ag_ClearChar(3000);

	int f_JobID = f_TX->m_jobid - 1;

	if(f_JobID < 0)
		{
		f_JobID = 0;
		}

	switch(f_TX->m_blocktype) //win g_Wallet->m_vec_jobboardid[g_Wallet->m_current_IDX]
		{
		case ecoin_BlockType::ecoin_Block_Target_TypeName:
			{
			sprintf(txquery, "SELECT 1, IFNULL(SUM(score), 0.0) / (SELECT IFNULL(SUM(score), 1.0) FROM share WHERE ((jobid = %i) AND (blocktype = %i))) * %f FROM share WHERE ((jobid = %i) AND (blocktype = %i) AND (owner = '%s'))", f_JobID, ecoin_BlockType::ecoin_Block_Target_TypeName, f_TX->m_reward, f_JobID, ecoin_BlockType::ecoin_Block_Target_TypeName, f_Owner.c_str());
			}break;

		case ecoin_BlockType::ecoin_Block_Target_TimedType:
			{
			sprintf(txquery, "SELECT 2, IFNULL(SUM(score), 0.0) / (SELECT IFNULL(SUM(score), 1.0) FROM share WHERE ((jobid = %i) AND (blocktype = %i))) * %f FROM share WHERE ((jobid = %i) AND (blocktype = %i) AND (owner = '%s'))", f_JobID, ecoin_BlockType::ecoin_Block_Target_TimedType, f_TX->m_reward, f_JobID, ecoin_BlockType::ecoin_Block_Target_TimedType, f_Owner.c_str());
			}break;

		case ecoin_BlockType::ecoin_Block_Target_SCP:
			{
			sprintf(txquery, "SELECT 3, IFNULL(myelementcount, 0) / (SELECT IFNULL(SUM(myelementcount), 0) FROM txout WHERE (jobid = %i)) * %f FROM txout WHERE ((jobid = %i) AND (owner = '%s'))", f_JobID, f_TX->m_reward, f_JobID, f_Owner.c_str());
			}break;

		case ecoin_BlockType::ecoin_Block_TimedPledge:
		case ecoin_BlockType::ecoin_Block_MaxPledge:
		case ecoin_BlockType::ecoin_Block_MaxTimedPledge:
			{
			sprintf(txquery, "SELECT 4, IFNULL(SUM(ecnpledge) / (SELECT IFNULL(SUM(ecnpledge), 1.0) FROM reference WHERE ((shareid = %i) AND (jobid = %i))) / (SELECT IFNULL(SUM(ecnpledge), 1.0) FROM reference WHERE (jobid = %i)), 0.0) FROM reference WHERE ((jobid = %i) AND (shareid = %i) AND (owner = '%s'));", f_TX->m_shareid, f_JobID, f_JobID, f_JobID, f_TX->m_shareid, f_Owner.c_str());
			}break;
		}

	g_SafeL[0]->acSelectCommand(txquery, false, false);

	delete txquery;

	int f_AmtLCount = 0;
		
	if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
		{
		f_AmtLCount = 0;
		}
	else
		{
		f_AmtLCount = g_Schedular[0]->acEntrySize();
		}

	//ECN::Stat::: f_TxLCount f_TxLCount
	if(f_AmtLCount == 1)
		{
		f_Amount = atof(g_Schedular[0]->acEntry(0)[1].c_str());
		}
	else
		{
#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif //add debug message
		}

	return f_Amount;
}

std::shared_ptr<CubeTransaction> _Cag::ag_getTX(int f_txid, int f_txoutid) //f_txoutid: optional, sets flag upon found for use later
{
	std::string f_ref_CurrentPath = "ag_getTX";

	ag_StatusLive(f_ref_CurrentPath, "f_TX");
	std::shared_ptr<CubeTransaction> f_TX = std::make_shared_reflect<CubeTransaction>();

	char* txquery = ag_ClearChar(1000);
	sprintf(txquery, "SELECT status, typed, hash, amt, fee, confirmation, jobid, reward, rewardid, blocktype, hdid, gnshareid, owner, hashnib, blockid FROM transactions WHERE id = %i", f_txid);
	g_SafeL[0]->acSelectCommand(txquery, false, false);
	delete txquery;

	int f_TxLCount = 0;
		
	if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
		{
		f_TxLCount = 0;
		}
	else
		{
		f_TxLCount = g_Schedular[0]->acEntrySize();
		}

	//ECN::Stat::: f_TxLCount
	if(f_TxLCount > 0)
		{
		f_TX->m_txid = f_txid;
		f_TX->m_status = atoi(g_Schedular[0]->acEntry(0)[0].c_str());
		f_TX->m_type = atoi(g_Schedular[0]->acEntry(0)[1].c_str());
		f_TX->m_Hash = g_Schedular[0]->acEntry(0)[2];
		f_TX->m_confirmation = atoi(g_Schedular[0]->acEntry(0)[5].c_str());
		f_TX->m_amt = atof(g_Schedular[0]->acEntry(0)[3].c_str());
		f_TX->m_fee = atof(g_Schedular[0]->acEntry(0)[4].c_str());
		f_TX->m_jobid = atoi(g_Schedular[0]->acEntry(0)[6].c_str());
		f_TX->m_reward = atof(g_Schedular[0]->acEntry(0)[7].c_str());
		f_TX->m_rewardid = atoi(g_Schedular[0]->acEntry(0)[8].c_str());
		f_TX->m_blocktype = atoi(g_Schedular[0]->acEntry(0)[9].c_str());
		f_TX->m_hdid = g_Schedular[0]->acEntry(0)[10];
		int f_gnsharesupport = atoi(g_Schedular[0]->acEntry(0)[11].c_str());
		f_TX->m_owner = g_Schedular[0]->acEntry(0)[12];
		f_TX->m_Hashnib = g_Schedular[0]->acEntry(0)[13];
		f_TX->m_blockid = atoi(g_Schedular[0]->acEntry(0)[14].c_str());

		//out
		char* txoutquery = ag_ClearChar(1000);
		sprintf(txoutquery, "SELECT id, adrid, owner, txoutamt, owneramt, myelementcount, dated FROM txout WHERE transactionid = %i", f_txid);
		g_SafeL[0]->acSelectCommand(txoutquery, false, false);
		delete txoutquery;

		int f_TxoutLCount = 0;
		
		if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
			{
			f_TxoutLCount = 0;
			}
		else
			{
			f_TxoutLCount = g_Schedular[0]->acEntrySize();
			}

		//ECN::Stat::: f_TxinLCount f_TxoutLCount
		if(f_TxoutLCount > 0)
			{
			for(int f_jet = 0; f_jet < f_TxoutLCount; f_jet++)
				{
				ag_StatusLive(f_ref_CurrentPath, "f_txout");
				std::shared_ptr<CubeTXOUT> f_txout = std::make_shared_reflect<CubeTXOUT>();

				f_txout->m_txid = f_txid;
				f_txout->m_txoutid = atoi(g_Schedular[0]->acEntry(f_jet)[0].c_str());
				f_txout->m_adrid = atoi(g_Schedular[0]->acEntry(f_jet)[1].c_str());
				f_txout->m_owner = g_Schedular[0]->acEntry(f_jet)[2];
				f_txout->m_txoutamt = atof(g_Schedular[0]->acEntry(f_jet)[3].c_str());
				f_txout->m_owneramt = atof(g_Schedular[0]->acEntry(f_jet)[4].c_str());
				f_txout->m_myelementcount = atoi(g_Schedular[0]->acEntry(f_jet)[5].c_str());

				//verify flag
				if(f_txout->m_txoutid == f_txoutid)
					{
					f_txout->m_Flag = 1;
					}

				f_TX->m_txout.push_back(f_txout);
				}
			}

		//in
		char* txinquery = ag_ClearChar(1000);
		sprintf(txinquery, "SELECT id, vout, pubkey, vsign, amt, dated FROM txin WHERE transactionid = %i", f_txid);
		g_SafeL[0]->acSelectCommand(txinquery, false, false);
		delete txinquery;

		int f_TxinLCount = 0;
		
		if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
			{
			f_TxinLCount = 0;
			}
		else
			{
			f_TxinLCount = g_Schedular[0]->acEntrySize();
			}

		//ECN::Stat::: f_TxinLCount f_TxinLCount
		if(f_TxinLCount > 0)
			{
			for(int f_jet = 0; f_jet < f_TxinLCount; f_jet++)
				{
				ag_StatusLive(f_ref_CurrentPath, "f_txin");
				std::shared_ptr<CubeTXIN> f_txin = std::make_shared_reflect<CubeTXIN>();

				f_txin->m_txinid = atoi(g_Schedular[0]->acEntry(0)[0].c_str());
				f_txin->m_vout = g_Schedular[0]->acEntry(0)[1];
				f_txin->m_pubkey = g_Schedular[0]->acEntry(0)[2];
				f_txin->m_sigstr = g_Schedular[0]->acEntry(0)[3];
				float f_txinrow4 = atof(g_Schedular[0]->acEntry(0)[4].c_str());

				  ///////////////////
				 // TXIN vout
				std::string f_vout = g_Schedular[0]->acEntry(0)[1];

				  /////////////
				 // Add Away
				//
				f_TX->m_txin.push_back(f_txin);

				   ///////////////////
				  // Detect Genesis
				 // Tracking... generate coin
				//
				if(f_vout.compare("Genesis Tracking") == 0)
					{
					if(f_TxoutLCount == 1)
						{
 						float f_Amount = ag_CalcOwnerGenesisTX(f_TX->m_txout[0]->m_owner, f_TX->m_jobid, f_TX);

						char* f_fiquery = ag_ClearChar(150);
						sprintf(f_fiquery, "SELECT id, amt FROM address WHERE owner = '%s'", f_TX->m_txout[0]->m_owner.c_str());
						g_SafeL[0]->acSelectCommand(f_fiquery, false, false);
						delete f_fiquery;

						int f_AdrCount = 0;
		
						if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
							{
							f_AdrCount = 0;
							}
						else
							{
							f_AdrCount = g_Schedular[0]->acEntrySize();
							}

						if(f_AdrCount > 0)
							{
							if(f_AdrCount > 1)
								{
#ifdef ECOIN_DEBUG_BREAKS
								__debugbreak();
#endif
								}

							float f_peer_Amount = atof(g_Schedular[0]->acEntry(0)[1].c_str());

							float f_full_reward = f_peer_Amount + f_Amount;

							f_TX->m_amt = f_Amount;
							f_txin->m_txid = f_txid;
							f_txin->m_amt = f_full_reward;
							f_txin->m_gnshareid = f_gnsharesupport;
							f_TX->m_txout[0]->m_txoutamt = f_Amount;
							f_TX->m_txout[0]->m_owneramt = f_full_reward;
							}
						else
							{
#ifdef ECOIN_DEBUG_BREAKS
							__debugbreak();
#endif
							//ECN::ADVWARN f_AdrCount f_AdrCount);
							}
						}
					else
						{
#ifdef ECOIN_DEBUG_BREAKS
						__debugbreak();
#endif
						//ECN::ADVWARN txout for genesis coin invalid txid f_TX->m_txid
						}
					}
				else if(f_vout.compare("Genesis Coin") == 0)
					{
					if(f_TxoutLCount == 1)
						{
						float f_Amount = 1.0f;

						char* f_fiquery = ag_ClearChar(256);
						sprintf(f_fiquery, "SELECT id, amt FROM address WHERE owner = '%s'", f_TX->m_txout[0]->m_owner.c_str());
						g_SafeL[0]->acSelectCommand(f_fiquery, false, false);
						delete f_fiquery;

						int f_AdrCount = 0;
		
						if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
							{
							f_AdrCount = 0;
							}
						else
							{
							f_AdrCount = g_Schedular[0]->acEntrySize();
							}

						if(f_AdrCount > 0)
							{
							if(f_AdrCount > 1)
								{
#ifdef ECOIN_DEBUG_BREAKS
								__debugbreak();
#endif
								//ECN::ADR ERROR
								}

							float f_peer_Amount = atof(g_Schedular[0]->acEntry(0)[1].c_str());

							float f_full_reward = f_peer_Amount + f_Amount;

							f_TX->m_amt = f_Amount;
							f_txin->m_txid = f_txid;
							f_txin->m_amt = f_full_reward;
							f_TX->m_txout[0]->m_txoutamt = f_Amount;
							f_TX->m_txout[0]->m_owneramt = f_full_reward;
							}
						else
							{
#ifdef ECOIN_DEBUG_BREAKS
							__debugbreak();
#endif
							//ECN::ADVWARN f_AdrCount f_AdrCount
							}
						}
					else
						{
#ifdef ECOIN_DEBUG_BREAKS
						__debugbreak();
#endif
						}
					}
				else
					{
					bool h_OK = true;

					f_txin->m_txid = f_txid;
					f_txin->m_amt = f_txinrow4;
					f_txin->m_gnshareid = f_gnsharesupport;

					std::string f_Hash = f_TX->m_Hash;
					std::string f_PubKey = f_txin->m_pubkey;
					std::string f_Signiture = f_txin->m_sigstr;
					
					h_OK = Cag->ag_Verify_PublicSigniture(f_PubKey, f_Hash, f_Signiture);

					if(h_OK == false)
						{
						f_TX->m_status = -5;
						f_TX->m_fresh = false;

						f_TX->m_Hash = "VERIFYFAILA";

#ifdef ECOIN_DEBUG_BREAKS_TX
						__debugbreak();
#endif //add debug message
						}

					f_TX->acHash();

					std::string f_PubKeyB = f_TX->m_txin[0]->m_pubkey;
					std::string f_HashB = f_TX->m_Hash;
					std::string f_SignitureB = f_TX->m_txin[0]->m_sigstr;

					h_OK = Cag->ag_Verify_PublicSigniture(f_PubKeyB, f_HashB, f_SignitureB);

					if(h_OK == false)
						{
						f_TX->m_status = -5;
						f_TX->m_fresh = false;

						f_TX->m_Hash += "VERIFYFAILB";

#ifdef ECOIN_DEBUG_BREAKS_TX
						__debugbreak();
#endif //add debug message
						}
					}
				}
			}
		}

	return f_TX;
}

#if 0
bool h_OK = ag_Verify_TX_ReHash_VerifySigniture(f_TX);

	if(h_OK == false)
		{
		f_TX->m_status = -5;
		f_TX->m_Hash = "VERIFYFAIL";

#ifdef ECOIN_DEBUG_BREAKS_TX
		__debugbreak();
#endif //add debug message
		}
#endif

#if 0
std::shared_ptr<CubeTransaction> ag_getTX(int f_ShareID, float f_CostCPS)
{
	//!function unused!
	std::string f_ref_CurrentPath = "ag_getTX";

	ag_StatusLive(f_ref_CurrentPath, "f_TX");
	std::shared_ptr<CubeTransaction> f_TX = std::make_shared_reflect<CubeTransaction>();

	char* txquery = ag_ClearChar(1000);
	sprintf(txquery, "SELECT id, status, typed, hash, amt, fee, confirmation, jobid, reward, rewardid, blocktype, hdid, shareid, gnshareid, owner, blockid FROM transactions WHERE id = %i", f_ShareID);
	g_SafeL[0]->acSelectCommand(txquery, false, false);
	delete txquery;

	int f_TxLCount = 0;
		
	if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
		{
		f_TxLCount = 0;
		}
	else
		{
		f_TxLCount = g_Schedular[0]->acEntrySize();
		}

	//ECN::Stat::: f_TxLCount f_TxLCount
	if(f_TxLCount > 0)
		{
		f_TX->m_txid = atoi(g_Schedular[0]->acEntry(0)[0].c_str());
		f_TX->m_status = atoi(g_Schedular[0]->acEntry(0)[1].c_str());
		f_TX->m_type = atoi(g_Schedular[0]->acEntry(0)[2].c_str());
		f_TX->m_Hash = g_Schedular[0]->acEntry(0)[3];
		f_TX->m_confirmation = atoi(g_Schedular[0]->acEntry(0)[6].c_str());
		f_TX->m_amt = atof(g_Schedular[0]->acEntry(0)[4].c_str());
		f_TX->m_fee = atof(g_Schedular[0]->acEntry(0)[5].c_str());
		f_TX->m_jobid = atoi(g_Schedular[0]->acEntry(0)[7].c_str());
		f_TX->m_reward = atof(g_Schedular[0]->acEntry(0)[8].c_str());
		f_TX->m_rewardid = atoi(g_Schedular[0]->acEntry(0)[9].c_str());
		f_TX->m_blocktype = atoi(g_Schedular[0]->acEntry(0)[10].c_str());
		f_TX->m_hdid = g_Schedular[0]->acEntry(0)[11];
		f_TX->m_shareid = atoi(g_Schedular[0]->acEntry(0)[12].c_str());
		int f_gnsharesupport = atoi(g_Schedular[0]->acEntry(0)[13].c_str());
		f_TX->m_owner = g_Schedular[0]->acEntry(0)[14];
		f_TX->m_blockid = atoi(g_Schedular[0]->acEntry(0)[15].c_str());

		//out
		char* txoutquery = ag_ClearChar(1000);;
		sprintf(txoutquery, "SELECT id, adrid, owner, pubkey, txoutamt, owneramt, myelementcount, dated FROM txout WHERE transactionid = %i", f_TX->m_txid);
		g_SafeL[0]->acSelectCommand(txoutquery, false, false);
		delete txoutquery;

		int f_TxoutLCount = 0;
		
		if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
			{
			f_TxoutLCount = 0;
			}
		else
			{
			f_TxoutLCount = g_Schedular[0]->acEntrySize();
			}

		//ECN::Stat::: f_TxinLCount f_TxoutLCount
		if(f_TxoutLCount > 0)
			{
			for(int f_jet = 0; f_jet < f_TxoutLCount; f_jet++)
				{
				ag_StatusLive(f_ref_CurrentPath, "f_txout");
				std::shared_ptr<CubeTXOUT> f_txout = std::make_shared_reflect<CubeTXOUT>();

				f_txout->m_txid = f_TX->m_txid;
				f_txout->m_txoutid = atoi(g_Schedular[0]->acEntry(f_jet)[0].c_str());
				f_txout->m_adrid = atoi(g_Schedular[0]->acEntry(f_jet)[1].c_str());
				f_txout->m_owner = g_Schedular[0]->acEntry(f_jet)[2];
				f_txout->m_txoutamt = atof(g_Schedular[0]->acEntry(f_jet)[3].c_str());
				f_txout->m_owneramt = atof(g_Schedular[0]->acEntry(f_jet)[4].c_str());
				f_txout->m_myelementcount = atoi(g_Schedular[0]->acEntry(f_jet)[5].c_str());

				f_TX->m_txout.push_back(f_txout);
				}
			}

		//in
		char* txinquery = ag_ClearChar(1000);
		sprintf(txinquery, "SELECT id, vout, pubkey, vsign, amt, dated FROM txin WHERE transactionid = %i", f_TX->m_txid);
		g_SafeL[0]->acSelectCommand(txinquery, false, false);
		delete txinquery;

		int f_TxinLCount = 0;
		
		if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
			{
			f_TxinLCount = 0;
			}
		else
			{
			f_TxinLCount = g_Schedular[0]->acEntrySize();
			}

		//ECN::Stat::: f_TxinLCount f_TxinLCount
		if(f_TxinLCount > 0)
			{
			for(int f_jet = 0; f_jet < f_TxinLCount; f_jet++)
				{
				ag_StatusLive(f_ref_CurrentPath, "f_txin");
				std::shared_ptr<CubeTXIN> f_txin = std::make_shared_reflect<CubeTXIN>();

				f_txin->m_txinid = atoi(g_Schedular[0]->acEntry(0)[0].c_str());
				f_txin->m_vout = g_Schedular[0]->acEntry(0)[1];
				f_txin->m_pubkey = g_Schedular[0]->acEntry(0)[2];
				f_txin->m_sigstr = g_Schedular[0]->acEntry(0)[3];
				float f_txinrow4 = atof(g_Schedular[0]->acEntry(0)[4].c_str());

				  ///////////////////
				 // TXIN vout
				std::string f_vout = g_Schedular[0]->acEntry(0)[1];


				  /////////////
				 // Add away
				//
				f_TX->m_txin.push_back(f_txin);

				  ///////////////////
				 // Detect Genesis
				// Tracking
				if(f_vout.compare("Genesis Tracking") == 0)
					{
					if(f_TxoutLCount == 1)
						{
 						float f_Amount = ag_CalcOwnerGenesisTX(f_TX->m_txout[0]->m_owner, f_TX->m_jobid, f_TX);

						char* f_fiquery = ag_ClearChar(256);
						sprintf(f_fiquery, "SELECT id, amt FROM address WHERE owner = '%s'", f_TX->m_txout[0]->m_owner.c_str());
						g_SafeL[0]->acSelectCommand(f_fiquery, false, false);
						delete f_fiquery;

						int f_AdrCount = 0;
		
						if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
							{
							f_AdrCount = 0;
							}
						else
							{
							f_AdrCount = g_Schedular[0]->acEntrySize();
							}

						if(f_AdrCount > 0)
							{
							if(f_AdrCount > 1)
								{
#ifdef ECOIN_DEBUG_BREAKS
								__debugbreak();
#endif
								}

							float f_peer_Amount = atof(g_Schedular[0]->acEntry(0)[1].c_str());

							float f_full_reward = f_peer_Amount + f_Amount;

							f_TX->m_amt = f_Amount;
							f_txin->m_txid = f_TX->m_txid;
							f_txin->m_amt = f_full_reward;
							f_txin->m_gnshareid = f_gnsharesupport;
							f_TX->m_txout[0]->m_txoutamt = f_Amount;
							f_TX->m_txout[0]->m_owneramt = f_full_reward;
							}
						else
							{
#ifdef ECOIN_DEBUG_BREAKS
							__debugbreak();
#endif
							//ECN::ADVWARN f_AdrCount f_AdrCount);
							}
						}
					else
						{
#ifdef ECOIN_DEBUG_BREAKS
						__debugbreak();
#endif
						//ECN::ADVWARN txout for genesis coin invalid txid f_TX->m_txid
						}
					}
				else if(f_vout.compare("Genesis Coin") == 0)
					{
					if(f_TxoutLCount == 1)
						{
						float f_Amount = 1.0f;

						char* f_fiquery = ag_ClearChar(150);
						sprintf(f_fiquery, "SELECT id, amt FROM address WHERE owner = '%s'", f_TX->m_txout[0]->m_owner.c_str());
						g_SafeL[0]->acSelectCommand(f_fiquery, false, false);
						delete f_fiquery;

						int f_AdrCount = 0;
		
						if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
							{
							f_AdrCount = 0;
							}
						else
							{
							f_AdrCount = g_Schedular[0]->acEntrySize();
							}

						if(f_AdrCount > 0)
							{
							if(f_AdrCount > 1)
								{
#ifdef ECOIN_DEBUG_BREAKS
								__debugbreak();
#endif
								//ECN::ADR ERROR
								}
							
							float f_peer_Amount = atof(g_Schedular[0]->acEntry(0)[1].c_str());

							float f_full_reward = f_peer_Amount + f_Amount;

							f_TX->m_amt = f_Amount;
							f_txin->m_txid = f_TX->m_txid;
							f_txin->m_amt = f_full_reward;
							f_TX->m_txout[0]->m_txoutamt = f_Amount;
							f_TX->m_txout[0]->m_owneramt = f_full_reward;
							}
						else
							{
#ifdef ECOIN_DEBUG_BREAKS
							__debugbreak();
#endif
							//ECN::ADVWARN f_AdrCount f_AdrCount
							}
						}
					else
						{
#ifdef ECOIN_DEBUG_BREAKS
						__debugbreak();
#endif
						//ECN::ADVWARN txout for genesis coin invalid txid f_TX->m_txid
						}
					}
				else
					{
					bool h_OK = true;

					f_txin->m_txid = f_TX->m_txid;
					f_txin->m_amt = f_txinrow4;
					f_txin->m_gnshareid = f_gnsharesupport;

					std::string f_Hash = f_TX->m_Hash;
					std::string f_PubKey = f_txin->m_pubkey;
					std::string f_Signiture = f_txin->m_sigstr;
					
					h_OK = _Cag::ag_Verify_PublicSigniture(f_PubKey, f_Hash, f_Signiture);

					if(h_OK == false)
						{
						f_TX->m_status = -5;
						f_TX->m_fresh = false;

						f_TX->m_Hash = "VERIFYFAIL";

#ifdef ECOIN_DEBUG_BREAKS_TX
						__debugbreak();
#endif //add debug message
						}

					f_TX->acHash();

					std::string f_HashB = f_TX->m_Hash;
					std::string f_PubKeyB = f_TX->m_txin[0]->m_pubkey;
					std::string f_SignitureB = f_TX->m_txin[0]->m_sigstr;

					h_OK = _Cag::ag_Verify_PublicSigniture(f_PubKeyB, f_HashB, f_SignitureB);

					if(h_OK == false)
						{
						f_TX->m_status = -5;
						f_TX->m_fresh = false;

						f_TX->m_Hash += "VERIFYFAIL";

#ifdef ECOIN_DEBUG_BREAKS_TX
						__debugbreak();
#endif //add debug message
						}
					}
				}
			}
		}

	return f_TX;
}
#endif

std::shared_ptr<CubeTransaction> _Cag::ag_get_TXfromvout(std::string f_vout)
{
	std::string f_ref_CurrentPath = "ag_get_TXfromvout";

	char* txquery = ag_ClearChar(1000);
	sprintf(txquery, "SELECT IFNULL(MAX(txoutlist.transactionid), -1), IFNULL(txoutlist.id FROM txout AS txoutlist INNER JOIN transactions AS txlist ON (txoutlist.transactionid = txlist.id) AND (txoutlist.owner = '%s') AND (txlist.status != -5) AND (txlist.confirmation = 6) ORDER BY dated DESC LIMIT 1", f_vout.c_str());
	g_SafeL[0]->acSelectCommand(txquery, false, false);
	delete txquery;

	std::shared_ptr<CubeTransaction> f_TX = nullptr;

	if(g_Schedular[0]->acEntry(0)[0].at(0) != '0')
		{
		int f_TXoutID = ag_CheckInteger(g_Schedular[0]->acEntry(0)[1]);
		int f_TxLID = ag_CheckInteger(g_Schedular[0]->acEntry(0)[0]);

		if((f_TxLID > 0) && (f_TXoutID > 0))
			{
			f_TX = Cag->ag_getTX(f_TxLID, f_TXoutID);

#ifdef ECOIN_DEBUG_BREAKS_TX
			if(f_TX->m_status == -5)
				{
				__debugbreak();
				}
#endif	//add debug message

			return f_TX;
			}
		}

#ifdef ECOIN_DEBUG_BREAKS_TX
	__debugbreak();
#endif	//add debug message

	return nullptr;
}

bool _Cag::ag_Verify_TX_ReHash_VerifySigniture(std::shared_ptr<Cube::CubeTransaction> f_TX)
{
	//rehash tx
	f_TX->acHash();

	std::string f_PubKey = f_TX->m_txin[0]->m_pubkey;

	std::string f_Hash = f_TX->m_Hash;

	std::string f_Signiture = f_TX->m_txin[0]->m_sigstr;

	bool h_OK = Cag->ag_Verify_PublicSigniture(f_PubKey, f_Hash, f_Signiture);

#ifdef ECOIN_DEBUG_BREAKS
	if(h_OK == false)
		{
		__debugbreak();
		}
#endif

	return h_OK;
}

bool _Cag::ag_Verify_PublicSigniture(std::string f_PubKey, std::string f_Hash, std::string f_Sign)
{
	//prime public key
	std::vector<unsigned char> vch;

	for(int f_XY = 0; f_XY < f_PubKey.length(); f_XY++)
		{
		vch.push_back(f_PubKey.at(f_XY));
		}

	std::shared_ptr<CPubKey> f_PublicKey = std::make_shared<CPubKey>(vch);

	//prime signiture
	std::vector<unsigned char> f_vchSig;

	for(int f_XY = 0; f_XY < f_Sign.length(); f_XY++)
		{
		f_vchSig.push_back(f_Sign.at(f_XY));
		}

	unsigned char k[32];

	ag_hex2bin(k, f_Hash.c_str(), 64);

	uint256& f_256uint = reinterpret_cast<uint256&>(k);

	bool h_OK = f_PublicKey->Verify(f_256uint, f_vchSig);

#ifdef ECOIN_DEBUG_BREAKS_TX
	if(h_OK == false)
		{
		__debugbreak();
		}
#endif //add debug message

	return h_OK;
}

float _Cag::ag_OwnerBalance(std::string f_owner)
{
	char* balquery = ag_ClearChar(1000);
	sprintf(balquery, "SELECT id, amt, owner FROM address WHERE owner = '%s'", f_owner.c_str());
	g_SafeL[0]->acSelectCommand(balquery, true, false);
	delete balquery;

	int f_balCount = 0;

	if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
		{
		f_balCount = 0;
		}
	else
		{
		f_balCount = g_Schedular[0]->acEntrySize();
		}

	//ECN::Stat::: f_balCount f_balCount
	if(f_balCount > 0)
		{
		float f_amt = atof(g_Schedular[0]->acEntry(0)[1].c_str());

		return f_amt;
		}
	else
		{
#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif

		//ECN::Error address not found:: owner balance
		}

	return -1.0f;
}

void _Cag::ag_UpdateOwnerBalance(std::string f_Owner, float f_Amount)
{
	char* f_balupvalue[1];
	char* f_balupfield[1];
	char* f_balupwhere[1];

	f_balupvalue[0] = (char*)malloc(sizeof(char) * 1024);
	f_balupfield[0] = (char*)malloc(sizeof(char) * 1024);
	f_balupwhere[0] = (char*)malloc(sizeof(char) * 1024);

	sprintf(f_balupfield[0], "amt");
	sprintf(f_balupvalue[0], "%f", f_Amount);
	sprintf(f_balupwhere[0], "owner = '%s'", f_Owner.c_str());

	g_SafeL[0]->Update("address", (const char **)f_balupfield, (const char **)f_balupvalue, 1, f_balupwhere[0], false, false);

	free(f_balupvalue[0]);
	free(f_balupfield[0]);
	free(f_balupwhere[0]);
}

std::shared_ptr<Cube::CubeResults> _Cag::ag_GatherTransactions(int f_JobID, int f_IDX)
{
	std::string f_ref_CurrentPath = "ag_GatherTransactions";

	std::string f_Result;
	f_Result.clear();

	std::string f_unverified_Result;
	f_unverified_Result.clear();

	std::string f_ReferencesPad;
	f_ReferencesPad.clear();

	std::string f_FinalResult;
	f_FinalResult.clear();

	std::string f_CurrentNib = "0000000000000000000000000000000000000000000000000000000000000001";

	ag_StatusLive(f_ref_CurrentPath, "f_CubeResults");
	std::shared_ptr<Cube::CubeResults> f_CubeResults = std::make_shared_reflect<Cube::CubeResults>();

	char* txcountquery = ag_ClearChar(2555);
	::sprintf(txcountquery, "SELECT IFNULL(COUNT(id), 0), IFNULL(MIN(id), 0) FROM transactions WHERE (status != -5) AND (jobid = %i)", f_JobID);
	g_SafeL[0]->acSelectCommand(txcountquery, 2, false);
	delete txcountquery;

	int f_TxCLCount = 0;
		
	if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
		{
		f_TxCLCount = 0;
		}
	else
		{
		f_TxCLCount = g_Schedular[0]->acEntrySize();
		}

	int f_TXRowCount = 0;

	if(f_TxCLCount == 1)
		{
		f_TXRowCount = atoi(g_Schedular[0]->acEntry(0)[0].c_str());

		 /////////////////
		// CubeResults //
		f_CubeResults->m_HashNibCount = f_TXRowCount / ECOIN_TX_NIB_SIZE;

		char* txquery = ag_ClearChar(1024);
		::sprintf(txquery, "SELECT id, hash, confirmation, owner, jobid, locktime FROM transactions WHERE ((id >= IFNULL((SELECT MAX(id) FROM transactions WHERE ((status != -5) AND (jobid = %i) AND (hashnib != 'G'))), IFNULL((SELECT MIN(id) FROM transactions WHERE ((status != -5) AND (jobid = %i) AND (hashnib = 'G'))), 0))) AND (status != -5) AND (jobid = %i)) ORDER BY id ASC LIMIT %i", f_JobID, f_JobID, f_JobID, ECOIN_TX_NIB_SIZE);
		g_SafeL[0]->acSelectCommand(txquery, 2, false);
		delete txquery;

		int f_TxLCount = 0;
		
		if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
			{
			f_TxLCount = 0;
			}
		else
			{
			f_TxLCount = g_Schedular[0]->acEntrySize();
			}

		//copy entrant board [TX]
		std::shared_ptr<std::vector<std::vector<std::string>>> f_EntryTX = g_Schedular[0]->acEntryPtr();

		if(f_TxLCount > 0)
			{
			char* txnibquery = ag_ClearChar(1024);
			::sprintf(txnibquery, "SELECT IFNULL(MAX(id), 0), COALESCE(hashnib, 'G') FROM transactions WHERE (status != -5) AND ((jobid = %i) AND (hashnib != 'G'))", f_JobID);
			g_SafeL[0]->acSelectCommand(txnibquery, 2, false);
			delete txnibquery; //HashNib Grab

			int f_TxNibLCount = 0;
		
			if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
				{
				f_TxNibLCount = 0;
				}
			else
				{
				f_TxNibLCount = g_Schedular[0]->acEntrySize();
				}

			if(f_TxNibLCount == 1)
				{
				f_CurrentNib = g_Schedular[0]->acEntry(0)[1];
				}

			std::vector<std::shared_ptr<CubeTransaction>> f_vec_TX;

			int f_idx_vec_TX = 0;
			int f_UnConfirmed = 0;
			bool f_ScanTX = true;

			while(f_ScanTX == true)
 				{
				//f_idx_vec_TX hash += 1
				ag_StatusLive(f_ref_CurrentPath, "f_Transaction");
				std::shared_ptr<CubeTransaction> f_Transaction = std::make_shared_reflect<CubeTransaction>();

				f_Transaction->m_txid = atoi(f_EntryTX->at(f_idx_vec_TX)[0].c_str());
				f_Transaction->m_Hash = f_EntryTX->at(f_idx_vec_TX)[1];
				f_Transaction->m_confirmation = atoi(f_EntryTX->at(f_idx_vec_TX)[2].c_str());
				f_Transaction->m_owner = f_EntryTX->at(f_idx_vec_TX)[3];
				f_Transaction->m_jobid = atoi(f_EntryTX->at(f_idx_vec_TX)[4].c_str());
				f_Transaction->m_locktime = atoi(f_EntryTX->at(f_idx_vec_TX)[5].c_str());
				f_Transaction->m_status = 1;

				f_vec_TX.push_back(f_Transaction);

				f_idx_vec_TX++;

				if((f_Transaction->m_confirmation < 6) && (f_Transaction->m_status != -5))
					{
					f_UnConfirmed++;

					if(f_UnConfirmed >= ECOIN_TX_CONFIRM_SIZE)
						{
						f_ScanTX = false;
						}
					}

				if((f_idx_vec_TX >= f_TxLCount) || (f_idx_vec_TX >= f_TXRowCount))
					{
					f_ScanTX = false;
					}
				}

			std::vector<std::shared_ptr<CubeTransaction>> f_vec_TransactionA;

			f_Result.clear(); //gathered result tx
			f_unverified_Result.clear(); //gathered result tx
			
			for(int f_Jet = 0; f_Jet < f_idx_vec_TX; f_Jet++) //perform genesis tx duplication check
				{
				int f_txid = f_vec_TX[f_Jet]->m_txid;
				std::string f_txowner = f_vec_TX[f_Jet]->m_owner;
				int f_txjobid = f_vec_TX[f_Jet]->m_jobid;
				int f_txlc = f_vec_TX[f_Jet]->m_locktime;
				
				for(int f_RM = 0; f_RM < f_idx_vec_TX; f_RM++)
					{
					if(f_Jet != f_RM)
						{
						if(f_vec_TX[f_RM]->m_status != -5)
							{
							int f_RMid = f_vec_TX[f_RM]->m_txid;
							std::string f_RMowner = f_vec_TX[f_RM]->m_owner;
							int f_RMjobid = f_vec_TX[f_RM]->m_jobid;
							int f_RMlc = f_vec_TX[f_RM]->m_locktime;
							
							if(((f_txlc == 2) && (f_RMlc == 2)) && (f_txowner.compare(f_RMowner) == 0) && (f_txjobid == f_RMjobid))
								{
								if(f_txid > f_RMid)
									{
									f_vec_TX[f_RM]->m_status = -5;
									
									std::shared_ptr<CubeTransaction> f_TransactionA = Cag->ag_getTX(f_RMid);

									f_TransactionA->m_fresh = VERIFY_FAIL;

									f_unverified_Result += Cag->ag_cont_VerifySingleTransaction(f_TransactionA, VERIFY_FAIL);
									}
								}
							}
						}
					}
				}

			  ///////////////////////////////
			 // result gathered each spin //
			///////////////////////////////
			bool f_ResultOn = true;

			std::shared_ptr<CubeTransaction> f_lastTransactionA = nullptr;

			for(int f_t = 0; f_t < f_idx_vec_TX; f_t++)
				{
				if(f_vec_TX[f_t]->m_status != -5)
					{
					if(f_vec_TX[f_t]->m_confirmation < 6)
						{
						std::shared_ptr<CubeTransaction> f_TransactionA = Cag->ag_getTX(f_vec_TX[f_t]->m_txid);

						if(f_TransactionA->isValid() == true)
							{
							f_TransactionA->m_fresh = VERIFY_SUCCEEDING;

							f_Result += Cag->ag_cont_VerifySingleTransaction(f_TransactionA, VERIFY_SUCCEEDING);

							f_vec_TransactionA.push_back(f_TransactionA);
							}
						else
							{
							f_TransactionA->m_fresh = VERIFY_FAIL;
					
							f_Result += Cag->ag_cont_VerifySingleTransaction(f_TransactionA, VERIFY_FAIL);

							f_vec_TransactionA.push_back(f_TransactionA);
							}

						if(f_TransactionA->m_confirmation != 6)
							{
							f_ResultOn = false;
							}
						else
							{
							f_lastTransactionA = f_TransactionA;
							}
						}
					else //win conditions add previously verified tx onto pile
						{
						f_Result += f_vec_TX[f_t]->m_Hash;
						}
					}
				else //win conditions add previously verified tx onto pile
					{
					f_Result += f_vec_TX[f_t]->m_Hash;
					}
				}

			if(f_UnConfirmed <= 0)
				{
				f_ReferencesPad = "";
				}

			if(f_ResultOn == true)
				{
				if(f_lastTransactionA != nullptr)
					{
					f_ReferencesPad = Cag->ag_GatherAllReferences(f_lastTransactionA->m_jobid, f_IDX);

					char* f_refpadvalue[1];
					char* f_refpadfield[1];
					char* f_refpadwhere[1];

					f_refpadvalue[0] = (char*)malloc(sizeof(char) * 1024);
					f_refpadfield[0] = (char*)malloc(sizeof(char) * 1024);
					f_refpadwhere[0] = (char*)malloc(sizeof(char) * 1024);

					sprintf(f_refpadfield[0], "hashnib");
					sprintf(f_refpadvalue[0], "%s", f_ReferencesPad.c_str());
					sprintf(f_refpadwhere[0], "id = %i", f_lastTransactionA->m_txid);

					g_SafeL[0]->Update("transactions", (const char**)f_refpadfield, (const char**)f_refpadvalue, 1, (const char*)f_refpadwhere[0], false, false);

					free(f_refpadvalue[0]);
					free(f_refpadfield[0]);
					free(f_refpadwhere[0]);

					bool h_OKa = Cag->ag_makeGenesisCoin();
					}

				f_CubeResults->m_Job_Complete = true;
				}

			g_hasha.init(); //reset hasher state
			g_hasha.process(f_Result.begin(), f_Result.end());
			g_hasha.finish();
			picosha2::get_hash_hex_string(g_hasha, f_FinalResult);
			}
		else
			{
			f_ReferencesPad = "";
			}
		}
	else
		{
		f_ReferencesPad = "";
		}

	if(f_FinalResult.length() <= 0)
		{
		f_Result += "0000000000000000000000000000000000000000000000000000000000000001"; //no tx worth checking simply return genesis tx pad
		}
	else
		{
		f_Result = f_CurrentNib + f_FinalResult + f_ReferencesPad;

		  /////////////////
	     // CubeResults //
		/////////////////

		f_CubeResults->m_CurrentNib = f_CurrentNib;
		f_CubeResults->m_ReferencesPad = f_ReferencesPad;
		f_CubeResults->m_FinalResult = f_FinalResult;
		f_CubeResults->m_Result = f_Result;
		}

	return f_CubeResults;
}

std::string _Cag::ag_GatherAllReferences(int f_JobID, int f_IDX)
{
	std::string f_ref_CurrentPath = "ag_GatherAllReferences";

	std::string f_ReferencePad;
	f_ReferencePad.clear();

	char* referencequery = ag_ClearChar(1000);
	::sprintf(referencequery, "SELECT md5(group_concat(concat(id, hdid, access, shareid, jobid, blockid, comid, score, owner, pledge, ecnpledge, dated))) as hash, 1 as grouper FROM reference WHERE ((status != -5) AND (jobid >= %i) AND (jobid <= %i)) GROUP BY grouper LIMIT %i", g_Wallet->m_vec_joborigin[f_IDX], g_Wallet->m_vec_jobid[f_IDX], ECOIN_TX_NIB_SIZE * ECOIN_TX_REFERON_NIB_RATIO);
	g_SafeL[0]->acSelectCommand(referencequery, false, false);
	delete referencequery;

	int f_RfLCount = 0;
		
	if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
		{
		f_RfLCount = 0;
		}
	else
		{
		f_RfLCount = g_Schedular[0]->acEntrySize();
		}

	if(f_RfLCount == 1)
		{
		f_ReferencePad = g_Schedular[0]->acEntry(0)[0];

		return f_ReferencePad;
		}

	return "00000000000000000000000000000001";
}

std::string _Cag::ag_cont_VerifySingleTransaction(std::shared_ptr<CubeTransaction> f_Transaction, bool f_initialVerified)
{
	bool f_Verified = f_initialVerified;

	if(f_initialVerified == true)
		{
		if(f_Transaction->m_confirmation < 6)
			{
			float f_combin = 0.0f;

			for(int f_Jet = 0; f_Jet < f_Transaction->m_txin.size(); f_Jet++)
				{
				if((f_Transaction->m_txin[f_Jet]->m_gnshareid > 0) || (f_Transaction->m_txin[f_Jet]->m_vout.compare("Genesis Coin") == 0) || (f_Transaction->m_txin[f_Jet]->m_vout.compare("Genesis Tracking") == 0))
					{  //genesis share present
					if((f_Transaction->m_txin[f_Jet]->m_vout.compare("Genesis Tracking") == 0))
						{  //genesis reward
						char* rewardquery = ag_ClearChar(1000);

						sprintf(rewardquery, "SELECT reward FROM reward WHERE id = %i", f_Transaction->m_rewardid);

						g_SafeL[0]->acSelectCommand(rewardquery, 2, false);

						delete rewardquery;

						int f_RewardLCount = 0;
		
						if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
							{
							f_RewardLCount = 0;
							}
						else
							{
							f_RewardLCount = g_Schedular[0]->acEntrySize();
							}

						//ECN::Stat::: f_RewardLCount != 1
						if(f_RewardLCount != 1)
							{
							f_Verified = VERIFY_FAIL;

							f_Transaction->m_fresh = VERIFY_FAIL;
							}
						else  //One Reward Row
							{
							float f_Reward = atof(g_Schedular[0]->acEntry(0)[0].c_str());

							if(f_Reward != f_Transaction->m_reward)
								{
								f_Verified = VERIFY_FAIL;

								f_Transaction->m_fresh = VERIFY_FAIL;
								}
							else  //in sync, transaction and reward row
								{
								if((f_Reward < 0.0f) || (f_Reward > 50.0f))
									{
									f_Verified = VERIFY_FAIL;

									f_Transaction->m_fresh = VERIFY_FAIL;
									}
								else  //reasonable reward row
									{
									f_combin += f_Transaction->m_txin[f_Jet]->m_amt;
									}
								}
							}
						}
					else if((f_Transaction->m_txin[f_Jet]->m_vout.compare("Genesis Coin") == 0))
						{  //genesis reward
						f_combin += 1.0f;
						}
					}
				else
					{
					f_combin += f_Transaction->m_txin[f_Jet]->m_amt;
					}
				}

			//tx Input size test
			if(f_combin != f_Transaction->m_amt)
				{
				f_Verified = VERIFY_FAIL;

				f_Transaction->m_fresh = VERIFY_FAIL;
				}

			float f_combout = 0.0f;

			for(int f_Jet = 0; f_Jet < f_Transaction->m_txout.size(); f_Jet++)
				{
				f_combout += f_Transaction->m_txout[f_Jet]->m_txoutamt;
				}

			//tx Output size test
			if(f_combout != f_Transaction->m_amt)
				{
				f_Verified = VERIFY_FAIL;

				f_Transaction->m_fresh = VERIFY_FAIL;
				}

			if((f_Verified == true) && (f_Transaction->m_txin[0]->m_gnshareid <= 0) && (f_Transaction->m_txin[0]->m_gnshareid != -2) && (f_Transaction->m_txin[0]->m_vout.compare("Genesis Coin") != 0) && (f_Transaction->m_txin[0]->m_vout.compare("Genesis Tracking") != 0))
				{
				for(int f_helly = 0; f_helly < f_Transaction->m_txin.size(); f_helly++)
					{
					std::shared_ptr<CubeTXIN> f_txin = f_Transaction->m_txin[f_helly];

					f_Verified = ag_VerifyTXIN(f_txin, f_Transaction->m_amt);
					}
				}
			}
		else
			{
			f_Verified = VERIFY_SUCCEEDING;

			f_Transaction->m_fresh = VERIFY_FAIL;
			}
		}
		
	if(f_initialVerified == VERIFY_FAIL)
		{
		f_Verified = VERIFY_FAIL;
		
		f_Transaction->m_fresh = VERIFY_FAIL;
		}
		
	return Cag->ag_cont_VerifyResult(f_Transaction, f_Verified);
}

std::string _Cag::ag_cont_VerifyResult(std::shared_ptr<CubeTransaction> f_Transaction, bool f_initialVerified)
{
	if(f_initialVerified == true)
		{  //stack tx hash
		bool f_Verified = true;

		if(f_Transaction->m_fresh == true)
			{
			f_Transaction->m_confirmation++;

			if(f_Transaction->m_confirmation == 6)
				{	  //final confirmation
				if(f_Verified == true) //verify process TXOUT
					{
					for(int f_Jet = 0; f_Jet < f_Transaction->m_txout.size(); f_Jet++)
						{		       //TXOUT
						if(f_Transaction->m_txin[0]->m_gnshareid != -2)
							{
							if(f_Transaction->m_txout[f_Jet]->m_owner.compare("feeowner") != 0) //not fee txout
								{
								float f_owner_value = ag_OwnerBalance(f_Transaction->m_txout[f_Jet]->m_owner);

								float f_finalBalance = f_owner_value + f_Transaction->m_txout[f_Jet]->m_txoutamt;

								ag_UpdateOwnerBalance(f_Transaction->m_txout[f_Jet]->m_owner, f_finalBalance);

								f_Transaction->m_txout[f_Jet]->m_owneramt = f_finalBalance;
								}
							else //-insert fee owner - YOU
								{
								f_Transaction->m_txout[f_Jet]->m_owner = g_Wallet->GetAdr();
							
								//send fee
								float f_owner_value = ag_OwnerBalance(f_Transaction->m_txout[f_Jet]->m_owner);

								float f_finalBalance = f_owner_value + ECN_TX_FEE;

								ag_UpdateOwnerBalance(f_Transaction->m_txout[f_Jet]->m_owner, f_finalBalance);
									
								f_Transaction->m_txout[f_Jet]->m_owneramt = f_finalBalance;

								f_Transaction->m_txout[f_Jet]->m_txoutamt = ECN_TX_FEE;

								g_Found_Msg = 26;
								g_Found_Text = "Congratulations Won 0.01000000 ECN From Verification";
								}
							}
						else
							{ //Change Transaction
							float f_owner_value = ag_OwnerBalance(f_Transaction->m_txout[f_Jet]->m_owner);

							float f_finalBalance = f_owner_value + f_Transaction->m_txout[f_Jet]->m_txoutamt;

							f_Transaction->m_txout[f_Jet]->m_owneramt = f_finalBalance;
							}
						}
					}
				}
			
			if(f_Verified == true)
				{
				f_Transaction->acHash();

				f_Transaction->acUpdateSync();

				return f_Transaction->m_Hash;
				//ECN::Transaction Verified pad
				}
			else
				{
				if(f_Transaction->m_fresh == false)
					{
#ifdef ECOIN_DEBUG_BREAKS_TX
					__debugbreak();
#endif //add debug message

					f_Transaction->m_status = -5;

					char* f_txfailvalue[1];
					char* f_txfailfield[1];
					char* f_txfailwhere[1];

					f_txfailvalue[0] = (char*)malloc(sizeof(char) * 1024);
					f_txfailfield[0] = (char*)malloc(sizeof(char) * 1024);
					f_txfailwhere[0] = (char*)malloc(sizeof(char) * 1024);

					sprintf(f_txfailfield[0], "status");
					sprintf(f_txfailvalue[0], "%i", -5);
					sprintf(f_txfailwhere[0], "id = %i", f_Transaction->m_txid);

					g_SafeL[0]->Update("transactions", (const char **)f_txfailfield, (const char **)f_txfailvalue, 1, (const char*)f_txfailwhere[0], false, false);

					free(f_txfailvalue[0]);
					free(f_txfailfield[0]);
					free(f_txfailwhere[0]);

					f_Transaction->m_Hash = "VERIFYFAIL";

					return f_Transaction->m_Hash;
					}
				else
					{ //unverified yet to be checked transaction hash of 1
					return f_Transaction->m_Hash;
					}
				}
			}
		else
			{
			return f_Transaction->m_Hash;
			}
		}
	else
		{
		if(f_Transaction->m_fresh == false)
			{
			f_Transaction->m_status = -5;

			char* f_txfailvalue[1];
			char* f_txfailfield[1];
			char* f_txfailwhere[1];

			f_txfailvalue[0] = (char*)malloc(sizeof(char) * 1024);
			f_txfailfield[0] = (char*)malloc(sizeof(char) * 1024);
			f_txfailwhere[0] = (char*)malloc(sizeof(char) * 1024);

			sprintf(f_txfailfield[0], "status");
			sprintf(f_txfailvalue[0], "%i", -5);
			sprintf(f_txfailwhere[0], "id = %i", f_Transaction->m_txid);

			g_SafeL[0]->Update("transactions", (const char **)f_txfailfield, (const char **)f_txfailvalue, 1, f_txfailwhere[0], false, false);

			free(f_txfailvalue[0]);
			free(f_txfailfield[0]);
			free(f_txfailwhere[0]);

			f_Transaction->m_Hash = "VERIFYFAIL";

			return f_Transaction->m_Hash;
			} 
		else
			{ //unverified yet to be checked transaction hash of 1
			return f_Transaction->m_Hash;
			}
		}

	return "0000000000000000000000000000000000000000000000000000000000000001";
}

char* Cube::ag_ClearChar(int f_Size)
{
	char* f_Char = new char[f_Size];

	for(int f_XY = 0; f_XY < f_Size; f_XY++)
		{
		f_Char[f_XY] = '\0';
		}

	return f_Char;
}

void Cube::CubeTransaction::acHash(void)
{
	std::string f_InputHash;
	f_InputHash.clear();

	for(int f_x = 0; f_x < m_txin.size(); f_x++)
		{
#if 0
		char* f_Char = ag_ClearChar(32);
		sprintf(f_Char, "%i", m_txin[f_x]->m_txid);
		f_InputHash += f_Char;
		delete f_Char;

		f_Char = ag_ClearChar(32);
		sprintf(f_Char, "%i", m_txin[f_x]->m_gnshareid);
		f_InputHash += f_Char;
		delete f_Char;
#endif

		if((m_txin[f_x]->m_vout.compare("Genesis Tracking") != 0) && (m_txin[f_x]->m_vout.compare("Genesis Coin") != 0))
			{
			char* f_Char = ag_ClearChar(128);
			sprintf(f_Char, "%f", m_txin[f_x]->m_amt);
			f_InputHash += f_Char;
			delete f_Char;
			}

		f_InputHash += m_txin[f_x]->m_vout;

#if 0
		f_InputHash += m_txin[f_x]->m_pubkey;
		f_InputHash += m_txin[f_x]->m_sigstr;
#endif
		}

	for(int f_y = 0; f_y < m_txout.size(); f_y++)
		{
		if(m_txout[f_y]->m_Flag == 1)
			{
			char* f_Char = ag_ClearChar(32);
			sprintf(f_Char, "%i", m_txout[f_y]->m_txid);//?
			f_InputHash += f_Char;
			delete f_Char;
			f_Char = ag_ClearChar(32);
			sprintf(f_Char, "%i", m_txout[f_y]->m_adrid);
			f_InputHash += f_Char;
			delete f_Char;
			f_InputHash += m_txout[f_y]->m_owner;

			if((m_txin[0]->m_vout.compare("Genesis Tracking") != 0) && (m_txin[0]->m_vout.compare("Genesis Coin") != 0))
				{
				f_Char = ag_ClearChar(64);
				sprintf(f_Char, "%f", m_txout[f_y]->m_txoutamt);
				f_InputHash += f_Char;
				delete f_Char;
				f_Char = ag_ClearChar(64);
				sprintf(f_Char, "%f", m_txout[f_y]->m_owneramt);
				f_InputHash += f_Char;
				delete f_Char;
				f_Char = ag_ClearChar(64);
				sprintf(f_Char, "%i", m_txout[f_y]->m_myelementcount);
				f_InputHash += f_Char;
				delete f_Char;
				}
			}
		}

	if((m_txin[0]->m_vout.compare("Genesis Tracking") != 0) && (m_txin[0]->m_vout.compare("Genesis Coin") != 0))
		{
		char* f_CharX = ag_ClearChar(64);
		sprintf(f_CharX, "%f", m_amt);
		f_InputHash += f_CharX;
		delete f_CharX;
		}

	char* f_Char = ag_ClearChar(32);
	sprintf(f_Char, "%f", m_fee);
	f_InputHash += f_Char;
	delete f_Char;

#if 0
	f_Char = ag_ClearChar(32);
	sprintf(f_Char, "%i", m_txid);
	f_InputHash += f_Char;
	delete f_Char;
	f_Char = ag_ClearChar(32);
	sprintf(f_Char, "%i", m_jobid); //hash? rehash?
	f_InputHash += f_Char;
	delete f_Char;
	f_Char = ag_ClearChar(32);
	sprintf(f_Char, "%i", m_confirmation); //hash? rehash?
	f_InputHash += f_Char;
	delete f_Char;
#endif

	f_InputHash += m_hdid;
	f_Char = ag_ClearChar(32);
	sprintf(f_Char, "%f", m_reward);
	f_InputHash += f_Char;
	delete f_Char;
	f_Char = ag_ClearChar(32);
	sprintf(f_Char, "%i", m_rewardid);
	f_InputHash += f_Char;
	delete f_Char;
	f_Char = ag_ClearChar(32);
	sprintf(f_Char, "%i", m_type);
	f_InputHash += f_Char;
	delete f_Char;
	f_Char = ag_ClearChar(32);
	sprintf(f_Char, "%i", m_blocktype);
	f_InputHash += f_Char;
	delete f_Char;

#if 0
	f_Char = ag_ClearChar(32); //status new addition
	sprintf(f_Char, "%i", m_status); //hash? rehash?
	f_InputHash += f_Char;
	delete f_Char;
#endif

	g_hasha.init(); //reset hasher state
	g_hasha.process(f_InputHash.begin(), f_InputHash.end());
	g_hasha.finish();
	picosha2::get_hash_hex_string(g_hasha, m_Hash);

	//saved to transaction->m_Hash
}

void Cube::CubeTransaction::acUpdateSync(void)
{
	char* g_syncTXvalue[7];
	char* g_syncTXfield[7];
	char* g_syncTXwhere[1];

	for(int f_s = 0; f_s < 7; f_s++)
		{
		g_syncTXvalue[f_s] = (char*)malloc(sizeof(char) * 256);
		g_syncTXfield[f_s] = (char*)malloc(sizeof(char) * 256);
		}

	g_syncTXwhere[0] = (char*)malloc(sizeof(char) * 256);

	sprintf(g_syncTXfield[0], "shareid");
	sprintf(g_syncTXfield[1], "gnshareid");
	sprintf(g_syncTXfield[2], "jobid");
	sprintf(g_syncTXfield[3], "hash");
	sprintf(g_syncTXfield[4], "hashnib");
	sprintf(g_syncTXfield[5], "amt");
	sprintf(g_syncTXfield[6], "confirmation");

	sprintf(g_syncTXvalue[0], "%i", m_shareid);
	sprintf(g_syncTXvalue[1], "%i", m_txin[0]->m_gnshareid);
	sprintf(g_syncTXvalue[2], "%i", m_jobid);
	sprintf(g_syncTXvalue[3], "%s", m_Hash.c_str());
	sprintf(g_syncTXvalue[4], "%s", m_Hashnib.c_str());
	sprintf(g_syncTXvalue[5], "%f", m_amt);
	sprintf(g_syncTXvalue[6], "%i", m_confirmation);

	sprintf(g_syncTXwhere[0], "id = %i", m_txid);

	g_SafeL[0]->Update("transactions", (const char **)g_syncTXfield, (const char **)g_syncTXvalue, 7, g_syncTXwhere[0], false, false);

	for(int f_s = 0; f_s < 7; f_s++)
		{
		free(g_syncTXvalue[f_s]);
		free(g_syncTXfield[f_s]);
		}

	free(g_syncTXwhere[0]);

	for(int f_Int = 0; f_Int < m_txout.size(); f_Int++)
		{
		if(m_txout[f_Int]->m_txoutid > 0)
			{
			char* g_txoutsyncwhere[1];

			g_txoutsyncwhere[0] = (char*)malloc(sizeof(char) * 256);

			char* g_txoutsyncvalue[6];

			for(int f_s2 = 0; f_s2 < 6; f_s2++)
				{
				g_txoutsyncvalue[f_s2] = (char*)malloc(sizeof(char) * 256);
				}

			m_txout[f_Int]->m_txid = m_txid;

			sprintf((char*)(g_txoutsyncvalue[0]), "%i", m_txout[f_Int]->m_txid);
			sprintf((char*)(g_txoutsyncvalue[1]), "%i", m_txout[f_Int]->m_adrid);
			sprintf((char*)(g_txoutsyncvalue[2]), "%s", m_txout[f_Int]->m_owner.c_str());
			sprintf((char*)(g_txoutsyncvalue[3]), "%f", m_txout[f_Int]->m_txoutamt);
			sprintf((char*)(g_txoutsyncvalue[4]), "%f", m_txout[f_Int]->m_owneramt);
			sprintf((char*)(g_txoutsyncvalue[5]), "%i", m_txout[f_Int]->m_myelementcount);

			sprintf(g_txoutsyncwhere[0], "id = %i", m_txout[f_Int]->m_txoutid);

			g_SafeL[0]->Update("txout", (const char **)g_txoutsyncfield, (const char **)g_txoutsyncvalue, 6, g_txoutsyncwhere[0], false, false);

			for(int f_s2 = 0; f_s2 < 6; f_s2++)
				{
				free(g_txoutsyncvalue[f_s2]);
				}

			free(g_txoutsyncwhere[0]);
			}
		else
			{
			char* g_txoutsyncvalue[6];

			for(int f_s2 = 0; f_s2 < 6; f_s2++)
				{
				g_txoutsyncvalue[f_s2] = (char*)malloc(sizeof(char) * 256);
				}

			m_txout[f_Int]->m_txid = m_txid;

			sprintf(g_txoutsyncvalue[0], "%i", m_txout[f_Int]->m_txid);
			sprintf(g_txoutsyncvalue[1], "%i", m_txout[f_Int]->m_adrid);
			sprintf(g_txoutsyncvalue[2], "%s", m_txout[f_Int]->m_owner.c_str());
			sprintf(g_txoutsyncvalue[3], "%f", m_txout[f_Int]->m_txoutamt);
			sprintf(g_txoutsyncvalue[4], "%f", m_txout[f_Int]->m_owneramt);
			sprintf(g_txoutsyncvalue[5], "%i", m_txout[f_Int]->m_myelementcount);

			m_txout[f_Int]->m_txoutid = g_SafeL[0]->Insert("txout", (const char **)g_txoutsyncfield, (const char **)g_txoutsyncvalue, 6, false, false);

			for(int f_s2 = 0; f_s2 < 6; f_s2++)
				{
				free(g_txoutsyncvalue[f_s2]);
				}
			}
		}
}

void Cube::CubeTransaction::acSynchronize(void)
{
	char* g_syncvalue[17];

	for(int f_s = 0; f_s < 17; f_s++)
		{
		g_syncvalue[f_s] = (char*)malloc(sizeof(char) * 256);
		}

	sprintf(g_syncvalue[0], "%i", 1);
	sprintf(g_syncvalue[1], "%i", 1);// f_Address.c_str());
	sprintf(g_syncvalue[2], "%i", 0);
	sprintf(g_syncvalue[3], "%s", m_hdid.c_str());
	sprintf(g_syncvalue[4], "%i", m_shareid);
	sprintf(g_syncvalue[5], "%i", m_txin[0]->m_gnshareid);
	sprintf(g_syncvalue[6], "%i", m_jobid);
	sprintf(g_syncvalue[7], "%i", m_rewardid);
	sprintf(g_syncvalue[8], "%i", m_blocktype);
	sprintf(g_syncvalue[9], "%s", m_Hash.c_str());
	sprintf(g_syncvalue[10], "%s", "G");
	sprintf(g_syncvalue[11], "%f", m_amt);
	sprintf(g_syncvalue[12], "%f", m_fee);
	sprintf(g_syncvalue[13], "%f", m_reward);
	sprintf(g_syncvalue[14], "%s", m_txout[0]->m_owner.c_str());
	sprintf(g_syncvalue[15], "%i", m_blockid);
	sprintf(g_syncvalue[16], "%i", m_type);

	char* syncquery = ag_ClearChar(512);
	sprintf(syncquery, "SELECT id FROM transactions WHERE hash = '%s'", m_Hash.c_str());
	g_SafeL[0]->acSelectCommand(syncquery, false, false);
	delete syncquery;

	int f_SyncLCount = 0;
		
	if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
		{
		f_SyncLCount = 0;
		}
	else
		{
		f_SyncLCount = g_Schedular[0]->acEntrySize();
		}

	//ECN::Stat::: f_SyncLCount
	if(f_SyncLCount == 0)
		{	//Unique Transaction Made ID = m_txid - txinsyncvalue
		m_txid = g_SafeL[0]->Insert("transactions", (const char **)g_syncfield, (const char **)g_syncvalue, 17, false, false);

		for(int f_s = 0; f_s < 16; f_s++)
			{
			free(g_syncvalue[f_s]);
			}

		char* g_txinsyncvalue[6];

		for(int f_s1 = 0; f_s1 < 6; f_s1++)
			{
			g_txinsyncvalue[f_s1] = (char*)malloc(sizeof(char) * 256);
			}

		sprintf(g_txinsyncvalue[0], "%i", m_txid);
		sprintf(g_txinsyncvalue[1], "%s", m_txin[0]->m_vout.c_str());
		sprintf(g_txinsyncvalue[2], "%s", m_txin[0]->m_pubkey.c_str());
		sprintf(g_txinsyncvalue[3], "%s", m_txin[0]->m_sigstr.c_str());
		sprintf(g_txinsyncvalue[4], "%f", m_amt);
		sprintf(g_txinsyncvalue[5], "%i", m_txin[0]->m_gnshareid);

		m_txin[0]->m_txinid = g_SafeL[0]->Insert("txin", (const char **)g_txinsyncfield, (const char **)g_txinsyncvalue, 6, false, false);

		for(int f_s1 = 0; f_s1 < 6; f_s1++)
			{
			free(g_txinsyncvalue[f_s1]);
			}

		for(int f_Int = 0; f_Int < m_txout.size(); f_Int++)
			{
			char* g_txoutsyncvalue[6];

			for(int f_s2 = 0; f_s2 < 6; f_s2++)
				{
				g_txoutsyncvalue[f_s2] = (char*)malloc(sizeof(char) * 256);
				}

			sprintf(g_txoutsyncvalue[0], "%i", m_txid);
			sprintf(g_txoutsyncvalue[1], "%i", m_txout[f_Int]->m_adrid);
			sprintf(g_txoutsyncvalue[2], "%s", m_txout[f_Int]->m_owner.c_str());
			sprintf(g_txoutsyncvalue[3], "%f", m_txout[f_Int]->m_txoutamt);
			sprintf(g_txoutsyncvalue[4], "%f", m_txout[f_Int]->m_owneramt);
			sprintf(g_txoutsyncvalue[5], "%i", m_txout[f_Int]->m_myelementcount);

			m_txout[f_Int]->m_txoutid = g_SafeL[0]->Insert("txout", (const char **)g_txoutsyncfield, (const char **)g_txoutsyncvalue, 6, false, false);

			for(int f_s2 = 0; f_s2 < 6; f_s2++)
				{
				free(g_txoutsyncvalue[f_s2]);
				}
			}
		}
}

int _Cag::ag_GenerateTransaction(std::string f_A, std::string f_B, float f_amt, std::shared_ptr<CubeTransaction> f_tx)
	{
	std::string f_ref_CurrentPath = "ag_GenerateTransaction";

		///////////////
	   // Research
	  // Entropy
	 // Key
	// Privacy
	std::shared_ptr<CKey> key = nullptr;

	bool f_Found = false;
	int f_Index = 0;
	for(int f_Helly = 0; f_Helly < g_Wallet->m_vec_Key.size(); f_Helly++)
		{
		if(g_Wallet->m_vec_Key[f_Helly]->m_owner.size() >= 27)
			{
			if(g_Wallet->m_vec_Key[f_Helly]->m_owner.compare(f_A) == 0)
				{
				f_Found = true;
				f_Index = f_Helly;
				}
			}
		}

	if(f_Found)
		{
		key = g_Wallet->m_vec_Key[f_Index];
		}

	if(key) ///////////////////////////////
		{  // OK pass key acquisition   //
		  // defaults to single in/out //
		 ///////////////////////////////
		// Prev Transaction          //
		std::shared_ptr<CubeTransaction> f_prvTX = ag_get_TXfromvout(f_A.c_str());

		if(!f_prvTX)
			{
			return 2;
			}
		else
			{
			if(!f_prvTX->isValid())
				{
				return 2;
				}
			}

		ag_StatusLive(f_ref_CurrentPath, "f_tx");
		f_tx = std::make_shared_reflect<CubeTransaction>(f_A, f_B, f_amt);

		f_tx->m_reward = g_Wallet->m_Reward;
		f_tx->m_rewardid = g_Wallet->m_RewardID;

		ag_StatusLive(f_ref_CurrentPath, "f_txout_fee");
		std::shared_ptr<CubeTXOUT> f_txout_fee = std::make_shared_reflect<CubeTXOUT>();

		f_txout_fee->m_adrid = -2;
		f_txout_fee->m_owner = "feeowner";
		f_txout_fee->m_txoutamt = ECN_TX_FEE;
		f_txout_fee->m_owneramt = 0.0f;
		f_txout_fee->m_myelementcount = 0;

		f_tx->m_txout.push_back(f_txout_fee);

		//set fee
		f_tx->m_fee = ECN_TX_FEE;

#pragma message("add conditional fail on address not known")
		if(1)
			{
			float f_owneramt = ag_OwnerBalance(f_prvTX->m_txout[0]->m_owner);

			if(f_amt > f_owneramt)
				{
				//ECN::transaction failed not enough ecoin in prvout

				return 3;
				}
			else
				{	// Eviscerate the coin
				for(int f_Jet = 0; f_Jet < f_tx->m_txin.size(); f_Jet++)
					{
					char* f_balupvalue[1];
					char* f_balupfield[1];
					char* f_balupwhere[1];

					f_balupvalue[0] = (char*)malloc(sizeof(char) * 1024);
					f_balupfield[0] = (char*)malloc(sizeof(char) * 1024);
					f_balupwhere[0] = (char*)malloc(sizeof(char) * 1024);

					float f_OwnerBalance = ag_OwnerBalance(f_tx->m_txin[0]->m_vout);
					float f_finalBalance = f_OwnerBalance - f_amt;

					sprintf(f_balupfield[0], "amt");
					sprintf(f_balupvalue[0], "%f", f_finalBalance);
					sprintf(f_balupwhere[0], "owner = '%s'", f_tx->m_txin[0]->m_vout.c_str());

					g_SafeL[0]->Update("address", (const char **)f_balupfield, (const char **)f_balupvalue, 1, f_balupwhere[0], false, false);

					free(f_balupvalue[0]);
					free(f_balupfield[0]);
					free(f_balupwhere[0]);
					}

				if(f_amt != f_owneramt)
					{
					ag_StatusLive(f_ref_CurrentPath, "f_txout");
					std::shared_ptr<CubeTXOUT> f_txout = std::make_shared_reflect<CubeTXOUT>();

					f_txout->m_owner = g_Wallet->GetNextChangeKey()->m_owner;
					f_txout->m_adrid = 3;

					float f_change_value = ag_OwnerBalance(f_txout->m_owner);

					f_change_value += f_owneramt - f_amt;
					
					f_txout->m_txoutamt = f_owneramt - f_amt;
					f_txout->m_owneramt = f_change_value;
					f_tx->m_txout.push_back(f_txout);

					ag_StatusLive(f_ref_CurrentPath, "f_changetoadrtx");
					std::shared_ptr<CubeTransaction> f_changetoadrtx = std::make_shared_reflect<CubeTransaction>(f_txout->m_owner, f_A, f_change_value);

					f_changetoadrtx->m_txin[0]->m_gnshareid = -2;

					f_changetoadrtx->acHash();

					unsigned char k[32];

					ag_hex2bin(k, f_changetoadrtx->m_Hash.c_str(), 64);

					uint256& f_256uint = reinterpret_cast<uint256&>(k);

					bool f_res = key->Sign(f_256uint, f_changetoadrtx->m_txin[0]->m_sig);

					char f_k[142];

					ag_bin2hex((char*)f_k, f_changetoadrtx->m_txin[0]->m_sig, 71);

					f_changetoadrtx->m_txin[0]->m_sigstr.clear();

					for(int j2o = 0; j2o < 142; j2o++)
						{
						f_changetoadrtx->m_txin[0]->m_sigstr.push_back(f_k[j2o]);
						}

					f_changetoadrtx->m_jobid = g_JobID;

					f_changetoadrtx->m_blockid = 0;

					f_changetoadrtx->acSynchronize();
					
					  //////////////////////////////////////////////////////////////////////////////
					 //ECN::successfully completed synchronisation of return change transaction//
					////////////////////////////////////////////////////////////////////////////
					}
				}
			}

		f_tx->acHash();

		unsigned char k[32];

		ag_hex2bin(k, f_tx->m_Hash.c_str(), 64);

		uint256& f_256uint = reinterpret_cast<uint256&>(k);

		bool f_res = key->Sign(f_256uint, f_tx->m_txin[0]->m_sig);

		if(f_res == false)
			{
			//ECN::Failed txvout sign.

#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif
			}

		char f_k[142];

		ag_bin2hex((char*)f_k, f_tx->m_txin[0]->m_sig, 71);

		f_tx->m_txin[0]->m_sigstr.clear();

		for(int j2o = 0; j2o < 142; j2o++)
			{
			f_tx->m_txin[0]->m_sigstr.push_back(f_k[j2o]);
			}

		f_tx->m_jobid = g_JobID;

		f_tx->m_blockid = 0;

		f_tx->acSynchronize();

		  //////////////////////////////////////////////////////////////////////////
		 //ECN::successfully completed synchronisation of normal live transaction//
		//////////////////////////////////////////////////////////////////////////
		return 1;
		}
	else
		{ ////////////////////////////////////////////////////////////////////////
		 //ECN::transaction failed finding the wallet key for requested address//
		////////////////////////////////////////////////////////////////////////
		return 2;
		}

	  ////////////////////////////////////////
	 // ECN::transaction generation failed //
	////////////////////////////////////////

	return 0;
}

bool _Cag::ag_addGenesisTracking(int f_gnid, int f_blocktype, int f_elementcount)
{
	std::string f_ref_CurrentPath = "ag_addGenesisTracking";

	  /////////////////////////
	 // Add onto Next JobID //
	/////////////////////////
	int f_jobid = g_JobID + 1;

	//~hardware identification
	auto f_Info = winrt::Windows::Security::ExchangeActiveSyncProvisioning::EasClientDeviceInformation();
	char* f_CharX = ag_ClearChar(256);
	::sprintf(f_CharX, "%u%u", f_Info.Id().Data1, f_Info.Id().Data2);
	std::string Id = f_CharX;
	delete f_CharX;

	char* hdquery = ag_ClearChar(5000);

	if(f_blocktype >= ecoin_BlockType::ecoin_Block_Target_SCP)
		{
		if(f_gnid > 0)
			{
			sprintf(hdquery, "SELECT IFNULL(MAX(txoutlist.id), 0) FROM txout AS txoutlist INNER JOIN transactions AS txlist ON ((txlist.jobid = %i) AND ((txlist.gnshareid = %i) OR (txlist.shareid = %i)) AND (txoutlist.owner = '%s') AND (txlist.id = txoutlist.transactionid) AND (txlist.amt = -1) AND (txlist.hdid = '%s'))", f_jobid, f_gnid, f_gnid, g_Wallet->GetAdr().c_str(), Id.c_str());
			}
		else
			{
#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif //add debug message
			}
		}
	else
		{
		sprintf(hdquery, "SELECT IFNULL(MAX(txoutlist.id), 0) FROM txout AS txoutlist INNER JOIN transactions AS txlist ON ((txlist.jobid = %i) AND (txoutlist.owner = '%s') AND (txlist.id = txoutlist.transactionid) AND (txlist.amt = -1) AND (txlist.hdid = '%s'))", f_jobid, g_Wallet->GetAdr().c_str(), Id.c_str());
		}

	g_SafeL[0]->acSelectCommand(hdquery, false, false);

	delete hdquery;

	int f_hdLCount = 0;
		
	if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
		{
		f_hdLCount = 0;
		}
	else
		{
		f_hdLCount = g_Schedular[0]->acEntrySize();
		}

	//ECN::Stat::: f_hdLCount
	if(f_hdLCount == 0)
		{
		ag_StatusLive(f_ref_CurrentPath, "f_tx");
		std::shared_ptr<CubeTransaction> f_tx = std::make_shared_reflect<CubeTransaction>("Genesis Tracking", g_Wallet->GetAdr(), -1.0f);

		ag_Freshanon<int>(g_Wallet->m_vec_blockid, g_Wallet->m_current_IDX, -1);

		f_tx->m_shareid = f_gnid;
		f_tx->m_txin[0]->m_gnshareid = f_gnid;
		f_tx->m_jobid = f_jobid;
		f_tx->m_hdid = Id;
		f_tx->m_fee = 0.0f;
		f_tx->m_blocktype = f_blocktype;
		f_tx->m_txout[0]->m_myelementcount = f_elementcount * g_CountLM;
		f_tx->m_rewardid = g_Wallet->m_RewardID;
		f_tx->m_reward = g_Wallet->m_Reward;
		f_tx->m_blockid = g_Wallet->m_vec_blockid[g_Wallet->m_current_IDX];

		f_tx->acHash();

		f_tx->acSynchronize();

		return true;
		}
	else //else update existing
		{
		std::string f_Resultance = "";
		int f_txoutID = atoi(g_Schedular[0]->acEntry(0)[0].c_str());

		char* f_CharQuery = ag_ClearChar(512);
		::sprintf(f_CharQuery, "UPDATE txout SET myelementcount = myelementcount + %i WHERE id = %i", f_elementcount * g_CountLM, f_txoutID);
		f_Resultance += f_CharQuery;
		delete f_CharQuery;

		int f_Resp = g_SafeL[0]->acCommand(f_Resultance.c_str(), 0, false, true);

		return true;
		}

	return false;
}

bool _Cag::ag_makeGenesisCoin(void)
{
	std::string f_ref_CurrentPath = "ag_makeGenesisCoin";

	ag_StatusLive(f_ref_CurrentPath, "f_tx");
	std::shared_ptr<CubeTransaction> f_tx = std::make_shared_reflect<CubeTransaction>("Genesis Coin", g_Wallet->GetAdr(), 1.0f);

	f_tx->m_txin[0]->m_gnshareid = -5;

	f_tx->m_jobid = g_JobID + 1;

	f_tx->m_hdid = "unused";

	f_tx->m_rewardid = g_Wallet->m_RewardID;

	f_tx->m_reward = g_Wallet->m_Reward;

	f_tx->m_blockid = g_Wallet->m_vec_blockid[g_Wallet->m_current_IDX];

	f_tx->acHash();

	f_tx->acSynchronize();

	g_Found_Msg = 28;
	g_Found_Text = "Congratulations Won 1.00000000 ECN Genesis Coin";

	return true;
}

CubeHESH::CubeHESH(std::string f_Buffer, uint* f_Chk)
{
	acClear();

	m_Timestamp = acBufreadValueUL((char *)f_Buffer.c_str(), f_Chk);

	m_ID = acBufreadValueInteger((char *)f_Buffer.c_str(), f_Chk);

	m_RotateX = acBufreadValueFloat((char *)f_Buffer.c_str(), f_Chk);

	m_RotateY = acBufreadValueFloat((char *)f_Buffer.c_str(), f_Chk);

	m_RotateZ = acBufreadValueFloat((char *)f_Buffer.c_str(), f_Chk);

	int f_AdSize = acBufreadValueInteger((char *)f_Buffer.c_str(), f_Chk);

	for(int f_I = 0; f_I < f_AdSize; f_I++)
		{
		int f_Ad = acBufreadValueInteger((char *)f_Buffer.c_str(), f_Chk);
		m_adIndex.push_back(f_Ad);
		}

	int f_BiSize = acBufreadValueInteger((char *)f_Buffer.c_str(), f_Chk);

	for(int f_I = 0; f_I < f_BiSize; f_I++)
		{
		std::shared_ptr<CubeBicycle> f_CB = std::make_shared<CubeBicycle>(f_Buffer, f_Chk);

		vec_Bicycle.push_back(f_CB);
		}

	m_ValueBank = acBufreadValueDouble((char *)f_Buffer.c_str(), f_Chk);
}

void CubeHESH::acSerialise(std::string* f_String)
{
	acBufwriteValueUL(f_String, m_Timestamp);

	acBufwriteValueInteger(f_String, m_ID);

	acBufwriteValueFloat(f_String, m_RotateX);

	acBufwriteValueFloat(f_String, m_RotateY);

	acBufwriteValueFloat(f_String, m_RotateZ);

	acBufwriteValueInteger(f_String, m_adIndex.size());

	for(int f_I = 0; f_I < m_adIndex.size(); f_I++)
		{
		acBufwriteValueInteger(f_String, m_adIndex[f_I]);
		}

	acBufwriteValueInteger(f_String, vec_Bicycle.size());

	for(int f_I = 0; f_I < vec_Bicycle.size(); f_I++)
		{
		vec_Bicycle[f_I]->acSerialise(f_String);
		}

	acBufwriteValueDouble(f_String, g_WALLETBANK);

	char f_Chr = '\n';

	*(f_String) += f_Chr;
}

void CubeBicycle::acSerialise(std::string* f_String)
{
	acBufwriteValueInteger(f_String, vec_Vertex.size());

	for(int f_I = 0; f_I < vec_Vertex.size(); f_I++)
		{
		acBufwriteValueFloat(f_String, vec_Vertex[f_I]->m_X);

		acBufwriteValueFloat(f_String, vec_Vertex[f_I]->m_Y);

		acBufwriteValueFloat(f_String, vec_Vertex[f_I]->m_Z);
		}

	acBufwriteValueInteger(f_String, vec_Color.size());

	for(int f_C = 0; f_C < vec_Color.size(); f_C++)
		{
		acBufwriteValueFloat(f_String, vec_Color[f_C]->m_X);

		acBufwriteValueFloat(f_String, vec_Color[f_C]->m_Y);

		acBufwriteValueFloat(f_String, vec_Color[f_C]->m_Z);
		}
}

CubeBicycle::CubeBicycle(std::string f_Buffer, uint* f_Chk) 
{
	acClear();

	int f_VertSize = acBufreadValueInteger((char *)f_Buffer.c_str(), f_Chk);

	for(int f_I = 0; f_I < f_VertSize; f_I++)
		{
		std::shared_ptr<Cube::BiVector> f_Vector = std::make_shared<Cube::BiVector>(acBufreadValueFloat((char *)f_Buffer.c_str(), f_Chk), acBufreadValueFloat((char *)f_Buffer.c_str(), f_Chk), acBufreadValueFloat((char *)f_Buffer.c_str(), f_Chk));

		vec_Vertex.push_back(f_Vector);
		}

	int f_ColorSize = acBufreadValueInteger((char *)f_Buffer.c_str(), f_Chk);

	for(int f_C = 0; f_C < f_ColorSize; f_C++)
		{
		std::shared_ptr<Cube::BiVector> f_Color = std::make_shared<Cube::BiVector>(acBufreadValueFloat((char *)f_Buffer.c_str(), f_Chk), acBufreadValueFloat((char *)f_Buffer.c_str(), f_Chk), acBufreadValueFloat((char *)f_Buffer.c_str(), f_Chk));

		vec_Color.push_back(f_Color);
		}
}

void CubeHESH::acSaveCloud(std::string f_Name, int f_ID)
{
	std::string f_NameString = "LIMESH#" + f_Name + "#ICS Library ID Hesh";

	std::string f_ShareLedgerPrimer = acHashMap(f_NameString, f_ID);

	char* g_sharevalue[25];

	for(int f_Count = 0; f_Count < 25; f_Count++)
		{
		g_sharevalue[f_Count] = (char*)malloc(sizeof(char) * 1024);
		}

	::sprintf(g_sharevalue[0], "%i", 0);
	::sprintf(g_sharevalue[1], "%f", 0.0f);
	::sprintf(g_sharevalue[2], "%i", 1);
	::sprintf(g_sharevalue[3], "%i", 3);
	::sprintf(g_sharevalue[4], "%i", 0);
	::sprintf(g_sharevalue[5], "%i", 0);
	::sprintf(g_sharevalue[6], "%i", 0);
	::sprintf(g_sharevalue[7], "%i", 0);
	::sprintf(g_sharevalue[8], "%s", f_NameString.c_str());
	::sprintf(g_sharevalue[9], "%f", 0.0f);
	::sprintf(g_sharevalue[10], "%f", 0.0f);
	::sprintf(g_sharevalue[11], "%f", 0.0f);
	::sprintf(g_sharevalue[12], "%s", f_ShareLedgerPrimer.c_str());
	::sprintf(g_sharevalue[13], "%s", f_ShareLedgerPrimer.c_str());
	::sprintf(g_sharevalue[14], "%s", g_Wallet->GetAdr().c_str());
	::sprintf(g_sharevalue[15], "%f", m_bckred);
	::sprintf(g_sharevalue[16], "%f", m_bckgreen);
	::sprintf(g_sharevalue[17], "%f", m_bckblue);
	::sprintf(g_sharevalue[18], "%i", f_ID);
	::sprintf(g_sharevalue[19], "%f", 0.0f);
	::sprintf(g_sharevalue[20], "%f", 0.0f);
	::sprintf(g_sharevalue[21], "%f", 0.0f);
	::sprintf(g_sharevalue[22], "%f", 0.0f);
	::sprintf(g_sharevalue[23], "%f", 0.0f);
	::sprintf(g_sharevalue[24], "%i", ecoin_BlockType::ecoin_Block_Default);

	int f_ShareID = g_SafeL[0]->Insert("share", (const char**)g_sharefield, (const char**)g_sharevalue, 25, 2, false);

	for(int f_Count = 0; f_Count < 25; f_Count++)
		{
		free(g_sharevalue[f_Count]);
		}

	for(int f_XY = 0; f_XY < vec_Bicycle.size(); f_XY++)
		{
		std::shared_ptr<CubeBicycle> f_Bike = vec_Bicycle[f_XY];

		char* g_cubevalue[55];

		for(int f_Count = 0; f_Count < 55; f_Count++)
			{
			g_cubevalue[f_Count] = (char*)malloc(sizeof(char) * 100);
			}

		int f_ForSize = f_Bike->vec_Vertex.size();

		for(int f_Int2 = 0; f_Int2 < f_ForSize; f_Int2++)
			{
			::sprintf(g_cubevalue[f_Int2 * 3], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_X);
			::sprintf(g_cubevalue[(f_Int2 * 3) + 1], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Y);
			::sprintf(g_cubevalue[(f_Int2 * 3) + 2], "%.8f", f_Bike->vec_Vertex[f_Int2]->m_Z);
			::sprintf(g_cubevalue[(24 + (f_Int2 * 3))], "%.8f", f_Bike->vec_Color[f_Int2]->m_X);
			::sprintf(g_cubevalue[(24 + (f_Int2 * 3)) + 1], "%.8f", f_Bike->vec_Color[f_Int2]->m_Y);
			::sprintf(g_cubevalue[(24 + (f_Int2 * 3)) + 2], "%.8f", f_Bike->vec_Color[f_Int2]->m_Z);
			}

		for(int f_Int3 = f_ForSize; f_Int3 < 8; f_Int3++)
			{
			::sprintf(g_cubevalue[f_Int3 * 3], "%.8f", -15.0f);
			::sprintf(g_cubevalue[(f_Int3 * 3) + 1], "%.8f", -15.0f);
			::sprintf(g_cubevalue[(f_Int3 * 3) + 2], "%.8f", -15.0f);
			::sprintf(g_cubevalue[(24 + (f_Int3 * 3))], "%.8f", 0.8f);
			::sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 1], "%.8f", 0.8f);
			::sprintf(g_cubevalue[(24 + (f_Int3 * 3)) + 2], "%.8f", 0.8f);
			}

		::sprintf(g_cubevalue[48], "%i", ECOIN_DEFAULT_BLOCKID);
		::sprintf(g_cubevalue[49], "%i", f_ShareID);
		::sprintf(g_cubevalue[50], "%i", g_JobID);
		::sprintf(g_cubevalue[51], "%i", f_XY);
		::sprintf(g_cubevalue[52], "%i", g_CountLM);	// FIXME ADD L-TARGETID
		::sprintf(g_cubevalue[53], "%s", "CubePiece");
		::sprintf(g_cubevalue[54], "%f", 100.0f);

		int f_adIndex = g_SafeL[0]->Insert("cube", (const char **)g_cubefield, (const char **)g_cubevalue, 55, 2, false);

		for(int f_Count = 0; f_Count < 55; f_Count++)
			{
			free(g_cubevalue[f_Count]);
			}
		}
}

#if 0
void CubeBicycle::acRefresh(void)
	{
	if (m_Refresh)
		{
		m_Refresh = false;

		GLfloat vertexPositions[] =
			{
			vec_Vertex[0].m_X, vec_Vertex[0].m_Y, vec_Vertex[0].m_Z, vec_Vertex[1].m_X, vec_Vertex[1].m_Y, vec_Vertex[1].m_Z, vec_Vertex[2].m_X, vec_Vertex[2].m_Y, vec_Vertex[2].m_Z,
			vec_Vertex[1].m_X, vec_Vertex[1].m_Y, vec_Vertex[1].m_Z, vec_Vertex[3].m_X, vec_Vertex[3].m_Y, vec_Vertex[3].m_Z, vec_Vertex[2].m_X, vec_Vertex[2].m_Y, vec_Vertex[2].m_Z,
			vec_Vertex[4].m_X, vec_Vertex[4].m_Y, vec_Vertex[4].m_Z, vec_Vertex[6].m_X, vec_Vertex[6].m_Y, vec_Vertex[6].m_Z, vec_Vertex[5].m_X, vec_Vertex[5].m_Y, vec_Vertex[5].m_Z,
			vec_Vertex[5].m_X, vec_Vertex[5].m_Y, vec_Vertex[5].m_Z, vec_Vertex[6].m_X, vec_Vertex[6].m_Y, vec_Vertex[6].m_Z, vec_Vertex[7].m_X, vec_Vertex[7].m_Y, vec_Vertex[7].m_Z,
			vec_Vertex[0].m_X, vec_Vertex[0].m_Y, vec_Vertex[0].m_Z, vec_Vertex[5].m_X, vec_Vertex[5].m_Y, vec_Vertex[5].m_Z, vec_Vertex[1].m_X, vec_Vertex[1].m_Y, vec_Vertex[1].m_Z,
			vec_Vertex[0].m_X, vec_Vertex[0].m_Y, vec_Vertex[0].m_Z, vec_Vertex[4].m_X, vec_Vertex[4].m_Y, vec_Vertex[4].m_Z, vec_Vertex[5].m_X, vec_Vertex[5].m_Y, vec_Vertex[5].m_Z,
			vec_Vertex[2].m_X, vec_Vertex[2].m_Y, vec_Vertex[2].m_Z, vec_Vertex[7].m_X, vec_Vertex[7].m_Y, vec_Vertex[7].m_Z, vec_Vertex[6].m_X, vec_Vertex[6].m_Y, vec_Vertex[6].m_Z,
			vec_Vertex[2].m_X, vec_Vertex[2].m_Y, vec_Vertex[2].m_Z, vec_Vertex[3].m_X, vec_Vertex[3].m_Y, vec_Vertex[3].m_Z, vec_Vertex[7].m_X, vec_Vertex[7].m_Y, vec_Vertex[7].m_Z,
			vec_Vertex[0].m_X, vec_Vertex[0].m_Y, vec_Vertex[0].m_Z, vec_Vertex[6].m_X, vec_Vertex[6].m_Y, vec_Vertex[6].m_Z, vec_Vertex[4].m_X, vec_Vertex[4].m_Y, vec_Vertex[4].m_Z,
			vec_Vertex[0].m_X, vec_Vertex[0].m_Y, vec_Vertex[0].m_Z, vec_Vertex[2].m_X, vec_Vertex[2].m_Y, vec_Vertex[2].m_Z, vec_Vertex[6].m_X, vec_Vertex[6].m_Y, vec_Vertex[6].m_Z,
			vec_Vertex[1].m_X, vec_Vertex[1].m_Y, vec_Vertex[1].m_Z, vec_Vertex[7].m_X, vec_Vertex[7].m_Y, vec_Vertex[7].m_Z, vec_Vertex[3].m_X, vec_Vertex[3].m_Y, vec_Vertex[3].m_Z,
			vec_Vertex[1].m_X, vec_Vertex[1].m_Y, vec_Vertex[1].m_Z, vec_Vertex[5].m_X, vec_Vertex[5].m_Y, vec_Vertex[5].m_Z, vec_Vertex[7].m_X, vec_Vertex[7].m_Y, vec_Vertex[7].m_Z
			};

		glGenBuffers(1, &mVertexPositionBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

		GLfloat vertexColors[] =
			{
			vec_Color[0].m_X, vec_Color[0].m_Y, vec_Color[0].m_Z, vec_Color[1].m_X, vec_Color[1].m_Y, vec_Color[1].m_Z, vec_Color[2].m_X, vec_Color[2].m_Y, vec_Color[2].m_Z,
			vec_Color[1].m_X, vec_Color[1].m_Y, vec_Color[1].m_Z, vec_Color[3].m_X, vec_Color[3].m_Y, vec_Color[3].m_Z, vec_Color[2].m_X, vec_Color[2].m_Y, vec_Color[2].m_Z,
			vec_Color[4].m_X, vec_Color[4].m_Y, vec_Color[4].m_Z, vec_Color[6].m_X, vec_Color[6].m_Y, vec_Color[6].m_Z, vec_Color[5].m_X, vec_Color[5].m_Y, vec_Color[5].m_Z,
			vec_Color[5].m_X, vec_Color[5].m_Y, vec_Color[5].m_Z, vec_Color[6].m_X, vec_Color[6].m_Y, vec_Color[6].m_Z, vec_Color[7].m_X, vec_Color[7].m_Y, vec_Color[7].m_Z,
			vec_Color[0].m_X, vec_Color[0].m_Y, vec_Color[0].m_Z, vec_Color[5].m_X, vec_Color[5].m_Y, vec_Color[5].m_Z, vec_Color[1].m_X, vec_Color[1].m_Y, vec_Color[1].m_Z,
			vec_Color[0].m_X, vec_Color[0].m_Y, vec_Color[0].m_Z, vec_Color[4].m_X, vec_Color[4].m_Y, vec_Color[4].m_Z, vec_Color[5].m_X, vec_Color[5].m_Y, vec_Color[5].m_Z,
			vec_Color[2].m_X, vec_Color[2].m_Y, vec_Color[2].m_Z, vec_Color[7].m_X, vec_Color[7].m_Y, vec_Color[7].m_Z, vec_Color[6].m_X, vec_Color[6].m_Y, vec_Color[6].m_Z,
			vec_Color[2].m_X, vec_Color[2].m_Y, vec_Color[2].m_Z, vec_Color[3].m_X, vec_Color[3].m_Y, vec_Color[3].m_Z, vec_Color[7].m_X, vec_Color[7].m_Y, vec_Color[7].m_Z,
			vec_Color[0].m_X, vec_Color[0].m_Y, vec_Color[0].m_Z, vec_Color[6].m_X, vec_Color[6].m_Y, vec_Color[6].m_Z, vec_Color[4].m_X, vec_Color[4].m_Y, vec_Color[4].m_Z,
			vec_Color[0].m_X, vec_Color[0].m_Y, vec_Color[0].m_Z, vec_Color[2].m_X, vec_Color[2].m_Y, vec_Color[2].m_Z, vec_Color[6].m_X, vec_Color[6].m_Y, vec_Color[6].m_Z,
			vec_Color[1].m_X, vec_Color[1].m_Y, vec_Color[1].m_Z, vec_Color[7].m_X, vec_Color[7].m_Y, vec_Color[7].m_Z, vec_Color[3].m_X, vec_Color[3].m_Y, vec_Color[3].m_Z,
			vec_Color[1].m_X, vec_Color[1].m_Y, vec_Color[1].m_Z, vec_Color[5].m_X, vec_Color[5].m_Y, vec_Color[5].m_Z, vec_Color[7].m_X, vec_Color[7].m_Y, vec_Color[7].m_Z
			};

		glGenBuffers(1, &mVertexColorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColors), vertexColors, GL_STATIC_DRAW);

		GLfloat vertexNormals[] =
			{
			-1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			};

		glGenBuffers(1, &mVertexNormalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexNormalBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexNormals), vertexNormals, GL_STATIC_DRAW);

		short indices[] =
			{
			0, 1, 2, // -x
			3, 4, 5,
			6, 7, 8, // +x
			9, 10, 11,
			12, 13, 14, // -y
			15, 16, 17,
			18, 19, 20, // +y
			21, 22, 23,
			24, 25, 26, // -z
			27, 28, 29,
			30, 31, 32, // +z
			33, 34, 35,
			};

		glGenBuffers(1, &mIndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		}
	}
#endif
#if 0
void pMesh::compute_normals(float f_UVFactor, int mode)
	{
	int i,j,k;
	pVector v0,v1,v2;
	pVertex *vv0,*vv1,*vv2;

	if (mode&P_COMPUTE_FACENORM)
	{
		k=0;
		for( i=0;i<nface;i++,k+=3 )
		{
			vv0=&vert[facevert[k]];
			vv1=&vert[facevert[k+1]];
			vv2=&vert[facevert[k+2]];
			v0.vec(vv0->pos[0],vv0->pos[1],vv0->pos[2]);
			v1.vec(vv1->pos[0],vv1->pos[1],vv1->pos[2]);
			v2.vec(vv2->pos[0],vv2->pos[1],vv2->pos[2]);

			v1=v1-v0;
			v2=v2-v0;

			face[i].face_normal.cross(v1,v2);
			face[i].face_normal.normalize();
			face[i].face_normal.w=VECDOT(face[i].face_normal,v0);
		}
	}

	if (mode&P_COMPUTE_VERTNORM)
	{
		pVector d1,d2;
		float f;

		for( i=0;i<nvert;i++ )
			vert[i].norm[0]=vert[i].norm[1]=vert[i].norm[2]=0;

		k=0;
		for( i=0;i<nface;i++,k+=3 )
			for( j=0;j<3;j++ )
			{
				vv0=&vert[facevert[k+j]];
				vv1=&vert[facevert[k+((j+1)%3)]];
				vv2=&vert[facevert[k+((j+2)%3)]];
				v0.vec(vv0->pos[0],vv0->pos[1],vv0->pos[2]);
				v1.vec(vv1->pos[0],vv1->pos[1],vv1->pos[2]);
				v2.vec(vv2->pos[0],vv2->pos[1],vv2->pos[2]);

				d1=v1-v0;
				d2=v2-v0;
				d1.normalize();
				d2.normalize();
				
				f=VECDOT(d1,d2);
				f=acosf(f);
				vv0->norm[0]+=f*face[i].face_normal.x;
				vv0->norm[1]+=f*face[i].face_normal.y;
				vv0->norm[2]+=f*face[i].face_normal.z;
			}
		
		for( i=0;i<nvert;i++ )
		{
			f=sqrtf(
					vert[i].norm[0]*vert[i].norm[0]+
					vert[i].norm[1]*vert[i].norm[1]+
					vert[i].norm[2]*vert[i].norm[2]);
			if (f>0.01f)
			{
				f=1.0f/f;
				vert[i].norm[0]*=f;
				vert[i].norm[1]*=f;
				vert[i].norm[2]*=f;
			}
		}
	}

	if (mode&P_COMPUTE_TANGENTS)
		compute_tangents();

	if (mode&P_COMPUTE_CURVATURE)
		compute_curvature();

	if (mode&P_COMPUTE_BBOX)
	{
		bbox.reset();
		for( i=0;i<nvert;i++ )
			bbox.add_point(vert[i].pos);
	}

	update_buffers(f_UVFactor);
	}
#endif

};