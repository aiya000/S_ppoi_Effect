/*
 * レポート
 * max_lenをデクリメントしている関数[toLower_Rows]でのデクリメントがおかしいです。
 */
#include "sound_ppoino.h"

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

int max_len;		//各Rowの中で一番長い棒の長さ
/********** サブスレッド関数 *********/

/* [q] が押されたらアプリケーションを終了 */
void* waitKey(void *args){
	char c = 0;
	while(c != 'q'){
		c = getchar();
	}
	runFlag = false;
}

/**************************************/


int gcount = 0;
/*-=-=-=-=- 統括関数 -=-=-=-=-*/

void run(){
	// 画面幅
	int height, width;
	// 表示位置
	int x, y;
	
	/* 位置計算 */
	getmaxyx(stdscr, height, width);
	y = height;
	x = width/4;

	// 下部バーを表示
	mvaddstr(y-3, x, "________________________________________________________________________");

	/* 乱数初期化 */
	srand( (unsigned int)time(NULL) );

	/* 表示開始 */
	runFlag = true;
	while(runFlag){
		fillSoundEffect();			//棒を構成
		while( !toLower_Rows() ){	//棒を引き下げる
			draw();					//棒を描画
		}
	}
}

/*-=-=-=-=-=-=-==-=-=-=-=-=-=-*/

/*-= スタート =-*/
int main(){
	pthread_t fetchKey;
	int status;
	int i;
	/**********/
	initscr();
	noecho();
	cbreak();
	/**********/
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	bkgd(COLOR_PAIR(1));
	/**********/

	/* スレッドを分岐 */
	status = pthread_create(&fetchKey, NULL, waitKey, (void*)NULL);
	// エラーチェック
	if(status != 0){
		fprintf(stderr, "SubThread Running Error : %s", strerror(status));
		return 1;
	}

	/* アプリケーションスタート */
	run();

	/**********/
	endwin();
	return 0;
	/**********/
}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/


/* 変数 */
//int max_len;		//各Rowの中で一番長い棒の長さ
int row_len[ROWS];	//各Rowの長さ
/* 棒を構成する関数 */
void fillSoundEffect(){
	int i, j;
	int rnd;
	max_len = 0;

	for(i=0; i<ROWS; i++){
		/* 乱数分の長さの棒を生成 */ //3以上LENGTH以下
		rnd = rand()*(LENGTH-3+1.0)/(1.0+RAND_MAX);
		/* 変数を構成 */
		if(rnd > max_len) max_len = rnd;
		row_len[i] = rnd;

		/* 棒のビルド */
		for(j=0; j<rnd; j++){
			soundEffect[i][j] = chara[i];
		}

		/* 足りない長さを補う空白 */
		for(;j<LENGTH; j++){
			soundEffect[i][j] = ' ';
		}
	}
	++gcount;
}

/* 全ての棒の長さを1つ下げる */
BOOL toLower_Rows(){
	int i;
	for(i=0; i<ROWS; i++){
		soundEffect[i][row_len[i]--] = ' ';
	}

	/* 引き下げた分MAXを下げる */
	//--max_len;
	int bak = max_len - 1;

	/* 棒を引き下げ終わったらfalseを返す */
	if(max_len-5 > 0){ //5は残す/*ここでsegment fault*/
	//if(bak > 17){ //5は残す
		max_len = bak;
		return FALSE;
	}else{
		return TRUE;
	}
}

/* 棒を描画する関数 */
void draw(){
	int i, j;
	int x, y, w, h;

	/* 表示位置を下部の中心にする */
	getmaxyx(stdscr, h, w);
	y = h;
	x = w/4;
	
	/* 1つの棒の太さを8として描画 */
	for(i=0; i<ROWS*8; i+=8){
		for(j=LENGTH-1; j>=0; j--){
			mvaddch(y-j-4, x+i, soundEffect[i/8][j]);
			mvaddch(y-j-4, x+(i+1), soundEffect[i/8][j]);
			mvaddch(y-j-4, x+(i+2), soundEffect[i/8][j]);
			mvaddch(y-j-4, x+(i+3), soundEffect[i/8][j]);
			mvaddch(y-j-4, x+(i+4), soundEffect[i/8][j]);
			mvaddch(y-j-4, x+(i+5), soundEffect[i/8][j]);
			mvaddch(y-j-4, x+(i+6), soundEffect[i/8][j]);
			mvaddch(y-j-4, x+(i+7), soundEffect[i/8][j]);
		}
	}
	
	//カーソルを邪魔にならない位置に移動
	move(h-1, 0);	
	//描画
	refresh();
	usleep(40000);
}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/


