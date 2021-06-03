/*---- Registro Academico ---- created by Gabriel Ortiz ---- version A3.3g ---- tested by Luis Pineda and Engel Reyes*/
/*--------1----------------------- Library --------------------------------*/
#include "covpagbv.h"

/*--------M----------------------- Constant -------------------------------*/
#define cursor 16/*      | S Y M B O L S                                     */
#define cursor2 26/*     |                                                   */

#define MaxAccounts 5/*  | L I M I T S                                       */
#define MaxStds 10/*     |                                                   */
/*--------1----------------------- Structs --------------------------------*/

typedef struct Account
{
    char user[MaxStrLn], password[MaxStrLn];
} account;

typedef struct Class
{
    char *nameClass;
    int nota, _isActive;
} class;

typedef struct Student
{
    int ID_student;
    char name[MaxStrLn], lastname[MaxStrLn], carnet[MaxStrLn];
    class class[9];
} student;

typedef struct Classroom
{
    int ID;
    student student[MaxStds];
} classroom;

struct Configuration
{
    int semester,ID_database,searchOption;
} configuration;
/*-------------------------------- Prototyping ----------------------------*/
void MenuDesigner(void);/*              |                                    */
void LoginAndRegisterDesigner(void);/*  |                                    */
void RegisterDesigner(void);/*          |- Designers (single execution)      */
void SearchDesigner(void);/*            |                                    */
void ShowDatabaseDesigner(void);/*      |                                    */

void Menu(void);/*                      |                                    */
void More(void);/*                      |                                    */
void Login(void);/*                     |                                    */
void LoginAndRegister(void);/*          |                                    */
void Add(void);/*                       |                                    */
void Register(void);/*                  |- Buttons (cicles funtions)         */
void Search(void);/*                    |                                    */
void ShowDatabase(void);/*              |                                    */
void editStudent(int ID);/*             |                                    */
void about(void);/*                     |                                    */

