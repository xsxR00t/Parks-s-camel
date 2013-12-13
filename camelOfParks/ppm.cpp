#include <windows.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief アスキーコードで符号化したppmフォーマットを読み込む
 */
void LoadPPM_ascii(char file_name[], GLubyte image[], int x_size, int y_size)
{
  FILE *fp;      // ファイルポインタの定義
  char buf[100]; // バッファーの用意
  int i;         // ループ用変数
  int header_lines = 3;

  // ファイルにアクセスする
  if ((fp = fopen(file_name, "r")) == NULL){ // 読み込みモード
    // エラー表示
    fprintf(stderr, "Cannot open PPM file %s\n", file_name);
    // 終了
    exit(0);
  }

  // header_lines分'#'まで読み込んでいく
  for (i = 0; i < header_lines; i++){
    fgets(buf, 100, fp);
    if (*buf == '#'){
      i--;
    }
  }
  // 縦、横、RGB分読み込む
  for (i = 0; i < x_size * y_size * 3; i++){
    fscanf(fp, "%d", &image[i]);
  }

  // ファイルのクローズ
  fclose(fp);
}