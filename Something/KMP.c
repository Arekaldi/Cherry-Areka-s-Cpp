#include <stdio.h> 
#include <stdlib.h>

char *s1, *s2, **Next;

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        s1 = (char *)malloc(sizeof(char) * (1e6 + 10));
        s2 = (char *)malloc(sizeof(char) * (1e6 + 10));
        Next = (char **)malloc(sizeof(char *) * (1e6 + 10));
        int *output = (int *)malloc(sizeof(int) * (1e5 + 2));
        int tot = 0;
        scanf("%s%s", s1 + 1, s2 + 1);
        *(Next + 1) = *(Next + 2) = s2;
        
        char *q = s2;
        for(char *p = s2 + 2; *p != '\0'; ++p) {
            while(q != s2 && *(q + 1) != *p)
                q = *(Next + (q - s2));
            if(*(q + 1) == *p)
                *(Next + (p - s2)) = ++q;
            else
                *(Next + (p - s2)) = s2;
        }

        q = s2;
        for(char *p = s1 + 1; *p != '\0'; ++p) {
            while(q != s2 && *p != *(q + 1))
                q = *(Next + (q - s2));
            if(*p == *(q + 1))
                q++;
            if(*(q + 1) == '\0') {
                output[++tot] = p - s1 - (q - s2) + 1;
                q = *(Next + (q - s2));
            }
        }
        printf("%d ", tot);
        for(int i = 1; i <= tot; ++i)
            printf("%d ", output[i]);
        puts("");
        free(s1);
        free(s2);
        free(Next);
    }
}