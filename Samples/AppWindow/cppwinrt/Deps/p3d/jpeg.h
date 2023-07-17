#ifndef JPEGP3D_H
#define JPEGP3D_H

#include <stdio.h>

typedef struct 
{
	char *buffer;
	int pos;
	int len;
} FILE2;

typedef struct 
{
   unsigned char *ptr;
   int    width;
   int    height;
   FILE  *output_file;
   FILE2 *input_file;
   int    aritcoding;
   int    CCIR601sampling;
   int    smoothingfactor;
   int    quality;
   int    status;
   int    components;
   int    numscan;
} JPEGDATA;

/*void jpeg_info(JPEGDATA *data);
void jpeg_read(JPEGDATA *data);
void jpeg_write(JPEGDATA *data);*/

#endif
