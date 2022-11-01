#ifndef MODEL_H
#define MODEL_H

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
        virtual ~Model();

    protected:

    private:
    void load_model(char* str);
};

#endif // MODEL_H
