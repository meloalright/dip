#include<stdio.h>
#include <iostream>
using namespace std;
#define H 640
#define W 640
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
	for(i = 0;i<H;i++){
		for(j=0;j<W;j++)
		{
			fread(&pp,1,3,inputfile);
			Pixel[i][j].B=pp.B;
			Pixel[i][j].G=pp.G;
			Pixel[i][j].R=pp.R;
		}
	}
	for(i = 125;i<371;i++){
		for(j=125;j<371;j++)
		{
			
			Pixel[i][j].B=0;
			Pixel[i][j].G=0;
			Pixel[i][j].R=0;
		}
	}

	for(i = 325;i<571;i++){
		for(j=325;j<571;j++)
		{
			
			Pixel[i][j].B=0;
			Pixel[i][j].G=0;
			Pixel[i][j].R=0;
		}
	}
	outfile=fopen("show.bmp","wb");
	fwrite(filehead,1,54,outfile);
	for(i = 0;i<H;i++)
	{
		for(j=0;j<W;j++)
		{
			fwrite(&Pixel[i][j],1,3,outfile);
		}
	}
	fclose(outfile);
	fclose(inputfile);
	return 0;

}