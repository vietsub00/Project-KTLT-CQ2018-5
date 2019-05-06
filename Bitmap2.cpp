#include "Bitmap.h"

// O(1)
int SetPixel(const Bitmap &bmp, int row, int col, Color color)
{
	if(row < 0 || row >= bmp.height
		 || col < 0 || col >= bmp.width)
		return 0;
	
	// color: B, G, R
	int offset = (bmp.height - 1 - row)*bmp.rowSize + col*3;
	bmp.pixels[offset] = color.B;
	bmp.pixels[offset + 1] = color.G;
	bmp.pixels[offset + 2] = color.R;
}

int GetPixel(const Bitmap &bmp, int row, int col, Color &color)
{
	if(row < 0 || row >= bmp.height
		 || col < 0 || col >= bmp.width)
		return 0;
	
	// color: B, G, R
	int offset = (bmp.height - 1 - row)*bmp.rowSize + col*3;
	color.B = bmp.pixels[offset];
	color.G = bmp.pixels[offset + 1];
	color.R = bmp.pixels[offset + 2];
}

int Truncate(int Value)
{
	if (Value > 255) return 255;
		else
			if (Value < 0) return 0;
				else return Value;
}

void Enlarge(const Bitmap &inbmp, Bitmap &outbmp)
{
	outbmp.width = 2 * inbmp.width;
	outbmp.height = 2 * inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for (register int row = 0; row < inbmp.height; row++)
		for (register int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			SetPixel(outbmp, 2*row, 2*col, color);
			SetPixel(outbmp, 2*row, 2*col + 1, color);
			SetPixel(outbmp, 2*row + 1, 2*col, color);
			SetPixel(outbmp, 2*row + 1, 2*col + 1, color);
		}
}

//tuong phan (-255,255)
void Contrast(const Bitmap &bmp, double contrast)
{
	//contrast = contrast * 255.0 / 10.0;
	for (register int row = 0; row < bmp.height; row++)
		for (register int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			
			double factor = (259 * (contrast + 255)) / (255 * (259 - contrast));

			color.R = Truncate(factor*(color.R - 128) + 128);

			color.G = Truncate(factor*(color.G - 128) + 128);

			color.B = Truncate(factor*(color.B - 128) + 128);

			SetPixel(bmp, row, col, color);
		}
}

//do sang (khong gioi han)
void Brightness(const Bitmap &bmp, double factor)
{
	for (register int row = 0; row < bmp.height; row++)
		for (register int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			
			color.R = Truncate(color.R + factor);
			
			color.G = Truncate(color.G + factor);

			color.B = Truncate(color.B + factor);
			
			SetPixel(bmp, row, col, color);
		}
}
/*
void Rotate(){}

void Hue(){}
*/

//lat tren duoi
void FlipHori(const Bitmap &bmp)
{
	for (register int row = 0; row < bmp.height / 2; row++)
		for (register int col = 0; col < bmp.width; col++)
		{
			Color color1, color2;

			GetPixel(bmp, row, col, color1);
			GetPixel(bmp, bmp.height - row , col, color2);

			swap(color1, color2);

			SetPixel(bmp, row, col, color1);
			SetPixel(bmp, bmp.height - row, col, color2);
		}
}

//lat trai phai
void FlipVert(const Bitmap &bmp)
{
	for (register int row = 0; row < bmp.height; row++)
		for (register int col = 0; col < bmp.width / 2; col++)
		{
			Color color1, color2;
			GetPixel(bmp, row, col, color1);
			GetPixel(bmp, row, bmp.width-col, color2);
			swap(color1, color2);
			SetPixel(bmp, row, col, color1);
			SetPixel(bmp, row, bmp.width - col, color2);
		}
}

