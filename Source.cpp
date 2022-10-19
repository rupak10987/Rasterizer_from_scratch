#include<graphics.h>
#include<iostream>
#include<math.h>
#include"Vec3.h"
#include"Light_Source.h"
#include"Col.h"
double Vals[500]= {0};
void draw_filled_tris(class Vec3 P0,class Vec3 P1,class Vec3 P2,class Col col);
void ineterpolate(double x0,double y0,double x1,double y1);
void draw_line(class Vec3 P,class Vec3 P1,class Col col);
class Vec3 normalized_to_screen_cord(int X,int Y);
int Win_Width=1000;
int Win_Height=1000;
int main()
{
    int win=initwindow(Win_Width,Win_Height,(const char*)"RASTERIZER");
    setcurrentwindow(win);
    class Vec3 p(20,-50,0);
    class Vec3 p1(-50,-100,0);
    class Vec3 p2(30,40,0);
    class Col c(0,255,255);
    class Col c1(255,0,0);
    for(int i=0; i<5; i++)
    {
        p.x+=50;
        p1.x+=50;
        p2.x+=50;
        draw_filled_tris(p,p1,p2,c);
        //draw_line(p,p1,c1);
        //draw_line(p1,p2,c1);
        //draw_line(p2,p,c1);
    }
    getch();
    closegraph();
    return 0;
}


void draw_filled_tris(class Vec3 P0,class Vec3 P1,class Vec3 P2,class Col col)
{
    class Vec3 X_left(0,0,0);
    class Vec3 X_right(0,0,0);
//sorting the points according to their height po lowest p1 mid and p2 highest
    if(P0.y>P1.y)
        draw_filled_tris(P1,P0,P2,col);
    if(P0.y>P2.y)
        draw_filled_tris(P2,P1,P0,col);
    if(P1.y>P2.y)
        draw_filled_tris(P0,P2,P1,col);

//calculate the x's for a y
    for(int i=(int)P0.y; i<(int)P2.y; i++)
    {
//check if i is in between p0-p1 or p1-p2
        if(i>=P0.y && i<=P1.y)//p0-p1
        {
//calculate x for  p0-p1
            double a=(P1.x-P0.x)/(P1.y-P0.y);
            double b=P0.x-(a*P0.y);
            X_left.x=b+a*i;
            X_left.y=i;
        }
        else//p1-p2
        {
//calculate x for p1-p2
            double a=(P2.x-P1.x)/(P2.y-P1.y);
            double b=P1.x-(a*P1.y);
            X_left.x=b+a*i;
            X_left.y=i;
        }
//calculate x for p0-p2
        double a=(P2.x-P0.x)/(P2.y-P0.y);
        double b=P0.x-(a*P0.y);
        X_right.x=b+a*i;
        X_right.y=i;

//draw the horizontal lines
        draw_line(X_left,X_right,col);

    }


}

void draw_line(class Vec3 P,class Vec3 P1,class Col col)
{
    double DX=abs(P1.x-P.x);
    double DY=abs(P1.y-P.y);
    if(DX>DY)//horizontal
    {
        if(P.x>P1.x)//checking if P is smaller than p1 always goes from low to high
        {
            draw_line(P1,P,col);
        }
        else
        {
            double m=(P1.y-P.y)/(P1.x-P.x);// calculating slope
            double yn=P.y;
            double h=0.51;
            for(int i=P.x; i<P1.x; i++)
            {
                Vec3 screen_cord;
                screen_cord=normalized_to_screen_cord(i,(int)yn);
                yn+=m;
                h+=0.01;
                putpixel(screen_cord.x,screen_cord.y,COLOR(col.r,col.g,col.b));
            }
        }
    }
    else//vertical
    {
        if(P.y>P1.y)//checking if P is smaller than p1 always goes from low to high
        {
            draw_line(P1,P,col);
        }
        else
        {
            double m=(P1.x-P.x)/(P1.y-P.y);//calculating slope
            double xn=P.x;
            for(int i=P.y; i<P1.y; i++)
            {
                Vec3 screen_cord;
                screen_cord=normalized_to_screen_cord((int)xn,i);//converting from normal graph cordinate to screen co_ordinate system
                xn+=m;
                putpixel(screen_cord.x,screen_cord.y,COLOR(col.r,col.g,col.b));
            }
        }
    }
}


class Vec3 normalized_to_screen_cord(int X,int Y)
{
    double retx=((double)Win_Width/2.0)+(double)X;
    double rety=((double)Win_Height/2.0)-(double)Y;
    class Vec3 v(retx,rety,0);
    return v;
};
