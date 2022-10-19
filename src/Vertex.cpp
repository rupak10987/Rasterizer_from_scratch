#include "Vertex.h"

Vertex::Vertex()
{
    //ctor
    this->Pos.x=0;
    this->Pos.y=0;
    this->Pos.z=0;
    this->Vertex_Col.r=255;
    this->Vertex_Col.g=255;
    this->Vertex_Col.b=255;
}
Vertex::Vertex(class Vec3 mpos,class Col mcol)
{
    //ctor
    this->Pos=mpos;
    this->Vertex_Col=mcol;
}
Vertex::Vertex(double x,double y,double z,char col)
{
    //ctor
    this->Pos.x=x;
    this->Pos.y=y;
    this->Pos.z=z;
    if(col=='r')
    {
        this->Vertex_Col.r=255;
        this->Vertex_Col.g=0;
        this->Vertex_Col.b=0;
    }
    else if(col=='g')
    {
        this->Vertex_Col.r=0;
        this->Vertex_Col.g=255;
        this->Vertex_Col.b=0;
    }
    else if(col=='g')
    {
        this->Vertex_Col.r=0;
        this->Vertex_Col.g=0;
        this->Vertex_Col.b=255;
    }
}

Vertex::Vertex(double x,double y,double z,class Col col)
{
    //ctor
    this->Pos.x=x;
    this->Pos.y=y;
    this->Pos.z=z;
    this->Vertex_Col=col;
}

Vertex::~Vertex()
{
    //dtor
}
