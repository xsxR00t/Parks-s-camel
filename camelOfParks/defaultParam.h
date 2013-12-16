#include <GL/glut.h>
#include "ppm.h"

#ifndef _DEFAULTPARAM_H_
#define _DEFAULTPARAM_H_

/* ウィンドウズのサイズ */
#define X_SIZE 640
#define Y_SIZE 480

/* ディスプレイの物理単位(cm) */

// Display
/*static const float DISPSIZE_X = 48;
static const float DISPPIX_X  = 1900;*/

// Dynabook
static const float DISPSIZE_X = 29.2;
static const float DISPPIX_X  = 1366;

/* モード変更用の変数 */
#define SLIT_MOVE_MODE  0 // スリットが動くモード
#define IMAGE_MOVE_MODE 1 // ラクダ画像が動くモード

/* ppm.hに宣言された変数の定義 */
texture_t dromedaryCamel_lineDrowing_black;
texture_t dromedaryCamel_lineDrowing_white;
texture_t dromedaryCamel_black;
texture_t dromedaryCamel_white;

texture_t bactrianCamel_lineDrowing_black;
texture_t bactrianCamel_lineDrowing_white;
texture_t bactrianCamel_black;
texture_t bactrianCamel_white;

texture_t momotaro;

texture_t blackSlit;
texture_t whiteSlit;

texture_t circle;
texture_t square;
texture_t triangle;

/* 調整用パラメーター */
// 移動用変数
GLfloat position_x = 0.0;
// スリット幅変数
GLfloat slitWidth = 0.0;
// スリットスピード変数
GLfloat slitSpeed = 0.0;

// 変換結果保存変数
GLfloat realSlitWidth = 0.0;
GLfloat realSlitSpeed = 0.0;

/* FPS関数 */
double time; // 経過時間
float fps = 60.0f;   // frame / s
float fRate = 16.666667f; // s / frame(ms)
int now = 0, old = 0, base = 0;

/* UI用変数 */
int mode = IMAGE_MOVE_MODE;   // モード選択変数
int slitColor = 0;  // スリット画像変更
int ImageMode = 0;  // 画像選択変数
int repetition = 0; // 反復機能用変数

/* fps用変数 */
int GLframe = 0;     // フレーム数
int GLtimenow = 0;   // 経過時間
int GLtimebase = 0;  // 計測開始時間

bool Change = false;     // 画面切り替えフラグ
bool moveChange = false; // 移動方向切り替えフラグ

/* プロトタイプ宣言 */
// 描画関数
void display();
// キーボードアクション
void keyboard(unsigned char key, int x, int y);
// アイドル関数
void idle();
// タイマー関数
void timer(int value);

// UI設定関数
void setGlui();
// スリット幅変更関数
void inputChangeSlitWidth(int num);
// スリットスピード変更関数
void inputChangeSlitSpeed(int num);
// テクスチャ読み込み関数
void loadTexture();
// 読み込み簡略化関数
void runLoadTexture(texture_t * obj, char * filename, int width, int height);
// 出力関数
void viewParam();
// EXIT用のコールバック関数
void gluiCallBack(int num);
// フルスクリーンモード関数
void fullscreen(void);
void countFPS();

#endif