#include <stdio.h>
#include <stdlib.h>

#define MAX_CHOICES 4
#define MAX_EVENTS 10

typedef struct {
	int fuel;
	int food;
	int shields;
	int crystals;
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
void ending();
void print_ship_attributes(Ship *ship);
void outcome_flee_pirates(Ship *ship);
void outcome_fight_pirates(Ship *ship);
void outcome_rob_pizza(Ship *ship);
void outcome_buy_pizza(Ship *ship);
Event* initialize_events();
Event* get_random_event(Event* events, int num_events);
int get_user_choice(Event* event);

int main() {

	int month = 1;
	Ship spaceship = {100, 100, 100, 100};
	Event* events = initialize_events();
	int num_events = 2;
	int user_choice;
	Event* current_event;

	srand(0);

	greeting();
	while (month < 10) {
		printf("It's month %d\n", month);
		
		current_event = get_random_event(events, num_events);
		
		printf("EVENT: %s\n", current_event->title);
		printf("%s", current_event->description);

		user_choice = get_user_choice(current_event);
		current_event->choices[user_choice - 1].outcome(&spaceship);

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
	printf("	Fuel:     %d\n", ship->fuel);
	printf("	Food:     %d\n", ship->food);
	printf("	Shields:  %d\n", ship->shields);
	printf("        Crystals: %d\n", ship->crystals);
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
}

void outcome_buy_pizza(Ship *ship) {
	ship->food += 50;
	ship->crystals -= 50;
}

Event* initialize_events() {
	static Event game_events[MAX_EVENTS];

	game_events[0] = (Event){
		"PIRATE ATTACK",
		"The pirates have spotted your ship, and they look mean and hungry!",
		2,
		{
			{"Fight", outcome_fight_pirates},
			{"Flee", outcome_flee_pirates}
		}
	};

	game_events[1] = (Event){
		"PAPA ZORB'S PIZZA",
		"You spot a rusty red shack nestled in an asteroid. \"Welcome to Papa Zorb's, home of the glorpiest pizza in the galaxy. What can i getcha?\"",
		2,
		{
			{"Rob the pizza", outcome_rob_pizza},
			{"Buy the pizza", outcome_buy_pizza}
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
