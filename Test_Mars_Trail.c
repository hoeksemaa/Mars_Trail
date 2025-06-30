#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CHOICES 4
#define MAX_EVENTS 10
#define MAX_WIDTH 4
#define MAX_OUTCOMES 4
#define MAX_TEXT

typedef struct {
	char description[MAX_TEXT];
	int probability;
	int fuel_delta;
	int food_delta;
	int shields_delta;
} Outcome;

typedef struct {
	char description[MAX_TEXT];
	Outcome outcomes[MAX_OUTCOMES];
	int num_outcomes;
} Choice;

typedef struct {
	char title[MAX_TEXT];
	char description[MAX_TEXT];
	int num_choices;
	Choice choices[MAX_CHOICES];
} Event;

typedef struct {
	int month;
	int fuel;
	int food;
	int shields;
} Gamestate;

void greeting();
void good_ending();
void bad_ending();
void print_ship_attributes(Ship *ship);

// pirate outcomes
void outcome_flee_pirates(Ship *ship);
void outcome_fight_pirates(Ship *ship);

Event* initialize_events();
Event* get_random_event(Event* events, int num_events);
int get_user_choice(Event* event);
bool is_ship_alive(Ship *ship);

int main() {

	int month = 1;
	Ship spaceship = {100, 100, 100};
	Event* events = initialize_events();
	int num_events = 1;
	int user_choice;
	Event* current_event;

	srand(12345);
	
	greeting();
	while (month < 10) {

		system("clear");
		printf("It's month %d\n", month);

		print_ship_attributes(&spaceship);
		
		current_event = get_random_event(events, num_events);
		
		printf("EVENT: %s\n", current_event->title);
		printf("%s", current_event->description);

		user_choice = get_user_choice(current_event);
		current_event->choices[user_choice - 1].outcome(&spaceship);

		printf("TITLE:       %s", current_event->title);
		printf("\n");
		printf("USER CHOICE: %d", user_choice);
		printf("\n");

		if (strcmp(current_event->title, "WORMHOLE") == 0 && user_choice == 2) {
			month += 2;
		}

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
	printf("        Shields:    %*d\n", MAX_WIDTH, ship->shields);
}

void outcome_flee_pirates(Ship *ship) {
	ship->fuel -= 50;
	ship->food -= 10;
	ship->shields -= 10;
}

void outcome_fight_pirates(Ship *ship) {
	ship->fuel -= 10;
	ship->food -= 10;
	ship->shields -= 50;
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
