#include<graphics.h>
#include<iostream>
#include"Vec3.h"
#include"Light_Source.h"
#include"Col.h"
int main()
{
    std::cout<<"hola amigos"<<std::endl;
    class Vec3 A(1,1,1);
    std::cout<<"DOT(A,A)= "<<A.DOT_PRODUCT(A,A)<<std::endl;
    int window=initwindow(500,500,"RASTERIZER");
    setcurrentwindow(window);
    for(int i=-500;i<500;i++)
        for(int j=-500;j<500;j++)
            putpixel(i,j,COLOR(255,0,0));
    getch();
     closegraph();
    return 0;
}
