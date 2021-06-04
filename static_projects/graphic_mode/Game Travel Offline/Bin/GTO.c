#include <alloc.h>
#include <c:\\tc20\\include\\airports.h>
#include <c:\\tc20\\include\\rooms.h>
#include <c:\\tc20\\include\\gtools.h>
#include <c:\\tc20\\include\\mundi.h>
#include <c:\\tc20\\include\\airplane.h>
#include <c:\\tc20\\include\\radar.h>
#include <c:\\tc20\\include\\flags.h>

#define duration 33
#define setfillcolor(color)              \
    {                                    \
        setfillstyle(SOLID_FILL, color); \
    }

typedef struct Character
{
    Skin skin;
    char name[25];
    int nation, currentNation;
} character;

void convertRoute(int source, int destination);
void fill_out_papers_designer(void);
void fill_out_papers(void);
void Pause(void);
void draw_Airport(void);
void Travel(void);
void Travel_Designer(void);
void House_Designer(void);
void House(void);
void CharacterMenu_Designer(void);
void CharacterMenu(void);
void nextFrame(void);
void InitializeGraphic(void);
void Menu(void);
void Menu_Designer(void);
bool isInside(int x0, int y0, int x1, int y1, int x2, int y2);
void InformationScreen(void);
void logo_uni(int x, int y);
void GameMenu(void);
void GameMenu_Designer(void);
void changeNation(int);
void personalizeCharacter(void);

int xpos, ypos;
int directionRadar = US_NIC;
int CountrySelected = 0;
bool flightScale = false;
int AvailableCountrys[4];
Room Rooms[6] = {{LIGHTGRAY, CYAN, DARKGRAY, BROWN, LIGHTGRAY, BLUE, true}, {DARKGRAY, LIGHTGRAY, DARKGRAY, BLACK, BLACK, GREEN, false}, {WHITE, LIGHTRED, BROWN, BLACK, WHITE, RED, true}, {LIGHTGRAY, LIGHTMAGENTA, DARKGRAY, BROWN, LIGHTGRAY, CYAN, false}, {WHITE, LIGHTBLUE, BROWN, BLACK, WHITE, WHITE, true}, {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, false}};

character player = {{LIGHTGRAY, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK}, "", Nicaragua, Nicaragua};

void main()
{
    InitializeGraphic();
    
    init_mundi();

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    Menu_Designer();
    mver();
    Menu();
    getch();
}

void Menu_Designer(void)
{
    int i;
    setfillcolor(BLACK);
    setcolor(LIGHTGREEN);
    bar(0, 0, getmaxx(), getmaxy());
    setfillcolor(WHITE);
    for (i = 0; i < 300; i++)
    {
        putpixel(rand() % 640, rand() % 480, WHITE);
        fillellipse(rand() % 640, rand() % 480, 1, 1);
    }

    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    outtextxy(100, 50, "GAME:");
    setcolor(LIGHTGREEN);
    outtextxy(100, 50, "G");
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 6);
    outtextxy(125, 100, "TRAVEL");
    outtextxy(250, 160, "OFFLINE");
    setcolor(LIGHTGREEN);
    outtextxy(125, 100, "T");
    outtextxy(250, 160, "O");

    setcolor(WHITE);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
    setlinestyle(SOLID_LINE, EMPTY_FILL, 3);
    rectangle(9, 432, 88, 471);
    outtextxy(25, 434, "Salir");

    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 5);
    setlinestyle(SOLID_LINE, EMPTY_FILL, 3);
    rectangle(326, 285, 476, 345);
    outtextxy(339, 287, "JUGAR");
    rectangle(163, 285, 313, 345);
    outtextxy(195, 287, "INFO");
}

void Menu(void)
{
    bool shadow_exit[2] = {true, false};
    bool shadow_info[2] = {true, false};
    bool shadow_play[2] = {true, false};

    do
    {
        if (minlimit(1, 9, 432, 88, 471))
            shadow_exit[1] = true;
        else
            shadow_exit[1] = false;

        if (minlimit(1, 326, 285, 476, 345))
            shadow_play[1] = true;
        else
            shadow_play[1] = false;

        if (minlimit(1, 163, 285, 313, 345))
            shadow_info[1] = true;
        else
            shadow_info[1] = false;

        if (shadow_exit[0] != shadow_exit[1])
        {
            setcolor(shadow_exit[1] ? LIGHTGREEN : WHITE);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            setlinestyle(SOLID_LINE, EMPTY_FILL, 3);
            mocultar();
            rectangle(9, 432, 88, 471);
            outtextxy(25, 434, "Salir");
            mver();
            shadow_exit[0] = shadow_exit[1];
        }

        else if (shadow_play[0] != shadow_play[1])
        {
            setcolor(shadow_play[1] ? LIGHTGREEN : WHITE);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 5);
            setlinestyle(SOLID_LINE, EMPTY_FILL, 3);
            mocultar();
            rectangle(326, 285, 476, 345);
            outtextxy(339, 287, "JUGAR");
            mver();
            shadow_play[0] = shadow_play[1];
        }

        else if (shadow_info[0] != shadow_info[1])
        {
            setcolor(shadow_info[1] ? LIGHTGREEN : WHITE);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 5);
            setlinestyle(SOLID_LINE, SOLID_FILL, 3);
            mocultar();
            rectangle(163, 285, 313, 345);
            outtextxy(195, 287, "INFO");
            mver();
            shadow_info[0] = shadow_info[1];
        }

    } while (mclick() == 0);
    xpos = mxpos(1);
    ypos = mypos(1);
    while (mclick() != 0)
        ;

    if (isInside(xpos, ypos, 9, 432, 88, 471))
        exit(0);
    else if (isInside(xpos, ypos, 326, 285, 476, 345))
    {
        mocultar();
        GameMenu_Designer();
        mver();
        GameMenu();
        mocultar();
        Menu_Designer();
        mver();
    }
    else if (isInside(xpos, ypos, 163, 285, 313, 345))
    {
        InformationScreen();
        mocultar();
        Menu_Designer();
        mver();
    }
    Menu();
}

