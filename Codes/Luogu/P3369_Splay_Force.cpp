#include<bits/stdc++.h>
#define MAXN 1100000
using namespace std;
int f[MAXN],cnt[MAXN],val[MAXN],sons[MAXN][5],sub_size[MAXN];
int whole_size,root;
void S_Clear(int x)
{
	sons[x][0]=sons[x][1]=sub_size[x]=cnt[x]=val[x]=0;
}
bool get_which(int x)
{
	 return sons[f[x]][1]==x;
}
void updata(int x)
{
	 if(x)
	 {
	 	sub_size[x]=cnt[x];
	 	if(sons[x][0]) sub_size[x]+=sub_size[sons[x][0]];
	 	if(sons[x][1]) sub_size[x]+=sub_size[sons[x][1]];
	 }
	 return ;
}
void rotate(int x)
{
	 int fa=f[x],g_fa=f[fa],which_son=get_which(x),which=get_which(fa);
	 sons[fa][which_son]=sons[x][which_son^1];
	 sons[fa][which_son]=sons[x][which_son^1];
	 f[sons[fa][which_son]]=fa;
	 sons[x][which_son^1]=fa;
	 f[fa]=x;
	 if(g_fa)
	 {
	 	sons[g_fa][which]=x;
	 }
	 updata(fa);
	 updata(x);
}

void splay(int x)
{
	 int fa;
	 for(;fa=f[x];rotate(x))
	    if(fa) rotate(get_which(x)==get_which(fa)?fa:x);
	 root=x;
}

void insert(int x)
{
	 if(!root)
	 {
	 	whole_size++;
	 	sons[whole_size][0]=sons[whole_size][1]=f[whole_size]=0;
	 	root=whole_size;
	 	sub_size[whole_size]=cnt[whole_size]++;
	 	val[whole_size]=x;
	 	return ;
	 }
	 int now=root,fa=0;
	 while(1)
	 {
	 	if(x==val[now])
	 	{
	 		cnt[now]++;
	 		updata(now);
	 		updata(fa);
	 		splay(now);
	 		break;
	 	}
	 	fa=now;
	 	now=sons[now][val[now]<x];
	 	if(!now)
	 	{
	 		whole_size++;
	 		sons[whole_size][0]=sons[whole_size][1]=0;
	 		f[whole_size]=fa;
	 		sub_size[whole_size]=cnt[whole_size]=1;
	 		sons[fa][val[fa]<x]=whole_size;
	 		val[whole_size]=x;
	 		updata(fa);
	 		splay(whole_size);
	 		break;
	 	}
	 }
}

int find_num(int x)
{
	 int now=root;
	 while(1)
	 {
	 	if(sons[now][0]&&x<=sub_size[sons[now][0]])
	 	{
	 		now=sons[x][0];
	 	}
	 	else
	 	{
	 		int temp=(sons[now][0]?sub_size[sons[now][0]]:0)+cnt[now];
	 		if(x<=temp) return val[now];
	 		x-=temp;
	 		now=sons[now][1];
	 	}
	 } 
}

int find_rank(int x)
{
	int now=root,ans=0;
	while(1)
	{
		if(x<val[now])
		{
			now=sons[now][0];
		}
		else 
		{
			ans+=(sons[now][0]?sub_size[sons[now][0]]:0);
			if(x==val[now])
			{
				splay(now);
				return ans+1;
			}
			ans+=cnt[now];
			now=sons[now][1];
		}
	}
}

int find_pre()
{
	int now=sons[root][0];
	while(sons[now][1]) now=sons[now][1];
	return now;
}

int find_suffix()
{
	int now=sons[root][1];
	while(sons[now][0]) now=sons[now][0];
	return now;
}

void del(int x)
{
	 int hh=find_rank(x);
	 if(cnt[root]>1)
	 {
	 	cnt[root]--;
	 	updata(root);
	 	return ;
	 }
	 if(!sons[root][0]&&!sons[root][1])
	 {
	 	S_Clear(root);
	 	root=0;
	 	return ;
	 }
	 else if(!sons[x][1])
	 {
	 	  int old=root;
	 	  root=sons[root][0];
	 	  f[root]=0;
	 	  S_Clear(old);
	 	  return ;
	 } 
	 int left_max=find_pre(),old=root;
	 splay(left_max);
	 sons[root][1]=sons[old][1];
	 f[sons[root][1]]=root;
	 S_Clear(old);
	 updata(root);
}

int main()
{
	int m,num,be_dealt;
    cin>>m;
    for(int i=1;i<=m;i++){
       cin>>num;
       cin>>be_dealt;
        switch(num)
        {
            case 1:insert(be_dealt);break;
            case 2:del(be_dealt);break;
            case 3:printf("%d\n",find_rank(be_dealt));break;
            case 4:printf("%d\n",find_num(be_dealt));break;
            case 5:insert(be_dealt);printf("%d\n",val[find_pre()]);del(be_dealt);break;
            case 6:insert(be_dealt);printf("%d\n",val[find_suffix()]);del(be_dealt);break;
        }
    }
    return 0;
}