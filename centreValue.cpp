#include<stdio.h>
#include <iostream>
using namespace std;
#define H 512
#define W 512
struct{
      unsigned char B,G,R;
}pp,Pixel[H][W];
int getCentre(int a0,int a1,int a2,int a3,int a4,int a5,int a6,int a7,int a8);
int main()
{
    FILE *inputfile,*outfile;
	char filehead[54];
	int i,j;
	inputfile = fopen("ori/lady.bmp","rb");//处理已经加噪声文件
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
	for(i = 1;i<H;i++){
		for(j=1;j<W;j++)
		{
			Pixel[i][j].R = getCentre(Pixel[i-1][j-1].R,Pixel[i-1][j].R,Pixel[i-1][j+1].R,Pixel[i][j-1].R,Pixel[i][j].R,Pixel[i][j+1].R,Pixel[i+1][j-1].R,Pixel[i+1][j].R,Pixel[i+1][j+1].R);
			Pixel[i][j].G = getCentre(Pixel[i-1][j-1].G,Pixel[i-1][j].G,Pixel[i-1][j+1].G,Pixel[i][j-1].G,Pixel[i][j].G,Pixel[i][j+1].G,Pixel[i+1][j-1].G,Pixel[i+1][j].G,Pixel[i+1][j+1].G);
			Pixel[i][j].B = getCentre(Pixel[i-1][j-1].B,Pixel[i-1][j].B,Pixel[i-1][j+1].B,Pixel[i][j-1].B,Pixel[i][j].B,Pixel[i][j+1].B,Pixel[i+1][j-1].B,Pixel[i+1][j].B,Pixel[i+1][j+1].B);
		}
	}
	outfile=fopen("centreValue.bmp","wb");
	fwrite(filehead,1,54,outfile);
	for(i = 0;i<H;i++)
		for(j=0;j<W;j++)
			fwrite(&Pixel[i][j],1,3,outfile);
	fclose(outfile);
	fclose(inputfile);
	return 0;

}
int getCentre(int a0,int a1,int a2,int a3,int a4,int a5,int a6,int a7,int a8){
	int centre;
	int tmp;
	int arr[9] = {a0,a1,a2,a3,a4,a5,a6,a7,a8};
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(arr[i]>arr[i+1]){
				tmp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = tmp;
			}
		}
	}
	return arr[4];
}