void GameMenu_Designer(void)
{
    int i;

    setfillcolor(BLACK);
    setcolor(LIGHTGREEN);
    bar(0, 0, getmaxx(), getmaxy());
    setfillcolor(WHITE);
    for (i = 0; i < 300; i++)
    {
        putpixel(rand() % 640, rand() % 480, WHITE);
        fillellipse(rand() % 640, rand() % 480, 1, 1);
    }

    setcolor(WHITE);
    setlinestyle(SOLID_LINE, EMPTY_FILL, 3);
    rectangle(142, 28, 500, 82);
    setlinestyle(SOLID_LINE, EMPTY_FILL, 1);
    rectangle(146, 33, 494, 76);

    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
    setlinestyle(SOLID_LINE, EMPTY_FILL, 3);
    rectangle(9, 432, 88, 471);
    outtextxy(23, 435, "Atras");

    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
    setlinestyle(SOLID_LINE, EMPTY_FILL, 3);
    rectangle(509, 432, 630, 471);
    outtextxy(520, 435, "Siguiente");

    NicaraguaFlag(75, 150);
    BrazilFlag(175, 150);
    SpainFlag(275, 150);
    ArgentinaFlag(375, 150);
    USAFlag(475, 150);
    setcolor(BLACK);
    changeNation(Nicaragua);
}

void GameMenu(void)
{
    bool shadow_textbox[2] = {true, false};
    bool shadow_exit[2] = {true, false};
    bool shadow_start[2] = {true, false};
    do
    {
        if (minlimit(1, 9, 432, 88, 471))
            shadow_exit[1] = true;
        else
            shadow_exit[1] = false;

        if (minlimit(1, 509, 432, 630, 471))
            shadow_start[1] = true;
        else
            shadow_start[1] = false;

        if (minlimit(1, 142, 28, 500, 82))
            shadow_textbox[1] = true;
        else
            shadow_textbox[1] = false;

        if (shadow_start[0] != shadow_start[1])
        {
            setcolor(shadow_start[1] ? GREEN : WHITE);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            setlinestyle(SOLID_LINE, EMPTY_FILL, 3);
            mocultar();
            rectangle(509, 432, 630, 471);
            outtextxy(520, 435, "Siguiente");
            mver();
            shadow_start[0] = shadow_start[1];
        }
        else if (shadow_textbox[0] != shadow_textbox[1])
        {
            setcolor(shadow_textbox[1] ? GREEN : WHITE);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            setlinestyle(SOLID_LINE, EMPTY_FILL, 3);
            mocultar();
            rectangle(142, 28, 500, 82);
            setlinestyle(SOLID_LINE, EMPTY_FILL, 1);
            rectangle(146, 33, 494, 76);
            outtextxy(164, 50, player.name);
            mver();
            shadow_textbox[0] = shadow_textbox[1];
        }
        else if (shadow_exit[0] != shadow_exit[1])
        {
            setcolor(shadow_exit[1] ? LIGHTGREEN : WHITE);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            setlinestyle(SOLID_LINE, EMPTY_FILL, 3);
            mocultar();
            rectangle(9, 432, 88, 471);
            outtextxy(23, 434, "Atras");
            mver();
            shadow_exit[0] = shadow_exit[1];
        }

    } while (mclick() == 0);

    xpos = mxpos(1);
    ypos = mypos(1);

    while (mclick() != 0)
    {
    }

    if (isInside(xpos, ypos, 509, 432, 630, 471) && strcmp(player.name, NULL) != 0)
    {
        mocultar();
        CharacterMenu_Designer();
        mver();
        CharacterMenu();
        mocultar();
        GameMenu_Designer();
        mver();
        return;
    }
    else if (isInside(xpos, ypos, 509, 432, 630, 471) && strcmp(player.name, NULL) == 0)
    {
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
        setcolor(LIGHTRED);
        outtextxy(150, 432, "Ingresa un nombre por favor");
    }
    else if (isInside(xpos, ypos, 75, 150, 135, 180))
        changeNation(Nicaragua);

    else if (isInside(xpos, ypos, 175, 150, 235, 180))
        changeNation(Brazil);

    else if (isInside(xpos, ypos, 275, 150, 335, 180))
        changeNation(Spain);

    else if (isInside(xpos, ypos, 375, 150, 435, 180))
        changeNation(Argentina);

    else if (isInside(xpos, ypos, 475, 150, 535, 180))
        changeNation(USA);

    else if (isInside(xpos, ypos, 9, 432, 88, 471))
        return;
    else if (isInside(xpos, ypos, 142, 28, 500, 82))
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        MinStrLn = 0;
        MaxStrLn = 21;
        setcolor(BLACK);
        mocultar();
        outtextxy(164, 50, player.name);
        mver();
        setcolor(GREEN);
        get_string(164, 50, player.name);

        if (strcmp(player.name, NULL) == 0)
            setcolor(LIGHTRED);
        else
            setcolor(BLACK);

        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
        outtextxy(150, 432, "Ingresa un nombre por favor");
    }

    GameMenu();
}

