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
    for(int i=0; i<rowA; i++)
        MAT[i]=new double[collumnB];
    for(int i=0; i<rowA; i++)
        for(int j=0; j<collumnB; j++)
            MAT[i][j]=0;

    if(collumnA!=rowB)
    {
        return MAT;
    }

    for(int i=0; i<rowA; i++)
    {
        for(int j=0; j<collumnB; j++)
        {
            for(int k=0; k<collumnA; k++)
                MAT[i][j]+=matA[i][k]*matB[k][j];
        }
    }
    return MAT;
}
class Vec3 Transform(class Vec3 pos, class Vec3 Scale,class Vec3 Rot,class Vec3 translate)
{
    double **pos_mat;
    pos_mat=new double*[4];
    for(int i=0; i<4; i++)
    {
        pos_mat[i]=new double;
    }
    pos_mat[0][0]=pos.x;
    pos_mat[1][0]=pos.y;
    pos_mat[2][0]=pos.z;
    pos_mat[3][0]=1;



    double **scale_mat;
    double **rot_mat_z;
    double **rot_mat_y;
    double **rot_mat_x;
    double **Transform_mat;
    scale_mat=new double*[4];
    rot_mat_x=new double*[4];//z axis only for now
    rot_mat_y=new double*[4];
    rot_mat_z=new double*[4];
    Transform_mat=new double*[4];
    for(int i=0; i<4; i++)
    {
        scale_mat[i]=new double[4];
        rot_mat_x[i]=new double[4];
        rot_mat_y[i]=new double[4];
        rot_mat_z[i]=new double[4];
        Transform_mat[i]=new double[4];
    }
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            scale_mat[i][j]=0;
            rot_mat_x[i][j]=0;
            rot_mat_y[i][j]=0;
            rot_mat_z[i][j]=0;
            Transform_mat[i][j]=0;
        }

    scale_mat[0][0]=Scale.x;
    scale_mat[1][1]=Scale.y;
    scale_mat[2][2]=Scale.z;
    scale_mat[3][3]=1;

    rot_mat_x[0][0]=1;
    rot_mat_x[1][1]=cos(Rot.x);
    rot_mat_x[1][2]=-sin(Rot.x);
    rot_mat_x[2][1]=sin(Rot.x);
    rot_mat_x[2][2]=cos(Rot.x);
    rot_mat_x[3][3]=1;

    rot_mat_y[0][0]=cos(Rot.y);
    rot_mat_y[0][2]=sin(Rot.y);
    rot_mat_y[1][1]=1;
    rot_mat_y[2][0]=-sin(Rot.y);
    rot_mat_y[2][2]=cos(Rot.y);
    rot_mat_y[3][3]=1;

    rot_mat_z[0][0]=cos(Rot.z);
    rot_mat_z[0][1]=-sin(Rot.z);
    rot_mat_z[1][0]=sin(Rot.z);
    rot_mat_z[1][1]=cos(Rot.z);
    rot_mat_z[2][2]=1;
    rot_mat_z[3][3]=1;

    Transform_mat[0][3]=translate.x;
    Transform_mat[1][3]=translate.y;
    Transform_mat[2][3]=translate.z;
    Transform_mat[3][3]=1;
    Transform_mat[2][2]=1;
    Transform_mat[1][1]=1;
    Transform_mat[0][0]=1;


    double **result_mat;
    result_mat=new double*[4];
    for(int i=0; i<4; i++)
        result_mat[i]=new double[4];

    result_mat=Matrix_Multiplication(rot_mat_x,scale_mat,4,4,4,4);
    result_mat=Matrix_Multiplication(rot_mat_y,result_mat,4,4,4,4);
    result_mat=Matrix_Multiplication(rot_mat_z,result_mat,4,4,4,4);
    result_mat=Matrix_Multiplication(Transform_mat,result_mat,4,4,4,4);

    double **row_vector;
    row_vector=new double*[4];
    for(int i=0; i<4; i++)
        row_vector[i]=new double;

    row_vector=Matrix_Multiplication(result_mat,pos_mat,4,4,4,1);
    class Vec3 rv(row_vector[0][0],row_vector[1][0],row_vector[2][0]);
    return rv;
}
};
//the function will be called like this transform matrix 4by 4 er ekta which will take the parameter
//vec3 as the position and return a vec3 as transforme positon
// transform matrix will also take scale vector(x,y,x), rotation vector(x,y,z),transfomration vector(x,y,z)

