#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;
#define H 512
#define W 512
struct{
      unsigned char B,G,R;
}pp,Pixel[H][W],px[H][W];

int main()
{
    FILE *inputfile,*outfile;
	char filehead[54];
	int i,j;
	inputfile = fopen("ori/lady.bmp","rb");//处理原来图像
	fread(filehead,1,54,inputfile);
	for(i = 0;i<H;i++)
		for(j=0;j<W;j++)
		{
			fread(&pp,1,3,inputfile);
			Pixel[i][j].B=pp.B;
			Pixel[i][j].G=pp.G;
			Pixel[i][j].R=pp.R;
			px[i][j].B=Pixel[i][j].B;
			px[i][j].G=Pixel[i][j].G;
			px[i][j].R=Pixel[i][j].R;
		}
	for(i = 0;i<H;i++){
		for(j=0;j<W;j++)
		{
			
			if((i+j)%22==0){
				px[i][j].R = 255;
				px[i][j].G = 255;
				px[i][j].B = 255;
			}
			else if((i-j)%22==0){
				px[i][j].R = 255;
				px[i][j].G = 255;
				px[i][j].B = 255;
			}
			else{
				px[i][j].R = 230;
				px[i][j].G = 0;
				px[i][j].B = 0;
			}
		}
	}
	outfile=fopen("push_noise.bmp","wb");
	fwrite(filehead,1,54,outfile);
	for(i = 0;i<H;i++)
		for(j=0;j<W;j++)
			fwrite(&px[i][j],1,3,outfile);
	fclose(outfile);
	fclose(inputfile);
	return 0;

}
