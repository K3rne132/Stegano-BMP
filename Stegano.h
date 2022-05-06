#ifndef STEGANO_H
#define STEGANO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BMPHEADER.h"

BITMAPFILEHEADER get_bmp_header(FILE** file) {
	BITMAPFILEHEADER header = { 0 };
	if (*file == NULL)
		return header;
	fseek(*file, 0, SEEK_SET);
	fread(&header, 1, sizeof(BITMAPFILEHEADER), *file);
	return header;
}

int hide_bmp_into_bmp(FILE** from, FILE** to, FILE** output) {
	if (*from == NULL)
		return 11;
	if (*to == NULL)
		return 12;
	BITMAPFILEHEADER h_from = get_bmp_header(from);
	BITMAPFILEHEADER h_to   = get_bmp_header(to);

	const unsigned long bytes_required  = h_from.bfSize * 8;
	const unsigned long bytes_available = h_to.bfSize - h_to.bfOffBits;
	if (bytes_required > bytes_available)
		return 13;

	fseek(*from, 0, SEEK_SET);
	unsigned char* buffer_to_write = (unsigned char*)malloc(h_from.bfSize);
	if (buffer_to_write == NULL)
		return 14;
	fread(buffer_to_write, 1, h_from.bfSize, *from);

	fseek(*to, 0, SEEK_SET);
	unsigned char* buffer_output = (unsigned char*)malloc(h_to.bfSize);
	if (buffer_output == NULL) {
		free(buffer_to_write);
		return 15;
	}
	fread(buffer_output, 1, h_to.bfSize, *to);

	for (unsigned int i = 0; i < h_from.bfSize; i++) {
		for (unsigned int j = 0; j < 8; j++) {
			unsigned char byte = buffer_to_write[i] >> (7 - j);
			byte &= 0x01;
			buffer_output[h_to.bfOffBits + i * 8 + j] &= 0xFE;
			buffer_output[h_to.bfOffBits + i * 8 + j] |= byte;
		}
	}
	free(buffer_to_write);

	fseek(*output, 0, SEEK_SET);
	fwrite(buffer_output, 1, h_to.bfSize, *output);
	free(buffer_output);
	return 0;
}

int restore_bmp_from_bmp(FILE** bmp, FILE** output) {
	BITMAPFILEHEADER h_bmp = get_bmp_header(bmp);

	unsigned char* buffer_read = (unsigned char*)malloc(h_bmp.bfSize);
	if (buffer_read == NULL)
		return 21;
	fseek(*bmp, h_bmp.bfOffBits, SEEK_SET);
	fread(buffer_read, 1, h_bmp.bfSize - h_bmp.bfOffBits, *bmp);

	unsigned char* buffer_to_write = (unsigned char*)calloc(h_bmp.bfSize, 1);
	if (buffer_to_write == NULL) {
		free(buffer_read);
		return 22;
	}
	
	const unsigned int size_of_header = sizeof(BITMAPFILEHEADER);
	for (unsigned int i = 0; i < size_of_header; i++) {
		unsigned char byte = 0x00;
		for (unsigned int j = 0; j < 8; j++) {
			unsigned char t = buffer_read[i * 8 + j];
			byte |= (t & 0x01) << (7 - j);
		}
		buffer_to_write[i] = byte;
	}

	BITMAPFILEHEADER h_out = { 0 };
	memcpy(&h_out, buffer_to_write, size_of_header);

	for (unsigned int i = size_of_header; i < h_out.bfSize; i++) {
		unsigned char byte = 0x00;
		for (unsigned int j = 0; j < 8; j++) {
			unsigned char t = buffer_read[i * 8 + j];
			byte |= (t & 0x01) << (7 - j);
		}
		buffer_to_write[i] = byte;
	}
	free(buffer_read);

	fwrite(buffer_to_write, 1, h_out.bfSize, *output);
	free(buffer_to_write);

	return 0;
}

#endif
