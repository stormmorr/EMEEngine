/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -QAGE Port Shell-
	- Minor Component -Function Definitions-

*/

//### INCLUDES
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"
#include "Q-PortSHELL-QCH.h"

#include "math.h"

#include "Q-Includes.h"
#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-GlobalHeader.h"
#include "Q-CORE-Avatar.h"

//##### Include Engine Specific Headers #####

#include "CSInclude/CSEngine.h"
#include "cal3d/animcallback.h"
#include "cal3d/cal3d.h"

#include "mbstring.h"
#include "malloc.h"

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <malloc.h>


using namespace GVARS;

namespace GVARS
{

void Q_PORTShell::Tex_Tool(const char * File)
	{
	File = "Bitmaps//shadowmapN.tga";

	csPrintf("Tex_Tool >>> Loading file %s\n", File);

	FILE *f = fopen(File, "rb");

	if(!f) csPrintf("Tex_Tool <<< cannot open file %s\n", File);

	fseek(f, 0, SEEK_END);
	size_t fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	csPrintf("Tex_Tool >>> Reading %zu bytes from file\n", fsize);

	csRef<iDataBuffer> buf;
		{
		char* buffer = new char[fsize];
		if (fread (buffer, 1, fsize, f) < fsize) csPrintf ("Tex_Tool <<< unexpected EOF while reading file %s\n", File);
		buf.AttachNew (new csDataBuffer (buffer, fsize, true));
		}

	fclose(f);

	int fmt;
	fmt = CS_IMGFMT_PALETTED8;
	fmt = CS_IMGFMT_TRUECOLOR;
	fmt = CS_IMGFMT_ANY;

	ImageLoader->SetDithering (true);

	csRef<iImage> ifile = ImageLoader->Load (buf, fmt | CS_IMGFMT_ALPHA);
	if(!ifile) csPrintf("Tex_Tool <<< failed to recognise image format for %s\n", File);

	if(TToption.verbose || TToption.info)
		{
		csPrintf ("<Image size: %d x %d pixels, %zu bytes>\n", ifile->GetWidth(),
		ifile->GetHeight(), csImageTools::ComputeDataSize(ifile));
		int fmt = ifile->GetFormat();
		csPrintf ("<Image format: %s, alpha channel: %s>\n",
			(fmt & CS_IMGFMT_MASK) == CS_IMGFMT_NONE ? "none" :
			(fmt & CS_IMGFMT_MASK) == CS_IMGFMT_PALETTED8 ? "paletted, 256 colors" :
			(fmt & CS_IMGFMT_MASK) == CS_IMGFMT_TRUECOLOR ? "truecolor" : "unknown",
			(fmt & CS_IMGFMT_ALPHA) ? "present" : "not present");
		}

	if(TToption.applykey && (TToption.transp || ifile->HasKeyColor()))
		{
		csRGBpixel transp;
		if (TToption.transp) transp = transpcolor;
		else
			{
			int kr, kg, kb;
			ifile->GetKeyColor (kr, kg, kb);
			transp.Set (kr, kg, kb);
			}
		ifile = csBakeKeyColor::Image (ifile, transp);
		}

	csString suffix;

	if(TToption.scaleX > 0)
		{
		int scaleY = TToption.scaleY;
		if (scaleY == -1) scaleY = (ifile->GetHeight () * TToption.scaleX) / ifile->GetWidth ();
		csPrintf ("Tex_Tool >>> Rescaling image to %d x %d\n", TToption.scaleX, scaleY);
		ifile = csImageManipulate::Rescale (ifile, TToption.scaleX, scaleY);
		suffix.AppendFmt ("-s%dx%d", TToption.scaleX, scaleY);
		}

	if(TToption.mipmap >= 0)
		{
		csPrintf ("Tex_Tool >>> Creating mipmap level %d from image\n", TToption.mipmap);
		ifile = csImageManipulate::Mipmap (ifile, TToption.mipmap,
		TToption.transp ? &transpcolor : 0);
		suffix.AppendFmt ("-m%d", TToption.mipmap);
		}

	if(TToption.stripalpha)
		{
		int format = ifile->GetFormat ();
		if (format & CS_IMGFMT_ALPHA)
			{
			csPrintf ("Tex_Tool >>> Removing alpha channel from image\n");
			ifile.AttachNew (new csImageMemory (ifile, format & ~CS_IMGFMT_ALPHA));
			}
		}

	if(TToption.addalpha)
		{
		int format = ifile->GetFormat ();
		if (!(format & CS_IMGFMT_ALPHA))
			{
			csPrintf ("Tex_Tool >>> Adding alpha channel from image\n");
			ifile.AttachNew (new csImageMemory (ifile, format | CS_IMGFMT_ALPHA));

			// merge keycolor into alpha
			if (ifile->HasKeyColor())
				{
				int pixels = ifile->GetWidth() * ifile->GetHeight();

				int key_r, key_g, key_b;
				ifile->GetKeyColor(key_r, key_g, key_b);
				csRGBcolor key(key_r, key_g, key_b);

				int i;
				switch (format & CS_IMGFMT_MASK)
					{
					case CS_IMGFMT_PALETTED8:
						{
						csImageMemory* newImg = new csImageMemory (ifile);
						const Uint8 *data = (Uint8*)ifile->GetImageData();
						const csRGBpixel *pal = ifile->GetPalette();
						Uint8 *alphamap = newImg->GetAlphaPtr();
						for (i = 0; i < pixels; i++)
							{
							if (pal[data[i]] == key)
								{
								alphamap[i] = 0;
								}
							}
						ifile.AttachNew (newImg);
						} break;
					case CS_IMGFMT_TRUECOLOR:
						{
						csRGBpixel *data = (csRGBpixel*)ifile->GetImageData();
						for (i = 0; i < pixels; i++) if (data[i] == key) data[i].alpha = 0;
						} break;
					}
				}//F-ifile
			}//F-format
		}//F-TToption.addalpha

	if (TToption.sharpen)
		{
		csPrintf ("Tex_Tool >>> Sharpening image with strength %d\n", TToption.sharpen);
		ifile = csImageManipulate::Sharpen (ifile, TToption.sharpen,
		TToption.transp ? &transpcolor : 0);
		}

	if (TToption.mipmaps)
		{
		csImageMemory* newImage = new csImageMemory (ifile);
		csRef<iImage> mip = ifile;
		uint m = 1;
		while ((mip->GetWidth() > 1) || (mip->GetHeight() > 1) || (mip->GetDepth() > 1))
			{
			mip = csImageManipulate::Mipmap (mip, 1, TToption.transp ? &transpcolor : 0);
			newImage->SetMipmap (m, mip);
			m++;
			}
		ifile.AttachNew (newImage);
		}
	}


void Q_PORTShell::Tex_AlphaLayerBlat(TextureAttributeItemHandle * Texture, TextureAttributeItemHandle * AlphaTexture, const char * Name)
	{
	ImageLoader->SetDithering (true);

	int TextureID = Engine->GetMaterialList()->Find(Texture);
	int ATextureID = Engine->GetMaterialList()->Find(AlphaTexture);
	const char* File;
	const char* AFile;

	int T = 0;
	int L = 1;
	while(T < TEXcounter && L == 1)
		{
		if(LOADED_TEXTURE[T].TextureID == TextureID)
			{
			File = LOADED_TEXTURE[T].FileName;
			L = 0;
			}
		T++;
		}

	T = 0;
	L = 1;
	while(T < TEXcounter && L == 1)
		{
		if(LOADED_TEXTURE[T].TextureID == ATextureID)
			{
			AFile = LOADED_TEXTURE[T].FileName;
			L = 0;
			}
		T++;
		}

	//####- LOAD ALPHA IMAGE -####

	printf("Alpha File = %s  Alpha TextureID = %i", AFile, ATextureID);

	csPrintf ("Loading file %s\n", AFile);

	FILE *f = fopen (AFile, "rb");

	if(!f) csPrintf ("cannot open file %s\n", AFile);

	fseek (f, 0, SEEK_END);
	size_t fsize = ftell (f);
	fseek (f, 0, SEEK_SET);

	csPrintf("Reading %zu bytes from file\n", fsize);

	csRef<iDataBuffer> Abuf;
		{
		char* buffer = new char[fsize];
		if (fread (buffer, 1, fsize, f) < fsize) csPrintf ("%s: unexpected EOF while reading file %s\n", AFile);
		Abuf.AttachNew (new csDataBuffer (buffer, fsize, true));
		}

	fclose(f);

	csRef<iImage> Aifile = ImageLoader->Load (Abuf, CS_IMGFMT_TRUECOLOR);
	if(!Aifile) csPrintf("%s: failed to recognise image format for %s\n", AFile);

	int Aformat = Aifile->GetFormat ();
	int Apixels = Aifile->GetWidth() * Aifile->GetHeight();

	const Uint8 *Adata;
	const csRGBpixel *Apal;
	csRGBpixel *Atruedata;

	int i;
	switch (Aformat & CS_IMGFMT_MASK)
		{
		case CS_IMGFMT_PALETTED8:
			{
			csImageMemory* newImg = new csImageMemory (Aifile);
			Adata = (Uint8*)Aifile->GetImageData();
			Apal = Aifile->GetPalette();
			QAGEsystem->ReportError("Alpha Format : CS_IMGFMT_PALETTED8");
			} break;

		case CS_IMGFMT_TRUECOLOR:
			{
			Atruedata = (csRGBpixel*)Aifile->GetImageData();
			} break;
		}

	//####- LOAD ACTUAL IMAGE -####

	printf("File = %s  TextureID = %i", File, TextureID);

	csPrintf ("Loading file %s\n", File);

	f = fopen (File, "rb");

	if(!f) csPrintf ("cannot open file %s\n", File);

	fseek (f, 0, SEEK_END);
	fsize = ftell (f);
	fseek (f, 0, SEEK_SET);

	csPrintf("Reading %zu bytes from file\n", fsize);

	csRef<iDataBuffer> buf;
		{
		char* buffer = new char[fsize];
		if (fread (buffer, 1, fsize, f) < fsize) csPrintf ("%s: unexpected EOF while reading file %s\n", File);
		buf.AttachNew (new csDataBuffer (buffer, fsize, true));
		}

	fclose(f);

	//csRef<iImage> ifile = ImageLoader->Load (buf, CS_IMGFMT_ANY | CS_IMGFMT_ALPHA);
	csRef<iImage> ifile = ImageLoader->Load (buf, CS_IMGFMT_TRUECOLOR);
	if(!ifile) csPrintf("%s: failed to recognise image format for %s\n", File);

	int format = ifile->GetFormat ();
	int pixels = ifile->GetWidth() * ifile->GetHeight();

	if (!(format & CS_IMGFMT_ALPHA))
		{
		csPrintf ("Adding alpha channel from image\n");
		ifile.AttachNew (new csImageMemory (ifile, format | CS_IMGFMT_ALPHA));

		int i;
		switch (format & CS_IMGFMT_MASK)
			{
			case CS_IMGFMT_PALETTED8:
				{
				csImageMemory* newImg = new csImageMemory (ifile);
				//const Uint8 *data = (Uint8*)ifile->GetImageData();
				//const csRGBpixel *pal = ifile->GetPalette();
				Uint8 *alphamap = newImg->GetAlphaPtr();
				for (i = 0; i < pixels; i++)
					{
					//if (pal[data[i]] == key)
					//	{
					//	alphamap[i] = 0;
					//	}
					alphamap[i] = Adata[i];
					}
				ifile.AttachNew (newImg);
				QAGEsystem->ReportError("Image Format : CS_IMGFMT_PALETTED8");
				} break;

			case CS_IMGFMT_TRUECOLOR:
				{
				csPrintf ("Format : CS_IMGFMT_TRUECOLOR\n");

				float RedA;
				float GreenA;
				float BlueA;
				float TotA;

				csRGBpixel *data = (csRGBpixel*)ifile->GetImageData();

				for (i = 0; i < pixels; i++)
					{
					RedA = Atruedata[i].red;
					GreenA = Atruedata[i].green;
					BlueA = Atruedata[i].blue;

					TotA = (RedA + GreenA + BlueA) / 3;

					data[i].alpha = TotA;
					}
				} break;
			}
		}

	//####- SAVE IMAGE -####

	csRef<iDataBuffer> imgData = ImageLoader->Save (ifile, "image/tga");

	csRef<iFile> file = myVFS->Open (Name, VFS_FILE_WRITE);

	if(file)
		{
		file->Write (imgData->GetData (), imgData->GetSize ());
		}

	printf("Texture converted to %s", Name);
	}

};