#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <GL/GL.h>
#include <GL/glui.h>
#include <GL/glut.h>

/** ユーザー定義関数 **/
#include "defaultParam.h"
#include "gl_init.h"
#include "texture.h"
#include "ppm.h"
#include "draw.h"

/**
 * @brief Main関数
 */
int main(int argc, char **argv)
{
  // Window作成のための初期化関数
  glutInit(&argc, argv);
  // ディスプレイモードの選択
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  // ウィンドウのサイズ
  glutInitWindowSize(X_SIZE, Y_SIZE);
  // 初期表示位置
  glutInitWindowPosition(150, 150);
  // ウィンドウ作成の名前
  glutCreateWindow("Parks");

  realSlitWidth = (GLfloat)((3 * DISPPIX_X * 0.3) / (DISPSIZE_X * X_SIZE));
  realSlitSpeed = (GLfloat)((18000 * DISPSIZE_X * 3) / (58.823528 * DISPPIX_X * X_SIZE));

  gl_init();     // 全体の初期化関数
  loadTexture(); // テクスチャーの読み込み
  setGlui();     // UI設定

  //wglSwapIntervalEXT(0);

  //glutKeyboardFunc(keyboard); // キーボードイベント登録
  glutDisplayFunc(display);   // 描画イベント登録
  //glutIdleFunc(idle);         // アイドルイベント登録
  glutIdleFunc(countFPS);
  //glutTimerFunc(16, timer, 0); // タイマー関数
  glutMainLoop();             // ループ処理
}

/**
 * @brief UI設定関数
 */
void setGlui(void)
{
  /* GLUIコントローラーの設定 */
  GLUI * glui = GLUI_Master.create_glui("Control Panel", 0);

  /* スリットサイズのテキストボックス追加 */
  GLUI_EditText * editSlitWidth = new GLUI_EditText(glui, "Slit width (cm)", &slitWidth, NULL, inputChangeSlitWidth);
  // 限界値とその処理
  //editSlitWidth->set_float_limits(0.0, 1.0, GLUI_LIMIT_CLAMP);
  // 初期値
  editSlitWidth->set_float_val(0.3);

  /* 移動スピードのテキストボックス追加 */
  GLUI_EditText * editSlitSpeed = new GLUI_EditText(glui, "Slit speed (cm)/s", &slitSpeed, NULL, inputChangeSlitSpeed);
  //editSlitSpeed->set_float_limits(0.0, 1.0, GLUI_LIMIT_CLAMP);
  editSlitSpeed->set_float_val(18000);

  // 仕切り線
  glui->add_separator();

  /* モード変更用のラジオボタン */
  // テキスト
  glui->add_statictext("Move select");
  GLUI_RadioGroup * mode_radio = new GLUI_RadioGroup(glui, &mode);
  // モード変更の項目設定
  glui->add_radiobutton_to_group(mode_radio, "Slit Move");
  glui->add_radiobutton_to_group(mode_radio, "Image Move");

  // 仕切り線
  glui->add_separator();

  // 反復ボタン
  new GLUI_Checkbox(glui, "Repetition", &repetition);

  glui->add_separator();

  /* 画像変更のラジオボタン */
  glui->add_statictext("Image select");
  GLUI_RadioGroup * imageMode_radio = new GLUI_RadioGroup(glui, &ImageMode);
  glui->add_radiobutton_to_group(imageMode_radio, "Dromedary camel - Line drowing black");
  glui->add_radiobutton_to_group(imageMode_radio, "Dromedary camel - Line drowing white");
  glui->add_radiobutton_to_group(imageMode_radio, "Dromedary camel - Black");
  glui->add_radiobutton_to_group(imageMode_radio, "Dromedary camel - White");

  glui->add_radiobutton_to_group(imageMode_radio, "Bactrian camel - Line drowing black");
  glui->add_radiobutton_to_group(imageMode_radio, "Bactrian camel - Line drowing white");
  glui->add_radiobutton_to_group(imageMode_radio, "Bactrian camel - Black");
  glui->add_radiobutton_to_group(imageMode_radio, "Bactrian camel - White");

  glui->add_radiobutton_to_group(imageMode_radio, "Momotaro");

  glui->add_radiobutton_to_group(imageMode_radio, "Circle");
  glui->add_radiobutton_to_group(imageMode_radio, "Square");
  glui->add_radiobutton_to_group(imageMode_radio, "triangle");

  // 仕切り線
  glui->add_separator();

  /* exitボタン */
  glui->add_button("Exit", 0, gluiCallBack);

  // idlezコールバック関数はGLUIで登録
  GLUI_Master.set_glutIdleFunc(NULL);
}

