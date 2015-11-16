#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <dos.h>

float angulo(float X1, float Y1,float X2,float Y2)
{
	float ang=atan((Y2-Y1)/(X2-X1));
	ang=ang*57.29;
	if(!ang)
	{
		if(Y1==Y2 && X1<X2) return 0;
		if(X1==X2 && Y1<Y2) return 90;
		if(Y1==Y2 && X1>X2) return 180;
		if(X1==X2 && Y1>Y2) return 270;
	}

	if (ang < 90  && ang > 0 && Y2 > Y1)
		return ang;
	if (ang > -90 &&  Y2 > Y1)
		return 180+ang;
	if (ang > 0 && X2 < X1)
		return 180+ang;
	if (ang > -90 && Y1 > Y2)
		return 360+ang;
}


float distancia(float x1, float y1,float x2,float y2)
{
	float distancia;
	distancia=sqrt( pow((x2-x1),2) + pow((y2-y1),2) );
	return distancia;
}


float redondea(float num=0)
{
	float aux;
	aux=num- floor(num);			//saco la parte decimal
	if(aux>=0.5) return (num-aux)+1;
	return num-aux;
}

void elipse(int X, int Y, int a, int b, int color=GREEN)
{
	int x=X,y=Y;
	putpixel(x+a,(480-y)+b,color);		//EL PRIMER PIXEL
}


void main(void)
{
	int X=320,Y=240,a=100,b=80;
	int gdriver = DETECT, gmode;
	randomize();
	initgraph(&gdriver, &gmode,"c:/bc31/bgi");

	elipse(X,Y,a,b);
	getch();	getch();


	closegraph();
}
