///////////////////
// IN/OUT structures

//#include "UNshaderFunctions.h"

float3x3 mult(float i_float, float3x3 i_matrix)
{
float3x3 i_result;
i_result._m00 = i_matrix._m00 * i_float;
i_result._m01 = i_matrix._m01 * i_float;
i_result._m02 = i_matrix._m02 * i_float;

i_result._m10 = i_matrix._m10 * i_float;
i_result._m11 = i_matrix._m11 * i_float;
i_result._m12 = i_matrix._m12 * i_float;

i_result._m20 = i_matrix._m20 * i_float;
i_result._m21 = i_matrix._m21 * i_float;
i_result._m22 = i_matrix._m22 * i_float;
return i_matrix;
}

struct a2v 
{
	float4 pos       : POSITION;
	float3 normal    : NORMAL;
	float2 texcoord  : TEXCOORD0;
	float4 tangent   : TEXCOORD1;
	float4 binormal  : TEXCOORD2;
	float2 curvature : TEXCOORD3;
};

struct a2v_mesh 
{
	float4 pos				: POSITION;
	float3 normal			: NORMAL;
	float2 texcoord			: TEXCOORD0;
	float4 weight			: TEXCOORD1;
	float4 matrixindices	: TEXCOORD2;
};

struct v2f
{
	float4 hpos : POSITION;
	float4 color : COLOR0;
	float2 texcoord : TEXCOORD0;
	float3 vpos : TEXCOORD1;
	float3 normal : TEXCOORD2;
	float3 tangent : TEXCOORD3;
	float3 binormal : TEXCOORD4;
	float3 view : TEXCOORD5;
	float3 scale : TEXCOORD6;
};

struct v2f_blur
{
	float4 hpos : POSITION;
	float2 texcoord : TEXCOORD0;
};	

struct f2s
{	
	float4 color : COLOR;
};

struct f2s_mrt
{	
	float3 color0 : COLOR0;	// normal
	float3 color1 : COLOR1;	// diffuse
	float4 color2 : COLOR2;	// specular
#ifndef NV_RENDER_DEPTH_TEXTURE
	float3 color3 : COLOR3;	// depth
#endif
};

////////////////////////////////
// Global Variables
//uniform float3x3 rotationMatrices[16];
//uniform float3 translationVectors[16];

bool depth_bias = true;
float4 constant = { 1, 3, 0, 0 };

////////////////////////////////
// Color3ub to Float to Color3ub

float color_to_float(float3 color)
{
	const float3 byte_to_float=float3(1,1.0/256.0,1.0/(256.0*256.0));
	return dot(color,byte_to_float);
}

float3 float_to_color(in float f)
{
	float3 color;
	f*=256;
	color.x=floor(f);
	f=(f-color.x)*256;
	color.y=floor(f);
	color.z=f-color.y;
	color.xy*=0.00390625;
	return color;
}

////////////////////////////
// Blur used for scene bloom

#define NUMPOINTS 7

f2s blur(
	v2f_blur IN,
	uniform sampler2D texture:TEXUNIT0,
	uniform float2 disp[NUMPOINTS])
{
	f2s OUT;

	float4 tex=float4(0,0,0,1);
	for( int i=0;i<NUMPOINTS;i++ )
	{
		float3 t=f3tex2D(texture,IN.texcoord+disp[i]);
		tex.xyz+=dot(t,t);
	}
	tex*=0.5/NUMPOINTS;

	OUT.color=tex;

	return OUT;
}

// setup ray pos and dir based on view vector
// and apply depth bias and depth factor
void setup_ray(v2f IN,out float3 p,out float3 v)
{
	float depth = 4.1;
	p = float3(IN.texcoord,0);
	v = normalize(IN.view);
	
	v.z = abs(v.z);

	if (depth_bias)
	{
		float db = 1.0-v.z; db*=db; db*=db; db=1.0-db*db;
		v.xy *= db;
	}
	
	v.xy *= depth;
}

///////////////////////////
// Transforms to view space

v2f view_space(
	a2v IN,
	uniform float tile,				// tile factor
	uniform float depth)			// depth factor
{
	v2f OUT;

	// vertex position in object space
	float4 pos=float4(IN.pos.x,IN.pos.y,IN.pos.z,1.0);

	// vertex position in clip space
	OUT.hpos=mul(glstate.matrix.mvp,pos);

	// copy color and texture coordinates
	OUT.texcoord=IN.texcoord.xy*tile;

	// compute modelview rotation only part
	float3x3 modelviewrot=float3x3(glstate.matrix.modelview[0]);

	// vertex position in view space (with model transformations)
	OUT.vpos=mul(glstate.matrix.modelview[0],pos).xyz;

	// tangent vector in view space
	float3 tangent=mul(modelviewrot,IN.tangent.xyz);
	OUT.tangent=tangent;

	// binormal vector in view space
	float3 binormal=mul(modelviewrot,IN.binormal.xyz);
	OUT.binormal=binormal;

	// normal vector in view space
	float3 normal=mul(modelviewrot,IN.normal);
	OUT.normal=normal;

	// tangent space matrix
	float3x3 tangentspace=float3x3(tangent,binormal,normal);
	OUT.view=mul(tangentspace,OUT.vpos);
	OUT.view.z=-OUT.view.z;

	// scale factor
	OUT.scale=float3(IN.tangent.w,IN.binormal.w,depth)/tile;

	return OUT;
}

///////////////////////////
// Transforms to mesh view space

typedef packed float3x3 MatrixArray;

v2f view_mesh(
	a2v_mesh IN,
	uniform float4x4 meshmatrix,
	uniform float tile,				// tile factor
	uniform float depth,
	uniform MatrixArray rotationMatrices[56]
	/*uniform float3 translationVectors[56]*/)			// depth factor
{
	v2f OUT;

	// vertex position in object space
	float4 pos=float4(IN.pos.x,IN.pos.y,IN.pos.z,1.0);

	// vertex position in clip space
	//pos=mul(meshmatrix,pos);
	//float4 transpos;
	
	//transpos += mul(meshmatrix, pos);
	//float4x4 rotmatrix;
	//rotmatrix = meshmatrix * glstate.matrix.mvp;
	//OUT.hpos = mul(rotmatrix, pos);
    
    // Real Verts in original state
    //OUT.hpos = mul(glstate.matrix.mvp,pos);
	
    //OUT.hpos = glstate.matrix.mvp * meshmatrix;
	//OUT.hpos=mul(glstate.matrix.mvp,pos);
	//OUT.hpos=mul(meshmatrix,OUT.hpos);
	//OUT.hpos = pos;
	
	float3 pos3=float3(IN.pos.x,IN.pos.y,IN.pos.z);
	float4 matrixind = IN.matrixindices * 3;

	float3x3 totalRotation = rotationMatrices[int(matrixind.w)];
    //float3 transformedPosition = IN.weight.x * translationVectors[int(IN.matrixindices.x)];

	totalRotation += rotationMatrices[int(matrixind.z)];
	//transformedPosition += IN.weight.y * translationVectors[int(IN.matrixindices.y)];

	totalRotation += rotationMatrices[int(matrixind.y)];
	//transformedPosition += IN.weight.z * translationVectors[int(IN.matrixindices.z)];

	totalRotation += rotationMatrices[int(matrixind.x)];
	//transformedPosition += IN.weight.w * translationVectors[int(IN.matrixindices.w)];


    float3 position = mul(totalRotation, pos3);
    OUT.hpos = mul(glstate.matrix.mvp, float4(position, 1.0));

	//OUT.hpos += mul(glstate.matrix.mvp, IN.pos);
	//OUT.texcoord = IN.texcoord;

	// copy color and texture coordinates
	//OUT.texcoord=IN.texcoord.xy*tile;
	
	// compute modelview rotation only part
	//float3x3 modelviewrot=float3x3(glstate.matrix.modelview[0]);

	// vertex position in view space (with model transformations)
	//OUT.vpos=mul(glstate.matrix.modelview[0],pos).xyz;

	// tangent vector in view space
	//float3 tangent=mul(modelviewrot,IN.tangent.xyz);
	//OUT.tangent=tangent;

	// binormal vector in view space
	//float3 binormal=mul(modelviewrot,IN.binormal.xyz);
	//OUT.binormal=binormal;

	// normal vector in view space
	//float3 normal=mul(modelviewrot,IN.normal);
	//OUT.normal=normal;

	// tangent space matrix
	//float3x3 tangentspace=float3x3(tangent,binormal,normal);
	//OUT.view=mul(tangentspace,OUT.vpos);
	//OUT.view.z=-OUT.view.z;

	// scale factor
	//OUT.scale=float3(IN.tangent.w,IN.binormal.w,depth)/tile;

	// vertex position in view space (with model transformations)
	//OUT.vpos=mul(glstate.matrix.modelview[0],pos).xyz;

    //OUT.hpos = mul(glstate.matrix.modelview[0], float4(transformedPosition, 1.0));
    
    //OUT.hpos = IN.pos;
    
    //OUT.hpos.x = 5;

	return OUT;
}

/////////////////
// Normal Mapping

f2s_mrt mrt_normal(
	v2f IN,
	uniform sampler2D relieftex:TEXUNIT0,	// relief texture map 
	uniform sampler2D colortex:TEXUNIT1,	// color texture map 
	uniform float4 diffuse,		// diffuse color
	uniform float4 specular,	// specular color
	uniform float2 planes)		// near and far plane information
{
	f2s_mrt OUT;

	// relief map
	float3 normal=f3tex2D(relieftex,IN.texcoord);

	// color map
	float3 color=f3tex2D(colortex,IN.texcoord);

	// transform normal to world space
	normal-=0.5;
	normal=normalize(normal.x*IN.tangent+
		normal.y*IN.binormal+normal.z*IN.normal);

	// convert normal back to [0,1] color space
	normal=normal*0.5+0.5;

	OUT.color0=normal;
	OUT.color1=color*diffuse.xyz;
	OUT.color2=specular;

#ifndef NV_RENDER_DEPTH_TEXTURE
	float d=((planes.x*IN.vpos.z+planes.y)/-IN.vpos.z);
	OUT.color3=float_to_color(d);
#endif

	return OUT;
}

f2s_mrt mrt_normal_mesh(v2f IN, uniform sampler2D colortex:TEXUNIT0)
{
	f2s_mrt OUT;

	// relief map
	//float3 normal=f3tex2D(relieftex,IN.texcoord);

	// color map
	//float3 color=f3tex2D(colortex,IN.texcoord);

	// transform normal to world space
	//normal-=0.5;
	//normal=normalize(normal.x*IN.tangent+
	//	normal.y*IN.binormal+normal.z*IN.normal);

	// convert normal back to [0,1] color space
	//normal=normal*0.5+0.5;

	OUT.color0=f3tex2D(colortex,IN.texcoord);
	OUT.color1=f3tex2D(colortex,IN.texcoord);
	OUT.color2=float4(0,0.7,0.3,0);//specular;

	return OUT;
}

/////////////////
// Relief Mapping

