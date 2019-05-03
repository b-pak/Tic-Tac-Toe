#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <setjmp.h>

int c[10] = {'x', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
int available[9] = {1,2,3,4,5,6,7,8,9};
/* available array should not include 0 as it would translate into c[0] which does not trigger any action.
This should be reflected in the for loop within the expert_system, thus i = choice - 1 not = choice
*/
int i, choice, temp, AIgameover, Playergameover;
char name[20];
char response[20];
jmp_buf DECISION;

void board_initial();
void board_actual();
void AIchoice();
void expert_system();
void check_validity();
void winning_condition();

int main() {

/* Intro
*/
	printf("Tic - a game made by beginners, for beginners.\n");
	board_initial();
  printf("What is your name?\n");
  fgets(name, 10, stdin);
	name[strcspn(name, "\n")] = 0;
	/* strcspn compares the length of first argument and the second*/
	printf("Hi %s. Welcome to Tic.\n", name);
	printf("Would you like to go first? Please answer yes or no.\n");
	scanf("%s", response);
	if(strcmp(response,"yes")==0) {
		board_initial();
		printf("Please enter a number.\n");
		check_validity();
	}
	else if(strcmp(response,"no")==0) {
		printf("Waiting for your opponent. This may take a few seconds.\n");
		sleep(5);
		AIchoice();
		board_actual();
		printf("Please enter a number.\n");
		check_validity();
	}

/* Game On
*/
	expert_system();

	while ((AIgameover != true) || (Playergameover != true)) {
		setjmp(DECISION);
		printf("Please enter a number.\n");
		check_validity();
		expert_system();
		winning_condition();
		if (AIgameover == true){
			printf("Congratulations %s! You won!\n", name);
			break;
		}
		else if (Playergameover == true) {
			printf("Good try! You lost.\n");
			break;
		}
		else if ((AIgameover == false) && (Playergameover == false)) {
			printf("Friendly reminder: if you would like to restart the game. Use control shift.\n");
		}
	}

	return 0;
}

/* Set up
*/
void board_initial() {
	printf("  %c  |  %c  |  %c \n", c[1], c[2], c[3]);
	printf("------------------ \n");
	printf("  %c  |  %c  |  %c \n", c[4], c[5], c[6]);
	printf("------------------ \n");
	printf("  %c  |  %c  |  %c \n", c[7], c[8], c[9]);
}
void board_actual() {
	printf("  %c  |  %c  |  %c \n", c[1], c[2], c[3]);
	printf("------------------ \n");
	printf("  %c  |  %c  |  %c \n", c[4], c[5], c[6]);
	printf("------------------ \n");
	printf("  %c  |  %c  |  %c \n", c[7], c[8], c[9]);
}
void AIchoice() {
	do {
		srand(time(NULL));
		temp = available[rand()%9];
	} while((c[temp]=='x') || (c[temp]=='o'));
	c[temp]='o';
}

void expert_system() {
	c[choice] = 'x';
	AIchoice();
	board_actual();
}

void check_validity() {
	scanf("%d", &choice);
	if ((c[choice]=='x') || (c[choice]=='o')) {
		printf("Invalid. ");
		longjmp(DECISION, 1);
	}
}

/* Winning Conditions
*/
void winning_condition() {
	/* for (i=1,i<4,i++) {
		if (c[i]==('x') && c[i+3]==('x') && c[i+6]==('x')) {
			AIgameover = true;
		}
		else if (c[i]==('o') && c[i+3]==('o') && c[i+6]==('o')) {
			Playergameover = true;
		}
	for (i=1,i<4,i+=3) {
		if (c[i]==('x') && c[i+2]==('x') && c[i+3]==('x') {
			AIgameover = true;
		}
		else if (c[i]==('o') && c[i+2]==('o') && c[i+3]==('o') {
			Playergameover = true;
		})
	}
	if (c[1]=='o' && c[5]=='o' && c[9]=='o') {
			Playergameover = true;
	} */

	if (c[1]=='x' && c[2]=='x' && c[3]=='x') {
		AIgameover = true;
	}
	else if (c[4]=='x' && c[5]=='x' && c[6]=='x') {
		AIgameover = true;
	}
	else if (c[7]=='x' && c[8]=='x' && c[9]=='x') {
		AIgameover = true;
	}
	else if (c[1]=='x' && c[5]=='x' && c[9]=='x') {
		AIgameover = true;
	}
	else if (c[3]=='x' && c[5]=='x' && c[7]=='x') {
		AIgameover = true;
	}
	else if (c[1]=='x' && c[4]=='x' && c[7]=='x') {
		AIgameover = true;
	}
	else if (c[2]=='x' && c[5]=='x' && c[8]=='x') {
		AIgameover = true;
	}
	else if (c[3]=='x' && c[6]=='x' && c[9]=='x') {
		AIgameover = true;
	}
	else if (c[1]=='o' && c[2]=='o' && c[3]=='o') {
		Playergameover = true;
	}
	else if (c[4]=='o' && c[5]=='o' && c[6]=='o') {
		Playergameover = true;
	}
	else if (c[7]=='o' && c[8]=='o' && c[9]=='o') {
		Playergameover = true;
	}
	else if (c[1]=='o' && c[5]=='o' && c[9]=='o') {
		Playergameover = true;
	}
	else if (c[3]=='o' && c[5]=='o' && c[7]=='o') {
		Playergameover = true;
	}
	else if (c[1]=='o' && c[4]=='o' && c[7]=='o') {
		Playergameover = true;
	}
	else if (c[2]=='o' && c[5]=='o' && c[8]=='o') {
		Playergameover = true;
	}
	else if (c[3]=='o' && c[6]=='o' && c[9]=='o') {
		Playergameover = true;
	}
	else {
		AIgameover = false;
		Playergameover = false;
	}
}
