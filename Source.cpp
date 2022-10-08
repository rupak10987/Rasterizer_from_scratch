#include<graphics.h>
#include<iostream>
#include"Vec3.h"
#include"Light_Source.h"
#include"Col.h"
void draw_line(class Vec3 P,class Vec3 P1,class Col col);
int main()
{
    int win=initwindow(500,500,(const char*)"RASTERIZER");
    setcurrentwindow(win);
class Vec3 p(1,1,0);
class Vec3 p1(200,200,0);
class Col c(255,255,0);
    draw_line(p,p1,c);
    getch();
    closegraph();
    return 0;
}
void draw_line(class Vec3 P,class Vec3 P1,class Col col)
{
    double m=P.clac_xy_slope(P.Direction_Vec(P1,P));
    double y0=P.y;
    for(int i=P.x;i<P1.x;i++)
    {
        double y=m*i+y0;
        putpixel(i,y,COLOR(col.r,col.g,col.b));
        y0+=m;
    }

}
