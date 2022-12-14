#include "Vec3.h"

Vec3::Vec3(double i,double j,double k)
{
    this->x=i;
    this->y=j;
    this->z=k;

}
Vec3::Vec3()
{
    this->x=0.00;
    this->y=0.00;
    this->z=0.00;
}
Vec3::~Vec3()
{

}
class Vec3 Vec3:: Direction_Vec(class Vec3 target,class Vec3 from)
{
    target.x-=from.x;
    target.y-=from.y;
    target.z-=from.z;
    return target;
};

class Vec3 Vec3:: addition_Vec(class Vec3 target,class Vec3 from)
{
    target.x+=from.x;
    target.y+=from.y;
    target.z+=from.z;
    return target;
};
class Vec3 Vec3:: Scaler_Mul_Vec(double a,class Vec3 from)
{
    from.x*=a;
    from.y*=a;
    from.z*=a;
    return from;
};
class Vec3 Vec3:: Scaler_Div_Vec(double a,class Vec3 from)
{
    from.x/=a;
    from.y/=a;
    from.z/=a;
    return from;
};
double Vec3::DOT_PRODUCT(class Vec3* A,class Vec3* B)
{
    return (A->x*B->x)+(A->y*B->y)+(A->z*B->z);
}
double Vec3::DOT_PRODUCT(class Vec3 A,class Vec3 B)
{
    return (A.x*B.x)+(A.y*B.y)+(A.z*B.z);
}
class Vec3 Vec3:: Negate(class Vec3 A)
{
    A.x=-A.x;
    A.y=-A.y;
    A.z=-A.z;
    return A;
}
class Vec3 Vec3::Normalized_Vec(class Vec3 A)
{
    return A.Scaler_Div_Vec(sqrt(A.DOT_PRODUCT(A,A)),A);
}
class Vec3 Vec3:: CROSS_PRODUCT(class Vec3 A,class Vec3 B)
{
    class Vec3 C;
    C.x=A.y*B.z-A.z*B.y;
    C.y=A.z*B.x-A.x*B.z;
    C.z=A.x*B.y-A.y*B.x;
    return C;

}
double Vec3::clac_xy_slope(class Vec3 A)
{
    return A.y/A.x;
}
double Vec3::Length(class Vec3 A)
{
    return sqrt(A.DOT_PRODUCT(A,A));
}
double Vec3::unsigned_angle_between(class Vec3 From,class Vec3 To)
{
    double cos_angle;
    cos_angle=(double)DOT_PRODUCT(From,To)/(double)(Length(From)*Length(To));
    double angle;
    angle=(double)acos(cos_angle)*(180.00/3.1416);
    return angle;
}
