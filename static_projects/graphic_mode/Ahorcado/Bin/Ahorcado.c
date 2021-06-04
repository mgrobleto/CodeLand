#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <mouse.h>
#include "button.h"

/**************************/
/*PROYECTO AHORCADO
  Elaborado por Luis.M Pineda.J
  Grupo 2M1-CO
  Fecha de Terminacion: 27/05/2021
  ****DERECHOS RESERVADOS****/

void Teclado(int x, int y);
int Validacion_del_teclado(int x, int y);
void PintarDibujo(int Errores);
void Pantalla_de_juego(void);
void Pantalla_principal(void);

void main(){

    int g_adap = DETECT, g_mode;

    initgraph(&g_adap,&g_mode,"C:\\TC20\\BIN");

    Pantalla_principal();

    closegraph();
}

void Pantalla_principal(void){

    int xpos = 0, ypos = 0;

	setfillstyle(1,LIGHTGRAY);
    bar(0,0,640,480);

    setcolor(RED);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
    outtextxy(226,62,"AHORCADO");
    
    /*Marco*/
    setfillstyle(1,CYAN);
    bar(0,0,10,480);
    bar(10,0,640,10);
    bar(10,470,640,480);

    setfillstyle(1,LIGHTBLUE);
    bar(334,460,640,480);
    bar(630,0,640,480);

    /*Botones*/
    setfillstyle(1,DARKGRAY);
    bar(183,160,444,236);
    bar(183,260,444,336);

    setcolor(BLUE);
    outtextxy(255,185,"Jugar");
    outtextxy(255,285,"Salir");
    
    /*CopyRight*/
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
    outtextxy(370,466,"Desarrollado por Luis.M Joseph");

    setcolor(WHITE);

    mver();

    /*Validar opciones en menu principal*/
    do{
        while(mclick()!=1);

        xpos = mxpos(1);
        ypos = mypos(1);

        if(limit(xpos,ypos,183,160,444,236)){
            mocultar();
            Pantalla_de_juego();
        }
        if(limit(xpos,ypos,183,260,444,336))
            exit(0);

        while(mclick()==1);

    }while(1);

}

void Pantalla_de_juego(void){

	int Letra = 0, Escorrecto = 0, Longitud = 0, i = 0, Intentos = 1, Gana = 0;
    char Palabra[5], Copy[5];
    int xpos = 0, ypos = 0;
    bool Ingame = true, Incorrecto = true;

    setfillstyle(1,DARKGRAY);
    bar(0,0,640,480);

    Teclado(80,340);

    setfillstyle(1,LIGHTGRAY);
    bar(65,40,575,295);
    bar(600,0,640,30);

    setcolor(RED);
    line(603,3,637,27);
    line(603,27,637,3);

    setfillstyle(1,CYAN);
    bar(70,45,570,290);

    setcolor(RED);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);

    outtextxy(90,100,"INGRESE LA PALABRA A ADIVINAR");

    setfillstyle(1,LIGHTBLUE);
    bar(140,210,155,213);
    bar(220,210,235,213);
    bar(300,210,315,213);
    bar(380,210,395,213);
    bar(460,210,475,213);

    setcolor(BLUE);

    mver();

    do{
        while(mclick()!=1);

        xpos = mxpos(1);
        ypos = mypos(1);
        
        if(limit(xpos,ypos,600,0,640,30))
            exit(0);

        Palabra[Longitud] = Validacion_del_teclado(80,340);
        sprintf(Copy,"%c",Palabra[Longitud]);
        outtextxy(141+(Longitud*80),190,Copy);
        Longitud++;

        while (mclick()==1);        
    }while(Longitud != 5);

    delay(150);

    mocultar();

    setfillstyle(1,LIGHTGRAY);
    bar(65,40,575,295);
    
    setfillstyle(1,CYAN);
    bar(70,45,570,290);
    
    setfillstyle(1,LIGHTGRAY);
    bar(318,45,320,290);
    mver();

    setcolor(BLACK);
    outtextxy(390,80,"PALABRA");
    
    setfillstyle(1,LIGHTBLUE);
    bar(339,140,355,143);
    bar(384,140,400,143);
    bar(429,140,445,143);
    bar(474,140,490,143);
    bar(519,140,535,143);

    do{
        while(mclick()!=1);

        xpos = mxpos(1);
        ypos = mypos(1);
        
        Letra = 0;
        Incorrecto = true;

        if(limit(xpos,ypos,600,0,640,30))
            exit(0);

        Letra = Validacion_del_teclado(80,340);
        
        for(i = 0; i < 5; i++){
            if(Letra == Palabra[i]){
                setcolor(BROWN);
                sprintf(Copy,"%c",Letra);
                outtextxy(340+(i*45),125,Copy);
                Escorrecto++;
                Incorrecto = false;
            }
        }
        
        if(Incorrecto == true){ 
            PintarDibujo(Intentos);
            Intentos++;
        }

        if(Escorrecto == 5){ 
            Ingame = false;
            Gana = 1;
        }
        else if(Intentos == 11){
            Ingame = false;
            Gana = 2;
        }
        while(mclick()==1);

    }while(Ingame);

    setfillstyle(1,LIGHTGRAY);
    bar(365,175,530,200);
    if(Gana == 1){ 
        setcolor(GREEN);
        outtextxy(374,180,"HA GANADO");
    }else{
        setcolor(RED);
        outtextxy(370,180,"HA PERDIDO");
        setcolor(YELLOW);
        for(i = 0; i < 5; i++){
            sprintf(Copy,"%c",Palabra[i]);
            outtextxy(340+(i*45),125,Copy);
        }
    }

    setcolor(BLUE);
    setfillstyle(1,WHITE);
    bar(335,240,560,265);
    outtextxy(338,245,"JUGAR DE NUEVO");

    do
    {
        while(mclick() != 1);

        xpos = mxpos(1);
        ypos = mypos(1);

        if(limit(xpos,ypos,345,240,550,265)){
            mocultar();
            Pantalla_de_juego();
        }else if(limit(xpos,ypos,600,0,640,30))
            exit(0);

        while(mclick()==1);
    } while(1);
}

