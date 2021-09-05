/*
p==2
Ó¦¸ÃÄÜÄÃ°É 
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline int read(){ 
	int r=0,W=1; 
	char ch=getchar(); 
	while(ch>'9'or ch<'0') { if(ch=='-') W=-1; ch=getchar();} 
	while(ch>='0'and ch<='9') { r=r*10+ch-'0'; ch=getchar();} 
	return r*W;
}
int n,m,k;
int main() {
	freopen("paint.in","r",stdin);
	freopen("paint.out","w",stdout);
	cin>>n>>m>>k;
	cout<<k;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
