#include<bits/stdc++.h>
#define il inline
#define g() getchar() 
#define ls T[x].lson
#define rs T[x].rson

using namespace std;
const int N = 1e6 + 10;
const int INF = 0x3f3f3f3f;

il int re()
{
    int x = 0, p =1 ;
    char ch = g();
    while(ch < '0' || ch > '9') {if(ch == '-') p = -1;ch = g();}
    while(ch <= '9' and ch >= '0') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = g();}
    return x * p;
}

int n, m;
struct node
{
    int lson, rson, fa, h, v;
}T[N];
struct dian
{
    int typ, derta, life;
}a[N];
vector<int> city[N];
int lazy1[N], lazy2[N];
int poi[N], dep[N], fath[N], die[N], ended[N], st[N];

int head[N], tot, ver[N], nxt[N];
void add(int x, int y)
{
    ver[++tot] = y;
    nxt[tot] = head[x];
    head[x] = tot;
}

int get(int x) {return T[x].fa == x ? x : T[x].fa = get(T[x].fa);}

void make_tree()
{
    for(int i = 1; i <= n; ++i)
    {
        T[i].lson = T[i].rson = T[i].h = 0;
        T[i].fa = i;        
    }
}

void pushdown(int x)
{
    if(lazy1[x])
    {
        T[rs].v += lazy1[x];
        lazy1[rs] += lazy1[x];
    }else{
        T[rs].v *= lazy2[x];
        lazy2[rs] *= lazy2[x];
    }
}

int Merge(int x, int y)
{
    // if(lazy1[x]) T[x].v += lazy1[x];
    // if(lazy2[x] != 1) T[x].v *= lazy2[x];
    if(!x || !y) return x + y;
    if(T[x].v > T[y].v || (T[x].v == T[y].v and x > y)) swap(x, y);
    // if(!lazy1[x] || lazy2[x] != 1) pushdown(x);
    rs = Merge(rs, y);
    if(T[rs].h > T[ls].h) swap(rs, ls);
    T[ls].fa = T[x].fa = T[rs].fa = x;
    T[x].h = T[rs].h + 1;
    return x;
}

void del(int x)
{
    int l = ls, r = rs;
    T[ls].fa = l, T[rs].fa = r;
    T[x].v = INF;
    T[x].lson = T[x].rson = T[x].h = 0;
    T[x].fa = Merge(l, r);
}

signed main()
{
    n = re(), m = re();
    make_tree();
    for(int i = 1; i <= n; ++i)
    {
        a[i].life = re(), poi[i] = -1;
    }
    memset(lazy1, 0, sizeof(lazy1));
    for(int i = 1; i <= n; ++i) lazy2[i] = 1;
    dep[1] = 1;
    for(int i = 2; i <= n; ++i)
    {
        int x = re();
        a[i].typ = re(), a[i].derta = re();
        if(a[i].typ) lazy2[i] = a[i].derta;
        else lazy1[i] = a[i].derta;
        fath[i] = x;
        dep[i] = dep[fath[i]] + 1;
    }
    for(int i = 1; i <= m; ++i)
    {
        int x = re(), y = re();
        st[i] = y;
        city[y].push_back(i);
        T[i].v = x;
    }
    for(int i = 1; i <= n; ++i) {
        for(auto it = city[i].begin(); it != city[i].end(); ++it) {
            if(poi[i] == -1)
                poi[i] = *it;
            else
                poi[i] = Merge(poi[i], *it);
        }
    }

    for(int i = n; i >= 1; --i) {
        while(true) {
            pushdown(poi[i]);
            if(T[poi[i]].v < a[i].life) {
                die[poi[i]] = i;
                if(T[poi[i]].lson == 0) {
                    poi[i] = -1;
                    break;
                }
                else
                    del(poi[i]);
            }
            else
                break;
        }

        if(i == 1)
            break;
        if(poi[i] == -1)
            continue;

        if(poi[fath[i]] == -1)
            poi[fath[i]] = poi[i];
        else
            Merge();
    }


    for(int i = 1; i <= n; ++i)
    {
        cout<<die[i]<<endl;
        
    }
    for(int i = 1; i <= m; ++i)
    {
        cout<<dep[ended[i]] - dep[st[i]]<<endl;
    }
}