void CharacterMenu_Designer(void)
{
    int i;

    setcolor(LIGHTGREEN);
    setfillcolor(BLACK);
    bar(0, 0, getmaxx(), getmaxy());
    setfillcolor(WHITE);
    for (i = 0; i < 300; i++)
    {
        putpixel(rand() % 640, rand() % 480, WHITE);
        fillellipse(rand() % 640, rand() % 480, 1, 1);
    }

    setcolor(WHITE);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 5);
    outtextxy(60, 10, "Personaliza tu personaje");

    setfillcolor(LIGHTGRAY);
    bar(47, 122, 153, 428);
    setfillcolor(DARKGRAY);
    bar(50, 125, 150, 425);

    Avatar(50, 125, &player.skin);

    setcolor(WHITE);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
    setlinestyle(SOLID_LINE, EMPTY_FILL, 3);

    rectangle(getmaxx() / 2, 100, getmaxx() / 2 + 150, 139);
    outtextxy(getmaxx() / 2 + 55, 103, "Piel");

    rectangle(getmaxx() / 2, 150, getmaxx() / 2 + 150, 189);
    outtextxy(getmaxx() / 2 + 55, 153, "Pelo");

    rectangle(getmaxx() / 2, 200, getmaxx() / 2 + 150, 239);
    outtextxy(getmaxx() / 2 + 55, 203, "Ojos");

    rectangle(getmaxx() / 2, 250, getmaxx() / 2 + 150, 289);
    outtextxy(getmaxx() / 2 + 20, 253, "Chaqueta");

    rectangle(getmaxx() / 2, 300, getmaxx() / 2 + 150, 339);
    outtextxy(getmaxx() / 2 + 25, 303, "Hombro");

    rectangle(getmaxx() / 2, 350, getmaxx() / 2 + 150, 389);
    outtextxy(getmaxx() / 2 + 23, 353, "Pantalon");

    rectangle(getmaxx() / 2, 400, getmaxx() / 2 + 150, 439);
    outtextxy(getmaxx() / 2 + 25, 403, "Zapatos");

    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
    setlinestyle(SOLID_LINE, EMPTY_FILL, 3);
    rectangle(509, 432, 630, 471);
    outtextxy(520, 435, " Iniciar ");
    rectangle(9, 432, 88, 471);
    outtextxy(23, 435, "Atras");
}

