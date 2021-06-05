/********************* Simulacion Cajero Automatico GAMI *********************/

/*--------------- Creado por: Gabriela Robleto y Michelle Calderon ---------------*/

/* Claves de PIN: 1. 9212
/*                2. 8640
				  3. 8212
*/

#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define LONGITUD 4
#define MAX 80

/*Variables Globales*/
float cuenta=500;
float NIO=500*34.33;
float agua=1500;float luz=600;
char PIN_1[LONGITUD+1];char PIN_2[LONGITUD+1];char PIN_3[LONGITUD+1];char PIN_USUARIO[LONGITUD+1];
char NEWPIN_USUARIO[LONGITUD+1];
int sala=0;
int validar_num(char numero[2000]);
/*Funciones*/
void menu();
void Sala(char [],char []);
void recivsalario(char [],char [],int,float);
void consulta();
void retiros(char [],char []);
void recivRetirar(char [],char [],float,float);
void recivRetirar2(char [],char [],float,float);
void transferencia(char[]);
void Aux_transferencia(char[]);
void arbolito();
void menu1(char *);
void menu2(char *);
void menu3(char *);
void recargas(char []);
void deposito(char[],char[]);
void factura(float,char[],char[]);
void servicios(char[],char[],float *,float *);
void CAMBIOPIN(char *, char *,char *,char *,char *);
void NuevoPIN(char *,char *);
void NuevoPIN2(char *,char *);
void NuevoPIN3(char *,char *);

/*Funcion Principal*/
void menu(){
int i=0;
clrscr();
for(i=0;i<39;i++){printf("*");printf(" ");}
gotoxy(25,10);printf("\n\t\t\tBIENVENIDOS AL CAJERO \n");
gotoxy(1,25);for(i=0;i<39;i++){printf("*");printf(" ");}sleep(3);
clrscr();for(i=0;i<39;i++){printf("*");printf(" ");}gotoxy(25,10);
printf("\n\t\tPOR FAVOR PRESIONE ENTER PARA INGRESAR SU TARJETA\n\n\t\t\tY SIGA LAS INSTRUCCIONES\n\n\t\tLA TARJETA POSEE CHIP,DEBE PERMANECER EN CAJERO\n\n\t\t\tHASTA FINALIZAR SU TRANSACCION\n");
gotoxy(1,25);for(i=0;i<39;i++){printf("*");printf(" ");}getch();clrscr();getch();
}
void main(void){
	char caracter;
	int i=0,ingresa=0,intentos=0;
	strcpy(PIN_1, "9212");
	strcpy(PIN_2, "8640");
	strcpy(PIN_3, "8212");
	menu();
	do{
		i=0;
		clrscr();
		gotoxy(31,4);
		printf("******LOGIN******");
		gotoxy(1,6);
		printf("\n\tDigite su PIN: ");
		
		while(caracter = getch()){
			if(caracter == 13)
			{
				PIN_USUARIO[i]='\0'; /*Esto me indica el final de una cadena*/
				break;
			}else if(caracter==8)
			{
				if(i > 0)
				{
					i--; /*El caracter ira disminuyendo*/
					printf("\b \b"); /*Mueve el cursor hacia la izquierda (backspace)*/
				
				}
			}else
			{
				if(i < LONGITUD)
				{
					printf("*");
					
					PIN_USUARIO[i]=caracter;
					i++; /*Para que el caracter que le sigue se imprima con asterisco*/
				}
			}
		}
		if(strcmp(PIN_1, PIN_USUARIO)==0 || strcmp(PIN_2,PIN_USUARIO)==0 || strcmp(PIN_3,PIN_USUARIO)==0)
		{
			ingresa=1;
		}else
		{
			clrscr();
			gotoxy(5,12);
			printf("\t\t\t\tPIN INCORRECTO!");
			intentos++;
			getchar();
		}
	}while(intentos< 3 && ingresa==0);/*ingresa 0 es falso, el usuario solo tiene 3 intentos*/
	/*Si el PIN es correcto, entonces...*/
	if(ingresa==1)
	{ 
		clrscr();
		gotoxy(5,13);
    	printf("\t\t\t\tCargando.");
    	sleep(1);
    	printf(".");
    	sleep(1);
    	printf(".");
    	sleep(1);
    	clrscr();
		if(strcmp(PIN_USUARIO,PIN_1)==0)
		{
		
			menu1(PIN_1);
		}else
		{
			if(strcmp(PIN_USUARIO,PIN_2)==0)
			{
				
				menu2(PIN_2);
			}else
			{
				
				menu3(PIN_3);
			}
		}
	}else
	{
		clrscr();
		gotoxy(1,13);
		printf("\t\tHa excedido el intento maximo de intentos permitidos");
	}
	getch();
}

void menu1(){ /*Menu-Usuario 1*/
	char numcuenta[10]="234567980";char numcard[17]="1234XXXXXXXX1121";
	char usuario1[20]="Norwing";
	char s[MAX];
	int opcion;
	do{
		
		clrscr();
		printf("BIENVENIDO: %s", usuario1);
		sleep(1);
		/*printf("\nSaldo actual: %.2f",cuenta);*/
		printf("\n\n\t\tSELECCIONE EL TIPO DE OPERACION QUE DESEA REALIZAR");
		printf("\n\n\n\t\t1<-Tranferencias\t\t2<-Extracciones\n\n\n\t\t3<-Adelantos");
		printf("\t\t\t4<-Recargas telefonicas\n\n\n\t\t5<-Gestion de Claves\t\t6<-Depositos\n\n\n\t\t7<-Pago de Servicios publicos\t8<-Consulta de Saldo\n\n\n\t\t9<-Salir");
		printf("\n\n\t\tOpcion: [ ]\b\b");
		fflush(stdin);
		scanf("%d",&opcion);
		switch(opcion){
			case 1:
				fflush(stdin);
				if(cuenta<=0){
					clrscr();
					gotoxy(25,10);
					printf("Lo sentimos no hay suficiente en la cuenta");
					getch();
				}else{
					transferencia(numcard);	
				}
			break;
			case 2:
				fflush(stdin);
				if(cuenta<=0){
					clrscr();
					gotoxy(25,10);
					printf("Lo sentimos no hay suficiente en la cuenta");
					getch();
				}else{
					retiros(numcuenta,numcard);
				}
			break;
			case 3:
			    Sala(numcuenta,numcard);
			break;	
			case 4:
				fflush(stdin);
				if(cuenta<=0){
					clrscr();
					gotoxy(25,10);
					printf("Lo sentimos no hay suficiente en la cuenta");
					getch();
				}else{
					recargas(numcuenta);
				}
			break;
            case 5:
                CAMBIOPIN(PIN_USUARIO,PIN_1,PIN_2,PIN_3,NEWPIN_USUARIO);
            break;
			case 6:
				deposito(numcuenta,numcard);
			break;
			case 7:
				fflush(stdin);
				if(cuenta<=0){
					clrscr();
					gotoxy(25,10);
					printf("Lo sentimos no hay suficiente en la cuenta");
					getch();
				}else{
					servicios(numcuenta,numcard,&agua,&luz);
				}
				
			break;
			case 8:
			    consulta();
			break;
			case 9:
			    exit(1);
			break;
		}
	volver:
		clrscr();
		gotoxy(7,9);
		printf("\n\n\t\tDesea realizar otra operacion? [S/N]: [ ]\b\b");fflush(stdin);
		gets(s);
	}while(strcmp(s,"S")==0 || strcmp(s,"s")==0);
	if(strcmp(s,"N")==0 || strcmp(s,"n")==0)
	{
		clrscr();
		gotoxy(10,13);
		printf("\t\t\tSaliendo.");
		sleep(1);
		printf(".");
		sleep(1);
		printf(".");
		sleep(1);
	}else
	{
		printf("\n\n\n\t\tPor favor, introduzca datos validos!");
		goto volver;
	}
}

