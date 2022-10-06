#ifndef COL_H
#define COL_H


class Col
{
    public:
        Col();
        Col(int r,int g,int b);
        virtual ~Col();
        int r;
        int g;
        int b;
        class Col Mix(class Col A,class Col B,double amount);
    protected:

    private:
};

#endif // COL_H
