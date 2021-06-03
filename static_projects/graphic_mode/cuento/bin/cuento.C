#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <mario.h>

#define ARRIBA 72
#define ABAJO 80
#define DERECHA 77
#define IZQUIERDA 75
#define ENTER 13


 void paisaje(void);
 void animales(void);
 void conejote(void);
 void tortuga(void);
 int texto1();
 int texto2();
 int texto3();
 void patas1(void);
 void patas2(void);
 void cuerpo_negro1(void);
 void cuerpo_negro2(void);
 void conejo2(void);
 void pajaros(void);
 void conejomimido(void);
void tortugarun(void);
void tortupatas1(void);
void tortupatas2(void);
void tortugarun2(void);
void tortugapatas3(void);
void tortugarun3(void);
void tortugapatas4(void);
void tortugafeliz(void);
void happyending(void);
void portada(void);
void tortuga1(void);
void patass2(void);
void oscura_patas2(void);
void patass1(void);
void ocura_patas1(void);


int conejo[52] = {
469, 367,477, 421,470, 427,467, 436,473, 442,481, 442,487, 433,489, 433,492, 435,493, 438,496, 443,526, 442,542, 424,553, 421,556, 408,556, 398,555, 392,551, 387,546, 387,542, 371,536, 360,528, 349,518, 341,507, 337,501, 327,469, 367
};

int Arbol1[70] = {14, 328,20, 328,24, 319,31, 316,34, 319,40, 316,44, 316,47, 322,49, 326,55, 329
,59, 329,63, 329,65, 335,62, 339,60, 343,62, 343,66, 345,69, 350,69, 357,66, 360,63, 362,57, 363,56, 367,47, 369,34, 369,30, 368,20, 368,17, 368
,13, 360,9, 352,6, 352,6, 347,11, 341,13, 344,14, 329};

int Arbol3[50] = {637, 336,628, 337,619, 337,612, 338,604, 343,601, 345,597, 350,593, 357,578, 359,578, 365,573, 372
,572, 374,581, 388,588, 396,601, 402,614, 402,625, 399,630, 394,637, 394,639, 387,639, 371,635, 355,638, 345,639, 338,637, 337};
int Arbol4[54] = {21, 215,16, 219,15, 227,15, 235,12, 239,12, 252,14, 258,14, 266,14, 285,17, 294,17, 305,18, 319,24, 321
,29, 316,29, 310,31, 301,30, 296,28, 289,30, 276,30, 260,31, 252,31, 241,28, 237,28, 229,28, 219,24, 215,21, 216};
int Arbol5[34] = {5, 225,5, 240,5, 251,3, 257,3, 263,6, 277,12, 287,7, 300,5, 308,5, 325
,5, 331,4, 342,0, 329,0, 288,0, 233,0, 223,5, 226};

int nube[80] = {261,137,251,140,263,142,269,143,273,142,271,144,272,146,288,146,292,145,293,146,295,146,296,147,298,147,299,148,308,148,309,147,317,144,
319,144,327,144,333,141,343,137,346,134,345,130,342,129,344,125,330,117,323,117,316,118,309,117,306,118,301,119,293,118,276,120,270,122,
267,125,267,128,258,131,261,135,264,135,261,137};

int montana[102]= {0,300,1,282,5,261,10,238,15,219,18,208,23,193,34,169,41,160,52,146,71,122,83,108,99,101,110,106,110,109,116,115,131,129,
140,136,160,151,163,155,163,169,173,177,189,178,202,170,211,163,223,161,244,161,264,174,299,183,343,185,357,196,377,242,396,244,404,232,
430,195,458,172,471,166,491,148,504,137,509,133,515,133,526,141,543,152,576,177,600,196,619,211,627,217,631,227,639,235,639,297,0,300};

int nieve[42]= {52,146,60,146,79,145,89,140,98,140,108,147,121,151,136,158,143,165,163,167,163,155,160,151,140,136,131,129,116,115,110,109,
110,106,99,101,83,108,71,122,52,146};

int nieve2[42]= {189,178,206,187,218,190,240,197,276,197,287,204,297,211,302,213,310,215,319,214,332,217,365,218,357,196,343,185,299,183,
264,174,244,161,223,161,211,163,202,170,189,178};

int nieve3[40]={443,185,449,187,481,188,493,184,496,178,505,175,516,174,523,176,536,177,553,179,575,178,543,152,526,141,514,134,509,133,
504,137,491,148,471,166,458,172,443,185};

int nube2[46]={521,74,515,73,512,70 ,521,66,523,61,529,59,539,58,553,56,569,55,584,56,597,63,596,67,599,72,588,76,573,82,563,85,553,86,543,83,
526,84,518,80,515,78,515,75,521,74};

int lago[80] = {477,333,472,332,468,328,468,324,473,319,478,319,478,313,484,307,495,305,500,307,508,302,514,302,518,305,523,301,530,300,535,303,539,301,
546,300,553,305,557,308,562,313,562,319,560,321,564,324,564,330,561,334,553,338,551,342,545,347,532,347,525,354,514,355,505,351,
497,352,486,351,480,346,472,343,471,338,472,334,477,333 };

int animal1[16] = {102, 357,103, 304,107, 306,110, 317,125, 316,125, 303,150, 357,102, 357
};
int pecho[12] = {
130,348,
122,329,
99,330,
105,335,
107,351,
130,348
};

int oreja1[8]={
127,305,
133,316,
126,316,
127,305

};