void CharacterMenu(void)
{
    bool shadow_exit[2] = {true, false};
    bool shadow_skin[2] = {true, false};
    bool shadow_hair[2] = {true, false};
    bool shadow_eyes[2] = {true, false};
    bool shadow_jacket[2] = {true, false};
    bool shadow_jacket2[2] = {true, false};
    bool shadow_jean[2] = {true, false};
    bool shadow_shoes[2] = {true, false};
    bool shadow_start[2] = {true, false};
    do
    {
        if (minlimit(1, 9, 432, 88, 471))
            shadow_exit[1] = true;
        else
            shadow_exit[1] = false;

        if (minlimit(1, getmaxx() / 2, 100, getmaxx() / 2 + 150, 139))
            shadow_skin[1] = true;
        else
            shadow_skin[1] = false;

        if (minlimit(1, getmaxx() / 2, 150, getmaxx() / 2 + 150, 189))
            shadow_hair[1] = true;
        else
            shadow_hair[1] = false;

        if (minlimit(1, getmaxx() / 2, 200, getmaxx() / 2 + 150, 239))
            shadow_eyes[1] = true;
        else
            shadow_eyes[1] = false;

        if (minlimit(1, getmaxx() / 2, 250, getmaxx() / 2 + 150, 289))
            shadow_jacket[1] = true;
        else
            shadow_jacket[1] = false;

        if (minlimit(1, getmaxx() / 2, 300, getmaxx() / 2 + 150, 339))
            shadow_jacket2[1] = true;
        else
            shadow_jacket2[1] = false;

        if (minlimit(1, getmaxx() / 2, 350, getmaxx() / 2 + 150, 389))
            shadow_jean[1] = true;
        else
            shadow_jean[1] = false;

        if (minlimit(1, getmaxx() / 2, 400, getmaxx() / 2 + 150, 439))
            shadow_shoes[1] = true;
        else
            shadow_shoes[1] = false;

        if (minlimit(1, 509, 432, 630, 471))
            shadow_start[1] = true;
        else
            shadow_start[1] = false;

        if (shadow_exit[0] != shadow_exit[1])
        {
            setcolor(shadow_exit[1] ? LIGHTGREEN : WHITE);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            setlinestyle(SOLID_LINE, EMPTY_FILL, 3);
            mocultar();
            rectangle(9, 432, 88, 471);
            outtextxy(23, 434, "Atras");
            mver();
            shadow_exit[0] = shadow_exit[1];
        }
        else if (shadow_start[1] != shadow_start[0])
        {
            setcolor(shadow_start[1] ? GREEN : WHITE);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            setlinestyle(SOLID_LINE, EMPTY_FILL, 3);

            mocultar();
            rectangle(509, 432, 630, 471);
            outtextxy(520, 435, " Iniciar ");
            mver();

            shadow_start[0] = shadow_start[1];
        }
        else if (shadow_skin[1] != shadow_skin[0])
        {
            setcolor(shadow_skin[1] ? GREEN : WHITE);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            setlinestyle(SOLID_LINE, EMPTY_FILL, 3);

            mocultar();
            rectangle(getmaxx() / 2, 100, getmaxx() / 2 + 150, 139);
            outtextxy(getmaxx() / 2 + 55, 103, "Piel");
            mver();

            shadow_skin[0] = shadow_skin[1];
        }
        else if (shadow_hair[1] != shadow_hair[0])
        {
            setcolor(shadow_hair[1] ? GREEN : WHITE);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            setlinestyle(SOLID_LINE, EMPTY_FILL, 3);

            mocultar();
            rectangle(getmaxx() / 2, 150, getmaxx() / 2 + 150, 189);
            outtextxy(getmaxx() / 2 + 55, 153, "Pelo");
            mver();

            shadow_hair[0] = shadow_hair[1];
        }
        else if (shadow_eyes[1] != shadow_eyes[0])
        {
            setcolor(shadow_eyes[1] ? GREEN : WHITE);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            setlinestyle(SOLID_LINE, EMPTY_FILL, 3);

            mocultar();
            rectangle(getmaxx() / 2, 200, getmaxx() / 2 + 150, 239);
            outtextxy(getmaxx() / 2 + 55, 203, "Ojos");
            mver();

            shadow_eyes[0] = shadow_eyes[1];
        }
        else if (shadow_jacket[1] != shadow_jacket[0])
        {
            setcolor(shadow_jacket[1] ? GREEN : WHITE);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            setlinestyle(SOLID_LINE, EMPTY_FILL, 3);

            mocultar();
            rectangle(getmaxx() / 2, 250, getmaxx() / 2 + 150, 289);
            outtextxy(getmaxx() / 2 + 20, 253, "Chaqueta");
            mver();

            shadow_jacket[0] = shadow_jacket[1];
        }
        else if (shadow_jacket2[1] != shadow_jacket2[0])
        {
            setcolor(shadow_jacket2[1] ? GREEN : WHITE);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            setlinestyle(SOLID_LINE, EMPTY_FILL, 3);

            mocultar();
            rectangle(getmaxx() / 2, 300, getmaxx() / 2 + 150, 339);
            outtextxy(getmaxx() / 2 + 25, 303, "Hombro");
            mver();

            shadow_jacket2[0] = shadow_jacket2[1];
        }
        else if (shadow_jean[1] != shadow_jean[0])
        {
            setcolor(shadow_jean[1] ? GREEN : WHITE);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            setlinestyle(SOLID_LINE, EMPTY_FILL, 3);

            mocultar();
            rectangle(getmaxx() / 2, 350, getmaxx() / 2 + 150, 389);
            outtextxy(getmaxx() / 2 + 23, 353, "Pantalon");
            mver();

            shadow_jean[0] = shadow_jean[1];
        }
        else if (shadow_shoes[1] != shadow_shoes[0])
        {
            setcolor(shadow_shoes[1] ? GREEN : WHITE);
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            setlinestyle(SOLID_LINE, EMPTY_FILL, 3);

            mocultar();
            rectangle(getmaxx() / 2, 400, getmaxx() / 2 + 150, 439);
            outtextxy(getmaxx() / 2 + 25, 403, "Zapatos");
            mver();
            shadow_shoes[0] = shadow_shoes[1];
        }
    } while (mclick() == 0);

    xpos = mxpos(1);
    ypos = mypos(1);

    while (mclick() != 0)
        ;

    if (isInside(xpos, ypos, 509, 432, 630, 471))
    {
        nextFrame();
        House_Designer();
        House();
        return;
    }
    else if (isInside(xpos, ypos, 9, 432, 88, 471))
        return;
    else if (isInside(xpos, ypos, getmaxx() / 2, 100, getmaxx() / 2 + 150, 139))
    {
        setlinestyle(SOLID_LINE, SOLID_FILL, 1);
        player.skin.skinColor = player.skin.skinColor == LIGHTGRAY ? BROWN : LIGHTGRAY;
        Avatar(50, 125, &player.skin);
    }

    else if (isInside(xpos, ypos, getmaxx() / 2, 150, getmaxx() / 2 + 150, 189))
    {
        setlinestyle(SOLID_LINE, SOLID_FILL, 1);

        if (player.skin.hairColor == WHITE)
            player.skin.hairColor = BLACK;
        else
            player.skin.hairColor++;

        Avatar(50, 125, &player.skin);
    }

    else if (isInside(xpos, ypos, getmaxx() / 2, 200, getmaxx() / 2 + 150, 239))
    {
        setlinestyle(SOLID_LINE, SOLID_FILL, 1);

        if (player.skin.eyesColor == WHITE - 1)
            player.skin.eyesColor = BLACK;
        else
            player.skin.eyesColor++;

        Avatar(50, 125, &player.skin);
    }

    else if (isInside(xpos, ypos, getmaxx() / 2, 250, getmaxx() / 2 + 150, 289))
    {
        setlinestyle(SOLID_LINE, SOLID_FILL, 1);

        if (player.skin.jacketColor == WHITE)
            player.skin.jacketColor = BLACK;
        else
            player.skin.jacketColor++;

        Avatar(50, 125, &player.skin);
    }

    else if (isInside(xpos, ypos, getmaxx() / 2, 300, getmaxx() / 2 + 150, 339))
    {
        setlinestyle(SOLID_LINE, SOLID_FILL, 1);

        if (player.skin.jacketColorSecond == WHITE)
            player.skin.jacketColorSecond = BLACK;
        else
            player.skin.jacketColorSecond++;

        Avatar(50, 125, &player.skin);
    }

    else if (isInside(xpos, ypos, getmaxx() / 2, 350, getmaxx() / 2 + 150, 389))
    {
        setlinestyle(SOLID_LINE, SOLID_FILL, 1);

        if (player.skin.jeanColor == WHITE)
            player.skin.jeanColor = BLACK;
        else
            player.skin.jeanColor++;

        Avatar(50, 125, &player.skin);
    }

    else if (isInside(xpos, ypos, getmaxx() / 2, 400, getmaxx() / 2 + 150, 439))
    {
        setlinestyle(SOLID_LINE, SOLID_FILL, 1);

        if (player.skin.shoeColor == WHITE)
            player.skin.shoeColor = BLACK;
        else
            player.skin.shoeColor++;

        Avatar(50, 125, &player.skin);
    }
    CharacterMenu();
}