void clearscreen(void);/*               |                                    */
void addFramework(void);/*              |                                    */
void clearwindow(char window);/*        |                                    */
void loadStudentData(student* student);/*|- Funtions                          */
void save(void);/*                      |                                    */
void load(void);/*                      |                                    */
void saveConfiguration(void);/*         |                                    */
void loadConfiguration(void);/*         |                                    */
/*-------------------------------- Global var -----------------------------*/
account user;
classroom database[4];
char *lessons[2][5]={{"Introduccion a la computacion","Ingles","Filosofia","Geometria Analitica"," "},
{"Lenguaje de Programacion","Conceptos de Lenguaje","Matematicas I","Ingles II","Redaccion Tecnica"}};
char *searchMethod[3]={"Nombre","Apellido","Carnet"};
char *cleaner[] = {"                     ","          ","    ","    ","    ","    ","    ","    ","    ","    ","    "};
char key;
char *groupInformation[]=       {"Elija con cual de los ","grupos desea trabajar.","                      ","Tome en cuenta   ","que cada grupo es     ","independiente uno del ","otro.                 "};
char *semesterInformation[]=    {"Cambie el semestre en ","el cual se encuentre. ","                      ","Dependiendo de   ","cual se elija se veran","las clases de ese     ","semestre.             "};
char *aboutInformation[]=       {"Creditos e informacion","de los desarrolladores","del programa Registro ","Academico,       ","compilado en Turbo C  ","y realizado para el SO","de MS - DOS.          "};
char *closeSessionInformation[]={"Cierra la cuenta en la","que se encuentra, tome","                      ","Se pediran las   ","credenciales otra vez.","                      ","                      "};
char *registerInformation[]=    {"Registre una cuenta   ","nueva, se le pedira un","usuario y password el ","cual debe guardar","Las mayusculas se toma","en cuenta a la hora de","guardar los datos."    };
char *exitInformation[]=        {"Se terminara          ","la ejecucion del      ","programa.             ","                 ","                      ","                      ","                      "};
char *searchMethodInformation[]={"Elija el parametro con","el que desea buscar al","estudiante.           "};
char *getStringInformation[]=   {"Ingrese el            ","del estudiante que    ","desea buscar.         "};
char *searchInformation[]=      {"Presione enter para   ","buscar al estudiante  ","                      "};
char *nameInformation[] =       {"Debe ingresar el      ","nombre del estudiante ","que desea agregar.    ","                 ","(Maximo 10 caracteres)"};
char *lastNameInformation[] =   {"Digite el apellido    ","del estudiante que    ","desea agregar.        ","                 ","(Maximo 10 caracteres)"};
char *carnetInformation[]=      {"Digite un numero de   ","carnet, recuerde que  ","los primeros 4 digitos","corresponden a la","fecha anual.          "};
char *classInformation[]=       {"Inscriba las clases   ","que el alumno llevara ","Para desinscribir una ","clase, debe dejar","vacia la nota.        "};
char *cancelInformation[]=      {"No se guardara ningun ","cambio realizado en el","estudiante            ","                 ","                      "};
char *deleteInformation[]=      {"El alumno se eliminara","del registro academico","de la UNI.            ","Los datos se     ","perderan.             "};
char *updateInformation[]=      {"Se guardaran los      ","cambios realizados en ","el alumno, los datos  ","anteriores se    ","perderan              "};
char *addInformation[]=         {"Se agregara este      ","alumno al registro    ","academico de la UNI   ","                 ","Revise la informacion "};
char *enableClass[] =           {"Esta clase no necesita","de una clase previa   ","                      ","El alumno puede  ","llevar esta clase.    "};
char *disabledClass0[] =        {"Esta clase requiere   ","que el estudiante haya","recibido la clase de  ","Introduccion a la","Computacion.          "};
char *disabledClass1[] =        {"Esta clase requiere   ","que el estudiante haya","aprobado la clase de  ","Introduccion a la","Computacion.          "};
char *disabledClass2[] =        {"Esta clase requiere   ","que el estudiante haya","aprobado la clase de  ","Ingles I         ","                      "};
int loginCount=0, accountCount=0, screen, option, suboption, i,j;
/*-------------------------------- Initializer -----------------------------*/
void main()
{   
    InitializeComponent();
    load();
    loadConfiguration();
    MenuDesigner();
    addFramework();
    Login();
    Menu();
}
/*--------------------------------- Designers ------------------------------*/
void RegisterDesigner(void)
{
    MessageBox();
    textbackground(BLUE);
    textcolor(WHITE);
    gotoxy(31,7);   
    cprintf(" Registrar cuenta ");
    Register();
}
void LoginAndRegisterDesigner(void)
{
    option = 0;
    MessageBox();
    textbackground(BLUE);
    textcolor(WHITE);
    gotoxy(30,7); cprintf(" Registro Academico ");
    LoginAndRegister();
    addFramework();
    clearwindow('a');
}
void MenuDesigner(void)
{
    textbackground(BLUE);
    clrscr();
    textcolor(WHITE);
    gotoxy(2,25);
    cprintf("Esc - Salir   Enter - Ir   %c%c - Desplazarse",24,25);

    clearscreen();
    for(i=1;i<=80;i++)
    {
        textbackground(CYAN);
        gotoxy(i,1);
        cprintf("%c",0);
    }
    textcolor(BLACK);
    gotoxy(26,1);
    cprintf("REGISTRO ACADEMICO DE LA UNI");
}
void ShowDatabaseDesigner(void)
{
    char *titles[2][7]={
        {"Nombre & Apellido","Carnet",  "IICC",     "Ingles",  "Filosofia",     "Geometria",    ""},
        {"Nombre & Apellido","Carnet",  "LLPP",     "CCLL",    "Mat.I",         "InglesII",     "Redaccion"}};

    int k=0;
    option=0;

    textcolor(BLACK);
    if(configuration.semester==0)
        for(j=3;j<=24;j++)
            for(i=1;i<=80;i++)
            {
                gotoxy(i,j);
                if( (j==3||j==5||j==24) && i>=1 && i<=80)
                    cprintf("%c",lineaH);
                else if( (i==1||i==23||i==34||i==45||i==56||i==68||i==80) && j<=24 && j>=3)
                    cprintf("%c",lineaV);

                
                gotoxy(i,j);
                if((j==3||j==5||j==24) && (i==1||i==23||i==34||i==45||i==56||i==68||i==80))
                    cprintf("%c", j==3? i==1?esquinaNW: i==80?esquinaNE: cruceWES : j==5? i==1? cruceNSW: i==80?cruceNSE: cruceNSWE : i==1? esquinaSW: i==80?esquinaSE: cruceNWE);
                
                if( (j==4) && (i==4||i==26||i==38||i==48||i==58||i==70) )
                {
                    cprintf("%s",titles[configuration.semester][k]);
                    k++;
                }
            }
    else
        for(j=3;j<=24;j++)
            for(i=1;i<=80;i++)
            {
                gotoxy(i,j);
                if( (j==3||j==5||j==24) && i>=1 && i<=80)
                    cprintf("%c",lineaH);
                else if( (i==1||i==23||i==34||i==43||i==52||i==61||i==70||i==80) && j<=24 && j>=3)
                    cprintf("%c",lineaV);

                
                gotoxy(i,j);
                if((j==3||j==5||j==24) && (i==1||i==23||i==34||i==43||i==52||i==61||i==70||i==80))
                    cprintf("%c", j==3? i==1?esquinaNW: i==80?esquinaNE: cruceWES : j==5? i==1? cruceNSW: i==80?cruceNSE: cruceNSWE : i==1? esquinaSW: i==80?esquinaSE: cruceNWE);
                
                if( (j==4) && (i==4||i==26||i==37||i==46||i==54||i==62||i==71) )
                {
                    cprintf("%s",titles[configuration.semester][k]);
                    k++;
                }
            }
}
void SearchDesigner(void)
{
    char * titles[3][11]={{" "," ","Intr","Geo ","Filo","In- ","Leng","Cpto","Mat.","Re  ","In- "},
     {"Nombre & Apellido","Carnet","a la","me  ","so ","gles" ,"de  ","de  ","I   ","dac ","gles"},
                        {"\0","\0","comp","tria","fia ","\0"  ,"prog","leng","\0"  ,"cion","In- "}};
    int k=0;

    textcolor(BLACK);
    for(j=3;j<=24;j++)
        for(i=1;i<=80;i++)
        {
            gotoxy(i,j);
            if( (j==12||j==16||j==24) && i>=1 && i<=80)
                cprintf("%c",lineaH);
            else if( (i==1||i==23||i==34||i==39||i==44||i==49||i==54||i==55||i==60||i==65||i==70||i==75||i==80) && j<=24 && j>=12)
                cprintf("%c",lineaV);

            gotoxy(i,j);
            if( (j==3||j==11) && i>=1 && i<=80 )
                cprintf("%c",lineaH);
            else if( (i==1 || i==57 ||i==80) && j<=11 && j>=3 )
                cprintf("%c",lineaV);

            gotoxy(i,j);
            if( (j==3||j==11) && (i==1 || i==57 || i==80))
                if(j==3)
                    cprintf("%c",i==1?esquinaNW: i==57?cruceWES:esquinaNE);
                else if(j==11)
                    cprintf("%c",i==1?esquinaSW: i==57?cruceNWE:esquinaSE);

            gotoxy(i,j);
            if((j==12||j==16||j==24) && (i==1||i==23||i==34||i==39||i==44||i==49||i==54||i==55||i==60||i==65||i==70||i==75||i==80))
                cprintf("%c", j==12? i==1?esquinaNW: i==80?esquinaNE: cruceWES : j==16? i==1? cruceNSW: i==80?cruceNSE: cruceNSWE : i==1? esquinaSW: i==80?esquinaSE: cruceNWE);

            if((j>=13&&j<=15) && (i==4||i==26||i==35||i==40||i==45||i==50||i==56||i==61||i==66||i==71||i==76))
            {
                gotoxy(i,j);
                cprintf("%s",titles[j-13][k]);
                k = k==10 ? 0 : k+1;
            } 
        }

    gotoxy(35,5);
    cprintf("[  %s  ]",searchMethod[configuration.searchOption]);
    gotoxy(34,7);
    cprintf("[              ]");
    Search();
}
/*--------------------------------- Buttons  -------------------------------*/
void ShowDatabase(void)
{
    int PositionX[2][7] = {
        {2,24,38,49,60,72,0},
        {2,24,37,46,55,64,73}};
    int ID;
    
    for(i=0;i<database[configuration.ID_database].ID;i++)
        for(j=0;configuration.semester==0?j<6:j<7;j++)
        {
            gotoxy( PositionX[configuration.semester][j] , i+6);
            
            if(option==i)
                textcolor(BLUE);
            else
                textcolor(BLACK);

            switch(j)
            {
                case 0:
                    cprintf("%s %s",database[configuration.ID_database].student[i].name, database[configuration.ID_database].student[i].lastname);
                    break;

                case 1:
                    cprintf("%s",database[configuration.ID_database].student[i].carnet);
                    break;

                default:
                    if(database[configuration.ID_database].student[i].class[ (configuration.semester==0?j:j+4) -2]._isActive == true)
                    {
                        if(database[configuration.ID_database].student[i].class[ (configuration.semester==0?j:j+4) -2].nota>=60)
                            textcolor(GREEN);
                        else
                            textcolor(RED);
                        cprintf("%d",database[configuration.ID_database].student[i].class[ (configuration.semester==0?j:j+4) -2].nota);
                    }
                    else
                        cprintf(" n/a ");

                    break;
            }
        }

    RemoveCursor(3,4);
    do
        key=getch();
    while(key!=up && key!=down && key!=enter && key!=esc && key!=tab);

    if(key==up)
        option = option==0 ? 0 : option - 1;

    else if(key==down)
        option = option==database[configuration.ID_database].ID-1 ? database[configuration.ID_database].ID-1 : option + 1;

    else if(key==enter)
    {
        ID = option;
        option = 0;
        editStudent(ID);
        return;
    }
    else if(key==esc || key==tab)
    {
        for(j=0;configuration.semester==0?j<6:j<7;j++)
        {   
            gotoxy( PositionX[configuration.semester][j] , option+6);
            textcolor(BLACK);
            switch(j)
            {
                case 0:
                    cprintf("%s %s",database[configuration.ID_database].student[option].name, database[configuration.ID_database].student[option].lastname);
                    break;
                case 1:
                    cprintf("%s",database[configuration.ID_database].student[option].carnet);
                    break;
                default:
                    if(database[configuration.ID_database].student[option].class[ (configuration.semester==0?j:j+4) -2]._isActive == true)
                    {
                        if(database[configuration.ID_database].student[option].class[ (configuration.semester==0?j:j+4) -2].nota>=60)
                            textcolor(GREEN);
                        else
                            textcolor(RED);
                        cprintf("%d",database[configuration.ID_database].student[option].class[ (configuration.semester==0?j:j+4) -2].nota);
                    }
                    else
                        cprintf(" n/a ");

                    break;
            }
        }
        return;
    }    
    ShowDatabase();
}
void Search(void)
{
    char *commands[] = {"Metodo de busqueda","Ingrese el","Buscar"};
    int PositionX[11] = {2,24,35,40,45,50,56,61,66,71,76};
    int positionY=0;
    student student;

    student.carnet[0]='\0';
    student.name[0]='\0';
    student.lastname[0]='\0';

    textcolor(BLACK);
    gotoxy(63,4);
    cprintf("INFORMACION");

    do
    {
        for(i=0;i<3;i++)
        {
            if(i==option)
                textcolor(BLUE);
            else
                textcolor(BLACK);
            
            gotoxy(4,(i*2)+5);
            cprintf("%c %s %s    ", i==option?cursor:0 , commands[i], i==1?searchMethod[configuration.searchOption]:" ");

            textcolor(BLACK);
            gotoxy(58,6+i);
            cprintf("%s", option==0?searchMethodInformation[i]: option==1?getStringInformation[i]: searchInformation[i]);   
        }

        RemoveCursor(3,4);
        do
            key = getch();
        while(key!=enter&&key!=up&&key!=down&&key!=tab&&key!=esc);

        if(key==up)
            option = option==0 ? 2 : option - 1;
        else if(key==down)
            option = option==2 ? 0 : option + 1;
        else if(key==tab || key == esc)
        {
            gotoxy(4,(option*2)+5);
            textcolor(BLACK);
            cprintf("%c %s",0,commands[option]);
            return;
        }
        else if(key==enter)
            switch(option)
            {
                case 0:
                    do
                    {
                        textcolor(BLUE);
                        gotoxy(35,5);
                        cprintf("[  %s  ]    ",searchMethod[configuration.searchOption]);

                        RemoveCursor(4,4);
                        do
                            key = getch();
                        while(key!=up&&key!=down&&key!=enter&&key!=esc&&key!=tab);

                        if(key==up)
                            configuration.searchOption = configuration.searchOption==0 ? 2 : configuration.searchOption-1;
                        else if(key==down)
                            configuration.searchOption = configuration.searchOption==2 ? 0 : configuration.searchOption+1;
                    }
                    while(key!=enter&&key!=esc&&key!=tab);
                    saveConfiguration();
                    key=NULL;
                    gotoxy(37,7);
                    cprintf("          ");
                    textcolor(BLACK);
                    gotoxy(35,5);
                    cprintf("[  %s  ]",searchMethod[configuration.searchOption]);
                    break;
                case 1:
                    gotoxy(37,7);
                    cprintf("          ");
                    textcolor(BLUE);
                    if(configuration.searchOption==0)
                        getString(37,7,false,student.name);
                    else if(configuration.searchOption==1)
                        getString(37,7,false,student.lastname);
                    else if(configuration.searchOption==2)
                        getCarnet(37,7,student.carnet);
                    textcolor(BLACK);
                    gotoxy(37,7);
                    cprintf("%s", configuration.searchOption==2 ? student.carnet : configuration.searchOption==1? student.lastname : student.name);
                    key=NULL;
                    break;
                case 2:
                    textcolor(BLACK);
                    positionY=0;
                    for(i=0;i<=6;i++)
                        for(j=0;j<11;j++)
                        {
                            gotoxy(PositionX[j],i+17);
                            cprintf("%s",cleaner[j]);
                        }
                    
                    for(i=0;i<database[configuration.ID_database].ID;i++)
                        if(strcmp(database[configuration.ID_database].student[i].name,student.name)==0 || strcmp(database[configuration.ID_database].student[i].lastname,student.lastname)==0 || strcmp(database[configuration.ID_database].student[i].carnet,student.carnet)==0)
                        {
                            for(j=0;j<11;j++)
                            {
                                gotoxy( PositionX[j] , positionY+17);
                                
                                switch(j)
                                {
                                    case 0:
                                        textcolor(BLACK);
                                        cprintf("%s %s",database[configuration.ID_database].student[i].name, database[configuration.ID_database].student[i].lastname);
                                        break;
                                    case 1:
                                        textcolor(BLACK);
                                        cprintf("%s",database[configuration.ID_database].student[i].carnet);
                                        break;
                                    default:
                                        if(database[configuration.ID_database].student[i].class[j-2]._isActive == true)
                                        {
                                            if(database[configuration.ID_database].student[i].class[j-2].nota>=60)
                                                textcolor(GREEN);
                                            else
                                                textcolor(RED);
                                            cprintf("%d",database[configuration.ID_database].student[i].class[j-2].nota);
                                        }
                                        else
                                        {
                                            textcolor(BLACK);
                                            cprintf(" - ");
                                        }
                                        break;
                                }
                            }
                            positionY++;
                            if(positionY>6)
                                break;
                        }
                    
                    if(positionY==0)
                    {
                        gotoxy(60,9); cprintf("No se ha encontrado");
                        gotoxy(60,10); cprintf("ese registro");
                    }
                    else
                    {
                        gotoxy(60,9); cprintf("                   ");
                        gotoxy(60,10); cprintf("                   ");
                    }
                    
                    student.carnet[0]='\0';
                    student.name[0]='\0';
                    student.lastname[0]='\0';
                    gotoxy(37,7);
                    cprintf("          ");
                    key=NULL;
                    break;
                default:
                    FatalError();
                    break;
            }
    }
    while(key!=enter&&key!=tab&&key!=esc);
}
void Login(void)
{
    FILE * file;
    account temporaryAccount,validAccount;
    
    MessageBox();
    textbackground(BLUE);
    textcolor(WHITE);

    gotoxy(23,16);
    if(loginCount==0)
        cprintf("                                 ");

    else if(loginCount==1)
        cprintf("Incorrecto, intente nuevamente...");

    else if(loginCount==2)
        cprintf("Incorrecto, intente por ultima vez");

    else if(loginCount==3)
        exit(0);
    
    gotoxy(32,7); cprintf(" Inicio de Sesion ");
    gotoxy(24,10); cprintf("Usuario:                 ");
    gotoxy(24,14); cprintf("Contrase%ca:                 ",enye);
    getString(24+9,10,false,temporaryAccount.user);
    getString(24+12,14,true,temporaryAccount.password);

    file = fopen("Accounts.txt","r");
    if(file==NULL)
    {
        strcpy(validAccount.user,"admin");
        strcpy(validAccount.password,"admin");
        file = fopen("Accounts.txt","w");
        fwrite(&validAccount,sizeof(account),1,file);
        fclose(file);
        file = fopen("Accounts.txt","r");
    }
    while(!feof(file))
    {
        fread(&validAccount,sizeof(validAccount),1,file);
        if(strcmp(validAccount.user,temporaryAccount.user)==0 && strcmp(validAccount.password,temporaryAccount.password)==0)
        {
            textcolor(WHITE);
            gotoxy(2,25);
            cprintf("Esc - Atras   Enter - Ir   %c%c - Desplazarse   Tab - Siguiente pesta%ca",24,25,enye);
            user = temporaryAccount;
            textcolor(LIGHTGRAY);
            gotoxy(60,2); cprintf("                   ");
            gotoxy(60,2); cprintf("Usuario: %s",user.user);
            clearwindow('a');
            addFramework();
            about();
            return;
        }
    }
    fclose(file);

    loginCount++;
    Login();
}
void Register(void)
{   
    char *commands[]={"Usuario","Password","Cancelar","Registrar"};
    FILE * file;
    account newAccount, registeredAccount;
    int isAvailable=false;

    newAccount.user[0]='\0';
    newAccount.password[0]='\0';
    option = 0;

    do
    {
        for(i=0;i<4;i++)
        {
            if(i==option)
                textbackground(BLACK);
            else
                textbackground(BLUE);

            textcolor(WHITE);
            gotoxy(24,(i*2)+10);
            cprintf("%s",commands[i]);
        }

        RemoveCursor(3,4);
        do
            key=getch();
        while(key!=up&&key!=down&&key!=esc&&key!=enter);

        textcolor(WHITE);
        if(key==up)
            option = option==0 ? 3 : option - 1;
        else if(key==down)
            option = option==3 ? 0 : option + 1;
        else if(key==esc)
        {
            clearwindow('a');
            addFramework();
            return;
        }
        else if(key==enter)
            switch(option)
            {
                case 0:
                    isAvailable=true;
                    gotoxy(32,10); cprintf("          ");
                    getString(32,10,false,newAccount.user);
                    file = fopen("Accounts.txt","a++");
                    if(file==NULL)
                    {
                        gotoxy(26,18);
                        cprintf("No se ha podido abrir el fichero");
                        RemoveCursor(4,4);
                        getch();
                        clearscreen();
                        addFramework();
                        return;
                    }
                    while(!feof(file))
                    {
                        fread(&registeredAccount,sizeof(registeredAccount),1,file);
                        if(strcmp(registeredAccount.user,newAccount.user)==0)
                        {
                            isAvailable=false;
                            textcolor(LIGHTRED);
                            gotoxy(32,10); cprintf("%s",newAccount.user);
                            RemoveCursor(4,4);
                        }                        
                    }
                    break;
                case 1: 
                    gotoxy(33,12); cprintf("          ");
                    getString(33,12,true,newAccount.password);               
                    break;
                case 2:
                    option=3;
                    clearwindow('a');
                    addFramework();
                    More();
                    return;
                case 3:
                    textbackground(BLUE);
                    if(strcmp(newAccount.user,NULL)==0)
                    {
                        gotoxy(26,18);
                        cprintf("  Debe escribir un usuario   ");
                        RemoveCursor(4,4);
                    }
                    else if(strcmp(newAccount.password,NULL)==0)
                    {
                        gotoxy(26,18);
                        cprintf("Debe escribir una contrase%ca",enye);
                        RemoveCursor(4,4);
                    }
                    else if(isAvailable==false)
                    {
                        textcolor(LIGHTRED);
                        gotoxy(26,18);  
                        cprintf("    El usuario ya existe    ");
                        RemoveCursor(4,4);
                    }
                    else
                    {
                        file = fopen("Accounts.txt","a++");
                        if(file==NULL)
                        {
                            gotoxy(26,18);
                            cprintf("No se ha podido abrir el fichero");
                            RemoveCursor(4,4);
                            getch();
                            clearscreen();
                            addFramework();
                            return;
                        }

                        fwrite(&newAccount,sizeof(newAccount),1,file);
                        fclose(file);
                        gotoxy(27,18);  cprintf("La cuenta se ha registrado");
                        RemoveCursor(4,4);
                        getch();
                        LoginAndRegisterDesigner();
                        return;
                    }
                    break;
                default:
                    FatalError();
                    break;
            }
    }
    while(key!=esc);
}
void LoginAndRegister(void)
{
    char *commands[]={"Iniciar Sesion","Registrarse"};
    int positionY[2]={10,14};

    for(i=0;i<2;i++)
    {
        if(i==option)
            textbackground(BLACK);
        else
            textbackground(BLUE);
        
        textcolor(WHITE);
        gotoxy(24,positionY[i]);
        cprintf("%c %s",i==option ? 16 : 0,commands[i]);
    }
    
    RemoveCursor(4,4);
    do
        key = getch();
    while(key!=up && key!=down && key!=enter && key!=esc);
    

    if(key==up)
        option = option == 0  ? 1 : 0 ;

    else if(key==down)
        option = option == 1  ? 0 : 1 ;
    
    else if(key==esc)
        exit(0);
    
    else
        switch(option)
        {
            case 0:
                loginCount=0;
                Login();
                return;
            case 1:
                RegisterDesigner();
                return;
            default:
                exit(-1);
                break;
        }
    LoginAndRegister();
}
void Menu(void)
{
    char *commands[] = {"Agregar","Buscar","Registro","Mas"};   
    gotoxy(3,2);

    for(i=0;i<4;i++)
    {
        if(i!=screen)
        {
            textbackground(BLUE);
            textcolor(LIGHTGRAY);
        }
        else
        {
            textbackground(LIGHTGRAY);
            textcolor(BLUE);
        }
        cprintf("  %s  ",commands[i]);
    }

    RemoveCursor(3,4);
    do
        key = getch();
    while(key!=tab && key!=enter && key!=left && key!=right);

    if(key==tab || key==right)
        screen = screen!=3 ? screen + 1 : 0;

    else if(key==left)
        screen = screen!=0 ? screen - 1 : 3;

    else
    {
        option=0;
        clearwindow('a');
        switch(screen)
        {
            case 0:
                addFramework();
                Add();
                break;
            case 1:
                clearscreen();
                SearchDesigner();
                break;
            case 2:
                clearscreen();
                ShowDatabaseDesigner();
                if(database[configuration.ID_database].ID > 0)
                    ShowDatabase();
                break;
            case 3:
                addFramework();
                More();
                break;
            default:
                FatalError();
                break;
        }
    }

    Menu();
}
void More(void)
{
    char *group[]= {"1M1 - CO","1M2 - CO","1M3 - CO","1M4 - CO"}, *chosenSemestre[] = {"I ","II"}, *commands[] = {"Grupo","Semestre","Acerca de","Registrar Cuenta","Cerrar Sesion","Salir"};

    textbackground(WHITE);
    for(i=0;i<6;i++)
    {
        if(i==option)
            textcolor(BLUE);
        else
            textcolor(BLACK);
        
        gotoxy(4,(i*2)+6);
        cprintf("%c %s",i==option ? cursor : false,commands[i]);
    }

    textcolor(BLACK);
    gotoxy(32,6);
    cprintf("[ %s ]",group[configuration.ID_database]);

    gotoxy(32,8);
    cprintf("[ %s ]",chosenSemestre[configuration.semester]);

    for(i=0;i<7;i++)
    {
        gotoxy(58,6+i);
        cprintf("%s", option==0?groupInformation[i]:option==1?semesterInformation[i]:option==2?aboutInformation[i]:option==3?registerInformation[i]:option==4?closeSessionInformation[i]:exitInformation[i]);
    }

    RemoveCursor(4,4);
    do
        key = getch();
    while(key!=up && key!=down && key!=enter && key!=esc && key!=tab);

    if(key == up)
        option = option==0 ? 5 : option - 1;

    else if(key == down)
        option = option==5 ? 0 : option + 1;

    else if(key == esc||key == tab)
    {
        textcolor(BLACK);
        gotoxy(4,(option*2)+6);
        cprintf("%c %s",0,commands[option]);
        return;
    }
    else if(key == enter)
    {
        switch(option)
        {
            case 0:
                suboption=configuration.ID_database;
                do
                {
                    gotoxy(32,6);
                    textcolor(BLUE);
                    cprintf("[ %s ]",group[suboption]);

                    RemoveCursor(4,4);
                    do
                        key = getch();
                    while(key!=up && key!=down && key!=enter && key!=esc);

                    if(key==up)
                        suboption = suboption==0 ? 3 : suboption - 1;

                    else if(key==down)
                        suboption = suboption==3 ? 0 : suboption + 1;

                    else if(key==enter || key==esc) 
                    {
                        configuration.ID_database = suboption;
                        saveConfiguration();
                        gotoxy(32,6);
                        textcolor(BLACK);
                        cprintf("[ %s ]",group[suboption]);
                    }
                }
                while(key!=enter && key!=esc);
                key=NULL;
                break;
            case 1:
                suboption=configuration.semester;
                do
                {
                    textcolor(BLUE);
                    gotoxy(32,8);
                    cprintf("[ %s ]",chosenSemestre[suboption]);

                    RemoveCursor(4,4);
                    do
                        key = getch();
                    while(key!=up && key!=down && key!=enter && key!=esc);

                    if(key==up)
                        suboption = suboption == 0 ? 1 : 0;

                    else if(key==down)
                        suboption = suboption == 1 ? 0 : 1;

                    else if(key==enter || key==esc)
                    {
                        configuration.semester = suboption;
                        saveConfiguration();
                        gotoxy(32,8);
                        textcolor(BLACK);
                        cprintf("[ %s ]",chosenSemestre[suboption]);
                    }
                }
                while(key!=enter && key!=esc);
                key=NULL;
                break;
            case 2:
                about();
                RemoveCursor(4,4);
                getch();
                clearwindow('a');
                break;
            case 3:
                RegisterDesigner();
                break;
            case 4:
                clearwindow('a');
                LoginAndRegisterDesigner();
                addFramework();
                about();
                return;
            default:
                save();
                system("cls");
                exit(0);
        }
    }
    More();
}