// fpo linear serach
//
// step equal intervals until 
// finding a point inside object
void ray_intersect_linear(
      in sampler2D relieftex,
      inout float3 p, 
      inout float3 v)
{
	const int search_steps=10;

	v/=search_steps;

	for( int i=0;i<search_steps-1;i++ )
	{
		float4 t=tex2D(relieftex,p.xy);
		if (p.z<t.w)
			p+=v;
	}
}

// fpo binary search
//
// serach around point for a closer
// intersection walking half distance
// at each step
void ray_intersect_binary(
      in sampler2D relieftex,
      inout float3 p, 
      inout float3 v)
{
	const int search_steps=5;
   
	for( int i=0;i<search_steps;i++ )
	{
		v*=0.5;
		float4 t=tex2D(relieftex,p.xy);
		if (p.z<t.w)
			p+=2*v;
		p-=v;
	}
}

f2s_mrt mrt_relief(
	v2f IN,
	uniform sampler2D relieftex:TEXUNIT0,	// relief texture map 
	uniform sampler2D colortex:TEXUNIT1,	// color texture map 
	uniform float4 diffuse,			// diffuse color
	uniform float4 specular,		// specular color
	uniform float2 planes)			// near and far plane information
{
	f2s_mrt OUT;

	// view vector in tangent space
	float3 v=normalize(IN.view);

#ifdef DEPTH_BIAS
	// depth bias
	float s=1.0-v.z; s=1.0-s*s; IN.scale.z*=s;
#endif

	// scale view into texture space scale
	v*=IN.scale.z/(IN.scale*v.z);

	// ray intersect depth map
	float3 p=float3(IN.texcoord,0);
	ray_intersect_linear(relieftex,p,v);
	ray_intersect_binary(relieftex,p,v);

	// get normal and color from textures
	float3 normal=f3tex2D(relieftex,p.xy);
	float3 color=f3tex2D(colortex,p.xy);

	// expand normal into object space
	normal-=0.5;
	normal=normalize(normal.x*IN.tangent+
		normal.y*IN.binormal+normal.z*IN.normal);

	// convert normal back to [0,1] color space
	normal=normal*0.5+0.5;

	// output mrt colors
	OUT.color0=normal;
	OUT.color1=color*diffuse.xyz;
	OUT.color2=specular;

#ifndef NV_RENDER_DEPTH_TEXTURE
	// corrected depth into a separate color buffer
	float3 pos=IN.vpos+normalize(IN.vpos)*p.z*IN.scale.z/IN.view.z;
	float d=((planes.x*pos.z+planes.y)/-pos.z);
	OUT.color3=float_to_color(d);
#endif

	//OUT.color3=float3(1,1,1);

	return OUT;
}

///////////////
// MRT lighting

f2s mrt_light(
	v2f IN,
	uniform sampler2D normal_map:TEXUNIT0,		// normal map 
	uniform sampler2D diffuse_map:TEXUNIT1,		// diffuse map 
	uniform sampler2D specular_map:TEXUNIT2,	// specular map 
	uniform sampler2D depth_map:TEXUNIT3,		// zbuffer depth map
	uniform float4 lightpos,		// light position
	uniform float3 lightcolor,		// light color
	uniform float2 planes)			// near and far plane information
{
	f2s OUT;

	// depth
#ifdef NV_RENDER_DEPTH_TEXTURE
	float depth=f1tex2D(depth_map,IN.texcoord);
#else
	float depth=color_to_float(f3tex2D(depth_map,IN.texcoord));
#endif

	// view dir
	float3 view=normalize(IN.vpos);

	// position
	float3 pos;
	pos.z=-planes.y/(planes.x+depth);
	pos.xy=view.xy/view.z*pos.z;

	// normal
	float3 normal=f3tex2D(normal_map,IN.texcoord)-0.5;
	float len=length(normal);
	if (len>0.1)
		normal/=len;
	else
		normal=0;
	
	// colors
	float3 diffuse=f3tex2D(diffuse_map,IN.texcoord);
	float4 specular=f4tex2D(specular_map,IN.texcoord);

	// ligth dir
	float3 light=lightpos.xyz-pos;
	float att=length(light);
	light/=att;
	att=saturate(1.0-att/lightpos.w);

	// compute diffuse and specular terms
	float diff=saturate(dot(light,normal.xyz));
	float spec=saturate(dot(normalize(view+light),normal.xyz));

	// diffuse and specular lighting
	float3 lighting=diffuse.xyz*diff + 
			specular.xyz*pow(spec,specular.w*255.0);

	OUT.color.xyz=att*lightcolor*lighting;

	return OUT;
}

/////////////////
// MRT anti-alias

f2s anti_alias(
	v2f IN,
	uniform sampler2D normal_map:TEXUNIT0,	// normal map
	uniform sampler2D color_map:TEXUNIT1,	// color map
	uniform float2 pixel_size,
	uniform float weight)
{
	f2s OUT;

	const float2 delta[8]=
	{ 
		float2(-1,1),float2(1,-1),float2(-1,1),float2(1,1), 
		float2(-1,0),float2(1,0),float2(0,-1),float2(0,1)
	};

	float4 tex=f4tex2D(normal_map,IN.texcoord);
	float factor=0.0f;

	for( int i=0;i<4;i++ )
	{
		float4 t=f4tex2D(normal_map,IN.texcoord+delta[i]*pixel_size);
		t-=tex;
		factor+=dot(t,t);
	}
	factor=min(1,factor)*weight;

//	debug: show edges to be anti-aliased
//	OUT.color=float4(factor,factor,factor,1);
//	return OUT;

	float4 color=float4(0,0,0,0);

	for( int i=0;i<8;i++ )
		color+=f4tex2D(color_map,IN.texcoord+delta[i]*pixel_size*factor);
	color+=2*f4tex2D(color_map,IN.texcoord);

	OUT.color=color*(1.0/10);

	return OUT;
}

/*// slowest, but best quality
float intersect_cone_exact(in vec2 dp, in vec3 ds)
	{
	// minimum feature size parameter
	float w = 1.0 / texsize;
	// the "not Z" component of the direction vector
	// (requires that the vector ds was normalized!)
	float iz = sqrt(1.0-ds.z*ds.z);
	// my starting location (is at z=1,
	// and moving down so I don't have
	// to invert height maps)
	// texture lookup
	vec4 t;
	// scaling distance along vector ds
	float sc=0.0;
	
	// the ds.z component is positive!
	// (headed the wrong way, since
	// I'm using heightmaps)
	
	// find the starting location and height
	t=tex2D(stepmap,dp);
	while (1.0-ds.z*sc > t.r)
		{
		// right, I need to take one step.
		// I use the current height above the texture,
		// and the information about the cone-ratio
		// to size a single step. So it is fast and
		// precise! (like a coneified version of
		// "space leaping", but adapted from voxels)
		sc += w + (1.0-ds.z*sc-t.r) / (ds.z + iz/(t.g*t.g));
		// find the new location and height
		t=tex2D(stepmap,dp+ds.xy*sc);
		}
	// reduce one step
	sc -= w;
	
	// return the vector length needed to hit the height-map
	return (sc);
	}

// the super fast version
// (change number of iterations at run time)
float intersect_cone_fixed(in vec2 dp, in vec3 ds)
	{
	// the "not Z" component of the direction vector
	// (requires that the vector ds was normalized!)
	float iz = sqrt(1.0-ds.z*ds.z);
	// my starting location (is at z=1,
	// and moving down so I don't have
	// to invert height maps)
	// texture lookup (and initialized to starting location)
	vec4 t;
	// scaling distance along vector ds
	float sc;

	// the ds.z component is positive!
	// (headed the wrong way, since
	// I'm using heightmaps)

	// find the initial location and height
	t=tex2D(stepmap,dp);
	// right, I need to take one step.
	// I use the current height above the texture,
	// and the information about the cone-ratio
	// to size a single step. So it is fast and
	// precise! (like a coneified version of
	// "space leaping", but adapted from voxels)
	sc = (1.0-ds.z*sc-t.r) / (ds.z + iz/(t.g*t.g));

	// and repeat a few (4x) times
	t=tex2D(stepmap,dp+ds.xy*sc);
	sc += (1.0-ds.z*sc-t.r) / (ds.z + iz/(t.g*t.g));
	t=tex2D(stepmap,dp+ds.xy*sc);
	sc += (1.0-ds.z*sc-t.r) / (ds.z + iz/(t.g*t.g));
	t=tex2D(stepmap,dp+ds.xy*sc);
	sc += (1.0-ds.z*sc-t.r) / (ds.z + iz/(t.g*t.g));
	t=tex2D(stepmap,dp+ds.xy*sc);
	sc += (1.0-ds.z*sc-t.r) / (ds.z + iz/(t.g*t.g));
	// and another five!
	t=tex2D(stepmap,dp+ds.xy*sc);
	sc += (1.0-ds.z*sc-t.r) / (ds.z + iz/(t.g*t.g));
	t=tex2D(stepmap,dp+ds.xy*sc);
	sc += (1.0-ds.z*sc-t.r) / (ds.z + iz/(t.g*t.g));
	t=tex2D(stepmap,dp+ds.xy*sc);
	sc += (1.0-ds.z*sc-t.r) / (ds.z + iz/(t.g*t.g));
	t=tex2D(stepmap,dp+ds.xy*sc);
	sc += (1.0-ds.z*sc-t.r) / (ds.z + iz/(t.g*t.g));
	t=tex2D(stepmap,dp+ds.xy*sc);
	sc += (1.0-ds.z*sc-t.r) / (ds.z + iz/(t.g*t.g));

	// return the vector length needed to hit the height-map
	return (sc);
	}
	
// pretty fast version
// (and you can do LOD by changing "conesteps" based on size/distance, etc.)
float intersect_cone_loop(in vec2 dp, in vec3 ds)
	{
	// the "not Z" component of the direction vector
	// (requires that the vector ds was normalized!)
	float iz = sqrt(1.0-ds.z*ds.z);
	// my starting location (is at z=1,
	// and moving down so I don't have
	// to invert height maps)
	// texture lookup (and initialized to starting location)
	vec4 t;
	// scaling distance along vector ds
	float sc=0.0;
	
	//t=tex2D(stepmap,dp);
	//return (max(0.0,-(t.b-0.5)*ds.x-(t.a-0.5)*ds.y));
	
	// the ds.z component is positive!
	// (headed the wrong way, since
	// I'm using heightmaps)
	
	// adaptive (same speed as it averages the same # steps)
	//for (int i = int(float(conesteps)*(0.5+iz)); i > 0; --i)
	// fixed
	for (int i = conesteps; i > 0; --i)
		{
		// find the new location and height
		t=tex2D(stepmap,dp+ds.xy*sc);
		// right, I need to take one step.
		// I use the current height above the texture,
		// and the information about the cone-ratio
		// to size a single step. So it is fast and
		// precise! (like a coneified version of
		// "space leaping", but adapted from voxels)
		sc += (1.0-ds.z*sc-t.r) / (ds.z + iz/(t.g*t.g));
		}
		
	// return the vector length needed to hit the height-map
	return (sc);
	}*/
	
	