void House_Designer(void)
{
    char message[100];
    mocultar();
    setlinestyle(SOLID_LINE, SOLID_FILL, 1);
    BedRoom(&Rooms[player.currentNation]);
    Avatar(getmaxx() / 2, 200, &player.skin);
    ShowMessageDialog(351, 465);

    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
    setlinestyle(SOLID_LINE, EMPTY_FILL, 3);

    setfillcolor(WHITE);
    rectangle(25, 50, 180, 90);
    bar(25, 50, 180, 90);
    outtextxy(25, 55, "    Dormir ");

    rectangle(25, 100, 180, 140);
    bar(25, 100, 180, 140);
    outtextxy(25, 105, "    Viajar   ");

    rectangle(25, 150, 180, 190);
    bar(25, 150, 180, 190);
    outtextxy(25, 155, "   Cerrar   ");

    if (player.currentNation == Nicaragua && player.nation == Nicaragua)
    {
        rectangle(25, 200, 180, 240);
        bar(25, 200, 180, 240);
        outtextxy(25, 205, " Ir a la UNI ");
    }

    if(player.currentNation == player.nation)
    {
        settextstyle(SMALL_FONT, HORIZ_DIR, 6);
        sprintf(message, "%s: Oh! que lindo dia, %cQue podria hacer...", player.name, 168);
        outtextxy(25, 380, message);

        outtextxy(25, 395, "hoy?. Seria divertido conocer el mundo");
        outtextxy(25, 425, "");
    }
    else
    {
        settextstyle(SMALL_FONT, HORIZ_DIR, 6);
        sprintf(message, "%s: Wow que bonito pais, estaria bien visitar", player.name, 168);
        outtextxy(25, 380, message);

        outtextxy(25, 395, "algun otro...");
        outtextxy(25, 425, "");
    }
    

    mver();
}

void House(void)
{
    bool shadow_option[4][2] = {{true, false}, {true, false}, {true, false}, {true, false}};
    int buttons[4][4] = {{25, 50, 180, 90}, {25, 100, 180, 140}, {25, 150, 180, 190}, {25, 200, 180, 240}};
    int i;
    char message[50];

    do
    {
        for (i = 0; i < 4; i++)
        {
            if (minlimit(1, buttons[i][0], buttons[i][1], buttons[i][2], buttons[i][3]))
                shadow_option[i][1] = true;
            else
                shadow_option[i][1] = false;
        }

        if (player.currentNation != Nicaragua || player.nation != Nicaragua)
            shadow_option[3][1] = shadow_option[3][0] = false;

        if (shadow_option[0][0] != shadow_option[0][1])
        {
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            setcolor(BLACK);
            setfillcolor(shadow_option[0][1] ? LIGHTGREEN : WHITE);
            mocultar();
            rectangle(25, 50, 180, 90);
            bar(25, 50, 180, 90);
            outtextxy(25, 55, "    Dormir ");
            mver();
            shadow_option[0][0] = shadow_option[0][1];
        }
        else if (shadow_option[1][0] != shadow_option[1][1])
        {
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            setcolor(BLACK);
            setfillcolor(shadow_option[1][1] ? LIGHTGREEN : WHITE);
            mocultar();
            rectangle(25, 100, 180, 140);
            bar(25, 100, 180, 140);
            outtextxy(25, 105, "    Viajar   ");
            mver();
            shadow_option[1][0] = shadow_option[1][1];
        }
        else if (shadow_option[2][0] != shadow_option[2][1])
        {
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            setcolor(BLACK);
            setfillcolor(shadow_option[2][1] ? LIGHTGREEN : WHITE);
            mocultar();
            rectangle(25, 150, 180, 190);
            bar(25, 150, 180, 190);
            outtextxy(25, 155, "   Cerrar   ");
            mver();
            shadow_option[2][0] = shadow_option[2][1];
        }
        else if (shadow_option[3][0] != shadow_option[3][1])
        {
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            setcolor(BLACK);
            setfillcolor(shadow_option[3][1] ? LIGHTGREEN : WHITE);
            mocultar();
            rectangle(25, 200, 180, 240);
            bar(25, 200, 180, 240);
            outtextxy(25, 205, " Ir a la UNI ");
            mver();
            shadow_option[3][0] = shadow_option[3][1];
        }
    } while (mclick() == 0);

    xpos = mxpos(1);
    ypos = mypos(1);

    while (mclick() != 0)
        ;
    if (shadow_option[0][1])
    {
        mocultar();
        BedRoom(&Rooms[6]);
        mver();

        Pause();

        setlinestyle(SOLID_LINE, SOLID_FILL, 1);

        mocultar();
        House_Designer();
        mver();
    }
    else if (shadow_option[1][1])
    {
        nextFrame();
        Travel_Designer();
        Travel();
        nextFrame();
        ShowMessageDialog(433, 465);
        setcolor(BLACK);
        if(player.currentNation == player.nation)
            outtextxy(19, 435, "Volviendo a tu hogar... Presione una tecla.");
        else
            outtextxy(19, 435, "Yendo a la habitacion... Presione una tecla.");
        Pause();
        House_Designer();
    }
    else if (shadow_option[2][1])
    {
        nextFrame();
        return;
    }
    else if (shadow_option[3][1])
    {
        settextstyle(SMALL_FONT, HORIZ_DIR, 6);
        setlinestyle(SOLID_LINE, SOLID_FILL, 1);
        mocultar();
        RigobertoLopezPerez(1);
        Avatar(100, 200, &player.skin);
        ShowMessageDialog(351, 465);
        outtextxy(25, 395, "Ya estamos aca, el edificio es de 5 pisos mi aula esta");
        outtextxy(25, 410, "en el segundo. Ire a clases esperame aca");
        mver();
        getch();

        settextstyle(SMALL_FONT, HORIZ_DIR, 6);
        setlinestyle(SOLID_LINE, SOLID_FILL, 1);
        mocultar();
        RigobertoLopezPerez(0);
        ShowMessageDialog(351, 465);
        sprintf(message, "Esperando que %s termine su clase...", player.name);
        outtextxy(25, 395, message);
        outtextxy(25, 410, "Pulsa una tecla para continuar");
        mver();
        getch();

        settextstyle(SMALL_FONT, HORIZ_DIR, 6);
        setlinestyle(SOLID_LINE, SOLID_FILL, 1);
        mocultar();
        Avatar(400, 200, &player.skin);
        ShowMessageDialog(351, 465);
        outtextxy(25, 395, "       Ya estoy aqui, tarde mucho?...");
        outtextxy(25, 410, "   Vamos a casa, nos dejaron un proyecto");
        mver();
        getch();

        settextstyle(SMALL_FONT, HORIZ_DIR, 6);
        setlinestyle(SOLID_LINE, SOLID_FILL, 1);
        mocultar();
        RigobertoLopezPerez(0);
        Avatar(200, 200, &player.skin);
        ShowMessageDialog(351, 465);
        outtextxy(25, 395, " Eh? Te interesa el proyecto?, Bueno nos dejaron ");
        outtextxy(25, 410, " hacer una animacion y la proxima sera simular una");
        outtextxy(25, 425, " version de Windows antigua haha... todo en Turbo C");
        mver();
        getch();

        House_Designer();
    }

    House();
}

