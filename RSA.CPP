/*	ENCRIPTAMIENTO DE UN TEXTO USANDO EL METODO RSA	*/
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <string.h>
#include <math.h>
#include <iostream.h>

int Z;
int D;

/*		¨QUE PASA CON LOS ESPACIOS
		Y LAS '¥' Y DEMAS SIMBOLOS?	*/
char Simbolico(int SIMBOLO)
{
int cont=1;
	for(char caracter='A'; caracter <= 'Z'; caracter++)
	{
		if (SIMBOLO==cont)
			return caracter;
		if (caracter==SIMBOLO)
			return cont;
		cont++;
	}
return 0;
}

int CalcE()
{
int A=0, B=0;
	for(int cont=0; cont<=Z; cont++)
	{
		A=fmod((cont*D), Z);
		B=fmod(1,Z);
		if( A == B) return cont;
	}
return cont;
}



int EsPrimo(int numero=0)
{
int veces=0;

	for(int cont=1; cont<=numero; cont++)
		if(!(numero % cont))
			veces++;
	if (veces==2)				//ES PRIMO
		return 1;
	else return 0;
}

int Primo(int Z=0)
{
int veces;
int num=0;
	for (num=1; num<Z; num++)
	{
		if(EsPrimo(num))
			if( Z%num )
				return num;
	}
return num;
}


void main(void)
{
	char LLANO[80]={"SUZANNE"};
	int ENCRIPTADO[80]={0};		//ARREGLO DE ENTEROS PARA ALMACENAR LOS SIMBOLOS ENCRIPTADOS
	char DESENCRIPTADO[80]={0};	//ARREGLO DE CARACTERES PARA ALMACENAR LOS SIMBOLOS DESENCRIPTADOS
	long double C=0, P=0;
	int p=0;	int q=0;			//1ø SELECCIONAR 2 NUMEROS PRIMOS

	textbackground(BLACK);		//FONDO COLOR ROJO
	clrscr();				//LIMPIAR PANTALLA
	printf("INTRODUZCA EL MENSAJE A ENCRIPTAR (EN MAYUSCULAS): ");
	scanf("%s",LLANO); 	strcpy(LLANO,strupr(LLANO));
	printf("INTRODUZCA EL 1ø # PRIMO: "); scanf("%d",&p);
	printf("INTRODUZCA EL 2ø # PRIMO: "); scanf("%d",&q);
	printf("\nMENSAJE LLANO: %s",LLANO);

	int N=p*q;            //2ø CALCULAR 'N' Y
	Z=(p-1) * (q-1); 		//CALCULAR 'Z'
	D=Primo(Z);              //3ø SELECCIONAR UN NUMERO PRIMO (EL MENOR) RESPECTO A 'Z' LLAMANDOLO 'D'
	int e=CalcE(); 		//4ø CALCULAR e

	printf("\nP: %d \t Q: %d",p, q);
	printf("\nN: %d \t Z: %d \tD: %d",N, Z, D);
	printf("\nE: %d \n",e);

	printf("\nPRESIONE UNA TECLA PARA CONTINUAR...........");
	getch();

	/*********************ENCRIPTANDO******************/
	int cont=0;
	char caracter=0;

		textbackground(BLUE);		//FONDO COLOR ROJO
		clrscr();
		gotoxy(25, 1); cout<<"ENCRIPTANDO";
		int Y=3;
		gotoxy(2, Y); cout<<"SIMBOLO";
		gotoxy(15, Y); cout<<"NUMERICO";
		gotoxy(30, Y); cout<<"P a la N";
		gotoxy(45, Y); cout<<"ENCRIPTADO";

		Y=4;
		while(cont < strlen(LLANO))
		{
			Y++;
			caracter=LLANO[cont];
			gotoxy(5, Y); cout<<caracter;

			C=Simbolico(caracter);
			gotoxy(18, Y); cout<<C;

			C=pow(C, e);			//SE ELEVA A LA 'E'
			gotoxy(30, Y); cout<<C;

			C=fmod(C, N);				//SE SACA EL MODULO
			ENCRIPTADO[cont]=C;		//AQUI SE ALMACENA EL MENSAJE ENCRIPTADO (ENTEROS)

			gotoxy(50, Y); cout<<C;
			cont++;
		};

		getch();
		textbackground(LIGHTBLUE);		//FONDO COLOR ROJO
		clrscr();
	/**********************DESENCRIPTANDO*****************/
		cont=0;
		gotoxy(25, 1); cout<<"DESENCRIPTANDO";
		Y=3;
		gotoxy(2, Y);	cout<<"ENCRIPTADO";
		gotoxy(15, Y); cout<<"C a la D";
		gotoxy(30, Y); cout<<"NUMERICO";
		gotoxy(45, Y);		cout<<"SIMBOLO";

		Y=4;
		while(cont < strlen(LLANO))
		{
			Y++;
			P=ENCRIPTADO[cont];
			gotoxy(5, Y); cout<<P;

			P=pow(P, D);
			gotoxy(16, Y); cout<<P;

			P=fmod(P, N);
			gotoxy(33, Y); cout<<P;

			DESENCRIPTADO[cont]=Simbolico(P);
			gotoxy(50, Y); cout<<DESENCRIPTADO[cont];
			cont++;
		};
	flushall();
	getch();		//HACER UNA PAUSA
}