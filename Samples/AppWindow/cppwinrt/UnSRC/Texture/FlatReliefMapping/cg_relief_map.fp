!!ARBfp1.0
# cgc version 2.0.0001, build date Jan 22 2007 00:21:19
# command line args: -profile arbfp1
# source file: c:\Projects Base\Unification\UnSRC\Texture\FlatReliefMapping\shaders\cg_relief_map.cg
#vendor NVIDIA Corporation
#version 2.0.0.1
#profile arbfp1
#program main_relief
#semantic main_relief.rmtex : TEXUNIT0
#semantic main_relief.colortex : TEXUNIT1
#semantic main_relief.ambient
#semantic main_relief.diffuse
#semantic main_relief.specular
#semantic main_relief.planes
#var float3 IN.vpos : $vin.TEXCOORD0 :  : 0 : 0
#var float2 IN.texcoord : $vin.TEXCOORD1 : TEX1 : 0 : 1
#var float3 IN.view : $vin.TEXCOORD2 : TEX2 : 0 : 1
#var float3 IN.light : $vin.TEXCOORD3 : TEX3 : 0 : 1
#var float4 IN.scale : $vin.TEXCOORD4 : TEX4 : 0 : 1
#var float2 IN.curvature : $vin.TEXCOORD5 :  : 0 : 0
#var sampler2D rmtex : TEXUNIT0 : texunit 0 : 1 : 1
#var sampler2D colortex : TEXUNIT1 : texunit 1 : 2 : 1
#var float4 ambient :  : c[0] : 3 : 1
#var float4 diffuse :  : c[1] : 4 : 1
#var float4 specular :  : c[2] : 5 : 1
#var float2 planes :  :  : 6 : 0
#var float4 main_relief.color : $vout.COLOR : COL : -1 : 1
#const c[3] = 1 0.1 0.5 0
PARAM c[4] = { program.local[0..2],
		{ 1, 0.1, 0.5, 0 } };
TEMP R0;
TEMP R1;
TEMP R2;
TEMP R3;
DP3 R0.x, fragment.texcoord[2], fragment.texcoord[2];
RSQ R1.x, R0.x;
MUL R2.xyz, R1.x, fragment.texcoord[2];
MUL R0.xyz, -R2.z, fragment.texcoord[4];
MOV R2.z, -R2;
TEX R0.w, fragment.texcoord[1], texture[0], 2D;
RCP R0.x, R0.x;
RCP R0.z, R0.z;
RCP R0.y, R0.y;
MUL R0.xyz, fragment.texcoord[4].z, R0;
MUL R0.xyz, R2, R0;
MUL R0.xyz, R0, c[3].y;
MOV R2.z, c[3].w;
MOV R2.xy, fragment.texcoord[1];
ADD R3.xyz, R0, R2;
CMP R2.xyz, -R0.w, R3, R2;
TEX R0.w, R2, texture[0], 2D;
ADD R3.xyz, R0, R2;
ADD R0.w, R2.z, -R0;
CMP R2.xyz, R0.w, R3, R2;
TEX R0.w, R2, texture[0], 2D;
ADD R3.xyz, R0, R2;
ADD R0.w, R2.z, -R0;
CMP R2.xyz, R0.w, R3, R2;
TEX R0.w, R2, texture[0], 2D;
ADD R3.xyz, R0, R2;
ADD R0.w, R2.z, -R0;
CMP R2.xyz, R0.w, R3, R2;
TEX R0.w, R2, texture[0], 2D;
ADD R3.xyz, R0, R2;
ADD R0.w, R2.z, -R0;
CMP R2.xyz, R0.w, R3, R2;
TEX R0.w, R2, texture[0], 2D;
ADD R3.xyz, R0, R2;
ADD R0.w, R2.z, -R0;
CMP R2.xyz, R0.w, R3, R2;
TEX R0.w, R2, texture[0], 2D;
ADD R3.xyz, R0, R2;
ADD R0.w, R2.z, -R0;
CMP R2.xyz, R0.w, R3, R2;
TEX R0.w, R2, texture[0], 2D;
ADD R3.xyz, R0, R2;
ADD R0.w, R2.z, -R0;
CMP R2.xyz, R0.w, R3, R2;
TEX R0.w, R2, texture[0], 2D;
ADD R3.xyz, R0, R2;
ADD R0.w, R2.z, -R0;
CMP R2.xyz, R0.w, R3, R2;
ADD R3.xyz, R0, R2;
TEX R0.w, R2, texture[0], 2D;
ADD R0.w, R2.z, -R0;
CMP R2.xyz, R0.w, R3, R2;
MUL R0.xyz, R0, c[3].z;
ADD R3.xyz, -R0, R2;
TEX R0.w, R3, texture[0], 2D;
ADD R0.w, R3.z, -R0;
CMP R2.xyz, R0.w, R2, R3;
MUL R0.xyz, R0, c[3].z;
ADD R3.xyz, -R0, R2;
TEX R0.w, R3, texture[0], 2D;
ADD R0.w, R3.z, -R0;
CMP R2.xyz, R0.w, R2, R3;
MUL R0.xyz, R0, c[3].z;
ADD R3.xyz, -R0, R2;
TEX R0.w, R3, texture[0], 2D;
ADD R0.w, R3.z, -R0;
CMP R2.xyz, R0.w, R2, R3;
MUL R0.xyz, R0, c[3].z;
ADD R3.xyz, -R0, R2;
TEX R0.w, R3, texture[0], 2D;
ADD R0.w, R3.z, -R0;
CMP R2.xyz, R0.w, R2, R3;
MUL R0.xyz, R0, c[3].z;
ADD R3.xyz, -R0, R2;
TEX R0.w, R3, texture[0], 2D;
ADD R0.z, R3, -R0.w;
CMP R1.zw, R0.z, R2.xyxy, R3.xyxy;
DP3 R0.w, fragment.texcoord[3], fragment.texcoord[3];
RSQ R0.z, R0.w;
MAD R3.xy, -R0, c[3].z, R1.zwzw;
MUL R2.xyz, R0.z, fragment.texcoord[3];
MAD R1.xyz, -R1.x, fragment.texcoord[2], R2;
DP3 R1.w, R1, R1;
RSQ R1.w, R1.w;
MUL R1.xyz, R1.w, R1;
MAX R1.w, R2.z, c[3];
TEX R0.xyz, R3, texture[0], 2D;
ADD R0.xyz, R0, -c[3].z;
DP3 R0.w, R0, R0;
RSQ R0.w, R0.w;
MUL R0.xyz, R0.w, R0;
DP3_SAT R0.w, R0, R1;
POW R1.x, R0.w, c[2].w;
DP3_SAT R0.w, R2, R0;
MUL R0.xyz, R1.x, c[2];
TEX R1.xyz, R3, texture[1], 2D;
MUL R2.xyz, R1, c[1];
MAD R0.xyz, R2, R0.w, R0;
ADD R1.w, -R1, c[3].x;
MAD R0.w, -R1, R1, c[3].x;
MUL R0.xyz, R0.w, R0;
MAD result.color.xyz, R1, c[0], R0;
MOV result.color.w, c[3].x;
END
# 103 instructions, 4 R-regs
