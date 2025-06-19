#include <stdio.h>

#define MAX_CHOICES 4

typedef struct {
	int fuel;
	int food;
	int shields;
} Ship;

typedef struct {
	char description[100];
	void (*outcome)(Ship *ship);
} Choice;

typedef struct {
	char title[50];
	char description[100];
	int num_choices;
	Choice choices[MAX_CHOICES];
} Event;

void greeting();
void ending();
void print_ship_attributes(Ship *ship);
void outcome_flee_pirates(Ship *ship);
void outcome_fight_pirates(Ship *ship);

int main() {

	int month = 1;
	Ship spaceship = {100, 100, 100};
	Event pirates = {
		"PIRATE ATTACK",
		"The pirates have spotted your ship; they look mean and hungry!",
		2,
		{
			{"Fight", outcome_fight_pirates},
			{"Flee", outcome_flee_pirates}
		}	
	};

	greeting();
	while (month < 10) {
		printf("It's month %d\n", month);
		// EVENT STUFF GOES HERE
		// TOO TIRED TO WRITE IT RN
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
