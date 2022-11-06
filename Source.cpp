#include<graphics.h>
#include<iostream>
#include<math.h>
#include"Vec3.h"
#include"Light_Source.h"
#include"Col.h"
#include"Vertex.h"
#include"Model.h"
#include"Matrix.h"
double **z_buff;
double Vals[500]= {0};
double calculate_light(class Vec3 N,class Vec3 P,class Vec3 V,double s);
double calc_intermedizte_z(int i,class Vec3 P,class Vec3 P1);
double calc_intermedizte_1_by_z(int i,class Vec3 P0,class Vec3 P1);
void render_object(class Model* mod,bool render_faces,bool render_wireframe);
void draw_filled_tris(class Vec3 P0,class Vec3 P1,class Vec3 P2,class Col col);
void ineterpolate(double x0,double y0,double x1,double y1);
void draw_line(class Vec3 P,class Vec3 P1,class Col col);
class Vec3 Project_Vertex(class Vertex A);
class Vec3 View_to_canvas(class Vec3 A);//scales up for the canvas
class Vec3 normalized_to_screen_cord(int X,int Y);
class Vec3 Calculate_Mid_of_triangle(class Vec3 P0,class Vec3 P1,class Vec3 P2);
int Win_Width=500;
int Win_Height=500;
int View_H=2;
int View_W=2;
double View_d=2;
class Light_Source* Lights[3];
int main()
{

z_buff=new double*[Win_Height+1];
for(int i=0;i<=Win_Height;i++)
z_buff[i]=new double[Win_Width+1];
for(int i=0;i<=Win_Height;i++)
for(int j=0;j<=Win_Width;j++)
z_buff[i][j]=9999;

//lights
class Vec3 point_(-4,-4,-4);
class Vec3 ambient_(-4,-4,-4);
class Vec3 direc_(1,1,0.5);
class Light_Source* point_l=new Light_Source(0,point,point_);
class Light_Source* ambient_l=new Light_Source(0.7,ambient,ambient_);
class Light_Source* directional_l=new Light_Source(0.25,directional,direc_);

Lights[0]=point_l;
Lights[1]=ambient_l;
Lights[2]=directional_l;


int win=initwindow(Win_Width,Win_Height,(const char*)"RASTERIZER");
setcurrentwindow(win);

//
//drawing two axis for ref
class Col axis_col_z(155,155,0);
class Col axis_col_y(0,155,155);
class Vec3 ver1(0,-Win_Height,30);
class Vec3 ver2(0,Win_Height,30);
class Vec3 hor1(-Win_Width,0,30);
class Vec3 hor2(Win_Width,0,30);
draw_line(ver1,ver2,axis_col_y);
draw_line(hor1,hor2,axis_col_z);
//

class Model* mod=new Model("3D_Models/frog.txt");
render_object(mod,true,false);


//test
class Vec3 A(0,0,-1);
class Vec3 B(1,1,1);
std::cout<<"test="<<A.unsigned_angle_between(A,B)<<std::endl;
//end of test


getch();
closegraph();
return 0;
}



