#include<graphics.h>
#include<iostream>
#include<math.h>
#include"Vec3.h"
#include"Light_Source.h"
#include"Col.h"
#include"Vertex.h"
#include"Model.h"
double Vals[500]= {0};
void render_object(class Model* mod);
void draw_filled_tris(class Vec3 P0,class Vec3 P1,class Vec3 P2,class Col col);
void ineterpolate(double x0,double y0,double x1,double y1);
void draw_line(class Vec3 P,class Vec3 P1,class Col col);
class Vec3 Project_Vertex(class Vertex A);
class Vec3 View_to_canvas(class Vec3 A);//scales up for the canvas
class Vec3 normalized_to_screen_cord(int X,int Y);
int Win_Width=500;
int Win_Height=500;
int View_H=5;
int View_W=5;
double View_d=1;
int main()
{
    int win=initwindow(Win_Width,Win_Height,(const char*)"RASTERIZER");
    setcurrentwindow(win);
    class Model* mod=new Model();
    render_object(mod);

    /*class Col c(255,255,0);
    class Vec3 v0(-10,-10,2);
    class Vec3 v1(10,-10,2);
    class Vec3 v2(-10,10,2);
    class Vec3 v3(10,10,2);
    draw_line(v0,v1,c);
    draw_line(v1,v2,c);
    draw_line(v0,v2,c);

    draw_line(v1,v3,c);
    draw_line(v2,v3,c);*/
   /* class Vertex Af(-1,1,1,'r');
    class Vertex Bf(1,1,1,'r');
    class Vertex Cf(1,-1,1,'r');
    class Vertex Df(-1,-1,1,'r');

    class Vertex Ab(1,1,2,'g');
    class Vertex Bb(3,1,2,'g');
    class Vertex Cb(3,-1,2,'g');
    class Vertex Db(1,-1,2,'g');

    class Col side_col(255,255,0);
    draw_line(Project_Vertex(Af),Project_Vertex(Bf),Af.Vertex_Col);
    draw_line(Project_Vertex(Bf),Project_Vertex(Cf),Cf.Vertex_Col);
    draw_line(Project_Vertex(Cf),Project_Vertex(Df),Df.Vertex_Col);
    draw_line(Project_Vertex(Af),Project_Vertex(Df),Af.Vertex_Col);

    draw_line(Project_Vertex(Ab),Project_Vertex(Bb),Bb.Vertex_Col);
    draw_line(Project_Vertex(Bb),Project_Vertex(Cb),Cb.Vertex_Col);
    draw_line(Project_Vertex(Cb),Project_Vertex(Db),Db.Vertex_Col);
    draw_line(Project_Vertex(Ab),Project_Vertex(Db),Ab.Vertex_Col);

    draw_line(Project_Vertex(Af),Project_Vertex(Ab),side_col);
    draw_line(Project_Vertex(Bf),Project_Vertex(Bb),side_col);
    draw_line(Project_Vertex(Cf),Project_Vertex(Cb),side_col);
    draw_line(Project_Vertex(Df),Project_Vertex(Db),side_col);*/


    getch();
    closegraph();
    return 0;
}



void render_object(class Model* mod)
{
int j=0;
class Vec3 Projected[(mod->Num_Verticies)];
std::cout<<mod->Num_Verticies<<std::endl;
for(int i=0;i<mod->Num_Verticies*3;i+=3)
{
Projected[j].x=(*(mod->Verticies+i));
Projected[j].y=(*(mod->Verticies+1+i));
Projected[j].z=(*(mod->Verticies+2+i));
std::cout<<"x="<<Projected[j].x<<" y="<<Projected[j].y<<" z="<<Projected[j].z<<std::endl;
class Vertex v(Projected[j].x,Projected[j].y,Projected[j].z,'g');
class Vec3 temp;
temp=Project_Vertex(v);
Projected[j]=temp;
std::cout<<"x="<<Projected[j].x<<" y="<<Projected[j].y<<" z="<<Projected[j].z<<std::endl<<std::endl;
j++;
}

for(int i=0;i<mod->Num_Indicies+3;i+=3)
{
class Col r(255,0,0);
draw_line(Projected[*(mod->Indicies+i)],Projected[*(mod->Indicies+i+1)],r);
draw_line(Projected[*(mod->Indicies+i+1)],Projected[*(mod->Indicies+i+2)],r);
draw_line(Projected[*(mod->Indicies+i)],Projected[*(mod->Indicies+i+2)],r);
//std::cout<<Projected[*(mod->Indicies+i)].x<<" "<<Projected[*(mod->Indicies+i+1)].x<<" "<<Projected[*(mod->Indicies+i+2)].x<<std::endl;
}
}




class Vec3 Project_Vertex(class Vertex A)
{
A.Pos.x=(A.Pos.x*View_d)/A.Pos.z;
A.Pos.y=(A.Pos.y*View_d)/A.Pos.z;
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

//calculate the x's for a y
    for(int i=(int)P0.y; i<(int)P2.y; i++)
    {
//check if i is in between p0-p1 or p1-p2
        if(i>=P0.y && i<=P1.y)//p0-p1
        {
//calculate x for  p0-p1
            double a=(P1.x-P0.x)/(P1.y-P0.y);
            double b=P0.x-(a*P0.y);
            X_left.x=b+a*i;
            X_left.y=i;
        }
        else//p1-p2
        {
//calculate x for p1-p2
            double a=(P2.x-P1.x)/(P2.y-P1.y);
            double b=P1.x-(a*P1.y);
            X_left.x=b+a*i;
            X_left.y=i;
        }
//calculate x for p0-p2
        double a=(P2.x-P0.x)/(P2.y-P0.y);
        double b=P0.x-(a*P0.y);
        X_right.x=b+a*i;
        X_right.y=i;

//draw the horizontal lines
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
            double m=(P1.y-P.y)/(P1.x-P.x);// calculating slope
            double yn=P.y;
            double h=0.51;
            for(int i=P.x; i<P1.x; i++)
            {
                Vec3 screen_cord;
                screen_cord=normalized_to_screen_cord(i,(int)yn);
                yn+=m;
                h+=0.01;
                putpixel(screen_cord.x,screen_cord.y,COLOR(col.r,col.g,col.b));
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
            double m=(P1.x-P.x)/(P1.y-P.y);//calculating slope
            double xn=P.x;
            for(int i=P.y; i<P1.y; i++)
            {
                Vec3 screen_cord;
                screen_cord=normalized_to_screen_cord((int)xn,i);//converting from normal graph cordinate to screen co_ordinate system
                xn+=m;
                putpixel(screen_cord.x,screen_cord.y,COLOR(col.r,col.g,col.b));
            }
        }
    }
}


class Vec3 normalized_to_screen_cord(int X,int Y)
{
    double retx=((double)Win_Width/2.0)+(double)X;
    double rety=((double)Win_Height/2.0)-(double)Y;
    class Vec3 v(retx,rety,0);
    return v;
};