// ray intersect depth map using binary cone space leaping
// depth value stored in alpha channel (black is at object surface)
// and cone ratio stored in blue channel
void ray_intersect_relaxedcone(
	sampler2D relaxedcone_relief_map,
	inout float3 p,
	inout float3 v)
{
	const int cone_steps=15;
	const int binary_steps=8;
	
	float3 p0 = p;

	v /= v.z;
	
	float dist = length(v.xy);
	
	for( int i=0;i<cone_steps;i++ )
	{
		float4 tex = tex2D(relaxedcone_relief_map, p.xy);

		float height = saturate(tex.w - p.z);
		
		float cone_ratio = tex.z;
		
		p += v * (cone_ratio * height / (dist + cone_ratio));
	}

	v *= p.z*0.5;
	p = p0 + v;

	for( int i=0;i<binary_steps;i++ )
	{
		float4 tex = tex2D(relaxedcone_relief_map, p.xy);
		v *= 0.5;
		if (p.z<tex.w)
			p+=v;
		else
			p-=v;
	}
}

// do normal mapping using given texture coordinate
// tangent space phong lighting with optional border clamp
// normal X and Y stored in red and green channels
float4 normal_mapping(
	sampler2D color_map,
	sampler2D normal_map,
	float2 texcoord,
	v2f IN)
{
	// color map
	float4 color = f4tex2D(color_map,texcoord);
	
	// normal map
	float4 normal = f4tex2D(normal_map,texcoord);
	normal.xy = 2*normal.xy - 1;
	normal.y = -normal.y;
	normal.z = sqrt(1.0 - dot(normal.xy,normal.xy));

	// light and view in tangent space
	//float3 l = normalize(IN.light);
	float3 l = float3(1,5,0);
	
	float3 v = normalize(IN.view);

	// compute diffuse and specular terms
	float diff = saturate(dot(l,normal.xyz));
	float spec = saturate(dot(normalize(l-v),normal.xyz));

	// attenuation factor
	float att = 1.0 - max(0,l.z); 
	att = 1.0 - att*att;

	// border clamp
	bool border_clamp = false;
	float tile = 1;
	float3 ambient = float3(0.2,0.2,0.2);
	float3 diffuse = float3(1,1,1);
	float3 specular = float3(0.75,0.75,0.75);
	float shine = 32.0;
	
	float alpha=1;
	if (border_clamp)
	{
		if (texcoord.x<0) alpha=0;
		if (texcoord.y<0) alpha=0;
		if (texcoord.x>tile) alpha=0;
		if (texcoord.y>tile) alpha=0;
	}
	
	// compute final color
	float4 finalcolor;
	finalcolor.xyz = ambient*color.xyz +
		att*(color.xyz*diffuse*diff +
		specular*pow(spec,shine));
	finalcolor.w = alpha;
	return finalcolor;
}

///////////////
// Relaxed Cone Step

f2s_mrt mrt_relief_relaxed(
	v2f IN,
	uniform sampler2D relieftex:TEXUNIT0,	// relief texture map 
	uniform sampler2D colortex:TEXUNIT1,	// color texture map 
	uniform float4 diffuse,			// diffuse color
	uniform float4 specular,		// specular color
	uniform float2 planes)			// near and far plane information
{
	f2s_mrt OUT;
	float3 p,v;
	
	setup_ray(IN,p,v);

	ray_intersect_relaxedcone(relieftex,p,v);
	
	float4 outcolor = normal_mapping(colortex,relieftex,p.xy,IN);
	float3 finalcolor = float3(outcolor.xyz);

	OUT.color0 = finalcolor;
	OUT.color1 = finalcolor;
	OUT.color2 = outcolor;

	return OUT;
}

void acTransmitVerts(void)
{
#if 0
	CC.vertinc = 0;
	for (CC.k = 0; CC.k < veclayer[0].vecPxGrid.size(); CC.k++) /// First Layer
		{
		for (CC.v = 0; CC.v < veclayer[0].vecPxGrid[CC.k]->nverts; CC.v += 3)
			{
			veclayer[0].vecPxGrid[CC.k]->nxvec[CC.v] = PxVec3 (veclayer[0].vecvert[veclayer[0].vecPxGrid[CC.k]->vecPxFace[CC.vertinc].m_v1][0], veclayer[0].vecvert[veclayer[0].vecPxGrid[CC.k]->vecPxFace[CC.vertinc].m_v1][1], veclayer[0].vecvert[veclayer[0].vecPxGrid[CC.k]->vecPxFace[CC.vertinc].m_v1][2]);
			veclayer[0].vecPxGrid[CC.k]->nxvec[CC.v+1] = PxVec3 (veclayer[0].vecvert[veclayer[0].vecPxGrid[CC.k]->vecPxFace[CC.vertinc].m_v2][0], veclayer[0].vecvert[veclayer[0].vecPxGrid[CC.k]->vecPxFace[CC.vertinc].m_v2][1], veclayer[0].vecvert[veclayer[0].vecPxGrid[CC.k]->vecPxFace[CC.vertinc].m_v2][2]);
			veclayer[0].vecPxGrid[CC.k]->nxvec[CC.v+2] = PxVec3 (veclayer[0].vecvert[veclayer[0].vecPxGrid[CC.k]->vecPxFace[CC.vertinc].m_v3][0], veclayer[0].vecvert[veclayer[0].vecPxGrid[CC.k]->vecPxFace[CC.vertinc].m_v3][1], veclayer[0].vecvert[veclayer[0].vecPxGrid[CC.k]->vecPxFace[CC.vertinc].m_v3][2]);
			}
		}

	for (CC.layertrav = 1; CC.layertrav < veclayer.size(); CC.layertrav++) /// Other Layers
		{
		for (CC.k = 0; CC.k < veclayer[CC.layertrav].vecPxGrid.size(); CC.k++) /// First Layer
			{
			for (CC.v = 0; CC.v < veclayer[CC.layertrav].vecPxGrid[CC.k]->vecPxFace.size(); CC.v++)
				{
				veclayer[CC.layertrav].vecPxGrid[CC.k]->nxvec[CC.v] = 
				veclayer[CC.layertrav].vecPxGrid[CC.k]->nxvec[CC.v+1] = 
				veclayer[CC.layertrav].vecPxGrid[CC.k]->nxvec[CC.v+2] = 
				}

			for (CC.v = 0; CC.v < veclayer[CC.layertrav].vecPxGrid[CC.k]->vecPxSeal.size(); CC.v++)
				{
				veclayer[CC.layertrav].vecPxGrid[CC.k]->nxvec[CC.vertinc] = 
				veclayer[CC.layertrav].vecPxGrid[CC.k]->nxvec[CC.vertinc+1] = 
				veclayer[CC.layertrav].vecPxGrid[CC.k]->nxvec[CC.vertinc+2] = 
				}
			}
		}
#endif
}

////////////////////////////////////////////////////////////////////////////////
/**
* Copyright (C) 2007 Ragecomm (http://www.ragecomm[2]om) and Piotr Obrzut
*
* This source is proprietary, and cannot be used, in part or in full without
* the express permission of Ragecomm and/or the original author. Ragecomm and
* the original author retain */#include "pch.h"/*the rights to use, modify, and/or relicense this
* code without notice.
*/
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
/**
* @file icShapesHelper[2]pp
*
* @author Piotr Obrzut (piotr_obrzut@o2.pl)
*
* @brief 
*/
////////////////////////////////////////////////////////////////////////////////
#include "icConstants.h"
#include <nvsg/Triangles.h>
#include <nvsg/Quads.h>
#include <nvsg/VertexAttributeSet.h>
#include <nvmath/Vec2f.h>
#include <nvsg/Face.h>
#include "icShapesHelper.h"

using namespace nvmath;
using namespace nvsg;
using namespace nvutil;

