#include <stdio.h>

int test[] = {1, 2};
int tt1 = 10;

extern void swap();

int main() {
	printf("%d %d\n", test[0], test[1]);
	swap();
	printf("%d %d\n", test[0], test[1]);
}
