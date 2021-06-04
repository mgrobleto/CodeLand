/*Importamos librerias*/
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <stdlib.h>
#include <stdio.h>
#include <mouse.h>
#include "button.h"

enum TipoDibujo{
    Equis,
    Cero
};

/**************************/
/*PROYECTO TIC TAC TOE
  Elaborado por Luis.M Pineda.J
  Grupo 2M1-CO
  Fecha de Terminacion: 14/05/2021
  ****DERECHOS RESERVADOS****/

/*Prototipamos las funciones*/
int Ganador(int Pos[3][3]);
void Pantalla_de_juego(int Dificultad);
void Tabla(void);
void Pintar_Dibujos(int x, int y, int TipoDibujo);
void PantallaVictoria(int Ganador);
void Pantalla_principal(void);
void TicTacToe(int game[][3]);
void PintarEquis(void);

/*Inicializamos variables globales*/
int VictoriasCero = 0, VictoriasEquis = 0;
int Positions[3][3];

/*Esta variable modalidad se cambiara segun la opcion que elija el usuario
  1 es para jugar contra la IA, 2 es para que puedan jugar ambos jugadores*/
int Modalidad = 1;

void main(){

    /*Inicializamos Modo Grafico*/
    int g_adap = DETECT, g_mode;

    initgraph(&g_adap,&g_mode,"C:\\TC20\\BIN");

    /*Llamamos esta funcion la cual contiene la interfaz de inicio(menu principal)*/
    Pantalla_principal();
}

/*Esta funcion muestra la pantalla principal, y segun la opcion que elija entre jugar o 
salir se ejecutara dicha accion*/
void Pantalla_principal(void){

    int xpos = 0, ypos = 0;

	setfillstyle(1,LIGHTGRAY);
    bar(0,0,640,480);

    setcolor(RED);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
    outtextxy(191,58,"TIC TAC TOE");
    
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
            Pantalla_de_juego(Modalidad);
        }
        if(limit(xpos,ypos,183,260,444,336)){
            mocultar();
            closegraph();
            exit(0);
        }

        while(mclick()==1);

    }while(1);

}