int oreja2[8]={
104,306,
108,317,
103,317,
104,306
};

int cesped[48] = {
9, 356
,18, 348
,23, 354
,34, 351
,38, 353
,47, 350
,57, 353
,68, 350
,76, 354
,81, 349
,92, 350
,102, 348
,109, 352
,119, 350
,126, 351
,133, 348
,140, 351
,150, 347
,156, 350
,163, 346
,164, 351
,168, 355
,168, 356
,9, 356

};

int caballo[32] = {
272, 314
,271, 306
,268, 307
,265, 307
,264, 295
,272, 289
,283, 284
,295, 280
,308, 276
,314, 282
,307, 289
,303, 294
,298, 300
,301, 308
,296, 314
,272, 314

};

int pechote[12] ={
281,303,
290,301,
295,309,
290,309,
285,308,
281,303
};

int cesped2[36] ={
245,327,
256,315,
264,322,
273,312,
288,320,
289,312,
304,319,
304,304,
320,316,
321,298,
336,307,
334,291,
346,302,
360,293,
379,313,
379,298,
395,317,
245,327
};

int cara[20] = {
499, 338
,499, 326
,511, 328
,527, 329
,534, 326
,537, 339
,524, 345
,523, 348
,517, 348,
499,338

};



int mapache [16] ={
498,353,
499,327,
509,330,
525,329,
532,327,
535,335,
537,349,
498,353
};

int cesped3[38] = {
461, 355
,468, 346
,475, 351
,480, 342
,494, 349
,506, 345
,511, 349
,529, 347
,537, 352
,545, 345
,558, 350
,563, 345
,569, 351
,582, 346
,600, 350
,613, 341
,620, 351,
471,365
,461, 355

};

int colibri[46] = {
461, 47
,460, 44
,456, 44
,454, 47
,454, 51
,448, 52
,440, 47
,441, 55
,444, 60
,447, 64
,444, 69
,439, 77
,437, 80
,442, 84
,446, 82
,446, 74
,452, 74
,458, 69
,459, 63
,461, 58
,461, 52
,471, 48,
461,47

};

int solaire[26] = {
414, 363
,411, 331
,399, 315
,414, 325
,414, 320
,412, 317
,418, 319
,418, 324
,432, 312
,424, 329
,422, 343
,421, 364,
414,363

};

int conejomimi[48] = {
305, 286
,280, 304
,264, 326
,260, 342
,251, 349
,249, 363
,253, 376
,261, 382
,264, 380
,276, 397
,310, 401
,314, 393
,320, 389
,326, 399
,335, 399
,338, 393
,343, 391
,342, 379
,335, 371
,332, 368
,337, 353
,338, 338
,337, 323
,305, 286

};

int patita[18] = {
318, 355
,319, 383
,325, 397
,334, 397
,340, 392
,343, 389
,341, 377
,332, 370
,318, 355

};

int tecla;
int huge DetectVGA256(void); /*Inicia el modo XGA para poder trabajar con la paleta de 256 colores*/
void main(void)
{
	int driver = DETECT,modo,i=0;
        installuserdriver("Svga256",DetectVGA256);
	initgraph(&driver,&modo,"C:\\TC20\\BIN");
portada();
delay(1000);
 paisaje();	
 animales();
pajaros();
delay(1000);
 cleardevice();
 paisaje();
 animales();
pajaros();
 conejote();
 texto1();
 delay(1000);
cleardevice();
paisaje();
animales();
tortuga();
conejote();
pajaros();
texto2();
delay(1000);
cleardevice();
paisaje();
texto3();
for (i = 0; i <= 10; i++)
	{
		if(i%2 == 0)
		{
			conejo2();
			
		}
		delay(i);
		cuerpo_negro1();
		
		patas2();
		delay(i);
		cuerpo_negro2();
}


if (i=10){
cleardevice();
paisaje();
animales();
conejomimido();
delay(300);
tortuga1();
delay(300);
tortugarun();
tortupatas1();
cleardevice();
paisaje();
animales();
conejomimido();
tortugarun();
tortupatas2();
cleardevice();
paisaje();
animales();
conejomimido();
tortugarun2();
tortugapatas3();
cleardevice();
paisaje();
animales();
conejomimido();
tortugarun3();
tortugapatas4();
delay(200);
cleardevice();
paisaje();
animales();
tortugafeliz();
tortugapatas3();
pajaros();
mario();
happyending();
delay(500);

}
   getch();
   closegraph();
}
int huge DetectVGA256()
{
	/*4 = 1024x768x256; modo XGA */
	return 2;
}


