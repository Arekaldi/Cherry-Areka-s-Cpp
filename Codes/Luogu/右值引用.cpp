#include <bits/stdc++.h>

using namespace std;

inline int read() {
	char ch;
	int x = 0, f = 1;
	while(!isdigit(ch = getchar()))
		(ch == '-') and (f = -1);
	for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 1) + (x << 3) + (ch ^ 48));
	return x * f;
}

const int maxn = 1e5 + 1;

void foo(int &)  { std::cout << "lvalue" << std::endl; }
void foo(int &&) { std::cout << "rvalue" << std::endl; }

signed main() {
  int &&rref = 1;
  foo(rref);    // which overload will be seleted?
}
