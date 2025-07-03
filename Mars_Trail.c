#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CHOICES 4
#define MAX_EVENTS 10
#define MAX_WIDTH 4
#define MAX_TEXT 300

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
	int month;
} Gamestate;

typedef struct {
	char choice_description[MAX_TEXT];
	char result_description[MAX_TEXT];
	int fuel_delta;
	int food_delta;
	int shields_delta;
	int crystals_delta;
	int cigarettes_delta;
	int morale_delta;
	int tires_delta;
	int pilot_delta;
	int scientist_delta;
	int month_delta;	
} Choice;

typedef struct {
	char title[MAX_TEXT];
	char description[MAX_TEXT];
	int num_choices;
	Choice choices[MAX_CHOICES];
} Event;

void greeting();
void good_ending();
void bad_ending();
void print_state_attributes(Gamestate *state);

// pirate outcomes
void outcome_flee_pirates(Gamestate *state);
void outcome_fight_pirates(Gamestate *state);

// pizza outcomes
void outcome_rob_pizza(Gamestate *state);
void outcome_buy_pizza(Gamestate *state);
void outcome_leave(Gamestate *state);

// smoking outcomes
void outcome_chew_him_out(Gamestate *state);
void outcome_smoke_together(Gamestate *state);
void outcome_dont_care(Gamestate *state);

// fuel tanker outcomes
void outcome_give_nothing(Gamestate *state);
void outcome_give_food(Gamestate *state);
void outcome_give_cigarette(Gamestate *state);

// alien capitalists outcomes
void outcome_trade_nothing(Gamestate *state);
void outcome_insult_them(Gamestate *state);
void outcome_trade_small_fuel(Gamestate *state);
void outcome_trade_small_fuel(Gamestate *state);

// wormhole
void outcome_keep_flying(Gamestate *state);
void outcome_go_in(Gamestate *state);

// snakes
void outcome_let_pilot_die(Gamestate *state);
void outcome_kill_doctor_save_pilot(Gamestate *state);

// IRS
void outcome_flee_irs(Gamestate *state);
void outcome_fight_irs(Gamestate *state);
void outcome_bribe_irs(Gamestate *state);
void outcome_pay_irs(Gamestate *state);

// leif erikson
void outcome_give_him_food(Gamestate *state);
void outcome_follow_map(Gamestate *state);
void outcome_ignore_him(Gamestate *state);

Event* initialize_events();
Event* get_random_event(Event* events, int num_events);
int get_user_choice(Event* event);
bool is_state_alive(Gamestate *state);

int main() {

	Gamestate state = {100, 100, 100, 100, 0, 100, 0, 1, 1, 1, 1};
	Event* events = initialize_events();
	int num_events = 9;
	int user_choice;
	Event* current_event;

	srand(0);
	
	greeting();

	while (state.month < 10) {

		system("clear");
		printf("It's month %d\n", state.month);

		print_state_attributes(&state);
		
		current_event = get_random_event(events, num_events);
		
		printf("EVENT: %s\n", current_event->title);
		printf("%s", current_event->description);

		user_choice = get_user_choice(current_event);
		current_event->choices[user_choice - 1].outcome(&state);

		//printf("TITLE:       %s", current_event->title);
		//printf("\n");
		//printf("USER CHOICE: %d", user_choice);
		//printf("\n");

		if (is_state_alive(&state) == false) {
			bad_ending();
			break;
		}
		
		state.month++;
	}
	
	// the state survived through all 9 months, so trigger the good ending
	if (state.month == 10) {
		good_ending();	
	}
	
	return 0;
}

void greeting() {
	printf("Get ur ass in that spacestate\n");
}

void good_ending() {
	printf("You safely touch down on the planet Mars! You become national heroes back at home. Fortunately, you're not back at home.\n");
}

void bad_ending() {
	printf("A crack splits your state. As you're thrown into space and feel the air ripped from your lungs, you notice the stars look beautiful tonight.\n");
}

void print_state_attributes(Gamestate *state) {
	printf("Gamestate Status:\n");
	printf("	Fuel:       %*d\n", MAX_WIDTH, state->fuel);
	printf("	Food:       %*d\n", MAX_WIDTH, state->food);
	printf("	Shields:    %*d\n", MAX_WIDTH, state->shields);
	printf("        Crystals:   %*d\n", MAX_WIDTH, state->crystals);
	printf("        Cigarettes: %*d\n", MAX_WIDTH, state->cigarettes);
	printf("        Morale:     %*d\n", MAX_WIDTH, state->morale);
	printf("        Tires:      %*d\n", MAX_WIDTH, state->tires);
	printf("        Pilot:      %*d\n", MAX_WIDTH, state->pilot);
	printf("        Doctor:     %*d\n", MAX_WIDTH, state->doctor);
	printf("        Scientist:  %*d\n", MAX_WIDTH, state->scientist);
}