void menu2(){
	char numcuenta[10]="210920021";char numcard[17]="8910XXXXXXXX1112";
	char usuario2[20]="Michelle";
	char s[MAX];
	int opcion;
	do{
		clrscr();
		printf("BIENVENIDA: %s", usuario2);
		sleep(1);
		/*printf("\nSaldo actual: %.2f",cuenta);*/
		printf("\n\n\t\tSELECCIONE EL TIPO DE OPERACION QUE DESEA REALIZAR");
		printf("\n\n\n\t\t1<-Tranferencias\t\t2<-Extracciones\n\n\n\t\t3<-Adelantos");
		printf("\t\t\t4<-Recargas telefonicas\n\n\n\t\t5<-Gestion de Claves\t\t6<-Depositos\n\n\n\t\t7<-Pago de Servicios publicos\t8<-Consulta de Saldo\n\n\n\t\t9<-Salir");
		printf("\n\n\n\t\tOpcion: ");fflush(stdin);
		scanf("%d",&opcion);
	switch(opcion){
			case 1:
				fflush(stdin);
				if(cuenta<=0){
					clrscr();
					gotoxy(25,10);
					printf("Lo sentimos no hay suficiente en la cuenta");
					getch();
				}else{
					transferencia(numcard);	
				}
			break;
			case 2:
				fflush(stdin);
				if(cuenta<=0){
					clrscr();
					gotoxy(25,10);
					printf("Lo sentimos no hay suficiente en la cuenta");
					getch();
				}else{
					retiros(numcuenta,numcard);
				}
			break;
			case 3:
			    Sala(numcuenta,numcard);
			break;	
			case 4:
				fflush(stdin);
				if(cuenta<=0){
					clrscr();
					gotoxy(25,10);
					printf("Lo sentimos no hay suficiente en la cuenta");
					getch();
				}else{
					recargas(numcuenta);
				}
			break;
            case 5:
                CAMBIOPIN(PIN_USUARIO,PIN_1,PIN_2,PIN_3,NEWPIN_USUARIO);
            break;
			case 6:
				deposito(numcuenta,numcard);
			break;
			case 7:
				fflush(stdin);
				if(cuenta<=0){
					clrscr();
					gotoxy(25,10);
					printf("Lo sentimos no hay suficiente en la cuenta");
					getch();
				}else{
					servicios(numcuenta,numcard,&agua,&luz);
				}
				
			break;
			case 8:
			    consulta();
			break;
			case 9:
			    exit(1);
			break;
		}
	volver:
		clrscr();
		gotoxy(7,9);
		printf("\n\n\t\tDesea realizar otra operacion? [S/N]: [ ]\b\b");fflush(stdin);
		gets(s);fflush(stdin);
	}while(strcmp(s,"S")==0 || strcmp(s,"s")==0);
	if(strcmp(s,"N")==0 || strcmp(s,"n")==0)
	{
		clrscr();
		gotoxy(10,13);
		printf("\t\t\tSaliendo.");
		sleep(1);
		printf(".");
		sleep(1);
		printf(".");
		sleep(1);
	}else
	{
		printf("\n\n\n\t\tPor favor, introduzca datos validos!");
		goto volver;
	}
}

void menu3(){
	char numcuenta[]="821202427"; char numcard[]="1314XXXXXXXX1516";
	char usuario3[20]="Gabriela";
	int opcion;
	char s[MAX];
	do{
		clrscr();
		printf("BIENVENIDA: %s", usuario3);
		sleep(1);
		/*printf("\nSaldo actual: %.2f",cuenta);*/
		printf("\n\n\t\tSELECCIONE EL TIPO DE OPERACION QUE DESEA REALIZAR");
		printf("\n\n\n\t\t1<-Tranferencias\t\t2<-Extracciones\n\n\n\t\t3<-Adelantos");
		printf("\t\t\t4<-Recargas telefonicas\n\n\n\t\t5<-Gestion de Claves\t\t6<-Depositos\n\n\n\t\t7<-Pago de Servicios publicos\t8<-Consulta de Saldo\n\n\n\t\t9<-Salir");
		printf("\n\n\n\t\tOpcion: ");fflush(stdin);
		scanf("%d",&opcion);
		switch(opcion){
			case 1:
				fflush(stdin);
				if(cuenta<=0){
					clrscr();
					gotoxy(25,10);
					printf("Lo sentimos no hay suficiente en la cuenta");
					getch();
				}else{
					transferencia(numcard);	
				}
			break;
			case 2:
				fflush(stdin);
				if(cuenta<=0){
					clrscr();
					gotoxy(25,10);
					printf("Lo sentimos no hay suficiente en la cuenta");
					getch();
				}else{
					retiros(numcuenta,numcard);
				}
			break;
			case 3:
			    Sala(numcuenta,numcard);
			break;	
			case 4:
				fflush(stdin);
				if(cuenta<=0){
					clrscr();
					gotoxy(25,10);
					printf("Lo sentimos no hay suficiente en la cuenta");
					getch();
				}else{
					recargas(numcuenta);
				}
			break;
            case 5:
                CAMBIOPIN(PIN_USUARIO,PIN_1,PIN_2,PIN_3,NEWPIN_USUARIO);
            break;
			case 6:
				deposito(numcuenta,numcard);
			break;
			case 7:
				fflush(stdin);
				if(cuenta<=0){
					clrscr();
					gotoxy(25,10);
					printf("Lo sentimos no hay suficiente en la cuenta");
					getch();
				}else{
					servicios(numcuenta,numcard,&agua,&luz);
				}
				
			break;
			case 8:
			    consulta();
			break;
			case 9:
			    exit(1);
			break;
		}
	volver:
		clrscr();
		gotoxy(7,9);
		printf("\n\n\t\tDesea realizar otra operacion? [S/N]: [ ]\b\b");fflush(stdin);
		gets(s);fflush(stdin);
	}while(strcmp(s,"S")==0 || strcmp(s,"s")==0);
	if(strcmp(s,"N")==0 || strcmp(s,"n")==0)
	{
		clrscr();
		gotoxy(10,13);
		printf("\t\t\tSaliendo.");
		sleep(1);
		printf(".");
		sleep(1);
		printf(".");
		sleep(1);
	}else
	{
		printf("\n\n\n\t\tPor favor, introduzca datos validos!");
		goto volver;
	}
}

void transferencia(char numcard[]){
int OpcBanc=0,i=0;


do{
fflush(stdin);
clrscr();
for(i=0;i<39;i++){printf("*");printf(" ");}
printf("\nSELECCIONE EL BANCO DONDE QUIERE REALIZAR LA TRANSFERENCIA");
printf("\n\n1<-Banpro\t\t\t2<-BDF\n\n3<-lafise\t\t\t4<-Avanz\n\n5<-Ficohsa\t\t\t6<-Bac\n");
for(i=0;i<39;i++){printf("*");printf(" ");}
fflush(stdin);
printf("\nOpcion: ");scanf("%d",&OpcBanc);
switch(OpcBanc){
	case 1:
	 Aux_transferencia(numcard);	
	 arbolito();
     break;
    case 2:
     Aux_transferencia(numcard);	
	 arbolito();
    break;
    case 3:
     Aux_transferencia(numcard);	
	 arbolito();
    break;
   case 4:
   	Aux_transferencia(numcard);		
	arbolito();
    break;
    case 5:
     Aux_transferencia(numcard);	
	 arbolito();
    break;
    case 6:
     Aux_transferencia(numcard);	
	 arbolito();
    break;
}
}while(!(OpcBanc==1||OpcBanc==2||OpcBanc==3||OpcBanc==4||OpcBanc==5||OpcBanc==6));
}

