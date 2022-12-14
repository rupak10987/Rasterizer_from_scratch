#ifndef MODEL_H
#define MODEL_H
#include"Vec3.h"
class Model
{
public:
    Model();
    Model(char* filepath);
    int Num_Verticies;//num of distinct positions in xyz space
    int Num_Indicies;//num of faces
    double* Verticies;
    int* Indicies;
    double* cols;
    double *Face_Normals;
    virtual ~Model();
    class Vec3 Global_Pos;
    class Vec3 Rotation;
    class Vec3 Scale;

protected:

private:
    void load_model(char* str);
};

#endif // MODEL_H
