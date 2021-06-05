#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <graphics.h>

void bb8(void);
void fondo(void);
void cabeza(void);
void cabeza_dk(void);
void cuerpo(int r_cuerpo);
void cuerpo_dk(int r_cuerpo);
void lente(int x, int y);
void movimiento(int x, int y, int r_cuerpo);

void main(void)
{
  int driver = DETECT, modo;
  int x = 334, y = 170, r_cuerpo = 110;
  initgraph(&driver, &modo, "C\\TC20\\BIN");

  movimiento(x, y, r_cuerpo);


  getch();
}

void fondo(void)
{
  time_t t;
   int x, y, i;
   /* Intializes random number generator */
   srand((unsigned) time(&t));

   /* Print 5 random numbers from 0 to 49 */
   for( i = 0 ; i < 1000 ; i++ )
   {
      x = rand() % 641;
      y = rand() % 481;

      line(x, y, x, y);
   }
   setcolor(6);
   setfillstyle(SOLID_FILL, 6);
   line(0, 400, 640, 400);
   floodfill(1, 401, 6);
}

void bb8(void)
{
  /* Detalles cuerpo */
  setcolor(1);
  setfillstyle(SOLID_FILL, 1);
  circle(319, 329, 60);
  floodfill(319, 329, 1);

  /* Estrella centro */
  setcolor(8);
  setfillstyle(SOLID_FILL, 8);
  line(310, 290, 355, 309);
  line(310, 290, 315, 309);
  line(315, 309, 298, 295);
  line(285, 330, 298, 295);
  line(285, 330, 308, 330);
  line(308, 330, 290, 344);
  line(327, 344, 333, 362);
  line(327, 344, 346, 361);
  line(290, 344, 333, 362);
  line(346, 361, 360, 325);
  line(341, 323, 360, 325);
  line(341, 323, 355, 309);
  floodfill(319, 329, 8);

  /* otros circulos */

  setcolor(1);
  setfillstyle(SOLID_FILL, 1);
  ellipse(226, 329, 0, 360, 10, 55);
  floodfill(226, 330, 1);

  setfillstyle(SOLID_FILL, 1);
  ellipse(413, 329, 0, 360, 10, 55);
  floodfill(413, 330, 1);

  setfillstyle(SOLID_FILL, 1);
  ellipse(319, 237, 0, 360, 55, 10);
  floodfill(319, 237, 1);

  setfillstyle(SOLID_FILL, 1);
  ellipse(319, 420, 0, 360, 55, 10);
  floodfill(319, 420, 1);
}

void cabeza(void)
{
  setcolor(7);
  setfillstyle(SOLID_FILL, 7);
  arc(334, 195, 350, 170, 66);
  line(270, 185, 278, 206);
  line(398, 209, 381, 223);
  line(278, 206, 381, 223);
  floodfill(334, 195, 7);

  setcolor(1);
  line(270, 185, 398, 209);
  line(310, 130, 384, 150);
}
void cabeza_dk(void)
{
  setcolor(0);
  setfillstyle(SOLID_FILL, 0);
  arc(334, 195, 350, 170, 66);
  line(270, 185, 278, 206);
  line(398, 209, 381, 223);
  line(278, 206, 381, 223);
  floodfill(334, 195, 0);
}
void lente(int x, int y)
{
  setcolor(0);
  setfillstyle(SOLID_FILL, 0);
  circle(x, y, 20);
  floodfill(x, y, 0);

  setcolor(8);
  setfillstyle(SOLID_FILL, 8);
  circle(x, y, 10);
  floodfill(x, y, 8);
}
void cuerpo(int r_cuerpo)
{
  setcolor(7);
  setfillstyle(SOLID_FILL, 7);
  circle(319, 329, r_cuerpo);
  floodfill(319, 329, 7);
}
void cuerpo_dk(int r_cuerpo)
{
  setcolor(0);
  setfillstyle(SOLID_FILL, 0);
  circle(319, 329, r_cuerpo);
  floodfill(319, 329, 0);
}

void movimiento(int x, int y, int r_cuerpo)
{
  char c;
  fondo();
  bb8();
  do
  {
    c  = getch();
    if (c == 72) /* arriba */
    {
      y-=5;

    }
    if (c  == 80) /* abajo */
    {
      y+=5;

    }
    if (c == 75) /* izquierda */
    {
      x-=5;
    }
    if (c == 77) /* derecha */
    {
      x+=5;
    }
		if (c == 27)
		{
			break;
		}
    /* cuerpo */
    if (c == 97) /*a*/
    {
      r_cuerpo += 5;
    }
    if (c == 115) /*s*/
    {
      r_cuerpo -= 5;
    }
    if (c == 114)
    {
      cleardevice();
      fondo();
      cabeza();
      bb8();
      x = 334;
      y = 170;
      r_cuerpo = 110;
      cuerpo(r_cuerpo);
      lente(x, y);
    }
    cabeza_dk();
    cabeza();
    cuerpo_dk(r_cuerpo);
    cuerpo(r_cuerpo);
    bb8();
    lente(x, y);
	}
  while (c != 100000);
}
