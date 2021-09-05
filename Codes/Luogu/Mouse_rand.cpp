#include<windows.h>
#include<cstdlib>
#include<ctime>
#include <iostream>
using namespace std;
int main()
{
    int x=GetSystemMetrics(SM_CXSCREEN); //更新马里奥初始位置，x.
    int y=GetSystemMetrics(SM_CYSCREEN); //更新马里奥初始位置，y. 
    srand(time(0)); //随机生成怪物. 
    int tot = 0;
    while(++tot <= 1000) {
        //游戏时间设为无线. 
        printf("%d\n", tot);
        SetCursorPos(rand()%x,rand()%y); //加载游戏中.
    }
    //运行后，就可以愉快的玩马里奥了！！（温馨提示：这个游戏操作很好，画面质朴，良心游戏.） 
    return 0;
}