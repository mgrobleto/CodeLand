#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>

#define esc 27
#define arriba 72
#define abajo 80
#define derecha 77
#define izquierda 75

void dibujarVertical(int x1,int y1,int x2,int y2){
setcolor(BLUE);
line(x1,y1,x2,y2);
}

void dibujarHorizontal(int x1,int y1,int x2){
setcolor(BLUE);
line(x1,y1,x2,y1);
}

void franjasNegras(){
	setcolor(BLACK);
	setfillstyle(SOLID_FILL,BLACK);
	bar(230,146,410,148);bar(230,158,410,161);
	bar(230,170,410,173);bar(230,179,410,182);
	bar(230,191,410,194);bar(230,201,410,205);
	bar(230,213,410,216);bar(230,220,410,225);
}

void pixeles(){
int ran1,ran2,i;

for(i=0;i<700;i++){
		    ran1 = 1 + random (640);
		    ran2 = 1 + random (259);
		    putpixel(ran1,ran2,WHITE);
	  	}

	  	for(i=0;i<800;i++){
		    ran1 = 1 + random (640);
		    ran2 = 260 + random (480);
		    putpixel(ran1,ran2,DARKGRAY);
	  	}
}
void main(void){
	int driver=DETECT,modo;
	int x1,x2,y1,y2;
	int x,y,xz;
	int key,i,n;
		
		initgraph(&driver,&modo,"");
		x1=0,x2=-750,y1=260,y2=480;
		x=0,y=260,xz=640;
		n=45;

		for(i=0;i<n;i++){
			dibujarVertical(x1,y1,x2,y2);
			dibujarHorizontal(x,y,xz);
			x1+=15;
			x2+=50;
			y=y+(i*3);
		}

		pixeles();
		setcolor(RED);
		setfillstyle(SOLID_FILL,YELLOW);
		fillellipse(320,150,90,80);
		franjasNegras();
	getch();
	}