void inputChangeSlitWidth(int num)
{
  realSlitWidth = (GLfloat)((3 * DISPPIX_X * slitWidth) / (DISPSIZE_X * X_SIZE));
  printf("change slit width : %lf\n", realSlitWidth);
}

void inputChangeSlitSpeed(int num)
{
  realSlitSpeed = (GLfloat)((slitSpeed * DISPSIZE_X * 3) / (58.823528 * DISPPIX_X * X_SIZE)) * 100.0;
  printf("change slit speed : %lf\n", realSlitSpeed);
}

/**
 * @brief テクスチャの読み込み
 */
void loadTexture()
{
  // ヒトコブラクダ
  runLoadTexture(&dromedaryCamel_lineDrowing_black, "dromedaryCamel_lineDrowing_black.ppm", 640, 480);
  runLoadTexture(&dromedaryCamel_lineDrowing_white, "dromedaryCamel_lineDrowing_white.ppm", 640, 480);
  runLoadTexture(&dromedaryCamel_black,       "dromedaryCamel_black.ppm",       640, 480);
  runLoadTexture(&dromedaryCamel_white,       "dromedaryCamel_white.ppm",       640, 480);

  // フタコブラクダ画像
  runLoadTexture(&bactrianCamel_lineDrowing_black, "bactrianCamel_lineDrowing_black.ppm", 640, 480);
  runLoadTexture(&bactrianCamel_lineDrowing_white, "bactrianCamel_lineDrowing_white.ppm", 640, 480);
  runLoadTexture(&bactrianCamel_black,       "bactrianCamel_black.ppm",       640, 480);
  runLoadTexture(&bactrianCamel_white,       "bactrianCamel_white.ppm",       640, 480);

  // モモタロウ
  runLoadTexture(&momotaro, "momotaro.ppm", 640, 480);

  // スリットの黒画像
  runLoadTexture(&blackSlit, "black.ppm", 512, 512);

  // 単純画像
  runLoadTexture(&circle,   "circle.ppm",   640, 480);
  runLoadTexture(&square,   "square.ppm",   640, 480);
  runLoadTexture(&triangle, "triangle.ppm", 640, 480);
}

/**
 * @brief 読み込み簡略化関数
 * @param *obj : 対象のテクスチャ構造体ポインタ
 * @param filename : 対象の画像名
 * @param width : 横サイズ
 * @param height : 縦サイズ
 */
void runLoadTexture(texture_t * obj, char * filename, int width, int height)
{
  // 画像サイズの定義
  obj->imageWidth = width;
  obj->imageHeight = height;

  // テクスチャ画像用配列の確保(幅、高さ、RGBの3)(幅、高さ、RGBの3)
  obj->texture_Image = (GLubyte *)malloc(sizeof(GLubyte)* obj->imageWidth * obj->imageHeight * 3);
  // ファイルのロード
  LoadPPM_ascii(filename, obj->texture_Image, obj->imageWidth, obj->imageHeight);
  // ファイルをセットする
  set_texture(obj->texture_Image, &obj->texture_id, obj->imageWidth, obj->imageHeight);
}

/**
 * @brief 描画イベント関数
 */
