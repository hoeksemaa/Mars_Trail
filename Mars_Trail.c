#include <stdio.h>

void greeting();
void ending();

int main() {

	int month = 1;

	greeting();
	while (month < 10) {
		printf("It's month %d\n", month);
		month++;
	}
	ending();
	
	return 0;
}

void greeting() {
	printf("Get ur ass in that spaceship\n");
}

void ending() {
	printf("That's all Folks!\n");
}
