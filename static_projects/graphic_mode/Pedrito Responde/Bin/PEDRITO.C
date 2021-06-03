/* * * * * * * * * * * * * * * * * * PEDRITO RESPONDE * * * * * * * * * * * * *
*   Desarrollador:
*     Br.Jeyson Eduardo
*   Carrera:
*	   Ingenieria en computacion - UNI_NICARAGUA
*   Grupo: 
*       2m1-co 
*	Fecha:
*	 Abril del 2021
*   Modo:
*     Grafico 
*   Dimension:
*     640x480   
*/
#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<mouse.h>
#include <string.h>
#include <time.h>
void main()
{
	int driver= DETECT,mode,x,y,on,i=0,j,vali=0,w,v=0;
	char pedrito[50],validacion[50],mensage,val[50],pregunta[50];
	char ra[50][41];
	FILE * archivo;
	srand (time(NULL));
	for(i=0;i<50;i++){
		for(j=0;j<41;j++){
			ra[50][41]='\0';
		}
	}
	strcpy(pedrito,"Pedrito podrias responder mi pregunta");
	initgraph(&driver,&mode,"C:\\TC20\\BIN");
	i=0;

	w=i;
	setfillstyle(SOLID_FILL, 0);
	bar(0,0,640,480);
	mlimit(1,40,75,597,411);
	setfillstyle(SOLID_FILL, 7);
	bar(40,75,597,411);
	setfillstyle(SOLID_FILL, 0);
	bar(53,91,578,398);
	settextstyle(GOTHIC_FONT ,HORIZ_DIR,1);
	setcolor(WHITE);
	outtextxy(70,151, "Peticion:");
	outtextxy(70,186, "Pregunta:");
	outtextxy(70,221, "Respuesta:");
	settextstyle(GOTHIC_FONT ,HORIZ_DIR,3);
	outtextxy(206,108, "PEDRITO RESPONDE");
	setfillstyle(SOLID_FILL, 15);
	bar(156,149,465,169);
	bar(156,181,465,202);
	settextstyle(SMALL_FONT ,HORIZ_DIR,5);
	setcolor(WHITE);
	outtextxy(65,382, "EJEMPLO PARA GEOMETRIA COMPUTACIONAL");
	setfillstyle(SOLID_FILL,15);
	bar(483,149,540,166);
	setcolor(10);
	line(483,149,540,149);
	line(483,149,483,166);
	setcolor(BLUE);
	line(483,166,540,166);
	line(540,149,540,166);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	setcolor(0);
	outtextxy(495,155,"Nuevo");
	setfillstyle(SOLID_FILL,15);
	bar(480,179,540,197);
	setcolor(10);
	line(480,179,540,179);
	line(480,179,480,197);
	setcolor(BLUE);
	line(480,197,540,197);
	line(540,197,540,179);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	setcolor(0);
	outtextxy(505,185,"OK");
	setfillstyle(SOLID_FILL,15);
	bar(522,97,570,113);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	setcolor(0);
	outtextxy(523,104,"Cerrar");
	
	msituar(1,320,235);
	setlinestyle (SOLID_LINE, THICK_WIDTH,3);
	while(1){ 
		setcolor(10);
		line(483,149,540,149);
		line(483,149,483,166);
		setcolor(BLUE);
		line(483,166,540,166);
		line(540,149,540,166);
		/*ok*/
		setcolor(10);
		line(480,179,540,179);
		line(480,179,480,197);
		setcolor(BLUE);
		line(480,197,540,197);
		line(540,197,540,179);
		mver();
		x=mxpos(1);/*envia las coordenadas en el eje de las x*/
		y=mypos(1);/*lo mismo pero con las y*/
		on=mclick();/*retorna el numero del boton del mouse*/
		if(on==1){
			if(x>=483 && x<=540 && y>=149 && y<=166){
				/*nuevo*/
				setcolor(BLUE);/*mover*/
				line(483,149,540,149);
				line(483,149,483,166);
				setcolor(10);
				line(483,166,540,166);
				line(540,149,540,166);
				delay(500);
				vali=0;
				v=0;
				setfillstyle(SOLID_FILL, 15);
				bar(156,181,465,202);
				setfillstyle(SOLID_FILL, 15);
				bar(156,149,465,169);
				setfillstyle(SOLID_FILL, 0);
				bar(156,210,550,237);
	
			}else if(x>=480 && x<=540 && y>=179 && y<=197){
				/*ok*/
				setcolor(BLUE);
				line(480,179,540,179);
				line(480,179,480,197);
				setcolor(10);
				line(480,197,540,197);
				line(540,197,540,179);
				delay(500);
				if(vali==0 && v==1){
					setfillstyle(SOLID_FILL, 0);
					bar(156,210,550,237);
					j=rand()%(w);
					settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
					setcolor(15);
					outtextxy(158,230, ra[j]);
					
				}else if(vali==1 && v==1){
					setfillstyle(SOLID_FILL, 0);
					bar(156,210,550,237);
					
					settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
					setcolor(15);
					outtextxy(158,230, validacion);
				}
				msituar(1,320,235);
			}else if(x>=522 && x<=570 && y>=97 && y<=113){
					setcolor(RED);
					outtextxy(523,104,"Cerrar");
					delay(500);
					exit(1);
			}else if(x>=156 && y>=181 && x<=465 && y<=202){
				mocultar();	
				setfillstyle(SOLID_FILL, 15);
				bar(156,181,465,202);
				v=1;
				for(i=0;i<50;i++){
				pregunta[i]='\0';
				}i=0;
				while(1){
					mensage=getch();
					if(mensage==13 && i>0 )	{
					pregunta[i]='\0';
					break;
					}
					else if(mensage==8)	{
					if(i>0){
						setfillstyle(SOLID_FILL, 15);
						bar(156,181,465,202);
						i--;
						pregunta[i]='\0';
						settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
						setcolor(0);
						pregunta[i]='\0';
						outtextxy(158,185, pregunta);
						}
					}else {
						if(i<39){
						pregunta[i]=mensage;
						settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
						setcolor(0);
						outtextxy(158,185, pregunta);
						i++;
						}
					}
				}
			}else if(x>=156 && y>=149 && x<=465 && y<=169){
				mocultar();vali=1;
				setfillstyle(SOLID_FILL, 15);
				bar(156,149,465,169);
				for(i=0;i<50;i++){
				validacion[i]='\0';
				val[i]='\0';
				}i=0;
				while(1){
					mensage=getch();
					if(mensage==13 && i>0 )	{
					validacion[i]='\0';
					settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
					setcolor(0);
					outtextxy(158,154, pedrito);
					break;
					}
					else if(mensage==8)	{
					if(i>0){
						setfillstyle(SOLID_FILL, 15);
						bar(156,149,465,169);
						i--;
						validacion[i]='\0';
						settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
						setcolor(0);
						val[i]='\0';
						outtextxy(158,154, val);
						}
					}else {
						if(i<39){
						validacion[i]=mensage;
						settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
						setcolor(0);
						val[i]=pedrito[i];
						outtextxy(158,154, val);
						i++;
						}
					}
				}
			}		
				
		}
	}
	
	
	getch();
}