#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<iostream.h>
#define max 20       //el tama¤o de las palabras
#define ESC 0x1b   //DEFINE LA TECLA ESC

int num_pal=0;
char resp;
typedef struct tipoceldaABB
{
   struct tipoceldaABB *izq,*der,*arr;
   char etiqueta[max];
   int nivel;
} *nodoABB;
typedef nodoABB ABB;

ABB raiz=NULL;


//FUNCION QUE CREA LA RAIZ DEL ARBOL
ABB Crear(char et[max])
{
  ABB raiz;
   raiz = (ABB)malloc(sizeof(struct tipoceldaABB));
  if (!raiz)      //si falla malloc
    {
      printf("ERROR: Memoria Insuficiente.");
      getch();
      exit(0);
    }

  strcpy(raiz->etiqueta,et);
  raiz->arr = NULL;               //arriba de la raiz no hay nadie
  raiz->izq = NULL;               //a la izquierda de la raiz no hay nadie
  raiz->der = NULL;              //a la derecha de la raiz no hay nadie
  raiz->nivel=0;                  //el nivel de la raiz es 0
  num_pal++;
  printf("SE AGREGO \"%s\" AL DICCIONARIO \n",et);
  return(raiz);
}

//RECIBE EL DATO A INSERTAR, LA RAIZ DEL ARBOL Y LA DIRECCION DEL NODO PADRE
void Inserta(char x[max], ABB *t,int niv,ABB *padre)
{
if(num_pal==0)
   *t=Crear(x);
else
{

 if(!(*t))
 {
   *t=(nodoABB)malloc(sizeof(struct tipoceldaABB));
    if(!(*t))      //si falla malloc
      {
         printf("MEMORIA INSUFICIENTE \nNO SE PUDO INSERTAR  \"%s\" AL DICCIONARIO",x);
         getch();
         exit(0);
      }
    strcpy((*t)->etiqueta,x);
    printf("SE AGREGO \"%s\" AL DICCIONARIO \n",x);
    (*t)->arr=*padre;
    (*t)->der=NULL;
    (*t)->izq=NULL;
    (*t)->nivel=niv;
    num_pal++;
 }
  else
   {
      padre=t;
      if( strcmpi(x,(*t)->etiqueta) == 0 )
         {
         printf("LA PALABRA \"%s\" YA EXISTE EN EL DICCIONARIO \n",x);
         getch();
         }

      if( strcmpi(x,(*t)->etiqueta) < 0 )
         Inserta(x,&((*t)->izq),++niv,&(*padre));
      else
         if( strcmpi(x,(*t)->etiqueta) > 0 )
            Inserta(x,&(*t)->der,++niv,&(*padre));
   }
}//fin del else
}



//DEVUELVE UN PUNTERO EN DONDE SE ENCUENTRA EL MENOR ELEMENTO DEL ARBOL QUE RECIBE COMO PARAMETRO
ABB MENOR(ABB *p)
{
if((*p)->izq==NULL)
   return(*p);
else
   MENOR(&(*p)->izq);
}



//DISMINUYE EN UNO LOS NIVELES DE LOS NODOS DEL ARBOL PASADO COMO PARAMETRO
void REACOMODAR_NIVELES(ABB P)
{
if(P)
   {
   REACOMODAR_NIVELES(P->izq);
   REACOMODAR_NIVELES(P->der);
   P->nivel=P->nivel-1;
   }
}

