#include<iostream>
#include<fstream>
#include<math.h>
namespace MESH
{
void load_obj_data(char* filePath,double* vertex,int *num_vertex,int* index,int *num_index,double* color)
{
    int elements_counted=0;
    int local_vertex_count=*num_vertex*3;
    int local_index_count=*num_index*3;
    int local_col_count=*num_index*3;
    std::ifstream in(filePath);
    char c;
    if(in.is_open())
    {
        bool is_negative=false;
        bool reading_alphabets=true;
        bool read_deci=true;
        double num=0.0;
        int stack_left[8]= {0};
        int stack_top=0;
        int stack_max=0;
        int quee_right[8]= {0};
        int quee_head=0;
        int quee_tail=0;
        while(in.good())
        {
            in.get(c);
            if(reading_alphabets)
            {
                if((int)c==45)
                {
                    is_negative=true;
                }
                if((int)c>=48&&(int)c<=57)
                {

                    reading_alphabets=false;
                    stack_left[stack_top]=(int)c-48;
                    stack_top++;
                    stack_max++;
                }
            }
            else if(!reading_alphabets)
            {
                if(read_deci)//was reading deci
                {
                    if((int)c>=48&&(int)c<=57)//numbers
                    {
                        stack_left[stack_top]=(int)c-48;
                        stack_top++;
                        stack_max++;
                    }
                    else if((int)c==46)//deecimal point occured
                    {
                        read_deci=false;
                    }
                    else//any other charecter ,
                    {

                        reading_alphabets=true;
                        stack_top--;
                        stack_max--;
                        for(int i=stack_top; i>=0; i--) //stack
                        {
                            if(is_negative)
                                num-=(double)stack_left[i]*(double)pow(10,(stack_max-i));
                            else
                                num+=(double)stack_left[i]*(double)pow(10,(stack_max-i));
                        }
                        for(int i=quee_tail; i<quee_head; i++) //quee
                        {
                            if(is_negative)
                                num-=(double)quee_right[i]*pow(10,-i-1);
                            else
                                num+=(double)quee_right[i]*pow(10,-i-1);
                        }

                        elements_counted+=1;
                        if(elements_counted>2)
                        {
                            //std::cout<<num<<std::endl;
                            if(local_vertex_count>=0)
                            {
                                vertex[(*num_vertex)*3-local_vertex_count]=num;
                                local_vertex_count--;
                            }
                            if(local_index_count>0 && local_vertex_count<0)
                            {
                                index[(*num_index)*3-local_index_count]=(int)num;
                                local_index_count--;
                            }
                            else if(local_col_count>0 && local_vertex_count<0 && local_index_count<=0)
                            {
                                color[(*num_index)*3-local_col_count]=num;
                                local_col_count--;
                            }
                        }
//reinitialize quee and stack
                        stack_top=0;
                        stack_max=0;
                        quee_head=0;
                        quee_tail=0;
                        num=0;
                        is_negative=false;
                        for(int i=0; i<8; i++)
                        {
                            stack_left[i]=0;
                            quee_right[i]=0;
                        }
//done initializing

//done

                    }
                }
                else//was reading after decimal point
                {
                    if((int)c>=48 &&(int)c<=57)//nums after deci
                    {
                        quee_right[quee_head]=(int)c-48;
                        quee_head++;
                    }
                    else//any other charecter
                    {

                        read_deci=true;
                        reading_alphabets=true;
                        stack_top--;
                        stack_max--;
                        for(int i=stack_top; i>=0; i--) //stack
                        {
                            if(is_negative)
                                num-=(double)stack_left[i]*pow(10,(stack_max-i));
                            else
                                num+=(double)stack_left[i]*pow(10,(stack_max-i));
                        }

                        for(int i=quee_tail; i<quee_head; i++) //quee
                        {
                            if(is_negative)
                                num-=(double)quee_right[i]*pow(10,-i-1);
                            else
                                num+=(double)quee_right[i]*pow(10,-i-1);
                        }
                        //new bullshit

                        //end of new bullshit
                        elements_counted+=1;
                        if(elements_counted>2)
                        {
                            //std::cout<<num<<std::endl;
                            if(local_vertex_count>0)
                            {
                                vertex[(*num_vertex)*3-local_vertex_count]=num;
                                local_vertex_count--;
                            }
                            if(local_index_count>0 && local_vertex_count<0)
                            {
                                index[(*num_index)*3-local_index_count]=(int)num;
                                local_index_count--;
                            }
                            else if(local_col_count>0 && local_vertex_count<0 && local_index_count<=0)
                            {
                                color[(*num_index)*3-local_col_count]=num;
                                local_col_count--;
                            }
                        }


//reinitialize quee and stack
                        stack_top=0;
                        stack_max=0;
                        quee_head=0;
                        quee_tail=0;
                        num=0;
                        is_negative=false;
                        for(int i=0; i<8; i++)
                        {
                            stack_left[i]=0;
                            quee_right[i]=0;
                        }
//done initializing


                    }
                }
            }
//end of good
        }
    }
    if(!in.eof() && in.fail())
        std::cout << "error reading " << filePath <<std::endl;
    in.close();
}







void load_Array_sizes(char* filepath,int* num_of_verts,int *num_of_indicies)
{
    std::ifstream in(filepath);
    int counted=0;
    char c;
    if(in.is_open())
    {
        while(in.good())
        {
            bool is_negative=false;
            bool reading_alphabets=true;
            bool read_deci=true;
            double num=0.0;
            int stack_left[8]= {0};
            int stack_top=0;
            int stack_max=0;
            int quee_right[8]= {0};
            int quee_head=0;
            int quee_tail=0;
            while(in.good())
            {
                in.get(c);
                if(reading_alphabets)
                {
                    if((int)c==45)
                    {
                        is_negative=true;
                    }
                    if((int)c>=48&&(int)c<=57)
                    {

                        reading_alphabets=false;
                        stack_left[stack_top]=(int)c-48;
                        stack_top++;
                        stack_max++;
                    }
                }
                else if(!reading_alphabets)
                {
                    if(read_deci)//was reading deci
                    {
                        if((int)c>=48&&(int)c<=57)//numbers
                        {
                            stack_left[stack_top]=(int)c-48;
                            stack_top++;
                            stack_max++;
                        }
                        else if((int)c==46)//deecimal point occured
                        {
                            read_deci=false;
                        }
                        else//any other charecter ,
                        {
//done
                            reading_alphabets=true;
                            stack_top--;
                            stack_max--;
                            for(int i=stack_top; i>=0; i--) //stack
                            {
                                if(is_negative)
                                    num-=(double)stack_left[i]*(double)pow(10,(stack_max-i));
                                else
                                    num+=(double)stack_left[i]*(double)pow(10,(stack_max-i));
                            }
                            for(int i=quee_tail; i<quee_head; i++) //quee
                            {
                                if(is_negative)
                                    num-=(double)quee_right[i]*pow(10,-i-1);
                                else
                                    num+=(double)quee_right[i]*pow(10,-i-1);
                            }
                            counted++;
                            if(counted==1)
                            {
                                *num_of_verts=(int)num;
                                std::cout<<"loaded vertex size"<<std::endl;
                            }
                            else if(counted==2)
                            {
                                *num_of_indicies=(int)num;
                                std::cout<<"loaded indicies size"<<std::endl;
                                return;
                            }
//reinitialize quee and stack
                            stack_top=0;
                            stack_max=0;
                            quee_head=0;
                            quee_tail=0;
                            num=0;
                            is_negative=false;
                            for(int i=0; i<8; i++)
                            {
                                stack_left[i]=0;
                                quee_right[i]=0;
                            }
//done initializing
                        }
                    }
                    else//was reading after decimal point
                    {
                        if((int)c>=48 &&(int)c<=57)//nums after deci
                        {
                            quee_right[quee_head]=(int)c-48;
                            quee_head++;
                        }
                        else//any other charecter
                        {
                            read_deci=true;
                            reading_alphabets=true;
                            stack_top--;
                            stack_max--;
                            for(int i=stack_top; i>=0; i--) //stack
                            {
                                if(is_negative)
                                    num-=(double)stack_left[i]*pow(10,(stack_max-i));
                                else
                                    num+=(double)stack_left[i]*pow(10,(stack_max-i));
                            }

                            for(int i=quee_tail; i<quee_head; i++) //quee
                            {
                                if(is_negative)
                                    num-=(double)quee_right[i]*pow(10,-i-1);
                                else
                                    num+=(double)quee_right[i]*pow(10,-i-1);
                            }
                            //new bullshit

                            //end of new bullshit
                            counted++;
                            if(counted==1)
                            {
                                std::cout<<"loaded vertex size"<<std::endl;
                                *num_of_verts=(int)num;
                            }
                            else if(counted==2)
                            {
                                *num_of_indicies=(int)num;
                                std::cout<<"loaded indicies size"<<std::endl;
                                return;

                            }
//reinitialize quee and stack
                            stack_top=0;
                            stack_max=0;
                            quee_head=0;
                            quee_tail=0;
                            num=0;
                            is_negative=false;
                            for(int i=0; i<8; i++)
                            {
                                stack_left[i]=0;
                                quee_right[i]=0;
                            }
//done initializing
                        }
                    }
                }
            }
        }
        if(!in.eof() && in.fail())
        std::cout << "error reading " << filepath <<std::endl;
        in.close();
    }
}
};
