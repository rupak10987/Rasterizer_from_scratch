#include "Model.h"

Model::Model(char* str)
{
    //ctor

}
Model::Model()
{
    //ctor
    this->Num_Indicies=4;//num of faces
    this->Num_Verticies=4;
    double VA[12]={0.0,5.0,1.0,
0.8660253882408142,-0.5000000596046448,1.0,
-0.866025447845459,-0.49999991059303284,1.0,
0.0,0.0,3.0};

    int IA[12]=  {0,3,1,
0,1,2,
1,3,2,
2,3,0};

this->Verticies=new double[Num_Verticies*3];
for(int i=0;i<Num_Verticies*3;i++)
{
    *(Verticies+i)=VA[i];
}

this->Indicies=new int[Num_Indicies*3];
for(int i=0;i<Num_Indicies*3;i++)
{
    *(Indicies+i)=IA[i];
}
}
Model::~Model()
{
    //dtor
}