void render_object(class Model* mod,bool render_faces,bool render_wireframe)
{
double light_intensity=0;
class Vec3 Not_Projected[(mod->Num_Verticies)];
class Vec3 Projected[(mod->Num_Verticies)];
for(int i=0;i<mod->Num_Verticies*3;i+=3)
{
Projected[i/3].x=(*(mod->Verticies+i))+mod->Global_Pos.x;
Projected[i/3].y=(*(mod->Verticies+1+i))+mod->Global_Pos.y;
Projected[i/3].z=(*(mod->Verticies+2+i))+mod->Global_Pos.z;

Not_Projected[i/3].x=(*(mod->Verticies+i))+mod->Global_Pos.x;
Not_Projected[i/3].y=(*(mod->Verticies+1+i))+mod->Global_Pos.y;
Not_Projected[i/3].z=(*(mod->Verticies+2+i))+mod->Global_Pos.z;

mod->Rotation.y=(3.1416*-30)/180.0;
mod->Rotation.x=(3.1416*0)/180.0;
mod->Rotation.z=0;
mod->Scale.x=2.5;
mod->Scale.y=2.5;
mod->Scale.z=2.5;
class Vec3 translate(1,0,30);
Projected[i/3]=Matrix::Transform(Projected[i/3],mod->Scale,mod->Rotation,translate);

class Vertex v(Projected[i/3].x,Projected[i/3].y,Projected[i/3].z,'g');
Projected[i/3]=Project_Vertex(v);
}
//drawing the faces
if(render_faces)
{
 for(int i=0;i<mod->Num_Indicies*3;i+=3)
{
class Col r(*(mod->cols+i),*(mod->cols+i+1),*(mod->cols+i+2));

//light calculations
class Vec3 Normal(*(mod->Face_Normals+i),*(mod->Face_Normals+i+1),*(mod->Face_Normals+i+2));

mod->Rotation.y=(3.1416*-30)/180.0;
mod->Rotation.x=(3.1416*0)/180.0;
mod->Rotation.z=0;
mod->Scale.x=2.5;
mod->Scale.y=2.5;
mod->Scale.z=2.5;
class Vec3 translate(1,0,30);
Normal=Matrix::Transform(Normal,mod->Scale,mod->Rotation,translate);

class Vec3 Origin(0,0,0);
class Vec3 Mid_of_tri;
Mid_of_tri=Calculate_Mid_of_triangle(Not_Projected[*(mod->Indicies+i)],Not_Projected[*(mod->Indicies+i+1)],Not_Projected[*(mod->Indicies+i+2)]);
class Vec3 view_vec(-Mid_of_tri.x,-Mid_of_tri.y,-Mid_of_tri.z);
light_intensity=calculate_light(Normal,Mid_of_tri,view_vec,1);
r.Set_Intensity(light_intensity);


//back face cull
//std::cout<<"mid= "<<Mid_of_tri.x<<","<<Mid_of_tri.y<<","<<Mid_of_tri.z<<"|| " ;
//std::cout<<"View= "<<view_vec.x<<","<<view_vec.y<<","<<view_vec.z<<"|| " ;
//std::cout<<"Normal= "<<Normal.x<<","<<Normal.y<<","<<Normal.z<<"|| "<<"angle= "<<Normal.unsigned_angle_between(view_vec,Normal)<<std::endl;
//if(Normal.unsigned_angle_between(view_vec,Normal)<=90)
draw_filled_tris(Projected[*(mod->Indicies+i)],Projected[*(mod->Indicies+i+1)],Projected[*(mod->Indicies+i+2)],r);
}
}
if(render_wireframe)
{
  //drawing the lines as overlay
class Col y(255,255,255);
for(int i=0;i<mod->Num_Indicies*3;i+=3)
{
class Col r(*(mod->cols+i),*(mod->cols+i+1),*(mod->cols+i+2));
draw_line(Projected[*(mod->Indicies+i)],Projected[*(mod->Indicies+i+1)],r);
draw_line(Projected[*(mod->Indicies+i+1)],Projected[*(mod->Indicies+i+2)],r);
draw_line(Projected[*(mod->Indicies+i)],Projected[*(mod->Indicies+i+2)],r);
}
}

}




class Vec3 Project_Vertex(class Vertex A)
{
A.Pos.x=(A.Pos.x*View_d)/A.Pos.z;
A.Pos.y=((double)Win_Width/(double)Win_Height)*(A.Pos.y*View_d)/(A.Pos.z);
return View_to_canvas(A.Pos);
}


class Vec3 View_to_canvas(class Vec3 A)
{
A.x=(Win_Width*A.x)/View_W;
A.y=(Win_Height*A.y)/View_H;
return A;
}