void outcome_flee_pirates(Gamestate *state) {
	state->fuel -= 30;
	state->food -= 10;
}

void outcome_fight_pirates(Gamestate *state) {
	state->fuel -= 10;
	state->food -= 10;
	state->shields -= 20;
}

void outcome_rob_pizza(Gamestate *state) {
	state->food += 50;
	state->fuel -= 10;
}

void outcome_buy_pizza(Gamestate *state) {
	state->food += 50;
	state->crystals -= 50;
	state->fuel -= 10;
}

void outcome_leave(Gamestate *state) {
	state->fuel -= 10;
}

void outcome_chew_him_out(Gamestate *state) {
	state->morale -= 20;
}

void outcome_smoke_together(Gamestate *state) {
	state->morale += 20;
	state->cigarettes += 1;
}

void outcome_dont_care(Gamestate *state) {
	state->morale += 10;
}

void outcome_give_nothing(Gamestate *state) {
	state->fuel -= 10;
}

void outcome_give_food(Gamestate *state) {
	state->food -= 10;
	state->fuel += 30;
}

void outcome_give_cigarette(Gamestate *state) {
	state->cigarettes -= 1;
	state->fuel += 300;
}

void outcome_trade_nothing(Gamestate *state) {
	state->fuel -= 10;
}

void outcome_insult_them(Gamestate *state) {
	state->shields -= 90;
	state->fuel -= 30;
	state->morale += 30;
}

void outcome_trade_small_fuel(Gamestate *state) {
	state->fuel -= 10;
	state->shields += 20;
}

void outcome_trade_large_fuel(Gamestate *state) {
	state->fuel -= 200;
	state->tires += 1;
}

void outcome_keep_flying(Gamestate *state) {
	state->fuel -= 10;
}

void outcome_go_in(Gamestate *state) {
	state->fuel += 10;
	state->month += 2;
}

void outcome_let_pilot_die(Gamestate *state) {
	state->pilot -= 1;
}

void outcome_kill_doctor_save_pilot(Gamestate *state) {
	state->doctor -= 1;
}

void outcome_give_him_food(Gamestate *state) {
	state->food -= 10;
	state->morale += 50;
}

void outcome_follow_map(Gamestate *state) {
	state->fuel += 40;
	state->morale += 20;
}

void outcome_ignore_him(Gamestate *state) {
	state->fuel -= 10;
}

void outcome_flee_irs(Gamestate *state) {
	state->crystals -= 100;
	state->fuel -= 200;
	state->morale -= 10;
}

void outcome_fight_irs(Gamestate *state) {
	state->crystals -= 100;
	state->doctor -= 1;
	state->scientist -= 1;
	state->morale -= 10;
}

void outcome_bribe_irs(Gamestate *state) {
	state->crystals -= 100;
	state->morale -= 100;
}

void outcome_pay_irs(Gamestate *state) {
	state->crystals -= 100;
	state->morale -= 10;
}

Event* initialize_events() {
	static Event game_events[MAX_EVENTS];

	game_events[0] = (Event){
		"PIRATE ATTACK",
		"The pirates have spotted your state, and they look mean and hungry!\n",
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
		"One night, you can't sleep. You decide to go on a walk around the state instead. What's this?! You catch the doctor smoking! NASA treats everything flammable like the plague.",
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
		"Long-tentacled aliens with 5 large green eyes knock politely on your state door. \"Wxould yxou lxike txo txrade sxome fxuel txo uxs? wxe wxill cxompensate yxou axs bxest wxe cxan.\" They wait patiently for your reply.",
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
		"The state sensors pick up a wormhole; it's barely within their range. Who knows where it will lead. Steer into it?",
		2,
		{
			{"Not worth it. Maintain course", outcome_keep_flying},
			{"Cowabunga dude!", outcome_go_in}
		}
	};

	game_events[6] = (Event){
		"SNAKE",
		"The pilot has suited up in his EVA suit and is changing the spacestate's flat tire. Suddenly, a snake rushes out of the darkness and sinks its teeth into the pilot's ankle! The pilot is beginning to bleed out...",
		2,
		{
			{"Let the pilot die. There's no way to save him", outcome_let_pilot_die},
			{"Kill the doctor and give his blood to the pilot. It might stabilize him", outcome_kill_doctor_save_pilot}
		}
	};

	game_events[7] = (Event){
		"VISIT FROM THE IRS",
		"You're sipping your morning coffee when you hear a loud banging on the state's entry port. \"THIS IS THE IRS. OUR RECORDS INDICATE YOU HAVE SIGNIFICANT UNPAID TAX LIABILITIES FROM THE PAST FIVE YEARS. YOU WILL LET US IN AND PROVIDE ALL FINANCIAL RECORDS UP TO TWELVE YEARS IN THE PAST.\"",
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

bool is_state_alive(Gamestate *state) {
	if (state->shields < 0) {
		return false;
	} else {
		return true;
	}
}
