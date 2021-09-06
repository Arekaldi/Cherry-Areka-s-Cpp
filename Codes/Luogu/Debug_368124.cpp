#include<iostream>
#include<stack>
#include<algorithm>
#include<map>
using namespace std;
int n;
int d[505];
stack<int>ans;
int flag[505][505];
int maxx=1;
void dfs(int x){
    for(int i=1;i<=maxx;i++){
        if(flag[x][i]>=1){
            flag[x][i]--;
            flag[i][x]--;
            dfs(i);
        }
    }
    ans.push(x);
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        d[x]++;
        d[y]++;
        flag[x][y]++;
        flag[y][x]++;
        maxx=max(maxx,max(x,y));
    }
    int start;
    for(int i=1;i<=maxx;i++){
        if(d[i]%2==1){
            start=i;
            break;
        }
    }
    dfs(start);
    while(!ans.empty()){
        cout<<ans.top()<<endl;
        ans.pop();
    }
    return 0;
}