
/* bool型宣言 */
#ifndef BOOL
#define BOOL short
#define TRUE 1
#define FALSE 0
#endif

/********** グローバル変数 **********/

/* サウンドエフェクトっぽい棒の列数 */
#define ROWS 9
/* 棒の長さ上限 */
#define LENGTH 40

/* 棒集合体の本体 */
char soundEffect[ROWS][LENGTH+1];

/* 棒を構成する記号 */
char chara[9] = {'#', '$', '%', '&', '#', '&', '%', '$', '#'};

/* アプリケーションの稼動制御 */
BOOL runFlag;


/*************** 関数 ***************/

/* 統括関数 */
void run();

/* サウンドエフェクトっぽい棒を生成する */
void fillSoundEffect();

/* 棒を1つ引き下げる*/
BOOL toLower_Rows();

/* 棒を描画する */
void draw();

/********** サブスレッド関数 *********/

void* waitKey(void *args);

/************************************/