/*Esta funcion se encarga de mostrar la interfaz de juego al usuario*/
void Pantalla_de_juego(int Dificultad){

    bool Ingame = true;
    int Ganad = 0, Contador = 0;
    int xpos = 0, ypos = 0;
    int Cruz[] = {385-2,30+4, 380-2,33+4, 405-2,47+4, 380-2,58+4, 385-2,62+4, 411-2,50+4, 434-2,62+4, 442-2,58+4, 417-2,47+4, 440-2,33+4, 435-2,30+4, 411-2,44+4, 385-2,31+4};
    char Victorias[5];

    int i = 0, j = 0;

    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            Positions[i][j] = 0;

    setfillstyle(1,DARKGRAY);
    bar(0,0,640,480);
    
    /*Puntuacion*/
    setfillstyle(1,BLUE);
    fillellipse(238,48+4,20,20);

    setfillstyle(1,DARKGRAY);
    fillellipse(238,48+4,14,14);

    setfillstyle(1,RED);
    fillpoly(13,Cruz);

    settextstyle(0,0,2);
    sprintf(Victorias,"%d : %d",VictoriasCero,VictoriasEquis);
    outtextxy(244,4,"PUNTUACION");
    outtextxy(278,46+4,Victorias);
    
    /*Botones de regresar y opciones de modalidad*/
    setfillstyle(1,LIGHTGRAY);
    bar(18,30,74,66);
    bar(554,30,614,50);
    
    settextstyle(0,0,1);
    outtextxy(558,35,"Ajustes");

    setcolor(BLACK);
    line(34,48,58,48);
    line(34,48,43,35);
    line(34,48,43,61);
    setcolor(WHITE);

    /*Mostramos los bloques donde se estaran poniendo las figuras del cero y X*/
    Tabla();

    mver();

    /*Validacion del click sobre los bloques que tienen y no tienen las figuras y/o se ha heclo click sobre estos anteriormente*/
    do{
        while(mclick()!=1);

        xpos = mxpos(1);
        ypos = mypos(1);
 
        for(i = 0; i < 3; i++){
            for(j = 0; j < 3; j++){
                /*Validamos si hizo click dentro de algun cuadro de juego*/
                if(limit(xpos,ypos,68+(j*182),134+(i*116),224+(j*182),214+(i*116))){  
                    if(Dificultad == 1 && Positions[i][j] == 0){
                        mocultar();
                        Pintar_Dibujos((224+(j*373))/2,(214+(i*232))/2+50,Cero);
                        setfillstyle(1,DARKGRAY);
                        bar(68+(j*182)-4,134+(i*116),68+(j*182)-2,214+(i*116));
                        bar(68+(j*182),214+(i*116)+2,224+(j*182),214+(i*116)+4);
                        setfillstyle(1,RED);
                        bar(224+(j*182)+4,134+(i*116),224+(j*182)+2,214+(i*116));
                        bar(68+(j*182),134+(i*116)-2,224+(j*182),134+(i*116)-4);

                        Positions[i][j] = 1;

                        /*Esta variable tendra el valor que retona la funcion ganador
                         ya sea 1 para indicar que gano cero, 2 para indicar que gano X o 3 para indicat un empate*/            
                        Ganad = Ganador(Positions);

                        /*Si ya hay un ganador terminara el juego y se mostrara una pantalla de victoria*/
                        if(Ganad == 1 || Ganad == 2 || Ganad == 3)
                            Ingame = false;

                        /*En caso no haya ganador aun, se llamara la funcion tic tac toe, la cual colocara una X 
                          donde no haya dado click anteriormente el jugador, y donde no este tampoco otra X*/
                        if(Ganad != 1 || Ganad != 2 || Ganad != 3){
                            TicTacToe(Positions);
                            PintarEquis();

                            Ganad = Ganador(Positions);

                            if(Ganad == 1 || Ganad == 2 || Ganad == 3)
                                Ingame = false;
                        }
                    }
                    if(Dificultad == 2 && Positions[i][j] == 0){
                        mocultar();
                        Pintar_Dibujos((224+(j*373))/2,(214+(i*232))/2+50,Contador%2==0 ? Cero : Equis);
                        setfillstyle(1,DARKGRAY);
                        bar(68+(j*182)-4,134+(i*116),68+(j*182)-2,214+(i*116));
                        bar(68+(j*182),214+(i*116)+2,224+(j*182),214+(i*116)+4);
                        setfillstyle(1,RED);
                        bar(224+(j*182)+4,134+(i*116),224+(j*182)+2,214+(i*116));
                        bar(68+(j*182),134+(i*116)-2,224+(j*182),134+(i*116)-4);
                        Positions[i][j] = Contador%2==0 ? 1 : 4;
                        Contador++;

                        Ganad = Ganador(Positions);

                        if(Ganad == 1 || Ganad == 2 || Ganad == 3)
                            Ingame = false;
                    }
                    mver();
                }
            }
        }
        /*Boton regresar, este te devolvera al menu principal, y reiniciara los valores de las victorias*/
        if(limit(xpos,ypos,18,30,74,66)){
            mocultar();
            VictoriasCero = 0;
            VictoriasEquis = 0;
            Pantalla_principal();
        }
        /*Boton Ajustes, al presionar este boton se detendra el juego y esperara a que el jugador seleccione una modalidad de juego*/
        if(limit(xpos,ypos,554,30,614,50)){

            mocultar();
            setfillstyle(1,LIGHTBLUE);
            bar(554,50,614,70);
            bar(554,70,614,90);
            settextstyle(0,0,1);
            outtextxy(575,55,"IA");
            outtextxy(555,75,"2 Jugad");
            mver();

            do
            {   
                while(mclick()!=1);

                xpos = mxpos(1);   
                ypos = mypos(1);   

                if(limit(xpos,ypos,554,50,614,70)){
                    Modalidad = 1;
                    mocultar();
                    Pantalla_de_juego(Modalidad);
                }else if(limit(xpos,ypos,554,70,614,90)){
                    Modalidad = 2;
                    mocultar();
                    Pantalla_de_juego(Modalidad);
                }

                while(mclick()==1);

            }while(1);

        }

        while(mclick() == 1);

    }while(Ingame);

    /*Se mostrara la pantalla de victoria, en caso gane cero, X, o sea un empate*/
    PantallaVictoria(Ganad);
}

/*Funcion que pinta las X, utilizando los valores de la matriz, si existe un valor en la matriz que sea 4(X) se
  pintara en esa posicion*/
