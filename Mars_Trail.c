#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CHOICES 4
#define MAX_EVENTS 12
#define MAX_WIDTH 4
#define MAX_TEXT 400

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
void print_state_attributes(Gamestate *state);
Event* initialize_events();
Event* get_random_event(Event* events, int num_events);
int get_user_choice(Event* event);
void apply_choice(Gamestate *state, Event* current_event, int user_choice);
bool is_game_over(Gamestate *state);

int main(int argc, char *argv[]) {

	// seed manipulation
	int seed = 0;
	
	if (argc > 1) {
		char *endptr;
		long val = strtol(argv[1], &endptr, 10);

		if (*endptr == '\0') {
			seed = val;
		}
	}

	srand(seed);
	printf("using seed: %d\n", seed);

	// gameplay
	Gamestate state = {100, 100, 100, 100, 0, 100, 0, 1, 1, 1, 1};
	Event* events = initialize_events();
	int num_events = 9;
	int user_choice;
	Event* current_event;
	
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

		if (is_game_over(&state) == true) {
			break;
		}
	}
	
	return 0;
}

void greeting() {
	printf("Liftoff! NASA has sent you on a one-way 9-month Hohmann transfer mission to Mars. Getting there (after your initial burn) should be easy; getting there in one piece may be hard. Manage your resources carefully.\n");
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
		.title = "PIRATES",
		.description = "Pirates spot your ship! They raise a black flag (it doesn't flutter), draw their blades, and burn towards your location.\n",
		.num_choices = 2,
		{
			{
				.description = "Fight", 
				.result = "Your shields take a hit, but you send the pirates packing after a couple well-placed blaster shots",
				.fuel_delta = -10,
				.food_delta = -10,
				.shields_delta = -50,
				.month_delta = 1
			},
			{
				.description = "Flee", 
				.result = "You burn the engines hard, narrowly missing swipes from their cutlasses and rapiers. The sad squawk of a parrot is barely audible over the commotion",
				.fuel_delta = -50,
				.food_delta = -10,
                                .month_delta = 1
			}
		}
	};

	game_events[1] = (Event){
		.title = "PAPA ZORB'S PIZZA",
		.description = "You spot a rusty red shack nestled in an asteroid. A pimply alien in a red hat greets you: \"Welcome to Papa Zorb's, home of the glorpiest pizza in the galaxy. You want anything?\"\n",
		.num_choices = 3,
		{
			{
				.description = "Rob the pizza", 
				.result = "He doesn't react as you hop over the counter and pocket a greasy slice. Your crew looks on in dismay.",
				.food_delta = 50,
				.morale_delta = -50,
                                .month_delta = 1
			},
			{
				.description = "Buy the pizza", 
				.result = "You hand the creature a couple crystals; he hands you a warm slice in a triangular cardboard box. Are slices normally this big?",
				.food_delta = 50,
				.crystals_delta = -30,
                                .month_delta = 1
			},
			{
				.description = "Keep flying", 
				.result = "You've got a mission at hand; no time for fast food! You see your crew salivating.",
				.fuel_delta = -10,
				.food_delta = -10,
				.morale_delta = -50,
                                .month_delta = 1
			}
		}
	};

	game_events[2] = (Event){
		.title = "CAUGHT REDHANDED",
		.description = "A nightmare of crashing into Mars jolts you out of a deep sleep. Groggy, you decide to go on a walk in the centrifugal ring. Is that... your crewmember? ...putting out a cigarette?",
		.num_choices = 3,
		{
			{
				.description = "Chew him out", 
				.result = "You were trained for this; NASA treats everything flammable like the plague. You lecture him about crew endangerment, and then go back to bed.",
				.food_delta = -10,
				.morale_delta = -40,
                                .month_delta = 1
			},
			{
				.description = "Ask for one yourself", 
				.result = "You ask. Nervously, he mumbles something about it being a hard mission for everyone and passes you a cigarette. You go back to bed.",
				.food_delta = -10,
				.cigarettes_delta = 1,
				.morale_delta = 20,
                                .month_delta = 1
			},
			{
				.description = "Go back to bed",
				.result = "You turn around and pretend you didn't see anything. You go back to bed.",
				.food_delta = -10,
				.morale_delta = 20,
                                .month_delta = 1
			}
		}
	};

	game_events[3] = (Event){
		.title = "PLUG'S BUTT-UGLY FUEL TANKER",
		.description = "An old man with a white handlebar mustasche in an 18-wheeler fuel truck pulls up next to you. \"Ih've been movin this cargo for 3 weeks straight naw. Got anythin to take tha edge off?\"",
		.num_choices = 3,
		{
			{
				.description = "Refuse",
				.result = "He yells something about fancy city folk and speeds off angrily. Your crew hang their head slightly.",
				.fuel_delta = -10,
				.food_delta = -10,
				.morale_delta = -30,
                                .month_delta = 1
			},
			{
				.description = "Give him a tortilla",
				.result = "He graciously accepts. As thanks, he adds a bit of fuel to the ship's tank and rambles about his daughter. The crew seem to enjoy talking with another human",
				.fuel_delta = 30,
				.food_delta = -20,
				.morale_delta = 30,
                                .month_delta = 1
			},
			{
				.description = "Give him a cigarette",
				.result = "His eyes light up! He whips out a lighter and immediately begins puffing it. As thanks, he adds a significant amount of fuel to the ship's tank and regales the crew with stories of wild nights on New Las Vegas, Enceladus. The crew seem to enjoy talking with another human.",
				.fuel_delta = 300,
				.food_delta = -10,
				.cigarettes_delta = -1,
				.morale_delta = 40,
                                .month_delta = 1
			}
		}
	};

	game_events[4] = (Event){
		.title = "ALIEN CAPITALISTS",
		.description = "Long-tentacled aliens with 5 large green eyes knock politely on your ship door. \"Wxould yxou lxike txo txrade wxith uxs? wxe wxill cxompensate yxou axs bxest wxe cxan.\" A small, uncontrolled giggle rises out of you at their appearance. Very unprofessional. Very unastronaut. They don't react, and wait patiently for your reply.",
		.num_choices = 4,
		{
			{
				.description = "Refuse",
				.result = "They inform you: \"Wxe uxnderstand sxupplies axre txight. Bxest wxishes oxn yxour fxuture exndeavors.\" They fly away.",
				.food_delta = -10,
                                .month_delta = 1
			},
			{
				.description = "Call them the worst word you know.",
				.result = "They inform you: \"Yxour cxonduct wxill bxe rxemembered.\" as they furrow the area of their body where a brow would go. They make note of your ship's serial number and fly away. Your crew is disconcerted.",
				.food_delta = -10,
				.morale_delta = -20,
                                .month_delta = 1
			},
			{
				.description = "Trade them 80 crystals.",
				.result = "They inform you: \"Wxe axppreciate txhe bxusiness.\" and deposit a sizeable amount of food into your ship's storage bay.",
				.food_delta = 100,
				.crystals_delta = -80,
                                .month_delta = 1
			},
			{
				.description = "Trade them 200 fuel.",
				.result = "They inform you: \"Txhis ixs qxuite exxceptional mxaterial.\" and deposit a their most valuable object into your ship's storage bay.",
				.fuel_delta = -200,
				.food_delta = -10,
				.tires_delta = 1,
                                .month_delta = 1
			}
		}
	};

	game_events[5] = (Event){
		.title = "WORMHOLE",
		.description = "The ship's sensors pick up a wormhole, about 200 kilometers out. You've never seen a worm's hole before.",
		.num_choices = 2,
		{
			{
				.description = "Keep flying.",
				.result = "The crew sighs with relief. They've never seen a worm's hole either.",
				.food_delta = -10,
				.morale_delta = 10,
                                .month_delta = 1
			},
			{
				.description = "Fly into it.",
				.result = "You burn the engines while the crew screams with fear. As the wormhole engulfs you, everything goes black and you get a funny feeling.",
				.fuel_delta = -30,
				.food_delta = -10,
				.morale_delta = -20,
				.month_delta = 3
			}
		}
	};

	game_events[6] = (Event){
		.title = "SNAKE",
		.description = "The pilot has suited up in his EVA suit and is changing the spacestate's flat tire. Suddenly, a snake rushes out of the darkness and sinks its teeth into the pilot's ankle! The pilot is beginning to bleed out...",
		.num_choices = 2,
		{
			{
				.description = "Let the pilot die. There's no way to save him",
				.result = "seeya later space cowboy",
				.food_delta = -10,
				.morale_delta = -50,
				.month_delta = 1
			},
			{
				.description = "Kill the doctor and give his blood to the pilot. It might stabilize him",
				.result = "ashes to ashes, dust to dust",
				.food_delta = -10,
				.morale_delta = -10,
				.month_delta = 1
			}
		}
	};

	game_events[7] = (Event){
		.title = "VISIT FROM THE IRS",
		.description = "You're sipping your morning coffee when you hear a loud banging on the state's entry port. \"THIS IS THE IRS. OUR RECORDS INDICATE YOU HAVE SIGNIFICANT UNPAID TAX LIABILITIES FROM THE PAST FIVE YEARS. YOU WILL LET US IN AND PROVIDE ALL FINANCIAL RECORDS UP TO TWELVE YEARS IN THE PAST.\"",
		.num_choices = 4,
		{
			{
				.description = "We're getting out of here! Engines to max! Flee the scene.",
				.result = "ugly death",
				.food_delta = -10,
				.month_delta = 1
			},
			{
				.description = "I'm not going down without a fight! Draw your NASA-standard-issue S&W revolver",
				.result = "cowboy death",
				.food_delta = -10,
				.month_delta = 1
			},
			{
				.description = "I'm sure you're mistaken. Make a large contribution to the agent's child's college fund.",
				.result = "al capone death",
				.food_delta = -10,
				.month_delta = 1
			},
			{
				.description = "Sigh heavily. Let them in.",
				.result = "normal old death",
				.food_delta = -10,
				.month_delta = 1
			}
		}
	};

	game_events[8] = (Event){
		.title = "LEIF ERIKSON",
		.description = "You find famed explorer Leif Erikson drifting through space, alive and kicking at the ripe age of 1050 years old. He looks up from studying a star map. \"I'm famished! Got anything to eat?\" You notice he's circled a portion of his map and labelled it \"Fuel cloud\"",
		.num_choices = 3,
		{
			{
				.description = "Give him some food. He's probably got some crazy stories",
				.result = "lemme tell you about the time i fought the britains",
				.food_delta = -10,
				.month_delta = 1
			},
			{
				.description = "Track down this fuel cloud",
				.result = "huffing fuel XD",
				.food_delta = -10,
				.month_delta = 1
			},
			{
				.description = "Ignore him. He weirds me out",
				.result = "fuckn jerk",
				.food_delta = -10,
				.month_delta = 1
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

bool is_game_over(Gamestate *state) {
	// food ran out
	if (state->food <= 0) {
		printf("crew withered away n died :(. The end.\n");
		return true;

	// morale ran out
	} else if (state->morale <= 0) {
		printf("you became very unpopular. crew snacked on your liver. The end.\n");
		return true;

	// bad ending; no fuel when you get to mars
	} else if (state->fuel <= 0 && state->month >= 10) {
		printf("with no fuel on board, you've left nothing in the tank to land. you smash into the planet mars at 12,345 mph and are instantly atomized. The end.\n");
		return true;

	// bad ending: no pilot when you get to mars
	} else if (state->pilot <= 0 && state->month >= 10) {
		printf("did you really think you could land the ship?? without a pilot, you fiddle around with the engine controls but smash helplessly into the surface.\n");
		return true;
	
	// secret ending
	} else if (state->tires >= 1) {
		printf("You safely touch down on the planet Mars! A martian farmer saunters up to you: i'll trade you 5000 acres for that tire. You did good.\n");
		return true;

	// good ending
	} else if (state->month >= 10) {
		printf("You safely touch down on the planet Mars! You become national heroes back at home. Fortunately, you're not back at home.\n");
		return true;
	}

	return false;
}