nvsg::TrianglesHandle *icShapesHelper::createCapsuleGeometry (float l, float r, uint sides)
{
  const uint n = sides * 4;
  const size_t numVertices = n * 2 + (sides + 1) * (n + 1) * 2 * 2;
  const size_t numTriangles = (n) * 4 + (sides + 1) * (n) * 4 * 2;
  l *= 0.5;
  float a = float(PI*2.0)/float(n);
  float sa = (float) sin(a);
  float ca = (float) cos(a);

  Vec2f *texels = new Vec2f [numVertices];
  Vec3f *vertices = new Vec3f [numVertices];
  Vec3f *normals = new Vec3f [numVertices];
  Face3 *triangles = new Face3[numTriangles];

  size_t vId = 0;
  size_t tId = 0;
  // cylinder body
  float ny = 1, nz = 0;
  for (uint i = 0; i < n; i++)
  {
    normals[vId] = Vec3f (ny, 0, nz);
    vertices[vId] = Vec3f (ny * r, l, nz * r); 
    size_t v1 = vId;
    vId++;

    normals[vId] = Vec3f (0, ny, nz);
    vertices[vId] = Vec3f (ny * r, -l, nz * r); 
    size_t v2 = vId;
    vId++;

    float tmp =  ca * ny - sa * nz;
    nz = sa*ny + ca*nz;
    ny = tmp;

    if (i > 0)
    {
      triangles[tId][0] = v2; triangles[tId][1] = v1, triangles[tId][2] = v1 - 2; tId++;
      triangles[tId][0] = v1 - 1; triangles[tId][1] = v2, triangles[tId][2] = v1; tId++;
      triangles[tId][0] = v1 - 2; triangles[tId][1] = v1 - 1, triangles[tId][2] = v2; tId++;
      triangles[tId][0] = v1; triangles[tId][1] = v1 - 2, triangles[tId][2] = v1 - 1; tId++;
      if (i == n - 1)
      {
        triangles[tId][0] = 1; triangles[tId][1] = 0, triangles[tId][2] = v1; tId++;
        triangles[tId][0] = v2; triangles[tId][1] = v2, triangles[tId][2] = 1; tId++;
        triangles[tId][0] = v1; triangles[tId][1] = v2, triangles[tId][2] = 1; tId++;
        triangles[tId][0] = 0; triangles[tId][1] = v1, triangles[tId][2] = v2; tId++;
      }
    }
  }

  // top cap
  float start_nx = 0;
  float start_ny = 1;
  for (uint j = 0; j <= sides; j++) 
  {
    float start_nx2 =  ca*start_nx + sa*start_ny;
    float start_ny2 = -sa*start_nx + ca*start_ny;
    float nx = start_nx; ny = start_ny; nz = 0;
    float nx2 = start_nx2, ny2 = start_ny2, nz2 = 0;
    for (uint i = 0; i <= n; i++) 
    {
      normals[vId] = Vec3f (ny2, nx2, nz2);
      vertices[vId] = Vec3f (ny2*r, l+nx2*r, nz2*r); 
      size_t v1 = vId;
      vId++;

      normals[vId] = Vec3f (ny, nx, nz);
      vertices[vId] = Vec3f (ny*r, l+nx*r, nz*r); 
      size_t v2 = vId;
      vId++;

      float tmp = ca*ny - sa*nz;
      nz = sa*ny + ca*nz;
      ny = tmp;
      tmp = ca*ny2- sa*nz2;
      nz2 = sa*ny2 + ca*nz2;
      ny2 = tmp;

      if (i > 0)
      {
        triangles[tId][0] = v2; triangles[tId][1] = v1; triangles[tId][2] = v1 - 2; tId++;
        triangles[tId][0] = v1 - 1; triangles[tId][1] = v2; triangles[tId][2] = v1; tId++;
        triangles[tId][0] = v1 - 2; triangles[tId][1] = v1 - 1; triangles[tId][2] = v2; tId++;
        triangles[tId][0] = v1; triangles[tId][1] = v1 - 2; triangles[tId][2] = v1 - 1; tId++;
      }
    }
    start_nx = start_nx2;
    start_ny = start_ny2;
  }

  // second cap
  start_nx = 0;
  start_ny = 1;
  for (uint j = 0; j <= sides; j++) 
  {
    float start_nx2 =  ca*start_nx - sa*start_ny;
    float start_ny2 = sa*start_nx + ca*start_ny;
    float nx = start_nx; ny = start_ny; nz = 0;
    float nx2 = start_nx2, ny2 = start_ny2, nz2 = 0;
    for (uint i = 0; i <= n; i++) 
    {
      normals[vId] = Vec3f (ny, nx, nz);
      vertices[vId] = Vec3f (ny*r, -l+nx*r, nz*r); 
      size_t v1 = vId;
      vId++;

      normals[vId] = Vec3f (ny2, nx2, nz2);
      vertices[vId] = Vec3f (ny2*r, -l+nx2*r, nz2*r); 
      size_t v2 = vId;
      vId++;

      float tmp = ca*ny - sa*nz;
      nz = sa*ny + ca*nz;
      ny = tmp;
      tmp = ca*ny2 - sa*nz2;
      nz2 = sa*ny2 + ca*nz2;
      ny2 = tmp;

      if (i > 0)
      {
        triangles[tId][0] = v2; triangles[tId][1] = v1, triangles[tId][2] = v1 - 2; tId++;
        triangles[tId][0] = v1 - 1; triangles[tId][1] = v2, triangles[tId][2] = v1; tId++;
        triangles[tId][0] = v1 - 2; triangles[tId][1] = v1 - 1, triangles[tId][2] = v2; tId++;
        triangles[tId][0] = v1; triangles[tId][1] = v1 - 2, triangles[tId][2] = v1 - 1; tId++;
      }
    }
    start_nx = start_nx2;
    start_ny = start_ny2;
  }

  VertexAttributeSetHandle *vasHdl = CreateHandle (VertexAttributeSetHandle);
  {
    WritableObject<VertexAttributeSet> vas (vasHdl);
    vas->setVertices (vertices, numVertices);
    vas->setNormals (normals, numVertices);
    vas->setTexCoords (0, 2, texels->getPtr (), numVertices);
  }
  TrianglesHandle *trisHdl = CreateHandle (TrianglesHandle);
  {
    WritableObject<Triangles> tris (trisHdl);
    tris->setVertexAttributeSet (vasHdl);
    tris->setFaces (triangles, numTriangles);
  }
  
  delete[] texels;
  delete[] triangles;
  delete[] normals;
  delete[] vertices;

  return trisHdl;
}
TrianglesHandle *icShapesHelper::createSphereGeometry (nvmath::Vec3f size, uint numRimVertices, bool reversed)
{
  size_t numVertices = numRimVertices + ((numRimVertices / 2 - 1) * numRimVertices) * 2 + 2;
  size_t numTriangles = numRimVertices * (numRimVertices / 2 - 1) * 4 + 2 * numRimVertices;
  float radius = 1.0f;

  uint *prevVerticesT = new uint[numVertices];
  uint *newVerticesT = new uint[numVertices];
  uint *prevVerticesB = new uint[numVertices];
  uint *newVerticesB = new uint[numVertices];
  Face3 *triangles = new Face3[numTriangles];

  static const float twoPI = 2 * PI;
  
  Vec2f *texels = new Vec2f [numVertices];
  Vec3f *vertices = new Vec3f [numVertices];
  Vec3f *normals = new Vec3f [numVertices];

  // Number of degrees between layers.
  float radiusStep = 180.0f / numRimVertices;
  float vertRadius = radius;

  uint currVertID = 0;

  // Generate the first series of vertices (the outer circle).
  // Calculate u,v for them.
  for (uint i = 0; i < numRimVertices; i++)
  {
    float newRadius = radius;
    float newHeight = 0.0f;
    float angle = i * 2.0f * radiusStep * twoPI / 360.0f;
    vertices[i] = Vec3f (newRadius * (float) cos (angle), newHeight, newRadius * (float) sin (angle));
    texels[i] = Vec2f ((float) cos (angle) * 0.5f + 0.5f, (float) sin (angle) * 0.5f + 0.5f);
    prevVerticesT[currVertID] = currVertID;
    prevVerticesB[currVertID] = currVertID;
    currVertID++;
  }

  uint currTriID = 0;

  // First create the layered triangle strips.
  for (uint i = 1; i < (numRimVertices / 2); i++)
  {
    //-----
    // First create a new series of vertices.
    //-----
    // Angle from the center to the new circle of vertices.
    float newAngle = i * radiusStep * twoPI / 360.0f;
    // Radius of the new circle of vertices.
    float newRadius = radius * (float) cos (newAngle);
    // Height of the new circle of vertices.
    float newHeight = vertRadius * (float) sin (newAngle);
    // UV radius.
    float uvRadius = (1.0f - 2.0f * (float) i / (float)numRimVertices) * 0.5f;
    for (uint j = 0; j < numRimVertices; j++)
    {
      float angle = j * 2.0f * radiusStep * twoPI / 360.0f;

      vertices[currVertID] = Vec3f (newRadius * (float) cos (angle),
        newHeight, newRadius * (float) sin (angle));
      float u = uvRadius * (float) cos (angle) + 0.5f;
      float v = uvRadius * (float) sin (angle) + 0.5f;
      texels[currVertID] = Vec2f (u, v);
      newVerticesT[j] = currVertID;

      currVertID++;

      vertices[currVertID] = Vec3f (newRadius * (float) cos (angle),
        -newHeight, newRadius * (float) sin (angle));
      texels[currVertID] = Vec2f (u, v);
      newVerticesB[j] = currVertID;

      currVertID++;
    }

    //-----
    // Now make the triangle strips.
    //-----
    for (uint j = 0; j < numRimVertices; j++)
    {
      uint j1num = (j+1) % numRimVertices;

      Face3 tri1 = {prevVerticesT[j], newVerticesT[j1num], newVerticesT[j]};
      triangles[currTriID] = tri1;
      currTriID++;

      Face3 tri2 = {prevVerticesT[j], prevVerticesT[j1num], newVerticesT[j1num]};
      triangles[currTriID] = tri2;
      currTriID++;

      Face3 tri3 = {prevVerticesB[j], newVerticesB[j1num], newVerticesB[j]};
      triangles[currTriID] = tri3;
      currTriID++;

      Face3 tri4 = {prevVerticesB[j], prevVerticesB[j1num], newVerticesB[j1num]};
      triangles[currTriID] = tri4;
      currTriID++;
    }

    //-----
    // Copy the new vertex array to prev_vertices.
    //-----
    for (uint j = 0 ; j < numRimVertices ; j++)
    {
      prevVerticesT[j] = newVerticesT[j];
      prevVerticesB[j] = newVerticesB[j];
    }
  }

  // Create the top and bottom vertices.
  uint topVertex = currVertID;
  vertices[currVertID] = Vec3f (0.0f, vertRadius, 0.0f);
  texels[currVertID] = Vec2f (0.5f, 0.5f);
  currVertID++;
  uint bottomVertex = 0;

  bottomVertex = currVertID;
  vertices[currVertID] = Vec3f (0.0f, -vertRadius, 0.0f);
  texels[currVertID] = Vec2f (0.5f, 0.5f);
  currVertID++;


  //-----
  // Make the top triangle fan.
  //-----
  for (uint j = 0 ; j < numRimVertices ; j++)
  {
    uint j1num = (j+1)%numRimVertices;
    Face3 tri = {topVertex, prevVerticesT[j], prevVerticesT[j1num]};
    triangles[currTriID] = tri;
    currTriID++;
  }

  //-----
  // Make the bottom triangle fan.
  //-----
  for (uint j = 0 ; j < numRimVertices ; j++)
  {
    uint j1num = (j+1)%numRimVertices;
    Face3 tri = {bottomVertex, prevVerticesB[j], prevVerticesB[j1num]};
    triangles[currTriID] = tri;
    currTriID++;
  }

  // Scale and shift all the vertices.
  for (uint i = 0 ; i < currVertID ; i++)
  {
    vertices[i][0] *= size[0];
    vertices[i][1] *= size[1];
    vertices[i][2] *= size[2];
    Vec3f normal = vertices[i];
    normal.normalize ();
    normals[i] = (reversed)? -normal : normal;
  }

  VertexAttributeSetHandle *vasHdl = CreateHandle (VertexAttributeSetHandle);
  {
    WritableObject<VertexAttributeSet> vas (vasHdl);
    vas->setVertices (vertices, numVertices);
    vas->setNormals (normals, numVertices);
    vas->setTexCoords (0, 2, texels->getPtr (), numVertices);
  }

  // Swap all triangles if needed.
  if (reversed)
  {
    for (size_t i = 0 ; i < numTriangles ; i++)
    {
      int s = triangles[i][0];
      triangles[i][0] = triangles[i][2];
      triangles[i][2] = s;
    }
  }

  TrianglesHandle *trisHdl = CreateHandle (TrianglesHandle);
  {
    WritableObject<Triangles> tris (trisHdl);
    tris->setVertexAttributeSet (vasHdl);
    tris->setFaces (triangles, numTriangles);
  }

  delete[] prevVerticesT;
  delete[] newVerticesT;
  delete[] prevVerticesB;
  delete[] newVerticesB;
  delete[] triangles;
  delete[] texels;
  delete[] vertices;
  delete[] normals;

  return trisHdl;
}
QuadsHandle *icShapesHelper::createQuadGeometry (nvmath::Vec2f size)
{
  Face4 face = {1,2,3,0};
  Vec3f vertices[4] = {Vec3f (0, size[0], -size[1]), 
    Vec3f (0, -size[0], -size[1]),
    Vec3f (0, -size[0], size[1]),
    Vec3f (0, size[0], size[1])};
  Vec2f texels[4] = {Vec2f (0,0), Vec2f (1,0), Vec2f (1,1), Vec2f (0,1)};

  VertexAttributeSetHandle *quadVASHdl = CreateHandle (VertexAttributeSetHandle);
  {
    WritableObject<VertexAttributeSet> quadVAS (quadVASHdl);
    quadVAS->setVertices (vertices, 4);
    quadVAS->setTexCoords (0, 2, texels->getPtr (), 4);
  }
  QuadsHandle *quadHdl = CreateHandle (QuadsHandle);
  {
    WritableObject<Quads> quad (quadHdl);
    quad->setFaces (&face, 1);
    quad->setVertexAttributeSet (quadVASHdl);
  }
  return quadHdl;
}
#if 0
QuadsHandle *icShapesHelper::createQuadGizmo (nvmath::Vec2f size)
{
  Face4 face = {1,2,3,0};
  Vec3f vertices[4] = {Vec3f (size[0], 0, -size[1]), 
    Vec3f (-size[0], 0, -size[1]),
    Vec3f (-size[0], 0,  size[1]),
    Vec3f (size[0], 0, size[1])};

  Vec2f texels[4] = {Vec2f (0,0), Vec2f (1,0), Vec2f (1,1), Vec2f (0,1)};

  VertexAttributeSetHandle *quadVASHdl = CreateHandle (VertexAttributeSetHandle);
  {
    WritableObject<VertexAttributeSet> quadVAS (quadVASHdl);
    quadVAS->setVertices (vertices, 4);
    quadVAS->setTexCoords (0, 2, texels->getPtr (), 4);
  }
  QuadsHandle *quadHdl = CreateHandle (QuadsHandle);
  {
    WritableObject<Quads> quad (quadHdl);
    quad->setFaces (&face, 1);
    quad->setVertexAttributeSet (quadVASHdl);
  }
  return quadHdl;
}
#endif
#if 0
QuadsHandle *icShapesHelper::createQuadGizmo (nvmath::Vec2f size)
{
  Face4 *faces = new Face4[2];

  faces[0][0] = 1;
  faces[0][1] = 2;
  faces[0][2] = 3;
  faces[0][3] = 0;

  faces[1][0] = 0;
  faces[1][1] = 2;
  faces[1][2] = 3;
  faces[1][3] = 1;

  Vec3f vertices[4] = {
	Vec3f (size[0], 0, -size[1]),
    Vec3f (-size[0], 0, -size[1]),
    Vec3f (-size[0], 0,  size[1]),
    Vec3f (size[0], 0, size[1])};

  //Vec2f texels[8] = {Vec2f (0,0), Vec2f (1,0), Vec2f (1,1), Vec2f (0,1),
  //					Vec2f (0,0), Vec2f (0,1), Vec2f (1,1), Vec2f (1,0)};
  Vec2f texels[4] = {Vec2f (0,0), Vec2f (1,0), Vec2f (1,1), Vec2f (0,1)};

  VertexAttributeSetHandle *quadVASHdl = CreateHandle (VertexAttributeSetHandle);
  {
    WritableObject<VertexAttributeSet> quadVAS (quadVASHdl);
    quadVAS->setVertices (vertices, 4);
    quadVAS->setTexCoords (0, 2, texels->getPtr (), 4);
  }
  QuadsHandle *quadHdl = CreateHandle (QuadsHandle);
  {
    WritableObject<Quads> quad (quadHdl);
    quad->setFaces (faces, 2);
    quad->setVertexAttributeSet (quadVASHdl);
  }
  return quadHdl;
}
#endif
TrianglesHandle *icShapesHelper::createBoxGeometry (Vec3f size)
{
  Vec3f vertices[24];
  Vec3f normals[24];
  Vec2f texels[24];
  Face3 triangles[12];

  Vec3f halfSize = size /= 2.0f;

  vertices[0] = Vec3f (-halfSize[0], halfSize[1], -halfSize[2]);
  vertices[1] = Vec3f (-halfSize[0], halfSize[1], -halfSize[2]);
  vertices[2] = Vec3f (-halfSize[0], halfSize[1], -halfSize[2]);

  vertices[3] = Vec3f (-halfSize[0], halfSize[1], halfSize[2]);
  vertices[4] = Vec3f (-halfSize[0], halfSize[1], halfSize[2]);
  vertices[5] = Vec3f (-halfSize[0], halfSize[1], halfSize[2]);

  vertices[6] = Vec3f (halfSize[0], halfSize[1], halfSize[2]);
  vertices[7] = Vec3f (halfSize[0], halfSize[1], halfSize[2]);
  vertices[8] = Vec3f (halfSize[0], halfSize[1], halfSize[2]);

  vertices[9] = Vec3f (halfSize[0], halfSize[1], -halfSize[2]);
  vertices[10] = Vec3f (halfSize[0], halfSize[1], -halfSize[2]);
  vertices[11] = Vec3f (halfSize[0], halfSize[1], -halfSize[2]);

  vertices[12] = Vec3f (-halfSize[0], -halfSize[1], halfSize[2]);
  vertices[13] = Vec3f (-halfSize[0], -halfSize[1], halfSize[2]);
  vertices[14] = Vec3f (-halfSize[0], -halfSize[1], halfSize[2]);

  vertices[15] = Vec3f (halfSize[0], -halfSize[1], halfSize[2]);
  vertices[16] = Vec3f (halfSize[0], -halfSize[1], halfSize[2]);
  vertices[17] = Vec3f (halfSize[0], -halfSize[1], halfSize[2]);

  vertices[18] = Vec3f (halfSize[0], -halfSize[1], -halfSize[2]);
  vertices[19] = Vec3f (halfSize[0], -halfSize[1], -halfSize[2]);
  vertices[20] = Vec3f (halfSize[0], -halfSize[1], -halfSize[2]);

  vertices[21] = Vec3f (-halfSize[0], -halfSize[1], -halfSize[2]);
  vertices[22] = Vec3f (-halfSize[0], -halfSize[1], -halfSize[2]);
  vertices[23] = Vec3f (-halfSize[0], -halfSize[1], -halfSize[2]);

  texels[0] = Vec2f (0, 0); // 1
  texels[1] = Vec2f (0, 1); // 2
  texels[2] = Vec2f (1, 0); // 3

  texels[3] = Vec2f (0, 0); // 2
  texels[4] = Vec2f (0, 0); // 3
  texels[5] = Vec2f (1, 0); // 4

  texels[6] = Vec2f (1, 0); // 2
  texels[7] = Vec2f (0, 0); // 4
  texels[8] = Vec2f (1, 0); // 5

  texels[9] = Vec2f (1, 0); // 1
  texels[10] = Vec2f (1, 1); // 2
  texels[11] = Vec2f (0, 0); // 5

  texels[12] = Vec2f (0, 1); // 3
  texels[13] = Vec2f (1, 1); // 4
  texels[14] = Vec2f (1, 1); // 6

  texels[15] = Vec2f (0, 1); // 4
  texels[16] = Vec2f (1, 1); // 5
  texels[17] = Vec2f (1, 0); // 6

  texels[18] = Vec2f (1, 1); // 1
  texels[19] = Vec2f (0, 1); // 5
  texels[20] = Vec2f (0, 0); // 6

  texels[21] = Vec2f (0, 1); // 1
  texels[22] = Vec2f (1, 1); // 3
  texels[23] = Vec2f (0, 1); // 6

  normals[0] = Vec3f (-halfSize[0],halfSize[1],-halfSize[2]); normals[0].normalize ();
  normals[1] = Vec3f (-halfSize[0],halfSize[1],-halfSize[2]); normals[1].normalize ();
  normals[2] = Vec3f (-halfSize[0],halfSize[1],-halfSize[2]); normals[2].normalize ();

  normals[3] = Vec3f (-halfSize[0],halfSize[1],halfSize[2]); normals[3].normalize ();
  normals[4] = Vec3f (-halfSize[0],halfSize[1],halfSize[2]); normals[4].normalize ();
  normals[5] = Vec3f (-halfSize[0],halfSize[1],halfSize[2]); normals[5].normalize ();

  normals[6] = Vec3f (halfSize[0],halfSize[1],halfSize[2]); normals[6].normalize ();
  normals[7] = Vec3f (halfSize[0],halfSize[1],halfSize[2]); normals[7].normalize ();
  normals[8] = Vec3f (halfSize[0],halfSize[1],halfSize[2]); normals[8].normalize ();

  normals[9] = Vec3f (halfSize[0],halfSize[1],-halfSize[2]); normals[9].normalize ();
  normals[10] = Vec3f (halfSize[0],halfSize[1],-halfSize[2]); normals[10].normalize ();
  normals[11] = Vec3f (halfSize[0],halfSize[1],-halfSize[2]); normals[11].normalize ();

  normals[12] = Vec3f (-halfSize[0],-halfSize[1],halfSize[2]); normals[12].normalize ();
  normals[13] = Vec3f (-halfSize[0],-halfSize[1],halfSize[2]); normals[13].normalize ();
  normals[14] = Vec3f (-halfSize[0],-halfSize[1],halfSize[2]); normals[14].normalize ();

  normals[15] = Vec3f (halfSize[0],-halfSize[1],halfSize[2]); normals[15].normalize ();
  normals[16] = Vec3f (halfSize[0],-halfSize[1],halfSize[2]); normals[16].normalize ();
  normals[17] = Vec3f (halfSize[0],-halfSize[1],halfSize[2]); normals[17].normalize ();

  normals[18] = Vec3f (halfSize[0],-halfSize[1],-halfSize[2]); normals[18].normalize ();
  normals[19] = Vec3f (halfSize[0],-halfSize[1],-halfSize[2]); normals[19].normalize ();
  normals[20] = Vec3f (halfSize[0],-halfSize[1],-halfSize[2]); normals[20].normalize ();

  normals[21] = Vec3f (-halfSize[0],-halfSize[1],-halfSize[2]); normals[21].normalize ();
  normals[22] = Vec3f (-halfSize[0],-halfSize[1],-halfSize[2]); normals[22].normalize ();
  normals[23] = Vec3f (-halfSize[0],-halfSize[1],-halfSize[2]); normals[23].normalize ();

  VertexAttributeSetHandle *vasHdl = CreateHandle(VertexAttributeSetHandle);
  {
    WritableObject<VertexAttributeSet> vas(vasHdl);
    vas->setVertices(vertices, 24);
    vas->setNormals(normals, 24);
    vas->setTexCoords (0, 2, texels[0].getPtr (), 24);
  }

  triangles[0][0] = 0; triangles[0][1] = 9; triangles[0][2] = 18;
  triangles[1][0] = 0; triangles[1][1] = 18; triangles[1][2] = 21;

  triangles[2][0] = 3; triangles[2][1] = 6; triangles[2][2] = 10;
  triangles[3][0] = 3; triangles[3][1] = 10; triangles[3][2] = 1;

  triangles[4][0] = 4; triangles[4][1] = 2; triangles[4][2] = 22;
  triangles[5][0] = 4; triangles[5][1] = 22; triangles[5][2] = 12;

  triangles[6][0] = 7; triangles[6][1] = 5; triangles[6][2] = 13;
  triangles[7][0] = 7; triangles[7][1] = 13; triangles[7][2] = 15;

  triangles[8][0] = 11; triangles[8][1] = 8; triangles[8][2] = 16;
  triangles[9][0] = 11; triangles[9][1] = 16; triangles[9][2] = 19;

  triangles[10][0] = 23; triangles[10][1] = 20; triangles[10][2] = 17;
  triangles[11][0] = 23; triangles[11][1] = 17; triangles[11][2] = 14;

  TrianglesHandle *triHdl = CreateHandle(TrianglesHandle);
  {
    WritableObject<Triangles> tri(triHdl);
    tri->setFaces (triangles, 12);
    tri->setVertexAttributeSet( vasHdl );
  }

  return triHdl;
}

