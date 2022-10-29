#include"Vec3.h"
#include<iostream>
namespace Matrix
{
double check(double a)
{
    a*=2;
    return a;
}
void Matrix_Multiplication(int row1,int collumn1,int row2,int collumn2)
{
    double mat1[4][4]={(1,1)};
    double mat2[4][1]={(1,1)};
    double MAT[4][1]={0};
    if(collumn1!=row2)
    return;
    for(int i=0;i<row1;i++)
    {
        for(int j=0;j<collumn2;j++)
        {
        for(int k=0;k<collumn1;k++)
        MAT[i][j]+=mat1[i][k]*mat2[k][j];
        std::cout<<MAT[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

}
};
