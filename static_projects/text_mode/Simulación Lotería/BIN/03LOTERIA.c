/*************************** Simulacion Loteria ***************************/

/*--------------- Creado por: [Michelle Calderon] -------------------------*
							  [Gabriela Robleto] 
							  [Zharoon Treminio]
							  [William Caceres] 
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <conio.h>
#include "UNILIB.h"
#include "drc.h"
#include "bug.h"
#include "presen.h"

void invertir(char []);
void aleatorio(char [],char []);
void datos(int,int,int,char [],int,int);
int menu();
void help();
void help(){
	gotoxy(27,4);cprintf("----------OPCIONES----------");
	gotoxy(10,6);cprintf("1-Presentacion : Universidad  y nombre de integrantes del equipo.");
	gotoxy(10,8);cprintf("2-Adquirir un Numero :Obtendras un Numero para poder jugar.");
	gotoxy(10,10);cprintf("3-Comenzar a jugar :Empezaras Jugar Animo! puede que ganes :-).");
	gotoxy(10,12);cprintf("4-Volver a Jugar: Jugaras de Nuevo...");
	gotoxy(10,14);cprintf("5-Ayuda: Estas en esta parte.");
	gotoxy(10,16);cprintf("6-Salir: Teminaras la ejecucion del programa.");

	textcolor(GREEN + BLINK);
	gotoxy(27,20);cprintf("Presiona cualquier tecla para regresar al menu...");
	getch();
}
int menu(){
   int i=0,opc=0,j=0;
   char selec[10],x,y;
   clrscr();
   textcolor(WHITE);
   for(i=1;i<81;i++){
      gotoxy(i,1);cprintf("=");
   }
   textcolor(GREEN);
   gotoxy(1,2);cprintf("1.");
   gotoxy(30,2);cprintf("2.");
   gotoxy(63,2);cprintf("3.");

   gotoxy(1,23);cprintf("4.");
   gotoxy(27,23);cprintf("5.");
   gotoxy(48,23);cprintf("6.");
   textcolor(WHITE);
   gotoxy(3,2);cprintf("Presentacion");
   gotoxy(33,2);cprintf("Adquirir numero");
   gotoxy(65,2);cprintf("Comenzar a jugar");
   for(i=1;i<81;i++){
      gotoxy(i,3);cprintf("=");
   }
   for(i=1;i<81;i++){
      gotoxy(i,22);cprintf("=");
   }

   gotoxy(3,23);cprintf("Volver a jugar");
   gotoxy(29,23);cprintf("Help");
   gotoxy(50,23);cprintf("Salir");
   gotoxy(68,23);cprintf("Opcion:");
 
   for(i=1;i<81;i++){
      gotoxy(i,24);cprintf("=");
   }
     Bug();
   /*---------fin del diseño del menu*/
   /*bloqueamos teclado*/
   menu:
   i=0;
   for (; ;) /*Sólo desimos que iniciaremos un nuevo ciclo*/
		{
	 textcolor(GREEN);
			gotoxy(75,23);x=getch();

	 if (x=='\r')/*si es enter muestra un mensaje*/
				if(y=='1'){
	       opc=1;
	       return opc;
	    }else if(y=='2'){
	       opc=2;
	       return opc;
	    }else if(y=='3'){
	       opc=3;
	       return opc;
	    }else if(y=='4'){
	       opc=4;
	       return opc;
	    }else if(y=='5'){
	       opc=5;
	       return opc;
	    }else if(y=='6'){
	       opc=6;
	       return opc;
	    }
			if (x!='\r'&&x!='\b' && x=='1'||x=='2'||x=='3'||x=='4'||x=='5'||x=='6') /*\r=enter \b= borrar*/
			{
				putch(x);
				y=x;
				i++;
			}
			else if (x=='\b'&&i>0)/*esperamos que ddigite algo*/
			{
				i--;
	    y=' ';
				putch(x);
	    gotoxy(75,23);
				putch(' ');
				putch(x);

			}
		}
}
int  main()
{
   int seleccion=0,a=0,b=0,noti=0,vol=0,vol_2=0;/*para validar que invirtio*/
   char auxiliar[2];
   char Reciv_tecla,x,y;
   int i = 0, j = 0, p = 0,n=0;
   char array[2];
   char arreg[1];


   logo();
   getch();
   delay(250);

   barra();
   /*menu del programa*/
   cuerpo_menu:
   seleccion=menu();

   switch(seleccion){
      case 1:
	      Logotipo ();
	      goto cuerpo_menu;
      break;
      case 2:
	      volver:
	     if (noti==0)
	     {  
            clrscr();
            fflush(stdin);
            textcolor(WHITE);
            for (p = 1; p < 81; p++)
            {gotoxy(p, 1);cprintf("=");}
            gotoxy(19, 3);                                   /*La ubicacion donde aparecera eltexto*/
            cprintf("Ingrese su numero a jugar desde [00] <--> [99]\n");
            Inicio:                                         /*Etiqueta que nos ayudara para retornar*/
            fflush(stdin);
            gotoxy(40,6);clreol();                         /*Esta funcion sirve para borrar solo la linea establecida*/
	        array[0] = ' ';
            array[1] = ' ';
            array[2]=' ';
	        i = 0;
	        j = 0;
            gotoxy(40, 6);                                 /*La ubicacion donde va aparecer la opcion digitada*/
            Llenar_array:
	        array[1] = ' ';
            array[2]=' ';                               /*Validacion de entrada para los digitos */
            while (Reciv_tecla = getch())                  /*ciclo infinito*/
	        {
	       if (Reciv_tecla > 47 && Reciv_tecla < 58)  /*Preguntamos si es un numero*/
	        {
	       if (i == 0)
	        {
		    array[0] = Reciv_tecla;
		    cprintf("%c", array[0]);
		    i = 1;
		    j = 1;
		    goto Llenar_array;
	        }
	       if (j == 1 && i == 1)
	        {
		   array[1] = Reciv_tecla;
		   cprintf("%c", array[1]);
		   j = 0;
	       }
	       }
	      if (Reciv_tecla == '\b')                                    /*\b es borrar */
		  {goto Inicio;                                             /*si borra su numero que lo devuelva*/
		  }
	      if (Reciv_tecla == '\r')                                     /*\r es Enter*/
	      {
	      array[2] = '\0';                                        /*Finalizamos el arreglo*/
	      break;                                                   /*Con esto quebramos el ciclo ya que el usuario le dio al ENTER*/
	      }
	      }
		  /*FUERA DEL CICLO VEMOS SI TODO ESTA LLENO CORRECTAMENTE SI NO QUE LO DEVUELVA */
         if (array[0] == '1' || array[0] == '2' || array[0] == '3' || array[0] == '4' || array[0] == '5' || array[0] == '6' || array[0] == '7' || array[0] == '8' || array[0] == '9' || array[0] == '0')
	     {
	     if (array[1] == '1' || array[1] == '2' || array[1] == '3' || array[1] == '4' || array[1] == '5' || array[1] == '6' || array[1] == '7' || array[1] == '8' || array[1] == '9' || array[1] == '0')
	      {
	      if (array[2] == '\0')
	     {
	      invertir(array);
	      Cantidad:                 /*Validacion de entrada para la cantidad */
	     fflush(stdin);
	     gotoxy(45,23);clreol();
	     x=' ';
	     arreg[0]=' ';
	     arreg[1]=' ';
	     while (x=getch())
	     {
	     if (x!='\r'&&x!='\b' && x=='D'||x=='d'||x=='T'||x=='t'||x=='C'||x=='c'||x=='S'||x=='s') /*\r=enter \b= borrar*/
		  {
	     x=toupper(x);
	      textcolor(GREEN);gotoxy(45,23);putch(x);
	     arreg[0]=x;
	     }
	     if (x=='\b'){goto Cantidad;}
	     if (x=='\r')
	     {
	      arreg[1]='\0';
	     break;
	     }
	      }
	      if (arreg[0]=='D'||arreg[0]=='d'||arreg[0]=='T'||arreg[0]=='t'||arreg[0]=='C'||arreg[0]=='c'||arreg[0]=='S'||arreg[0]=='s')
	      {
	     if (arreg[1]=='\0')
	     {}else{goto Cantidad;}
	     }else{goto Cantidad;}
         }else{goto Inicio;}
         }else{goto Inicio;}
          }else{goto Inicio;}
		  noti=1;
		  vol=1;
		  vol_2=0;
	     }else if (noti==1)
		 {
			clrscr();
		    gotoxy(20,13);cprintf("Usted ya adquirido un numero \n");
			gotoxy(18,14);cprintf("Para comenzar a jugar dirijase al menu\n");
			gotoxy(20,15);cprintf("Y seleccione la opcion numero ( 3 ) \n");
			textcolor(GREEN + BLINK);
	        gotoxy(17,20);cprintf("Presiona cualquier tecla para regresar al menu...");
			getch();
		 }
		 goto cuerpo_menu;
         break;
       case 3:
	    if (noti==1)
		{
		 aleatorio(array,arreg);
	     getch();
		 vol_2=1;
		 noti=0;
		}else if (noti==0)
		{
			clrscr();
		    gotoxy(20,13);cprintf("Usted no ha adquirido un numero \n");
			gotoxy(18,14);cprintf("Para adquirir un numero dirijase al menu\n");
			gotoxy(20,15);cprintf("Y seleccione la opcion numero ( 2 ) \n");
			textcolor(GREEN + BLINK);
	        gotoxy(17,20);cprintf("Presiona cualquier tecla para regresar al menu...");
			getch();
			
		}
		  goto cuerpo_menu;
       break;
       case 4:
	     if (vol==1&&vol_2==1)
		 {
		   noti=0;
		   vol=0;
		   vol_2=0;
		   goto volver;
		 }
		  if (vol==0&&vol_2==0)
		 {
		 clrscr();
		 gotoxy(18,13);cprintf("Usted no ha adquirido numero ni ha comenzado a jugar\n");
		 gotoxy(16,14);cprintf("Para adquirir un numero y comenzar a jugar dirijase al menu\n");
		 gotoxy(14,15);cprintf("Y seleccione la opcion numero ( 2 ) y luego la opcion numero ( 3 )\n");
		 textcolor(GREEN + BLINK);
	    gotoxy(17,20);cprintf("Presiona cualquier tecla para regresar al menu...");
		 getch();
          goto cuerpo_menu;
		 }
		 if (vol==1&&vol_2==0)
		 {
		 clrscr();
		 gotoxy(20,13);cprintf("Usted ya adquirido un numero \n");
		 gotoxy(18,14);cprintf("Para comenzar a jugar dirijase al menu\n");
		 gotoxy(20,15);cprintf("Y seleccione la opcion numero ( 3 ) \n");
		 textcolor(GREEN + BLINK);
	     gotoxy(17,20);cprintf("Presiona cualquier tecla para regresar al menu...");
		 getch();
		 goto cuerpo_menu;
		}
       break;
       case 5:
	   clrscr();
       help();
       goto cuerpo_menu;
       break;
       case 6:
       saliendo();
       return 1;
      break;
      default:
      goto cuerpo_menu;
      break;
   }
   getch();
   return 0;
}
void invertir(char array[]){
    int i=0,x=0,y=0,p=0,z=0;


     textcolor(WHITE);
     for (p = 1; p < 81; p++){gotoxy(p, 1);cprintf("=");}
     gotoxy(19, 3);cprintf("Ingrese su numero a jugar desde [00] <--> [99]\n");
     textcolor(GREEN);gotoxy(33, 6);cprintf("===>[%c%c]<===", array[0], array[1]);/*Mostramos lo ingresado */
     textcolor(WHITE+ BLINK);                                                      /*Decoracion */
     for (i=30; i<50; i++)
	{
		gotoxy(i,5);/*coordenadas donde estara la linea superior*/
		cprintf("%c",175);/*imprimir con formato el caracter*/
		gotoxy(i,7);/*coordenadas donde estara la linea inferior*/
		cprintf("%c",174);/*imprimir con formato el caracter*/
	}
    /*Los cuadritos con la opcion adentro*/
    textcolor(WHITE);gotoxy(29,8);cprintf("\nCantidad a invertir:\n");
    gotoxy(8,12);cprintf("%c",201);gotoxy(16,12);cprintf("%c",187); gotoxy(8,16);cprintf("%c",200);gotoxy(16,16);cprintf("%c",188);
    textcolor(GREEN);gotoxy(12,14);cprintf("10");gotoxy(11,18);cprintf("D");gotoxy(12,18);textcolor(WHITE);cprintf("iez");
    gotoxy(24,12);cprintf("%c",201);gotoxy(32,12);cprintf("%c",187);gotoxy(24,16);cprintf("%c",200);gotoxy(32,16);cprintf("%c",188);
    textcolor(GREEN);gotoxy(28,14);cprintf("30");gotoxy(26,18);cprintf("T");gotoxy(27,18);textcolor(WHITE);cprintf("reinta");
    gotoxy(42,12);cprintf("%c",201);gotoxy(50,12);cprintf("%c",187);gotoxy(42,16);cprintf("%c",200);gotoxy(50,16);cprintf("%c",188);
    textcolor(GREEN);gotoxy(46,14);cprintf("50");gotoxy(44,18);cprintf("C");gotoxy(45,18);textcolor(WHITE);cprintf("incuenta");
    gotoxy(58,12);cprintf("%c",201);gotoxy(66,12);cprintf("%c",187);gotoxy(58,16);cprintf("%c",200);gotoxy(66,16);cprintf("%c",188);
    textcolor(GREEN);gotoxy(62,14);cprintf("60");gotoxy(60,18);cprintf("S");gotoxy(61,18);textcolor(WHITE);cprintf("esenta");
    textcolor(WHITE);for(i=1;i<81;i++){gotoxy(i,22);cprintf("=");}
    textcolor(WHITE);for(i=1;i<81;i++){gotoxy(i,24);cprintf("=");}
    textcolor(LIGHTGRAY);gotoxy(19,21);cprintf("/*Ingrese la letra inicial ya sea (D-T-C-S)*/");
    textcolor(WHITE);gotoxy(37,23);cprintf("Opcion:");

}
void aleatorio(char array[],char arreg[])
{
   int numeros=0,i,cociente,residuo,num1=0,num2=0;
	char enter;
	/*Jugamos con el tiempo del sistema para asi obtener los numeros aleatorios,cambiando constantemente*/
	srand(time(NULL));
	while(1)
	{
		while (!kbhit())
		{
			system("cls");
			numeros=rand() % 99;
			cociente= numeros/10;
			residuo= numeros % 10;
			circulo();
			gotoxy(18,13); cprintf("%d",cociente);
			gotoxy(35,13); cprintf("%d",residuo);
			delay(600);
			i++;
		}
			enter=getch();
			if(enter == 13)
			{
				break;
			}
	}
	num1=array[0] - '0'; num2=array[1] - '0';/*Restar del digito el numero 0, opera los caracteres con su codigo ascii*/
	datos(numeros,num1,num2,arreg,cociente,residuo);
}
void datos(int numeros,int num1,int num2,char arreg[],int cociente,int residuo)
{
	int i;
	resultados();
	/*DATOS*/
	textcolor(WHITE);
	gotoxy(56,10);
	cprintf("NUMERO COMPRADO: [  ]\b\b\b%d%d\n",num1,num2);
	gotoxy(56,12);
	cprintf("CANTIDAD INVERTIDA: [  ]\n");
	gotoxy(56,14);
	cprintf("NUMERO GANADOR: [  ]\b\b\b%d\n",numeros);
	gotoxy(56,16);
	cprintf("ESTADO:[            ] \n");
	gotoxy(56,18);
	cprintf("PREMIO:[            ]");
   textcolor(LIGHTGREEN);
   if((num1 == cociente ) && (num2 == residuo))
   {
		gotoxy(66,16);
	   cprintf("GANADOR");fflush(stdin);
      winner();
      switch (arreg[0])
      {
      case 'D':
      case 'd': gotoxy(64,18);cprintf("PIZZA 10PLG");
         break;
      case 'T':
      case 't': gotoxy(64,18);cprintf("XIOMI MI BAND 5");
         break;
      case 'C':
      case 'c': gotoxy(64,18);cprintf("REDMI NOTE 9");
         break;
      case 'S':
      case 's': gotoxy(65,18);cprintf("MOTO NINJA");
         break;
      }
	}else
   {
      textcolor(LIGHTRED);
      gotoxy(66,16); cprintf("PERDISTE");
      gameover();
      gotoxy(66,18); cprintf("NINGUNO");
   }
   textcolor(LIGHTGREEN);
   if(arreg[0]=='D' || arreg[0]=='d')
   {
      gotoxy(77,12); cprintf("10");
      arreg[0]=' ';
   }
   if(arreg[0]=='T' || arreg[0]=='t')
   {
      gotoxy(77,12); cprintf("30");
      arreg[0]=' ';
   }
   if(arreg[0]=='C' || arreg[0]=='c')
   {
      gotoxy(77,12); cprintf("50");
      arreg[0]=' ';
   }
   if(arreg[0]=='S' || arreg[0]=='s')
   {
      gotoxy(77,12); cprintf("60");
      arreg[0]=' ';
   }
}