//RECIBE COMO PARAMETRO LA DIRECCION QUE SE QUIERE ELIMINAR
void ELIMINAR (ABB *TEMP)
{
ABB AUXILIAR;
if((*TEMP)->izq==NULL&&(*TEMP)->der==NULL)//si es una hoja
   {
      if((*TEMP)->arr->izq==(*TEMP))
         (*TEMP)->arr->izq=NULL;

         else   if((*TEMP)->arr->der==(*TEMP))
            (*TEMP)->arr->der=NULL;

         else   if((*TEMP)->arr==NULL)   //SI ES LA RAIZ EL UNICO ELEMENTO
            raiz=NULL;

   free((*TEMP));
   num_pal--;
   }
else
   if((*TEMP)->der&&(*TEMP)->izq)//si tiene dos hijos
      {
         ABB P=MENOR(&(*TEMP)->der);   //BUSCO EL MENOR ELEMENTO DEL SUBARBOL DERECHO...
         strcpy((*TEMP)->etiqueta,P->etiqueta);      //Y LO SUSTITUYO POR EL NODO A ELIMINAR
         ELIMINAR(&P);   //ELIMINO EL NODO QUE SUSTITUI
      }
else
if((*TEMP)->der)//si solo tiene hijo a la derecha
   {
   AUXILIAR= *TEMP;
   *TEMP=(*TEMP)->der;

      if(AUXILIAR->arr->izq==AUXILIAR)
         AUXILIAR->arr->izq=*TEMP;
      else if(AUXILIAR->arr->der==AUXILIAR)
         AUXILIAR->arr->der=*TEMP;

   REACOMODAR_NIVELES(*TEMP);
   num_pal--;
   free(AUXILIAR);
   }
else   if((*TEMP)->izq)//si solo tiene hijo a la izquierda
   {
   AUXILIAR= *TEMP;
   *TEMP=(*TEMP)->izq;

      if(AUXILIAR->arr->izq==AUXILIAR)
         AUXILIAR->arr->izq=*TEMP;
      else
         if(AUXILIAR->arr->der==AUXILIAR)
			AUXILIAR->arr->der=*TEMP;
			
   REACOMODAR_NIVELES(*TEMP);
   num_pal--;
   free(AUXILIAR);
   }

}//fin de la funcion eliminar



//DEVUELVE LA PROFUNDIDAD DEL ARBOL RECIBIDO COMO PARAMETRO
int MAYOR_NIVEL(ABB p)
{
if(!p)   return 0;
else
   {
    int nivelI=MAYOR_NIVEL(p->izq);
    int nivelD=MAYOR_NIVEL(p->der);
      if (nivelI>nivelD)   return nivelI+1;
         else
            return  nivelD+1;
   }
}



void POR_NIVELES(ABB p,int nivel)
{
if (p)
   {
      POR_NIVELES(p->izq,nivel);
      POR_NIVELES(p->der,nivel);
      if (p->nivel==nivel)
         cout<<p->etiqueta<<" ";
   }
}


void EN_ORDEN(ABB p)
{
if(p!=NULL)
   {
      EN_ORDEN(p->izq);
      cout<<p->etiqueta<<" ";
      EN_ORDEN(p->der);
   }
}


void POSTORDEN(ABB p)
{
if(p!=NULL)
   {
      POSTORDEN(p->izq);
      POSTORDEN(p->der);
      cout<<p->etiqueta<<" ";
   }
}




void PREORDEN(ABB p)
{
if(p!=NULL)
   {
      cout<<p->etiqueta<<" ";
      PREORDEN(p->izq);
      PREORDEN(p->der);
   }
}



//BUSCA LA ETIQUETA X EN EL ARBOL P
ABB BUSCAR(ABB *p,char x[max])
{
if((*p)==NULL)               //SI NO LO ENCUENTRA DEVUELVE UN VALOR DE 0
   return(0);
else
   if( strcmpi(x,(*p)->etiqueta) == 0 )   //SI ES ENCONTRADO DEVUELVE UN PUNTERON A LA DIRECCION DEL NODO BUSCADO
      return((*p));

else   if( strcmpi(x,(*p)->etiqueta) < 0 )
      return( BUSCAR(&(*p)->izq,x) );
else
      return( BUSCAR(&(*p)->der,x) );
}



