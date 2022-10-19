#ifndef VERTEX_H
#define VERTEX_H
#include"Vec3.h"
#include"Col.h"

class Vertex
{
    public:
        Vertex();
        class Vec3 Pos;
        class Col Vertex_Col;
        virtual ~Vertex();
        Vertex(class Vec3 mpos,class Col mcol);
        Vertex(double x,double y,double z,char col);
        Vertex(double x,double y,double z,class Col col);

    protected:

    private:
};

#endif // VERTEX_H