bool (const std::string& strFilename, PxClothMeshDesc &desc, bool texCoords, bool tearLines)
{
  // open the file
  std::ifstream file;
  file.open(strFilename.c_str(), std::ios::in | std::ios::binary);

  // make sure it opened properly
  if(!file)
	{
	printf("ERROR:::Load Physics Mesh:::File not found\n");
    return false;
	}

  //make a new stream data source and use it to load the mesh
  CalStreamSource streamSrc( file );

  // check if this is a valid file
  char magic[4];
  if(!streamSrc.readBytes(&magic[0], 4) || (memcmp(&magic[0], Cal::MESH_FILE_MAGIC, 4) != 0))
    {
	printf("ERROR:::Load Physics Mesh:::Invalid file format\n");
    return false;
	}

  // check if the version is compatible with the library
  int version;
  if(!streamSrc.readInteger(version) || (version < Cal::EARLIEST_COMPATIBLE_FILE_VERSION) || (version > Cal::CURRENT_FILE_VERSION))
    {
	printf("ERROR:::Load Physics Mesh:::Incompatible file version\n");
    return false;
	}

  // get the number of submeshes
  int submeshCount;
  if(!streamSrc.readInteger(submeshCount))
    {
	printf("ERROR:::Load Physics Mesh:::Invalid file format\n");
    return false;
	}

  // load all core submeshes
  for(int submeshId = 0; submeshId < submeshCount; ++submeshId)
    {
	generateCal3d(streamSrc, desc, texCoords, tearLines);
    }

  //close the file
  file.close();

  return true;
}