void paisaje(void)
{
/*fondo*/

	setfillstyle(1,54);
	bar(0,0,640,339);
	/*piso*/

	setcolor(6);
	setfillstyle(1,6);
	bar(1,295,640,480);


   /*pajaros*/

   setcolor(15);
line(25,130,43,135);
line(43,135,51,123);

line(129,96,139,100);
line(139,100,142,88);

line(174,37,186,47);
line(186,47,198,39);

line(218,78,235,85);
line(235,85,236,75);

line(243,37,259,46);
line(259,46,273,30);

line(317,13,338,25);
line(338,25,347,13);

line(299,55,311,65);
line(311,65,315,48);

line(336,63,353,68);
line(353,68,357,52);


line(377,19,394,26);
line(394,26,405,19);

line(335,60,355,70);
line(355,70,356,54);

line(456,17,471,27);
line(471,27,477,15);

line(435,56,446,62);
line(446,62,456,51);

line(392,74,404,81);
line(404,81,408,73);

line(400,107,413,113);
line(413,113,415,101);

line(558,18,580,25);
line(580,25,596,13);
  
  /*Sol, Solecito*/
 setcolor(14);
   setfillstyle(1,14);
   circle(50,50,30);
   floodfill(53,54,14);


   /*arbusto */
   setcolor(2);
   setfillstyle(1,2);
   fillpoly(35,Arbol1);

   /*arbustos*/

   fillpoly(25,Arbol3);
   fillpoly(27,Arbol4);
   fillpoly(17,Arbol5);

   /*Nube 1*/
   setcolor(15);
   setfillstyle(1,15);
   fillpoly(40,nube);

     /*Nube 2*/
   setcolor(15);
   setfillstyle(1,15);
   fillpoly(23,nube2);

   /*Montaña*/
   setcolor(2);
   setfillstyle(1,2);
   fillpoly(51,montana);

   /*Nieve*/
   setcolor(15);
   setfillstyle(1,15);
   fillpoly(21,nieve);

   /*Nieve 2*/
   setcolor(15);
   setfillstyle(1,15);
   fillpoly(21,nieve2);

    /*Nieve 3*/
   setcolor(15);
   setfillstyle(1,15);
   fillpoly(20,nieve3);

    /*Lago*/
   setcolor(9);
   setfillstyle(1,9);
   fillpoly(40,lago);
}

void animales(void)
{

setcolor(42);
setfillstyle(1,42);
drawpoly(8,animal1);
floodfill(131,335,42);

setcolor(15);
setfillstyle(1,15);
drawpoly(6,pecho);
floodfill(119,339,15);


setcolor(15);
setfillstyle(1,15);
drawpoly(4,oreja1);
floodfill(128,312,15);


setcolor(15);
setfillstyle(1,15);
drawpoly(4,oreja2);
floodfill(104,313,15);


setcolor(15);
setfillstyle(1,15);
circle(124,322,5);
floodfill(124,321,15);

circle(105,322,5);
floodfill(106,322,15);

setcolor(16);
setfillstyle(1,16);
circle(124,322,3);
floodfill(123,321,16);

circle(105,322,3);
floodfill(106,323,16);

setcolor(15);

putpixel(124,322,15);
putpixel(105,322,15);

setcolor(48);
setfillstyle(1,48);
drawpoly(24,cesped);
floodfill(152,353,48);

setcolor(6);
setfillstyle(1,6);
drawpoly(16,caballo);
floodfill(292,293,6);

setcolor(15);
setfillstyle(1,15);
drawpoly(6,pechote);
floodfill(287,304,15);

setcolor(15);
setfillstyle(1,15);
circle(278,292,3);
floodfill(279,292,15);

setcolor(16);
setfillstyle(1,16);
circle(278,292,1);
floodfill(279,292,16);

setcolor(15);
setfillstyle(1,15);
circle(289,289,3);
floodfill(289,288,15);

setcolor(16);
setfillstyle(1,16);
circle(289,289,1);
floodfill(289,288,16);

setcolor(16);
setfillstyle(1,16);
circle(309,279,4);
floodfill(306,280,16);

setcolor(16);
line(301,289,307,291);

setcolor(48);
setfillstyle(1,48);
drawpoly(18,cesped2);
floodfill(308,314,48);

setcolor(24);
setfillstyle(1,24);
drawpoly(8,mapache);
floodfill(530,347,24);

setcolor(20);
setfillstyle(1,20);
drawpoly(10,cara);
floodfill(518,335,20);

setcolor(15);
setfillstyle(1,15);
ellipse(513,341,0,360,4,2);
floodfill(511,341,15);

ellipse(527,340,0,360,4,2);
floodfill(527,340,15);


setcolor(16);
setfillstyle(1,16);
ellipse(513,341,0,360,3,2);
floodfill(513,340,16);

ellipse(527,340,0,360,3,2);
floodfill(527,339,16);
circle(521,347,3);
floodfill(521,346,16);

setcolor(48);
setfillstyle(1,48);
drawpoly(19,cesped3);
floodfill(546,348,48);

setcolor(45);
setfillstyle(1,45);
drawpoly(23,colibri);
floodfill(455,62,45);

setcolor(16);
setfillstyle(1,16);
circle(457,48,3);
floodfill(458,48,16);

setcolor(44);
setfillstyle(1,44);
line(449,71,459,53);
line(459,53,453,71);
line(453,71,449,71);
floodfill(453,66,44);

setcolor(18);
setfillstyle(1,18);
line(452,62,449,54);
line(449,54,444,54);
line(444,54,452,62);
floodfill(448,57,18);

setcolor(15);
setfillstyle(1,15);
circle(459,48,1);
floodfill(459,48,15);

setcolor(41);
setfillstyle(1,41);
drawpoly(13,solaire);
floodfill(419,336,41);


}

