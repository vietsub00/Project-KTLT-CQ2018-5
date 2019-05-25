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
	double factor = (259 * (contrast + 255)) / (255 * (259 - contrast));
	for (register int row = 0; row < bmp.height; row++)
		for (register int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);

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

//xoay anh
void Rotate(const Bitmap &bmp, Bitmap &outbmp)
{
	outbmp.height = bmp.width;
	outbmp.width = bmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3) / 4) * 4;

	outbmp.pixels = new unsigned char[outbmp.height * outbmp.rowSize];
	for (register int row = 0; row < bmp.height; row++)
		for (register int col = 0; col < bmp.width; col++)
		{
			Color color1, color2;
			GetPixel(bmp, row, col, color1);
			SetPixel(outbmp, col, outbmp.width - row - 1, color1);
		}
}

//xoay anh sang phai
void RotateR(const Bitmap &bmp, Bitmap &bmpout)
{
	//provideBM(bmpout, bmp.width, bmp.height);

	for (register int row = 0; row < bmpout.height; row++)
	for (register int col = 0; col < bmpout.width; col++)
	{
		Color color;
		GetPixel(bmp, bmpout.width - col - 1, row, color);
		SetPixel(bmpout, row, col, color);
	}
}

/*

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
			GetPixel(bmp, bmp.height - 1 - row, col, color2);

			swap(color1, color2);

			SetPixel(bmp, row, col, color1);
			SetPixel(bmp, bmp.height - 1 - row, col, color2);
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
			GetPixel(bmp, row, bmp.width - 1 - col, color2);
			swap(color1, color2);
			SetPixel(bmp, row, col, color1);
			SetPixel(bmp, row, bmp.width - 1 - col, color2);
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

//export image's histogram
void Hist(const Bitmap &bmp)
{
	int** hist;
	hist = new int*[3];
	for (register int i = 0; i < 3; i++) hist[i] = (int *)calloc(256, sizeof(int));

	for (register int row = 0; row < bmp.height; row++)
		for (register int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);

			hist[0][color.R]++;
			hist[1][color.G]++;
			hist[2][color.B]++;
		}

		//xac dinh height

		unsigned int Max = 0;
		for (register int i = 0; i < 256; i++)
		{
			if (Max < hist[0][i])Max = hist[0][i];
			if (Max < hist[1][i])Max = hist[1][i];
			if (Max < hist[2][i])Max = hist[2][i];
		}

		for (register int i = 0; i < 256; i++)
		{
			hist[0][i] = hist[0][i] * 200 / Max;
			hist[1][i] = hist[1][i] * 200 / Max;
			hist[2][i] = hist[2][i] * 200 / Max;
		}
		
		cout << Max << endl;
		
		Bitmap histogram;
		provideBM(histogram, 210, 256);

		for (register int row = 0; row < histogram.height; row++)
			for (register int col = 0; col < histogram.width; col++)
			{
				Color color;
				color.R=0;
				color.G=0;
				color.B=0;
				
				if (row <= hist[0][col]) color.R = 255;
				if (row <= hist[1][col]) color.G = 255;
				if (row <= hist[2][col]) color.B = 255;
				
				SetPixel(histogram, histogram.height - 1 - row, histogram.width - 1 - col, color);
			}
			
		//luu hinh anh
			if (SaveBitmap("histogram.bmp", histogram))
			{
			}
			else
				printf("Can not save the bitmap file!!!\n");

			//giai phóng bộ nhớ
			DisposeBitmap(histogram);
			
			for (register int i = 0; i < 3; i++) delete[] hist[i];
			delete[] hist;

}

//tach kenh R/G/B
void RGBSplit(const Bitmap &bmp)
{
	Bitmap BMR, BMG, BMB;
	provideBM(BMR, bmp.height, bmp.width);
	provideBM(BMG, bmp.height, bmp.width);
	provideBM(BMB, bmp.height, bmp.width);

	for (register int row = 0; row < bmp.height; row++)
		for (register int col = 0; col < bmp.width; col++)
		{
			Color R, G, B, color;
			GetPixel(bmp, row, col, color);

			R.R = color.R;
			R.G = color.R;
			R.B = color.R;

			G.R = color.G;
			G.G = color.G;
			G.B = color.G;

			B.R = color.B;
			B.G = color.B;
			B.B = color.B;

			SetPixel(BMR, row, col, R);
			SetPixel(BMG, row, col, G);
			SetPixel(BMB, row, col, B);
		}
		SaveBitmap("R.bmp", BMR);
		SaveBitmap("G.bmp", BMG);
		SaveBitmap("B.bmp", BMB);
		DisposeBitmap(BMR);
		DisposeBitmap(BMG);
		DisposeBitmap(BMB);
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

//lam mo
void Blur(const Bitmap &bmp, Bitmap &bmpout)
{
		for (register int row = 0; row < bmp.height; row++)
			for (register int col = 0; col < bmp.width; col++)
			{
				Color color;
				if (row == 0 || col == 0 || row == bmp.height - 1 || col == bmp.width - 1)
					GetPixel(bmp, row, col, color);
				else
				{
					Color color1, color2, color3, color4;

					GetPixel(bmp, row - 1, col, color1);
					GetPixel(bmp, row + 1, col, color2);
					GetPixel(bmp, row, col - 1, color3);
					GetPixel(bmp, row, col + 1, color4);

					color.R = (color1.R + color2.R + color3.R + color4.R) / 4;
					color.G = (color1.G + color2.G + color3.G + color4.G) / 4;
					color.B = (color1.B + color2.B + color3.B + color4.B) / 4;
				}
					
				SetPixel(bmpout, row, col, color);
			}
}

void EdgeDetect(const Bitmap &bmp, Bitmap &bmpout)
{

	int KernelSobelX[9] ={
		1, 0, -1,
		2, 0, -2,
		1, 0, -1
	};

	int KernelSobelY[9] ={
		 1,  2,  1,
		 0,  0,  0,
		-1, -2, -1
	};

	for (int row = 1; row < bmp.height - 1; row++)
		for (int col = 1; col < bmp.width - 1; col++)
		{
			Color color0;
			int XR = 0, XG = 0, XB = 0, YR = 0, YG = 0, YB = 0;

			for (register int m = -1; m <= 1; m++)
				for (register int n = -1; n <= 1; n++)
				{
					Color color;
					GetPixel(bmp, row + m, col + n , color);
					XR += color.R * KernelSobelX[(m + 1) * 3 + (n + 1)];
					XG += color.G * KernelSobelX[(m + 1) * 3 + (n + 1)];
					XB += color.B * KernelSobelX[(m + 1) * 3 + (n + 1)];
					YR += color.R * KernelSobelY[(m + 1) * 3 + (n + 1)];
					YG += color.G * KernelSobelY[(m + 1) * 3 + (n + 1)];
					YB += color.B * KernelSobelY[(m + 1) * 3 + (n + 1)];
				}

				color0.R = fabs((double)(XR + YR) / 2);
				color0.G = fabs((double)(XG + YG) / 2);
				color0.B = fabs((double)(XB + YB) / 2);

				SetPixel(bmpout, row, col, color0);
		}
}
