#include<graphics.h>
#include<iostream>
#include<math.h>
#include"Vec3.h"
#include"Light_Source.h"
#include"Col.h"
double Vals[500]={0};
void ineterpolate(double x0,double y0,double x1,double y1);
void draw_line(class Vec3 P,class Vec3 P1,class Col col);
class Vec3 normalized_to_screen_cord(int X,int Y);
int Win_Width=500;
int Win_Height=500;
int main()
{
    int win=initwindow(Win_Width,Win_Height,(const char*)"RASTERIZER");
    setcurrentwindow(win);
    class Vec3 p(-250,-250,0);
    class Vec3 p1(0,0,0);
    class Col c(255,255,255);
    draw_line(p,p1,c);
    //p.y=50;
    //draw_line(p,p1,c);
    getch();
    closegraph();
    return 0;
}

void draw_line(class Vec3 P,class Vec3 P1,class Col col)
{


        //check if the function is horizontalish or verticalish
        double dx=abs(P1.x-P.x);
        double dy=abs(P1.y-P.y);
        if(dx>dy)//horizontalish
        {
        if(P.x>P1.x)//always goes to right from left
        draw_line(P1,P,col);
        ineterpolate(P.x,P.y,P1.x,P1.y);
        for(int i=P.x;i<P1.x;i++)
        {
        class Vec3 screen_cord;
        screen_cord=normalized_to_screen_cord(i,Vals[i-(int)P.x+(Win_Width/2)]);
std::cout<<screen_cord.x<<", "<<screen_cord.y<<std::endl;
        putpixel(screen_cord.x,screen_cord.y,COLOR(col.r,col.g,col.b));
        }
        }
        else//verticalish just changing dependent to independent & vice versa
        {
        if(P.y>P1.y)//always goes to up from down
        draw_line(P1,P,col);
        ineterpolate(P.y,P.x,P1.y,P1.x);
        for(int i=P.y;i<P1.y;i++)
        {
        class Vec3 screen_cord;
        screen_cord=normalized_to_screen_cord(i,Vals[i-(int)P.y+(Win_Width/2)]);
        std::cout<<screen_cord.x<<", "<<screen_cord.y<<std::endl;
        putpixel(screen_cord.y,screen_cord.x,COLOR(col.r,col.g,col.b));
        }
        }

};

void ineterpolate(double x0,double y0,double x1,double y1)
{

if(x0==x1)
{
    Vals[int(x0)+(Win_Width/2)]={y0};
}
double m=abs(y1-y0)/abs(x1-x0);

double y=y0;
for(int i=x0;i<=x1;i++)
{

   Vals[i+250]=y;
    y=y+m;
}
}

class Vec3 normalized_to_screen_cord(int X,int Y)
{
double retx=((double)Win_Width/2.0)+(double)X;
double rety=((double)Win_Height/2.0)-(double)Y;
class Vec3 v(retx,rety,0);
return v;
};