void draw_filled_tris(class Vec3 P0,class Vec3 P1,class Vec3 P2,class Col col)
{
    class Vec3 X_left(0,0,0);
    class Vec3 X_right(0,0,0);
//sorting the points according to their height po lowest p1 mid and p2 highest
    if(P0.y>P1.y)
        draw_filled_tris(P1,P0,P2,col);
    if(P0.y>P2.y)
        draw_filled_tris(P2,P1,P0,col);
    if(P1.y>P2.y)
        draw_filled_tris(P0,P2,P1,col);

//if the triangle is like a st line do nothing
    double a_side=P1.Length(P1.Direction_Vec(P1,P0));
    double b_side=P1.Length(P1.Direction_Vec(P2,P1));
    double c_side=P1.Length(P1.Direction_Vec(P2,P0));
    double length=a_side+b_side+c_side;
    if(length<a_side+b_side || length<b_side+c_side || length<a_side+c_side)
    return;

//calculate the x's for a y
    for(int i=(int)P0.y+1; i<(int)P2.y; i++)
    {
//check if i is in between p0-p1 or p1-p2
        if(i>=P0.y && i<=P1.y)//p0-p1
        {
//calculate x for  p0-p1
            double a=(double)(P1.x-P0.x)/(double)(P1.y-P0.y);
            double b=P0.x-(a*P0.y);
            X_left.x=b+a*i;
            X_left.y=i;
            X_left.z=calc_intermedizte_z(i,P0,P1);
        }
        else if(i>P1.y && i<P2.y)//p1-p2
        {
//calculate x for p1-p2
            double a=(double)(P2.x-P1.x)/(double)(P2.y-P1.y);
            double b=P1.x-(a*P1.y);
            X_left.x=b+a*i;
            X_left.y=i;
            X_left.z=calc_intermedizte_z(i,P1,P2);
        }
//calculate x for p0-p2
        if(i>P0.y && i<P2.y)
        {
        double a=(double)(P2.x-P0.x)/(double)(P2.y-P0.y);
        double b=P0.x-(a*P0.y);
        X_right.x=b+a*i;
        X_right.y=i;
        X_right.z=calc_intermedizte_z(i,P0,P2);
        }

//draw the horizontal lines
        if(X_left.x>X_right.x)
        {
            class Vec3 temp;
            temp=X_left;
            X_left=X_right;
            X_right=temp;
        }
        draw_line(X_left,X_right,col);

    }


}


void draw_line(class Vec3 P,class Vec3 P1,class Col col)
{
    double DX=abs(P1.x-P.x);
    double DY=abs(P1.y-P.y);
    if(DX>DY)//horizontal
    {
        if(P.x>P1.x)//checking if P is smaller than p1 always goes from low to high
        {
            draw_line(P1,P,col);
        }
        else
        {
            double m=(double)(P1.y-P.y)/(double)(P1.x-P.x);// calculating slope
            double yn=P.y;
            double h=0.51;
            for(int i=P.x; i<=P1.x; i++)
            {
                Vec3 screen_cord;
                screen_cord=normalized_to_screen_cord(i,(int)yn);
                yn+=m;
                h+=0.01;
                double zz=calc_intermedizte_z(i,P,P1);//calc_intermedizte_z(i,P,P1);
                if(screen_cord.x<=Win_Width && screen_cord.x>=0 && screen_cord.y>=0 && screen_cord.y<=Win_Height)
                if(z_buff[(int)screen_cord.y][(int)screen_cord.x]>zz)
                {
                    z_buff[(int)screen_cord.y][(int)screen_cord.x]=zz;
                    putpixel((int)screen_cord.x,(int)screen_cord.y,COLOR(col.r,col.g,col.b));
                }

            }
        }
    }
    else//vertical
    {
        if(P.y>P1.y)//checking if P is smaller than p1 always goes from low to high
        {
            draw_line(P1,P,col);
        }
        else
        {
            double m=(double)(P1.x-P.x)/(double)(P1.y-P.y);//calculating slope
            double xn=P.x;
            for(int i=P.y; i<=P1.y; i++)
            {
                Vec3 screen_cord;
                screen_cord=normalized_to_screen_cord((int)xn,i);//converting from normal graph cordinate to screen co_ordinate system
                xn+=m;
                double zz=calc_intermedizte_z(i,P,P1);//calc_intermedizte_z(i,P,P1);
                if(screen_cord.x<=Win_Width && screen_cord.x>=0 && screen_cord.y>=0 && screen_cord.y<=Win_Height)
                if(z_buff[(int)screen_cord.y][(int)screen_cord.x]>zz )
                {
                    z_buff[(int)screen_cord.y][(int)screen_cord.x]=zz;
                    putpixel((int)screen_cord.x,(int)screen_cord.y,COLOR(col.r,col.g,col.b));
                }
            }
        }
    }
}