void display()
{
  if (X_SIZE != glutGet(GLUT_WINDOW_WIDTH))
  {
    realSlitWidth = (GLfloat)((3 * DISPPIX_X * slitWidth) / (DISPSIZE_X * X_SIZE));
    realSlitSpeed = (GLfloat)((slitSpeed * DISPSIZE_X * 3) / (58.823528 * DISPPIX_X * X_SIZE)) * 100.0;
    printf("Slit speed : %lf\n", realSlitSpeed);
  }

  // 移動方向判別
  if (!moveChange)
    position_x += realSlitSpeed;
  else
    position_x -= realSlitSpeed;

  // 不用意な領域にいかない
  switch (mode)
  {
  case SLIT_MOVE_MODE:
    if (repetition == 0)
    {
      if (position_x > 2.95)     // 右端に行き過ぎたとき
        position_x = 0.0 - realSlitWidth;
      else if (position_x + realSlitWidth < 0.0) // 左端に行き過ぎたとき
        position_x = 2.95;
    }
    else
    {
      if (position_x > 2.95)     // 右端に行き過ぎたとき
        moveChange = true;
      else if (position_x + realSlitWidth < 0.0) // 左端に行き過ぎたとき
        moveChange = false;
    }
    break;

  case IMAGE_MOVE_MODE:
    if (repetition == 0)
    {
      if (position_x > 1.5 + (realSlitWidth / 2.0))      // 右端に行き過ぎたとき
        position_x = -1.5 - (realSlitWidth / 2.0);
      else if (position_x + 3.0 < 1.5 - (realSlitWidth / 2.0)) // 左端に行き過ぎたとき
        position_x = 1.5 + (realSlitWidth / 2.0);
    }
    else
    {
      if (position_x > 1.5 + (realSlitWidth / 2.0))      // 右端に行き過ぎたとき
        moveChange = true;
      else if (position_x + 3.0 < 1.5 - (realSlitWidth / 2.0)) // 左端に行き過ぎたとき
        moveChange = false;
    }
    break;

  default:
    break;
  }

  glutPostRedisplay(); // 再描画要求


  // バッファのクリア
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // モデルを見る準備
  glMatrixMode(GL_MODELVIEW);
  // 行列を初期化
  glLoadIdentity();

  // 現在のパラメーターを表示
  //viewParam();

  // 描画する
  switch (mode)
  {
  case SLIT_MOVE_MODE:  // スリットが動く
    draw_moveSlit(position_x, realSlitWidth, ImageMode);
    break;

  case IMAGE_MOVE_MODE: // 画像が動く
    draw_moveImage(position_x, realSlitWidth, ImageMode);
    break;

  default:
    break;
  }

  // 描画させる
  glFlush();
  // バッファの入れ替え
  glutSwapBuffers();

  // swap buf が終了するまでwait
  glFinish();
}

/**
 * @brief 現在の(x,y,z)を表示
 */
void viewParam(void)
{
  //printf("position_x : %lf\n", position_x);
  //printf("repetition : %d\n", repetition);
  //printf("mode : %d\n", mode);
  //printf("Slit width : %lf\n", realSlitWidth);
  printf("Slit speed : %lf\n", realSlitSpeed);
  //printf("Carrent display width : %d\n", glutGet(GLUT_INIT_WINDOW_WIDTH));
  printf("Dispplay width : %d\n", glutGet(GLUT_WINDOW_WIDTH));
}

/**
 * @brief 終了関数
 */
void gluiCallBack(int num)
{
  exit(0);
}

/**
 * @brief アイドル関数
 */
void idle(void)
{
  // 移動方向判別
  if (!moveChange)
    position_x += realSlitSpeed;
  else
    position_x -= realSlitSpeed;

  // 不用意な領域にいかない
  switch (mode)
  {
  case SLIT_MOVE_MODE:
    if (repetition == 0)
    {
      if (position_x > 2.95)     // 右端に行き過ぎたとき
        position_x = 0.0 - realSlitWidth;
      else if (position_x + realSlitWidth < 0.0) // 左端に行き過ぎたとき
        position_x = 2.95;
    }
    else
    {
      if (position_x > 2.95)     // 右端に行き過ぎたとき
        moveChange = true;
      else if (position_x + realSlitWidth < 0.0) // 左端に行き過ぎたとき
        moveChange = false;
    }
    break;

  case IMAGE_MOVE_MODE:
    if (repetition == 0)
    {
      if (position_x > 1.5 + (realSlitWidth / 2.0))      // 右端に行き過ぎたとき
        position_x = -1.5 - (realSlitWidth / 2.0);
      else if (position_x + 3.0 < 1.5 - (realSlitWidth / 2.0)) // 左端に行き過ぎたとき
        position_x = 1.5 + (realSlitWidth / 2.0);
    }
    else
    {
      if (position_x > 1.5 + (realSlitWidth / 2.0))      // 右端に行き過ぎたとき
        moveChange = true;
      else if (position_x + 3.0 < 1.5 - (realSlitWidth / 2.0)) // 左端に行き過ぎたとき
        moveChange = false;
    }
    break;

  default:
    break;
  }

  glutPostRedisplay(); // 再描画要求
}

