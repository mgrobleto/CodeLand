#include<stdio.h>
#include<graphics.h>

#define esc 27

void borrar(int x, int y){
	setcolor(BLACK);
	setfillstyle(SOLID_FILL,BLACK);
	fillellipse(x,y,20,20);
}

void dibujar(int x, int y){
	setcolor(YELLOW);
 	setfillstyle(SOLID_FILL,YELLOW);
	fillellipse(x,y,20,20);
}

void main(void){
	int driver=DETECT,modo;
	int x,y,saltox,saltoy,dir;
	int key;
		
		initgraph(&driver,&modo,"");

			x=getmaxx()/2,y=getmaxy()/2;
			saltox=10,saltoy=10,dir=-1;

		dibujar(x,y);

		do{
			delay(100);
		borrar(x,y);
		x+=saltox;
		y+=saltoy;
		dibujar(x,y);

		if(x>=600){
			saltox*=dir;
		}
		if(y>=440){
			saltoy*=dir;
		}

		if(x<=40){
			saltox*=dir;
		}
		if(y<=40){
			saltoy*=dir;
		}

		}while(key!=esc);
}