void retiros(char  numcard[],char numcuenta[]){
	int opc=0,Ocant=0;
	float saldo=0.0,cantUsuario;
	
	clrscr();
	do{
	 gotoxy(25,10);
     printf("\n\t\t\tSeleccione su moneda\n");
	 printf("\n\n\n\t\t\t\t\t\t1>Dolares\n\n\n");
   	 printf("\n\t\t\t\t\t\t2>Cordobas\n\n\n");
     scanf("%d",&opc);
     fflush(stdin);
     clrscr();
	 if(opc==1){
	 	fflush(stdin);
	 	do{/*Dolares*/
	     printf("\n\t\t\tSeleccione la cantidad a retirar\n");
	     printf("\n\n1>|_____20_____|\t\t\t\t\t\t2>|_____40_____|\n\n\n\n\n\n\n3>|_____60_____|\t\t\t\t\t\t4>|_____80_____|\n\n\n\n\n\n\n5>|_____100_____|\t\t\t\t\t6>|___Otra cantidad___|\n\n");
	     scanf("%d",&Ocant);
	     fflush(stdin);
	     clrscr();
	     switch(Ocant){
	     	case 1:
	     		cantUsuario=20;
	     	    saldo=(cuenta-cantUsuario);
	     	    recivRetirar(numcard,numcuenta,cantUsuario,saldo);
	     	    arbolito();
	     	    break;
	     	case 2:
	     		cantUsuario=40;
	     	    saldo=cuenta-cantUsuario;
	     	    recivRetirar(numcard,numcuenta,cantUsuario,saldo);
	     	    arbolito();
	     	    break;
	     case 3:
	     		cantUsuario=60;
	     	    saldo=cuenta-cantUsuario;
	     	    recivRetirar(numcard,numcuenta,cantUsuario,saldo);
	     	    arbolito();
	     	    break;	    
	    case 4:
	     		cantUsuario=80;
	     	    saldo=cuenta-cantUsuario;
	     	    recivRetirar(numcard,numcuenta,cantUsuario,saldo);
	     	    arbolito();
	     	    break;
	    case 5:
	     		cantUsuario=100;
	     	    saldo=cuenta-cantUsuario;
	     	    recivRetirar(numcard,numcuenta,cantUsuario,saldo);
	     	    arbolito();
	     	    break;
	   case 6:
	     		clrscr();
	     		fflush(stdin);
	     		gotoxy(25,10);
	     		printf("\n\t\t\tIngrese otra cantidad: \n");
	    	if((scanf("%f",&cantUsuario))==1){/*Para que solo  ingrese numeros*/
	     		fflush(stdin);
	     		clrscr();
	     		    if(cantUsuario<=0){
	     		    	gotoxy(25,10);
	     		    	printf("\n\t\t\tCantidad incorrecta\n");
				   }else{
				 	if(cantUsuario>cuenta){
	     			gotoxy(25,10);
	     			printf("\n\t\t\tL0 SENTIMOS NO DISPONE SUFICIENTE EN SU CUENTA\n");
				 }
				 else{
				saldo=cuenta-cantUsuario;
				recivRetirar(numcard,numcuenta,cantUsuario,saldo);
	     	    arbolito();
	     	    	    
                  }
				 }
	     		
			 }else{
			 clrscr();gotoxy(25,10);printf("\n\t\tError dato no valido");
			 }	
               break;
		 }
	    }while(!(Ocant==1||Ocant==2||Ocant==3||Ocant==4||Ocant==5||Ocant==6));
	}
	 if(opc==2){
	 	fflush(stdin);
	 	do{/*Cordobas*/
	     printf("\n\t\t\tSeleccione la cantidad a retirar\n");
	     printf("\n\n1>|_____100_____|\t\t\t\t\t\t2>|____200____|\n\n\n\n\n\n\n3>|_____400_____|\t\t\t\t\t\t4>|____600____|\n\n\n\n\n\n\n5>|_____1000_____|\t\t\t\t\t6>|___Otra cantidad___|\n\n");
	     scanf("%d",&Ocant);
	     fflush(stdin);
	     clrscr();
	     switch(Ocant){
	     	case 1:
	     		clrscr();
	     		fflush(stdin);
	     		cantUsuario=100;
	     	    cuenta=cuenta*34.33;
	     	    recivRetirar2(numcard,numcuenta,cantUsuario,saldo);
	     	    arbolito();
	     	    break;
	     	case 2:
	     		clrscr();
	     		fflush(stdin);
	     		cantUsuario=200;
	     	    saldo=(cuenta*34.33)-cantUsuario;
	     	    recivRetirar2(numcard,numcuenta,cantUsuario,saldo);
	     	    arbolito();
	     	    break;
	     case 3:
	     		clrscr();
	     		fflush(stdin);
	     		cantUsuario=400;
	     	    saldo=(cuenta*34.33)-cantUsuario;
	     	    recivRetirar2(numcard,numcuenta,cantUsuario,saldo);
	     	    arbolito();
	     	    break;	    
	    case 4:
	     		clrscr();
	     		fflush(stdin);
	     		cantUsuario=600;
	     	    saldo=(cuenta*34.33)-cantUsuario;
	     	    recivRetirar2(numcard,numcuenta,cantUsuario,saldo);
	     	    arbolito();
	     	    break;
	    case 5:
	     		clrscr();
	     		fflush(stdin);
	     		cantUsuario=1000;
	     	    saldo=(cuenta*34.33)-cantUsuario;
	     	    recivRetirar2(numcard,numcuenta,cantUsuario,saldo);
	     	    arbolito();
	     	    break;
	   case 6:
	     		clrscr();
	     		fflush(stdin);
	     		gotoxy(25,10);
	     		printf("\n\t\t\tIngrese otra cantidad: \n");
	     	    if((scanf("%f",&cantUsuario))==1){
	     	  	fflush(stdin);
	     		clrscr();
	     		if(cantUsuario<=0){
	     			printf("\n\t\t\tCantidad incorrecta\n");
				 }else{
				 	if(cantUsuario>cuenta*34.33){
	     		gotoxy(25,10);
	     		printf("\n\t\t\tL0 SENTIMOS NO DISPONE SUFICIENTE EN SU CUENTA\n");
				 }
				 else{
				saldo=(cuenta*34.33)-cantUsuario;
				recivRetirar2(numcard,numcuenta,cantUsuario,saldo);
	     	    arbolito();
				 }
	     	    
		     	}
			   }else{
			   clrscr();gotoxy(25,10);printf("\n\t\tError dato no valido");}
			   break;
			}
	    }while(!(Ocant==1||Ocant==2||Ocant==3||Ocant==4||Ocant==5||Ocant==6));
 }

	}while(!(opc==2||opc==1));/*Para que no ingrese otra cosa loca solo 1&2*/
	getch();
}

void recivRetirar(char numcard[],char numcuenta[],float cantUsuario,float saldo){
	int i=0;
	time_t tiempo_real;
    struct tm * timeinfo;
     clrscr();time(&tiempo_real);timeinfo=localtime(&tiempo_real);
	clrscr();
	fflush(stdin);
	for(i=0;i<39;i++){printf("*");printf(" ");}
	fflush(stdin);
	printf("\n\t\t\t\tGAMI\n\t\t\tSiempre en servicio\n\t\t\tDinero las 24 horas\n\t\t\t\t\t\tMANAGUA-NICARAGUA\n");
    printf("\n\nNumero de tarjeta: %s", numcard);
	printf("\n\nNumero de cuenta : %s",numcuenta);
	printf("\n\nFecha y hora     : %s ",asctime(timeinfo));
	printf("\n\nMaquina          :GAMI26 MULTI SUC LAS AM");
	printf("\n\nMonto            :%f",cantUsuario);
	printf("\n\nBalance          :%.2f",saldo);
	fflush(stdin);
	gotoxy(1,25);
    for(i=0;i<39;i++){printf("*");printf(" ");}getch();
    cuenta=cuenta-cantUsuario;
}

