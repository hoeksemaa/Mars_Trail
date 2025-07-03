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
	char description[MAX_TEXT];
	char result[MAX_TEXT];
	int fuel_delta;
	int food_delta;
	int shields_delta;
	int crystals_delta;
	int cigarettes_delta;
	int morale_delta;
	int tires_delta;
	int pilot_delta;
	int doctor_delta;
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

Event* initialize_events();
Event* get_random_event(Event* events, int num_events);
int get_user_choice(Event* event);
bool is_state_alive(Gamestate *state);
void apply_choice(Gamestate *state, Event* current_event, int user_choice);

int main() {

	Gamestate state = {100, 100, 100, 100, 0, 100, 0, 1, 1, 1, 1};
	Event* events = initialize_events();
	int num_events = 9;
	int user_choice;
	Event* current_event;

	srand(0);
	
	greeting();

	while (state.month < 10) {

		//system("clear");
		printf("It's month %d\n", state.month);

		print_state_attributes(&state);
		
		current_event = get_random_event(events, num_events);
		
		printf("EVENT: %s\n", current_event->title);
		printf("%s", current_event->description);

		user_choice = get_user_choice(current_event);
		apply_choice(&state, current_event, user_choice);
		//current_event->choices[user_choice - 1].outcome(&state);

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

void apply_choice(Gamestate *state, Event* current_event, int user_choice) {
	Choice *choice = &current_event->choices[user_choice - 1];

	printf("\n%s\n", choice->result);

	// apply the deltas to the gamestate
	state->fuel       += choice->fuel_delta;
	state->food       += choice->food_delta;
	state->shields    += choice->shields_delta;
	state->crystals   += choice->crystals_delta;
	state->cigarettes += choice->cigarettes_delta;
	state->morale     += choice->morale_delta;
	state->tires      += choice->tires_delta;
	state->pilot      += choice->pilot_delta;
	state->doctor     += choice->doctor_delta;
	state->scientist  += choice->scientist_delta;
	state->month      += choice->month_delta;
}

Event* initialize_events() {
	static Event game_events[MAX_EVENTS];

	game_events[0] = (Event){
		"PIRATE ATTACK",
		"The pirates have spotted your state, and they look mean and hungry!\n",
		2,
		{
			{
				"Fight", 
				"ouchie",
				-30, -10, 0, 0, 0, 0, 0, 0, 0, 0, 0
			},
			{
				"Flee", 
				"zooooooooooom",
				-10, -10, -20, 0, 0, 0, 0, 0, 0, 0, 0
			}
		}
	};

	game_events[1] = (Event){
		"PAPA ZORB'S PIZZA",
		"You spot a rusty red shack nestled in an asteroid.\"Welcome to Papa Zorb's, home of the glorpiest pizza in the galaxy. What can i getcha?\"\n",
		3,
		{
			{
				"Rob the pizza", 
				"He doesn't react as you hop over the counter and pocket a greasy slice.",
				-10, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0
			},
			{
				"Buy the pizza", 
				"thx man $",
				-10, 50, 0, -50, 0, 0, 0, 0, 0, 0, 0
			},
			{
				"Leave emptyhanded", 
				"aight",
				-10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
			}
		}
	};

	game_events[2] = (Event){
		"CAUGHT REDHANDED",
		"One night, you can't sleep. You decide to go on a walk around the state instead. What's this?! You catch the doctor smoking! NASA treats everything flammable like the plague.",
		3,
		{
			{
				"Chew him out", 
				"wow how original",
				0, 0, 0, 0, 0, -20, 0, 0, 0, 0, 0
			},
			{
				"Fuck it. Pass me one", 
				"hel yea bruder",
				0, 0, 0, 0, 1, 20, 0, 0, 0, 0, 0
			},
			{
				"Walk away. Pretend it didn't happen",
				"seeya",
				0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0
			}
		}
	};

	game_events[3] = (Event){
		"PLUG'S BUTT-UGLY FUEL TANKER",
		"An old man with a white handlebar mustasche in an 18-wheeler fuel truck pulls up next to you. \"I've been moving this cargo for 3 weeks straight now. Got anything to take the edge off?\"",
		3,
		{
			{
				"Sorry; supplies are tight",
				"no worries bruv",
				-10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
			},
			{
				"Give him a tortilla",
				"o hel yea astronaut bread",
				30, -10, 0, 0, 0, 0, 0, 0, 0, 0, 0
			},
			{
				"Give him a cigarette",
				"smoooooooth mhm",
				300, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0
			}
		}
	};

	game_events[4] = (Event){
		"ALIEN CAPITALISTS",
		"Long-tentacled aliens with 5 large green eyes knock politely on your state door. \"Wxould yxou lxike txo txrade sxome fxuel txo uxs? wxe wxill cxompensate yxou axs bxest wxe cxan.\" They wait patiently for your reply.",
		4,
		{
			{
				"Sorry; supplies are tight",
				"fine :(",
				-10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
			},
			{
				"They look funny! Call them the worst word you know.",
				"why woud u do that",
				-30, 0, -90, 0, 0, 30, 0, 0, 0, 0, 0
			},
			{
				"We can spare a little",
				"hel yea :)",
				-20, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0
			},
			{
				"Fuck it; take almost everything",
				"BIG W",
				-200, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0
			}
		}
	};

	game_events[5] = (Event){
		"WORMHOLE",
		"The state sensors pick up a wormhole; it's barely within their range. Who knows where it will lead. Steer into it?",
		2,
		{
			{
				"Not worth it. Maintain course",
				"lame",
				-10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
			},
			{
				"Cowabunga dude!",
				"into the fuuuuuuuuuuture!",
				10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2
			}
		}
	};

	game_events[6] = (Event){
		"SNAKE",
		"The pilot has suited up in his EVA suit and is changing the spacestate's flat tire. Suddenly, a snake rushes out of the darkness and sinks its teeth into the pilot's ankle! The pilot is beginning to bleed out...",
		2,
		{
			{
				"Let the pilot die. There's no way to save him",
				"seeya later space cowboy",
				0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0
			},
			{
				"Kill the doctor and give his blood to the pilot. It might stabilize him",
				"ashes to ashes, dust to dust",
				0, 0, 0, 0, 0, 10, 0, 0, -1, 0, 0
			}
		}
	};

	game_events[7] = (Event){
		"VISIT FROM THE IRS",
		"You're sipping your morning coffee when you hear a loud banging on the state's entry port. \"THIS IS THE IRS. OUR RECORDS INDICATE YOU HAVE SIGNIFICANT UNPAID TAX LIABILITIES FROM THE PAST FIVE YEARS. YOU WILL LET US IN AND PROVIDE ALL FINANCIAL RECORDS UP TO TWELVE YEARS IN THE PAST.\"",
		4,
		{
			{
				"We're getting out of here! Engines to max! Flee the scene.",
				"ugly death",
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
			},
			{
				"I'm not going down without a fight! Draw your NASA-standard-issue S&W revolver",
				"cowboy death",
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
			},
			{
				"I'm sure you're mistaken. Make a large contribution to the agent's child's college fund.",
				"al capone death",
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
			},
			{
				"Sigh heavily. Let them in.",
				"normal old death",
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
			}
		}
	};

	game_events[8] = (Event){
		"LEIF ERIKSON",
		"You find famed explorer Leif Erikson drifting through space, alive and kicking at the ripe age of 1050 years old. He looks up from studying a star map. \"I'm famished! Got anything to eat?\" You notice he's circled a portion of his map and labelled it \"Fuel cloud\"",
		3,
		{
			{
				"Give him some food. He's probably got some crazy stories",
				"lemme tell you about the time i fought the britains",
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
			},
			{
				"Track down this fuel cloud",
				"huffing fuel XD",
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
			},
			{
				"Ignore him. He weirds me out",
				"fuckn jerk",
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
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

bool is_state_alive(Gamestate *state) {
	if (state->shields < 0) {
		return false;
	} else {
		return true;
	}
}
