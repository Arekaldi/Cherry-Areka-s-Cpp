#include <bits/stdc++.h>

const int MAXV=110;
const int MAXE=10010;
const long long INF=1e15;

struct Edge{
    int from;
    int to;
    int flow;
    Edge* rev;
    Edge* next;
};
Edge E[MAXE];
Edge* head[MAXV];
Edge* cur[MAXV];
Edge* top=E;

int v;
int e;
int s;
int t;
int depth[MAXV];

bool BFS(int,int);
void Insert(int,int,int);
long long Dinic(int,int);
long long DFS(int,long long,int);

int main(){
    scanf("%d%d%d%d",&v,&e,&s,&t);
    for(int i=0;i<e;i++){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        Insert(a,b,c);
    }
    printf("%lld\n",Dinic(s,t));
    return 0;
}

long long Dinic(int s,int t){
    long long ans=0;
    while(BFS(s,t))
        ans+=DFS(s,INF,t);
    return ans;
}

bool BFS(int s,int t){
    memset(depth,0,sizeof(depth));
    std::queue<int> q;
    q.push(s);
    depth[s]=1;
    cur[s]=head[s];
    while(!q.empty()){
        s=q.front();
        q.pop();
        for(Edge* i=head[s];i!=NULL;i=i->next){
            if(i->flow>0&&depth[i->to]==0){
                depth[i->to]=depth[s]+1;
                cur[i->to]=head[i->to];
                if(i->to==t)
                    return true;
                q.push(i->to);
            }
        }
    }
    return false;
}

long long DFS(int s,long long flow,int t){
    if(s==t||flow<=0)
        return flow;
    long long rest=flow;
    for(Edge* & i=cur[s];i!=NULL;i=i->next){
        if(i->flow>0&&depth[i->to]==depth[s]+1){
            long long tmp=DFS(i->to,std::min(rest,(long long)i->flow),t);
            if(tmp<=0)
                depth[i->to]=0;
            rest-=tmp;
            i->flow-=tmp;
            i->rev->flow+=tmp;
            if(rest<=0)
                break;
        }
    }
    return flow-rest;
}

void Insert(int from,int to,int flow){
    top->from=from;
    top->to=to;
    top->flow=flow;
    top->rev=top+1;
    top->next=head[from];
    head[from]=top++;
    
    top->from=to;
    top->to=from;
    top->flow=0;
    top->rev=top-1;
    top->next=head[to];
    head[to]=top++;
}