void recivRetirar2(char numcard[],char numcuenta[],float cantUsuario,float saldo ){
	int i=0;
	time_t tiempo_real;
    struct tm * timeinfo;
     clrscr();time(&tiempo_real);timeinfo=localtime(&tiempo_real);
    saldo=cuenta*34.33-cantUsuario;
	clrscr();
	fflush(stdin);
	for(i=0;i<39;i++){printf("*");printf(" ");}
	fflush(stdin);
	printf("\n\t\t\t\tGAMI\n\t\t\tSiempre en servicio\n\t\t\tDinero las 24 horas\n\t\t\t\t\t\tMANAGUA-NICARAGUA\n");
    printf("\n\nNumero de tarjeta: %s", numcard);
	printf("\n\nNumero de cuenta : %s",numcuenta);
	printf("\n\nFecha y hora     : %s ",asctime(timeinfo));
	printf("\n\nMaquina          :GAMI26 MULTI SUC LAS AM");
	printf("\n\nMonto            :%f",cantUsuario);
	printf("\n\nBalance          :%.2f",saldo);
	fflush(stdin);
	gotoxy(1,25);
    for(i=0;i<39;i++){printf("*");printf(" ");}getch();
    cuenta=saldo/34.33;
}


void Sala(char numcard[],char numcuenta[]){
	sala=sala;
	fflush(stdin);
		clrscr();
	if(sala==1){
		fflush(stdin);
		clrscr();
		gotoxy(25,10);
		printf("\n\t\tUsted ya realizo adelanto de salario\n");
		getch();
	}
	if(sala==0){
		int salario=6000,opc=0,i=0;
	float adelanto=0.0;
	char empleado[50];
	time_t tiempo_real;
    struct tm * timeinfo;
     clrscr();
    time(&tiempo_real);
    timeinfo=localtime(&tiempo_real);
	clrscr();
	gotoxy(1,9);
	for(i=0;i<39;i++){
	printf("*");
	printf(" ");
	}
	fflush(stdin);
	gotoxy(25,10);
	printf("\nIngrese su nombre y primer apellido: ");
	gets(empleado);
	printf("\nSu salario en NIO es:%d \n",salario);
	gotoxy(1,18);
	for(i=0;i<39;i++){
	printf("*");
	printf(" ");
	}sleep(2);
	
		do{
		fflush(stdin);
		clrscr();	
			gotoxy(25,10);
         printf("\n\tSeleccione el porcentaje del salario que quiere adelantar\n");
	      printf("\n\n\n\t1>15 por ciento \t\t2>30 por ciento\n");
   	     printf("\n\n\t3>50 por ciento \t\t4>80 por ciento\n");
          scanf("%d",&opc);
          switch(opc){
          	case 1:
          		fflush(stdin);
          		adelanto=900;
          		clrscr();
	     	    recivsalario(numcard,numcuenta,salario,adelanto);
	             arbolito();break;
          	case 2:
          		fflush(stdin);
          		adelanto=1800;
          		clrscr();
	     	    recivsalario(numcard,numcuenta,salario,adelanto);
	             arbolito();break;
          	case 3:
          		fflush(stdin);
          		adelanto=3000;
          		clrscr();
	     	    recivsalario(numcard,numcuenta,salario,adelanto);
	             arbolito();break;
          	case 4:
          		fflush(stdin);
          		adelanto=4800;
          		clrscr();
	     	    recivsalario(numcard,numcuenta,salario,adelanto);
	            arbolito();break;
          				
		  }
		}while(!(opc==1||opc==2||opc==3||opc==4));
	}
	
		sala++;
	 
	}
	
void recivsalario(char numcard[],char numcuenta[],int salario,float adelanto){/*El del salario*/
	int i=0;/*Para el for,de ahi los otros valores son pedidos*/
	time_t tiempo_real;
    struct tm * timeinfo;
    clrscr();
    time(&tiempo_real);
    timeinfo=localtime(&tiempo_real);
	clrscr();
for(i=0;i<39;i++){printf("*");printf(" ");}
fflush(stdin);
printf("\n\t\t\t\tGAMI\n\t\t\tSiempre en servicio\n\t\t\tDinero las 24 horas\n\t\t\t\t\t\tMANAGUA-NICARAGUA\n");
printf("\n\nNumero de tarjeta: %s", numcard);
printf("\n\nNumero de cuenta : %s",numcuenta);
printf("\n\nFecha y hora     :%s",asctime(timeinfo));
printf("\n\nMaquina          :GAMI26 MULTI SUC LAS AM");
printf("\n\nSalario          :%d",salario);
printf("\n\nAdelanto         :%.2f",adelanto);
printf("\n\nBalance          :%.2f",-adelanto);
fflush(stdin);
gotoxy(1,25);
for(i=0;i<39;i++){printf("*");printf(" ");}
getch();
adelanto=adelanto/34.33;
cuenta=-adelanto;
}

void recargas(char numcuenta[]){
	
	int Ropc=0,Nio=0,conf=0,i=0,tam=0;
    float monto;
    long int numero=0;
    time_t tiempo_real;
    struct tm * timeinfo;
    clrscr();
    time(&tiempo_real);
    timeinfo=localtime(&tiempo_real);
	fflush(stdin);clrscr();
	/*Aqui inicia todo*/
	do{
	 gotoxy(25,10);
     printf("\n\t\t\tSeleccione su servicio\n");
	 printf("\n\n\n\t\t\t\t\t\t1>Tigo\n\n\n");
   	 printf("\n\t\t\t\t\t\t2>Claro\n\n\n");
     scanf("%d",&Ropc);
     fflush(stdin);
     clrscr();
     if(Ropc==1){
     	do{
     	fflush(stdin);
     	clrscr();
     	for(i=0;i<39;i++){printf("*");printf(" ");}
     	printf("\n\t\tServicio\n\tTigo\n\t\tIngrese el n%cmero\n\t",163);
     	if(scanf("%li",&numero)==1){
     		if(numero>10000000&&numero<99999999){
     			printf("\n\t\tIngrese la cantidad a pagar en NIO\n\t");
     	        if(scanf("%d",&Nio)==1){/*Para verificar que solo ingrese el numero y no letras :V*/
     	        	if(Nio>=10&&Nio<=300){
     	         	 printf("\n\t\tCuenta origen\n\t%s",numcuenta);printf("\n\t\tConcepto de debito\n\tRecarga\n");
     	             for(i=0;i<39;i++){printf("*");printf(" ");}
		             printf("\n1>Confirmar\t\t\t\t2>Cancelar\n");scanf("%d",&conf);
				     }else{
				  	clrscr();gotoxy(25,10);printf("\n\t\tError al introducir cantidad");getch();/*Este else es por si realiza una recarga arriba de 100*/
				    }
				 }else{
				 	clrscr();gotoxy(25,10);printf("\n\t\tError dato no valido",163);getch();
				 }
     	         
			 }else{
			 	clrscr();gotoxy(25,10);printf("\n\t\tError al introducir n%cmero",163);getch();/*Por si ingresa menos de 8 numeros 0 mayores*/
			 }
		 }else{
		 	clrscr();gotoxy(25,10);printf("\n\t\tError dato no valido",163);getch();/*Por si introduce letras*/
		 }	
	    }while(!(conf==1||conf==2));
	     if(conf==1){/*Si el usuario confirma sus datos*/
		     clrscr();
		     monto=Nio/34.33;gotoxy(1,10);
		     for(i=0;i<39;i++){printf("*");printf(" ");}
		     printf("\n\t\tCuenta origen\n");
		     for(i=0;i<10;i++){printf("-------");}
		     printf("\n{Alias}\nCuenta de ahorro [USD]\nCuenta\n%s",numcuenta);
		     printf("\nMoto a debitar:USD %.2f",monto);
		     printf("\nTasa de cambio: 34.33");printf("\nFecha y hora  :%s",asctime(timeinfo));gotoxy(1,22);for(i=0;i<39;i++){printf("*"); printf(" ");}getch();
		      cuenta=cuenta-monto;
		    
		    }
		   if(conf==2){/*Si cancela ahi termina el programa*/
		   }
	 }
     if(Ropc==2){
     	do{
     	fflush(stdin);
     	clrscr();
     	for(i=0;i<39;i++){printf("*");printf(" ");}
     	printf("\n\t\tServicio\n\tClaro\n\t\tIngrese el n%cmero\n\t",163);
     	if(scanf("%li",&numero)==1){
     		if(numero>10000000&&numero<99999999){
     			printf("\n\t\tIngrese la cantidad a pagar en NIO\n\t");
     	        if(scanf("%d",&Nio)==1){/*Para verificar que solo ingrese el numero y no letras :V*/
     	        	if(Nio>=10&&Nio<=300){
     	         	 printf("\n\t\tCuenta origen\n\t%s",numcuenta);printf("\n\t\tConcepto de debito\n\tRecarga\n");
     	             for(i=0;i<39;i++){printf("*");printf(" ");}
		             printf("\n1>Confirmar\t\t\t\t2>Cancelar\n");scanf("%d",&conf);
				     }else{
				  	clrscr();gotoxy(25,10);printf("\n\t\tError al introducir cantidad");getch();/*Este else es por si realiza una recarga arriba de 100*/
				    }
				 }else{
				 	clrscr();gotoxy(25,10);printf("\n\t\tError dato no valido",163);getch();
				 }
     	         
			 }else{
			 	clrscr();gotoxy(25,10);printf("\n\t\tError al introducir n%cmero",163);getch();/*Por si ingresa menos de 8 numeros 0 mayores*/
			 }
		 }else{
		 	clrscr();gotoxy(25,10);printf("\n\t\tError dato no valido",163);getch();/*Por si introduce letras*/
		 }	
	    }while(!(conf==1||conf==2));
	    if(conf==1){/*Si el usuario confirma sus datos*/
		     clrscr();
		     monto=Nio/34.33;gotoxy(1,10);
		     for(i=0;i<39;i++){printf("*");printf(" ");}
		     printf("\n\t\tCuenta origen\n");
		     for(i=0;i<10;i++){printf("-------");}
		     printf("\n{Alias}\nCuenta de ahorro [USD]\nCuenta\n%s",numcuenta);
		     printf("\nMoto a debitar:USD %.2f",monto);
		     printf("\nTasa de cambio: 34.33");printf("\nFecha y hora  :%s",asctime(timeinfo));gotoxy(1,22);for(i=0;i<39;i++){printf("*"); printf(" ");}getch();
		      cuenta=cuenta-monto;
		      
		    }
		   if(conf==2){/*Si cancela ahi termina el programa*/
		   }
	 }
	
	}while(!(Ropc==1||Ropc==2));/*Para validar que no ingrese otro numero*/
}

