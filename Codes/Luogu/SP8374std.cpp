#include<bits/stdc++.h>
using namespace std;

int main(){
    int r,b;
    scanf("%d%d",&r,&b);
    int s=r+b;
    for(int i=2;i<=s;i++)
        if(s%i==0&&(i-2)*(s/i-2)==b){
            int x=max(i,s/i),y=min(i,s/i);
            cout<<x<<" "<<y<<endl; //注意先大后小
        }
    return 0;   
}