void about(void)
{
    char *info[] = {"PROYECTO REGISTRO ACADEMICO","Lider en ciencia y tecnologia","FEC - FACULTAD DE ELECTROTECNIA Y COMPUTACION","1M1 - CO","Integrantes","Gabriel Ortiz","2020-0325U","Luis Pineda","2020-0251U","Engel Reyes","2020-0505U","Ing. Nelson Barrios"};
    int positionxy[2][12] = {
        {16,15,07,24,63,60,67,60,67,60,67,59},
        {05,16,18,20,05,7,9,11,13,15,17,21}};

    clearwindow('a');

    textcolor(BLACK);
    for (i=0;i<12;i++)
    {
        gotoxy(positionxy[0][i],positionxy[1][i]);
        cprintf("%s",info[i]);
    }
    LogoSmall(21,7);
}

void Add(void)
{
    char *commands[5] = {"Nombre:","Apellido:","Carnet:","Asignaturas","Agregar"};
    int positionY[5] = {5,7,9,11,22};
    char *subcommands[2]={"Si","No"};
    int subPositionX[2]={32,43};
    char *limitsCommands[]={"Limite de estudiantes por","aula alcanzado...","OK"};
    int limitsPosition[2][3]={{27,27,39},{11,12,16}};
    student student;
    student.name[0]=NULL;
    student.lastname[0]=NULL;
    student.carnet[0]=NULL;

    for(i=0;i<9;i++)
    {
        if(i<4)
            student.class->nameClass=lessons[0][i];
        else
            student.class->nameClass=lessons[1][i];
        
        student.class[i].nota=-1;
        student.class[i]._isActive=false;
    }
    textcolor(BLACK);
    gotoxy(19,11);
    cprintf("Clase                           Nota");
    do
    {
        textbackground(WHITE);
        for(i=0;i<5;i++)
        {
            if(i==option)
                textcolor(BLUE);
            else
                textcolor(BLACK);
            
            gotoxy(4,positionY[i]);
            cprintf("%c %s",i==option ? cursor : 0,commands[i]);

            gotoxy(17,(i*2)+13);
            textcolor(BLACK);
            cprintf("%c %s",student.class[configuration.semester==0?i:i+4]._isActive==true?cursor2:0, lessons[configuration.semester][i]);
        }
        textcolor(BLACK);
        for(i=0;i<5;i++)
        {
            gotoxy(58,6+i);
            cprintf("%s", option==0? nameInformation[i] : option==1? lastNameInformation[i] : option==2? carnetInformation[i] : option==3? classInformation[i] : addInformation[i]);
        }
        RemoveCursor(3,4);
        do
            key =  getch();
        while(key!=up && key!=down && key!=esc && key!=enter && key!=tab);

        if(key==up)
            option = option==0 ? 4 : option - 1 ;
        else if(key==down)
            option = option==4 ? 0 : option + 1 ;
        else if(key==esc||key==tab)
        {
            textcolor(BLACK);
            gotoxy(4,positionY[option]);
            cprintf("%c %s",0,commands[option]);
            return;
        }
        else if(key==enter)
        {
            textcolor(WHITE);
            switch(option)
            {
                case 0:
                    gotoxy(14,5);
                    cprintf("           ");
                    getString(14,5,false,student.name);
                    textcolor(BLACK);
                    gotoxy(14,5);
                    cprintf("%s",student.name);
                    break;
                case 1:
                    gotoxy(16,7);
                    cprintf("           ");
                    getString(16, 7,false,student.lastname);
                    textcolor(BLACK);
                    gotoxy(16,7);
                    cprintf("%s",student.lastname);
                    break;
                case 2:
                    gotoxy(14,9);
                    cprintf("           ");
                    getCarnet(14,9,student.carnet);

                    textcolor(RED);
                    gotoxy(14,9);
                    cprintf("%s",student.carnet);

                    for(i=0;i<4;i++)
                        for(j=0;j<database[i].ID;j++)
                            if(strcmp(database[i].student[j].carnet,student.carnet)==0)
                                student.carnet[0]='\0';
                    
                    if(!strcmp(NULL,student.carnet)==0)
                    {
                        textcolor(BLACK);
                        gotoxy(14,9);
                        cprintf("%s",student.carnet);    
                    }   
                    break;
                case 3:
                    textcolor(BLACK);
                    gotoxy(19,11);
                    cprintf("Clase                           Nota");
                    suboption=0;
                    do
                    {
                        for(i=0;i<5;i++)
                        {
                            if(suboption==i)
                                textcolor(BLUE);

                            else
                                textcolor(BLACK);
                            
                            gotoxy(17,(i*2)+13);
                            cprintf("%c %s",student.class[configuration.semester==0?i:i+4]._isActive==true?cursor2:0, lessons[configuration.semester][i]);
                        }

                        for(i=0;i<5;i++)
                        {
                            gotoxy(58,14+i);
                            if(configuration.semester==0)
                                cprintf("%s", enableClass[i]);
                            else
                                cprintf("%s", suboption==4 ? enableClass[i] : suboption==3 ? disabledClass2[i] : suboption==0 ? disabledClass1[i] : disabledClass0[i]);
                        }
                        RemoveCursor(4,4);
                        do
                            key = getch();
                        while (key!=up && key!=down && key!=enter && key!=esc);

                        if(key==up)
                            suboption = suboption==0 ? 0 : suboption-1 ;
                        else if(key==down)
                            if(configuration.semester==0)
                                suboption = suboption==3 ? 3 : suboption+1;
                            else
                                suboption = suboption==4 ? 4 : suboption+1;
                        else if (key==enter) 
                            if(!((configuration.semester==1) && ( (suboption==0&&student.class[0].nota<60) || ((suboption==1||suboption==2)&&student.class[0]._isActive==false)||(suboption==3&&student.class[1].nota<60))))
                            {
                                textcolor(BLUE);
                                gotoxy(51,(suboption*2)+13);
                                cprintf("   ");
                                student.class[configuration.semester==0 ? suboption : suboption+4].nota = getScore(51,(suboption*2)+13);
                                
                                if(student.class[configuration.semester==0 ? suboption : suboption+4].nota>=0)
                                {
                                    textcolor(BLACK);
                                    gotoxy(51,(suboption*2)+13);
                                    cprintf("%d   ",student.class[configuration.semester==0 ? suboption : suboption+4].nota);
                                    student.class[configuration.semester==0 ? suboption : suboption+4]._isActive=true;
                                }
                                else
                                {
                                    gotoxy(51,(suboption*2)+13);
                                    cprintf("   ");
                                    student.class[configuration.semester==0 ? suboption : suboption+4]._isActive=false;
                                }
                            }
                        else if (key==esc)
                        {
                            textcolor(BLACK);
                            gotoxy(17,(suboption*2)+13);
                            cprintf("%c %s",student.class[configuration.semester==0 ? suboption : suboption+4]._isActive==true?cursor2:0, lessons[configuration.semester][suboption]);
                        }
                    }
                    while(key!=esc);
                    clearwindow('r');
                    key=NULL;
                    break;
                case 4:
                    if(strcmp(student.name,NULL)==0||strcmp(student.lastname,NULL)==0||strcmp(student.carnet,NULL)==0) 
                        break;

                    MessageBox();
                    gotoxy(27,11);
                    textbackground(BLUE);
                    cprintf("%cDesea agregar el usuario?",opensing);
                    suboption=0;

                    do
                    {
                        textcolor(WHITE);
                        for(i=0;i<2;i++)
                        {
                            if(i==suboption)
                                textbackground(BLACK);
                            else
                                textbackground(BLUE);
                            
                            gotoxy(subPositionX[i],15);
                            cprintf("%c %s",i==suboption?cursor:0,subcommands[i]);
                        }

                        RemoveCursor(4,4);
                        do
                            key=getch();
                        while(key!=left&&key!=right&&key!=enter&&key!=esc);
                        
                        if(key==left)
                            suboption = suboption == 0 ? 1 : 0;
                        else if(key==right)
                            suboption = suboption == 1 ? 0 : 1;
                        else if(key==esc)
                        {
                            clearscreen();
                            addFramework();
                            loadStudentData(&student);
                        }
                        else if(key==enter)
                        {
                            if(suboption==1)
                            {
                                clearscreen();
                                addFramework();
                                loadStudentData(&student);
                            }
                            else if(database[configuration.ID_database].ID>=MaxStds)
                            {
                                MessageBox();
                                textcolor(WHITE);

                                for(i=0;i<3;i++)
                                {
                                    if(i==2)
                                        textbackground(BLACK);
                                    else
                                        textbackground(BLUE);

                                    gotoxy(limitsPosition[0][i],limitsPosition[1][i]);
                                    cprintf("%s",limitsCommands[i]);
                                }
                                getch();
                                clearscreen();
                                addFramework();
                                Add();
                                return;
                            }
                            else if(suboption==0)
                            {
                                database[configuration.ID_database].student[database[configuration.ID_database].ID]=student;
                                database[configuration.ID_database].ID++;
                                clearscreen();
                                addFramework();
                                save();
                                Add();
                                return;
                            }
                        }
                    }
                    while(key!=esc && key!=enter);
                    key=NULL;
                    break;
                default:
                    FatalError();
                    break;
            }
        }
    }
    while(key!=esc);
}