double calc_intermedizte_z(int i,class Vec3 P0,class Vec3 P1)
{

double DX=abs(P1.x-P0.x);
double DY=abs(P1.y-P0.y);
if(DX>DY)
{
double a=(double)(P1.z-P0.z)/(double)(P1.x-P0.x);
double b=P0.z-(a*P0.x);
double z=b+a*i;
return z;
}
else
{
double a=(double)(P1.z-P0.z)/(double)(P1.y-P0.y);
double b=P0.z-(a*P0.y);
double z=b+a*i;
return z;
}
}


double calc_intermedizte_1_by_z(int i,class Vec3 P0,class Vec3 P1)
{

double DX=abs(P1.x-P0.x);
double DY=abs(P1.y-P0.y);

P0.z=(double)1.0/P0.z;
P1.z=(double)1.0/P1.z;


if(DX>DY)
{
double z=P0.z+(i+P0.x)*(double(P1.z-P0.z)/double(P1.x-P0.x));
return z;
}
else
{
double z=P0.z+(i+P0.y)*(double(P1.z-P0.z)/double(P1.y-P0.y));
return z;
}
}



class Vec3 normalized_to_screen_cord(int X,int Y)
{
    double retx=((double)Win_Width/2.0)+(double)X;
    double rety=((double)Win_Height/2.0)-(double)Y;
    class Vec3 v(retx,rety,0);
    return v;
};
double calculate_light(class Vec3 N,class Vec3 P,class Vec3 V,double s)
{
double intense=0;
for(int i=0;i<3;i++)//point+ambient+directional
{
if(Lights[i]->type==ambient)
{
    intense+=Lights[i]->intensity;
}
else
{

    class Vec3 L;
    if(Lights[i]->type==point)
    {
    L=L.Direction_Vec(Lights[i]->pos,P);

    }
    else
    {
    L=Lights[i]->pos;//pos is the direction here

    }
    double n_dot_l=L.DOT_PRODUCT(N,L);
    if(n_dot_l>0)
    {
        intense+=(Lights[i]->intensity * n_dot_l)/(sqrt(N.DOT_PRODUCT(N,N))*sqrt(L.DOT_PRODUCT(L,L)));
    //specular calculatins
    if(s!=-1)
    {
        class Vec3 R;
        R=R.Direction_Vec(R.Scaler_Mul_Vec(2*R.DOT_PRODUCT(N,L),N),L);
        double r_dot_v=R.DOT_PRODUCT(R,V);
        intense+=Lights[i]->intensity*pow(r_dot_v/(sqrt(R.DOT_PRODUCT(R,R))*sqrt(R.DOT_PRODUCT(V,V))),s);
    }
    }
}

}
return intense;
}

class Vec3 Calculate_Mid_of_triangle(class Vec3 P0,class Vec3 P1,class Vec3 P2)
{

   double x=(double)0.333*(P0.x+P1.x+P2.x);
   double y=(double)0.333*(P0.y+P1.y+P2.y);
   double z=(double)0.333*(P0.z+P1.z+P2.z);
   class Vec3 M(x,y,z);
   return M;

};
