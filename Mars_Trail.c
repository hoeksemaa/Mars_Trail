#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CHOICES 4
#define MAX_EVENTS 10
#define MAX_WIDTH 4

typedef struct {
	int fuel;
	int food;
	int shields;
	int crystals;
	int cigarettes;
	int morale;
} Ship;

typedef struct {
	char description[100];
	void (*outcome)(Ship *ship);
} Choice;

typedef struct {
	char title[50];
	char description[200];
	int num_choices;
	Choice choices[MAX_CHOICES];
} Event;

void greeting();
void good_ending();
void bad_ending();
void print_ship_attributes(Ship *ship);

// all Event outcomes
void outcome_flee_pirates(Ship *ship);
void outcome_fight_pirates(Ship *ship);
void outcome_rob_pizza(Ship *ship);
void outcome_buy_pizza(Ship *ship);
void outcome_leave(Ship *ship);
void outcome_chew_him_out(Ship *ship);
void outcome_smoke_together(Ship *ship);
void outcome_dont_care(Ship *ship);
void outcome_give_nothing(Ship *ship);
void outcome_give_food(Ship *ship);
void outcome_give_cigarette(Ship *ship);

Event* initialize_events();
Event* get_random_event(Event* events, int num_events);
int get_user_choice(Event* event);
bool is_ship_alive(Ship *ship);

int main() {

	int month = 1;
	Ship spaceship = {100, 100, 100, 100, 0, 100};
	Event* events = initialize_events();
	int num_events = 4;
	int user_choice;
	Event* current_event;

	srand(0);

	greeting();
	while (month < 10) {
		printf("It's month %d\n", month);

		print_ship_attributes(&spaceship);
		
		current_event = get_random_event(events, num_events);
		
		printf("EVENT: %s\n", current_event->title);
		printf("%s", current_event->description);

		user_choice = get_user_choice(current_event);
		current_event->choices[user_choice - 1].outcome(&spaceship);

		if (is_ship_alive(&spaceship) == false) {
			bad_ending();
			break;
		}
		
		month++;
	}
	
	// the ship survived through all 9 months, so trigger the good ending
	if (month == 10) {
		good_ending();	
	}
	
	return 0;
}

void greeting() {
	printf("Get ur ass in that spaceship\n");
}

void good_ending() {
	printf("You safely touch down on the planet Mars! You become national heroes back at home. Unfortunately, you're not back at home.\n");
}

void bad_ending() {
	printf("A crack splits your ship. As you're thrown into space and feel the air ripped from your lungs, you notice the stars look beautiful tonight.\n");
}

void print_ship_attributes(Ship *ship) {
	printf("Ship Status:\n");
	printf("	Fuel:       %*d\n", MAX_WIDTH, ship->fuel);
	printf("	Food:       %*d\n", MAX_WIDTH, ship->food);
	printf("	Shields:    %*d\n", MAX_WIDTH, ship->shields);
	printf("        Crystals:   %*d\n", MAX_WIDTH, ship->crystals);
	printf("        Cigarettes: %*d\n", MAX_WIDTH, ship->cigarettes);
	printf("        Morale:     %*d\n", MAX_WIDTH, ship->morale);
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

void outcome_rob_pizza(Ship *ship) {
	ship->food += 50;
	ship->fuel -= 10;
}

void outcome_buy_pizza(Ship *ship) {
	ship->food += 50;
	ship->crystals -= 50;
	ship->fuel -= 10;
}

void outcome_leave(Ship *ship) {
	ship->fuel -= 10;
}

void outcome_chew_him_out(Ship *ship) {
	ship->morale -= 20;
}

void outcome_smoke_together(Ship *ship) {
	ship->morale += 20;
	ship->cigarettes += 1;
}

void outcome_dont_care(Ship *ship) {
	ship->morale += 10;
}

void outcome_give_nothing(Ship *ship) {
	ship->fuel -= 10;
}

void outcome_give_food(Ship *ship) {
	ship->food -= 10;
	ship->fuel += 30;
}

void outcome_give_cigarette(Ship *ship) {
	ship->cigarettes -= 1;
	ship->fuel += 300;
}

Event* initialize_events() {
	static Event game_events[MAX_EVENTS];

	game_events[0] = (Event){
		"PIRATE ATTACK",
		"The pirates have spotted your ship, and they look mean and hungry!\n",
		2,
		{
			{"Fight", outcome_fight_pirates},
			{"Flee", outcome_flee_pirates}
		}
	};

	game_events[1] = (Event){
		"PAPA ZORB'S PIZZA",
		"You spot a rusty red shack nestled in an asteroid.\"Welcome to Papa Zorb's, home of the glorpiest pizza in the galaxy. What can i getcha?\"\n",
		3,
		{
			{"Rob the pizza", outcome_rob_pizza},
			{"Buy the pizza", outcome_buy_pizza},
			{"Leave emptyhanded", outcome_leave}
		}
	};

	game_events[2] = (Event){
		"CAUGHT REDHANDED",
		"One night, you can't sleep. You decide to go on a walk around the ship instead. What's this?! You catch the doctor smoking! NASA treats everything flammable like the plague.",
		3,
		{
			{"Chew him out", outcome_chew_him_out},
			{"Fuck it. Pass me one", outcome_smoke_together},
			{"Walk away. Pretend it didn't happen", outcome_dont_care}
		}
	};

	game_events[3] = (Event){
		"PLUG'S BUTT-UGLY FUEL TANKER",
		"An old man with a white handlebar mustasche in an 18-wheeler fuel truck pulls up next to you. \"I've been moving this cargo for 3 weeks straight now. Got anything to take the edge off?\"",
		3,
		{
			{"Sorry; supplies are tight", outcome_give_nothing},
			{"Give him a tortilla", outcome_give_food},
			{"Give him a cigarette", outcome_give_cigarette}
		}
	};

	return game_events;
}

Event* get_random_event(Event* events, int num_events) {
	int idx = rand() % num_events;
	return &events[idx];
}

int get_user_choice(Event* event) {
	int user_choice;

	printf("What do you want to do?\n");
	for (int i = 0; i < event->num_choices; i++) {
		printf("%d. %s\n", 1 + i, event->choices[i].description);
	}

	printf("Enter your choice: ");
	scanf("%d", &user_choice);

	return user_choice;
}

bool is_ship_alive(Ship *ship) {
	if (ship->shields < 0) {
		return false;
	} else {
		return true;
	}
}
