#include <stdio.h>

#define MAX_CHOICES 4

typedef struct {
	int fuel;
	int food;
	int shields;
} Ship;

void greeting();
void ending();
void print_ship_attributes(Ship *ship);
void outcome_flee_pirates(Ship *ship);
void outcome_fight_pirates(Ship *ship);

int main() {

	int month = 1;
	Ship spaceship = {100, 100, 100};

	greeting();
	while (month < 10) {
		printf("It's month %d\n", month);
		outcome_fight_pirates(&spaceship);
		print_ship_attributes(&spaceship);
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

void print_ship_attributes(Ship *ship) {
	printf("Ship Status:\n");
	printf("	Fuel:    %d\n", ship->fuel);
	printf("	Food:    %d\n", ship->food);
	printf("	Shields: %d\n", ship->shields);
}

void outcome_flee_pirates(Ship *ship) {
	ship->fuel -= 50;
	ship->food -= 10;
}

void outcome_fight_pirates(Ship *ship) {
	ship->fuel -= 10;
	ship->food -= 10;
	ship->shields -= 70;
}
