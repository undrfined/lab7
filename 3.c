#include <stdio.h>

int f(int x) {
	if(x < 3) return x;
	return f(x -= 3);
}
int main() {
	int a = 0, b = 30;
	for(int x = a; x <= b; x++) {
		printf("%d %% 3 == %d\n", x, f(x));
	}
	return 0;
}
