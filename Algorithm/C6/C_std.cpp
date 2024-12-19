#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const int MAXN=1e6;
inline int read()
{
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
const double Pi=acos(-1.0);
struct complex
{
    double x,y;
    complex (double xx=0,double yy=0){x=xx,y=yy;}
}a[MAXN],b[MAXN];
complex operator + (complex a,complex b){ return complex(a.x+b.x , a.y+b.y);}
complex operator - (complex a,complex b){ return complex(a.x-b.x , a.y-b.y);}
complex operator * (complex a,complex b){ return complex(a.x*b.x-a.y*b.y , a.x*b.y+a.y*b.x);}//不懂的看复数的运算那部分 
int N,M;
int l,r[MAXN];
int limit=1;
void fast_fast_tle(complex *A,int type)
{
    for(int i=0;i<limit;i++) 
        if(i<r[i]) swap(A[i],A[r[i]]);
    for(int mid=1;mid<limit;mid<<=1)
    {
        complex Wn( cos(Pi/mid) , type*sin(Pi/mid) ); 
        for(int R=mid<<1,j=0;j<limit;j+=R)
        {
            complex w(1,0);
            for(int k=0;k<mid;k++,w=w*Wn)
            {
                 complex x=A[j+k],y=w*A[j+mid+k];
                A[j+k]=x+y;
                A[j+mid+k]=x-y;
            }
        }
    }
}
int main()
{
    int k = read();
    int N = 1 << k;
    for(int i=0;i<N;i++) a[i].x=read();
    limit = N, l = k;
    double nn = N * 1.0;
    for(int i=0;i<limit;i++)
        r[i]= ( r[i>>1]>>1 )| ( (i&1)<<(l-1) ) ;
    fast_fast_tle(a,-1);
    for(int i=0;i<N;i++)
        printf("%.2lf %.2lf\n",a[i].x/nn,a[i].y/nn);
    return 0;
}