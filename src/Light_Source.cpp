#include "Light_Source.h"

Light_Source::Light_Source()
{
    //ctor
    this->intensity=0.2;
    this->pos.x=1;
    this->pos.y=6;
    this->pos.z=1;
    this->type=point;
}
Light_Source::Light_Source(double intensity,Light_type type,class Vec3 pos)
{
    //ctor
    this->intensity=intensity;
    this->pos=pos;
    this->type=type;
}

Light_Source::~Light_Source()
{
    //dtor
}
