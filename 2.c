#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void tabulate(float a, float b, float h, void (*func)(float, float, float));
void tabulate_while(float a, float b, float h);
void tabulate_for(float a, float b, float h);
void tabulate_dowhile(float a, float b, float h);
float fn(float x);

int main(void) {
	float a = 1., b = 9., h = 1.;
	tabulate(a, b, h, tabulate_for);
	tabulate(a, b, h, tabulate_while);
	tabulate(a, b, h, tabulate_dowhile);
}

float fn(float x) {
	return x * cbrt(1. - x);
}

void tabulate(float a, float b, float h, void (*function)(float, float, float)) {
	function(a, b, h);
}

void tabulate_for(float a, float b, float h) {
	printf("Tabulate (for):\n");
	for(float x = a; x <= b; x += h) {
		printf("| %5.1f | %5.1f |\n", x, fn(x));	
	}
}

void tabulate_while(float a, float b, float h) {
	printf("Tabulate (while):\n");
	float x = a;
	while(x <= b) {
		printf("| %5.1f | %5.1f |\n", x, fn(x));	
		x += h;
	}

}

void tabulate_dowhile(float a, float b, float h) {
	printf("Tabulate (do while):\n");
	float x = a;
	do {
		printf("| %5.1f | %5.1f |\n", x, fn(x));	
		x += h;
	} while(x <= b);

}
