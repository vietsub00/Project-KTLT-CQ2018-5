#ifndef _BITMAP_
#define _BITMAP_
#include <iostream>
#include <fstream>
using namespace std;

struct Bitmap
{
	int width;
	int height;
	int rowSize;
	unsigned char *pixels;
};

struct Color
{
	unsigned char R, G, B;
};

int LoadBitmap(const char *fname, Bitmap &bmp);
int SaveBitmap(const char *fname, const Bitmap &bmp);
void provideBM(Bitmap &bmp, int height, int width);
void DisposeBitmap(Bitmap &bmp);

int SetPixel(const Bitmap &bmp, int row, int col, Color color);
int GetPixel(const Bitmap &bmp, int row, int col, Color &color);

int Truncate(int Value);

void Hist(const Bitmap &bmp);
void Enlarge(const Bitmap &inbmp, Bitmap &outbmp);
void Brightness(const Bitmap &bmp, double factor);
void BnW(const Bitmap &bmp);
void Reverse(const Bitmap &bmp);
void FlipVert(const Bitmap &bmp);
void FlipHori(const Bitmap &bmp);
void Saturation(const Bitmap &bmp, double factor);
void Contrast(const Bitmap &bmp, double contrast);
void Resize(const Bitmap &bmpin, Bitmap &bmpout, int width, int height);
void Blur(const Bitmap &bmp, Bitmap &bmpout);
void RGBSplit(const Bitmap &bmp);
void EdgeDetect(const Bitmap &bmp, Bitmap &bmpout);

#endif