void editStudent(int ID)
{
    char *commands[7] = {"Nombre:","Apellido:","Carnet:","Asignaturas","Cancelar","Eliminar","Actualizar"};
    int positionY[7] = {5,7,9,11,18,20,22};
    char *subcommands[2]={"Si","No"};
    int subPositionX[2]={32,43};
    int acumulation,activeClass,semesterAcumulation,semesterActiveClass;
    float average,semesterAverage;
    student student=database[configuration.ID_database].student[ID];
    
    clearscreen();
    addFramework();
    loadStudentData(&student);
    gotoxy(30,5);
    cprintf("Promedio anual: -");
    gotoxy(30,7);
    cprintf("Promedio semestral: -");
    
    do
    {
        acumulation=0;
        activeClass=0;
        semesterAcumulation=0;
        semesterActiveClass=0;
        for(i=0;i<9;i++)
        {
            if(configuration.semester==0 && i<4 && student.class[i]._isActive==true)
            {
                semesterAcumulation += student.class[i].nota;
                semesterActiveClass++;
            }
            else if (configuration.semester==1 && i>=4 && student.class[i]._isActive==true)
            {
                semesterAcumulation += student.class[i].nota;
                semesterActiveClass++;
            }
            if(student.class[i]._isActive==true)
            {
                acumulation += student.class[i].nota;
                activeClass++;
            }
        }
        textcolor(BLACK);
        if(activeClass!=0)
        {
            average = acumulation/activeClass;
            gotoxy(46,5);
            cprintf("%.2f", average);
        }

        if(semesterActiveClass)
        {
            semesterAverage = semesterAcumulation/semesterActiveClass;   
            gotoxy(50,7);
            cprintf("%.2f",semesterAverage);
        }
        
        textbackground(WHITE);
        for(i=0;i<7;i++)
        {
            if(i==option)
                textcolor(BLUE);
            else
                textcolor(BLACK);
            
            gotoxy(4,positionY[i]);
            cprintf("%c %s",i==option ? cursor : 0,commands[i]);
        }

        for(i=0;i<5;i++)
        {
            gotoxy(58,6+i);
            cprintf("%s", option==0? nameInformation[i] : option==1? lastNameInformation[i] : option==2? carnetInformation[i] : option==3? classInformation[i] : option==4? cancelInformation[i] : option==5? deleteInformation[i] : updateInformation[i]);
        }

        RemoveCursor(3,4);
        do
            key =  getch();
        while(key!=up && key!=down && key!=esc && key!=enter && key!=tab);

        if(key==up)
            option = option==0 ? 6 : option - 1 ;
        else if(key==down)
            option = option==6 ? 0 : option + 1 ;
        else if(key==esc||key==tab)
        {
            clearscreen();
            ShowDatabaseDesigner();
            if(database[configuration.ID_database].ID > 0)
                ShowDatabase();
            return;
        }
        else if(key==enter)
        {
            textcolor(WHITE);
            switch(option)
            {
                case 0:
                    gotoxy(14,5);
                    cprintf("           ");
                    getString(14,5,false,student.name);
                    textcolor(BLACK);
                    gotoxy(14,5);
                    cprintf("%s",student.name);
                    break;
                case 1:
                    gotoxy(16,7);
                    cprintf("           ");
                    getString(16, 7,false,student.lastname);
                    textcolor(BLACK);
                    gotoxy(16,7);
                    cprintf("%s",student.lastname);
                    break;
                case 2:
                    break;
                case 3:
                    textcolor(BLACK);
                    gotoxy(19,11);
                    cprintf("Clase                           Nota");
                    suboption=0;
                    do
                    {
                        for(i=0;configuration.semester==1?i<5:i<4;i++)
                        {
                            if(suboption==i)
                                textcolor(BLUE);

                            else
                                textcolor(BLACK);
                            
                            gotoxy(17,(i*2)+13);
                            cprintf("%c %s",student.class[configuration.semester==0?i:i+4]._isActive==true?cursor2:0, lessons[configuration.semester][i]);
                        }
                        
                        for(i=0;i<5;i++)
                        {
                            textcolor(BLACK);
                            gotoxy(58,14+i);
                            if(configuration.semester==0)
                                cprintf("%s", enableClass[i]);
                            else
                                cprintf("%s", suboption==4 ? enableClass[i] : suboption==3 ? disabledClass2[i] : suboption==0 ? disabledClass1[i] : disabledClass0[i]);
                        }
                        RemoveCursor(3,4);
                        do
                            key = getch();
                        while (key!=up && key!=down && key!=enter && key!=esc);

                        if(key==up)
                            suboption = suboption==0 ? 0 : suboption-1 ;
                        else if(key==down)
                            if(configuration.semester==0)
                                suboption = suboption==3 ? 3 : suboption+1;
                            else
                                suboption = suboption==4 ? 4 : suboption+1;
                        else if (key==enter)
                        {
                            if(!((configuration.semester==1) && ( (suboption==0&&student.class[0].nota<60) || ((suboption==1||suboption==2)&&student.class[0]._isActive==false)||(suboption==3&&student.class[1].nota<60))))
                            {
                                gotoxy(51,(suboption*2)+13);
                                cprintf("   ");
                                textcolor(BLUE);
                                student.class[configuration.semester==0 ? suboption : suboption+4].nota = getScore(51,(suboption*2)+13);
                                
                                if(configuration.semester == 0 && suboption==0 && student.class[0].nota<60 && student.class[4]._isActive==true)
                                    student.class[0].nota=60;
                                
                                else if(configuration.semester==0 && suboption==0 && student.class[0].nota<0 && (student.class[5]._isActive==true || student.class[6]._isActive==true))
                                    student.class[0].nota=0;

                                if(configuration.semester==0 && suboption==1 && student.class[1].nota<60 && student.class[7]._isActive==true)
                                    student.class[1].nota=60;

                                if(student.class[configuration.semester==0 ? suboption : suboption+4].nota>=0)
                                {
                                    textcolor(BLACK);
                                    gotoxy(51,(suboption*2)+13);
                                    cprintf("%d  ",student.class[configuration.semester==0 ? suboption : suboption+4].nota);
                                    student.class[configuration.semester==0 ? suboption : suboption+4]._isActive=true;
                                }
                                else
                                {
                                    gotoxy(51,(suboption*2)+13);
                                    cprintf("   ");
                                    student.class[configuration.semester==0 ? suboption : suboption+4]._isActive=false;
                                }
                            }
                        }
                        else if (key==esc)
                        {
                            textcolor(BLACK);
                            gotoxy(17,(suboption*2)+13);
                            cprintf("%c %s",student.class[configuration.semester==0 ? suboption : suboption+4]._isActive==true?cursor2:0, lessons[configuration.semester][suboption]);
                        }
                    }
                    while(key!=esc);
                    clearwindow('r');
                    key=NULL;
                    break;
                case 4:
                    option=ID;
                    clearscreen();
                    ShowDatabaseDesigner();
                    if(database[configuration.ID_database].ID > 0)
                        ShowDatabase();
                    return;
                case 5:
                    Login();
                    for(i=ID;i<database[configuration.ID_database].ID-1;i++)
                        database[configuration.ID_database].student[i]=database[configuration.ID_database].student[i+1];

                    database[configuration.ID_database].ID--;
                    option=0;
                    save();
                    clearscreen();
                    ShowDatabaseDesigner();
                    if(database[configuration.ID_database].ID > 0)
                        ShowDatabase();
                    return;
                case 6:
                    if(strcmp(student.name,NULL)==0||strcmp(student.lastname,NULL)==0||strcmp(student.carnet,NULL)==0) 
                        break;

                    MessageBox();
                    gotoxy(27,11);
                    textbackground(BLUE);
                    cprintf("%cDesea actualizar el usuario?",opensing);
                    suboption=0;
                    do
                    {
                        textcolor(WHITE);
                        for(i=0;i<2;i++)
                        {
                            if(i==suboption)
                                textbackground(BLACK);
                            else
                                textbackground(BLUE);
                            
                            gotoxy(subPositionX[i],15);
                            cprintf("%c %s",i==suboption?cursor:0,subcommands[i]);
                        }

                        RemoveCursor(3,4);
                        do
                            key=getch();
                        while(key!=left&&key!=right&&key!=enter&&key!=esc);
                        
                        if(key==left)
                            suboption = suboption == 0 ? 1 : 0;
                        else if(key==right)
                            suboption = suboption == 1 ? 0 : 1;
                        else if(key==enter||key==esc)
                        {
                            clearscreen();
                            addFramework();
                            textcolor(BLACK);
                            if(suboption==1)
                                for(i=0;i<3;i++)
                                {
                                    gotoxy(i==1?16:14,positionY[i]);
                                    cprintf("%s",i==0?student.name:i==1?student.lastname:student.carnet);
                                }
                            else 
                            {
                                database[configuration.ID_database].student[ID]=student;
                                save();
                                clearscreen();
                                ShowDatabaseDesigner();
                                ShowDatabaseDesigner();
                                if(database[configuration.ID_database].ID > 0)
                                    ShowDatabase();
                                return;
                            }
                        }
                    }
                    while(key!=esc && key!=enter);
                    key=NULL;
                    break;
                default:
                    FatalError();
                    break;
            }
        }
        
    }
    while(key!=esc);
}
/*--------------------------------- Funtions -------------------------------*/
void saveConfiguration(void)
{
    FILE * file;

    file = fopen("Config.txt","w");
    fwrite(&configuration,sizeof(configuration),1,file);
    fclose(file);
}