//VERIFICA EL ARCHIVO QUE SE DESEE ( P.ejem: C:\TC\BIN\HOLA.CPP )
int VERIFICAR_ARCH IVO()
{
char archivo[50];//VARIABLE PARA ALMACENAR EL NOMBRE DEL ARCHIVO
FILE *pfe;         //UN PUNTERO A UN ARCHIVO
char palabra[20];   //VARIABLE PARA GUARDAR LAS PALABRAS QUE SE VAYAN FORMANDO
char c=1;//PARA QUE LA SEGUNDA VEZ QUE SE QUIERA CHECAR UNA CADENA C TENGA UN VALOR DISTINTO DE FIN DE CADENA
int CONT=-1;
int z=1;

clrscr();
printf ("INTRODUZCA LA RUTA DE ACCESO COMPLETA DEL ARCHIVO INCLUYENDO SU EXTENSIàN\n");
gets (archivo);

if ((pfe = fopen (archivo, "r")) == NULL)
   {
   printf ("\nERROR: No es posible abrir %s.\n", archivo);
   getch();
   return(1);
   }


while (!feof(pfe))  //MIENTRAS NO SE LLEGUE AL FINAL DEL ARCHIVO
 {

   while(c)   //MIENTRAS C SEA DIFERENTE DE FIN DE ARCHIVO
   {
      c=fgetc(pfe);      /**********ojooooooooooooooo**************/
      if(c==' '||c=='\n'||feof(pfe))      //SI C ES UN ESPACIO O UN SALTO DE LINEA
      break;

      else
      {
      CONT++;
      if (!((c>=33&&c<=47) || (c>=58&&c<=64)))      //PARA IGNORAR LOS SIMBOLOS ESPECIALES
         palabra[CONT]=c;
      }
   }
palabra[CONT+1]=0;

if(!BUSCAR(&raiz,palabra))
   {
   printf("\n\nPALABRA #%d: \"%s\"  NO SE ENCUENTRA EN EL DICCIONARIO ",z,palabra);
   printf("\nDESEA AGREGARLA (s/n)? ");
   cin>>resp;
   if(resp=='s'||resp=='S')   //si presionas ESC se termina el BUCLE
   Inserta(palabra,&raiz,0,NULL);
   }

CONT=-1;
z++;
}
if(fclose(pfe)!=0)
   {
   printf("ERROR: NO SE PUDO CERRAR %s ",archivo);
   getch();
   return(1);
   }
return(0);
}//FIN DE LA FUNCION




//VERIFICA UN TEXTO INTRODUCIDO POR TECLADO
void VERIFICAR_TEXT O()
{
char frase[80],palabra[20];
char c=1;//PARA QUE LA SEGUNDA VEZ QUE SE QUIERA CHECAR UNA CADENA C TENGA UN VALOR DISTINTO DE O ( O FIN DE CADENA)
int cont_pal=1;
int a=0;
clrscr();

cout<<"TENGA CUIDADO DE NO DEJAR MAS DE UN ESPACIO EN BLANCO ENTRE PALABRA Y PALABRA\n";
cout<<"DAME UNA PARRAFO DE MAXIMO 80 CARACTERES\n";
gets(frase);

while(c)      //MIENTRAS NO SE LLEGUE AL FINAL DE LA CADENA
{
int CONT=-1;
   while(c!=' '&&c)      //MIENTRAS C SEA DIFERENTE DE ESPACIO Y FIN DE CADENA
   {
      c=frase[a];
      if(c==' ')      //SI C ES UN ESPACIO
      {
         a++;
         c=frase[a];
         break;
      }
      else
      {
      if (!((c>=33&&c<=47)||(c>=58&&c<=64)))      //para ignorar los simbolos especiales
         palabra[++CONT]=c;
      a++;
      }
   }
palabra[CONT+1]=0;

if(!BUSCAR(&raiz,palabra))
   {
   printf("\n\nPALABRA #%d: \"%s\"  NO SE ENCUENTRA EN EL DICCIONARIO ",cont_pal,palabra);
   printf("\nDESEA AGREGARLA (s/n)? ");
   cin>>resp;
   if(resp=='s'||resp=='S')   //si presionas ESC se termina el BUCLE
   Inserta(palabra,&raiz,0,NULL);
   }
cont_pal++;
}
}//FIN DE LA FUNCION




