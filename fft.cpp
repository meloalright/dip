#include <stdio.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
#define H 512
#define W 512


/*struct{
      unsigned char B,G,R;
}Pixel[H][W],px[H][W];
*/
const double INFS=0.0;//zInfinitesimal=+0.0;
//const double fInfinitesimal=-0.0;
const double INF=1.0/INFS;//zInf=1.0/zInfinitesimal;
//const double NINF=-1.0/INFS;//fInf=-1.0/fInfinitesimal;
//double a_b_s[W][H],py[W][H],maxe = 0;

//no oo
//struct
typedef struct
{
		unsigned char B,G,R;
}pixel_RGB;
pixel_RGB Pixel[H][W],px[H][W];
typedef struct
{
	double r;
	double i;
	//int r;
	//int i;
}COMPLEX;
COMPLEX input[H][W];
COMPLEX output[H][W];
unsigned char py[H][W];
COMPLEX com_add(COMPLEX x,COMPLEX y)
{
	COMPLEX z;
	z.r=x.r+y.r;
	z.i=x.i+y.i;
	return z;
}
COMPLEX com_dvd(COMPLEX x,COMPLEX y)
{
	COMPLEX z;
	z.r=x.r-y.r;
	z.i=x.i-y.i;
	return z;
}
COMPLEX com_mul(COMPLEX x,COMPLEX y)
{
	COMPLEX z;
	z.r=x.r*y.r-x.i*y.i;
	z.i=x.r*y.i+x.i*y.r;
	return z;
}
COMPLEX com(double x,double y)
{
	COMPLEX z;
	z.r=x;
	z.i=y;
	return z;
}
//
//模长函数
double myabs(COMPLEX a){
	double x,y,ans,temp;
	x=fabs(a.r);
	y=fabs(a.i);
	if(x==0.0)ans=y;
	else if(y==0.0)ans=x;
	else if(x>y){temp=y/x;ans=x*sqrt(1.0+temp*temp);}
	else {temp=x/y;ans=y*sqrt(1.0+temp*temp);}
	return ans;
};

double getPositive(double x){
	return x>0?x:-x;
}
//fft
void fft(COMPLEX data[],int n,int isign){
	int i,j,k,step;
	COMPLEX ctemp,w,wp;
	double theta;
	for(i=1;i<n;i++){
		j=n+i;k=0;
		//i=1,2,3,4,5,6
		//j=2,3,4,5,6,7
		
		while(j>1){
			if(j%2==1){
				k = 2*k+1;
			}
			else{
				k = 2*k;
			}
			j = j/2;
		}
		if(k>i)
		{
			ctemp=data[i];
			data[i]=data[k];
			data[k]=ctemp;
			//k==0;j==1;//noexchange
			//k==1;j==1;//noexchange
			//k==0;j==1;//noexchange
			//k==1;j==1;//noexchange
			//k==1;j==1;//noexchange
			//k==2;j==1;//6<->2
		}
	}
	for(step=2;step<=n;step*=2){
		for(theta=-isign*M_PI*2/step,wp=com(cos(theta),sin(theta)),w=com(1.0,0.0),
			k=0;k<step/2;k++,w=com_mul(w,wp)){
			for(i=k;i<n;i+=step){
				j=i+step/2;
				ctemp=com_mul(w,data[j]);
				data[j]=com_dvd(data[i],ctemp);
				data[i]=com_add(data[i],ctemp);
			}
		}
	}
	if(isign==-1){
		for(i=0;i<n;i++){
			data[i].r=data[i].r*1.0/n;
			data[i].i=data[i].i*1.0/n;
		}
	}
}


double a_b_s[H][W],maxe=0;

