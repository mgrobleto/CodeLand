/* Creado por: Priscilla Fernanda Zelaya Pineda */

#include<stdlib.h>
#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>

#define ARRIBA 72
#define ABAJO  80
#define DER    75
#define IZQ    77
#define ENTER  13

int leer_card(void);
void pupila_hule(int x, int y, int radiox, int radioy);

void main(){
	int driver=DETECT, modo, x, y, radiox, radioy;

    initgraph(&driver, &modo,"C:\\TC20\\BIN");
    /*silueta grande*/
    circle(322, 159, 204);

    /*Contorno Turquesa*/
    setfillstyle(9,CYAN);
    fillellipse(324, 145, 197, 195);

    /*Parte blanca*/
    setfillstyle(1,WHITE);
    fillellipse(324, 145, 165, 178);

    /*Iris*/
    setfillstyle(9,BROWN);
    fillellipse(324, 145, 105, 148);
	pupila_hule(x, y, radiox, radioy);

    closegraph();
    exit(0);
}

    int leer_card(void)
    {
    	int tecla;
    	while((tecla=getch())!=0)
    	if(tecla == ENTER)
    	return(tecla);
    	return(getch());
    }

/*pupila, se mueve*/
void pupila_hule(int x, int y, int radiox, int radioy)
{
    int lineas_enojo[18] = {
    196,0, 210,14, 323,52, 436,15, 443,0, 344,0
    ,323,8, 301,0, 196,0
    };
    int silueta1[24]={
    316, 289, 302, 278, 277, 247, 306, 268, 316, 264,
    323, 199, 328, 264, 338, 268, 368, 247, 343, 277,
    331, 289, 316, 289
    };

    /*ojo derc*/
    int ojo_derecho[8]={
    308, 304, 300, 313, 280, 292, 308, 304
    };

    int ojo_izquierdo[8]={
    337, 304, 342, 313, 364, 292, 337, 304
    };

    int silueta2[18]={
    314, 301, 313, 310, 303, 319, 289, 319, 272, 298, 272, 272, 275, 263, 278, 279, 314, 301
    };

    int silueta3[18]={
    329, 301, 330, 310, 341, 319, 355, 319, 372, 297, 372, 273, 370, 264, 366, 279, 329, 301
    };

    int traje1[18]={
    182, 478, 194, 427, 217, 404, 223, 402, 223, 407, 253, 411, 213, 424, 188, 478, 182, 478
    };

    int traje2[18]={
    462, 478, 454, 478, 432, 426, 392, 411, 419, 405, 416, 402, 424, 404, 451, 429, 462, 478
    };

    int pecho[34]={
    265, 478, 242, 478, 274, 426, 267, 418, 267, 408, 303, 395, 343, 395, 377, 408, 377, 418, 371, 427, 409, 478, 382, 478, 355, 443, 329, 478, 311, 478, 288, 444, 265, 478
    };

    int logo[12]={
    304, 412, 311, 409, 334, 409, 340, 412, 323, 442, 304, 412
    };

int tecla, r;
radiox=8;
radioy=80;
x=323;
y=146;
    do
    {
    setfillstyle(1,BLACK);
    fillellipse(322, 145, 80, 123);
	setfillstyle(1,WHITE);
    fillellipse(x, y, radiox, radioy);
    setfillstyle(9,CYAN);
	fillpoly(9,lineas_enojo);
    drawpoly(9,lineas_enojo);
    /*cuello*/
    arc(278, 387, 290, 0, 26);
    /*pecho izquierdo*/
    line(215, 413, 285, 413);
    arc(232, 451, 115 , 195, 42);
    line(305, 362, 305, 387);
    /*cuello derecho*/
    arc(373, 387, 180, 290, 26);
    /*pecho derecho*/
    line(378, 413, 435, 413);
    arc(415, 451, -15, 65, 42);
    line(347, 362, 347, 387);
    /*cabeza*/
    setfillstyle(1,BLACK);
    fillellipse(323, 280, 54, 90);
    /*Contorno del tercer ojo*/
    setfillstyle(9,CYAN);
	fillpoly(12,silueta1);
	drawpoly(12,silueta1);
    /*cara*/
    setfillstyle(1,WHITE);
    fillellipse(323, 276, 16, 11);

    setfillstyle(9,CYAN);
	fillpoly(9,silueta2);
	drawpoly(9,silueta2);

    setfillstyle(9,CYAN);
	fillpoly(9,silueta3);
	drawpoly(9,silueta3);

    r=0;

    setfillstyle(1,WHITE);
	fillpoly(4,ojo_derecho);
	drawpoly(4,ojo_derecho);

    setfillstyle(1,WHITE);
	fillpoly(4,ojo_izquierdo);
	drawpoly(4,ojo_izquierdo);

    setfillstyle(9,CYAN);
	fillpoly(9,traje1);
	drawpoly(9,traje1);

    setfillstyle(9,CYAN);
	fillpoly(9,traje2);
	drawpoly(9,traje2);

    setfillstyle(9,CYAN);
	fillpoly(17,pecho);
	drawpoly(17,pecho);

    setfillstyle(1,WHITE);
	fillpoly(6,logo);
	drawpoly(6,logo);

    setfillstyle(1,BLACK);
    fillellipse(323, 424, 2, 8);
	switch(tecla = leer_card())
        {
            case DER: radiox-=5;
            break;
            case IZQ: radiox+=5;
            break;
            case ARRIBA: r--;
            break;
            case ABAJO: r++;
            break;
        }

    drawpoly(5,ojo_derecho);
    ojo_derecho[0] -=r;  ojo_derecho[6] -= r; ojo_derecho[1] += r;  ojo_derecho[7] += r;
	ojo_derecho[3] -=r;  ojo_derecho[4]+=r; ojo_derecho[5] += r;
    drawpoly(5,ojo_izquierdo);
    ojo_izquierdo[0] +=r;  ojo_izquierdo[6] += r; ojo_izquierdo[1] -= r;  ojo_izquierdo[7] -= r;
	ojo_izquierdo[3] +=r;  ojo_izquierdo[4] -=r; ojo_izquierdo[5] -= r;
        setfillstyle(1,BLACK);
        fillellipse(x, y, radiox, radioy);
        /*cabeza*/
        setfillstyle(1,BLACK);
        fillellipse(323, 280, 53, 90);

        setfillstyle(9,CYAN);
	    fillpoly(9,lineas_enojo);
        drawpoly(9,lineas_enojo);

        /*Contorno del tercer ojo*/
        setfillstyle(9,CYAN);
	    fillpoly(12,silueta1);
	    drawpoly(12,silueta1);

        /*cara*/
        setfillstyle(1,WHITE);
        fillellipse(323, 276, 16, 11);

    } while (tecla != 13);
}