void countFPS(void)
{
  ++time;
  now = glutGet(GLUT_ELAPSED_TIME);	// 経過時間を取得
  if (now - old < fRate)	return;

  // 1秒毎にFPS数表示(経過してなければ何もしない)
  if (1000 <= now - base){
    printf("Now FPS : %lf\n", (1000.0f / float(now - old)));
    base = now;
  }
  // Update
  glutPostRedisplay();

  old = now;
}

void timer(int value)
{
  // 移動方向判別
  if (!moveChange)
    position_x += realSlitSpeed;
  else
    position_x -= realSlitSpeed;

  // 不用意な領域にいかない
  switch (mode)
  {
  case SLIT_MOVE_MODE:
    if (repetition == 0)
    {
      if (position_x > 2.95)     // 右端に行き過ぎたとき
        position_x = 0.0 - realSlitWidth;
      else if (position_x + realSlitWidth < 0.0) // 左端に行き過ぎたとき
        position_x = 2.95;
    }
    else
    {
      if (position_x > 2.95)     // 右端に行き過ぎたとき
        moveChange = true;
      else if (position_x + realSlitWidth < 0.0) // 左端に行き過ぎたとき
        moveChange = false;
    }
    break;

  case IMAGE_MOVE_MODE:
    if (repetition == 0)
    {
      if (position_x > 1.5 + (realSlitWidth / 2.0))      // 右端に行き過ぎたとき
        position_x = -1.5 - (realSlitWidth / 2.0);
      else if (position_x + 3.0 < 1.5 - (realSlitWidth / 2.0)) // 左端に行き過ぎたとき
        position_x = 1.5 + (realSlitWidth / 2.0);
    }
    else
    {
      if (position_x > 1.5 + (realSlitWidth / 2.0))      // 右端に行き過ぎたとき
        moveChange = true;
      else if (position_x + 3.0 < 1.5 - (realSlitWidth / 2.0)) // 左端に行き過ぎたとき
        moveChange = false;
    }
    break;

  default:
    break;
  }

  glutPostRedisplay();
  // タイマー関数
  glutTimerFunc(16, timer, 0);
}

/**
 * @brief フルスクリーンにする関数
 */
void fullscreen(){
  int nMode = 0;
  DEVMODE devMode;
  HWND hWnd;
  hWnd = GetActiveWindow();

  // 描画変更される
  if (Change)
  {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (EnumDisplaySettings(NULL, nMode++, &devMode))
    {

      // 640×480をサポートしているか
      if (devMode.dmPelsWidth != X_SIZE || devMode.dmPelsHeight != Y_SIZE)
        continue;

      // 32ビットカラーをサポートしているか
      if (devMode.dmBitsPerPel != 32)
        continue;

      // テストして切り替えれるなら
      if (ChangeDisplaySettings(&devMode, CDS_TEST) == DISP_CHANGE_SUCCESSFUL)
        break;
    }
    ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
    glutFullScreen();
    glViewport(0, 0, X_SIZE, Y_SIZE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.4, (double)X_SIZE / (double)Y_SIZE, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
  }

  else{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    ChangeDisplaySettings(NULL, 0);
    glutPositionWindow(100, 100);

    glutReshapeWindow(X_SIZE, Y_SIZE);
    glViewport(0, 0, X_SIZE, Y_SIZE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.4, (double)X_SIZE / (double)Y_SIZE, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
  }
}