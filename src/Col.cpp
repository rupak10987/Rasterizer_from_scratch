#include "Col.h"

Col::Col()
{
    this->r=255;
    this->g=0;
    this->b=200;
}
Col::Col(int r,int g,int b)
{
    this->r=r;
    this->g=g;
    this->b=b;
}
class Col Col:: Mix(class Col A,class Col B,double amount)
{
    A.r=A.r*amount+B.r*(1-amount);
    A.g=A.g*amount+B.g*(1-amount);
    A.b=A.b*amount+B.b*(1-amount);
    return A;
};
Col::~Col()
{
    //dtor
}
