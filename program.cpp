#include <stdio.h>
#include "Bitmap.h"

int main()
{
	const char *inFileName = "fish.bmp";
	const char *outFileName= "out.bmp";
	Bitmap bmp,bmp1;
	
	if(LoadBitmap(inFileName, bmp))
	{
		printf("%dx%d\n", bmp.width, bmp.height);
		
		//Bightness(bmp, 50);
		provideBM(bmp1, bmp.height, bmp.width);
		TestFunc(bmp,bmp1);
		somethingelsethatidontknow(bmp1,3);
		BnW(bmp1);
		//TestFunc(bmp1, bmp);
		//somethingelsethatidontknow(bmp1,3);
		//Reverse(bmp);
		//Contrast(bmp, -5);
		//FlipHori(bmp);
		//Resize(bmp, bmp1,bmp.width/10, bmp.height/10);
		//Blur(bmp1, 1);
		//printf("%dx%d\n", bmp1.width, bmp1.height);

		if (SaveBitmap(outFileName, bmp1))
		{
		}
		else
			printf("Can not save the bitmap file!!!\n");
		
		DisposeBitmap(bmp);
		DisposeBitmap(bmp1);
	}
	else
		printf("Can not load the bitmap file!!!\n");
	
	printf("Bye!\n");
	
	return 0;
}
