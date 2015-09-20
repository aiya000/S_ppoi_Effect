#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>

#define LEN(T, array) sizeof(array)/sizeof(T)
#define ROWS 10
#define LENGTH 20
char* line_cleaner = "                    ";
char soundEfect[ROWS][LENGTH+1];
char chara[5] = {'#', '$', '%', '&', '='};

static void run();
static void view();

int main(){
	initscr();
	noecho();
	cbreak();

	srand( (unsigned int)time(NULL) );
	while(1){
	run();
	view();
	}

	endwin();
	return 0;
}

static void run(){
	int i, j;
	int rnd;
	for(i=0; i<ROWS; i++){
		rnd = rand()%LENGTH+1;
		for(j=0; j<rnd; j++){
			soundEfect[i][j] = chara[i%5];
		}
		soundEfect[i][j] = '\0';
	}
}

static void view(){
	int i, j;
	for(i=0; i<ROWS; i++){
		for(j=0; j<LEN(char, soundEfect[i]); j++){
			mvaddch(10+i, j, soundEfect[i][j]);
		}
	}
	refresh();
	usleep(500000);

	/* 画面のクリア */
	for(i=0; i<ROWS; i++){
			mvaddstr(i, 0, line_cleaner);
	}
	refresh();
}