int main()
{
    FILE *inputfile,*outfile;
	unsigned char filehead[54];
	int i,j;
	//init
	for(i = 0;i<H;i++){
		for(j=0;j<W;j++)
		{
			output[i][j]=com(0,0);//避免栈溢出就把512*512二维数组定义在全局段
			input[i][j]=com(0,0);
		}
	};
	for(i = 0;i<H;i++){
		for(j=0;j<W;j++)
		{
			py[i][j]=0;
			a_b_s[i][j]='0';
		}
	};

	inputfile = fopen("pushnoise.bmp","rb");//处理已经加噪声文件
	outfile = fopen("fft.bmp","wb");//
	fread(filehead,1,54,inputfile);
	fread(Pixel,3,W*H,inputfile);
	//com

	
	//翻转四角
	for(i=0;i<H;i++){
		for(j=0;j<W;j++)
		{
			input[i][j].r=(Pixel[i][j].R*pow(-1,i+j));//这里input[i][j].r是real
		}
	};
	

	//fft
	for(i=0;i<H;i++)
	{
		fft(&input[i][0],W,1);
		//dft(&output[i][0],&input[i][0],W,1);
	};
	
	//testcode
	/*
	for(i=0;i<W;i++){
		for(j=0;j<H;j++)
		{
			double x = myabs(input[i][j]);
			if(x>255)
				x=255;
			else if(x<0)
				x=0;
			Pixel[i][j].B=(unsigned char)x;
			Pixel[i][j].G=(unsigned char)x;
			Pixel[i][j].R=(unsigned char)x;

		}
	}
	fwrite(filehead,1,54,outfile);
	fwrite(Pixel,3,W*H,outfile);
	return 0;
	*/
	//testcode

	
	//turn
	for(i=0;i<H;i++){
		for(j=0;j<W;j++)
		{
			output[j][i] = input[i][j];//发生转置
			//input[j][i] = output[i][j];//发生转置
		}
	};



	//
	for(i=0;i<H;i++)
	{
		fft(&output[i][0],H,1);
		//dft(&output[i][0],&input[i][0],H,1);
		//
		//for(int s=0;s<H;s++)
			//cout << output[i][s].r << '+' << output[i][s].i << 'i' << endl;
	};



	//getMAX
	for(i=0;i<H;i++){
		for(j=0;j<W;j++)
		{
			if(output[i][j].r>maxe)
				maxe=output[i][j].r;
		}
	}
	maxe=maxe/255;
	printf("%f\n\n\n\n",maxe);
	int count=0,add=0;
	for(i=0;i<H;i++){
		for(j=0;j<W;j++)
		{
			//output[i][j].r=myabs(output[i][j].r)/3000;
			//output[i][j].i=myabs(output[i][j].i)/3000;
			output[i][j].r = output[i][j].r/5000;
			output[i][j].i = output[i][j].i/5000;
			a_b_s[i][j]=pow(sqrt(pow(output[i][j].r,2)+pow(output[i][j].i,2)),1.7);
			//a_b_s[i][j]=pow(myabs(mysqrt(output[i][j])),2);
			//a_b_s[i][j]=pow((output[i][j]),2.2);//1.7
			if(a_b_s[i][j]>255){
				a_b_s[i][j]=255;
			}
			else{
				a_b_s[i][j]=a_b_s[i][j];
			}
			/*if((double )a_b_s[i][j]<5){
				a_b_s[i][j]=0;
				++add;
			}*/
			py[i][j]=(unsigned char)a_b_s[i][j];
			//py[i][j]=easyFilter(i,j,(unsigned char)a_b_s[i][j]);
			//if((double )py[i][j]>100)
				//cout << "ok" << '@'<<i<<','<<j << '='<<py[i][j]<<endl;


		}
	}

	//
	for(i=0;i<H;i++){
		for(j=0;j<W;j++)
		{
			px[i][j].B=py[i][j];
			px[i][j].G=py[i][j];
			px[i][j].R=py[i][j];

		}
	}
	fwrite(filehead,1,54,outfile);
	fwrite(px,3,W*H,outfile);
	for(i=0;i<H;i++){
		for(j=0;j<W;j++)
		{
			if((int)px[i][j].R>230){
				cout <<i << ',' << j <<'@'<<"b=" <<(int)px[i][j].B ;
				cout <<"g=" <<(int)px[i][j].G ;
				cout <<"r=" <<(int)px[i][j].R << endl;
			}

		}
	}
	fclose(outfile);
	fclose(inputfile);
	return 0;

}