/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*//*- Minor Component -Cloud Control-

*/

#include "pch.h"

//### INCLUDES
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"
#include <stdlib.h>

#include "Q-Includes.h"
#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-WE-CloudControl.h"
#include "Q-Structs.h"
#include "Q-CORE-Avatar.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"
#include "Q-WE-EnergyMatrix.h"

using namespace GVARS;

namespace GVARS
{

//########  - CLOUD SYSTEM - CLOUD CONTROL -  ########//

void Q_EFFCon::Cloud_ControlFrame(int Count)
	{
	switch(Q_Cloud->Cloud[Count].CloudType)
		{
		case 0: //### Smoke
			{												//25
			int FactorFinger = rand() % 36;

			if(FactorFinger > 15)
				{
				//Q_Cloud->Cloud[Count].CloudAlpha -= ((((float)rand() / 32767)*10)+0.5) *_->TimeScale;		//(((float)rand() / 32767)*3) *_->TimeScale;
				Q_Cloud->Cloud[Count].CloudAlpha -= ((((float)rand() / 32767)*3)+2) *_->TimeScale;		//(((float)rand() / 32767)*3) *_->TimeScale;

				if(Q_Cloud->Cloud[Count].CloudAlpha <= 0)
					{
					Q_Cloud->Cloud[Count].CloudAlpha = 0;
					Q_Cloud->Cloud[Count].CloudLive = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomCloud - 1)
						{
						Q_Cloud->Cloud[K] = Q_Cloud->Cloud[K+1];
						K++;
						}

					_->NomCloud--;
					}

				Q_Cloud->Cloud[Count].CloudScale += (((float)rand() / 32767)*0.01) *_->TimeScale;

				Q_Cloud->Cloud[Count].CloudTraVec.x += ((((float)rand() / 32767)-0.5)*0.1)*_->TimeScale;
				Q_Cloud->Cloud[Count].CloudTraVec.y += ((((float)rand() / 32767)-0.5)*0.1)*_->TimeScale;
				Q_Cloud->Cloud[Count].CloudTraVec.z += ((((float)rand() / 32767)-0.5)*0.1)*_->TimeScale;

				Qpo->Vec3d_AddScaled(&Q_Cloud->Cloud[Count].CloudPos, Q_Cloud->Cloud[Count].CloudSpeed*_->TimeScale, &Q_Cloud->Cloud[Count].CloudTraVec, &Q_Cloud->Cloud[Count].CloudPos);

				//1
				Q_Cloud->Cloud[Count].CloudPos.y += 0.2*_->TimeScale;

				Q_Cloud->Cloud[Count].CloudLVert.a = Q_Cloud->Cloud[Count].CloudAlpha;
				Q_Cloud->Cloud[Count].CloudLVert.r = 50;	//130	//255
				Q_Cloud->Cloud[Count].CloudLVert.g = 50;	//255
				Q_Cloud->Cloud[Count].CloudLVert.b = 50;	//255
				Q_Cloud->Cloud[Count].CloudLVert.u = 0;
				Q_Cloud->Cloud[Count].CloudLVert.v = 0;
				Q_Cloud->Cloud[Count].CloudLVert.x = Q_Cloud->Cloud[Count].CloudPos.x;
				Q_Cloud->Cloud[Count].CloudLVert.y = Q_Cloud->Cloud[Count].CloudPos.y;
				Q_Cloud->Cloud[Count].CloudLVert.z = Q_Cloud->Cloud[Count].CloudPos.z;

				Q_Cloud->Cloud[Count].CloudMatCNT++;
				if(Q_Cloud->Cloud[Count].CloudMatCNT > 49 || Q_Cloud->Cloud[Count].CloudMatCNT < 0) Q_Cloud->Cloud[Count].CloudMatCNT = 0;

				Qpo->Poly_AddOnce(&Q_Cloud->Cloud[Count].CloudLVert, 1, Medias->QSmoke[Q_Cloud->Cloud[Count].CloudMatCNT], QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, Q_Cloud->Cloud[Count].CloudScale);
				}
			} break;


			//###Blood
		case 1:
			{
			int FactorFinger = rand() % 36;

			if(FactorFinger > 15)
				{
				Q_Cloud->Cloud[Count].CloudAlpha -= ((((float)rand() / 32767)*3) + 1) *_->TimeScale; //((((float)rand() / 32767)*15) + 5) *_->TimeScale;

				if(Q_Cloud->Cloud[Count].CloudAlpha <= 0)
					{
					Q_Cloud->Cloud[Count].CloudAlpha = 0;
					Q_Cloud->Cloud[Count].CloudLive = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomCloud - 1)
						{
						Q_Cloud->Cloud[K] = Q_Cloud->Cloud[K+1];
						K++;
						}

					_->NomCloud--;
					}

				Q_Cloud->Cloud[Count].CloudScale += (((float)rand() / 32767)*0.08) *_->TimeScale;

				//Implement This Blood Gravity?
				//Q_Cloud->Cloud[Count].CloudTraVec.x += ((((float)rand() / 32767)-0.5)*2) *_->TimeScale;
				//Q_Cloud->Cloud[Count].CloudTraVec.y += ((((float)rand() / 32767)-0.5)*2) *_->TimeScale;
				//Q_Cloud->Cloud[Count].CloudTraVec.z += ((((float)rand() / 32767)-0.5)*2) *_->TimeScale;

				Qpo->Vec3d_AddScaled(&Q_Cloud->Cloud[Count].CloudPos, Q_Cloud->Cloud[Count].CloudSpeed, &Q_Cloud->Cloud[Count].CloudTraVec, &Q_Cloud->Cloud[Count].CloudPos);

				Q_Cloud->Cloud[Count].CloudLVert.a = Q_Cloud->Cloud[Count].CloudAlpha;
				Q_Cloud->Cloud[Count].CloudLVert.r = 255;
				Q_Cloud->Cloud[Count].CloudLVert.g = 255;
				Q_Cloud->Cloud[Count].CloudLVert.b = 255;
				Q_Cloud->Cloud[Count].CloudLVert.u = 0;
				Q_Cloud->Cloud[Count].CloudLVert.v = 0;
				Q_Cloud->Cloud[Count].CloudLVert.x = Q_Cloud->Cloud[Count].CloudPos.x;
				Q_Cloud->Cloud[Count].CloudLVert.y = Q_Cloud->Cloud[Count].CloudPos.y;
				Q_Cloud->Cloud[Count].CloudLVert.z = Q_Cloud->Cloud[Count].CloudPos.z;

				Qpo->Poly_AddOnce(&Q_Cloud->Cloud[Count].CloudLVert, 1, Medias->CloudBlood, QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, Q_Cloud->Cloud[Count].CloudScale);
				}
			} break;


