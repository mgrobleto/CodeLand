/* * * * * * * * * * * * * * * * * * Piedra Papel o Tijera* * * * * * * * * * * * *
*   Desarrolladores:
*     Br.LEONARDO JOSUE  ZAPATA CASTAÑEDA
*     Br.VICTOR MANUEL MORALES LARIOS
*	  Br.VICTOR JOSE ZAMORA MESA  
*   Carrera:
*	   Ingenieria en computacion - UNI_NICARAGUA
*   Grupo: 
*       2m1-co 
*	Fecha:
*	 Noviembre del 2020
*   Modo:
*     Grafico 
*   Dimension:
*     640x480   
*/
#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<mouse.h>
#include<time.h>
#include <string.h>
#include<dos.h>
void tijera(void);
void papel(void);
void roca(void);
int elegir(void);
void botones(int x,int y,int z,int c);
	void main()
	{
	 int driver=DETECT,mode,x,y,on,i,j,num[50],opc,puntos;
		char us[50][10],texto,n[5],val[50][5],validacion[50],mensage;

		FILE *archivo;srand (time(NULL));
		initgraph(&driver,&mode,"C:\\TC20\\bin");
		inicio:
		setfillstyle (SOLID_FILL ,9);
		bar(0,0,640,480);
		setfillstyle (SOLID_FILL ,12);
		bar(24,28,119,56);
		setfillstyle (SOLID_FILL ,12);
		bar(283,27,374,56);
		setfillstyle (SOLID_FILL ,12);
		bar(515,30,606,58);
		setfillstyle (SOLID_FILL ,12);
		bar(150,386,238,415);
		setfillstyle (SOLID_FILL ,12);
		bar(400,385,486,415);

		settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
		outtextxy(24,37,"Presentacion");
		settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
		outtextxy(300,37,"Jugar");
		settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
		outtextxy(527,38,"Registro");
		settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
		outtextxy(168,396,"Ayuda");
		settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
		outtextxy(426,395,"Salir");
		settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
		setcolor(15);
		outtextxy(90,230,"Piedra,papel o tijeras");

		mver();
		msituar(1,320,235);
		while(1){
			x=mxpos(1);/*envia las coordenadas en el eje de las x*/
			y=mypos(1);/*lo mismo pero con las y*/
			on=mclick();/*retorna el numero del boton del mouse*/
			if(on==1){
				if(x>=24 && x<=119 && y>=28 && y<=56){
					mocultar();
                   cleardevice();
					/*presentacion  */
					setfillstyle (SOLID_FILL ,9);
					bar3d(215,19,172,136,25,1);
					setfillstyle (SOLID_FILL ,9);
					bar3d(215,105,323,136,25,1);
					setfillstyle (SOLID_FILL ,9);
					bar3d(280,107,323,58,25,1);
					setfillstyle (SOLID_FILL ,9);
					bar3d(226,18,270,96,25,1);
					setfillstyle (SOLID_FILL ,9);
					bar3d(269,48,377,18,25,1);
					setfillstyle (SOLID_FILL ,9);
					bar3d(334,48,377,106,25,1);
					setfillstyle (SOLID_FILL ,9);
					bar3d(334,136,388,107,25,1);
					setfillstyle (SOLID_FILL ,9);
					bar3d(431,136,388,57,25,1);
					setfillstyle (SOLID_FILL ,9);
					bar3d(388,48,430,18,25,1);
					settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
					setcolor(15);
					outtextxy(200,180,"UNIVERSIDA NACIONAL DE INGENIERIA");
					settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
					setcolor(15);
					outtextxy(200,210,"PROYECTO DE PIEDRA, PAPEL Y TIJERAS");
					settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
					setcolor(15);
					outtextxy(200,240,"Docente");
					settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
					setcolor(15);
					outtextxy(200,270,"Nelson Alejandro Barrios Gonzales");
					settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
					setcolor(15);
					outtextxy(200,300,"Integrantes");
					settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
					setcolor(15);
					outtextxy(200,330,"LEONARDO JOSUE  ZAPATA CASTAÑEDA      2020-0346U");
					settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
					setcolor(15);
					outtextxy(200,360,"VICTOR MANUEL MORALES LARIOS      2020-0278U");
					settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
					setcolor(15);
					outtextxy(200,390,"VICTOR JOSE ZAMORA MESA      2020-0419U");
					settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
					setcolor(15);
					outtextxy(200,420,"Grupo 1M1-CO");
					mver();
					msituar(1,320,235);
					getch();
					goto inicio;

					/*presentacion*/
				}else if(x>=400 && y>=385 && x<=486 && y<=415){
					mocultar();
                   cleardevice();
					settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
					settextjustify(CENTER_TEXT,CENTER_TEXT);
					outtextxy((640/2),230,"SALIENDO...");
					setbkcolor(7);
					mver();
					msituar(1,320,235);
					sleep(5);
					exit(1);/*salida*/
				}else if(x>=150 && y>=386 && x<=238 && y<=415){
					/*ayuda*/
						setfillstyle (SOLID_FILL ,3);
						bar(0,0,640,480);

						setcolor(0);
						outtextxy(100,200,"SELECCIONA JUGAR");

						setcolor(0);
						outtextxy(100,230,"ELIJE ENTRE PIEDRA ");

						setcolor(0);
						outtextxy(100,260,"PAPEL O TIJERAS ");
						setcolor(0);
						outtextxy(100,290," DIVIERTETE :3");
						getch();
						goto inicio;

				}else if(x>=515 && y>=30 && x<=606 && y<=58){
					/*registros*/
					setfillstyle (SOLID_FILL ,9);
					bar(0,0,640,480);
					setfillstyle (SOLID_FILL ,15);
					bar3d(40,40,600,480,25,1);
					y=0;
					i=0;j=0;archivo=fopen("C:\\TC20\\BIN\\FICHERO\\ppt.txt","r");
					while(!feof(archivo)){
						texto=fgetc(archivo);
						if(texto>=48 && texto<=57){
							n[y]=texto;
							y++;
						}else if(texto=='|'){
							n[y]='\0';
							strcpy(val[j],n);
							for(x=0;x<5;x++){
								n[x]='\0';
							}
							us[j][i]='\0';
							j++;
							i=0;y=0;
						}else{
							us[j][i]=texto;
							i++;
						}
					}
					y=0;
					settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
					setcolor(0);
						outtextxy(160,35+y,"jugadores");
						outtextxy(400,35+y,"Victorias");
					for(x=0;x<j;x++){
						setcolor(0);
						settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
						outtextxy(160,55+y,us[x]);
						outtextxy(400,55+y,val[x]);
						y+=20;
					}
					fclose(archivo);
					getch();
					goto inicio;
				}else if(x>=283 	&& y>=27 && x<=374 && y<=56){
					setfillstyle (SOLID_FILL ,9);
					bar(0,0,640,480);
					settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
					textcolor(WHITE);
					outtextxy(140,240, "Nombre de usuario");
					for(i=0;i<50;i++){
						validacion[i]=' ';
					}i=0;
					while(1)		{
						mensage=getch();
						if(mensage==13 && i>0 )	{
						validacion[i]='\0';
						break;
						}
						else if(mensage==8)	{
						if(i>0){
							setfillstyle(SOLID_FILL, 9);
							bar(200,290,500,310);
							i--;
							validacion[i]='\0';
							settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
							setcolor(0);
							outtextxy(200,290, validacion);
							}
						}else {
							if(mensage>=65 && mensage<=90 && i<8 || mensage>=97 && mensage<=122 && i<8){
							validacion[i]=mensage;
							settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
							setcolor(0);
							outtextxy(200,290, validacion);
							i++;
							}
						}
					}/*para adelante*/
					archivo=fopen("C:\\TC20\\BIN\\FICHERO\\ppt.txt","a");
					fprintf(archivo,"%s",validacion);
					fclose(archivo);
					mocultar();
					setfillstyle (SOLID_FILL ,9);
					bar(0,0,640,480);
					setfillstyle(SOLID_FILL, 0);
					bar(55,65,505,155);
					bar(55,235,505,325);
					setcolor(15);
					rectangle(60,70,500,150);
					rectangle(60,240,500,320);
					settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
					setcolor(15);
					outtextxy(90,100, "   Dificil");

					settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
					setcolor(15);
					outtextxy(90,270, "    Facil");
					mver();
					msituar(1,320,240);
					while(1){
						x=mxpos(1);
						y=mypos(1);
						on=mclick();
						if(on==1){
							if(x>=55 && y>=65 && x<=505 && y<=155){/*dificil*/
							dificil:
								setfillstyle (SOLID_FILL ,9);
								bar(0,0,640,480);
								opc=elegir();
									setfillstyle (SOLID_FILL ,9);
									bar(55,143,250,359);
									sleep(1);
								if(opc==1){
									papel();
								}else if(opc==2){
									roca();
								}else {
									tijera();
								}
								setfillstyle (SOLID_FILL ,14);
								bar(418,408,228,457);
								settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
								setcolor(0);
								outtextxy(230,414, "Perdiste");
								botones(1,0,1,15);
								botones(1,0,1,15);
								mver();
								msituar(1,320,240);
								while(1){
									x=mxpos(1);
									y=mypos(1);
									on=mclick();
									if(on==1){
										if(x>=40 && y>=396 && x<=170 && y<=451){
											archivo=fopen("C:\\TC20\\BIN\\FICHERO\\ppt.txt","a");
											if(archivo==NULL){
												printf("algo anda mal");
												getch();
											}
											fprintf(archivo,"0|\n");
											fclose(archivo);
											goto inicio;
										}else if(x>=456 && y>=396 && x<=586 && y<=451){
											goto dificil;
										}
									}
								}
							}else if(x>=55 && y>=245 && x<=505 && y<=325){/*facil*/
									setfillstyle (SOLID_FILL ,9);
									bar(0,0,640,480);
									puntos=0;
									facil:
									opc=elegir();
									setfillstyle (SOLID_FILL ,14);
									bar(418,408,228,457);
									setfillstyle (SOLID_FILL ,9);
									bar(55,143,250,359);
									sleep(1);
									j=1+rand()%(3-1+1);
									if(j==1){
										roca();
									}else if(j==2){
										tijera();
									}else{
										papel();
									}
								if(opc==1){
									if(j==3){
										settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
										setcolor(0);
										outtextxy(230,414, "Perdiste");
									}else if(j==opc){
										settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
										setcolor(0);
										outtextxy(230,414, "Empate");
									}else{
										settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
										setcolor(0);
										outtextxy(230,414, "ganaste");
										puntos++;
									}
								}else if(opc==2){
									if(j==1){
										settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
										setcolor(0);
										outtextxy(230,414, "Perdiste");
									}else if(j==opc){
										settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
										setcolor(0);
										outtextxy(230,414, "Empate");
									}else{
										settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
										setcolor(0);
										outtextxy(230,414, "ganaste");
										puntos++;
									}
								}else {
									if(j==2){
										settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
										setcolor(0);
										outtextxy(230,414, "Perdiste");
										
									}else if(j==opc){
										settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
										setcolor(0);
										outtextxy(230,414, "Empate");
									}else{
										settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
										setcolor(0);
										outtextxy(230,414, "ganaste");
										puntos++;
									}
								}
								
								botones(1,0,1,15);
								mver();
								msituar(1,320,240);
								while(1){
									x=mxpos(1);
									y=mypos(1);
									on=mclick();
									if(on==1){
										if(x>=40 && y>=396 && x<=170 && y<=451){
											archivo=fopen("C:\\TC20\\BIN\\FICHERO\\ppt.txt","a");
											fprintf(archivo,"%d|\n",puntos);
											fclose(archivo);
											goto inicio;
										}else if(x>=456 && y>=396 && x<=586 && y<=451){
											goto facil;
										}
									}
								}
							}
						}
					}
					getch();
				}	
			}
		}
	goto inicio;
	getch();

}

