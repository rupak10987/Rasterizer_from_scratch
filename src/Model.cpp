#include "Model.h"
#include<../Loader.h>

Model::Model(char* filepath)
{
    //ctor
MESH::load_Array_sizes(filepath,&Num_Verticies,&Num_Indicies);
this->Verticies=new double[Num_Verticies*3];
this->Indicies=new int[Num_Indicies*3];
this->cols=new double[Num_Indicies*3];
MESH::load_obj_data(filepath,Verticies,&Num_Verticies,Indicies,&Num_Indicies,cols);
}


Model::Model()//ann icosphere
{
    //ctor
    this->Num_Indicies=12;//num of faces
    this->Num_Verticies=8;
    double VA[Num_Verticies*3]={-1.00,-1.00,1.00,
                                -1.00,-1.00,-1.00,
                                -1.00,1.00,1.00,
                                -1.00,1.00,-1.00,
                                1.00,-1.00,1.00,
                                1.00,-1.00,-1.00,
                                1.00,1.00,1.00,
                                1.00,1.00,-1.00};

int IA[Num_Indicies*3]={1,2,0,
                        3,6,2,
                        7,4,6,
                        5,0,4,
                        6,0,2,
                        3,5,7,
                        1,3,2,
                        3,7,6,
                        7,5,4,
                        5,1,0,
                        6,4,0,
                        3,1,5};

int ColA[Num_Indicies*3]=  {0,204,65,
                            42,0,204,
                            0,204,65,
                            42,0,204,
                            204,17,0,
                            204,17,0,
                            0,204,65,
                            42,0,204,
                            0,204,65,
                            42,0,204,
                            204,17,0,
                            204,17,0};

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
this->cols=new double[Num_Indicies*3];
for(int i=0;i<Num_Indicies*3;i++)
{
    *(cols+i)=ColA[i];
}
}



Model::~Model()
{
    //dtor

}