void PintarEquis(void){
	int i = 0, j = 0;

    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            if(Positions[i][j] == 4){
                Pintar_Dibujos((224+(j*373))/2,(214+(i*232))/2+50,Equis);
                setfillstyle(1,DARKGRAY);
                bar(68+(j*182)-4,134+(i*116),68+(j*182)-2,214+(i*116));
                bar(68+(j*182),214+(i*116)+2,224+(j*182),214+(i*116)+4);
                setfillstyle(1,GREEN);
                bar(224+(j*182)+4,134+(i*116),224+(j*182)+2,214+(i*116));
                bar(68+(j*182),134+(i*116)-2,224+(j*182),134+(i*116)-4);                
            }

        }
    }
}

/*Se mostrara la pantalla de vixtoria, pasando como parametro el valor del ganador, 1(Cero), 2(X), 3(Empate)*/
void PantallaVictoria(int Ganador){

    int xpos = 0, ypos = 0;

    mocultar();
    setfillstyle(1,LIGHTGRAY);
    bar(142,110,498,398);

    setfillstyle(1,BLUE);
    bar(138,110,140,398);
    bar(144,400,498,402);

    setfillstyle(1,RED);
    bar(500,110,502,398);
    bar(142,106,498,108);

    if(Ganador==1){
        settextstyle(0,0,2);
        outtextxy(174,150,"   El ganador es ");

        setfillstyle(1,BLUE);
        fillellipse(325,250,32,32);

        setfillstyle(1,LIGHTGRAY);
        fillellipse(325,250,26,26);
    }
    if(Ganador==2){
        settextstyle(0,0,2);
        outtextxy(174,150,"   El ganador es ");

        Pintar_Dibujos(284,230,Equis);
    }
    if(Ganador==3){
        settextstyle(0,0,3);
        outtextxy(220,195," Empate");
    }

    setfillstyle(1,CYAN);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);

    bar(162,340,278,360);
    outtextxy(165,345,"Jugar de nuevo");
    bar(335,340,468,360);
    outtextxy(338,345,"Regresar al menu");

    mver();

    do
    {
        while(mclick()!=1);

        xpos = mxpos(1);   
        ypos = mypos(1);

        if(limit(xpos,ypos,162,340,278,360)){
            mocultar();
            if(Ganador == 1)
                VictoriasCero += 1;
            if(Ganador == 2)
                VictoriasEquis += 1;
            Pantalla_de_juego(Modalidad);
        }
        if(limit(xpos,ypos,335,340,468,360)){
            mocultar();
            VictoriasCero = 0;
            VictoriasEquis = 0;
            Pantalla_principal();
        }

        while(mclick()==1);
    } while(1);
}

/*Pinta los cuadrados donde estaran los ceros y X*/
void Tabla(void){

    int i = 0, j = 0;

    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            setfillstyle(1,CYAN);
            bar(68+(j*182),134+(i*116),224+(j*182),214+(i*116));
            setfillstyle(1,BLUE);
            bar(68+(j*182)-4,134+(i*116),68+(j*182)-2,214+(i*116));
            bar(68+(j*182),214+(i*116)+2,224+(j*182),214+(i*116)+4);
        }
    }
}

/*Esta funcion recibe como parametros coordenadas donde estaran ubicados los dibujos del cero y X*/
void Pintar_Dibujos(int x, int y, int TipoDibujo){

    int i = 0;

    int equis[] = {2,6, 27,20, 2,34, 8,36, 34,24, 60,36, 66,34, 40,20, 66,6, 60,3, 34,17, 6,3, 2,6}; 

    switch (TipoDibujo)
    {
    case Equis:
        for(i=0; i<26; i++)
			equis[i] += i%2 == 0 ? x : y;

        setfillstyle(1,RED);
        fillpoly(13,equis);
        break;
    case Cero:
        setfillstyle(1,LIGHTBLUE);
        fillellipse(32+x,20+y,24,24);

        setfillstyle(1,CYAN);
        fillellipse(32+x,20+y,18,18);
        break;
    default:
        break;
    }
}

