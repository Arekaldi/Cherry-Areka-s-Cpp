#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int read(void) {
    int x, f = 1;
    char ch;
    while(!isdigit(ch = getchar()))
    (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 1) + (x << 3) + (ch ^ 48));
    return x * f;
}

void write(int x)
{
    if(x < 0)
        putchar('-'), x = -x;
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
    return;
}

int Heap[400010];
int n, tot;

void HeapInsert(int x) {
    Heap[++tot] = x;
    int now = tot;
    while(now > 1 && Heap[now] > Heap[now >> 1]) {
        int temp = Heap[now];
        Heap[now] = Heap[now >> 1];
        Heap[now >> 1] = temp;
        now >>= 1;
    }
    return;
}

void HeapDelete(void) {
    int temp = Heap[1];
    Heap[1] = Heap[tot--];
    Heap[tot + 1] = 0;
    int now = 1;
    while(now << 1 <= tot && (Heap[now] < Heap[now << 1] || Heap[now] < Heap[now << 1 | 1])) {
        int lValue = Heap[now << 1], rValue = Heap[now << 1 | 1];
        if(lValue > rValue && lValue > Heap[now]) {
            temp = lValue;
            Heap[now << 1] = Heap[now];
            Heap[now] = temp;
            now <<= 1;
        }
        else if(now << 1 | 1 <= tot && rValue > Heap[now]) {
            temp = rValue;
            Heap[now << 1 | 1] = Heap[now];
            Heap[now] = temp;
            now = now << 1 | 1;
        }
    }
    return;
}

int HeapQuery(void) {
    return Heap[1];
}

int HeapEmpty(void) {
    return Heap[1] == 0;
}

int main() {
    n = read();
    for(int i = 1; i <= n; ++i) {
        int opt = read();
        switch(opt) {
            case 1:
                HeapInsert(read());
                break;
            case 2:
                HeapDelete();
                break;
            case 3:
                printf("%d\n", HeapQuery());
                break;
        }
    }
    while(!HeapEmpty()) {
        write(HeapQuery());
        HeapDelete();
        putchar(' ');
    }
    return 0;
}