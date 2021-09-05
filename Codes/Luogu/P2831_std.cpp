#include<bits/stdc++.h>
using namespace std;
const double eps=1e-8;
int t,n,m,lines[20][20],lowunbit[1<<20],dp[1<<20];	//lowunbit就是题解中的x
double x[20],y[20];
void equation(double &x,double &y,double a1,double b1,double c1,double a2,double b2,double c2){	//解方程
	y=(a1*c2-a2*c1)/(a1*b2-a2*b1);
	x=(c1-b1*y)/a1;
}
int main(){
	for(int i=0;i<(1<<18);i++){	//预处理lowunbit
		int j=1;
		for(;j<=18 && i&(1<<(j-1));j++);
		lowunbit[i]=j;
	}
	scanf("%d",&t);
	while(t--){
		memset(lines,0,sizeof(lines));	//各种初始化
		memset(dp,0x3f,sizeof(dp));
		dp[0]=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++) scanf("%lf%lf",x+i,y+i);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){	//处理所有抛物线
				if(fabs(x[i]-x[j])<eps) continue;	//x坐标相同，不可能有解
				double a,b;
				equation(a,b,x[i]*x[i],x[i],y[i],x[j]*x[j],x[j],y[j]);
				if(a>-eps) continue;	//解出a和b
				for(int k=1;k<=n;k++)
					if(fabs(a*x[k]*x[k]+b*x[k]-y[k])<eps) lines[i][j]|=(1<<(k-1));
			}
        for(int i = 1; i <= n; ++i) {
            for(int j = i + 1; j <= n; ++j) {
                cout << i << " " << j << " " << lines[i][j] << endl;
            }
        }
		for(int i=0;i<(1<<n);i++){	//重点！状压开始！
			int j=lowunbit[i];	//必须经过lowunbit这个点
			dp[i|(1<<(j-1))]=min(dp[i|(1<<(j-1))],dp[i]+1);	//单独转移
			for(int k=1;k<=n;k++) dp[i|lines[j][k]]=min(dp[i|lines[j][k]],dp[i]+1);	//所有经过lowunbit的抛物线
		}
		printf("%d\n",dp[(1<<n)-1]);	//答案
	}
}