void loadConfiguration(void)
{
    FILE * file;

    file = fopen("Config.txt","r");
    if(file==NULL)
    {
        file = fopen("Config.txt","w");
        fwrite(&configuration,sizeof(configuration),1,file);
    }
    else
        fread(&configuration,sizeof(configuration),1,file);

    fclose(file);
}

void save(void)
{
    FILE * file;

    file = fopen("DATABASE.txt","w");
    if(!file == NULL)
        for(i=0;i<4;i++)
        {
            fwrite(&database[i],sizeof(database[i]),1,file);
        }
        fclose(file);
}

void load(void)
{
    FILE * file;

    file = fopen("DATABASE.txt","r");
    if(!file==NULL)
        for(i=0;i<4;i++)
            fread(&database[i],sizeof(database),1,file);

    else
        file = fopen("DATABASE.txt","w");

    fclose(file);
}

void loadStudentData(student* student)
{
    textcolor(BLACK);
    gotoxy(19,11);
    cprintf("Clase                           Nota");
    gotoxy(63,4);
    cprintf("INFORMACION");
    gotoxy(14,5);
    cprintf("%s", student->name);
    gotoxy(16,7);
    cprintf("%s",student->lastname);
    gotoxy(14,9);
    cprintf("%s",student->carnet);

    for(i=0; configuration.semester == 0 ? i<4 : i<5;i++)
    {
        textcolor(BLACK);
        gotoxy(17,(i*2)+13);
        cprintf("%c %s",student->class[configuration.semester==0?i:i+4]._isActive==true?cursor2:0, lessons[configuration.semester][i]);

        gotoxy(17,(i*2)+13);
        textcolor(BLACK);
        cprintf("%c %s",student->class[configuration.semester==0?i:i+4]._isActive==true?cursor2:0, lessons[configuration.semester][i]);

        gotoxy(51,(i*2)+13);
        if(student->class[configuration.semester==0 ? i : i+4]._isActive==true)
            cprintf("%d",student->class[configuration.semester==0 ? i : i+4].nota);
    }
}

