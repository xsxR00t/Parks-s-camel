#ifndef _PPM_H_
#define _PPM_H_

// 画像情報を扱うための構造体
typedef struct _TAG_TEXTURE
{
  GLubyte * texture_Image;
  GLuint texture_id;

  int imageWidth;
  int imageHeight;
} texture_t;

// 画像要変数(externによって宣言のみ)
// 実体は defaultParam.h に記述する

/* ヒトコブラクダ */
extern texture_t dromedaryCamel_lineDrowing_black;
extern texture_t dromedaryCamel_lineDrowing_white;
extern texture_t dromedaryCamel_black;
extern texture_t dromedaryCamel_white;

/* フタコブラクダ */
extern texture_t bactrianCamel_lineDrowing_black;
extern texture_t bactrianCamel_lineDrowing_white;
extern texture_t bactrianCamel_black;
extern texture_t bactrianCamel_white;

/* モモタロウ */
extern texture_t momotaro;

/* スリット用の黒背景 */
extern texture_t blackSlit;

/* 単純図形 */
extern texture_t circle;
extern texture_t square;
extern texture_t triangle;

/**
 * @brief アスキーコードで符号化したppmフォーマットを読み込む
 */
void LoadPPM_ascii(char file_name[], GLubyte image[], int x_size, int y_size);

#endif