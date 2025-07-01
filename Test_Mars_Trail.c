#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CHOICES 4
#define MAX_EVENTS 10
#define MAX_WIDTH 4
#define MAX_OUTCOMES 4
#define MAX_TEXT 100

typedef struct {
	int probability;
	char description[MAX_TEXT];
	int fuel_delta;
	int food_delta;
	int shields_delta;
} Outcome;

typedef struct {
	char description[MAX_TEXT];
	int num_outcomes;
	Outcome outcomes[MAX_OUTCOMES];
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
void print_gamestate(Gamestate *state);

// pirate outcomes
void outcome_flee_pirates(Gamestate *state);
void outcome_fight_pirates(Gamestate *state);

Event* initialize_events();
Event* get_random_event(Event* events, int num_events);
int get_user_choice(Event* event);
Outcome* execute_choice(Choice choice);
bool is_ship_alive(Gamestate *state);

int main() {

	Gamestate state = {1, 100, 100, 100};
	Event* events = initialize_events();
	int num_events = 1;
	int user_choice;
	Event* current_event;

	srand(12345);
	
	greeting();
	while (state.month < 10) {

		system("clear");
		printf("It's month %d\n", state.month);

		print_gamestate(&state);
		
		current_event = get_random_event(events, num_events);
		
		printf("EVENT: %s\n", current_event->title);
		printf("%s", current_event->description);

		user_choice = get_user_choice(current_event);
		Outcome* result = execute_choice(user_choice);
		//current_event->choices[user_choice - 1].outcome(&state);

		printf("TITLE:       %s", current_event->title);
		printf("\n");
		printf("USER CHOICE: %d", user_choice);
		printf("\n");

		if (strcmp(current_event->title, "WORMHOLE") == 0 && user_choice == 2) {
			state.month += 2;
		}

		if (is_ship_alive(&state) == false) {
			bad_ending();
			break;
		}
		
		state.month++;
	}
	
	// the ship survived through all 9 months, so trigger the good ending
	if (state.month == 10) {
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

void print_gamestate(Gamestate *state) {
	printf("Ship Status:\n");
	printf("	Fuel:       %*d\n", MAX_WIDTH, state->fuel);
	printf("	Food:       %*d\n", MAX_WIDTH, state->food);
	printf("        Shields:    %*d\n", MAX_WIDTH, state->shields);
}

void outcome_flee_pirates(Gamestate *state) {
	state->fuel -= 50;
	state->food -= 10;
	state->shields -= 10;
}

void outcome_fight_pirates(Gamestate *state) {
	state->fuel -= 10;
	state->food -= 10;
	state->shields -= 50;
}

Event* initialize_events() {
	static Event game_events[MAX_EVENTS];

	game_events[0] = (Event){
		"PIRATE ATTACK",
		"The pirates have spotted your ship, and they look mean and hungry!\n",
		2,
		{
			// fight
			{
				"FIGHT",
				3,
				{
					{50, "Minor injuries", 30, 0, 10},
					{40, "The pirates flee", 10, 0, 0},
					{10, "Major damage", 30, 0, 50}
				}
			},
			// flee
			{
				"FLEE",
				2,
				{
					{80, "Minor injuries", 30, 0, 10},
					{20, "Get away scott free", 30, 0, 0}
				}
			}
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

Outcome* execute_choice(Choice choice) {
	int roll = rand() % 100 + 1;
	int cumulative_prob = 0;

	for (int i = 0; i < choice.num_outcomes; i++) {
		cumulative_prob += choice.outcomes[i].probability;
		if (roll =< cumulative_prob) {
			return choice.outcomes[i];
		}
	}
}

bool is_ship_alive(Gamestate *state) {
	if (state->shields > 0) {
		return true;
	} else {
		return false;
	}
}
