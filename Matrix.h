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
double** Matrix_Multiplication(double**matA,double**matB,int rowA,int collumnA,int rowB,int collumnB)
{
    double **MAT;
    MAT=new double*[rowA];
    for(int i=0;i<rowA;i++)
    MAT[i]=new double[collumnB];
    for(int i=0;i<rowA;i++)
    for(int j=0;j<collumnB;j++)
    MAT[i][j]=0;

    if(collumnA!=rowB)
    {
        return MAT;
    }

    for(int i=0;i<rowA;i++)
    {
        for(int j=0;j<collumnB;j++)
        {
        for(int k=0;k<collumnA;k++)
        MAT[i][j]+=matA[i][k]*matB[k][j];
        }
    }
return MAT;
}
class Vec3 Transform(class Vec3 pos, class Vec3 Scale,class Vec3 Rot,class Vec3 translate)
{
double **scale_mat;
double **rot_mat;
double **Transform_mat;
scale_mat=new double*[4];
rot_mat=new double*[4];//z axis only for now
Transform_mat=new double*[4];
for(int i=0;i<4;i++)
{
    scale_mat[i]=new double[4];
    rot_mat[i]=new double[4];
    Transform_mat[i]=new double[4];
}
double **result_mat=Matrix_Multiplication(rot_mat,scale_mat,4,4,4,4);
result_mat=Matrix_Multiplication(Transform_mat,result_mat,4,4,4,4);
class Vec3 rv(result_mat[0][0],result_mat[0][1],result_mat[0][2]);
return rv;
}
};
//the function will be called like this transform matrix 4by 4 er ekta which will take the parameter
//vec3 as the position and return a vec3 as transforme positon
// transform matrix will also take scale vector(x,y,x), rotation vector(x,y,z),transfomration vector(x,y,z)

