#include<stdio.h>
#include <iostream>
using namespace std;
#define H 256
#define W 256
struct{
      unsigned char B,G,R;
}pp,Pixel[H][W];
int main()
{
    FILE *inputfile,*outfile;
	char filehead[54];
	int i,j;
	inputfile = fopen("ori/ori.bmp","rb");
	fread(filehead,1,54,inputfile);
	int grayTmp;
	for(i = 0;i<H;i++)
		for(j=0;j<W;j++)
		{
			fread(&pp,1,3,inputfile);
			Pixel[i][j].B=pp.B;
			Pixel[i][j].G=pp.G;
			Pixel[i][j].R=pp.R;
		}
	for(i = 0;i<H;i++){
		for(j=0;j<W;j++)
		{
			grayTmp = 0.299 * Pixel[i][j].R + 0.587 * Pixel[i][j].G + 0.144 * Pixel[i][j].B;
			if(grayTmp > 128){
				Pixel[i][j].B=255;
				Pixel[i][j].G=255;
				Pixel[i][j].R=255;
			}
			else{
				Pixel[i][j].B=0;
				Pixel[i][j].G=0;
				Pixel[i][j].R=0;
			}
		}
	}
	outfile=fopen("binary.bmp","wb");
	fwrite(filehead,1,54,outfile);
	for(i = 0;i<H;i++)
		for(j=0;j<W;j++)
			fwrite(&Pixel[i][j],1,3,outfile);
	fclose(outfile);
	fclose(inputfile);
	return 0;

}