void Pause(void)
{
    while (mclick() == 0)
        if (kbhit())
        {
            getch();
            break;
        }
    while (mclick() != 0)
        ;
}

void Travel_Designer(void)
{
    Skin recepcionist;
    recepcionist.skinColor = rand() % 2 == 0 ? BROWN : LIGHTGRAY;
    recepcionist.hairColor = rand() % 15;
    recepcionist.eyesColor = rand() % 14;
    recepcionist.jacketColor = rand() % 2 == 0 ? WHITE : LIGHTGRAY;
    recepcionist.jacketColorSecond = rand() % 2 == 0 ? LIGHTGRAY : DARKGRAY;
    recepcionist.jeanColor = rand() % 2 == 0 ? LIGHTGRAY : WHITE;
    recepcionist.shoeColor = BLACK;

    mocultar();
    if(player.currentNation != USA)
    {
        draw_Airport();
        Avatar(10, 250, &player.skin);
        ShowMessageDialog(433, 465);
        settextstyle(SMALL_FONT, HORIZ_DIR, 6);
        setcolor(BLACK);
        outtextxy(19, 435, "Hemos llegado al aereopuerto. Presiona una tecla para continuar");
        mver();
        Pause();
        nextFrame();
    }
        

    

    mocultar();
    RecepcionCompleta(0, 0);
    setcolor(BLACK);
    outtextxy(315, 25, "Recepcionista");
    Avatar(325, 50, &recepcionist);
    Avatar(500, 250, &player.skin);
    ShowMessageDialog(433, 465);
    setcolor(BLACK);
    outtextxy(19, 435, "Estamos en la recepcion del aereopuerto. Escoge una accion.");

    setfillcolor(WHITE);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, THICK_WIDTH);
    rectangle(25, 50, 200, 90);
    bar(25, 50, 200, 90);
    outtextxy(25, 55, "Llenar papeles");

    rectangle(25, 100, 200, 140);
    bar(25, 100, 200, 140);
    outtextxy(25, 105, "Volver a casa");

    mver();
}

void Travel(void)
{
    bool shadow_option[4][2] = {{true, false}, {true, false}, {true, false}, {true, false}};
    int buttons[4][4] = {{25, 50, 200, 90}, {25, 100, 200, 140}, {25, 150, 180, 190}, {25, 200, 180, 240}};
    int i;

    mver();
    do
    {
        for (i = 0; i < 2; i++)
        {
            if (minlimit(1, buttons[i][0], buttons[i][1], buttons[i][2], buttons[i][3]))
                shadow_option[i][1] = true;
            else
                shadow_option[i][1] = false;
        }

        if (shadow_option[0][0] != shadow_option[0][1])
        {
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            setcolor(BLACK);
            setfillcolor(shadow_option[0][1] ? LIGHTGREEN : WHITE);
            mocultar();
            rectangle(buttons[0][0], buttons[0][1], buttons[0][2], buttons[0][3]);
            bar(buttons[0][0], buttons[0][1], buttons[0][2], buttons[0][3]);
            outtextxy(25, 55, "Llenar papeles");
            mver();
            shadow_option[0][0] = shadow_option[0][1];
        }
        else if (shadow_option[1][0] != shadow_option[1][1])
        {
            settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
            setcolor(BLACK);
            setfillcolor(shadow_option[1][1] ? LIGHTGREEN : WHITE);
            mocultar();
            rectangle(buttons[1][0], buttons[1][1], buttons[1][2], buttons[1][3]);
            bar(buttons[1][0], buttons[1][1], buttons[1][2], buttons[1][3]);
            outtextxy(25, 105, "Volver a casa");
            mver();
            shadow_option[1][0] = shadow_option[1][1];
        }
    } while (mclick() == 0);

    xpos = mxpos(1);
    ypos = mypos(1);

    while (mclick() != 0);

    if (shadow_option[0][1])
    {
        fill_out_papers_designer();
        fill_out_papers();

        animation_mundi(0,1);

        if(flightScale)
            animation_mundi(1,2);

        mocultar();
        if(player.currentNation == Nicaragua)
        {
            nextFrame();
            environment(250);
            Radar(100,10,directionRadar);
        }
        

        nextFrame();
        draw_Airport();
        
        if(player.currentNation != USA && player.currentNation != Argentina)
            landing();
        else
        {
            mver();
            ShowMessageDialog(433, 465);
            setcolor(BLACK);
            outtextxy(19, 435, "Hemos llegado!. Presiona una tecla");
            Pause();
            mocultar();
        }
        mver();
        return;
    }
    else if (shadow_option[1][1])
        return;

    Travel();
}

