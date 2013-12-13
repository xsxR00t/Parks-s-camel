#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>

/**
 * @brief 描画設定関数
 */
void gl_init()
{
  // (RGBA)をゼロにする(白で画面を初期化)
  glClearColor(1.0, 1.0, 1.0, 0.0);
  // 透視投影の行列を指定する
  glMatrixMode(GL_PROJECTION);
  // 現在選択されている行列を初期化
  glLoadIdentity();
  // アスペクト比などの設定
  gluPerspective(45.0, 1.0, 2.0, 20.0);
  // 各多角形の前後関係決定
  glEnable(GL_DEPTH_TEST);
}