void CAMBIOPIN(char *PIN_USUARIO, char *PIN_1, char *PIN_2, char *PIN_3, char *NEWPIN_USUARIO){
	char caracter;
	int i=0;
	int ingresa=0,intentos=0;
	do{
		i=0;
		clrscr();
		printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
		gotoxy(2,24);
		printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
		gotoxy(5,7);
		printf("\n\n\t\t INGRESE SU CLAVE ACTUAL: ");
		fflush(stdin);
			while(caracter = getch()){
			if(caracter == 13)
			{
				PIN_USUARIO[i]='\0';
				break;

			}else if(caracter==8)
			{
				if(i > 0)
				{
					i--;
					printf("\b \b");
					fflush(stdin);
				}
			}else
			{
				if(i < LONGITUD)
				{
					printf("*");
					fflush(stdin);
					PIN_USUARIO[i]=caracter;
					i++;
				}
			}
		}
		if(strcmp(PIN_1, PIN_USUARIO)==0 || strcmp(PIN_2,PIN_USUARIO)==0 || strcmp(PIN_3,PIN_USUARIO)==0)
		{
			ingresa=1; /*Es verdadero*/
		}else
		{
            clrscr();
			gotoxy(6,12);
			printf("\n\t\t\t\tPIN INCORRECTO!");
			intentos++;
			getchar();
		}
	}while(intentos< 3 && ingresa==0);/* 0 Es falso, el usuario solo tiene 3 intentos*/
	if(ingresa==1)
	{
		/*Primer usuario*/
		if(strcmp(PIN_USUARIO,PIN_1)==0)
		{
			NuevoPIN(NEWPIN_USUARIO,PIN_1);
		}else
		{
			/*Segundo usuario*/
			if(strcmp(PIN_USUARIO,PIN_2)==0)
			{
				NuevoPIN2(NEWPIN_USUARIO,PIN_2);
			}else
			{
				/*Tercer usuario*/
				NuevoPIN3(NEWPIN_USUARIO,PIN_3);
			}
		}
	}else
	{
		clrscr();
		gotoxy(1,13);
		printf("\n\t\tHa excedido el intento maximo de intentos permitidos");
	}
}
/*================================================================================================================================*/
/*Hemos validado en el CAMBIO DE PIN, en donde el usuario debe digitar nada mas numeros, y asi mismo, el PIN debe tener 4 digitos*/
void NuevoPIN(char *NEWPIN_USUARIO, char *PIN_1){
	char caracter;
	int i=0,size;
	go:
		clrscr();
		gotoxy(5,11);
		printf("\n\n\t\t INGRESE SU NUEVO PIN: ");
		fflush(stdin);
		while(caracter = getch()){
		if(caracter == 13)
		{
			NEWPIN_USUARIO[i]='\0';
			break;

		}else if(caracter==8)
		{
			if(i > 0)
			{
				i--;
				printf("\b \b");
				fflush(stdin);
			}
		}else
		{
            if(caracter>=48 && caracter<=57)
            {
                if(i < LONGITUD)
			    {
				    printf("*");
				    fflush(stdin);
				    NEWPIN_USUARIO[i]=caracter;
				    i++;
			    }
            }else
            {
                clrscr();
				gotoxy(6,12);
				printf("\n\t\t\t\tDIGITO UN CARACTER INCORRECTO");
				sleep(3);
				clrscr();
				gotoxy(6,12);
				printf("\n\t\t\t\tPOR FAVOR VUELVA A INTENTARLO");
				sleep(3);
				i=0;
				goto go;
            }
            
		}
	}
        size=strlen(NEWPIN_USUARIO);
		if (size!=4)
		{
			clrscr();
			gotoxy(6,12);
			printf("\n\t\tSU PIN DEBE TENER 4 DIGITOS");
			sleep(3);
			i=0;
			goto go;
		}
		if(strcmp(PIN_1,NEWPIN_USUARIO)==0)
		{
			clrscr();
			gotoxy(14,4);
			printf("\n\t\t\t\t\tERROR\n\t\t\t\tLOS PINES SON IGUALES!");
			i=0;
			goto go;
		}else
		{
            clrscr();
			strcpy(PIN_1,NEWPIN_USUARIO);
			printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
			gotoxy(2,24);
			printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
			gotoxy(15,12);
			printf("\n\t\t\tSu PIN ha sido actualizado!");
			sleep(3);
		}
}
void NuevoPIN2(char *NEWPIN_USUARIO, char *PIN_2){
	char caracter;
	int i=0,size;
	go:
		clrscr();
		gotoxy(5,11);
		printf("\n\n\t\t INGRESE SU NUEVO PIN: ");
		fflush(stdin);
		while(caracter = getch()){
		if(caracter == 13)
		{
			NEWPIN_USUARIO[i]='\0';
			break;

		}else if(caracter==8)
		{
			if(i > 0)
			{
				i--;
				printf("\b \b");
				fflush(stdin);
			}
		}else
		{
            if (caracter>=48 && caracter<=57)
            {
                if(i < LONGITUD)
			    {
				    printf("*");
				    fflush(stdin);
				    NEWPIN_USUARIO[i]=caracter;
				    i++;
			    }
            }else
            {
                clrscr();
				gotoxy(6,12);
				printf("\n\t\t\t\tDIGITO UN CARACTER INCORRECTO");
				sleep(3);
				clrscr();
				gotoxy(6,12);
				printf("\n\t\t\t\tPOR FAVOR VUELVA A INTENTARLO");
				sleep(3);
				i=0;
				goto go;
            }
		}
	}
        size=strlen(NEWPIN_USUARIO);
        if (size!=4)
        {
            clrscr();
			gotoxy(6,12);
			printf("\n\t\tSU PIN DEBE TENER 4 DIGITOS");
			sleep(3);
			i=0;
			goto go;
        }
		if(strcmp(PIN_2,NEWPIN_USUARIO)==0)
		{
			clrscr();
			gotoxy(14,4);
			printf("\n\t\t\t\t\tERROR\n\t\t\t\tLOS PINES SON IGUALES!");
			i=0;
			goto go;
		}else
		{
            clrscr();
			strcpy(PIN_2,NEWPIN_USUARIO);
			printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
			gotoxy(2,24);
			printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
			gotoxy(15,12);
			printf("\n\t\t\tSu PIN ha sido actualizado!");
			sleep(3);
		}
}
void NuevoPIN3(char *NEWPIN_USUARIO, char *PIN_3){
	char caracter;
	int i=0,size;
	go:
		clrscr();
		clrscr();
		gotoxy(5,11);
		printf("\n\n\t\t INGRESE SU NUEVO PIN: ");
		fflush(stdin);
		while(caracter = getch()){
		if(caracter == 13)
		{
			NEWPIN_USUARIO[i]='\0';
			break;

		}else if(caracter==8)
		{
			if(i > 0)
			{
				i--;
				printf("\b \b");
				fflush(stdin);
			}
		}else
		{
            if(caracter>=48 && caracter<=57)
            {
                if(i < LONGITUD)
			    {
				    printf("*");
				    fflush(stdin);
				    NEWPIN_USUARIO[i]=caracter;
				    i++;
			    }
            }else
            {
                clrscr();
				gotoxy(6,12);
				printf("\n\t\t\t\tDIGITO UN CARACTER INCORRECTO");
				sleep(3);
				clrscr();
				gotoxy(6,12);
				printf("\n\t\t\t\tPOR FAVOR VUELVA A INTENTARLO");
				sleep(3);
				i=0;
				goto go;
            }
		}
	}
        size=strlen(NEWPIN_USUARIO);
        if (size!=4)
        {
            clrscr();
			gotoxy(6,12);
			printf("\n\t\tSU PIN DEBE TENER 4 DIGITOS");
			sleep(3);
			i=0;
			goto go;
        }
		if(strcmp(PIN_3,NEWPIN_USUARIO)==0)
		{
			clrscr();
			gotoxy(14,4);
			printf("\n\t\t\t\t\tERROR\n\t\t\t\tLOS PINES SON IGUALES!");
			i=0;
			goto go;
		}else
		{
            clrscr();
			strcpy(PIN_3,NEWPIN_USUARIO);
			printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
			gotoxy(2,24);
			printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
			gotoxy(15,14);
			printf("\n\t\t\tSu PIN ha sido actualizado!");
			sleep(3);
		}
}
/*===================================================================*/
/*Hemos validado la opcion para que el usuario digite otra cantidad,
tomando en cuenta que no puede ingresar letras, numeros negativos, ni decimales(Segun mis consultas en un cajero no puedes depositar una cantidad decimal)
Ademas definimos una cantidad maxima a depositar, que es en cordobas 3000 y dolares 500 :)*/
void deposito(char numcuenta[],char numcard[]){
	/*Mis variables*/
	int opc,dolar,num,size;
	float amount=0, new;
	char respuesta[MAX];
    char numero[2000+1];
	opcion:
	clrscr();
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
	gotoxy(2,24);
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
	gotoxy(2,4);
	printf("\n\t\tSELECCIONE LA MONEDA DEL DEPOSITO A REALIZAR");
	gotoxy(3,8);
	printf("\n\n\n\n\n\t\t1.CORDOBAS\t\t\t2.DOLARES");
	gotoxy(1,21);
	printf("\n\t\tOpcion: [ ]\b\b");
	scanf("%d",&opc);fflush(stdin);
	if(opc==1)
	{
		clrscr();
		printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
		gotoxy(2,24);
		printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
		gotoxy(14,13);
		printf("\t\t\tCargando.");
		sleep(1);
		printf(".");
		sleep(1),
		printf(".");
		sleep(1);
		opciones:
			clrscr();
			gotoxy(17,3);
			printf("\n\tPOR FAVOR INGRESE LA CANTIDAD DE BILLETES QUE DESEA INGRESAR\n\n\t\tINGRESE LOS BILLETES SIN CLIPS NI BANDAS ELASTICAS\n");
			sleep(2);
			gotoxy(4,8);
			printf("\n\n\t\t1<-100\t\t\t\t2<-300\t\t\t\t\n\n\t\t3<-500\t\t\t\t4<-1000\n\n\n\t\t5<-Otra Cantidad");
			printf("\n\n\t\tOpcion: [ ]\b\b");fflush(stdin);
			scanf("%d",&num);fflush(stdin);
			switch(num){
				case 1:
                    NIO=cuenta*34.33;
					cuenta=(NIO+100)/34.33;
					amount=100;
				break;
				case 2:
                    NIO=cuenta*34.33;
					cuenta=(NIO+300)/34.33;
					amount=300;
				break;
				case 3:
                    NIO=cuenta*34.33;
					cuenta=(NIO+500)/34.33;
					amount=500;
				break;
				case 4:
                    NIO=cuenta*34.33;
					cuenta=(NIO+1000)/34.33;
					amount=1000;
				break;
                case 5:
                    do{
						nuevo:
                        clrscr();
                        gotoxy(25,10);
	     		        printf("\n\t\t\tIngrese otra cantidad: \n");printf("\n\t\t\tCantidad: [   ]\b\b");
                        gets(numero);
    	                fflush(stdin);
                        size=validar_num(numero);
                        if(size==0)
		                {
                            new=atoi(numero);
							if (new>3000)
							{
								clrscr();
								gotoxy(5,12);
								printf("\n\t\tNO PUEDE DEPOSITAR UNA CANTIDAD MAXIMA DE C$2000");
								getch();
								goto nuevo;
							}else
							{
								NIO=cuenta*34.33;
                            	cuenta=(NIO+new)/34.33;
                            	amount=new;
							}
		                }else
		                {
			                clrscr();
				            gotoxy(6,12);
				            printf("\n\t\t\tDIGITO UN CARACTER INCORRECTO");
				            getch();
				            clrscr();
				            gotoxy(6,12);
				            printf("\n\t\t\tPOR FAVOR VUELVA A INTENTARLO");
				            getch();
		                }
	                }while(size);
                break;
				default	:
					goto opciones;
			}
	}else
	{
		if(opc==2)
		{
			clrscr();
			printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
			gotoxy(2,24);
			printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
			gotoxy(14,13);
			printf("\t\t\tCargando.");
			sleep(1);
			printf(".");
			sleep(1),
			printf(".");
			sleep(1);
			cantidad:
				clrscr();
				gotoxy(17,3);
				printf("\n\tPOR FAVOR INGRESE LA CANTIDAD DE BILLETES QUE DESEA INGRESAR\n\n\t\tINGRESE LOS BILLETES SIN CLIPS NI BANDAS ELASTICAS\n");
				sleep(2);
				gotoxy(4,8);
				printf("\n\n\t\t1<-20\t\t\t\t2<-40\t\t\t\t\n\n\t\t3<-50\t\t\t\t4<-100\n\n\t\t\t\t5<-Otra Cantidad");
				printf("\n\n\t\tOpcion: [  ]\b\b");fflush(stdin);
				scanf("%d",&dolar);fflush(stdin);
				switch(dolar){
					case 1:
						cuenta+=20;
						amount=20;
					break;
					case 2:
						cuenta+=40;
						amount=40;
					break;
					case 3:
						cuenta+=50;
						amount=50;
					break;
					case 4:
						cuenta+=100;
						amount=100;
					break;
                    case 5:
						valor:
                        do{
                            clrscr();
                            gotoxy(25,10);
	     		            printf("\n\t\t\tIngrese otra cantidad: \n");printf("\n\t\t\tCantidad: [   ]\b\b");
                            gets(numero);
    	                    fflush(stdin);
                            size=validar_num(numero);
                            if(size==0)
		                    {
                                new=atoi(numero);
								if (new>500)
								{
									clrscr();
									gotoxy(5,12);
									printf("\n\t\tNO PUEDE DEPOSITAR UNA CANTIDAD MAXIMA DE $500");
									getch();
									goto valor;
								}else
								{
									cuenta+=new;
                                	amount=new;
								}
		                    }else
		                    {
			                    clrscr();
				                gotoxy(6,12);
				                printf("\n\t\t\tDIGITO UN CARACTER INCORRECTO");
				                getch();
				                clrscr();
				                gotoxy(6,12);
				                printf("\n\t\t\tPOR FAVOR VUELVA A INTENTARLO");
				                getch();
		                    }
	                    }while(size);
                    break;
					default:
						goto cantidad;
				}
		}else
		{
			goto opcion;
		}
	}
	factura(amount,numcuenta,numcard);
    getch();
	arbolito();
}
/*==============================================*/
/*Validamos el ingreso de datos enteros*/
int validar_num(char numero[2000+1]){
	int i=0,j=0,size=0,num=0;
	
	j=strlen(numero);

	for(i=0;i<j;i++){
		if(isdigit(numero[i])!=0)
        {
			num++;
		}else
        {
			size=1;
		}
	}
	return size;
}
/*================================================*/
void factura(float amount,char numcuenta[],char numcard[]){
	/*Variables para mostrar el tiempo real*/
	time_t tiempo_real;
    struct tm * timeinfo;
    time(&tiempo_real);
    timeinfo=localtime(&tiempo_real);
	clrscr();
	gotoxy(17,10);
	printf("\n\t\t\tAGUARDE UN MOMENTO POR FAVOR\n\t\t ESTAMOS PROCESANDO LOS BILLETES INGRESADOS\n");
	sleep(4);
	clrscr();
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\n\t\t\t\tGAMI\n\t\t\tSiempre en servicio\n\t\t\tDinero las 24 horas\n\t\t\t\t\t\tMANAGUA-NICARAGUA\n");
	printf("\nNumero de Tarjeta      : %s",numcard);
	printf("\n\nNumero de Cuenta       : %s",numcuenta);
	printf("\n\nFecha y Hora           : %s",asctime(timeinfo));
    printf("\nMaquina                :GAMI26 MULTI SUC LAS AM");
	printf("\n\nCantidad Ingresada     : %.f",amount);
	printf("\n\nBalance en dolares     : $%.2f",cuenta);
	gotoxy(1,21);
	printf("\n\n\n\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");

}

