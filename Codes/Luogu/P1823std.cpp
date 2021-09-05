#include<bits/stdc++.h>
#define int long long
using namespace std;
const int ma=6e5+100;
int n;
int top=1,ans=0;
struct rec{
	int num;
	int cnt;
}q[ma];

void add(int x){
	while(top&&x>q[top].num){
		ans+=q[top].cnt;
		q[top--].cnt=0;
	}
	if(x==q[top].num){
		ans+=q[top].cnt;
		if(top!=1) ans++; 
		q[top].cnt++;
		return;
	}
	if(top) ans++;
	q[++top].num=x;
	q[top].cnt++;
	return ;
}

signed main(){
	freopen("1.txt", "r", stdin);
	freopen("a.txt", "w", stdout);
	cin>>n;
	int a;
	q[0].num=1e9;
	for(int i=1;i<=n;i++){
		cin>>a;
		add(a);	
	}
	cout<<ans;
	return 0;
}
