#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>

/********** グローバル変数 **********/

/* サウンドエフェクトっぽい棒の列数 */
#define ROWS 10
/* 棒の長さ上限 */
#define LENGTH 20

/* 棒集合体の本体 */
char soundEfect[ROWS][LENGTH+1];

/* 棒の描画で残った前回の棒の打ち消しに使う */
char* line_cleaner = "                    ";

/* 棒を構成する記号 */
char chara[5] = {'#', '$', '%', '&', '='};

/********** プライベート関数 **********/

/* 統括関数 */
static void run();

/* サウンドエフェクトっぽい棒を生成する */
static void fillSoundEfect();

/* 棒を描画する */
static void view();

/**************************************/


/*-=-=-=-=- 統括関数 -=-=-=-=-*/

static void run(){
	srand( (unsigned int)time(NULL) );
	while(1){
		fillSoundEfect();	//棒を構成
		view();				//棒を描画
	}
}

/*-=-=-=-=-=-=-==-=-=-=-=-=-=-*/


/*-= スタート =-*/
int main(){
	initscr();
	noecho();
	cbreak();
	/**********/

	/* アプリケーションスタート */
	run();

	/**********/
	endwin();
	return 0;
}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/


/* 棒を構成する関数 */
static void fillSoundEfect(){
	int i, j;
	int rnd;

	for(i=0; i<ROWS; i++){
		/* 乱数分の長さの棒を生成 */
		rnd = rand()%LENGTH+1;
		for(j=0; j<rnd; j++){
			soundEfect[i][j] = chara[i%5];
		}

		/* 足りない長さを補う空白 */
		for(;j<LENGTH; j++){
			soundEfect[i][j] = ' ';
		}

		/* EOSを最後尾に代入 */
		soundEfect[i][j] = '\0';
	}
}

/* 棒を描画する関数 */
static void view(){
	int i, j;
	/*for(i=0; i<ROWS; i++){
		mvaddstr(i, 0, soundEfect[i]);
	}*/
	for(i=0; i<LENGTH; i++){
		for(j=0; j<ROWS; j++){
			mvaddch(j, i, soundEfect[i][j]);
		}
	}
	
	//カーソルを邪魔にならない位置に移動
	move(11, 0);	
	//描画
	refresh();
	usleep(500000);

	/* 画面のクリア */
	for(i=0; i<ROWS; i++){
			mvaddstr(i, 0, line_cleaner);
	}
	refresh();
}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/


