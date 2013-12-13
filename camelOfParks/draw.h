#ifndef _DRAW_H_
#define _DRAW_H_

#define DROMEDARYCAMEL_LINEDROWING_BLACK 0
#define DROMEDARYCAMEL_LINEDROWING_WHITE 1
#define DROMEDARYCAMEL_BLACK             2
#define DROMEDARYCAMEL_WHITE             3

#define BACTRIANCAMEL_LINEDROWING_BLACK  4
#define BACTRIANCAMEL_LINEDROWING_WHITE  5
#define BACTRIANCAMEL_BLACK              6
#define BACTRIANCAMEL_WHITE              7

#define MOMOTARO           8

#define CIRCLE_IMAGE       9
#define SQUARE_IMAGE       10
#define TRIANGLE_IMAGE     11

/**
 * @brief スリットが動く
 * @param x : 基準x座標
 * @param slitWidth : スリット間隔
 * @param ImageMode : 画像変更用の変数
 */
void draw_moveSlit(GLfloat x, GLfloat slitWidth, int ImageMode);

/**
 * @brief スリットが動く
 * @param x : 基準x座標
 * @param slitWidth : スリット間隔
 */
void draw_moveImage(GLfloat x, GLfloat slitWidth, int ImageMode);

/**
 * @brief 画像を張り替える
 * @param * id : 選択された画像ID
 */
void bindTexture(int * id);

/**
 * @brief オブジェクトの座標を簡略
 */
void createObject(void);

/**
 * @brief スリットを作成するだけの関数
 */
void createObjectSlit(void);

#endif