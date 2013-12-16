#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>

#include "ppm.h"
#include "draw.h"

/**
 * @brief スリットが動く
 * @param x,y,z : 基準座標
 * @param slitWidth : スリットの幅
 */
void draw_moveSlit(GLfloat x, GLfloat slitWidth, int ImageMode, int slitColor)
{
  /* 画像を描画 */
  // 初期座標をプッシュ
  glPushMatrix();
  // 初期位置
  glTranslatef(0.0, 0.0, -3.6);
  // 画像テクスチャ作成
  bindTexture(&ImageMode);
  // 画像のプレートを描画
  createObject();
  // 初期座標に戻す
  glPopMatrix();

  /* スリット描画 */
  // 初期座標をプッシュ
  glPushMatrix();
  glTranslatef(x - 3.0, 0.0, -3.5);
  createObjectSlit(slitColor);

  // 初期座標をプッシュ
  glPushMatrix();
  glTranslatef(x + slitWidth, 0.0, -3.5);
  createObjectSlit(slitColor);
}

/**
 * @brief 画像が動く
 * @param x : 基準x座標
 * @param slitWidth : スリット間隔
 */
void draw_moveImage(GLfloat x, GLfloat slitWidth, int ImageMode, int slitColor)
{
  /* スリット描画 */
  // 初期座標をプッシュ
  glPushMatrix();
  glTranslatef(-1.5 - (slitWidth / 2.0), 0.0, -3.5);
  createObjectSlit(slitColor);

  // 初期座標をプッシュ
  glPushMatrix();
  glTranslatef(1.5 + (slitWidth / 2.0), 0.0, -3.5);
  createObjectSlit(slitColor);

  /* 画像を描画 */
  // 初期座標をプッシュ
  glPushMatrix();
  // 初期位置
  glTranslatef(x, 0.0, -3.6);
  // 画像テクスチャ作成
  bindTexture(&ImageMode);
  // 画像のプレートを描画
  createObject();

  // 初期座標に戻す
  glPopMatrix();
}

/**
 * @brief 画像を張り替える 
 * @param * id : 選択された 画像ID
 */
void bindTexture(int * id)
{
  switch (*id)
  {
  case DROMEDARYCAMEL_LINEDROWING_BLACK:
    glBindTexture(GL_TEXTURE_2D, dromedaryCamel_lineDrowing_black.texture_id);
    break;

  case  DROMEDARYCAMEL_LINEDROWING_WHITE:
    glBindTexture(GL_TEXTURE_2D, dromedaryCamel_lineDrowing_white.texture_id);
    break;

  case DROMEDARYCAMEL_BLACK:
    glBindTexture(GL_TEXTURE_2D, dromedaryCamel_black.texture_id);
    break;

  case DROMEDARYCAMEL_WHITE:
    glBindTexture(GL_TEXTURE_2D, dromedaryCamel_white.texture_id);
    break;

  case BACTRIANCAMEL_LINEDROWING_BLACK:
    glBindTexture(GL_TEXTURE_2D, bactrianCamel_lineDrowing_black.texture_id);
    break;

  case BACTRIANCAMEL_LINEDROWING_WHITE:
    glBindTexture(GL_TEXTURE_2D, bactrianCamel_lineDrowing_white.texture_id);
    break;

  case BACTRIANCAMEL_BLACK:
    glBindTexture(GL_TEXTURE_2D, bactrianCamel_black.texture_id);
    break;

  case BACTRIANCAMEL_WHITE:
    glBindTexture(GL_TEXTURE_2D, bactrianCamel_white.texture_id);
    break;

  case MOMOTARO:
    glBindTexture(GL_TEXTURE_2D, momotaro.texture_id);
    break;

  case CIRCLE_IMAGE:
    glBindTexture(GL_TEXTURE_2D, circle.texture_id);
    break;

  case SQUARE_IMAGE:
    glBindTexture(GL_TEXTURE_2D, square.texture_id);
    break;

  case TRIANGLE_IMAGE:
    glBindTexture(GL_TEXTURE_2D, triangle.texture_id);
    break;

  default:
    break;
  }
}

/**
 * @brief オブジェクトの座標を簡略
 */
void createObject(void)
{
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0);
  glVertex3f(-1.5, 1.5, 0.0);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(1.5, 1.5, 0.0);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(1.5, -1.5, 0.0);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-1.5, -1.5, 0.0);
  glEnd();
}

/**
 * @brief スリットを作成するだけの関数
 */
void createObjectSlit(int slitColor)
{
  // 画像テクスチャ作成
  switch (slitColor)
  {
  case 0:
    glBindTexture(GL_TEXTURE_2D, blackSlit.texture_id);
    break;
   
  case 1:
    glBindTexture(GL_TEXTURE_2D, whiteSlit.texture_id);
    break;

  default:
    break;
  }
  // スリット1枚目のプレートを作成
  createObject();
  // テクスチャのバインド解除
  switch (slitColor)
  {
  case 0:
    glBindTexture(GL_TEXTURE_2D, blackSlit.texture_id);
    break;

  case 1:
    glBindTexture(GL_TEXTURE_2D, whiteSlit.texture_id);
    break;

  default:
    break;
  }
  // 初期座標に戻す
  glPopMatrix();
}