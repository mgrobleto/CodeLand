#include <GRAPHICS.H>
#include <MOUSE.H>
#include <conio.h>

typedef struct Point
{
    int x, y;
} Point;

enum coord
{
    x, y
};

/*  
To find orientation of ordered triplet (p, q, r).
The function returns following values
0 --> p, q and r are colinear
1 --> Clockwise
2 --> Counterclockwise 
*/

int orientation(Point * p, Point * q, Point * r)
{
    long int val = (q->y - p->y) * (r->x - q->x) - (q->x - p->x) * (r->y - q->y);

    if (val == 0)
        return 0;             /* colinear */

    return (val > 0) ? 1 : 2; /* clock or counterclock wise */
}

/* Prints convex hull of a set of n points. */
void convexHull(Point points[], int n)
{
    /* Initialize Result */
    int hull[50][2];
    int hull_count = 0, i;
    /* Find the leftmost point */
    int l = 0, p, q;

    /* There must be at least 3 points */
    if (n < 3)
        return;
    
    for (i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;

    /* Start from leftmost point, keep moving counterclockwise
    until reach the start point again. This loop runs O(h)
    times where h is number of points in result or output. */
    p = l;
    do
    {
        /* Add current point to result */
        hull[hull_count][x] = points[p].x;
        hull[hull_count][y] = points[p].y;
        hull_count++;

        /* Search for a point 'q' such that orientation(p, q,
        x) is counterclockwise for all points 'x'. The idea
        is to keep track of last visited most counterclock-
        wise point in q. If any point 'i' is more counterclock-
        wise than q, then update q. */
        q = (p + 1) % n;
        for (i = 0; i < n; i++)
        {
            /* If i is more counterclockwise than current q, then
            update q */
            if (orientation(&points[p], &points[i], &points[q]) == 2)
                q = i;
        }

        /* Now q is the most counterclockwise with respect to p
        Set p as q for next iteration, so that q is added to
        result 'hull' */
        p = q;

    } while (p != l); /* While we don't come to first point */

    hull[hull_count][x] = hull[0][x];
    hull[hull_count][y] = hull[0][y];
    hull_count++;

    drawpoly(hull_count, *hull);
}

void clearcanvas(void)
{
    struct fillsettingstype settings;
    getfillsettings(&settings);
    setfillstyle(SOLID_FILL, WHITE);
    bar(0,0,getmaxx()/2 + 3,getmaxy()/2 + 3);
    setfillstyle(settings.pattern, settings.color);
}

void initializeGraph(void)
{
    int driver = DETECT, mode;
    initgraph(&driver, &mode, "c:\\tc20\\bin");
    mlimit(1,0,0,getmaxx()/2,getmaxy()/2);
    setfillstyle(SOLID_FILL,LIGHTBLUE);
    bar(0,0,getmaxx(),getmaxy());

    setfillstyle(SOLID_FILL,DARKGRAY);
    bar(0,0,getmaxx()/2 + 5,getmaxy()/2 + 5);

    settextstyle(DEFAULT_FONT,HORIZ_DIR,7);
    outtextxy(10,300,"CIERRE");
    outtextxy(10,400,"    CONVEXO");
    setcolor(DARKGRAY);
    outtextxy(14,304,"CIERRE");
    outtextxy(14,404,"    CONVEXO");

    setcolor(LIGHTGRAY);
    outtextxy(12,302,"CIERRE");
    outtextxy(12,402,"    CONVEXO");
    clearcanvas();

    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
    outtextxy(360,10,"Click izq.");
    outtextxy(360,40,"para agregar punto");
    outtextxy(360,100,"Click der.");
    outtextxy(360,130,"para usar algoritmo");
    outtextxy(360,200,"Presiona una tecla");
    outtextxy(360,230,"para cerrar");
    
    setcolor(DARKGRAY);
    outtextxy(362,12,"Click izq.");
    outtextxy(362,42,"para agregar punto");
    outtextxy(362,102,"Click der.");
    outtextxy(362,132,"para usar algoritmo");
    outtextxy(362,202,"Presiona una tecla");
    outtextxy(362,232,"para cerrar");

    setcolor(LIGHTGRAY);
    outtextxy(361,11,"Click izq.");
    outtextxy(361,41,"para agregar punto");
    outtextxy(361,101,"Click der.");
    outtextxy(361,131,"para usar algoritmo");
    outtextxy(361,201,"Presiona una tecla");
    outtextxy(361,231,"para cerrar");

    clearcanvas();


    mver();
}

/* Driver program to test above functions */
 int main()
{
    Point points[20];
    int n = 0, click, i;
    initializeGraph();

    for(;1;)
    {
        if(kbhit())
            break;
        while(mclick()==0);
        click = mclick();
        if(click == 1 && n < 50)
        {
            points[n].x = mxpos(1);
            points[n].y = mypos(1);
            n++;
        }
        while(mclick()!=0);

        mocultar();
        if(click == 1 && n < 20)
        {
            setcolor(BLACK);
            setfillstyle(SOLID_FILL, BLACK);
            fillellipse(points[n-1].x,points[n-1].y,2,2);
        } else if (click == 2 && n < 20)
        {
            setcolor(RED);
            convexHull(points,n);

            mver();
            if(kbhit())
                break;
            while(mclick()==0);
            mocultar();
            clearcanvas();
            setcolor(BLACK);
            setfillstyle(SOLID_FILL, BLACK);
            for(i = 0; i < n; i++)
                fillellipse(points[i].x,points[i].y,2,2);
        }
        
        mver();        
    }
    
    closegraph();
    return 0;   
}
