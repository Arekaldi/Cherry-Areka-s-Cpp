/*
桃       P
杀       K
闪       D
决斗  F
南猪    N
万剑    W
无懈    J
诸葛    Z 
*/
#include<iostream>
#include<cstdio>
#include<algorithm> 
#include<cstring>
#include<cstdlib>
using namespace std;
struct PiGs{
    int id;//1是主猪  2是忠猪  3是反猪
    int life;//剩余体力
    int numk;//杀 
    int nums;//闪
    int nump;//桃
    int numc;//手牌
    int numwxkj;//无懈可击
    bool zgln;//猪哥连弩 
    int target;//首要攻击对象
    int targetjd;//决斗首要攻击对象
    int pl;//前一头活着的猪 
    int pr;//下一头活着的猪 
    int zhu;//已知的状态 0未知 1跳忠 2跳反 3类反  
    bool DEAD;//死了吗 
    char cards[2010];//手牌
    PiGs(){
        DEAD=true;
        numk=nums=nump=numc=0;
    }
}p[15];
int n,m,k;//猪总数,卡牌总数,存活的反猪数量
int top;
char cards[2010]; 
int winn;//1是主猪胜利  2是反猪胜利 
int readnomber=1;
char read(){
    char s=getchar();
    while(s>'Z'||s<'A') s=getchar();
    readnomber++;
    return s;//读进来一张牌 
}
void memset_(int q){
    char s;
    cin >> s;
    if(s=='Z') p[q].id=2;//忠猪 
    else if(s=='M'){//主猪 
        p[q].id=1;
        p[q].zhu=1;
    } 
    else if(s=='F'){//反猪 
        p[q].id=3;
        p[q].targetjd=1;
        k++;
    }
    s=getchar(); 
    for(int i=1;i<=4;i++){
        p[q].cards[i]=read();
        if(p[q].cards[i]=='K') p[q].numk++;//杀加一 
        if(p[q].cards[i]=='D') p[q].nums++; //闪加一 
        if(p[q].cards[i]=='P') p[q].nump++;//桃加一 
        if(p[q].cards[i]=='J') p[q].numwxkj++;//无懈可击加一 
    }
    p[q].numc=4;
    p[q].life=4;//初始化手牌数和血量 
    if(q==1) p[q].pl=n;
    else p[q].pl=q-1;
    if(q==n) p[q].pr=1;
    else p[q].pr=q+1;//初始化前家后家 
    p[q].DEAD=true;//没死 
} 
char get_card(){//牌堆拿牌
    char c=cards[top];//拿牌堆顶的那张牌 
    if(top!=1) top--;//如果牌堆中还有牌，那么牌堆顶减减，否则就一直抽最后一张牌 
    return c; //返回 
}
void print(){
    if(winn==1) cout<<"MP"<<endl;
    else cout<<"FP"<<endl;//判断谁赢了 
    for(int i=1;i<=n;i++){
        if(p[i].DEAD==false){
            cout<<"DEAD"<<endl;//判断死亡 
        }
        else{
            if(p[i].numc!=0){//判断有没有牌 
                for(int j=1;j<p[i].numc;j++) cout<<p[i].cards[j]<<' ';//输出牌 
                cout<<p[i].cards[p[i].numc];//别忘了行末无空格 
            }
            cout<<endl;
        }
    }
}
bool END(){
    if(k==0){//反猪死光了 
        winn=1;//主猪胜利 
        return true; 
    } 
    if(p[1].DEAD==false){//主猪死了
        winn=2;//反猪胜利 
        return true;
    }
    return false;//game still going on… 
}
bool findwxkj(int q,int zhu){//找无懈可击 
    if(zhu==0||zhu==3) return false;//如果是未知身份或是类反猪，没人会帮他们 
    for(int i=q;;i=p[i].pr){//逆时针枚举 
        if(p[i].numwxkj>0){//如果这个猪有 
            if(zhu==1&&(p[i].id==1||p[i].id==2)){//如果是跳忠的猪被决斗，当前猪是主猪或忠猪，帮助他 
                int tmp=1;
                for(int j=1;j<=p[i].numc&&p[i].cards[j]!='J';j++) tmp=j;//记录无懈可击的位置 
                for(int j=tmp+1;j<=p[i].numc;j++) p[i].cards[j-1]=p[i].cards[j];//覆盖掉无懈可击 
                p[i].numc--;//手牌数减1 
                p[i].numwxkj--;//无懈可击数减1 
                if(p[i].zhu==0||p[i].zhu==3) p[i].zhu=1;//如果是未知身份回收类反猪，变为忠猪 
                return !findwxkj(i,2); //看看反猪那一方有没有猪出无懈可击 
            }
            else if(zhu==2&&p[i].id==3){//如果是反猪帮反猪 
                int tmp=1;
                for(int j=1;j<=p[i].numc&&p[i].cards[j]!='J';j++) tmp=j;//记录无懈可击的位置 
                for(int j=tmp+1;j<=p[i].numc;j++) p[i].cards[j-1]=p[i].cards[j];//覆盖掉无懈可击 
                p[i].numc--;//手牌数减1 
                p[i].numwxkj--;//无懈可击数减1 
                if(p[i].zhu==0||p[i].zhu==3) p[i].zhu=2;//标记为反猪 
                return !findwxkj(i,1);//看看忠猪那一方有没有猪出无懈可击 
            }
        }
        if(i==p[q].pl) return false;//如果已经找了一圈了，返回没有 
    }
}
void DIE(int from,int target){//from杀死了target 
    bool usep=false;//用桃子 
    if(p[target].nump>0){//有桃子 
        usep=true;//有当然用 
        int tmp=1;//记录桃的位置 
        for(int i=1;p[target].cards[i]!='P';i++) tmp=i;//记录 
        for(int i=tmp+1;i<=p[target].numc;i++) p[target].cards[i-1]=p[target].cards[i];
        //我们肯定会用，所以把它覆盖掉 
        p[target].nump--;//桃数减1 
        p[target].numc--;//牌数减1 
        p[target].life++;//生命加1 
    }    
    if(usep==false){ //不用桃 
        p[target].DEAD=false;//就会死 
        if(target==1){//如果是主猪死了 
            winn=2;//反猪赢了 
            print();//输出 
        }
        if(p[target].id==3){//如果是反猪死了 
            k--;//反猪总数减1 
            if(k==0){//如果反猪死光了 
                winn=1;//主猪赢了 
                print();//输出 
            }
        }
        p[p[target].pl].pr=p[target].pr;//死掉的猪的上家的下家变成死掉的猪的下家 
        p[p[target].pr].pl=p[target].pl;//死掉的猪的下家的上家变成死掉的猪的上家 
        if(from==1&&p[target].id==2){//如果主猪干掉了忠猪 
            p[1].zgln=0;//弃掉诸葛连弩 
            p[1].numc=0;//弃掉所有手牌 
            p[1].numk=0;//弃掉杀 
            p[1].nump=0;//弃掉桃 
            p[1].nums=0;//弃掉闪 
            p[1].numwxkj=0;//弃掉无懈可击 
        }
        if(p[target].id==3){//如果杀死了反猪 
            for(int i=1;i<=3;i++){//摸三张牌 
                p[from].numc++;//牌数加1 
                p[from].cards[p[from].numc]=get_card();//摸牌 
                if(p[from].cards[p[from].numc]=='K') p[from].numk++;//记录杀 
                if(p[from].cards[p[from].numc]=='D') p[from].nums++;//记录闪 
                if(p[from].cards[p[from].numc]=='P') p[from].nump++;//记录桃 
                if(p[from].cards[p[from].numc]=='J') p[from].numwxkj++;//记录无懈可击 
            }
        }
    }
}