void conejote(void)
{
setcolor(15);
setfillstyle(1,15);
drawpoly(26,conejo);
floodfill(496,375,15);



setcolor(15);
setfillstyle(1,15);
circle(478,340,28);
floodfill(477,347,15);


ellipse(469,300,0,360,5,25); 
floodfill(473,299,15);

ellipse(480,300,0,360,5,25);
floodfill(479,299,15);

setcolor(12);
setfillstyle(1,12);
ellipse(469,300,0,360,2,10);
floodfill(470,299,12);

ellipse(480,300,0,360,2,10);
floodfill(481,299,12);

setcolor(15);
setfillstyle(1,15);
circle(472,428,9);
floodfill(469,422,15);



setcolor(15);
setfillstyle(1,15);
circle(468,330,6);
floodfill(469,329,15);

setcolor(2);
setfillstyle(1,2);
circle(468,330,4);
floodfill(469,329,2);



setcolor(0);
setfillstyle(1,0);
circle(468,330,2);
floodfill(469,329,0);

setcolor(0);
line(463,435,475,417);

setcolor(0);
setfillstyle(1,0);
line(453,332,457,334);
line(457,334,453,341);
line(453,341,453,332);
floodfill(454,334,0);

setcolor(0);
arc(460,351,182,338,5);
arc(514,409,95,234,35);

}

void tortuga(void)
{

setcolor(2);
setfillstyle(1,2);
arc(161,400,0,180,90);
line(71,400,251,400);
floodfill(182,334,2);

setcolor(14);
setfillstyle(1,14);
rectangle(138,340,178,359);
floodfill(162,350,14);
rectangle(143,313,177,328);
floodfill(158,324,14);
rectangle(138,369,177,389);
floodfill(159,382,14);
rectangle(106,372,131,388);
floodfill(119,382,14);
rectangle(106,341,131,359);
floodfill(115,350,14);
rectangle(193,371,211,389);
floodfill(205,379,14);
rectangle(193,340,211,356);
floodfill(202,345,14);

setcolor(10);
setfillstyle(1,10);
circle(267,371,30);
floodfill(254,370,10);

setcolor(15);
setfillstyle(1,15);
circle(268,363,8);
floodfill(268,365,15);

setcolor(1);
setfillstyle(1,1);
circle(268,363,4);
floodfill(269,364,1);

setcolor(0);
setfillstyle(1,0);
circle(268,363,2);
floodfill(269,364,0);


setcolor(0);
arc(293,377,186,276,10);

setcolor(10);
setfillstyle(1,10);
rectangle(103,404,128,426);
floodfill(110,415,10);

setcolor(0);
line(121,426,121,409);
line(125,426,125,409);


setcolor(10);
setfillstyle(1,10);
rectangle(195,404,221,426);
floodfill(207,416,10);


setcolor(0);
line(218,426,218,409);
line(215,426,215,409);

setcolor(10);
setfillstyle(1,10);
line(47,392,70,383);
line(70,383,68,402);
line(68,402,47,392);
floodfill(62,397,10);


}

int texto1()
{

settextstyle(4,HORIZ_DIR,1);
setcolor(79);
outtextxy(25,405,"Habia una vez una liebre muy vanidosa que se pasaba todo el dia");
outtextxy(25,430,"presumiendo de lo rapido que podia correr.");


}

int texto2()
{

settextstyle(4,HORIZ_DIR,1);
setcolor(14);
  outtextxy(25,405,"Cansada de siempre escuchar sus alardes,");
  outtextxy(25,430,"la tortuga la retó a competir en una carrera.");


}

void conejo1(void)
{
	setcolor(15);
	setfillstyle(1,15);
	circle(478,340,28);
	floodfill(477,347,15);


	ellipse(469,300,0,360,5,25); 
	floodfill(473,299,15);

	ellipse(480,300,0,360,5,25);
	floodfill(479,299,15);

	setcolor(15);
	setfillstyle(1,15);
	circle(472,428,20);
	floodfill(469,422,15);


	setcolor(15);
	ellipse(390,340,0,360,70,50);
	floodfill(380,339,15);


	/*Patas del conejo*/

	ellipse(370, 390, 0, 360, 5,15); /* Pata Tracera*/
	floodfill(370,389,15);

	ellipse(430, 390, 0, 360, 5,15);  /* Pata delantera*/
	floodfill(434,389,15);

	setcolor(2);
	setfillstyle(1,2);
	circle(490,330,4);
	floodfill(490,329,2);

	/* Orejas Rosada*/
	setcolor(12);
	setfillstyle(1,12);
	ellipse(469,300,0,360,2,10);
	floodfill(470,299,12);

	ellipse(480,300,0,360,2,10);
	floodfill(481,299,12);
	/*Nariz*/
	setfillstyle(1,12);
	line(500, 340, 506, 340);
	line(500, 340, 505, 350);
	line(505, 350, 506, 340);
	floodfill(503, 340, 12);

	/*Pelos del conejo los 3 line*/
	setcolor(0);
	line(478, 335, 492, 340);
	line(478, 340, 492, 340);
	line(478, 345, 492, 340);

	setcolor(15);
}


void conejo2(void)
{
	int Cuerpo_Conejo[178] = { 224, 199,195, 210,174, 230,167, 248,159, 266,163, 289,169, 302,183, 307,201, 314,229, 315,239, 313,225, 325,220, 332,220, 339,228, 345,238, 342,248, 334,255, 328,257, 325,263, 325,271, 329,293, 333,307, 333,318, 333,329, 333,341, 333,352, 329,362, 329,379, 325,396, 319,405, 312,412, 308,423, 314,432, 317,439, 315,445, 310,446, 303,444, 300,440, 297,434, 297,434, 291,441, 286,448, 274,451, 264,450, 252,450, 241,447, 230,441, 225,436, 220,440, 211,440, 205,440, 193,434, 185,430, 178,422, 176,418, 181,418, 189,421, 198,419, 205,413, 198,403, 193,395, 191,382, 191,368, 191,359, 191,346, 191,335, 194,318, 199,309, 203,295, 209,283, 216,270, 216,256, 211,251, 205,245, 201,252, 193,258, 183,271, 168,279, 160,280, 149,272, 141,261, 141,252, 149,246, 155,239, 166,232, 173,230, 182,226, 189,224, 204};


	setcolor(15);
	setfillstyle(1,15);
	fillpoly(89,Cuerpo_Conejo);
}

