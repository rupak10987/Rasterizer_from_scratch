#include<graphics.h>
#include<iostream>
#include"Vec3.h"
#include"Light_Source.h"
#include"Col.h"
void draw_line(class Vec3 P,class Vec3 P1,class Col col);
class Vec3 normalized_to_screen_cord(int X,int Y);
int Win_Width=500;
int Win_Height=500;
int main()
{
    int win=initwindow(Win_Width,Win_Height,(const char*)"RASTERIZER");
    setcurrentwindow(win);
    class Vec3 p(0,0,0);
    class Vec3 p1(250,250,0);
    class Vec3 q(0,0,0);
    class Vec3 q1(0,250,0);
    class Vec3 r(0,0,0);
    class Vec3 r1(250,0,0);
    class Col c(255,255,0);
    draw_line(p,p1,c);
    draw_line(q,q1,c);
    draw_line(r,r1,c);
    getch();
    closegraph();
    return 0;
}

void draw_line(class Vec3 P,class Vec3 P1,class Col col)
{
    double m=P.clac_xy_slope(P.Direction_Vec(P1,P));
    double y0=P.y;
    for(int i=P.x; i<P1.x; i++)
    {
        int y=m*i+y0;
        class Vec3 screen_cord;
        screen_cord=normalized_to_screen_cord(i,(int)y);
        putpixel(screen_cord.x,screen_cord.y,COLOR(col.r,col.g,col.b));
        y0+=m;
    }
};

class Vec3 normalized_to_screen_cord(int X,int Y)
{
double retx=((double)Win_Width/2.0)+(double)X;
double rety=((double)Win_Height/2.0)-(double)Y;
class Vec3 v(retx,rety,0);
return v;
};
