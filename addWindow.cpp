#include<stdio.h>
#define H 256
#define W 256
#define H2 271
#define W2 276
#define W3 22
struct{
      unsigned char B,G,R;
}pp,Pixel[H2][W2];
int main()
{
    FILE *inputfile,*outfile;
	char filehead[54];
	int i,j;
	inputfile = fopen("ori/ori.bmp","rb");
	fread(filehead,1,54,inputfile);
	filehead[18]=20;
	filehead[19]=1;
	filehead[20]=0;
	filehead[21]=0;//biWidth=276=ox114
	filehead[22]=15;
	filehead[23]=1;
	filehead[24]=0;
	filehead[25]=0;//biHeight=271=ox10f
	filehead[34]=132;
	filehead[35]=108;
	filehead[36]=3;
	filehead[37]=0;//biSizeImage=(276*3)*271=224388=ox36C84
	filehead[2]=186;
	filehead[3]=108;
	filehead[4]=3;
	filehead[5]=0;//biSize=224388+54=224442=ox36CBA
	for(i = 0;i<H;i++)
		for(j=0;j<W;j++)
		{
			fread(&pp,1,3,inputfile);
			Pixel[i][j].B=pp.B;
			Pixel[i][j].G=pp.G;
			Pixel[i][j].R=pp.R;
		}
	for(i = 0;i<H2;i++)
		for(j=W;j<W2;j++)
		{
			
			Pixel[i][j].B=10;
			Pixel[i][j].G=220;
			Pixel[i][j].R=30;
		}
	for(i = H;i<H2;i++)
		for(j=0;j<W;j++)
		{
			
			Pixel[i][j].B=220;
			Pixel[i][j].G=10;
			Pixel[i][j].R=60;
		}
	
	for(i = 0;i<H2;i++)
		for(j=0;j<W3;j++)
		{
			
			Pixel[i][j].B=10;
			Pixel[i][j].G=2;
			Pixel[i][j].R=130;
		}
	outfile=fopen("addWindow.bmp","wb");
	fwrite(filehead,1,54,outfile);
	for(i = 0;i<H2;i++)
		for(j=0;j<W2;j++)
			fwrite(&Pixel[i][j],1,3,outfile);
	fclose(outfile);
	fclose(inputfile);
	return 0;

}