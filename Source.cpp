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
    return 0;
}