void tijera(void){
	int tijera[]={144 ,267,149 ,276,161 ,277,202 ,204,189 ,190,144 ,267};
	 int tijera1[]={143 ,266,152 ,254,109 ,197,100 ,215,143 ,266};
	 int tijera2[]={144 ,267,149 ,277,162 ,279,134 ,336,101 ,316,114 ,293,135 ,285,144 ,267};
	 int tijera3[]={168 ,265,182 ,282,204 ,287,215 ,309,190 ,330,160 ,285,161 ,275,168 ,265};
		
	setfillstyle (SOLID_FILL ,8);
	fillpoly(4,tijera1);
	fillpoly(5,tijera);
	setfillstyle (SOLID_FILL ,4);
	fillpoly(8,tijera3);
	fillpoly(8,tijera2);
		
}
void papel(void){
	int papel[]={88,202,96,212,87,205,95,346,117,351,112,342,121,351,193,351,223,335,223,302,214,301,221,295,207,291,221,284,222,202,161,207,160,226,157,206,88,202};
	setfillstyle (SOLID_FILL ,15);
	setcolor(0);
	fillpoly(18,papel);
	
}	

void roca(void){
	int roca[]={155,314,145,314,122,282,123,249,140,230,151,231,169,211,180,212,202,243,202,275,185,295,174,294,175,313,155,314};
	setfillstyle (SOLID_FILL ,7);
	setcolor(0);
	fillpoly(12,roca);
	
}

