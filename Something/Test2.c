extern int test[];

static int tt1;

void swap() {
	int temp = test[0];
	test[0] = test[1];
	test[1] = temp;
	return;
}
