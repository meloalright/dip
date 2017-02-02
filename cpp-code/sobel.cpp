#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;
#define H 512
#define W 512
struct{
      unsigned char B,G,R;
}pp,Pixel[H][W],px[H][W];
double sobel_X(int a0,int a1,int a2,int a3,int a4,int a5,int a6,int a7,int a8);
double sobel_Y(int a0,int a1,int a2,int a3,int a4,int a5,int a6,int a7,int a8);
double sobel(int a0,int a1,int a2,int a3,int a4,int a5,int a6,int a7,int a8);

int main()
{
    FILE *inputfile,*outfile;
	char filehead[54];
	int i,j;
	inputfile = fopen("ori/centreValue.bmp","rb");//处理原来图像
	fread(filehead,1,54,inputfile);
	int grayTmp;
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
			px[i][j].R = sobel(Pixel[i-1][j-1].R,Pixel[i][j-1].R,Pixel[i+1][j-1].R,Pixel[i-1][j].R,Pixel[i][j].R,Pixel[i+1][j].R,Pixel[i-1][j+1].R,Pixel[i][j+1].R,Pixel[i+1][j+1].R);
			px[i][j].G = px[i][j].R;
			px[i][j].B = px[i][j].R;
			
		}
	}
	outfile=fopen("sobel.bmp","wb");
	fwrite(filehead,1,54,outfile);
	for(i = 0;i<H;i++)
		for(j=0;j<W;j++)
			fwrite(&px[i][j],1,3,outfile);
	fclose(outfile);
	fclose(inputfile);
	return 0;

}
double sobel_X(int a0,int a1,int a2,int a3,int a4,int a5,int a6,int a7,int a8){
	return (-a0-2*a1-a2+0+0+0+a6+2*a7+a8)/9;
}

double sobel_Y(int a0,int a1,int a2,int a3,int a4,int a5,int a6,int a7,int a8){
	return (-a0+0+a2-2*a3+0+2*a5-a6+0+a8)/9;
}
double sobel(int a0,int a1,int a2,int a3,int a4,int a5,int a6,int a7,int a8){
	double x = sobel_X(a0,a1,a2,a3,a4,a5,a6,a7,a8);
	double y = sobel_Y(a0,a1,a2,a3,a4,a5,a6,a7,a8);
	if(x<-18||x>18){
		return 255;
	}
	else if(y<-18||y>18){
		return 255;
	}
	else{
		return 0;
	}
}