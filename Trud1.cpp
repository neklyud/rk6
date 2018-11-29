#include <iostream> 
//#include <vector> 
#include <stdlib.h> 
#include <time.h> 
#include <math.h> 
#include <fstream> 
#include <fcntl.h>

using namespace std; 

#define ktimes 10
#define Tleft 0
#define Tright 800
 
#define Tup 800
#define Tdown 20 
#define Izo 800
#define Temp 20

#define height 5
#define width 5
#define conduct 50
#define den 7
#define capacity 500

#define dx 0.2
#define dy 0.2
#define dt 1

class Matrix
{ 
    public:
        double **T,*value; 
        int Dimension;
        Matrix(int _x=0)
        {
            T=new double*[_x]; 
            for(int i=0;i<_x;i++)
            {
                T[i]=new double[_x];
            } 
            value=new double[_x];
            Dimension=_x;//h*w
        }
        void Installation();//начало 
        void PrintMatrix();//вывод
        void Normalize();
        bool SwapRowsMatrix(int i); 
        void RandMatrix();
        void AdditionRowsMatrix(int i); 
        void PrintValue();
};

void Matrix::PrintValue()
{
    int nxn=Dimension*Dimension; 
    for(int i=0;i<Dimension;++i)
    {
        cout<<"V"<<i+1<<"="<<value[i]<<endl;
    }
}

void Matrix::AdditionRowsMatrix(int i)
{
    double buffer;
    for(int j=i+1;j<Dimension;++j)
    {
            buffer=T[j][i];
        for(int k=i;k<Dimension;k++)
        {
            T[j][k]-=T[i][k]*buffer;
        }
        value[j]-=value[i]*buffer;
    }
    for(int j=i-1;j>=0;--j)
    {
        buffer=T[j][i];
        for(int k=i;k<Dimension;k++)
        {
            T[j][k]-=T[i][k]*buffer; 
        }
        value[j]-=value[i]*buffer;
    }
}
void Matrix::RandMatrix()
{
    for(int i=0;i<Dimension;++i)
    {
        for(int j=0;j<Dimension;++j) 
        T[i][j]=rand()%10-5;
        value[i]=rand()%10-5;
    }
}

bool Matrix::SwapRowsMatrix(int i)
{
    double buffer;
    for(int j=i+1;j<Dimension;++j)
    {
        if(T[j][i])
        {
            for(int k=i;k<Dimension;++k)
            {
                buffer=T[i][k]; 
                T[i][k]=T[j][k];
                T[j][k]=buffer;
            }
            buffer=value[i]; 
            value[i]=value[j]; 
            value[j]=buffer; 
            return true;
        }
    }
    return false;
}

void Matrix::Normalize()
{
    double before;
    for(int i=0;i<Dimension;++i)
    {
        if(T[i][i])
        {
            before=T[i][i];
            for(int j=i;j<Dimension;++j) 
                T[i][j]/=before;
            value[i]/=before;
            this->AdditionRowsMatrix(i);
        }
        else
        {
            if(this->SwapRowsMatrix(i))
            --i;
        }
    }
}
void Matrix::Installation()
{
    for(int i=0;i<Dimension;++i)
    {
        for(int j=0;j<Dimension;++j) 
            T[i][j]=0.0;
        value[i]=0.0;
    }
}

void Matrix::PrintMatrix()
{
    int nxn=Dimension*Dimension; 
    for(int i=0;i<Dimension;++i)
    {
        for(int j=0;j<Dimension;++j) 
            {
            cout<<T[i][j]<<" ";
            }
        cout<<"="<<value[i]<<endl;
    }
}
int main()
{
    int h,w;
    int kraz=ktimes/dt;
    double a=(double)conduct/((double)capacity*(double)den); 
    ofstream filedot;
    h=(height)/dy+1; 
    w=(width)/dx+1; 
    Matrix *T[kraz];
    for(int i=0;i<kraz;++i)
    {
        T[i]=new Matrix(h*w); 
        T[i]->Installation();
    }
    for(int j=0;j<w;++j)
    {
        for(int i=0;i<h;++i)
        {
            if(j==0)
            {
                T[0]->value[i+j*h]=Tleft; 
                continue;
            }
            if(i==0)
            {
                T[0]->value[i+j*h]=Tdown; 
                continue;
            }
            T[0]->value[i+j*h]=Temp;
        }   
    }
    for(int k=1;k<kraz;++k)
    {
        for(int j=0;j<w;++j)
        { 
            for(int i=0;i<h;++i)
            {
                if(j==0)
                {
                    T[k]->value[i+j*h]=Tleft; 
                    T[k]->T[i+j*h][i+j*h]+=1; 
                    continue;
                }
                else if(j==w-1)
                {
                    T[k]->T[i+j*h][i+j*h]=1;
                    T[k]->T[i+j*h][i+(j-1)*h]=-1;
                    T[k]->value[i+j*h]=Tright;
                    continue;
                }
                else if(i==h-1)
                {
                    T[k]->T[i+j*h][i+j*h]=1;
                    T[k]->T[i+j*h][i+j*h-1]=-1;
                    T[k]->value[i+j*h]=Tup;
                    continue;
                }
                else if(i==0)
                {
                    T[k]->value[i+j*h]=Tdown; 
                    T[k]->T[i+j*h][i+j*h]+=1; 
                    continue;
                }
                else
                {
                    T[k]->T[i+j*h][i+j*h+1]+=a*1/(dy*dy); 
                    T[k]->T[i+j*h][i+j*h-1]+=a*1/(dy*dy); 
                    T[k]->T[i+j*h][i+j*h]-=a*2/(dx*dx)+a*2/(dy*dy)+1/dt;
                    T[k]->T[i+j*h][i+(j-1)*h]+=a*1/(dx*dx);
                    T[k]->T[i+j*h][i+(j+1)*h]+=a*1/(dx*dx);
                    T[k]->value[i+j*h]-=T[k-1]->value[i+j*h]/dt;
                }
            }
        }
        T[k]->Normalize(); 
        cout<<k<<endl;
    }   
    filedot.open("result.txt"); 
    for(int k=0;k<kraz;++k)
    {
        filedot<<k<<endl; 
        for(int j=0;j<w;++j)
        {
            for(int i=0;i<h;++i)
            {
                filedot<<j*dx<<" "<<i*dy<<" "<<T[k]->value[i+j*h]<<endl;
            }
            filedot<<endl;
        }
        filedot<<endl;
    }
    cout<<kraz-1;
    filedot.close(); filedot.open("gra.gnu"); 
    filedot<<"set cbrange [0:800]"<<endl; 
    filedot<<"set pm3d map"<<endl;
    filedot<<"set pm3d flush begin ftriangles scansforward interpolate 2,2"<<endl;
    filedot<<"do for [i=0:"<<kraz-1<<"]{"<<endl;
    filedot<<"splot 'result.txt' index i using 1:2:3 with pm3d title '10 var'"<<endl;
    filedot<<"pause 0.5}"<<endl; 
    filedot<<"pause -1"; 
    filedot.close(); 
    system("gnuplot gra.gnu"); return 0;
}
