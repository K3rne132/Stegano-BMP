#include "Stegano.h"

int main(int argc, char** argv) {
	FILE* src;
	fopen_s(&src, "src.bmp", "rb");
	if (src == NULL)
		return 1;
	FILE* dst;
	fopen_s(&dst, "dst.bmp", "rb");
	if (dst == NULL)
		return 2;
	FILE* out;
	fopen_s(&out, "out.bmp", "w+b");
	if (out == NULL)
		return 3;
	FILE* out2;
	fopen_s(&out2, "out2.bmp", "w+b");
	if (out == NULL)
		return 3;

	int error = hide_bmp_into_bmp(&src, &dst, &out);
	if (error != 0)
		return error;
	error = restore_bmp_from_bmp(&out, &out2);
	if (error != 0)
		return error;

	return 0;
}