void servicios(char numcuenta[],char numcard[],float *agua,float *luz){
     /*Mis variables*/
	int opc;
	int comp[1];
    char respuesta[MAX];
    
    /*TIEMPO*/
    time_t tiempo_real;
    struct tm * timeinfo;
    srand(time(NULL));
	time(&tiempo_real);
    timeinfo=localtime(&tiempo_real);
    
    /*Aleatorio*/
    /*ale[i]=comp[i];
	for(i=0;i<1;i++){
	ale[i]=1000+rand()%(2000-1000+1);
	comp[i]=ale[i];
	}*/
    NIO=cuenta*34.33;

    two:
    clrscr();
	gotoxy(10,1);
	printf("\n\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    gotoxy(5,23);
	printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
	gotoxy(18,5);
	printf("SELECCIONE EL SERVICIO QUE DESEE PAGAR\n");
	printf("\n\n\n\n\n\n\t\t1.Agua\t\t\t\t2.Luz");
    gotoxy(1,22);
	printf("\n\t\tOpcion: [ ]\b\b");fflush(stdin);
	scanf("%d",&opc);
	if (opc==1)
    {
		if (*agua==0)
		{
			clrscr();
			gotoxy(10,13);
			printf("\n\t\tUSTED A REALIZADO EL PAGO DE ESTE MES");
			getch();
		}else
		{
			if (NIO<*agua)
			{
				clrscr();
				gotoxy(10,13);
				printf("\n\tUSTED NO CUENTA CON SALDO SUFICIENTE PARA REALIZAR EL PAGO");
			    getch();
			}else
			{
				cuenta=(NIO-*agua)/34.33;
        		clrscr();
				printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
				gotoxy(2,24);
				printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
				gotoxy(14,13);
				printf("\t\tEspere un momento.");
				sleep(1);
				printf(".");
				sleep(1);
				printf(".");
				sleep(1);
				clrscr();

				printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
				printf("\n\t\t\t\tGAMI\n\t\t\tSiempre en servicio\n\t\t\tDinero las 24 horas\n\t\t\t\t\t\tMANAGUA-NICARAGUA\n");
				printf("\nNumero de Tarjeta      : %s",numcard);
				printf("\n\nNumero de Cuenta       : %s",numcuenta);
				printf("\n\nFecha y Hora           : %s",asctime(timeinfo));
				printf("\nMaquina                :GAMI26 MULTI SUC LAS AM");
   				printf("\n\nCantidad a Pagar       : C$%f",*agua);
				printf("\n\nBalance en dolares     : $%.2f",cuenta);
				gotoxy(1,21);
				printf("\n\n\n\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
				*agua=0;
				getch();
				arbolito();
			}
		}
	}else
    {
        if (opc==2)
        {
			if (*luz==0)
			{
				clrscr();
				gotoxy(10,13);
				printf("\n\t\tUSTED A REALIZADO EL PAGO DE ESTE MES");
				getch();
			}else
			{
				if (NIO<*luz)
				{
					clrscr();
					gotoxy(10,13);
					printf("\n\tUSTED NO CUENTA CON SALDO SUFICIENTE PARA REALIZAR EL PAGO");
					getch();
				}else
				{
					cuenta=(NIO-*luz)/34.33;
            		clrscr();
		    		printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
		    		gotoxy(2,24);
		   	 		printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
		    		gotoxy(14,13);
		    		printf("\t\tEspere un momento.");
		    		sleep(1);
		    		printf(".");
		    		sleep(1);
		    		printf(".");
		    		sleep(1);
		    		clrscr();
		    		gotoxy(12,1);

					printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
					printf("\n\t\t\t\tGAMI\n\t\t\tSiempre en servicio\n\t\t\tDinero las 24 horas\n\t\t\t\t\t\tMANAGUA-NICARAGUA\n");
					printf("\nNumero de Tarjeta      : %s",numcard);
					printf("\n\nNumero de Cuenta       : %s",numcuenta);
					printf("\n\nFecha y Hora           : %s",asctime(timeinfo));
					printf("\nMaquina                :GAMI26 MULTI SUC LAS AM");
   					printf("\n\nCantidad a Pagar       : C$%f",*luz);
					printf("\n\nBalance en dolares     : $%.2f",cuenta);
					gotoxy(1,21);
					printf("\n\n\n\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
					*luz=0;
					getch();
					arbolito();
				}
			}
		}else
        {
            goto two;
        }
    }
}

void arbolito(){/*Esta funcion es la oficial para poner el arbolito y simular imprimir el recivo*/
int i=0,recivo=0,colu=0,filas=0,unitario=0;
clrscr();fflush(stdin);clrscr();fflush(stdin);
do{
clrscr();
printf("\n\t\t\tAyudenos a salvar un arbol\n");
colu= 1; while (colu <= 12){unitario = 12;filas = 1; printf(" ");while (unitario>colu){printf(" ");unitario--;}
while (filas <= colu){printf("**");filas++;}printf("\n");colu++;}printf("            *");
gotoxy(25,16);printf("\n\t\t\tDesea imprimir recivo?\n\n\n1>Si\n\n\n2>No\n");scanf("%d",&recivo);
fflush(stdin);
if(recivo==1){clrscr();for(i=0;i<39;i++){printf("*");printf(" ");}gotoxy(25,10);printf("\n\t\t\tPresione ENTER para retirar su tarjeta\n");
gotoxy(1,25);for(i=0;i<39;i++){printf("*");printf(" ");}getch();clrscr();for(i=0;i<39;i++){printf("*");printf(" ");}
gotoxy(25,10);printf("\n\t\t\tRetire su recivo\n");gotoxy(1,25);for(i=0;i<39;i++){printf("*");printf(" ");}sleep(2);
clrscr();for(i=0;i<39;i++){printf("*");printf(" ");}
gotoxy(25,10);printf("\n\t\t\tGracias por preferirnos\n\n\t\t\t Pase un buen dia\n");gotoxy(1,25);for(i=0;i<39;i++){printf("*");printf(" ");}
sleep(2);clrscr();}
if(recivo==2){clrscr();for(i=0;i<39;i++){printf("*");printf(" ");}gotoxy(25,10);printf("\n\t\t\tPresione ENTER para retirar su tarjeta\n");
gotoxy(1,25);for(i=0;i<39;i++){printf("*");printf(" ");}getch();clrscr();
for(i=0;i<39;i++){printf("*");printf(" ");}clrscr();for(i=0;i<39;i++){printf("*");printf(" ");} gotoxy(25,10);printf("\n\t\t\tGracias por preferirnos\n\n\t\t\t Pase un buen dia\n");
gotoxy(1,25);for(i=0;i<39;i++){printf("*");printf(" ");}sleep(2);clrscr();}
 }while(!(recivo==1||recivo==2));getch();
}

void Aux_transferencia(char  numcard[]){
	long int banco_cuenta=0;
	float amount;
	int i=0,coin=0,conf=0;
	time_t tiempo_real;
    struct tm * timeinfo;
    clrscr();
    time(&tiempo_real);
    timeinfo=localtime(&tiempo_real);
	fflush(stdin);clrscr();
	
	do{/*Este do para validar que solo sea 1 y 2 los ingresados en la moneda*/
	 fflush(stdin);
	 clrscr();
	 gotoxy(25,10);
	 printf("\n\t\tIngrese la moneda en que desee transferir");
	 printf("\n\n\n\t\t\t\t\t\t1>Dolares\n\n\n");
   	 printf("\n\t\t\t\t\t\t2>Cordobas\n\n\n");
	 fflush(stdin);
	 scanf("%d",&coin);
	 switch(coin){
		case 1:
			do{
			fflush(stdin);
			clrscr();
			printf("\nDigite el numero de cuenta al que desea transferir\n");
			if(scanf("%li",&banco_cuenta)==1){
				if(banco_cuenta>100000000&&banco_cuenta<999999999){
					printf("Digite la cantidad que desea transferir\n");
					if(scanf("%f",&amount)==1&&amount>=1){
						if(amount<=cuenta){
							printf("\n1>Confirmar\t\t\t\t2>Cancelar\n");scanf("%d",&conf);/*Aqui si pone 1 o 2 lo saca del while*/
						}else{
							clrscr();gotoxy(25,10);printf("\n\t\tNo cuenta con suficiente dinero\n\t\tpara realizar esta transferencia");getch();/*Por si introduce letras*/
						}
					}else{
						clrscr();gotoxy(25,10);printf("\n\t\tError dato no valido");getch();/*Por si introduce letras*/
					}
				}else{
			 	clrscr();gotoxy(25,10);printf("\n\t\tError al introducir n%cmero",163);getch();/*Por si ingresa menos de 8 numeros 0 mayores*/
			      }	
				}else{
		 	clrscr();gotoxy(25,10);printf("\n\t\tError dato no valido");getch();/*Por si introduce letras*/
		    }		
			}while(!(conf==1||conf==2));
			if(conf==1){
                clrscr();
	            fflush(stdin);
	   	        for(i=0;i<39;i++){printf("*");printf(" ");}
	        	fflush(stdin);
	            printf("\n\t\t\t\tGAMI\n\t\t\tSiempre en servicio\n\t\t\tDinero las 24 horas\n\t\t\t\t\t\tMANAGUA-NICARAGUA\n");
                printf("\n\nNumero de tarjeta:%s",numcard);
	            printf("\n\nBeneficiario     :%li",banco_cuenta);
	            printf("\n\nFecha y hora     :%s ",asctime(timeinfo));
		        printf("\n\nTransferencia    :%.2f",amount);
		        printf("\n\nBalance          :%.2f",cuenta-=amount);
                printf("\n\nMaquina          :GAMI26 MULTI SUC LAS AM");
	            fflush(stdin);
	         	gotoxy(1,25);
                for(i=0;i<39;i++){printf("*");printf(" ");}getch();
				}
				if(conf==2){/*Se cancela ahi termina el programa*/
				}
				break;
    case 2:
    	do{
    		fflush(stdin);
    		clrscr();
			printf("\nDigite el numero de cuenta al que desea transferir\n");
			if(scanf("%li",&banco_cuenta)==1){
				if(banco_cuenta>100000000&&banco_cuenta<999999999){
					printf("\nDigite la cantidad que desea transferir\n");
					if(scanf("%f",&amount)==1&&amount>=1){
						if(amount<=cuenta*34.33){
							printf("\n1>Confirmar\t\t\t\t2>Cancelar\n");scanf("%d",&conf);/*Aqui si pone 1 o 2 lo saca del while*/
						}else{
							clrscr();gotoxy(25,10);printf("\n\t\tNo cuenta con suficiente dinero\n\t\tpara realizar esta transferencia");getch();/*Por si introduce letras*/
						}
					}else{
						clrscr();gotoxy(25,10);printf("\n\t\tError dato no valido");getch();/*Por si introduce letras*/
					}
				}else{
			 	clrscr();gotoxy(25,10);printf("\n\t\tError al introducir n%cmero",163);getch();/*Por si ingresa menos de 8 numeros 0 mayores*/
			      }	
				}else{
		 	clrscr();gotoxy(25,10);printf("\n\t\tError dato no valido");getch();/*Por si introduce letras*/
		    }		
			}while(!(conf==1||conf==2));
			if(conf==1){
                clrscr();
	            fflush(stdin);
	   	        for(i=0;i<39;i++){printf("*");printf(" ");}
	        	fflush(stdin);
	            printf("\n\t\t\t\tGAMI\n\t\t\tSiempre en servicio\n\t\t\tDinero las 24 horas\n\t\t\t\t\t\tMANAGUA-NICARAGUA\n");
                printf("\n\nNumero de tarjeta: %s", numcard);
	            printf("\n\nBeneficiario     : %li",banco_cuenta);
	            printf("\n\nFecha y hora     : %s ",asctime(timeinfo));
		        printf("\n\nTransferencia    :%.2f",amount);
		        printf("\n\nBalance          :%.2f",cuenta=cuenta*34.33-amount);
                printf("\n\nMaquina          :GAMI26 MULTI SUC LAS AM");
	            fflush(stdin);
	            cuenta=cuenta/34.33;
	         	gotoxy(1,25);
                for(i=0;i<39;i++){printf("*");printf(" ");}getch();
				}
				if(conf==2){/*Se cancela ahi termina el programa*/
				}
				break;
	}	
	}while(!(coin==1||coin==2));
	
}

void consulta(){
	int opcion=0,i=0;
	NIO=cuenta*34.33;
	do{
	 fflush(stdin);
	 clrscr();
	 gotoxy(25,10);
     printf("\n\t\tSeleccione la moneda en que  desea ver su saldo\n");
	 printf("\n\n\n\t\t\t\t\t\t1>Dolares\n\n\n");
   	 printf("\n\t\t\t\t\t\t2>Cordobas\n\n\n");
     scanf("%d",&opcion);
     if(opcion==1){
     	 clrscr();
	     fflush(stdin);
	     gotoxy(25,10);printf("Su saldo es:%.2f",cuenta);getch();clrscr();
	 }
	 if(opcion==2){
	 	 clrscr();
	     fflush(stdin);
	     gotoxy(25,10);printf("Su saldo es:%.2f",NIO);getch();clrscr();
	 }
	}while(!(opcion==1||opcion==2));
	getch();
}
