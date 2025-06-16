#include <stdio.h>

#define MAX_CHOICES 4

void greeting();
void ending();

typedef struct {
	int fuel;
	int food;
	int shields;
} Ship;

typedef struct {
	char description[200];
	int fuel_change;
	int food_change;
	int shields_change;
} Choice;

typedef struct {
	char title[100];
	char description[200];
	Choice choices[MAX_CHOICES];
	int num_choices;
} Event;

int main() {

	int month = 1;
	Spaceship Ship = {100, 100, 100};

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
