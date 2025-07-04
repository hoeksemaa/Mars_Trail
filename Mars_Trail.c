#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
	int tires;
	int pilot;
	int doctor;
	int scientist;
} Ship;

typedef struct {
	char description[100];
	void (*outcome)(Ship *ship);
} Choice;

typedef struct {
	char title[50];
	char description[300];
	int num_choices;
	Choice choices[MAX_CHOICES];
} Event;

void greeting();
void good_ending();
void bad_ending();
void print_ship_attributes(Ship *ship);

// pirate outcomes
void outcome_flee_pirates(Ship *ship);
void outcome_fight_pirates(Ship *ship);

// pizza outcomes
void outcome_rob_pizza(Ship *ship);
void outcome_buy_pizza(Ship *ship);
void outcome_leave(Ship *ship);

// smoking outcomes
void outcome_chew_him_out(Ship *ship);
void outcome_smoke_together(Ship *ship);
void outcome_dont_care(Ship *ship);

// fuel tanker outcomes
void outcome_give_nothing(Ship *ship);
void outcome_give_food(Ship *ship);
void outcome_give_cigarette(Ship *ship);

// alien capitalists outcomes
void outcome_trade_nothing(Ship *ship);
void outcome_insult_them(Ship *ship);
void outcome_trade_small_fuel(Ship *ship);
void outcome_trade_small_fuel(Ship *ship);

// wormhole
void outcome_keep_flying(Ship *ship);
void outcome_go_in(Ship *ship);

// snakes
void outcome_let_pilot_die(Ship *ship);
void outcome_kill_doctor_save_pilot(Ship *ship);

// IRS
void outcome_flee_irs(Ship *ship);
void outcome_fight_irs(Ship *ship);
void outcome_bribe_irs(Ship *ship);
void outcome_pay_irs(Ship *ship);

// leif erikson
void outcome_give_him_food(Ship *ship);
void outcome_follow_map(Ship *ship);
void outcome_ignore_him(Ship *ship);

Event* initialize_events();
Event* get_random_event(Event* events, int num_events);
int get_user_choice(Event* event);
bool is_ship_alive(Ship *ship);

int main() {

	int month = 1;
	Ship spaceship = {100, 100, 100, 100, 0, 100, 0, 1, 1, 1};
	Event* events = initialize_events();
	int num_events = 9;
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
	printf("	Shields:    %*d\n", MAX_WIDTH, ship->shields);
	printf("        Crystals:   %*d\n", MAX_WIDTH, ship->crystals);
	printf("        Cigarettes: %*d\n", MAX_WIDTH, ship->cigarettes);
	printf("        Morale:     %*d\n", MAX_WIDTH, ship->morale);
	printf("        Tires:      %*d\n", MAX_WIDTH, ship->tires);
	printf("        Pilot:      %*d\n", MAX_WIDTH, ship->pilot);
	printf("        Doctor:     %*d\n", MAX_WIDTH, ship->doctor);
	printf("        Scientist:  %*d\n", MAX_WIDTH, ship->scientist);
}

void outcome_flee_pirates(Ship *ship) {
	ship->fuel -= 30;
	ship->food -= 10;
}