void patas1(void)
{

setbkcolor(6);
	setcolor(15);
	ellipse(370, 390, 0, 360, 5,15); /* Pata Tracera*/
	floodfill(370,389,15);
          
	ellipse(430, 390, 0, 360, 5,15);  /* Pata delantera*/
	floodfill(434,389,15);

}

void patas2(void)
{
	int SegundoConejos[196] = {211, 200,193, 211,184, 220,179, 227,168, 242,166, 251,162, 264,162, 276,162, 286,163, 295,172, 303,178, 308,185, 312,192, 314,200, 316,206, 316,214, 316,223, 316,232, 315,245, 315,254, 319,264, 326,274, 332,284, 337,293, 346,300, 350,306, 354,311, 344,312, 341,309, 332,300, 326,305, 320,319, 316,330, 317,337, 322,338, 330,335, 338,332, 342,332, 345,329, 353,331, 359,337, 357,343, 356,348, 349,349, 342,357, 335,367, 330,374, 328,394, 319,408, 314,413, 308,423, 302,437, 294,441, 287,449, 272,450, 261,451, 245,446, 233,438, 220,437, 214,437, 198,437, 191,431, 183,424, 180,415, 184,417, 198,405, 196,386, 191,365, 191,349, 191,334, 194,318, 198,303, 204,291, 210,273, 212,265, 212,257, 210,250, 204,250, 195,260, 185,268, 179,275, 173,277, 165,280, 155,280, 148,271, 141,262, 141,251, 146,244, 154,241, 162,234, 168,233, 174,228, 181,225, 188,220, 193,220, 196,218, 199,200, 206};
        setbkcolor(6);
	setcolor(15);
	setfillstyle(1,15);
	fillpoly(98,SegundoConejos);
}

void cuerpo_negro1(void)
{
	int Cuerpo_Conejo[178] = { 224, 199,195, 210,174, 230,167, 248,159, 266,163, 289,169, 302,183, 307,201, 314,229, 315,239, 313,225, 325,220, 332,220, 339,228, 345,238, 342,248, 334,255, 328,257, 325,263, 325,271, 329,293, 333,307, 333,318, 333,329, 333,341, 333,352, 329,362, 329,379, 325,396, 319,405, 312,412, 308,423, 314,432, 317,439, 315,445, 310,446, 303,444, 300,440, 297,434, 297,434, 291,441, 286,448, 274,451, 264,450, 252,450, 241,447, 230,441, 225,436, 220,440, 211,440, 205,440, 193,434, 185,430, 178,422, 176,418, 181,418, 189,421, 198,419, 205,413, 198,403, 193,395, 191,382, 191,368, 191,359, 191,346, 191,335, 194,318, 199,309, 203,295, 209,283, 216,270, 216,256, 211,251, 205,245, 201,252, 193,258, 183,271, 168,279, 160,280, 149,272, 141,261, 141,252, 149,246, 155,239, 166,232, 173,230, 182,226, 189,224, 204};

        setbkcolor(6);
	setcolor(6);
	setfillstyle(1,0);
	fillpoly(89,Cuerpo_Conejo);
}


void cuerpo_negro2(void)
{
	int SegundoConejos[196] = {211, 200,193, 211,184, 220,179, 227,168, 242,166, 251,162, 264,162, 276,162, 286,163, 295,172, 303,178, 308,185, 312,192, 314,200, 316,206, 316,214, 316,223, 316,232, 315,245, 315,254, 319,264, 326,274, 332,284, 337,293, 346,300, 350,306, 354,311, 344,312, 341,309, 332,300, 326,305, 320,319, 316,330, 317,337, 322,338, 330,335, 338,332, 342,332, 345,329, 353,331, 359,337, 357,343, 356,348, 349,349, 342,357, 335,367, 330,374, 328,394, 319,408, 314,413, 308,423, 302,437, 294,441, 287,449, 272,450, 261,451, 245,446, 233,438, 220,437, 214,437, 198,437, 191,431, 183,424, 180,415, 184,417, 198,405, 196,386, 191,365, 191,349, 191,334, 194,318, 198,303, 204,291, 210,273, 212,265, 212,257, 210,250, 204,250, 195,260, 185,268, 179,275, 173,277, 165,280, 155,280, 148,271, 141,262, 141,251, 146,244, 154,241, 162,234, 168,233, 174,228, 181,225, 188,220, 193,220, 196,218, 199,200, 206};
        setbkcolor(6);
	setcolor(6);
	setfillstyle(1,0);
	fillpoly(98,SegundoConejos);
}

int texto3()
{
settextstyle(4,HORIZ_DIR,1);
setcolor(14);
  outtextxy(25,405,"Entonces, los dos se prepararon para correr, cuando llego la hora");
  outtextxy(25,420,"los dos corrieron, y el conejo viendo que la tortuga iba lejos, se durmio");
outtextxy(25,440,",pero la tortuga continuo...");
getch();

}

