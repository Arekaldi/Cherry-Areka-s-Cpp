#include<bits/stdc++.h>
using namespace std;
int n,a[100010],ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) 
		cin>>a[i];
	int base=0;
	for(int i=1;i<=n+1;i++){
		if(a[i]>=base)base=a[i];
		else ans+=(base-a[i]),base=a[i];
	}
	cout<<ans<<endl;
	return 0;
}