void outcome_fight_pirates(Ship *ship) {
	ship->fuel -= 10;
	ship->food -= 10;
	ship->shields -= 20;
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

void outcome_trade_nothing(Ship *ship) {
	ship->fuel -= 10;
}

void outcome_insult_them(Ship *ship) {
	ship->shields -= 90;
	ship->fuel -= 30;
	ship->morale += 30;
}

void outcome_trade_small_fuel(Ship *ship) {
	ship->fuel -= 10;
	ship->shields += 20;
}

void outcome_trade_large_fuel(Ship *ship) {
	ship->fuel -= 200;
	ship->tires += 1;
}

void outcome_keep_flying(Ship *ship) {
	ship->fuel -= 10;
}

void outcome_go_in(Ship *ship) {
	ship->fuel += 10;
}

void outcome_let_pilot_die(Ship *ship) {
	ship->pilot -= 1;
}

void outcome_kill_doctor_save_pilot(Ship *ship) {
	ship->doctor -= 1;
}

void outcome_give_him_food(Ship *ship) {
	ship->food -= 10;
	ship->morale += 50;
}

void outcome_follow_map(Ship *ship) {
	ship->fuel += 40;
	ship->morale += 20;
}

void outcome_ignore_him(Ship *ship) {
	ship->fuel -= 10;
}

void outcome_flee_irs(Ship *ship) {
	ship->crystals -= 100;
	ship->fuel -= 200;
	ship->morale -= 10;
}

void outcome_fight_irs(Ship *ship) {
	ship->crystals -= 100;
	ship->doctor -= 1;
	ship->scientist -= 1;
	ship->morale -= 10;
}

void outcome_bribe_irs(Ship *ship) {
	ship->crystals -= 100;
	ship->morale -= 100;
}

void outcome_pay_irs(Ship *ship) {
	ship->crystals -= 100;
	ship->morale -= 10;
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

	game_events[4] = (Event){
		"ALIEN CAPITALISTS",
		"Long-tentacled aliens with 5 large green eyes knock politely on your ship door. \"Wxould yxou lxike txo txrade sxome fxuel txo uxs? wxe wxill cxompensate yxou axs bxest wxe cxan.\" They wait patiently for your reply.",
		4,
		{
			{"Sorry; supplies are tight", outcome_trade_nothing},
			{"They look funny! Call them the worst word you know.", outcome_insult_them},
			{"We can spare a little", outcome_trade_small_fuel},
			{"Fuck it; take almost everything", outcome_trade_large_fuel}
		}
	};

	game_events[5] = (Event){
		"WORMHOLE",
		"The ship sensors pick up a wormhole; it's barely within their range. Who knows where it will lead. Steer into it?",
		2,
		{
			{"Not worth it. Maintain course", outcome_keep_flying},
			{"Cowabunga dude!", outcome_go_in}
		}
	};

	game_events[6] = (Event){
		"SNAKE",
		"The pilot has suited up in his EVA suit and is changing the spaceship's flat tire. Suddenly, a snake rushes out of the darkness and sinks its teeth into the pilot's ankle! The pilot is beginning to bleed out...",
		2,
		{
			{"Let the pilot die. There's no way to save him", outcome_let_pilot_die},
			{"Kill the doctor and give his blood to the pilot. It might stabilize him", outcome_kill_doctor_save_pilot}
		}
	};

	game_events[7] = (Event){
		"VISIT FROM THE IRS",
		"You're sipping your morning coffee when you hear a loud banging on the ship's entry port. \"THIS IS THE IRS. OUR RECORDS INDICATE YOU HAVE SIGNIFICANT UNPAID TAX LIABILITIES FROM THE PAST FIVE YEARS. YOU WILL LET US IN AND PROVIDE ALL FINANCIAL RECORDS UP TO TWELVE YEARS IN THE PAST.\"",
		4,
		{
			{"We're getting out of here! Engines to max! Flee the scene.", outcome_flee_irs},
			{"I'm not going down without a fight! Draw your NASA-standard-issue S&W revolver", outcome_fight_irs},
			{"I'm sure you're mistaken. Make a large contribution to the agent's child's college fund.", outcome_bribe_irs},
			{"Sigh heavily. Let them in.", outcome_pay_irs}
		}
	};

	game_events[8] = (Event){
		"LEIF ERIKSON",
		"You find famed explorer Leif Erikson drifting through space, alive and kicking at the ripe age of 1050 years old. He looks up from studying a star map. \"I'm famished! Got anything to eat?\" You notice he's circled a portion of his map and labelled it \"Fuel cloud\"",
		3,
		{
			{"Give him some food. He's probably got some crazy stories", outcome_give_food},
			{"Track down this fuel cloud", outcome_follow_map},
			{"Ignore him. He weirds me out", outcome_ignore_him}
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