//bao hoa mau (khong gioi han)
void Saturation(const Bitmap &bmp, double factor)
{
	for (register int row = 0; row < bmp.height; row++)
		for (register int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			int AvgColor = (0.299*color.R + 0.587*color.G + 0.114*color.B);

			color.R = Truncate(AvgColor + (color.R - AvgColor)*factor);

			color.G = Truncate(AvgColor + (color.G - AvgColor)*factor);

			color.B = Truncate(AvgColor + (color.B - AvgColor)*factor);

			SetPixel(bmp, row, col, color);
		}
}

//
void somethingelsethatidontknow(const Bitmap &bmp,int factor)
{
	for (int row = 1; row < bmp.height - 1; row++)
	for (int col = 1; col < bmp.width - 1; col++)
	{
		Color color;
		GetPixel(bmp, row, col, color);

		color.R = Truncate(color.R*factor);
		color.G = Truncate(color.G*factor);
		color.B = Truncate(color.B*factor);

		SetPixel(bmp, row, col, color);
	}

}

//xuat anh trang den
void BnW(const Bitmap &bmp)
{
	for (register int row = 0; row < bmp.height; row++)
		for (register int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			int AvgColor = 0.299*color.R + 0.587*color.G + 0.114*color.B;

			color.R = AvgColor;
			color.G = AvgColor;
			color.B = AvgColor;

			SetPixel(bmp, row, col, color);
		}
}

//am ban
void Reverse(const Bitmap &bmp)
{
	for (register int row = 0; row < bmp.height; row++)
		for (register int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);

			color.R = 255 - color.R;
			color.G = 255 - color.G;
			color.B = 255 - color.B;

			SetPixel(bmp, row, col, color);
		}
}

//Resize
void Resize(const Bitmap &bmpin, Bitmap &bmpout, int width, int height)
{
	bmpout.height = height;
	bmpout.width = width;
	bmpout.rowSize = ((3 * bmpout.width + 3) / 4) * 4;

	bmpout.pixels = new unsigned char[bmpout.height * bmpout.rowSize];

	for (register int row = 0; row < bmpout.height; row++)
	for (register int col = 0; col < bmpout.width; col++)
	{
		Color color;
		int col0 = col*bmpin.width/width, row0 = row*bmpin.height/height;
		GetPixel(bmpin, row0, col0, color);
		SetPixel(bmpout, row, col, color);
	}
}

//lam mo (max = 20)
void Blur(const Bitmap &bmp, int factor)
{
	for (register int i = 0; i < factor; i++)
		for (register int row = 1; row < bmp.height - 1; row++)
			for (register int col = 1; col < bmp.width - 1; col++)
			{
				Color color, color1, color2, color3, color4;

				GetPixel(bmp, row - 1, col, color1);
				GetPixel(bmp, row + 1, col, color2);
				GetPixel(bmp, row, col - 1, color3);
				GetPixel(bmp, row, col + 1, color4);

				color.R = (color1.R + color2.R + color3.R + color4.R) / 4;
				color.G = (color1.G + color2.G + color3.G + color4.G) / 4;
				color.B = (color1.B + color2.B + color3.B + color4.B) / 4;

				SetPixel(bmp, row, col, color);
			}
}

//ham kiem thu
void TestFunc(const Bitmap &bmp,Bitmap &bmpout)
{
	for (int row = 1; row < bmp.height-1; row++)
		for (int col = 1; col < bmp.width-1; col++)
		{
			Color color,color1,color2,color3,color4;

			GetPixel(bmp, row-1, col, color1);
			GetPixel(bmp, row+1, col, color2);
			GetPixel(bmp, row, col-1, color3);
			GetPixel(bmp, row, col+1, color4);
			GetPixel(bmp, row, col, color);

			color.R = Truncate((color1.R + color2.R + color3.R + color4.R) / 4 - color.R);
			color.G = Truncate((color1.G + color2.G + color3.G + color4.G) / 4 - color.G);
			color.B = Truncate((color1.B + color2.B + color3.B + color4.B) / 4 - color.B);
			//int vector = (int)sqrt(pow(R - color.R, 2) + pow(G - color.G, 2) + pow(B - color.B, 2));
			SetPixel(bmpout, row, col, color);
		}

}