void clearscreen(void)
{
    textbackground(WHITE);
    for(i=1;i<=80;i+=20)
        for(j=3;j<=24;j++)
        {
            gotoxy(i,j);
            cprintf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
        }
}

void clearwindow(char window)
{
    textbackground(WHITE);
    if(window == 'l' || window == 'a')
    {
        for(i=2;i<=56;i+=11)
            for(j=4;j<=23;j++)
            {

                gotoxy(i,j);
                cprintf("%c%c%c%c%c%c%c%c%c%c%c",0,0,0,0,0,0,0,0,0,0,0);
            }
    }
    for(i=58;i<=79;i+=11)
        for(j=4;j<=23;j++)
        {
            gotoxy(i,j);
            cprintf("%c%c%c%c%c%c%c%c%c%c%c",0,0,0,0,0,0,0,0,0,0,0);
        }
    textcolor(BLACK);
    gotoxy(63,4);
    cprintf("INFORMACION");
}

void addFramework(void)
{    
    textbackground(WHITE);
    textcolor(BLACK);
    for(i=1;i<=80;i++)
    {
        gotoxy(i,3);
        if(i==80)
            cprintf("%c",esquinaNE);
        else if(i==1)
            cprintf("%c",esquinaNW);
        else if(i==57)
            cprintf("%c",194);
        else
            cprintf("%c",lineaH);
        
        gotoxy(i,24);
        if(i==80)
            cprintf("%c",esquinaSE);
        else if(i==1)
            cprintf("%c",esquinaSW);
        else if(i==57)
            cprintf("%c",193);
        else
            cprintf("%c",lineaH);
        
        if(i>=4&&i<=23)
        {
            gotoxy(1,i);
            cprintf("%c",lineaV);
            
            gotoxy(57,i);
            cprintf("%c",lineaV);

            gotoxy(80,i);
            cprintf("%c",lineaV);
        }
    }
}
