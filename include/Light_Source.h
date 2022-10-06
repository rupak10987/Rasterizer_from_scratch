#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H
#include"Vec3.h"
enum Light_type
{
    point,
    ambient,
    directional
};
class Light_Source
{
    public:
        double intensity;
        Light_type type;
        class Vec3 pos;

        Light_Source();
        Light_Source(double intensity,Light_type type,class Vec3 pos);
        virtual ~Light_Source();

    protected:

    private:
};

#endif // LIGHT_SOURCE_H