void pajaros(void)
{
  int x1 = 100,x2 = 100, y1 = 60, x3 = 500, x4 = 500, y2 = 60;
	while(y1 >= 0)
	{
		setcolor(15);
		line(x1 - 10, y1 - 10, 100 ,y1);
		line(x2 + 10, y1 - 10, 100 ,y1);

		line(x3- 10, y2 - 10, 500 ,y2);
		line(x4 + 10, y2 - 10, 500 ,y2);

		delay(200);
		setcolor(54);
		line(x1 - 10, y1 - 10, 100 ,y1);
		line(x2 + 10, y1 - 10, 100 ,y1);

		line(x3 - 10, y2 - 10, 500 ,y2);
		line(x4 + 10, y2 - 10, 500 ,y2);

		x1+=1;
		x2-=1;
		y1-=6;

		x3+=1;
		x4-=1;
		y2-=6;
	}

}

void conejomimido(void){

setcolor(15);
setfillstyle(1,15);
drawpoly(24,conejomimi);
floodfill(308,324,15);

setcolor(15);
setfillstyle(1,15);
circle(337,290,30);
floodfill(334,283,15);

setcolor(15);
setfillstyle(1,15);
drawpoly(9,patita);
floodfill(331,386,15);


setcolor(16);
line(330,378,336,394);
line(311,398,311,381);
line(311,381,302,381);
line(302,381,306,357);
line(306,357,303,336);
line(303,336,291,324);

setcolor(15);
setfillstyle(1,15);
ellipse(321,238,0,360,5,25);
floodfill(321,217,15);

ellipse(341,235,0,360,5,25);
floodfill(339,222,15);

setcolor(12);
setfillstyle(1,12);
ellipse(321,238,0,360,2,10);
floodfill(322,239,12);

ellipse(341,235,0,360,2,10);
floodfill(341,234,12);

setcolor(16);
line(329,283,342,283);

setfillstyle(1,16);
line(348,290,354,291);
line(354,291,350,296);
line(350,296,348,290);
floodfill(350,292,16);

setcolor(16);
line(345,310,333,307);

settextstyle(4,HORIZ_DIR,1);
setcolor(16);
  outtextxy(354,250,"Z Z Z");


}

void tortugarun(void){
setcolor(2);
setfillstyle(1,2);
arc(161,400,0,180,90);
line(71,400,251,400);
floodfill(182,334,2);

setcolor(14);
setfillstyle(1,14);
rectangle(138,340,178,359);
floodfill(162,350,14);
rectangle(143,313,177,328);
floodfill(158,324,14);
rectangle(138,369,177,389);
floodfill(159,382,14);
rectangle(106,372,131,388);
floodfill(119,382,14);
rectangle(106,341,131,359);
floodfill(115,350,14);
rectangle(193,371,211,389);
floodfill(205,379,14);
rectangle(193,340,211,356);
floodfill(202,345,14);

setcolor(10);
setfillstyle(1,10);
circle(267,371,30);
floodfill(254,370,10);

setcolor(15);
setfillstyle(1,15);
circle(268,363,8);
floodfill(268,365,15);

setcolor(1);
setfillstyle(1,1);
circle(268,363,4);
floodfill(269,364,1);

setcolor(0);
setfillstyle(1,0);
circle(268,363,2);
floodfill(269,364,0);


setcolor(0);
arc(293,377,186,276,10);

setcolor(10);
setfillstyle(1,10);
line(47,392,70,383);
line(70,383,68,402);
line(68,402,47,392);
floodfill(62,397,10);



}
void tortupatas1(void){

setcolor(10);
setfillstyle(1,10);
rectangle(103,394,128,416);
floodfill(104,399,10);

setcolor(0);
line(121,416,121,410);
line(125,416,125,410);


setcolor(10);
setfillstyle(1,10);
rectangle(195,414,221,436);
floodfill(196,416,10);


setcolor(0);
line(218,436,218,434);
line(215,436,215,434);






}
void tortupatas2(void){

setcolor(10);
setfillstyle(1,10);
rectangle(103,414,128,436);
floodfill(104,415,10);

setcolor(0);
line(121,436,121,434);
line(125,436,125,434);


setcolor(10);
setfillstyle(1,10);
rectangle(195,394,221,416);
floodfill(207,399,10);


setcolor(0);
line(218,416,218,410);
line(215,416,215,410);



}

void tortugarun2(void){

setcolor(2);
setfillstyle(1,2);
arc(221,400,0,180,90);
line(131,400,311,400);
floodfill(242,334,2);

setcolor(14);
setfillstyle(1,14);
rectangle(198,340,238,359);
floodfill(222,350,14);
rectangle(203,313,237,328);
floodfill(218,324,14);
rectangle(198,369,237,389);
floodfill(219,382,14);
rectangle(166,372,191,388);
floodfill(179,382,14);
rectangle(166,341,191,359);
floodfill(175,350,14);
rectangle(253,371,271,389);
floodfill(265,379,14);
rectangle(253,340,271,356);
floodfill(262,345,14);

setcolor(10);
setfillstyle(1,10);
circle(327,371,30);
floodfill(314,370,10);

setcolor(15);
setfillstyle(1,15);
circle(328,363,8);
floodfill(328,365,15);

setcolor(1);
setfillstyle(1,1);
circle(328,363,4);
floodfill(329,364,1);

setcolor(0);
setfillstyle(1,0);
circle(328,363,2);
floodfill(329,364,0);


setcolor(0);
arc(353,377,186,276,10);

setcolor(10);
setfillstyle(1,10);
line(107,392,130,383);
line(130,383,128,402);
line(128,402,107,392);
floodfill(122,397,10);


}