int elegir(void){
	int x,y,on,i;
	setfillstyle (SOLID_FILL ,9);
	bar(0,0,640,480);
	setfillstyle (SOLID_FILL ,15);
	bar(388,108,571,166);
	bar(388,199,571,256);
	bar(388,295,571,352);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
	setcolor(0);
	outtextxy(398,118, "PIEDRA");
	outtextxy(398,209, "TIJERA");
	outtextxy(398,305, "PAPEL");
	mver();
	msituar(1,320,240);i=0;
	while(1){
		
		x=mxpos(1);
		y=mypos(1);
		on=mclick();
		if(on==1){
			if(x>=388 && y>=108 && x<=571 && y<=166){
				return 1;
			}else if(x>=388 && y>=199 && x<=571 && y<=256){
				return 2;
			}else if(x>=388 && y>=295 && x<=571 && y<=352){
				return 3;
			}
		}
			
			if(i==0){
				roca();
			}else if(i==1){
				papel();
			}else {
				tijera();i=0;
			}
			delay(300);
			setfillstyle (SOLID_FILL ,9);
			bar(55,143,250,359);i++;
			}
}
void botones(int x,int y,int z,int c){
	int sal[]={118,403,135,403,135,438,101,438,101,444,74,431,101,419,101,425,118,425,118,403};/*9*/
	int sig[]={508,401,544,424,508,447,508,401};/*3*/
	int ret[]={516,408,519,404,541,404,547,411,547,435,539,442,506,442,498,435,498,421,493,421,504,404,515,421,510,421,510,428,532,428,532,415,520,415,516,412,516,408};/*18*/
	
	if(x==1){
	/*salida*/
	setfillstyle(SOLID_FILL, c);
			bar(40,396,170,451);
	setfillstyle(SOLID_FILL, 0);		
	fillpoly (9, sal);
	}
	if(y==1){
		/*entrada*/
	
	setfillstyle(SOLID_FILL, c);
			bar(456,396,586,451);
	setfillstyle(SOLID_FILL, 0);		
	fillpoly (3, sig);
	}
	if(z==1){
		/*retorno*/
	
	setfillstyle(SOLID_FILL, c);
			bar(456,396,586,451);
	setfillstyle(SOLID_FILL, 0);		
	fillpoly (18, ret);
	}
	
}