/*Funcion que determina el ganador y retorna un valor segun esto*/
int Ganador(int Pos[3][3]){
    int i = 0, j = 0;
    int SumaDiagonal = 0, SumaDiagonalInvertida = 0;
    int SumaFilas[3], SumaColumnas[3];
    int Gana = 0, Suma = 0;

    for(i = 0; i < 3; i++){
        SumaFilas[i] = 0;
        SumaColumnas[i] = 0;
    }

    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            if(i==j)
                SumaDiagonal += Pos[i][j];
			if(i+j == 2)
                SumaDiagonalInvertida += Pos[i][j];

            SumaFilas[i] += Pos[i][j];
            SumaColumnas[i] += Pos[j][i];
            Suma += Pos[i][j];
        }
        if(SumaFilas[i] == 3)
            Gana = 1;
        if(SumaColumnas[i] == 3)
            Gana = 1;
        if(SumaFilas[i] == 12)
            Gana = 2;
        if(SumaColumnas[i] == 12)
            Gana = 2;
    }

    if(SumaDiagonal == 3 || SumaDiagonalInvertida == 3)
        Gana = 1;
    if(SumaDiagonal == 12 || SumaDiagonalInvertida == 12)
        Gana = 2;
    if(Suma == 21 && Gana == 0)
        Gana = 3;
    return Gana;
}

/* Funcion TicTacToe pide como parametro una matriz de 3x3      *
 * la cual analizara y ubicara el siguiente movimiento mas      *
 * optimo en base a los espacios utilizados (1) y los espacios  *
 * vacios (0), ubicando su ficha (2) en las posiciones que      *
 * evitaran el gane de la ficha contraria                       */
void TicTacToe(int game[][3])
{
    /* + i y j como controladores de bucles                             *
     * + userTokens son las fichas del usuario (se utiliza una matriz   *
     *   para analizar en simultaneo)                                   *
     * + empty almacena los i y j de los espacios vacios de la matriz   *
     * + randomPosition almacenara el espacio random al que se ubicara  * 
     *   la ficha de la computadora                                     */
    int i = 0, j = 0, emptyCounts = 0;
    int userTokens[4];
    int empty[9][2];
    int randomPosition = 0;

    for(i = 0; i < 9; i++)
        for(j = 0; j < 2; j++)
            empty[i][j] = 0;

    for(i = 0; i < 3; i++)
    {
        userTokens[0] = userTokens[1] = userTokens[2] = userTokens[3] = 0;

        for(j = 0; j < 3; j++)
        {
            /* Se identifican los espacios vacios para que en caso de   *
             * no tener evitar un gane, pueda ponerlo en los espacios   *
             * vacios con un random (posterior al for)                  */
            if(game[i][j] == 0)
            {
                empty[emptyCounts][0] = i;
                empty[emptyCounts][1] = j;
                emptyCounts++;
            }

            /* Se analiza la fila correspondiente a i y se aumentan cada*
             * vez que exista un 1                                      */
            if(game[i][j] == 1)
                userTokens[0]++;

            /* Se analiza la columna correspondiente a i y se aumentan cada *
             * vez que exista un 1                                          */
            if(game[j][i] == 1)
                userTokens[1]++;

            /* Se analiza la diagonal para saber cuantos 1 existen */
            if(game[j][j] == 1)
                userTokens[2]++;
            
            /* Se analiza la diagonal inversa para saber cuantos 1 existen */
            if(game[j][2-j] == 1)
                userTokens[3]++;
        }
        
        /* En un dado caso el contador de 1 en la fila analizada sea 2  *
         * entonces se busca el espacio vacio para evitar el gane       */
        if(userTokens[0] == 2)
            for(j = 0; j < 3; j++)
                if(game[i][j] == 0)
                {
                    game[i][j] = 4;
                    return;
                }

        /* En un dado caso el contador de 1 en la columna analizada sea 2   *
         * entonces se busca el espacio vacio para evitar el gane           */
        if(userTokens[1] == 2)
            for(j = 0; j < 3; j++)
                if(game[j][i] == 0)
                {
                    game[j][i] = 4;
                    return;
                }

        /* En un dado caso el contador de 1 en la diagonal analizada sea 2  *
         * entonces se busca el espacio vacio para evitar el gane           */      
        if(userTokens[2] == 2)
            for(j = 0; j < 3; j++)
                if(game[j][j] == 0)
                {
                    game[j][j] = 4;
                    return;
                }

        /* En un dado caso el contador de 1 en la diagonal inversa analizada    *
         *sea 2 entonces se busca el espacio vacio para evitar el gane          */
        if(userTokens[3] == 2)
            for(j = 0; j < 3; j++)
                if(game[j][2-j] == 0)
                {
                    game[j][2-j] = 4;
                    return;
                }
    }

    /* Si no existiese amenaza, utiliza un random para  *
     * ubicar el 2 en alguno de los espacios vacios     */
    if(emptyCounts != 0){
        randomPosition = rand() % emptyCounts;
        game[empty[randomPosition][0]][empty[randomPosition][1]] = 4;
    }

}