void tortugapatas3(void){

setcolor(10);
setfillstyle(1,10);
rectangle(163,394,188,416);
floodfill(164,399,10);

setcolor(0);
line(181,416,181,410);
line(185,416,185,410);


setcolor(10);
setfillstyle(1,10);
rectangle(255,414,281,436);
floodfill(256,416,10);


setcolor(0);
line(278,436,278,434);
line(275,436,275,434);

}
void tortugarun3(void){

setcolor(2);
setfillstyle(1,2);
arc(421,400,0,180,90);
line(331,400,511,400);
floodfill(442,334,2);

setcolor(14);
setfillstyle(1,14);
rectangle(398,340,438,359);
floodfill(422,350,14);
rectangle(403,313,437,328);
floodfill(418,324,14);
rectangle(398,369,437,389);
floodfill(419,382,14);
rectangle(366,372,391,388);
floodfill(379,382,14);
rectangle(366,341,391,359);
floodfill(375,350,14);
rectangle(453,371,471,389);
floodfill(465,379,14);
rectangle(453,340,471,356);
floodfill(462,345,14);

setcolor(10);
setfillstyle(1,10);
circle(527,371,30);
floodfill(514,370,10);

setcolor(15);
setfillstyle(1,15);
circle(528,363,8);
floodfill(528,365,15);

setcolor(1);
setfillstyle(1,1);
circle(528,363,4);
floodfill(529,364,1);

setcolor(0);
setfillstyle(1,0);
circle(528,363,2);
floodfill(529,364,0);


setcolor(0);
arc(553,377,186,276,10);

setcolor(10);
setfillstyle(1,10);
line(307,392,330,383);
line(330,383,328,402);
line(328,402,307,392);
floodfill(322,397,10);




}

void tortugapatas4(void){

setcolor(10);
setfillstyle(1,10);
rectangle(363,414,388,436);
floodfill(364,415,10);

setcolor(0);
line(381,436,381,434);
line(385,436,385,434);


setcolor(10);
setfillstyle(1,10);
rectangle(455,394,481,416);
floodfill(467,399,10);


setcolor(0);
line(478,416,478,410);
line(475,416,475,410);


setcolor(14);
  outtextxy(470,278,"En tu cara conejo ******");


}

void tortugafeliz(void){

setcolor(2);
setfillstyle(1,2);
arc(221,400,0,180,90);
line(131,400,311,400);
floodfill(242,334,2);

setcolor(14);
setfillstyle(1,14);
rectangle(198,340,238,359);
floodfill(222,350,14);
rectangle(203,313,237,328);
floodfill(218,324,14);
rectangle(198,369,237,389);
floodfill(219,382,14);
rectangle(166,372,191,388);
floodfill(179,382,14);
rectangle(166,341,191,359);
floodfill(175,350,14);
rectangle(253,371,271,389);
floodfill(265,379,14);
rectangle(253,340,271,356);
floodfill(262,345,14);

setcolor(10);
setfillstyle(1,10);
circle(327,371,30);
floodfill(314,370,10);

setcolor(16);
setfillstyle(1,16);
circle(328,363,8);
floodfill(328,365,16);

setcolor(40);
setfillstyle(1,40);
circle(328,363,4);
floodfill(329,364,40);

setcolor(16);
setfillstyle(1,16);
circle(328,363,2);
floodfill(329,364,16);


setcolor(0);
arc(353,377,186,276,10);

setcolor(10);
setfillstyle(1,10);
line(107,392,130,383);
line(130,383,128,402);
line(128,402,107,392);
floodfill(122,397,10);


settextstyle(4,HORIZ_DIR,1);
setcolor(14);
outtextxy(25,405,"THE END????");

}

void happyending(void){

setbkcolor(40);
setcolor(16);
settextstyle(4,HORIZ_DIR,3);

outtextxy(25,405,"So, this is what the end looks like?");



}

void portada(void)
{

    setcolor(15);
	setfillstyle(SOLID_FILL, 1);

		/*LOGO DE LA UNI*/
        setfillstyle(SOLID_FILL,BLUE);
		bar(469,28,490,107);
		delay(50);
		bar(469,86,545,107);
		delay(50);
		bar(545,107,523,55);
		delay(50);
		bar(496,28,517,80);
		delay(50);
		bar(496,48,572,28);
		delay(50);
		bar(551,28,572,107);
		delay(50);
		bar(551,86,599,107);
		delay(50);
		bar(578,107,599,55);
		delay(50);
		bar(578,28,599,48);
		delay(50);

	setfillstyle(SOLID_FILL, 15);
	delay(10);
	rectangle(10,10,630,470);

	outtextxy(124,96,"UNIVERSIDAD NACIONAL DE INGENIERIA");
	delay(50);
	outtextxy(105,124,"FACULTAD DE ELECTROTECNIA Y COMPUTACION");
	delay(50);
	outtextxy(210,155,"Integrantes:");
	delay(50);
	outtextxy(105,190,"Juan Carlos Gonzalez Zeledon 2020-0282U.");
	delay(50);
	outtextxy(105,220,"Ruben Isaac Espinoza Lopez 2020-0357U.");
	delay(50);
	outtextxy(105,254,"Kevin Jose Miranda Rugama 2020-0341U.");
	delay(50);
	outtextxy(105,290,"Nestor Gabriel Aguirre canales 2020-0479U.");
	delay(50);
	outtextxy(175,325, "Ing. Rhene Hernandez.");
	delay(50);
	outtextxy(130,360,"Cuento: La tortuga y la Liebre.");
	delay(50);
	outtextxy(185,395,"FECHA 18/05/2021");
	delay(50);
}


