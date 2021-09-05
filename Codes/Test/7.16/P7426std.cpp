//wliss Œ“*ƒ„œ…»À 
#include<bits/stdc++.h>
#define six_hours 60*60*6
#define one_day 60*60*24
#define P make_pair
using namespace std;
int n,m;
map<long long,int>mp;
map<pair<int,int>,int >male,fmale;
struct runs{
	int ti;
	long long fr;
	int h,m,s;
	int hh,mm,ss;
	int lon;
	int a,b;
}daily[300001];
struct node{
	long long p;
	bool male,running;
	int mark;
	pair<int,int>ti;
	int f,c;
	int sunny_days;
	int run_sco,sunny,fir;
	int res;
}s[100001];
bool comp(runs a,runs b)
{
	if(a.fr!=b.fr)return (a.fr<b.fr);
	if(a.ti!=b.ti)return (a.ti<b.ti);
	return a.s<b.s;
}
int months[15]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int nxt(int x)
{
	int year=(x/10000);
	int day=(x%100);
	int mon=(x%10000)/100;
	day++;
	if(day>months[mon])
	{
		day=1;
		++mon;
	}
	if(mon>12)
	{
		++year;
		mon=1;
	}
	return year*10000+mon*100+day;
}
bool compp(node a,node b)
{
	return a.p<b.p;
}
int main()
{
	freopen("1.txt", "r", stdin);
	freopen("a.txt", "w", stdout);
	scanf("%d",&n);
	male[P(12,30)]=20;
	male[P(13,0)]=18;
	male[P(13,30)]=16;
	male[P(14,0)]=14;
	male[P(14,30)]=12;
	male[P(15,10)]=10;
	male[P(15,50)]=8;
	male[P(16,30)]=6;
	male[P(17,10)]=4;
	male[P(18,00)]=2;
	male[P(1111111100,0)]=0;
	fmale[P(6,40)]=20;
	fmale[P(6,57)]=18;
	fmale[P(7,14)]=16;
	fmale[P(7,31)]=14;
	fmale[P(7,50)]=12;
	fmale[P(8,5)]=10;
	fmale[P(8,20)]=8;
	fmale[P(8,35)]=6;
	fmale[P(8,50)]=4;
	fmale[P(9,0)]=2;
	fmale[P(1111111000,0)]=0;
	for(int i=1;i<=n;++i)
	{
		scanf("%lld",&s[i].p);
		mp[s[i].p]=i;
		char a;
		cin>>a;
		if(a=='M')s[i].male=true;
		scanf("%d",&s[i].mark);
		string b;
		scanf("%d'%d\"",&s[i].ti.first,&s[i].ti.second);
		cin>>a;
		if(a=='P')s[i].running=true;
		scanf("%d %d",&s[i].f,&s[i].c);
		if(s[i].male)
		{
			s[i].run_sco=(male.lower_bound(s[i].ti))->second;
		}
		else
		{
			s[i].run_sco=(fmale.lower_bound(s[i].ti))->second;
		}
		
	}
	scanf("%d",&m);
	int tot=0;
	for(int i=1;i<=m;++i)
	{
		++tot;
		cin>>daily[tot].ti;
		scanf("%lld",&daily[tot].fr);
		scanf("%d:%d:%d",&daily[tot].h,&daily[tot].m,&daily[tot].s);
		daily[tot].m+=daily[tot].h*60;
		daily[tot].s+=daily[tot].m*60;
		scanf("%d:%d:%d",&daily[tot].hh,&daily[tot].mm,&daily[tot].ss);
		daily[tot].mm+=daily[tot].hh*60;
		daily[tot].ss+=daily[tot].mm*60;
		double l,a,b,ss;
		scanf("%lf",&l);
		l*=1000;
		scanf("%lf'%lf\"",&a,&b);
		scanf("%lf",&ss);
		int x=mp[daily[tot].fr];
		if(s[x].male)
		{
			if(l<3000.0)
			{
				tot--;
				continue;
			}
		}
		else
		{
			if(l<1500.0)
			{
				tot--;
				continue;
			}
		}
		b+=a*60.0;
		if(b>30.0+4*60.0)
		{
			tot--;
			continue;
		}
		double ts=daily[tot].ss-daily[tot].s;
		if(l/(ts)<2.0||l/(ts)>5.0)
		{
			tot--;
			continue;
		}
		if(l/ss>1.5)
		{
			tot--;
			continue;
		}
	}
	sort(daily+1,daily+1+tot,comp);
	int la=0;
	for(int i=1;i<=tot;++i)
	{
		if(daily[i].fr==daily[la].fr)
		{
			if(daily[i].ti==daily[la].ti)
			{
				if(daily[i].s-daily[la].ss<six_hours)
				continue;
			}
			else
			{
				if(nxt(daily[la].ti)==daily[i].ti)
				{
					daily[i].s+=one_day;
					if(daily[i].s-daily[la].ss<six_hours)
					continue;
				}
			}
		}
		la=i;
		s[mp[daily[i].fr]].sunny_days++;
	}
	for(int i=1;i<=n;++i)
	{
		
		int x=s[i].sunny_days;
		s[i].c+=x;
		if(x>=21){s[i].sunny+=10;continue;}
		if(x>=19){s[i].sunny+=9;continue;}
		if(x>=17){s[i].sunny+=8;continue;}
		if(x>=14){s[i].sunny+=7;continue;}
		if(x>=11){s[i].sunny+=6;continue;}
		if(x>=7){s[i].sunny+=4;continue;}
		if(x>=3){s[i].sunny+=2;continue;}
	}
	for(int i=1;i<=n;++i)
	{
		int x=s[i].c;
		if(x>=18){s[i].fir=5;continue;}
		if(x>=15){s[i].fir=4;continue;}
		if(x>=12){s[i].fir=3;continue;}
		if(x>=9){s[i].fir=2;continue;}
		if(x>=6){s[i].fir=1;continue;}
	}
	for(int i=1;i<=n;++i)
	{
		s[i].res=s[i].mark+s[i].run_sco+s[i].running*10+s[i].f+s[i].sunny+s[i].fir;
	}
	sort(s+1,s+n+1,compp);
	cout << s[455].sunny_days << endl;
	for(int i=1;i<=n;++i)
	{
		printf("%lld %d ",s[i].p,s[i].res);
		if(s[i].res>=95){printf("A\n");continue;}
		if(s[i].res>=90){printf("A-\n");continue;}
		if(s[i].res>=85){printf("B+\n");continue;}
		if(s[i].res>=80){printf("B\n");continue;}
		if(s[i].res>=77){printf("B-\n");continue;}
		if(s[i].res>=73){printf("C+\n");continue;}
		if(s[i].res>=70){printf("C\n");continue;}
		if(s[i].res>=67){printf("C-\n");continue;}
		if(s[i].res>=63){printf("D+\n");continue;}
		if(s[i].res>=60){printf("D\n");continue;}
		cout<<"F\n";
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