void fill_out_papers_designer(void)
{
    int flagsPos[4][2] = {{170, 310}, {250, 310}, {330, 310}, {410, 310}};
    int i;
    string text = NULL;

    setfillcolor(WHITE);

    mocultar();
    setlinestyle(SOLID_LINE, SOLID_FILL, NORM_WIDTH);
    bar(150, 100, 500, 480);
    rectangle(150, 100, 500, 480);
    setlinestyle(SOLID_LINE, SOLID_FILL, THICK_WIDTH);
    rectangle(160, 110, 490, 480);
    setlinestyle(SOLID_LINE, SOLID_FILL, NORM_WIDTH);

    outtextxy(165,120," Aereopuerto Nacional de");
    switch (player.currentNation)
    {
        case Spain:
            sprintf(text,"Espa%ca",164);
            outtextxy(165,160,text);
            break;
        case Brazil:
            outtextxy(165,160," Brazil");
            break;
        case Argentina:
            outtextxy(165,160," Argentina");
            break;
        case USA:
            outtextxy(165,160," Estados Unidos");
            break;
        case Nicaragua:
        default:
            outtextxy(165,160," Nicaragua");
            break;
    }

    line(160, 200, 490, 200);
    sprintf(text,"Nombre: %s",player.name);
    outtextxy(165,210,text);
    outtextxy(165,250,"Nacionalidad: ");

    draw_flag(player.nation,320,250);
    setcolor(BLACK);
    line(160, 300, 490, 300);
    for (i = 0; i < 4; i++)
    {
        draw_flag(i == player.currentNation ? 4 : i, flagsPos[i][0], flagsPos[i][1]);
        AvailableCountrys[i] = i == player.currentNation ? 4 : i;
    }
    setcolor(BLACK);
    line(160, 350, 490, 350);

    rectangle(180,360,340,400);
    outtextxy(200,365,"Terminar");

    CountrySelected = 0;
    mver();

    
}

void fill_out_papers(void)
{
    int flagsPos[4][2] = {{170, 310}, {250, 310}, {330, 310}, {410, 310}};
    int i;
    while (mclick() == 0);
    xpos = mxpos(1);
    ypos = mypos(1);
    while (mclick() != 0);
    for(i = 0; i < 4; i++)
    {
        setlinestyle(SOLID_LINE, SOLID_FILL, THICK_WIDTH);
        setcolor(WHITE);
        if(isInside(xpos,ypos,flagsPos[i][0],flagsPos[i][1],flagsPos[i][0]+60,flagsPos[i][1]+30))
        {
            setlinestyle(SOLID_LINE, SOLID_FILL, THICK_WIDTH);
            CountrySelected = i;
            setcolor(LIGHTGREEN);
        }
        mocultar();
        rectangle(flagsPos[i][0],flagsPos[i][1],flagsPos[i][0]+60,flagsPos[i][1]+30);
        mver();
    }

    if(isInside(xpos,ypos,180,360,340,400))
    {
        mocultar();
        nextFrame();
        
        if(player.currentNation != USA && player.currentNation != Argentina)
        {
            draw_Airport();
            takeOff();
        }
            
        nextFrame();
        mundi();
        convertRoute(player.currentNation,AvailableCountrys[CountrySelected]);

        player.currentNation = AvailableCountrys[CountrySelected];
        mver();
        return;
    }

    fill_out_papers();
}

void convertRoute(int source, int destination)
{
    flightScale = false;
    switch (source)
    {
        case Nicaragua:
            switch (destination)
            {
                case Spain:
                    set_airline(&tours[0],NIC_US);
                    set_airline(&tours[1],US_ES);
                    flightScale = true;
                    break;
                case Argentina:
                    set_airline(&tours[0],NIC_AR);
                    break;
                case USA:
                    set_airline(&tours[0],NIC_US);
                    break;
                case Brazil:
                default:
                    set_airline(&tours[0],NIC_BR);
                    break;
            }
            break;
        case Spain:
            switch (destination)
            {
                case Nicaragua:
                    set_airline(&tours[0],ES_US);
                    set_airline(&tours[1],US_NIC);
                    directionRadar = US_NIC;
                    flightScale = true;
                    break;
                case Argentina:
                    set_airline(&tours[0],ES_BR);
                    set_airline(&tours[1],BR_AR);
                    flightScale = true;
                    break;
                case USA:
                    set_airline(&tours[0],ES_US);
                    break;
                case Brazil:
                default:
                    set_airline(&tours[0],ES_BR);
                    break;
            }
            break;
        case USA:
            switch (destination)
            {
                case Spain:
                    set_airline(&tours[0],US_ES);
                    break;
                case Argentina:
                    set_airline(&tours[0],US_NIC);
                    set_airline(&tours[1],NIC_AR);
                    flightScale = true;
                    break;
                case Nicaragua:
                    set_airline(&tours[0],US_NIC);
                    directionRadar = US_NIC;
                    break;
                case Brazil:
                default:
                    set_airline(&tours[0],US_BR);
                    break;
            }
            break;
        case Argentina:
            switch (destination)
            {
                case Spain:
                    set_airline(&tours[0],AR_BR);
                    set_airline(&tours[1],BR_ES);
                    flightScale = true;
                    break;
                case Nicaragua:
                    set_airline(&tours[0],AR_NIC);
                    directionRadar = AR_NIC;
                    break;
                case USA:
                    set_airline(&tours[0],AR_NIC);
                    set_airline(&tours[0],NIC_US);
                    flightScale = true;
                    break;
                case Brazil:
                default:
                    set_airline(&tours[0],AR_BR);
                    break;
            }
            break;
        case Brazil:
        default:
            switch (destination)
            {
                case Spain:
                    set_airline(&tours[0],BR_ES);
                    break;
                case Argentina:
                    set_airline(&tours[0],BR_AR);
                    break;
                case USA:
                    set_airline(&tours[0],BR_US);
                    break;
                case Nicaragua:
                default:
                    set_airline(&tours[0],BR_NIC);
                    directionRadar = BR_NIC;
                    break;
            }
            break;
    }
}