void Teclado(int x, int y){

	char Copy[27];
    int i = 0, j = 0;

    setfillstyle(1,LIGHTGRAY);
    setcolor(BLUE);
    settextstyle(0,0,2);

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 11; j++)
        {
            if(i != 2)
                bar(0+x+(j*45),0+y+(i*45),35+x+(j*45),35+y+(i*45));
            if(i == 0){
                sprintf(Copy,"%c",65+j);
                outtextxy(10+x+(j*45),10+y+(i*45),Copy);
            }
            if(i == 1){
                if(j<3){
                    sprintf(Copy,"%c",76+j);
                    outtextxy(10+x+(j*45),10+y+(i*45),Copy);
                }
                else if(j>3){
                    sprintf(Copy,"%c",75+j);
                    outtextxy(10+x+(j*45),10+y+(i*45),Copy);
                }
                else{
                    sprintf(Copy,"%c",165);
                    outtextxy(10+x+(j*45),10+y+(i*45),Copy);
                }
            }
            if(i == 2 && j < 5){
                bar(135+x+(j*45),0+y+(i*45),170+x+(j*45),35+y+(i*45));
                sprintf(Copy,"%c",86+j);
                outtextxy(145+x+(j*45),10+y+(i*45),Copy);
            }
        }
    }
}

int Validacion_del_teclado(int x, int y){

    int i = 0, j = 0, CodigoLetra = 0, xpos = 0, ypos = 0;

    mver();

    do{ 
        while(mclick() != 1);

        xpos = mxpos(1);
        ypos = mypos(1);

        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 11; j++)
            {
                if(limit(xpos,ypos,0+x+(j*45),0+y+(i*45),35+x+(j*45),35+y+(i*45))){
                    if(i == 0)
                        CodigoLetra = 65 + j;
                    if(i == 1)
                    {
                        if(j<3)
                            CodigoLetra = 76+j;
                        else if(j>3)
                            CodigoLetra = 75+j;
                        else
                            CodigoLetra = 165;
                    }
                }
                if(limit(xpos,ypos,135+x+(j*45),0+y+(i*45),170+x+(j*45),35+y+(i*45))){
                    if(i == 2 && j < 5)
                        CodigoLetra = 86 + j;
                }
            }
        }

        while(mclick()==1);

    }while(CodigoLetra == 0);

    return CodigoLetra;
}

void PintarDibujo(int Errores){

    setfillstyle(1,BLUE);
    setcolor(BLACK);

    switch(Errores)
    {
    case 1:
        bar(80,280,310,285);
        break;
    case 2:
        bar(305,60,310,285);
        break;
    case 3:
        bar(150,60,310,65);
        break;
    case 4:
        bar(150,65,155,115);
        break;
    case 5:
        circle(152.5,135,20);
        break;
    case 6:
        line(152.5,155,152.5,225);
        break;
    case 7:
        line(122,205,152.5,175);
        break;
    case 8:
        line(152.5,175,182.5,205);
        break;
    case 9:
        line(122,255,152.5,225);
        break;
    case 10:
        line(152.5,225,182.5,255);
        break;
    default:
        break;
    }
}