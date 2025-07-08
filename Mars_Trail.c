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
	int num_events = 12;
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
		
		state.month++;
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
		"PIRATES",
		"Pirates spot your ship! They raise a black flag (it doesn't flutter), draw their blades, and burn towards your location.\n",
		2,
		{
			{
				"Fight", 
				"Your shields take a hit, but you send the pirates packing after a couple well-placed blaster shots",
				-10, -10, -50, 0, 0, 0, 0, 0, 0, 0, 0
			},
			{
				"Flee", 
				"You burn the engines hard, narrowly missing swipes from their cutlasses and rapiers. The sad squawk of a parrot is barely audible over the commotion",
				-50, -10, 0, 0, 0, 0, 0, 0, 0, 0, 0
			}
		}
	};

	game_events[1] = (Event){
		"PAPA ZORB'S PIZZA",
		"You spot a rusty red shack nestled in an asteroid. A pimply alien in a red hat greets you: \"Welcome to Papa Zorb's, home of the glorpiest pizza in the galaxy. You want anything?\"\n",
		3,
		{
			{
				"Rob the pizza", 
				"He doesn't react as you hop over the counter and pocket a greasy slice. Your crew looks on in dismay.",
				0, 50, 0, 0, 0, -50, 0, 0, 0, 0, 0
			},
			{
				"Buy the pizza", 
				"You hand the creature a couple crystals; he hands you a warm slice in a triangular cardboard box. Are slices normally this big?",
				0, 50, 0, -30, 0, 0, 0, 0, 0, 0, 0
			},
			{
				"Keep flying", 
				"You've got a mission at hand; no time for fast food! You see your crew salivating.",
				-10, -10, 0, 0, 0, -50, 0, 0, 0, 0, 0
			}
		}
	};

	game_events[2] = (Event){
		"CAUGHT REDHANDED",
		"A nightmare of crashing into Mars jolts you out of a deep sleep. Groggy, you decide to go on a walk in the centrifugal ring. Is that... your crewmember? ...putting out a cigarette?",
		3,
		{
			{
				"Chew him out", 
				"You were trained for this; NASA treats everything flammable like the plague. You lecture him about crew endangerment, and then go back to bed.",
				0, -10, 0, 0, 0, -40, 0, 0, 0, 0, 0
			},
			{
				"Ask for one yourself", 
				"You ask. Nervously, he mumbles something about it being a hard mission for everyone and passes you a cigarette. You go back to bed.",
				0, -10, 0, 0, 1, 20, 0, 0, 0, 0, 0
			},
			{
				"Go back to bed",
				"You turn around and pretend you didn't see anything. You go back to bed.",
				0, -10, 0, 0, 0, 20, 0, 0, 0, 0, 0
			}
		}
	};

	game_events[3] = (Event){
		"PLUG'S BUTT-UGLY FUEL TANKER",
		"An old man with a white handlebar mustasche in an 18-wheeler fuel truck pulls up next to you. \"Ih've been movin this cargo for 3 weeks straight naw. Got anythin to take tha edge off?\"",
		3,
		{
			{
				"Refuse",
				"He yells something about fancy city folk and speeds off angrily. Your crew hang their head slightly.",
				-10, -10, 0, 0, 0, -30, 0, 0, 0, 0, 0
			},
			{
				"Give him a tortilla",
				"He graciously accepts. As thanks, he adds a bit of fuel to the ship's tank and rambles about his daughter. The crew seem to enjoy talking with another human",
				30, -20, 0, 0, 0, 30, 0, 0, 0, 0, 0
			},
			{
				"Give him a cigarette",
				"His eyes light up! He whips out a lighter and immediately begins puffing it. As thanks, he adds a significant amount of fuel to the ship's tank and regales the crew with stories of wild nights on New Las Vegas, Enceladus. The crew seem to enjoy talking with another human.",
				300, -10, 0, 0, -1, 40, 0, 0, 0, 0, 0
			}
		}
	};

	game_events[4] = (Event){
		"ALIEN CAPITALISTS",
		"Long-tentacled aliens with 5 large green eyes knock politely on your ship door. \"Wxould yxou lxike txo txrade wxith uxs? wxe wxill cxompensate yxou axs bxest wxe cxan.\" A small, uncontrolled giggle rises out of you at their appearance. Very unprofessional. Very unastronaut. They don't react, and wait patiently for your reply.",
		4,
		{
			{
				"Refuse",
				"They inform you: \"Wxe uxnderstand sxupplies axre txight. Bxest wxishes oxn yxour fxuture exndeavors.\" They fly away.",
				0, -10, 0, 0, 0, 0, 0, 0, 0, 0, 0
			},
			{
				"Call them the worst word you know.",
				"They inform you: \"Yxour cxonduct wxill bxe rxemembered.\" as they furrow the area of their body where a brow would go. They make note of your ship's serial number and fly away. Your crew is disconcerted.",
				0, -10, 0, 0, 0, -20, 0, 0, 0, 0, 0
			},
			{
				"Trade them 80 crystals.",
				"They inform you: \"Wxe axppreciate txhe bxusiness.\" and deposit a sizeable amount of food into your ship's storage bay.",
				0, 100, 0, -80, 0, 0, 0, 0, 0, 0, 0
			},
			{
				"Trade them 200 fuel.",
				"They inform you: \"Txhis ixs qxuite exxceptional mxaterial.\" and deposit a their most valuable object into your ship's storage bay.",
				-200, -10, 0, 0, 0, 0, 1, 0, 0, 0, 0
			}
		}
	};

	game_events[5] = (Event){
		"WORMHOLE",
		"The ship's sensors pick up a wormhole, about 200 kilometers out. You've never seen a worm's hole before.",
		2,
		{
			{
				"Keep flying.",
				"The crew sighs with relief. They've never seen a worm's hole either.",
				0, -10, 0, 0, 0, 10, 0, 0, 0, 0, 0
			},
			{
				"Fly into it.",
				"You burn the engines to change course. As the wormhole engulfs you, everything goes black and you get a funny feeling.",
				-30, -10, 0, 0, 0, 0, 0, 0, 0, 0, 2
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

	game_events[9] = (Event){
		"OLD LADY",
		"u see an old lady at a crosswalk.",
		2,
		{
			{
				"Help her cross.",
				"good citizen",
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
			},
			{
				"Ignore her; keep flying by",
				"bad bad bad citizen",
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
			}
		}
	};

	game_events[10] = (Event){
		"WHALES",
		"you see a pod of whales off of the port side of the ship. one of them glistens white, and has a harpoon scar running on its back.",
		3,
		{
			{
				"look for a while.",
				"very cool",
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
			},
			{
				"take a picture.",
				"itll last longer",
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
			},
			{
				"keep flying",
				"important business to attend to",
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
			}
		}
	};

	game_events[11] = (Event){
		"SATELLITE",
		"a starlink satellite is slowly approaching your ship, and the radio picks up some of its chatter. it seems.... distant.... incoherent.... corrupted. it asks to dock with the ship.",
		4,
		{
			{
				"fly away",
				"ok :(",
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
			},
			{
				"open fire",
				"it fires back",
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
			},
			{
				"try to hack it",
				"zeep zorp zop",
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
			},
			{
				"let it dock",
				"it accepts >:)",
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