void findjd(int q){//找到决斗的目标 
    for(int i=p[q].pr;i!=q;i=p[i].pr){//逆时针找跳反的猪或是类反猪 
        if((q==1&&(p[i].zhu==2||p[i].zhu==3))||(p[i].zhu==2&&p[q].id==2)){
            //主猪跳反的猪和类反猪都会打，忠猪只会打跳反的猪 
            p[q].targetjd=i;//确定就是他 
            return;
        }
    }
    p[q].target=0;//没有目标 
}
void findk(int q){
    if(p[q].id==2){//如果是忠猪 
        if(p[p[q].pr].zhu==2) p[q].target=p[q].pr;
        //zhu等于2表示跳反，如果忠猪的下家是跳反的猪，那么忠猪就会打他 
        else p[q].target=0;//否则不会打    注意：不能打到自己的上家！！！ 
    }
    else if(p[q].id==1){//如果是主猪 
        if(p[p[q].pr].zhu==2||p[p[q].pr].zhu==3) p[q].target=p[q].pr;
        //主猪跳反的猪和类反猪都会打，只要下家是他们中的任何一个，主猪都会打他 
        else p[q].target=0;//否则不会打 
    }
    else if(p[q].id==3){//如果是反猪 
        if(p[p[q].pr].zhu==1) p[q].target=p[q].pr;//反猪只会打主猪和跳忠的猪 
        else p[q].target=0;//否则不会打 
    }
}
void dojd(int from,int target){
    if(p[from].zhu==0||p[from].zhu==3){//如果是未知身份或是类反猪 
        if(p[target].zhu==1) p[from].zhu=2;//如果目标是主猪，直接跳反 
        else p[from].zhu=1;//否则目标一定是反猪，是跳忠 
    }
    bool wxkj=findwxkj(from,p[target].zhu);//看看能不能找到无懈可击 
    if(wxkj==true) return;//如果能出无懈可击，直接返回 
    if(p[target].id==2&&from==1){//如果主猪找忠猪决斗 
        p[target].life--;//忠猪不会弃置杀 
        if(p[target].life<=0) DIE(from,target);//如果主猪把忠猪弄死了，看看能不能用桃 
        return;//返回 
    }
    int nowpig=target;//开始决斗，先是目标猪弃置杀 
    while(p[nowpig].numk>0){//有杀 
        int tmp=1;//记录杀的位置 
        for(int i=1;p[nowpig].cards[i]!='K';i++) tmp=i;//找到杀的位置 
        for(int i=tmp+1;i<=p[nowpig].numc;i++) p[nowpig].cards[i-1]=p[nowpig].cards[i];
        //覆盖掉这张杀，因为我们要用它 
        p[nowpig].numc--;//牌数减一 
        p[nowpig].numk--;//杀数减一 
        if(nowpig==target) nowpig=from;
        else nowpig=target;//交换出牌方 
    }
    p[nowpig].life--;//输了的猪减血 
    int winner;
    if(nowpig==target) winner=from;
    else winner=target;//存储赢了的猪 
    if(p[nowpig].life<=0) DIE(winner,nowpig);//如果决斗死了，看看能不能用桃 
}
void dokill(int from,int target){//杀 
    if(p[from].zhu==0||p[from].zhu==3){//如果杀手是未知猪或是类反猪 
        if(p[target].zhu==1) p[from].zhu=2;//如果目标是主猪或是已经跳忠了的猪，标记为跳反的猪 
        else p[from].zhu=1;//标记为跳忠的猪 
    }
    if(p[target].nums>0){//如果被杀的猪有闪 
        int tmp=1;//记录闪的位置 
        for(int i=1;p[target].cards[i]!='D';i++) tmp=i;//记录 
        for(int i=tmp+1;i<=p[target].numc;i++) p[target].cards[i-1]=p[target].cards[i];
        //因为我们要用这张闪，所以我们要把它覆盖掉 
        p[target].nums--;//总牌数减1 
        p[target].numc--;//闪的数量减1 
    }
    else{//没有闪 
        p[target].life--;//减血 
        if(p[target].life<=0) DIE(from,target);//如果死掉了，看看能不能用桃 
    }
}
void donzrq(int from){//南猪入侵 
    for(int i=p[from].pr;i!=from;i=p[i].pr){//枚举除发起者之外的每一个猪 
        bool flag=findwxkj(from,p[i].zhu);//如果有无懈可击 
        if(flag==1) continue;//不会受到伤害 
        if(p[i].numk>0){//如果有杀 
            int tmp=1;
            for(int j=1;p[i].cards[j]!='K';j++) tmp=j;//记录杀的位置 
            for(int j=tmp+1;j<=p[i].numc;j++) p[i].cards[j-1]=p[i].cards[j];//覆盖掉杀 
            p[i].numc--;//手牌数减1 
            p[i].numk--;//杀数减1 
            flag=1;//标记为不受到伤害 
        }
        if(flag==1) continue;//如果出杀了，不受到伤害 
        if(i==1&&p[from].zhu==0) p[from].zhu=3;//如果未知猪伤害了主猪，认为他是类反猪 
        p[i].life--;//生命值减1 
        if(p[i].life<=0) DIE(from,i);//如果死了，结算 
    }
}
void dowjqf(int from){//万箭齐发 
    for(int i=p[from].pr;i!=from;i=p[i].pr){//举除发起者之外的每一个猪 
        bool flag=findwxkj(from,p[i].zhu);//如果有无懈可击 
        if(flag==1) continue;//不会受到伤害 
        if(p[i].nums>0){//如果有闪 
            int tmp=1;
            for(int j=1;p[i].cards[j]!='D';j++) tmp=j;//记录闪的位置 
            for(int j=tmp+1;j<=p[i].numc;j++) p[i].cards[j-1]=p[i].cards[j];//覆盖掉闪 
            p[i].numc--;//手牌数减1 
            p[i].nums--;//闪数减1 
            flag=1;//标记为不受到伤害 
        }
        if(flag==1) continue;//如果出闪了，不受到伤害 
        if(i==1&&p[from].zhu==0) p[from].zhu=3;//如果未知猪伤害了主猪，认为他是类反猪 
        p[i].life--;//生命值减1
        if(p[i].life<=0) DIE(from,i);//如果死了，结算 
    }
}
void oneround(int q){ 
    for(int i=1;i<=2;i++){//摸两张牌 
        char ch=get_card();//摸牌 
        p[q].numc++; 
        p[q].cards[p[q].numc]=ch;//记录 
        if(ch=='K') p[q].numk++;
        else if(ch=='D') p[q].nums++; 
        else if(ch=='P') p[q].nump++;
        else if(ch=='J') p[q].numwxkj++;//记录种类 
    }
    int kills=0;//这回合没有杀过 
    for(int i=1;p[q].numc>0&&i<=p[q].numc;i++){//枚举它的手牌 
        if(p[q].cards[i]=='Z'){//有诸葛连弩 
            for(int j=i+1;j<=p[q].numc;j++) p[q].cards[j-1]=p[q].cards[j];
            //用后面的牌把这张牌覆盖掉 
            p[q].numc--;//牌数减1 
            p[q].zgln=1;//有诸葛连弩 
            i=0;//重新扫一遍 
        }
        if(p[q].cards[i]=='F'){//有决斗 
            if(p[q].id!=3) findjd(q);//找到决斗的目标 
            if(p[q].targetjd!=0){//能找到目标 
                for(int j=i+1;j<=p[q].numc;j++) p[q].cards[j-1]=p[q].cards[j];
                //同上，覆盖掉这张牌 
                p[q].numc--;//牌数减1 
                dojd(q,p[q].targetjd);//决斗对方 
                if(p[q].DEAD==false) return; //如果死了，返回 
                i=0;//重新扫牌 
            }
        } 
        if(p[q].cards[i]=='K'&&(kills==0||p[q].zgln==1)){//有杀并且能杀
            findk(q);//找到杀的目标 
            if(p[q].target!=0){//能找到目标 
                for(int j=i+1;j<=p[q].numc;j++) p[q].cards[j-1]=p[q].cards[j];
                //同上，覆盖掉这张牌 
                p[q].numc--;//牌数减1 
                p[q].numk--;//杀数减1 
                dokill(q,p[q].target);//杀对方 
                kills++;//杀过了 
                i=0;//重新扫一遍 
            }
        }
        if(p[q].cards[i]=='P'&&p[q].life<4){//有桃并且不是满血 
            for(int j=i+1;j<=p[q].numc;j++) p[q].cards[j-1]=p[q].cards[j];
            //同上，覆盖掉这张牌 
            p[q].numc--;//牌数减1 
            p[q].nump--;//桃数减1 
            p[q].life++;//血量加1 
            i--;//从上一张牌开始扫 
        }
        if(p[q].cards[i]=='N'){//有南猪入侵 
            for(int j=i+1;j<=p[q].numc;j++) p[q].cards[j-1]=p[q].cards[j];
            //同上，覆盖掉这张牌 
            p[q].numc--;//牌数减1 
            donzrq(q);//使用南猪入侵 
            i=0;//重新扫一遍 
        }
        if(p[q].cards[i]=='W'){//有万箭齐发 
            for(int j=i+1;j<=p[q].numc;j++) p[q].cards[j-1]=p[q].cards[j];
            //同上，覆盖掉这张牌 
            p[q].numc--;//牌数减1 
            dowjqf(q);//使用万箭齐发 
            i=0; //重新扫一遍 
        }
    }
}
int main(){
    cin>>n>>m;
    top=m;
    int pig=1;
    for(int i=1;i<=n;i++) memset_(i);//初始化 
    for(int i=m;i>=1;i--) cards[i]=read();//读入初始牌堆  
    int i=1;
    while(END()==false){//游戏未结束
        oneround(pig);//进行一个猪的一回合 
        pig=p[pig].pr;//跳到下一头猪 
        i++;
    }
    print(); 
    return 0; 
}