void draw_Airport(void)
{
    switch (player.currentNation)
    {
    case Brazil:
        Airport4(rand() % 2);
        break;
    case Spain:
        Airport3(0, 0, rand() % 2);
        break;
    case Argentina:
        Airport2(0, 0, rand() % 2);
        break;
    case USA:
        Airport1(0, 0, rand() % 2);
        break;
    case Nicaragua:
    default:
        Airport5(rand() % 2);
        break;
    }
}

void InformationScreen(void)
{
    int i;
    int tab[10] = {0, 186, 274, 186, 293, 210, 274, 234, 0, 234};
    char *developers[6] = {"Marcel Emmanuel Diaz Largaespada 2020-1384U", "Gabriel Alejandro Ortiz Amador 2020-0325U", "Luis Miguel Pineda Joseph 2020-0251U", "Engel Gabriel Reyes Moreno 2020-0505U", "Obed Isai Rios Solano 2020-0331U", "Ronaldo Fabian Roman Arauz 2020-0375U"};

    mocultar();
    setfillcolor(WHITE);
    bar(0, 0, getmaxx(), getmaxy());

    setcolor(DARKGRAY);
    setlinestyle(SOLID_LINE, EMPTY_FILL, 1);
    setfillcolor(DARKGRAY);
    fillpoly(5, tab);
    bar(0, 106, 640, 158);

    setcolor(WHITE);

    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 5);
    outtextxy(40, 106, "GEOMETRIA COMPUTACIONAL");

    outtextxy(10, 184, "TURBO C 2.0");

    setcolor(DARKGRAY);

    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
    outtextxy(40, 40, "Universidad Nacional de Ingenieria");

    settextstyle(SMALL_FONT, HORIZ_DIR, 7);
    for (i = 0; i < 3; i++)
        outtextxy(20, 260 + i, "Desarrolladores:");

    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    for (i = 0; i < 6; i++)
        outtextxy(20, 300 + i * 20, developers[i]);

    setfillcolor(LIGHTGRAY);
    setcolor(WHITE);
    logo_uni(420, 350);
    mver();

    Pause();
}

void logo_uni(int x, int y)
{
    int part1[18] = {0, 0, 34, 0, 34, 85, 81, 86, 81, 43, 115, 43, 115, 121, 0, 121, 0, 0};
    int part2[26] = {42, 0, 42, 78, 74, 78, 74, 35, 122, 35, 122, 121, 198, 121, 198, 45, 161, 45, 161, 84, 154, 84, 154, 0, 42, 0};
    int i;

    for (i = 0; i < 26; i++)
    {
        if (i < 18)
            part1[i] += i % 2 == 0 ? x : y;
        part2[i] += i % 2 == 0 ? x : y;
    }

    fillpoly(9, part1);
    fillpoly(13, part2);
    bar(161 + x, 0 + y, 198 + x, 36 + y);
    rectangle(161 + x, 0 + y, 198 + x, 36 + y);
}

void nextFrame(void)
{
    int i;
    for (i = 0; i < 30; i++)
    {
        mocultar();
        printf("\n");
        mver();
        delay(300);
    }
    cleardevice();
}

void changeNation(int nation)
{
    setlinestyle(SOLID_LINE, EMPTY_FILL, 3);
    setcolor(BLACK);
    rectangle(75, 150, 135, 180);
    rectangle(175, 150, 235, 180);
    rectangle(275, 150, 335, 180);
    rectangle(375, 150, 435, 180);
    rectangle(475, 150, 535, 180);
    setcolor(LIGHTGREEN);
    mocultar();
    if (nation == Nicaragua)
        rectangle(75, 150, 135, 180);
    else if (nation == Brazil)
        rectangle(175, 150, 235, 180);
    else if (nation == Spain)
        rectangle(275, 150, 335, 180);
    else if (nation == Argentina)
        rectangle(375, 150, 435, 180);
    else if (nation == USA)
        rectangle(475, 150, 535, 180);
    mver();
    player.currentNation = player.nation = nation;
}

bool isInside(int x0, int y0, int x1, int y1, int x2, int y2)
{
    if ((x0 >= x1) && (x0 <= x2) && (y0 >= y1) && (y0 <= y2))
        return true;
    return false;
}

void InitializeGraphic(void)
{
    int mode = DETECT, gmode;
    initgraph(&mode, &gmode, "c:\\tc20\\bin");
}