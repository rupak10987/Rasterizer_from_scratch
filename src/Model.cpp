#include "Model.h"

Model::Model(char* str)
{
    //ctor

}
Model::Model()
{
    //ctor
    Num_Indicies=18;
    Num_Verticies=8;
    double VA[24]={-1,1,1,
                    1,1,1,
                    1,-1,1,
                   -1,-1,1,
                   -1,1,2,
                    1,1,2,
                    1,-1,2,
                   -1,-1,2 };
    int IA[24]={};
}
Model::~Model()
{
    //dtor
}