			//###Fire
		case 2:
			{
			int FactorFinger = rand() % 36;

			if(FactorFinger > 15)
				{
				Q_Cloud->Cloud[Count].CloudAlpha -= (((float)rand() / 32767)*15) *_->TimeScale;

				if(Q_Cloud->Cloud[Count].CloudAlpha <= 0)
					{
					Q_Cloud->Cloud[Count].CloudAlpha = 0;
					Q_Cloud->Cloud[Count].CloudLive = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomCloud - 1)
						{
						Q_Cloud->Cloud[K] = Q_Cloud->Cloud[K+1];
						K++;
						}

					_->NomCloud--;
					}

				Q_Cloud->Cloud[Count].CloudScale += (((float)rand() / 32767)*0.01) *_->TimeScale;

				Q_Cloud->Cloud[Count].CloudTraVec.x += ((((float)rand() / 32767)-0.5)*0.1)*_->TimeScale;
				Q_Cloud->Cloud[Count].CloudTraVec.y += ((((float)rand() / 32767)-0.5)*0.1)*_->TimeScale;
				Q_Cloud->Cloud[Count].CloudTraVec.z += ((((float)rand() / 32767)-0.5)*0.1)*_->TimeScale;

				Qpo->Vec3d_AddScaled(&Q_Cloud->Cloud[Count].CloudPos, Q_Cloud->Cloud[Count].CloudSpeed*_->TimeScale, &Q_Cloud->Cloud[Count].CloudTraVec, &Q_Cloud->Cloud[Count].CloudPos);

				Q_Cloud->Cloud[Count].CloudPos.y += 1*_->TimeScale;

				Q_Cloud->Cloud[Count].CloudLVert.a = Q_Cloud->Cloud[Count].CloudAlpha;
				Q_Cloud->Cloud[Count].CloudLVert.r = 255;
				Q_Cloud->Cloud[Count].CloudLVert.g = 255;
				Q_Cloud->Cloud[Count].CloudLVert.b = 255;
				Q_Cloud->Cloud[Count].CloudLVert.u = 0;
				Q_Cloud->Cloud[Count].CloudLVert.v = 0;
				Q_Cloud->Cloud[Count].CloudLVert.x = Q_Cloud->Cloud[Count].CloudPos.x;
				Q_Cloud->Cloud[Count].CloudLVert.y = Q_Cloud->Cloud[Count].CloudPos.y;
				Q_Cloud->Cloud[Count].CloudLVert.z = Q_Cloud->Cloud[Count].CloudPos.z;

				Qpo->Poly_AddOnce(&Q_Cloud->Cloud[Count].CloudLVert, 1, Medias->radfire[Q_Cloud->Cloud[Count].CloudSpecCnt], QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, Q_Cloud->Cloud[Count].CloudScale);

				if(Q_Cloud->Cloud[Count].CloudSpecCnt+1 < 64) Q_Cloud->Cloud[Count].CloudSpecCnt += 1;
				else Q_Cloud->Cloud[Count].CloudSpecCnt = 44;
				if(Q_Cloud->Cloud[Count].CloudSpecCnt < 44) Q_Cloud->Cloud[Count].CloudSpecCnt = 44;
				}
			} break;


			//###Fire Expand to disperse fast
		case 3:
			{
			int FactorFinger = rand() % 36;

			if(FactorFinger > 15)
				{
				Q_Cloud->Cloud[Count].CloudAlpha -= (((float)rand() / 32767)*35) *_->TimeScale;

				if(Q_Cloud->Cloud[Count].CloudAlpha <= 0)
					{
					Q_Cloud->Cloud[Count].CloudAlpha = 0;
					Q_Cloud->Cloud[Count].CloudLive = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomCloud - 1)
						{
						Q_Cloud->Cloud[K] = Q_Cloud->Cloud[K+1];
						K++;
						}

					_->NomCloud--;
					}

				Q_Cloud->Cloud[Count].CloudScale += ((((float)rand() / 32767)*0.1)+0.05) *_->TimeScale;

				Q_Cloud->Cloud[Count].CloudTraVec.x += ((((float)rand() / 32767)-0.5)*0.1)*_->TimeScale;
				Q_Cloud->Cloud[Count].CloudTraVec.y += ((((float)rand() / 32767)-0.5)*0.1)*_->TimeScale;
				Q_Cloud->Cloud[Count].CloudTraVec.z += ((((float)rand() / 32767)-0.5)*0.1)*_->TimeScale;

				Qpo->Vec3d_AddScaled(&Q_Cloud->Cloud[Count].CloudPos, Q_Cloud->Cloud[Count].CloudSpeed*_->TimeScale, &Q_Cloud->Cloud[Count].CloudTraVec, &Q_Cloud->Cloud[Count].CloudPos);

				//Q_Cloud->Cloud[Count].CloudPos.y -= 1;

				Q_Cloud->Cloud[Count].CloudLVert.a = Q_Cloud->Cloud[Count].CloudAlpha;
				Q_Cloud->Cloud[Count].CloudLVert.r = 255;
				Q_Cloud->Cloud[Count].CloudLVert.g = 255;
				Q_Cloud->Cloud[Count].CloudLVert.b = 255;
				Q_Cloud->Cloud[Count].CloudLVert.u = 0;
				Q_Cloud->Cloud[Count].CloudLVert.v = 0;
				Q_Cloud->Cloud[Count].CloudLVert.x = Q_Cloud->Cloud[Count].CloudPos.x;
				Q_Cloud->Cloud[Count].CloudLVert.y = Q_Cloud->Cloud[Count].CloudPos.y;
				Q_Cloud->Cloud[Count].CloudLVert.z = Q_Cloud->Cloud[Count].CloudPos.z;

				Qpo->Poly_AddOnce(&Q_Cloud->Cloud[Count].CloudLVert, 1, Medias->radfire[Q_Cloud->Cloud[Count].CloudSpecCnt], QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, Q_Cloud->Cloud[Count].CloudScale);

				if(Q_Cloud->Cloud[Count].CloudSpecCnt+1 < 64) Q_Cloud->Cloud[Count].CloudSpecCnt += 1;
				else Q_Cloud->Cloud[Count].CloudSpecCnt = 44;
				if(Q_Cloud->Cloud[Count].CloudSpecCnt < 44) Q_Cloud->Cloud[Count].CloudSpecCnt = 44;
				}
			} break;


			//###Limb Fire Clouds
		case 4:
			{
			int FactorFinger = rand() % 36;

			if(FactorFinger > 15)
				{
				Q_Cloud->Cloud[Count].CloudAlpha -= (((float)rand() / 32767)*10) *_->TimeScale;

				if(Q_Cloud->Cloud[Count].CloudAlpha <= 0)
					{
					Q_Cloud->Cloud[Count].CloudAlpha = 0;
					Q_Cloud->Cloud[Count].CloudLive = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomCloud - 1)
						{
						Q_Cloud->Cloud[K] = Q_Cloud->Cloud[K+1];
						K++;
						}

					_->NomCloud--;
					}

				Q_Cloud->Cloud[Count].CloudScale += (((float)rand() / 32767)*0.003) *_->TimeScale;

				Q_Cloud->Cloud[Count].CloudTraVec.y -= 0.18*_->TimeScale;

				Qpo->Vec3d_AddScaled(&Q_Cloud->Cloud[Count].CloudPos, Q_Cloud->Cloud[Count].CloudSpeed*_->TimeScale, &Q_Cloud->Cloud[Count].CloudTraVec, &Q_Cloud->Cloud[Count].CloudPos);

				Q_Cloud->Cloud[Count].CloudLVert.a = Q_Cloud->Cloud[Count].CloudAlpha;
				Q_Cloud->Cloud[Count].CloudLVert.r = 226;
				Q_Cloud->Cloud[Count].CloudLVert.g = 255;
				Q_Cloud->Cloud[Count].CloudLVert.b = 62;
				Q_Cloud->Cloud[Count].CloudLVert.u = 0;
				Q_Cloud->Cloud[Count].CloudLVert.v = 0;
				Q_Cloud->Cloud[Count].CloudLVert.x = Q_Cloud->Cloud[Count].CloudPos.x;
				Q_Cloud->Cloud[Count].CloudLVert.y = Q_Cloud->Cloud[Count].CloudPos.y;
				Q_Cloud->Cloud[Count].CloudLVert.z = Q_Cloud->Cloud[Count].CloudPos.z;

				Qpo->Poly_AddOnce(&Q_Cloud->Cloud[Count].CloudLVert, 1, Medias->CloudLimb, QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, Q_Cloud->Cloud[Count].CloudScale);
				}
			} break;

			//###Smoke Two
		case 5:
			{
			int FactorFinger = rand() % 36;

			if(FactorFinger > 15)
				{
				//Q_Cloud->Cloud[Count].CloudAlpha -= ((((float)rand() / 32767)*2) + 1) *_->TimeScale;		//((((float)rand() / 32767)*1.5) + 0.8) *_->TimeScale;
				Q_Cloud->Cloud[Count].CloudAlpha -= ((((float)rand() / 32767)*3) + 1) *_->TimeScale;		//((((float)rand() / 32767)*1.5) + 0.8) *_->TimeScale;

				if(Q_Cloud->Cloud[Count].CloudAlpha <= 0)
					{
					Q_Cloud->Cloud[Count].CloudAlpha = 0;
					Q_Cloud->Cloud[Count].CloudLive = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomCloud - 1)
						{
						Q_Cloud->Cloud[K] = Q_Cloud->Cloud[K+1];
						K++;
						}

					_->NomCloud--;
					}

				Q_Cloud->Cloud[Count].CloudScale += (((float)rand() / 32767)*0.00085) *_->TimeScale;

				Q_Cloud->Cloud[Count].CloudTraVec.x += ((((float)rand() / 32767)-0.5)*0.001)*_->TimeScale;
				Q_Cloud->Cloud[Count].CloudTraVec.y += ((((float)rand() / 32767)-0.5)*0.001)*_->TimeScale;
				Q_Cloud->Cloud[Count].CloudTraVec.z += ((((float)rand() / 32767)-0.5)*0.001)*_->TimeScale;

				Qpo->Vec3d_AddScaled(&Q_Cloud->Cloud[Count].CloudPos, Q_Cloud->Cloud[Count].CloudSpeed*_->TimeScale, &Q_Cloud->Cloud[Count].CloudTraVec, &Q_Cloud->Cloud[Count].CloudPos);

				Q_Cloud->Cloud[Count].CloudPos.y += (((float)rand() / 32767)*0.1)*_->TimeScale;

				Q_Cloud->Cloud[Count].CloudLVert.a = Q_Cloud->Cloud[Count].CloudAlpha;
				Q_Cloud->Cloud[Count].CloudLVert.r = 75;	//255
				Q_Cloud->Cloud[Count].CloudLVert.g = 75;	//255
				Q_Cloud->Cloud[Count].CloudLVert.b = 75;	//255
				Q_Cloud->Cloud[Count].CloudLVert.u = 0;
				Q_Cloud->Cloud[Count].CloudLVert.v = 0;
				Q_Cloud->Cloud[Count].CloudLVert.x = Q_Cloud->Cloud[Count].CloudPos.x;
				Q_Cloud->Cloud[Count].CloudLVert.y = Q_Cloud->Cloud[Count].CloudPos.y;
				Q_Cloud->Cloud[Count].CloudLVert.z = Q_Cloud->Cloud[Count].CloudPos.z;

				Q_Cloud->Cloud[Count].CloudMatCNT++;
				if(Q_Cloud->Cloud[Count].CloudMatCNT > 49 || Q_Cloud->Cloud[Count].CloudMatCNT < 0) Q_Cloud->Cloud[Count].CloudMatCNT = 0;

				Qpo->Poly_AddOnce(&Q_Cloud->Cloud[Count].CloudLVert, 1, Medias->QSmoke[Q_Cloud->Cloud[Count].CloudMatCNT], QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, Q_Cloud->Cloud[Count].CloudScale);
				}
			} break;


			//###Flames
		case 6:
			{
			int FactorFinger = rand() % 36;

			if(FactorFinger > 15)
				{
				Q_Cloud->Cloud[Count].CloudAlpha -= ((((float)rand() / 32767)*3.5) + 1.5) *_->TimeScale;		//((((float)rand() / 32767)*2.5) + 1) *_->TimeScale;

				if(Q_Cloud->Cloud[Count].CloudAlpha <= 0)
					{
					Q_Cloud->Cloud[Count].CloudAlpha = 0;
					Q_Cloud->Cloud[Count].CloudLive = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomCloud - 1)
						{
						Q_Cloud->Cloud[K] = Q_Cloud->Cloud[K+1];
						K++;
						}

					_->NomCloud--;
					}

				if(Q_Cloud->Cloud[Count].CloudScaleDIR == 0)
					{
					if(Q_Cloud->Cloud[Count].CloudScale + ((((float)rand() / 32767)*0.15)*_->TimeScale) < 1) Q_Cloud->Cloud[Count].CloudScale += (((float)rand() / 32767)*0.15)*_->TimeScale;
					else
						{
						Q_Cloud->Cloud[Count].CloudScale = 1;
						Q_Cloud->Cloud[Count].CloudScaleDIR = 1;
						}
					}
				else
					{
					if(Q_Cloud->Cloud[Count].CloudScale - ((((float)rand() / 32767)*0.15)*_->TimeScale) > 0.01) Q_Cloud->Cloud[Count].CloudScale -= (((float)rand() / 32767)*0.15)*_->TimeScale;
					else
						{
						Q_Cloud->Cloud[Count].CloudScale = 0.01;
						Q_Cloud->Cloud[Count].CloudScaleDIR = 0;
						}
					}

				Q_Cloud->Cloud[Count].CloudSpecCnt++;
				if(Q_Cloud->Cloud[Count].CloudSpecCnt > 15 || Q_Cloud->Cloud[Count].CloudSpecCnt < 0) Q_Cloud->Cloud[Count].CloudSpecCnt = 6;

				Q_Cloud->Cloud[Count].CloudTraVec.x += ((((float)rand() / 32767)-0.5)*0.01)*_->TimeScale;
				Q_Cloud->Cloud[Count].CloudTraVec.y += ((((float)rand() / 32767)-0.5)*0.01)*_->TimeScale;
				Q_Cloud->Cloud[Count].CloudTraVec.z += ((((float)rand() / 32767)-0.5)*0.01)*_->TimeScale;

				Qpo->Vec3d_AddScaled(&Q_Cloud->Cloud[Count].CloudPos, Q_Cloud->Cloud[Count].CloudSpeed*_->TimeScale, &Q_Cloud->Cloud[Count].CloudTraVec, &Q_Cloud->Cloud[Count].CloudPos);

				Q_Cloud->Cloud[Count].CloudPos.y += (((float)rand() / 32767)*0.1)*_->TimeScale;

				Q_Cloud->Cloud[Count].CloudLVert.a = Q_Cloud->Cloud[Count].CloudAlpha;
				Q_Cloud->Cloud[Count].CloudLVert.r = Q_Cloud->Cloud[Count].CloudRed;	//255
				Q_Cloud->Cloud[Count].CloudLVert.g = Q_Cloud->Cloud[Count].CloudGreen;	//255
				Q_Cloud->Cloud[Count].CloudLVert.b = Q_Cloud->Cloud[Count].CloudBlue;	//255
				Q_Cloud->Cloud[Count].CloudLVert.u = 0;
				Q_Cloud->Cloud[Count].CloudLVert.v = 0;
				Q_Cloud->Cloud[Count].CloudLVert.x = Q_Cloud->Cloud[Count].CloudPos.x;
				Q_Cloud->Cloud[Count].CloudLVert.y = Q_Cloud->Cloud[Count].CloudPos.y;
				Q_Cloud->Cloud[Count].CloudLVert.z = Q_Cloud->Cloud[Count].CloudPos.z;

				//Qpo->Poly_AddOnce(&Q_Cloud->Cloud[Count].CloudLVert, 1, Medias->Cloud3, QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, Q_Cloud->Cloud[Count].CloudScale);
				Qpo->Poly_AddOnce(&Q_Cloud->Cloud[Count].CloudLVert, 1, Medias->radfire[Q_Cloud->Cloud[Count].CloudSpecCnt], QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, Q_Cloud->Cloud[Count].CloudScale);
				}
			} break;


			//###Jink Smoke Blast
		case 7:
			{
			int FactorFinger = rand() % 36;

			if(FactorFinger > 15)
				{
				//Q_Cloud->Cloud[Count].CloudAlpha -= ((((float)rand() / 32767)*35) + 25) *_->TimeScale;
				Q_Cloud->Cloud[Count].CloudAlpha -= ((((float)rand() / 32767)*5) + 2) *_->TimeScale;

				if(Q_Cloud->Cloud[Count].CloudAlpha <= 0)
					{
					Q_Cloud->Cloud[Count].CloudAlpha = 0;
					Q_Cloud->Cloud[Count].CloudLive = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomCloud - 1)
						{
						Q_Cloud->Cloud[K] = Q_Cloud->Cloud[K+1];
						K++;
						}

					_->NomCloud--;
					}

				Q_Cloud->Cloud[Count].CloudSpeed += 0.095;

				Q_Cloud->Cloud[Count].CloudScale += (((float)rand() / 32767)*0.005) *_->TimeScale;

				Q_Cloud->Cloud[Count].CloudTraVec.x += ((((float)rand() / 32767)-0.5)*0.001)*_->TimeScale;
				Q_Cloud->Cloud[Count].CloudTraVec.y += ((((float)rand() / 32767)-0.5)*0.001)*_->TimeScale;
				Q_Cloud->Cloud[Count].CloudTraVec.z += ((((float)rand() / 32767)-0.5)*0.001)*_->TimeScale;

				Qpo->Vec3d_AddScaled(&Q_Cloud->Cloud[Count].CloudPos, Q_Cloud->Cloud[Count].CloudSpeed*_->TimeScale, &Q_Cloud->Cloud[Count].CloudTraVec, &Q_Cloud->Cloud[Count].CloudPos);

				Q_Cloud->Cloud[Count].CloudPos.y += (((float)rand() / 32767)*0.14)*_->TimeScale;

				Q_Cloud->Cloud[Count].CloudLVert.a = Q_Cloud->Cloud[Count].CloudAlpha;
				Q_Cloud->Cloud[Count].CloudLVert.r = 75;
				Q_Cloud->Cloud[Count].CloudLVert.g = 75;
				Q_Cloud->Cloud[Count].CloudLVert.b = 75;
				Q_Cloud->Cloud[Count].CloudLVert.u = 0;
				Q_Cloud->Cloud[Count].CloudLVert.v = 0;
				Q_Cloud->Cloud[Count].CloudLVert.x = Q_Cloud->Cloud[Count].CloudPos.x;
				Q_Cloud->Cloud[Count].CloudLVert.y = Q_Cloud->Cloud[Count].CloudPos.y;
				Q_Cloud->Cloud[Count].CloudLVert.z = Q_Cloud->Cloud[Count].CloudPos.z;

				Q_Cloud->Cloud[Count].CloudMatCNT++;
				if(Q_Cloud->Cloud[Count].CloudMatCNT > 49 || Q_Cloud->Cloud[Count].CloudMatCNT < 0) Q_Cloud->Cloud[Count].CloudMatCNT = 0;

				Qpo->Poly_AddOnce(&Q_Cloud->Cloud[Count].CloudLVert, 1, Medias->QSmoke[Q_Cloud->Cloud[Count].CloudMatCNT], QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, Q_Cloud->Cloud[Count].CloudScale);
				}
			} break;

		case 8:
			{
			int FactorFinger = rand() % 36;

			if(FactorFinger > 15)
				{
				Q_Cloud->Cloud[Count].CloudAlpha -= ((((float)rand() / 32767)*35) + 25) *_->TimeScale;

				if(Q_Cloud->Cloud[Count].CloudAlpha <= 0)
					{
					Q_Cloud->Cloud[Count].CloudAlpha = 0;
					Q_Cloud->Cloud[Count].CloudLive = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomCloud - 1)
						{
						Q_Cloud->Cloud[K] = Q_Cloud->Cloud[K+1];
						K++;
						}

					_->NomCloud--;
					}

				Q_Cloud->Cloud[Count].CloudSpeed += 0.095;

				Q_Cloud->Cloud[Count].CloudScale += (((float)rand() / 32767)*0.005) *_->TimeScale;

				Q_Cloud->Cloud[Count].CloudTraVec.x += ((((float)rand() / 32767)-0.5)*0.001)*_->TimeScale;
				Q_Cloud->Cloud[Count].CloudTraVec.y += ((((float)rand() / 32767)-0.5)*0.001)*_->TimeScale;
				Q_Cloud->Cloud[Count].CloudTraVec.z += ((((float)rand() / 32767)-0.5)*0.001)*_->TimeScale;

				Qpo->Vec3d_AddScaled(&Q_Cloud->Cloud[Count].CloudPos, Q_Cloud->Cloud[Count].CloudSpeed*_->TimeScale, &Q_Cloud->Cloud[Count].CloudTraVec, &Q_Cloud->Cloud[Count].CloudPos);

				Q_Cloud->Cloud[Count].CloudPos.y += (((float)rand() / 32767)*0.14)*_->TimeScale;

				Q_Cloud->Cloud[Count].CloudLVert.a = Q_Cloud->Cloud[Count].CloudAlpha;
				Q_Cloud->Cloud[Count].CloudLVert.r = 255;
				Q_Cloud->Cloud[Count].CloudLVert.g = 255;
				Q_Cloud->Cloud[Count].CloudLVert.b = 225;
				Q_Cloud->Cloud[Count].CloudLVert.u = 0;
				Q_Cloud->Cloud[Count].CloudLVert.v = 0;
				Q_Cloud->Cloud[Count].CloudLVert.x = Q_Cloud->Cloud[Count].CloudPos.x;
				Q_Cloud->Cloud[Count].CloudLVert.y = Q_Cloud->Cloud[Count].CloudPos.y;
				Q_Cloud->Cloud[Count].CloudLVert.z = Q_Cloud->Cloud[Count].CloudPos.z;

				Qpo->Poly_AddOnce(&Q_Cloud->Cloud[Count].CloudLVert, 1, Medias->Cloud3, QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, Q_Cloud->Cloud[Count].CloudScale);
				}
			} break;


			//### Shock
		case 9:
			{												//25	15
			int FactorFinger = rand() % 36;

			if(FactorFinger > 15)
				{
				Q_Cloud->Cloud[Count].CloudAlpha -= ((((float)rand() / 32767)*35)+10) *_->TimeScale; //(((float)rand() / 32767)*3) *_->TimeScale;

				if(Q_Cloud->Cloud[Count].CloudAlpha <= 0)
					{
					Q_Cloud->Cloud[Count].CloudAlpha = 0;
					Q_Cloud->Cloud[Count].CloudLive = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomCloud - 1)
						{
						Q_Cloud->Cloud[K] = Q_Cloud->Cloud[K+1];
						K++;
						}

					_->NomCloud--;
					}

				Q_Cloud->Cloud[Count].CloudScale += (((float)rand() / 32767)*0.025) *_->TimeScale;
				//Q_Cloud->Cloud[Count].CloudScale += (((float)rand() / 32767)*0.003) *_->TimeScale;

				//Q_Cloud->Cloud[Count].CloudTraVec.x += ((((float)rand() / 32767)-0.5)*0.1)*_->TimeScale;
				//Q_Cloud->Cloud[Count].CloudTraVec.y += ((((float)rand() / 32767)-0.5)*0.1)*_->TimeScale;
				//Q_Cloud->Cloud[Count].CloudTraVec.z += ((((float)rand() / 32767)-0.5)*0.1)*_->TimeScale;

				Qpo->Vec3d_AddScaled(&Q_Cloud->Cloud[Count].CloudPos, Q_Cloud->Cloud[Count].CloudSpeed*_->TimeScale, &Q_Cloud->Cloud[Count].CloudTraVec, &Q_Cloud->Cloud[Count].CloudPos);

				Q_Cloud->Cloud[Count].CloudSpeed *= 1.25 *_->TimeScale;

				Q_Cloud->Cloud[Count].CloudLVert.a = Q_Cloud->Cloud[Count].CloudAlpha;
				Q_Cloud->Cloud[Count].CloudLVert.r = 255;	//255
				Q_Cloud->Cloud[Count].CloudLVert.g = 255;	//255
				Q_Cloud->Cloud[Count].CloudLVert.b = 255;	//255
				Q_Cloud->Cloud[Count].CloudLVert.u = 0;
				Q_Cloud->Cloud[Count].CloudLVert.v = 0;
				Q_Cloud->Cloud[Count].CloudLVert.x = Q_Cloud->Cloud[Count].CloudPos.x;
				Q_Cloud->Cloud[Count].CloudLVert.y = Q_Cloud->Cloud[Count].CloudPos.y;
				Q_Cloud->Cloud[Count].CloudLVert.z = Q_Cloud->Cloud[Count].CloudPos.z;

				Qpo->Poly_AddOnce(&Q_Cloud->Cloud[Count].CloudLVert, 1, Medias->Cloud9, QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, Q_Cloud->Cloud[Count].CloudScale);
				}
			} break;

			//###Smoke Two
		case 10:
			{
			int FactorFinger = rand() % 36;

			if(FactorFinger > 15)
				{
				//Q_Cloud->Cloud[Count].CloudAlpha -= ((((float)rand() / 32767)*2) + 1) *_->TimeScale;		//((((float)rand() / 32767)*1.5) + 0.8) *_->TimeScale;
				Q_Cloud->Cloud[Count].CloudAlpha -= ((((float)rand() / 32767)*5) + 1) *_->TimeScale;		//((((float)rand() / 32767)*1.5) + 0.8) *_->TimeScale;

				if(Q_Cloud->Cloud[Count].CloudAlpha <= 0)
					{
					Q_Cloud->Cloud[Count].CloudAlpha = 0;
					Q_Cloud->Cloud[Count].CloudLive = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomCloud - 1)
						{
						Q_Cloud->Cloud[K] = Q_Cloud->Cloud[K+1];
						K++;
						}

					_->NomCloud--;
					}

				Q_Cloud->Cloud[Count].CloudScale += (((float)rand() / 32767)*0.01) *_->TimeScale;

				Q_Cloud->Cloud[Count].CloudTraVec.x += ((((float)rand() / 32767)-0.5)*0.001)*_->TimeScale;
				Q_Cloud->Cloud[Count].CloudTraVec.y += ((((float)rand() / 32767)-0.5)*0.001)*_->TimeScale;
				Q_Cloud->Cloud[Count].CloudTraVec.z += ((((float)rand() / 32767)-0.5)*0.001)*_->TimeScale;

				Qpo->Vec3d_AddScaled(&Q_Cloud->Cloud[Count].CloudPos, Q_Cloud->Cloud[Count].CloudSpeed*_->TimeScale, &Q_Cloud->Cloud[Count].CloudTraVec, &Q_Cloud->Cloud[Count].CloudPos);

				Q_Cloud->Cloud[Count].CloudPos.y += (((float)rand() / 32767)*0.7)*_->TimeScale;

				Q_Cloud->Cloud[Count].CloudLVert.a = Q_Cloud->Cloud[Count].CloudAlpha;
				Q_Cloud->Cloud[Count].CloudLVert.r = 75;	//255
				Q_Cloud->Cloud[Count].CloudLVert.g = 75;	//255
				Q_Cloud->Cloud[Count].CloudLVert.b = 75;	//255
				Q_Cloud->Cloud[Count].CloudLVert.u = 0;
				Q_Cloud->Cloud[Count].CloudLVert.v = 0;
				Q_Cloud->Cloud[Count].CloudLVert.x = Q_Cloud->Cloud[Count].CloudPos.x;
				Q_Cloud->Cloud[Count].CloudLVert.y = Q_Cloud->Cloud[Count].CloudPos.y;
				Q_Cloud->Cloud[Count].CloudLVert.z = Q_Cloud->Cloud[Count].CloudPos.z;

				Q_Cloud->Cloud[Count].CloudMatCNT++;
				if(Q_Cloud->Cloud[Count].CloudMatCNT > 49 || Q_Cloud->Cloud[Count].CloudMatCNT < 0) Q_Cloud->Cloud[Count].CloudMatCNT = 0;

				Qpo->Poly_AddOnce(&Q_Cloud->Cloud[Count].CloudLVert, 1, Medias->QSmoke[Q_Cloud->Cloud[Count].CloudMatCNT], QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, Q_Cloud->Cloud[Count].CloudScale);
				}
			} break;

				//###Smoke
		case 11:
			{
			int FactorFinger = rand() % 36;

			if(FactorFinger > 15)
				{
				Q_Cloud->Cloud[Count].CloudAlpha -= ((((float)rand() / 32767)*Q_Cloud->Cloud[Count].CloudALPHAINC)+(Q_Cloud->Cloud[Count].CloudALPHAINC/3)) *_->TimeScale;

				if(Q_Cloud->Cloud[Count].CloudAlpha <= 0)
					{
					Q_Cloud->Cloud[Count].CloudAlpha = 0;
					Q_Cloud->Cloud[Count].CloudLive = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomCloud - 1)
						{
						Q_Cloud->Cloud[K] = Q_Cloud->Cloud[K+1];
						K++;
						}

					_->NomCloud--;
					}

				Q_Cloud->Cloud[Count].CloudScale += (((float)rand() / 32767)*Q_Cloud->Cloud[Count].CloudSCALEINC) *_->TimeScale;

				Q_Cloud->Cloud[Count].CloudTraVec.x += ((((float)rand() / 32767)-0.5)*0.1)*_->TimeScale;
				Q_Cloud->Cloud[Count].CloudTraVec.y += ((((float)rand() / 32767)-0.5)*0.1)*_->TimeScale;
				Q_Cloud->Cloud[Count].CloudTraVec.z += ((((float)rand() / 32767)-0.5)*0.1)*_->TimeScale;

				Qpo->Vec3d_AddScaled(&Q_Cloud->Cloud[Count].CloudPos, Q_Cloud->Cloud[Count].CloudSpeed*_->TimeScale, &Q_Cloud->Cloud[Count].CloudTraVec, &Q_Cloud->Cloud[Count].CloudPos);

				Q_Cloud->Cloud[Count].CloudPos.y -= Q_Cloud->Cloud[Count].CloudGRAVITY*_->TimeScale;

				Q_Cloud->Cloud[Count].CloudLVert.a = Q_Cloud->Cloud[Count].CloudAlpha;
				Q_Cloud->Cloud[Count].CloudLVert.r = Q_Cloud->Cloud[Count].CloudRED;
				Q_Cloud->Cloud[Count].CloudLVert.g = Q_Cloud->Cloud[Count].CloudGREEN;
				Q_Cloud->Cloud[Count].CloudLVert.b = Q_Cloud->Cloud[Count].CloudBLUE;
				Q_Cloud->Cloud[Count].CloudLVert.u = 0;
				Q_Cloud->Cloud[Count].CloudLVert.v = 0;
				Q_Cloud->Cloud[Count].CloudLVert.x = Q_Cloud->Cloud[Count].CloudPos.x;
				Q_Cloud->Cloud[Count].CloudLVert.y = Q_Cloud->Cloud[Count].CloudPos.y;
				Q_Cloud->Cloud[Count].CloudLVert.z = Q_Cloud->Cloud[Count].CloudPos.z;

				Q_Cloud->Cloud[Count].CloudMatCNT++;
				if(Q_Cloud->Cloud[Count].CloudMatCNT > 49 || Q_Cloud->Cloud[Count].CloudMatCNT < 0) Q_Cloud->Cloud[Count].CloudMatCNT = 0;

				Qpo->Poly_AddOnce(&Q_Cloud->Cloud[Count].CloudLVert, 1, Medias->QSmoke[Q_Cloud->Cloud[Count].CloudMatCNT], QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, Q_Cloud->Cloud[Count].CloudScale);
				}
			} break;


				//###Smoke
		case 12:
			{
			int FactorFinger = rand() % 36;

			if(FactorFinger > 15)
				{
				if(Q_Cloud->Cloud[Count].CloudPos.x > Q_Cloud->Cloud[_->NomCloud].CloudMaxs.x
					&& Q_Cloud->Cloud[Count].CloudPos.x < Q_Cloud->Cloud[_->NomCloud].CloudMins.x
					&& Q_Cloud->Cloud[Count].CloudPos.y > Q_Cloud->Cloud[_->NomCloud].CloudMaxs.y
					&& Q_Cloud->Cloud[Count].CloudPos.y < Q_Cloud->Cloud[_->NomCloud].CloudMins.y
					&& Q_Cloud->Cloud[Count].CloudPos.z > Q_Cloud->Cloud[_->NomCloud].CloudMaxs.z
					&& Q_Cloud->Cloud[Count].CloudPos.z < Q_Cloud->Cloud[_->NomCloud].CloudMins.z)
					{
					Q_Cloud->Cloud[Count].CloudAlpha -= ((((float)rand() / 32767)*Q_Cloud->Cloud[Count].CloudALPHAINC)+(Q_Cloud->Cloud[Count].CloudALPHAINC/3)) *_->TimeScale;
					}
				else Q_Cloud->Cloud[Count].CloudAlpha -= 50 * _->TimeScale;

				if(Q_Cloud->Cloud[Count].CloudAlpha <= 0)
					{
					Q_Cloud->Cloud[Count].CloudAlpha = 0;
					Q_Cloud->Cloud[Count].CloudLive = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomCloud - 1)
						{
						Q_Cloud->Cloud[K] = Q_Cloud->Cloud[K+1];
						K++;
						}

					_->NomCloud--;
					}

				Q_Cloud->Cloud[Count].CloudScale += (((float)rand() / 32767)*Q_Cloud->Cloud[Count].CloudSCALEINC) *_->TimeScale;

				Q_Cloud->Cloud[Count].CloudTraVec.x += ((((float)rand() / 32767)-0.5)*0.2)*_->TimeScale;
				Q_Cloud->Cloud[Count].CloudTraVec.y -= (((float)rand() / 32767)*2)*_->TimeScale;
				Q_Cloud->Cloud[Count].CloudTraVec.z += ((((float)rand() / 32767)-0.5)*0.2)*_->TimeScale;

				Qpo->Vec3d_AddScaled(&Q_Cloud->Cloud[Count].CloudPos, Q_Cloud->Cloud[Count].CloudSpeed*_->TimeScale, &Q_Cloud->Cloud[Count].CloudTraVec, &Q_Cloud->Cloud[Count].CloudPos);

				Q_Cloud->Cloud[Count].CloudPos.y -= Q_Cloud->Cloud[Count].CloudGRAVITY*_->TimeScale;

				Q_Cloud->Cloud[Count].CloudLVert.a = Q_Cloud->Cloud[Count].CloudAlpha;
				Q_Cloud->Cloud[Count].CloudLVert.r = Q_Cloud->Cloud[Count].CloudRED;
				Q_Cloud->Cloud[Count].CloudLVert.g = Q_Cloud->Cloud[Count].CloudGREEN;
				Q_Cloud->Cloud[Count].CloudLVert.b = Q_Cloud->Cloud[Count].CloudBLUE;
				Q_Cloud->Cloud[Count].CloudLVert.u = 0;
				Q_Cloud->Cloud[Count].CloudLVert.v = 0;
				Q_Cloud->Cloud[Count].CloudLVert.x = Q_Cloud->Cloud[Count].CloudPos.x;
				Q_Cloud->Cloud[Count].CloudLVert.y = Q_Cloud->Cloud[Count].CloudPos.y;
				Q_Cloud->Cloud[Count].CloudLVert.z = Q_Cloud->Cloud[Count].CloudPos.z;

				Q_Cloud->Cloud[Count].CloudMatCNT++;
				if(Q_Cloud->Cloud[Count].CloudMatCNT > 49 || Q_Cloud->Cloud[Count].CloudMatCNT < 0) Q_Cloud->Cloud[Count].CloudMatCNT = 0;

				Qpo->Poly_AddOnce(&Q_Cloud->Cloud[Count].CloudLVert, 1, Medias->QSmoke[Q_Cloud->Cloud[Count].CloudMatCNT], QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, Q_Cloud->Cloud[Count].CloudScale);
				}
			} break;
		}
	}


	//###### CLOUD MANAGEMENT
void Q_COREFunctions::CloudManagement(void)
	{
	while(_->NomCloud >= Q_Cloud->m_ArrayMx)
		{
		helly = Cube::randomFac() % (Q_Cloud->m_ArrayMx - 1);

		Q_Cloud->Cloud[helly].CloudAlpha = 0;
		Q_Cloud->Cloud[helly].CloudLive = 0;

		//### Array Reorder
		int K = helly;
		while(K < _->NomCloud - 1)
			{
			Q_Cloud->Cloud[K] = Q_Cloud->Cloud[K+1];
			K++;
			}

		_->NomCloud--;
		}
	}

};