int (CalStreamSource &dataSrc, PxClothMeshDesc &desc, bool texCoords, bool tearLines)
{
	int integer = 0;
	float floating = 0;
	int influenceCount = 0;
	int i;

	// verify data Source
	if(!dataSrc.ok())
		{
		printf("ERROR:::pMesh::load_cal3d:::dataSrc error\n");
		return 0;
		}

	// get the material thread id of the submesh
	int coreMaterialThreadId;
	dataSrc.readInteger(coreMaterialThreadId);

	// get the number of vertices, faces, level-of-details and springs
	dataSrc.readInteger((int&)mMaxVertices);
	dataSrc.readInteger((int&)mMaxIndices);

	// initialize physx mesh description
	desc.numVertices				= mMaxVertices;
	desc.numTriangles				= mMaxIndices;
	desc.pointStrideBytes			= sizeof(PxVec3);
	desc.triangleStrideBytes		= 3*sizeof(PxU32);
	desc.vertexMassStrideBytes		= sizeof(PxReal);
	desc.vertexFlagStrideBytes		= sizeof(PxU32);
	desc.points						= (PxVec3*)malloc(sizeof(PxVec3)*desc.numVertices);
	desc.triangles					= (PxU32*)malloc(sizeof(PxU32)*desc.numTriangles*3);
	desc.vertexMasses				= 0;
	desc.vertexFlags				= 0;
	desc.flags						= NX_CLOTH_MESH_WELD_VERTICES;
	desc.weldingDistance			= 0.0001f;

	mMaxVertices = mMaxVertices * TEAR_MEMORY_FACTOR;
	mMaxIndices  = mMaxIndices * 3;

#if 0	// Scaling
	// copy positions and indices
	PxVec3 *vSrc = (PxVec3*)wo.mVertices;
	PxVec3 *vDest = (PxVec3*)desc.points;
	for (int i = 0; i < wo.mVertexCount; i++, vDest++, vSrc++) 
		*vDest = (*vSrc)*scale + myOffset;
	memcpy((PxU32*)desc.triangles, wo.mIndices, sizeof(PxU32)*desc.numTriangles*3);
#endif

	int lodCount;
	dataSrc.readInteger(lodCount);
	int springCount;
	dataSrc.readInteger(springCount);
	// get the number of texture coordinates per vertex
	int textureCoordinateCount;
	dataSrc.readInteger(textureCoordinateCount);

	// check if an error happened
	if(!dataSrc.ok())
		{
		printf("ERROR:::pMesh::load_cal3d:::dataSrc error\n");
		return 0;
		}

	PxVec3 *vDest = (PxVec3*)desc.points;

	// load all vertices and their influences
	for(int vertexId = 0; vertexId < desc.numVertices; ++vertexId)
		{
		dataSrc.readFloat(vDest[vertexId].x);
		dataSrc.readFloat(vDest[vertexId].y);
		dataSrc.readFloat(vDest[vertexId].z);

		CalVector position;
		CalVector normal;
		std::vector<Influence> vectorInfluence;
		int collapseId;
		int faceCollapseCount;

#if 0
		dataSrc.readFloat(vert[vertexId].norm[0]);
		dataSrc.readFloat(vert[vertexId].norm[1]);
		dataSrc.readFloat(vert[vertexId].norm[2]);
#endif

		dataSrc.readInteger(/*vertex.collapseId*/integer);
		dataSrc.readInteger(/*vertex.faceCollapseCount*/integer);

		// check if an error happened
		if(!dataSrc.ok())
			{
			printf("ERROR:::pMesh::load_cal3d:::dataSrc error\n");
			return 0;
			}

		if(texCoords)
			{
			mNumTempTexCoords = desc.numVertices;
			mTempTexCoords = (GLfloat *)malloc(sizeof(GLfloat) * mNumTempTexCoords * 2);

			mIndexRenderBuffer = (PxU32*)malloc(sizeof(PxU32) * mMaxIndices);
			memset(mIndexRenderBuffer, 0, sizeof(PxU32) * mMaxIndices);
			for (PxU32 i = 0; i < desc.numTriangles; i++)
				{
				assert((desc.flags & NX_CF_16_BIT_INDICES) == 0);
				PxU32* tri = (PxU32*)(((char*)desc.triangles) + (desc.triangleStrideBytes * i));
				mIndexRenderBuffer[3*i+0] = tri[0];
				mIndexRenderBuffer[3*i+1] = tri[1];
				mIndexRenderBuffer[3*i+2] = tri[2];
				}
			}
		else
			{
			mNumTempTexCoords = 0;
			mTempTexCoords = NULL;
			}

		// load all texture coordinates of the vertex
		for(int textureCoordinateId = 0; textureCoordinateId < textureCoordinateCount; ++textureCoordinateId)
			{
			// load data of the influence
			dataSrc.readFloat(mTempTexCoords[2*textureCoordinateId]);
			dataSrc.readFloat(mTempTexCoords[2*textureCoordinateId+1]);

			// check if an error happened
			if(!dataSrc.ok())
				{
				printf("ERROR:::pMesh::load_cal3d:::dataSrc error\n");
				return 0;
				}
			}

		// get the number of influences
		if(!dataSrc.readInteger(influenceCount) || (influenceCount < 0))
			{
			printf("ERROR:::pMesh::load_cal3d:::dataSrc error number of influences\n");
			return 0;
			}

		// load all influences of the vertex
		for(int influenceId = 0; influenceId < influenceCount; ++influenceId)
			{
			// load data of the influence
			dataSrc.readInteger(/*vertex.vectorInfluence[influenceId].boneId*/integer);
			dataSrc.readFloat(/*vertex.vectorInfluence[influenceId].weight*/floating);

			// check if an error happened
			if(!dataSrc.ok())
				{
				printf("ERROR:::pMesh::load_cal3d:::dataSrc influences\n");
				return 0;
				}
			}

		// load the physical property of the vertex if there are springs in the core submesh
		if(springCount > 0)
			{
			// load data of the physical property
			dataSrc.readFloat(/*physicalProperty.weight*/floating);

			// check if an error happened
			if(!dataSrc.ok())
				{
				printf("ERROR:::pMesh::load_cal3d:::dataSrc physical properties\n");
				return 0;
				}
			}
		}

	// load all springs
	for(int springId = 0; springId < springCount; ++springId)
		{
		// load data of the spring
		dataSrc.readInteger(/*spring.vertexId[0]*/integer);
		dataSrc.readInteger(/*spring.vertexId[1]*/integer);
		dataSrc.readFloat(/*spring.springCoefficient*/floating);
		dataSrc.readFloat(/*spring.idleLength*/floating);

		// check if an error happened
		if(!dataSrc.ok())
			{
			printf("ERROR:::pMesh::load_cal3d:::dataSrc error\n");
			return 0;
			}
		}

	int *vIndices = (int*)desc.triangles;

	// load all faces
	int justOnce = 0;
	bool flipModel = false;
	for(int faceId = 0; faceId < desc.numTriangles; ++faceId)
		{
		dataSrc.readInteger(vIndices[faceId]);
		dataSrc.readInteger(vIndices[faceId+1]);
		dataSrc.readInteger(vIndices[faceId+2]);

		//FIXME fractal design schemes material load or set real
		//face[faceId].material = coreMaterialThreadId;
		//face[faceId].flags = 0;

		// check if an error happened
		if(!dataSrc.ok())
			{
			printf("ERROR:::pMesh::load_cal3d:::dataSrc load faces error\n");
			return 0;
			}
		}

	return true;
}