/**********************FUNCIàN PRINCIPAL***************************/
void main()
{
int opcion;
char pal[max];
textbackground(9);
textcolor(2);

do
{
salir:
clrscr();
gotoxy(5,3);printf(" BIENVENIDO AL PROGRAMA DE VERIFICACIàN DE ORTOGRAFIA");
gotoxy(5,4);printf(" DESARROLLADO POR: SERGIO DE LEàN LàPEZ (rocker_hlm@hotmail.com)");
gotoxy(5,7);printf(" EL DICCIONARIO ACTUAL CUENTA CON: %d PALABRAS",num_pal);
gotoxy(10,10);printf(" 1.-AGREGAR PALABRAS AL DICCIONARIO");
gotoxy(10,11);printf(" 2.-ELIMINAR PALABRAS DEL DICCIONARIO");
gotoxy(10,12);printf(" 3.-BUSCAR PALABRAS EN EL DICCIONARIO");
gotoxy(10,13);printf(" 4.-DESPLEGAR LAS PALABRAS DEL DICCIONARIO");
gotoxy(10,14);printf(" 5.-VERIFICAR EL TEXTO");
gotoxy(10,15);printf(" 6.-SALIR");

gotoxy(10,16);
printf("¨QUE NUMERO DE OPCION DESEAS? ");
cin>>opcion;

switch(opcion)
{


case 1:
clrscr();
do
   {
      printf("\nHAY %d PALABRAS EN EL DICCIONARIO ",num_pal);
      printf("\nTECLEE LA PALABRA A A¥ADIR: ");
      cin>>pal;
         Inserta(pal,&raiz,0,NULL);
      printf ("\nDESEA SEGUIR AGREGANDO PALABRAS (s/n)? ");
      cin>>resp;
   }
while(resp=='s'||resp=='S');   //si presionas ESC se termina el BUCLE
break;                     //FIN DEL CASO 1


case 2:
clrscr();
do
{
if(num_pal==0)
   {
   printf("\nEL DICCIONARIO ESTA VACIO NO HAY NADA QUE ELIMINAR");
   break;
   }
   printf("\nHAY %d PALABRAS EN EL DICCIONARIO ",num_pal);
   printf("\nDAME LA PALABRA A ELIMINAR ");
   cin>>pal;
   ABB TEMP=BUSCAR(&raiz,pal);
   if(TEMP)
      ELIMINAR(&TEMP);
   else
      printf("NO SE PUEDE ELIMINAR %s\n NO SE ENCUENTRA EN EL DICCIONARIO ",pal);

if(num_pal!=0)
   {
   printf("\nDESEA SEGUIR ELIMINANDO PALABRAS (s/n)? ");
   cin>>resp;
   }

else
   {
   printf("\nEL DICCIONARIO ESTA VACIO YA NO HAY NADA QUE ELIMINAR");
   break;
   }

}      //fin del while
while(resp=='s'||resp=='S');

break;//FIN DEL CASO 2


case 3:
clrscr();
do
{
printf("\nHAY %d PALABRAS EN EL DICCIONARIO ",num_pal);
printf("\nDAME LA PALABRA A BUSCAR ");
cin>>pal;
if(BUSCAR(&raiz,pal)==0)
   {
   printf("LA PALABRA  \"%s\"  NO SE ENCUENTRA EN EL DICCIONARIO ",pal);
   printf("\nDESEA AGREGARLA (s/n)? ");
   cin>>resp;
   if(resp=='s'||resp=='S')   //si presionas ESC se termina el BUCLE
      Inserta(pal,&raiz,0,NULL);
   }
else
   printf("\nSI SE ENCONTRO \"%s\"  EN EL DICCIONARIO",pal);

printf("\nDESEA SEGUIR BUSCANDO PALABRAS (s/n)? ");
cin>>resp;
}      //fin del while
while(resp=='s'||resp=='S');
break;


case 4:
do
{
clrscr();
gotoxy(5,4);printf("DESPLEGAR PALABRAS DEL DICCIONARIO (p, o, i, n, q)");
gotoxy(5,6);printf("EL SIGNIFICADO DE LAS OPCIONES ES EL SIGUIENTE");
gotoxy(10,10);printf(" p.-PREORDEN");
gotoxy(10,11);printf(" o.-POSTORDEN");
gotoxy(10,12);printf(" i.-INORDEN");
gotoxy(10,13);printf(" n.-POR NIVELES");
gotoxy(10,14);printf(" q.-SALIR DE ESTA OPCIàN");
printf("\n\nTECLEE LA LETRA SEGUN SEA SU OPCION DESEADA ");
cin>>resp;
clrscr();
switch(resp)
{
case'p':case'P':
   printf("\n\nRECORRIDO EN PREORDEN...\n ");
   PREORDEN(raiz);
   break;

case'o':case'O':
      printf("\n\nRECORRIDO EN POSTORDEN...\n ");
      POSTORDEN(raiz);
      break;

case'i':case'I':
   printf("\n\nRECORRIDO INORDEN...\n ");
   EN_ORDEN(raiz);
break;

case'n':case'N':
printf("\n\nRECORRIDO POR NIVELES\n");

//REACOMODAR_NIVELES(raiz,0);
int nivel_max=MAYOR_NIVEL(raiz);
   for(int i=0;i<nivel_max;i++)
      POR_NIVELES(raiz,i);

break;

case'q':case'Q':
goto salir;

default:
printf("OPCION NO VALIDA INTENTE DE NUEVO");
}//fin del switch
printf ("\n\n\nPARA SALIR DE ESTE SUBMENU PRESIONE ESC...\nPRESIONE CUALQUIER TECLA PARA CONTINUAR...");
}//FIN DEL DO
while(getch()!=ESC);   //si presionas ESC se termina el BUCLE

break;//FIN DEL CASO 4


case 5:
do
{
clrscr();
gotoxy(10,10);printf("1.-CHECAR TEXTO DESDE TECLADO");
gotoxy(10,11);printf("2.-CHECAR UN ARCHIVO GUARDADO EN DISCO");
gotoxy(10,12);printf("3.-SALIR DE ESTA OPCION");
gotoxy(10,13);printf("4.-SALIR DEL PROGRAMA");

printf("\n\nTECLEE EL NUMERO DESEADO ");
cin>>resp;
switch(resp)
{

case '1':
VERIFICAR_TEXTO();
break;

case '2':
VERIFICAR_ARCHIVO();
break;

case '3':
goto salir;

case '4':
exit(0);

default:
printf("OPCION NO VALIDA INTENTE DE NUEVO");

}//fin del switch
printf ("\nPARA SALIR DE ESTE SUBMENU PRESIONE ESC...\nPRESIONE CUALQUIER TECLA PARA CONTINUAR...");
}
while(getch()!=ESC);   //si presionas ESC se termina el BUCLE
break;


case 6: //CASO 6 SALIR DEL PROGRAMA
exit(0);


default:
clrscr();
printf("OPCION NO VALIDA INTENTE DE NUEVO");

}//FIN DEL SWITCH
printf ("\n\nPARA SALIR DEL PROGRAMA PRESIONE ESC...\nPRESIONE CUALQUIER TECLA PARA CONTINUAR...");
}//fin de do
while(getch()!=ESC);   //si presionas ESC se termina el BUCLE

}//FIN DE LA FUNCION PRINCIPAL