#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
using namespace std;
int ans[1000001],x[1000001],y[1000001],ce;
int zoo=0,tool[1000001];
bool fu=false;
string a,b,yuan,as,bs;
string jian(string a,string b)
{
	
	int s1=a.size(),s2=b.size();
	if(s1<s2||(s1==s2&&a<b)) fu=true,swap(a,b);
	s1=a.size(),s2=b.size();
	for(int i=1;i<=s1;i++) x[i]=a[s1-i]-'0',ans[i]=0;
	for(int i=1;i<=s2;i++) y[i]=b[s2-i]-'0';
	for(int i=1;i<=s1;i++)
	{
		if(i>s2) y[i]=0;
		if(x[i]>=y[i]) ans[i]=x[i]-y[i];
		if(x[i]<y[i]) ans[i]=10+x[i]-y[i],x[i+1]-=1;
	}
	int now=s1;
	string s;
    while(ans[now]==0) now-=1;
    for(int i=now;i>=1;i--) s+=ans[i]+'0';
    if(fu==true) cout<<"-";
    return s;
}
string jia(string a,string b)
{
	memset(ans,0,sizeof(ans));
	int s1=a.size(),s2=b.size();
	if(s1<s2||(s1==s2&&a<b)) swap(a,b);
	s1=a.size(),s2=b.size();
	for(int i=1;i<=s1;i++) x[i]=a[s1-i]-'0';
	for(int i=1;i<=s2;i++) y[i]=b[s2-i]-'0';
	ans[1]=0;
	for(int i=1;i<=s1;i++)
	{
		if(i>s2) y[i]=0;
		ans[i]+=x[i]+y[i];
		if(ans[i]>=10)
		{
			ans[i+1]+=1;
			ans[i]%=10;
		}
	}
    int now=s1;
    string s;
    while(ans[now]==0) now-=1;
    for(int i=now;i>=1;i--) s+=ans[i]+'0';
    return s;
}
string cheng(string a,string b)
{
	memset(ans,0,sizeof(ans));
	int s1=a.size(),s2=b.size();
	if(s1<s2||(s1==s2&&a<b)) swap(a,b);
	s1=a.size(),s2=b.size();
	for(int i=1;i<=s1;i++) x[i]=a[s1-i]-'0';
	for(int i=1;i<=s2;i++) y[i]=b[s2-i]-'0';
	ans[1]=0;
	for(int i=1;i<=s2;i++)
	{
		for(int j=1;j<=s1;j++)
		{
			ans[j+i-1]+=x[j]*y[i];
			if(ans[j+i-1]>=10) ans[j+i]+=ans[j+i-1]/10,ans[j+i-1]%=10;
		}
	}
	int now=s1+s2;
    string s;
    while(ans[now]==0) now-=1;
    for(int i=now;i>=1;i--) s+=ans[i]+'0';
    return s;
}
// string change(long long x)
// {
// 	string s;
// 	int now=0,tool[10000001];
// 	while(x)
// 	{
// 		int to=x%10;
// 		now+=1;
// 		tool[now]=to;
// 		x/=10;
// 	}
// }
void Up()
{
    zoo = 0, memset(tool, 0, sizeof(tool));
    int l = ce + 1;
	cout << -1;
	string now="",base="";
	if(yuan[l]=='(')
	{
		l+=1;
		while(yuan[l]!=')')
		{
			now+=yuan[l];
			l+=1;
		}
		l+=1;
		while(yuan[l]>='0'&&yuan[l]<='9')
		{
			base+=yuan[l];
			l+=1;
		}
		now=cheng(now,base);
		as=jia(now,as);
		ce=l;
		return ;
	}
	else
	{
		int siz=1;
    	while(yuan[l]=='+' and l < yuan.size())
     	{
	    	siz+=1;
    		l+=1;
    	}
    	while(yuan[l]>='0'&&yuan[l]<='9' and l < yuan.size())
		{
			base+=yuan[l];
			l+=1;
		}
		while(siz)
		{
			int to=siz%10;
			zoo+=1;
			tool[zoo]=to;
			siz/=10;
		}
		for(int i=zoo;i>=1;i--) now+='0'+tool[i];
		now=cheng(now,base);
		as=jia(now,as);
		ce=l;
		return ;
	}
}
// void down(int l)
// {
// 	if(yuan[l]=='(')
// 	{
// 		l+=1;
// 		string now,base;
// 		while(yuan[l]!=')')
// 		{
// 			now+=yuan[l];
// 			l+=1;
// 		}
// 		l+=1;
// 		while(yuan[l]>='0'&&yuan[l]<='9')
// 		{
// 			base+=yuan[l];
// 			l+=1;
// 		}
// 		now=cheng(now,base);
// 		bs=jia(now,bs);
// 		ce=l;
// 		return ;
// 	}
// 	else
// 	{
// 		int siz=1;
// 		string base,now;
//     	while(yuan[l]=='-')
//      	{
// 	    	siz+=1;
//     		l+=1;
//     	}
//     	while(yuan[l]>='0'&&yuan[l]<='9')
// 		{
// 			base+=yuan[l];
// 			l+=1;
// 		}
// 		int zoo=0,tool[10001];
// 		while(siz)
// 		{
// 			int to=siz%10;
// 			zoo+=1;
// 			tool[zoo]=to;
// 			siz/=10;
// 		}
// 		for(int i=zoo;i>=1;i--) now+='0'+tool[i];
// 		now=cheng(now,base);
// 		bs=jia(now,bs);
// 		ce=l;
// 		return ;
// 	}
// }
signed main()
{
	cin>>yuan;
	while(ce < yuan.size())
	{
		if(yuan[ce]=='+')
		{
			cout<<"fgh";
			Up();
		}
		// else
		// {
		// 	if(yuan[ce]=='-')
		// 	{
		// 		down(ce+1);
		// 	}
		// 	else
		// 	{
		// 		if(ce==0) up();
		// 	}
		// }
	}
	if(bs.size()==0) cout<<as;
	else
	{
		if(as.size()==0) cout<<"-"<<bs;
		else cout<<jian(as,bs);
	}
	return 0;
}