void (int i_Iter, CalBone *pBone)
{
#if 1
	int i_Iter2 = 0;
	//CalQuaternion cal_Quat = pBone[8].getRotation();
	//CalVector cal_Vector = pBone[8].getTranslation();
	CalQuaternion cal_Quat = pBone[8].getRotationAbsolute();
	CalVector cal_Vector = pBone[8].getTranslationAbsolute();

	PxQuat i_Quat;
	PxQuat qRotLeft, qRotRight, qRotAround, qReal, qCorrect, qCorrect270, qTransfer;
	qRotLeft.fromAngleAxis(i_Iter, PxVec3(0,0,1));
	qRotRight.fromAngleAxis(-90, PxVec3(0,0,1));
	qRotAround.fromAngleAxis(180, PxVec3(0,0,1));
	qReal.fromAngleAxis(-90, PxVec3(1,0,0));
	qCorrect.fromAngleAxis(90, PxVec3(1,0,0));
	qCorrect270.fromAngleAxis(270, PxVec3(1,0,0));

	i_Quat.setWXYZ(cal_Quat.w, cal_Quat.x, cal_Quat.y, cal_Quat.z);
	i_Quat.normalize();
	//i_Quat.id();
	//printf("Trace w %f x %f y %f z %f\n", cal_Quat.w, cal_Quat.x, cal_Quat.y, cal_Quat.z);
	//printf("Trace x %f y %f z %f\n", cal_Vector.x, cal_Vector.y, cal_Vector.z);
	//vec_BoneStructure[i_Iter2]->head->setGlobalOrientationQuat(i_Quat);
	//vec_BoneStructure[i_Iter2]->head->setGlobalPosition(PxVec3(cal_Vector.x, cal_Vector.y, cal_Vector.z));
	//vec_BoneStructure[i_Iter2]->head->setGlobalOrientationQuat(qRotLeft);

#if 0
	vec_BoneStructure[i_Iter2]->head->setGlobalOrientationQuat(i_Quat);
#endif
#endif

#if 1
	cal_Quat = pBone[8].getRotationAbsolute();
	i_Quat.setWXYZ(cal_Quat.w, cal_Quat.x, cal_Quat.y, cal_Quat.z);
	i_Quat.normalize();
	vec_BoneStructure[i_Iter2]->head->setGlobalOrientationQuat(i_Quat);
	//vec_BoneStructure[i_Iter2]->head->setGlobalPosition(PxVec3(m_Mixer->m_RagSheet->Vector[8]->x, m_Mixer->m_RagSheet->Vector[8]->y, m_Mixer->m_RagSheet->Vector[8]->z));

	cal_Quat = pBone[3].getRotationAbsolute();
	i_Quat.setWXYZ(cal_Quat.w, cal_Quat.x, cal_Quat.y, cal_Quat.z);
	i_Quat.normalize();
	vec_BoneStructure[i_Iter2]->torso->setGlobalOrientationQuat(i_Quat);
	//vec_BoneStructure[i_Iter2]->torso->setGlobalPosition(PxVec3(m_Mixer->m_RagSheet->Vector[3]->x, m_Mixer->m_RagSheet->Vector[3]->y, m_Mixer->m_RagSheet->Vector[3]->z));

	cal_Quat = pBone[2].getRotationAbsolute();
	i_Quat.setWXYZ(cal_Quat.w, cal_Quat.x, cal_Quat.y, cal_Quat.z);
	i_Quat.normalize();
	vec_BoneStructure[i_Iter2]->pelvis->setGlobalOrientationQuat(i_Quat);
	//vec_BoneStructure[i_Iter2]->pelvis->setGlobalPosition(PxVec3(m_Mixer->m_RagSheet->Vector[2]->x, m_Mixer->m_RagSheet->Vector[2]->y, m_Mixer->m_RagSheet->Vector[2]->z));

	cal_Quat = pBone[10].getRotationAbsolute();
	i_Quat.setWXYZ(cal_Quat.w, cal_Quat.x, cal_Quat.y, cal_Quat.z);
	i_Quat.normalize();
	vec_BoneStructure[i_Iter2]->leftUpperArm->setGlobalOrientationQuat(i_Quat);
	//vec_BoneStructure[i_Iter2]->leftUpperArm->setGlobalPosition(PxVec3(m_Mixer->m_RagSheet->Vector[10]->x, m_Mixer->m_RagSheet->Vector[10]->y, m_Mixer->m_RagSheet->Vector[10]->z));

	cal_Quat = pBone[29].getRotationAbsolute();
	i_Quat.setWXYZ(cal_Quat.w, cal_Quat.x, cal_Quat.y, cal_Quat.z);
	i_Quat.normalize();
	vec_BoneStructure[i_Iter2]->rightUpperArm->setGlobalOrientationQuat(i_Quat);
	//vec_BoneStructure[i_Iter2]->rightUpperArm->setGlobalPosition(PxVec3(m_Mixer->m_RagSheet->Vector[29]->x, m_Mixer->m_RagSheet->Vector[29]->y, m_Mixer->m_RagSheet->Vector[29]->z));

	cal_Quat = pBone[11].getRotationAbsolute();
	i_Quat.setWXYZ(cal_Quat.w, cal_Quat.x, cal_Quat.y, cal_Quat.z);
	i_Quat.normalize();
	vec_BoneStructure[i_Iter2]->leftForeArm->setGlobalOrientationQuat(i_Quat);
	//vec_BoneStructure[i_Iter2]->leftForeArm->setGlobalPosition(PxVec3(m_Mixer->m_RagSheet->Vector[11]->x, m_Mixer->m_RagSheet->Vector[11]->y, m_Mixer->m_RagSheet->Vector[11]->z));

	cal_Quat = pBone[30].getRotationAbsolute();
	i_Quat.setWXYZ(cal_Quat.w, cal_Quat.x, cal_Quat.y, cal_Quat.z);
	i_Quat.normalize();
	vec_BoneStructure[i_Iter2]->rightForeArm->setGlobalOrientationQuat(i_Quat);
	//vec_BoneStructure[i_Iter2]->rightForeArm->setGlobalPosition(PxVec3(m_Mixer->m_RagSheet->Vector[30]->x, m_Mixer->m_RagSheet->Vector[30]->y, m_Mixer->m_RagSheet->Vector[30]->z));

	cal_Quat = pBone[12].getRotationAbsolute();
	i_Quat.setWXYZ(cal_Quat.w, cal_Quat.x, cal_Quat.y, cal_Quat.z);
	i_Quat.normalize();
	vec_BoneStructure[i_Iter2]->leftHand->setGlobalOrientationQuat(i_Quat);
	//vec_BoneStructure[i_Iter2]->leftHand->setGlobalPosition(PxVec3(m_Mixer->m_RagSheet->Vector[12]->x, m_Mixer->m_RagSheet->Vector[12]->y, m_Mixer->m_RagSheet->Vector[12]->z));

	cal_Quat = pBone[31].getRotationAbsolute();
	i_Quat.setWXYZ(cal_Quat.w, cal_Quat.x, cal_Quat.y, cal_Quat.z);
	i_Quat.normalize();
	vec_BoneStructure[i_Iter2]->rightHand->setGlobalOrientationQuat(i_Quat);
	//vec_BoneStructure[i_Iter2]->rightHand->setGlobalPosition(PxVec3(m_Mixer->m_RagSheet->Vector[31]->x, m_Mixer->m_RagSheet->Vector[31]->y, m_Mixer->m_RagSheet->Vector[31]->z));

	cal_Quat = pBone[47].getRotationAbsolute();
	i_Quat.setWXYZ(cal_Quat.w, cal_Quat.x, cal_Quat.y, cal_Quat.z);
	i_Quat.normalize();
	vec_BoneStructure[i_Iter2]->leftThigh->setGlobalOrientationQuat(i_Quat);
	//vec_BoneStructure[i_Iter2]->leftThigh->setGlobalPosition(PxVec3(m_Mixer->m_RagSheet->Vector[47]->x, m_Mixer->m_RagSheet->Vector[47]->y, m_Mixer->m_RagSheet->Vector[47]->z));

	cal_Quat = pBone[51].getRotationAbsolute();
	i_Quat.setWXYZ(cal_Quat.w, cal_Quat.x, cal_Quat.y, cal_Quat.z);
	i_Quat.normalize();
	vec_BoneStructure[i_Iter2]->rightThigh->setGlobalOrientationQuat(i_Quat);
	//vec_BoneStructure[i_Iter2]->rightThigh->setGlobalPosition(PxVec3(m_Mixer->m_RagSheet->Vector[51]->x, m_Mixer->m_RagSheet->Vector[51]->y, m_Mixer->m_RagSheet->Vector[51]->z));

	cal_Quat = pBone[48].getRotationAbsolute();
	i_Quat.setWXYZ(cal_Quat.w, cal_Quat.x, cal_Quat.y, cal_Quat.z);
	i_Quat.normalize();
	vec_BoneStructure[i_Iter2]->leftCalf->setGlobalOrientationQuat(i_Quat);
	//vec_BoneStructure[i_Iter2]->leftCalf->setGlobalPosition(PxVec3(m_Mixer->m_RagSheet->Vector[48]->x, m_Mixer->m_RagSheet->Vector[48]->y, m_Mixer->m_RagSheet->Vector[48]->z));

	cal_Quat = pBone[52].getRotationAbsolute();
	i_Quat.setWXYZ(cal_Quat.w, cal_Quat.x, cal_Quat.y, cal_Quat.z);
	i_Quat.normalize();
	vec_BoneStructure[i_Iter2]->rightCalf->setGlobalOrientationQuat(i_Quat);
	//vec_BoneStructure[i_Iter2]->rightCalf->setGlobalPosition(PxVec3(m_Mixer->m_RagSheet->Vector[52]->x, m_Mixer->m_RagSheet->Vector[52]->y, m_Mixer->m_RagSheet->Vector[52]->z));

	cal_Quat = pBone[49].getRotationAbsolute();
	i_Quat.setWXYZ(cal_Quat.w, cal_Quat.x, cal_Quat.y, cal_Quat.z);
	i_Quat.normalize();
	vec_BoneStructure[i_Iter2]->leftFoot->setGlobalOrientationQuat(i_Quat);
	//vec_BoneStructure[i_Iter2]->leftFoot->setGlobalPosition(PxVec3(m_Mixer->m_RagSheet->Vector[49]->x, m_Mixer->m_RagSheet->Vector[49]->y, m_Mixer->m_RagSheet->Vector[49]->z));

	cal_Quat = pBone[53].getRotationAbsolute();
	i_Quat.setWXYZ(cal_Quat.w, cal_Quat.x, cal_Quat.y, cal_Quat.z);
	i_Quat.normalize();
	vec_BoneStructure[i_Iter2]->rightFoot->setGlobalOrientationQuat(i_Quat);
	//vec_BoneStructure[i_Iter2]->rightFoot->setGlobalPosition(PxVec3(m_Mixer->m_RagSheet->Vector[53]->x, m_Mixer->m_RagSheet->Vector[53]->y, m_Mixer->m_RagSheet->Vector[53]->z));
#endif
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	QpoTransform Bone;

	cal_Quat = pBone[31]->getRotationAbsolute();
	cal_Vector = pBone[31]->getTranslationAbsolute();

	rotationMatrix = cal_Quat;

	Bone.Matrix.m[0][0] = rotationMatrix.dxdx;
	Bone.Matrix.m[0][1] = rotationMatrix.dydx;
	Bone.Matrix.m[0][2] = rotationMatrix.dzdx;
	Bone.Matrix.m[1][0] = rotationMatrix.dxdy;
	Bone.Matrix.m[1][1] = rotationMatrix.dydy;
	Bone.Matrix.m[1][2] = rotationMatrix.dzdy;
	Bone.Matrix.m[2][0] = rotationMatrix.dxdz;
	Bone.Matrix.m[2][1] = rotationMatrix.dydz;
	Bone.Matrix.m[2][2] = rotationMatrix.dzdz;

#if 0
	pMatrix i_Matrix;
	pQuaternion i_pQuat;
	i_pQuat.w = -0.09;
	i_pQuat.x = 0.82;
	i_pQuat.y = 2.039;
	i_pQuat.z = -19.240345;
	i_pQuat.normalize();
	i_pQuat.get_mat(i_Matrix);

	Bone.Matrix = i_Matrix * Bone.Matrix;
#endif

	Bone.Matrix = Bone.Matrix * i_ViewMatrix;

	pVector pVector1, pResult;
	pVector1.x = cal_Vector.x;
	pVector1.y = cal_Vector.y;
	pVector1.z = cal_Vector.z;
	pResult = pVector1 * i_ViewMatrix;

#if 1
	i_bmatrix.setRow(0, PxVec3(Bone.Matrix.m[0][0], Bone.Matrix.m[1][0], Bone.Matrix.m[2][0]));
	i_bmatrix.setRow(1, PxVec3(Bone.Matrix.m[0][1], Bone.Matrix.m[1][1], Bone.Matrix.m[2][1]));
	i_bmatrix.setRow(2, PxVec3(Bone.Matrix.m[0][2], Bone.Matrix.m[1][2], Bone.Matrix.m[2][2]));
#endif

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



void (int i_Iter, std::vector<CalBone *>& pBone, PxMat33 i_AvatarMatrix)
{
	int i_Iter2 = 0;
	CalQuaternion cal_Quat;
	CalVector cal_Vector;
	PxVec3 cal_Vec3d;
	PxMat33 i_bmatrix;
	CalMatrix rotationMatrix;

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[8]->getRotationAbsolute();
	cal_Vector = pBone[8]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

#if 0
	pMatrix i_Matrix;
	pQuaternion i_pQuat;
	i_pQuat.w = -0.09;
	i_pQuat.x = 0.82;
	i_pQuat.y = 2.039;
	i_pQuat.z = -19.240345;
	i_pQuat.normalize();
	i_pQuat.get_mat(i_Matrix);

	Bone.Matrix = i_Matrix * Bone.Matrix;
#endif

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->head->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->head->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[3]->getRotationAbsolute();
	cal_Vector = pBone[3]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->torso->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->torso->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[2]->getRotationAbsolute();
	cal_Vector = pBone[2]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->pelvis->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->pelvis->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[10]->getRotationAbsolute();
	cal_Vector = pBone[10]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->leftUpperArm->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->leftUpperArm->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[29]->getRotationAbsolute();
	cal_Vector = pBone[29]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->rightUpperArm->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->rightUpperArm->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[11]->getRotationAbsolute();
	cal_Vector = pBone[11]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->leftForeArm->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->leftForeArm->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[30]->getRotationAbsolute();
	cal_Vector = pBone[30]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->leftHand->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->leftHand->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[31]->getRotationAbsolute();
	cal_Vector = pBone[31]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->rightHand->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->rightHand->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[47]->getRotationAbsolute();
	cal_Vector = pBone[47]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->leftThigh->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->leftThigh->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[51]->getRotationAbsolute();
	cal_Vector = pBone[51]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->rightThigh->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->rightThigh->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[48]->getRotationAbsolute();
	cal_Vector = pBone[48]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->leftCalf->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->leftCalf->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[52]->getRotationAbsolute();
	cal_Vector = pBone[52]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->rightCalf->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->rightCalf->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[49]->getRotationAbsolute();
	cal_Vector = pBone[49]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->leftFoot->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->leftFoot->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[53]->getRotationAbsolute();
	cal_Vector = pBone[53]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->rightFoot->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->rightFoot->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
}

void (int i_Iter, std::vector<CalBone *>& pBone, PxMat33 i_AvatarMatrix)
{
	int i_Iter2 = 0;
	CalQuaternion cal_Quat;
	CalVector cal_Vector;
	PxVec3 cal_Vec3d;
	PxMat33 i_bmatrix;
	CalMatrix rotationMatrix;

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[8]->getRotationAbsolute();
	cal_Vector = pBone[8]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

#if 0
	pMatrix i_Matrix;
	pQuaternion i_pQuat;
	i_pQuat.w = -0.09;
	i_pQuat.x = 0.82;
	i_pQuat.y = 2.039;
	i_pQuat.z = -19.240345;
	i_pQuat.normalize();
	i_pQuat.get_mat(i_Matrix);

	Bone.Matrix = i_Matrix * Bone.Matrix;
#endif

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->head->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->head->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[3]->getRotationAbsolute();
	cal_Vector = pBone[3]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->torso->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->torso->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[2]->getRotationAbsolute();
	cal_Vector = pBone[2]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->pelvis->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->pelvis->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[10]->getRotationAbsolute();
	cal_Vector = pBone[10]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->leftUpperArm->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->leftUpperArm->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[29]->getRotationAbsolute();
	cal_Vector = pBone[29]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->rightUpperArm->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->rightUpperArm->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[11]->getRotationAbsolute();
	cal_Vector = pBone[11]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->leftForeArm->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->leftForeArm->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[12]->getRotationAbsolute();
	cal_Vector = pBone[12]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->leftHand->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->leftHand->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[31]->getRotationAbsolute();
	cal_Vector = pBone[31]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->rightHand->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->rightHand->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[47]->getRotationAbsolute();
	cal_Vector = pBone[47]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->leftThigh->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->leftThigh->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[51]->getRotationAbsolute();
	cal_Vector = pBone[51]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->rightThigh->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->rightThigh->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[48]->getRotationAbsolute();
	cal_Vector = pBone[48]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->leftCalf->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->leftCalf->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[52]->getRotationAbsolute();
	cal_Vector = pBone[52]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->rightCalf->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->rightCalf->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[49]->getRotationAbsolute();
	cal_Vector = pBone[49]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->leftFoot->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->leftFoot->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	cal_Quat = pBone[53]->getRotationAbsolute();
	cal_Vector = pBone[53]->getTranslationAbsolute();

	cal_Vec3d.set(cal_Vector.x, cal_Vector.y, cal_Vector.z);
	cal_Vec3d = i_AvatarMatrix * cal_Vec3d;

	//~~~~~~~~~~~~~~~~~~~~

	rotationMatrix = cal_Quat;

	i_bmatrix.setRow(0, PxVec3(rotationMatrix.dxdx, rotationMatrix.dxdy, rotationMatrix.dxdz));
	i_bmatrix.setRow(1, PxVec3(rotationMatrix.dydx, rotationMatrix.dydy, rotationMatrix.dydz));
	i_bmatrix.setRow(2, PxVec3(rotationMatrix.dzdx, rotationMatrix.dzdy, rotationMatrix.dzdz));

	i_bmatrix = i_AvatarMatrix * i_bmatrix;

	//~~~~~~~~~~~~~~~~~~~~

	vec_BoneStructure[i_Iter2]->rightFoot->setGlobalOrientation(i_bmatrix);
	vec_BoneStructure[i_Iter2]->rightFoot->setGlobalPosition(cal_Vec3d);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

bind_terrain_vertex();

int i_iterator;
int i_layer;
int i_instance;
for(i_iterator = 0; i_iterator < i_TrrBank->m_TerrainCell.size(); i_iterator++)
	{
	for(i_layer = 0; i_layer < i_TrrBank->m_TerrainCell[i_iterator]->veclayer.size(); i_layer++)
		{
		///// Render Layer Instances
		//Vertex Array - Position
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_TrrBank->m_TerrainCell[i_iterator]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[0]);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glEnableClientState(GL_VERTEX_ARRAY);

		//Normal Array - Normals
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_TrrBank->m_TerrainCell[i_iterator]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[2]);
		glNormalPointer(GL_FLOAT, 0, 0);
		glEnableClientState(GL_NORMAL_ARRAY);

		//Vertex Array - Texture Coords
		glClientActiveTextureARB(GL_TEXTURE0_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_TrrBank->m_TerrainCell[i_iterator]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[4]);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);

		//Vertex Array - Weights
		glClientActiveTextureARB(GL_TEXTURE1_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_TrrBank->m_TerrainCell[i_iterator]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[1]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Vertex Array - MatrixIndex
		glClientActiveTextureARB(GL_TEXTURE2_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_TrrBank->m_TerrainCell[i_iterator]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[3]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Elements Array - Face Indices
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, i_TrrBank->m_TerrainCell[i_iterator]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[5]);

		for(i_instance = 0; i_instance < i_TrrBank->m_TerrainCell[i_iterator]->m_Instance.size(); i_instance++)
			{
			glLoadIdentity();
			glMultMatrixf((float *)&g_render->camera.mat_t);
			glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

			//glTranslatef(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
			//glMultMatrixf(playerAV->Xform.Matrix.mf);
			//glDrawElements(GL_TRIANGLES, i_TrrBank->m_TerrainCell[0]->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL)+ 0));

			glTranslatef(i_TrrBank->m_TerrainCell[i_iterator]->m_Instance[i_instance]->x, i_TrrBank->m_TerrainCell[i_iterator]->m_Instance[i_instance]->y, i_TrrBank->m_TerrainCell[i_iterator]->m_Instance[i_instance]->z);
			//glMultMatrixf(playerAV->Xform.Matrix.mf);

			glDrawElements(GL_TRIANGLES, i_TrrBank->m_TerrainCell[i_iterator]->veclayer[i_layer].m_BufferSet[0]->m_IndexCounter, GL_UNSIGNED_INT, NULL);
			}

		// Render Seal Instances
		//Vertex Array - Position
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_TrrBank->m_TerrainCell[i_iterator]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[6]);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glEnableClientState(GL_VERTEX_ARRAY);

		//Normal Array - Normals
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_TrrBank->m_TerrainCell[i_iterator]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[8]);
		glNormalPointer(GL_FLOAT, 0, 0);
		glEnableClientState(GL_NORMAL_ARRAY);

		//Vertex Array - Texture Coords
		glClientActiveTextureARB(GL_TEXTURE0_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_TrrBank->m_TerrainCell[i_iterator]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[10]);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);

		//Vertex Array - Weights
		glClientActiveTextureARB(GL_TEXTURE1_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_TrrBank->m_TerrainCell[i_iterator]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[7]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Vertex Array - MatrixIndex
		glClientActiveTextureARB(GL_TEXTURE2_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_TrrBank->m_TerrainCell[i_iterator]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[9]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Elements Array - Face Indices
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, i_TrrBank->m_TerrainCell[i_iterator]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[11]);

		for(i_instance = 0; i_instance < i_TrrBank->m_TerrainCell[i_iterator]->m_Instance.size(); i_instance++)
			{
			glLoadIdentity();
			glMultMatrixf((float *)&g_render->camera.mat_t);
			glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

			//glTranslatef(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
			//glMultMatrixf(playerAV->Xform.Matrix.mf);
			//glDrawElements(GL_TRIANGLES, i_TrrBank->m_TerrainCell[0]->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL)+ 0));

			glTranslatef(i_TrrBank->m_TerrainCell[i_iterator]->m_Instance[i_instance]->x, i_TrrBank->m_TerrainCell[i_iterator]->m_Instance[i_instance]->y, i_TrrBank->m_TerrainCell[i_iterator]->m_Instance[i_instance]->z);
			//glMultMatrixf(playerAV->Xform.Matrix.mf);

			glDrawElements(GL_TRIANGLES, i_TrrBank->m_TerrainCell[i_iterator]->veclayer[i_layer].m_BufferSet[0]->m_sIndexCounter, GL_UNSIGNED_INT, NULL);
			}
		}
	}

unbind_terrain_vertex();

glClientActiveTextureARB(GL_TEXTURE0_ARB);