#include"Vec3.h"
#include<iostream>
#include<math.h>
namespace Matrix
{
double check(double a)
{
    a*=2;
    return a;
}
class Vec3 Matrix_Multiplication(double**matA,double**matB,int rowA,int collumnA,int rowB,int collumnB)
{
    double MAT[4][1]={0};
    if(collumnA!=rowB)
    {
        class Vec3 new_vec;
        return new_vec;
    }

    for(int i=0;i<rowA;i++)
    {
        for(int j=0;j<collumnB;j++)
        {
        for(int k=0;k<collumnA;k++)
        MAT[i][j]+=matA[i][k]*matB[k][j];
        }
    }
    class Vec3 new_vec(MAT[0][0],MAT[1][0],MAT[2][0]);
    return new_vec;
}
class Vec3 Transform(class Vec3 pos, class Vec3 Scale,class Vec3 Rot,class Vec3 translate)
{
//scale
double scale_mat[4][4]={{Scale.x,0,0,0},
                        {0,Scale.y,0,0},
                        {0,0,Scale.z,0},
                        {0,0,0,1}};

double rot_mat_z[4][4]={{cos(rot.z),sin(rot.z),0,0},
                        {-sin(rot.z),cos(rot.z),0,0},
                        {0,0,1,0},
                        {0,0,0,1}};
                        Matrix_Multiplication(rot_mat_z,scale_mat,4,4,4,4);
}
};
//the function will be called like this transform matrix 4by 4 er ekta which will take the parameter
//vec3 as the position and return a vec3 as transforme positon
// transform matrix will also take scale vector(x,y,x), rotation vector(x,y,z),transfomration vector(x,y,z)

