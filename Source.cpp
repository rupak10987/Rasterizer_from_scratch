#include<graphics.h>
#include<iostream>
#include<math.h>
#include"Vec3.h"
#include"Light_Source.h"
#include"Col.h"
double Vals[500]={0};
void ineterpolate(class Vec3 P,class Vec3 P1);
void draw_line(class Vec3 P,class Vec3 P1,class Col col);
class Vec3 normalized_to_screen_cord(int X,int Y);
int Win_Width=500;
int Win_Height=500;
int main()
{
    int win=initwindow(Win_Width,Win_Height,(const char*)"RASTERIZER");
    setcurrentwindow(win);
    class Vec3 p(0,0,0);
    class Vec3 p1(10,250,0);
    class Col c(255,255,0);
    draw_line(p,p1,c);
    getch();
    closegraph();
    return 0;
}

void draw_line(class Vec3 P,class Vec3 P1,class Col col)
{

        /*double* ys=*/ineterpolate(P,P1);
        for(int i=P.x;i<P1.x;i++)
        {
        class Vec3 screen_cord;
        screen_cord=normalized_to_screen_cord(i,Vals[i-(int)P.x]);
        putpixel(screen_cord.x,screen_cord.y,COLOR(col.r,col.g,col.b));
        }
};

void ineterpolate(class Vec3 P,class Vec3 P1)
{

if(P.x==P1.x)
{
    Vals[int(P.x)]={P.y};
}
double m=P.clac_xy_slope(P.Direction_Vec(P1,P));
double y=P.y;
for(int i=P.x;i<=P1.x;i++)
{
   Vals[i]=y;
    y+=m;
}
}

class Vec3 normalized_to_screen_cord(int X,int Y)
{
double retx=((double)Win_Width/2.0)+(double)X;
double rety=((double)Win_Height/2.0)-(double)Y;
class Vec3 v(retx,rety,0);
return v;
};
