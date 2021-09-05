#include<algorithm>
#include<iostream>
#include<cstdio>
using namespace std;
#define int long long
long long n,m,f[200000];
struct node{
    long long x,y,t;
}a[200000];
int cmp(struct node a,struct node b){
    return a.t<b.t;
}
int find(int num){
    if(f[num]==num) return num;
    else return f[num]=find(f[num]);
}
signed main(){
    scanf("%lld %lld",&n,&m);
    for(int i=1;i<=n;i++) f[i]=i;
    for(int i=1;i<=m;i++) scanf("%lld %lld %lld",&a[i].x,&a[i].y,&a[i].t);
    sort(a+1,a+m+1,cmp);
    for(int i=1;i<=m;i++){
        long long xx=find(a[i].x),yy=find(a[i].y);
        if(xx!=yy) f[xx]=yy;n--;
        if(n==1){
            printf("%lld",a[i].t);
            return 0;
        }
    }
    printf("-1");
    return 0;
}