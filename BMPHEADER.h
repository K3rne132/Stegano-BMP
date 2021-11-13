#ifndef BMPHEADER_H
#define BMPHEADER_H

#define WORD  unsigned short
#define DWORD unsigned long

#pragma pack(push, 1)
typedef struct {
	WORD  bfType;
	DWORD bfSize;
	WORD  bfReserved1;
	WORD  bfReserved2;
	DWORD bfOffBits;
} BITMAPFILEHEADER;
#pragma pack(pop)

#endif