void tortuga1(void)
{
int i;
	/*Caparazon*/
	setcolor(2);
	setfillstyle(1,2);
	arc(161,400,0,180,90);
	line(71,400,251,400);
	floodfill(182,334,2);

	/*Colores y forma de caparazon*/
	setcolor(14);
	setfillstyle(1,14);
	rectangle(138,340,178,359);
	floodfill(162,350,14);
	rectangle(143,313,177,328);
	floodfill(158,324,14);
	rectangle(138,369,177,389);
	floodfill(159,382,14);
	rectangle(106,372,131,388);
	floodfill(119,382,14);
	rectangle(106,341,131,359);
	floodfill(115,350,14);
	rectangle(193,371,211,389);
	floodfill(205,379,14);
	rectangle(193,340,211,356);
	floodfill(202,345,14);

	/*Cabeza solo la silueta*/
	setcolor(10);
	setfillstyle(1,10);
	circle(267,371,30);
	floodfill(254,370,10);

	/*Ojo izquierdo*/
	setcolor(15);
	setfillstyle(1,15);
	circle(268,363,8);
	floodfill(268,365,15);
	
	/*Iris del ojo*/
	setcolor(1);
	setfillstyle(1,1);
	circle(268,363,4);
	floodfill(269,364,1);

	/*Pupila del ojo (Color negro)*/
	setcolor(0);
	setfillstyle(1,0);
	circle(268,363,2);
	floodfill(269,364,0);

	/*Sonrisa de la tortuga*/
	setcolor(0);
	arc(293,377,186,276,10);


	/*Cola de la tortuga*/
	setcolor(10);
	setfillstyle(1,10);
	line(47,392,70,383);
	line(70,383,68,402);
	line(68,402,47,392);
	floodfill(62,397,10);

	for (i = 0; i <= 100; i++)
	{
		if(i%2 == 0)
		{
			patass1();
		}
		delay(60);
		ocura_patas1();
		patass2();
		delay(60);
		oscura_patas2();
		
	}

delay(400);
}


void patass2(void)
{
	/*pata izquierda*/
	setcolor(10);
	/*setfillstyle(1,10);
	rectangle(103,404,128,426);
	floodfill(110,415,10);*/

	setcolor(10);
	setfillstyle(1,10);
	line(103,404,128,404); /*parte de arriba*/
	line(103,404, 80,420); /*Lado Izquierdo*/
	line(80,420, 103, 420); /*Parte de abajo*/
	line(103,420, 128,404); /*Lado Derecho*/
	floodfill(110,415,10);
	/*floodfill(110,415,10);*/

	/*Unas de la para Izquierda*/
	

	/*pata Derecha*/
	/*setcolor(10);
	setfillstyle(1,10);
	rectangle(195,404,221,426);
	floodfill(207,416,10);*/

	setcolor(10);
	setfillstyle(1,10);
	line(195,404, 221,404); /*parte de arriba*/
	line(195,404, 219,420); /*Lado Izquierdo*/
	line(219,420, 240, 420); /*Parte de abajo*/
	line(240,420, 221,404); /*Lado Derecho*/
	floodfill(210,405,10);


	/*Unas de la para derecha*/
	setcolor(0);
	line(218,426,218,409);
	line(215,426,215,409);
}

void oscura_patas2(void)
{
	setcolor(10);
	line(100,420, 125,405);
	line(97,420,122,405);
	/*pata izquierda*/
	setcolor(0);
	setfillstyle(1,0);
	line(103,404,128,404); /*parte de arriba*/
	line(103,404, 80,420); /*Lado Izquierdo*/
	line(80,420, 103, 420); /*Parte de abajo*/
	line(103,420, 128,404); /*Lado Derecho*/
	floodfill(110,415,0);
	/*floodfill(110,415,10);*/


	setcolor(10);
	line(218,426,218,409);
	line(215,426,215,409);


	setcolor(0);
	setfillstyle(1,0);
	line(195,404, 221,404); /*parte de arriba*/
	line(195,404, 219,420); /*Lado Izquierdo*/
	line(219,420, 240, 420); /*Parte de abajo*/
	line(240,420, 221,404); /*Lado Derecho*/
	floodfill(210,405,0);


}

void patass1(void)
{
	/*pata izquierda*/
	setcolor(10);
	setfillstyle(1,10);
	rectangle(103,404,128,426);
	floodfill(110,415,10);

	/*Unas de la para Izquierda*/
	setcolor(0);
	line(121,426,121,409);
	line(125,426,125,409);

	/*pata Derecha*/
	setcolor(10);
	setfillstyle(1,10);
	rectangle(195,404,221,426);
	floodfill(207,416,10);

	/*Unas de la para derecha*/
	setcolor(0);
	line(218,426,218,409);
	line(215,426,215,409);
}


void ocura_patas1(void)
{
	setcolor(10);
	line(121,426,121,409);
	line(125,426,125,409);
	/*pata izquierda*/
	setcolor(0);
	setfillstyle(1,0);
	rectangle(100,404,130,426);
	floodfill(110,415,0);



	setcolor(10);
	line(218,426,218,409);
	line(215,426,215,409);
	/*pata Derecha*/
	setcolor(0);
	setfillstyle(1,0);
	rectangle(195,404,221,426);
	floodfill(207,416,0);
}