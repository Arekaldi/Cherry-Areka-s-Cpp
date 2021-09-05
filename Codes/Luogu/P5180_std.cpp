#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

const int maxn=3e5+7;
int n,m;
struct node{
    int head[maxn],ecnt;
    struct ss{
        int to,nxt;
    }tr[maxn<<1];
    void add(int a,int b) {
        tr[++ecnt].nxt=head[a];
        tr[ecnt].to=b;
        head[a]=ecnt;
        return;
    }
}mp,un_mp,dfs_tr,undfs_tr,nw_tr;//原图，反图，dfs树，反dfs树，支配树 

int cnt,dfn[maxn],id[maxn],fa[maxn];

void dfs(int x) {//寻找dfs树 
    id[dfn[x]=++cnt]=x;
    for(int i=mp.head[x];i;i=mp.tr[i].nxt) {
        int y=mp.tr[i].to;
        if(!dfn[y]) {
            dfs(y);
            fa[y]=x;
            dfs_tr.add(x,y);
        }
    }
    return;
}

int anc[maxn],min_anc[maxn],semi[maxn];//Semi-domination半支配 表示v点的所有半支配点的最小的那个
/**半支配点： 
存在从一个点u到v的路径中(不包括u，v)，所有dfs树的点的dfn都大于v的dfn
如果u是v在dfs树上的父节点，那么u也是v的半支配点
的semi最小的那个祖先，所以semi[mn[x]]=semi[x];*/
int fi_fa(int x) {
    if(x==anc[x]) 
        return x;
    int father=anc[x];
    anc[x]=fi_fa(anc[x]);
    if(dfn[semi[min_anc[x]]]>dfn[semi[min_anc[father]]])
        min_anc[x]=min_anc[father];
    return anc[x];
}

void sp_tarjan() {
    for(int i=1;i<=n;i++) 
        anc[i]=min_anc[i]=semi[i]=i;
    for(int j=n;j>1;j--) {
        int x=id[j];
        if(!x)
            continue;
        int res=j;
        for(int i=un_mp.head[x];i;i=un_mp.tr[i].nxt) {
            int y=un_mp.tr[i].to;
            if(!dfn[y])
                continue;
            if(dfn[y]<dfn[x])
                res=min(res,dfn[y]);
            else {
                fi_fa(y);
                res=min(res,dfn[semi[min_anc[y]]]);
            }
        }
        semi[x]=id[res];
        anc[x]=fa[x];
        dfs_tr.add(semi[x],x);
    }
    return;
}

int in[maxn],dept[maxn],fath[maxn][30];

int lca(int x,int y) {
    if(dept[x]<dept[y]) 
        swap(x,y);
    int d=dept[x]-dept[y];
    for(int i=0;i<=20;i++) 
        if((1<<i)&d)
            x=fath[x][i];
    if(x==y)
        return x;
    for(int i=20;i>=0;i--) {
        if(fath[x][i]!=fath[y][i]) {
            x=fath[x][i];
            y=fath[y][i];
        }
    }
    return fath[x][0];
}

void built_tree(int x) {
    int son=undfs_tr.tr[undfs_tr.head[x]].to;
    for(int i=undfs_tr.head[x];i;i=undfs_tr.tr[i].nxt) {
        int y=undfs_tr.tr[i].to;
        son=lca(son,y);
    }
    dept[x]=dept[son]+1;
    fath[x][0]=son;
    nw_tr.add(son,x);
    for(int i=1;i<=20;i++)
        fath[x][i]=fath[fath[x][i-1]][i-1];
    return;
}

void topu() {
    for(int x=1;x<=n;x++) {
        for(int i=dfs_tr.head[x];i;i=dfs_tr.tr[i].nxt) {
            int y=dfs_tr.tr[i].to;
            in[y]++;
            undfs_tr.add(y,x);
        }
    }
    for(int i=1;i<=n;i++) {
        if(!in[i]) {
            undfs_tr.add(i,0);
            dfs_tr.add(0,i);
        }
    }
    queue<int> q;
    q.push(0);
    while(!q.empty()) {
        int x=q.front();
        q.pop();
        for(int i=dfs_tr.head[x];i;i=dfs_tr.tr[i].nxt) {
            int y=dfs_tr.tr[i].to;
            if(--in[y]<=0) {
                q.push(y);
                built_tree(y);
            }
        }
    }
    return;
}

int siz[maxn];

void re_dfs(int x) {
    siz[x]=1;
    for(int i=nw_tr.head[x];i;i=nw_tr.tr[i].nxt) {
        int y=nw_tr.tr[i].to;
        re_dfs(y);
        siz[x]+=siz[y];
    }
    return;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) {
        int x,y;
        scanf("%d%d",&x,&y);
        mp.add(x,y);
        un_mp.add(y,x);
    }
    dfs(1);
    sp_tarjan();
    topu();
    re_dfs(0);
    for(int i=1;i<=n;i++) 
        cout<<siz[i]<<" ";
    cout<<endl;
    return 0;
}