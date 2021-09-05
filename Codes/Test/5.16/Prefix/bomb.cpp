//O(nlogn)
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
int pos[1000010];
int n,m;
int bomb,maxn=-1;
bool judge(int ans) {//O(n) judge
	
//	cout<<"ans_change to:"<<ans<<" ";
	int Ans=ans;
	ll L=bomb,R=bomb;
//	cout<<"L:\n";
	for(int i=L;i>=1;i--) {
//		cout<<i<<"->\n";
		for(int j=i;j>=1;j--) {
//			cout<<"is"<<i<<"-> "<<j<<" "<<pos[i]<<" "<<pos[j]<<" "<<ans<<endl;
			if(pos[i]-pos[j]>ans) {
				if(j==i-1)  {
//					cout<<"fw"<<endl;
					return false;
				}
				i=j+2;
				
				break;
			}
//			cout<<"tr"<<endl;
			if(j==1) i=0;
		}
		ans=(ans<<1)/3;
//		cout<<i<<" "<<ans<<" ";
	}
//	cout<<endl;
//	cout<<"R:"<<endl;
	for(int i=R;i<=n;i++) {
		for(int j=i;j<=n;j++) {
			if(pos[j]-pos[i]>Ans) {
				if(j==i+1) return false;
				i=j-2;
				break;
			}
			if(j==n) return true;
		}
		Ans=(Ans<<1)/3;
//		cout<<Ans<<" ";
	}
//	cout<<endl;
	return true;
}
int ans;
bool flag;
int main() {
	freopen("bomb.in","r",stdin);
	freopen("bomb.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++) pos[i]=read();
	sort(pos+1,pos+n+1);//nlogn sort
//	for(int i=1;i<=n;i++) cout<<pos[i]<<" ";
//	cout<<endl;
	for(int i=2;i<=n;i++) if(pos[i]-pos[i-1]>maxn) maxn=pos[i]-pos[i-1],bomb=i;
//	cout<<"bomb"<<bomb<<endl;
	
	if(bomb==2) bomb=n/2,bomb++;
	if(pos[bomb+1]-pos[bomb]<pos[bomb-1]-pos[bomb-2]) bomb=bomb-1;
	
//	cout<<bomb<<" "<<pos[bomb]<<endl;
	int l=maxn,r=500000010;
	while(l<r-1) {//logn ���� 
		int mid=(l+r)>>1;
//		cout<<"mid"<<mid<<":: \n";
		if(judge(mid)) {
			r=mid;
			ans=mid;
			flag=true;
//			cout<<"down"<<endl;
		}
		else l=mid,ans=mid,flag=false/*,cout<<"up"<<endl*/;
//		cout<<endl;
	}
	if(flag) cout<<l;
	else cout<<r;
//	cout<<((flag==true)?(l:r))<<endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
