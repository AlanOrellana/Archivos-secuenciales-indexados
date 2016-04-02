//============================================================================
// Name        : Archivos.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

void altas(int col,int fil)
{
struct nodo *bus=NULL;
struct nodo *ele=NULL;
int clv;
FILE *a;
a=fopen("c:\\agenda.dat","ab");
otra_vez://///////etiqueta para leer de nuevo si la clave esta repetida
cleardevice();
setfillstyle(11,RED);
bar(0,0,col,fil);
marco(0,0,col,fil,"",WHITE,LIGHTGRAY);
menu1(col);
menu2();
setfillstyle(1,GREEN);
marco(100,150,550,350,"AGREGAR TELEFONO",2,14);
gotoxy(20,12);printf("No.RAPIDO:");fflush(stdin);
gotoxy(35,12);scanf("%i",&datos.clave);
gotoxy(20,13);printf("NOMBRE:");fflush(stdin);
gotoxy(35,13);gets(datos.nombre);
gotoxy(20,14);printf("E-MAIL:");fflush(stdin);
gotoxy(35,14);gets(datos.email);
gotoxy(20,15);printf("EDAD:");fflush(stdin);
gotoxy(35,15);scanf("%i",&datos.edad);
gotoxy(20,16);printf("TELEFONO:");fflush(stdin);
gotoxy(35,16);gets(datos.telefono);
gotoxy(20,17);printf("DOMICILIO:");fflush(stdin);
gotoxy(35,17);gets(datos.domicilio);
clv=((datos.clave)%11);
bus=buscar(clv);
if(bus)
   {
   outtextxy(400,400,"El No. rapido ya existe...");
   getch();
   goto otra_vez;
   }
ele=crea_nodo();
if(ele)
   {
   ele->clave=datos.clave;
   ele->puntero_archivo=contador;
   ele->sig=NULL;
   insertar(ele,clv);
   fseek(a,(contador-1)*(sizeof(struct elementos)),SEEK_SET);
   fwrite(&datos,sizeof(struct elementos),1,a);
   contador++;
   outtextxy(400,400,"Informacion insertada...");
   getch();
   }
else
   {
   goto otra_vez;
   }
fclose(a);
}
void individual()
{
struct nodo *bus=NULL;
int clv,d;
FILE *a;
a=fopen("c:\\agenda.dat","rb");
setfillstyle(1,GREEN);
marco(100,150,550,350,"CONSULTAR PERSONA",2,14);///0-15 14 amarillo
gotoxy(20,12);printf("No. Rapido:");
fflush(stdin);
gotoxy(35,12);scanf("%i",&datos.clave);
clv=((datos.clave)%11);
bus=buscar(clv);
if(!bus)
   {
   outtextxy(400,400,"El No. Rapido no existe...");
   getch();
   goto final;
   }
d=bus->puntero_archivo;
fseek(a,(d-1)*(sizeof(struct elementos)),SEEK_SET);
fread(&datos,sizeof(struct elementos),1,a);
gotoxy(20,13);printf("NOMBRE:");
gotoxy(35,13);puts(datos.nombre);
gotoxy(20,14);printf("E-MAIL:");
gotoxy(35,14);puts(datos.email);
gotoxy(20,15);printf("EDAD:");
gotoxy(35,15);printf("%i",datos.edad);
gotoxy(20,16);printf("TELEFONO");
gotoxy(35,16);puts(datos.telefono);
gotoxy(20,17);printf("DOMICILIO:");
gotoxy(35,17);puts(datos.domicilio);
final:
getch();
fclose(a);
}
void pantalla(int col,int fil)
{
int z=0,y=4;
FILE *a;
struct nodo *aux=NULL;
cleardevice();
setfillstyle(11,RED);
bar(0,0,col,fil);
a=fopen("c:\\agenda.dat","rb");
marco(1,1,col,fil,"CONSULTAR TODO",2,14);
setfillstyle(1,BLUE);
bar(5,10,col-10,35);
gotoxy(2,2);printf("No.RAPIDO");
gotoxy(13,2);printf("NOMBRE");
gotoxy(40,2);printf("E-MAIL");
gotoxy(70,2);printf("TELEFONO");
rewind(a);
for(z=0;z<=10;z++)
    {
    aux=inicio[z];
    while(aux)
            {
               fseek(a,(aux->puntero_archivo-1)*sizeof(struct elementos),SEEK_SET);
               fread(&datos,sizeof(struct elementos),1,a);
               imprimir(y);
               y++;
               aux=aux->sig;
            }
    }
fclose(a);
getch();
}
void imprimir(int y)
{
gotoxy(2,y);printf("%i",datos.clave);
gotoxy(13,y);puts(datos.nombre);
gotoxy(40,y);puts(datos.email);
gotoxy(70,y);puts(datos.telefono);
}
void subir_memoria()
{
FILE *a;
struct nodo *ele=NULL;
int clv, aux=0;
marco(295,390,590,460,"",2,14);
outtextxy(300,400,"Cargando datos...");
if((a=fopen("c:\\agenda.dat","rb"))==NULL)
   {
   outtextxy(300,410,"Error, no se puede abrir el archivo...");
   }
else
   {
   rewind(a);
   while(!feof(a))
      {
      fread(&datos,sizeof(struct elementos),1,a);
      if(datos.clave!=aux)
         {
      clv=((datos.clave)%11);
         ele=crea_nodo();
         if(ele)
          {
          ele->clave=datos.clave;
          ele->puntero_archivo=contador;
         ele->sig=NULL;
         insertar(ele,clv);
         contador++;
         aux=datos.clave;
         }
       }
      }
   fclose(a);
   }
outtextxy(300,420,"Carga de datos finalizada...");
outtextxy(300,440,"Presione una tecla para continuar...");
getch();
}
struct nodo *buscar(int clv)
{
struct nodo *p=NULL;
p=inicio[clv];
while(p)
      {
      if(datos.clave==p->clave)
         return(p);
      else
         p=p->sig;
      }
return(NULL);
}
