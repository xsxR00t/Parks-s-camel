#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>

#include "ppm.h"
#include "draw.h"

/**
 * @brief �X���b�g������
 * @param x,y,z : ����W
 * @param slitWidth : �X���b�g�̕�
 */
void draw_moveSlit(GLfloat x, GLfloat slitWidth, int ImageMode, int slitColor)
{
  /* �摜��`�� */
  // �������W���v�b�V��
  glPushMatrix();
  // �����ʒu
  glTranslatef(0.0, 0.0, -3.6);
  // �摜�e�N�X�`���쐬
  bindTexture(&ImageMode);
  // �摜�̃v���[�g��`��
  createObject();
  // �������W�ɖ߂�
  glPopMatrix();

  /* �X���b�g�`�� */
  // �������W���v�b�V��
  glPushMatrix();
  glTranslatef(x - 3.0, 0.0, -3.5);
  createObjectSlit(slitColor);

  // �������W���v�b�V��
  glPushMatrix();
  glTranslatef(x + slitWidth, 0.0, -3.5);
  createObjectSlit(slitColor);
}

/**
 * @brief �摜������
 * @param x : �x���W
 * @param slitWidth : �X���b�g�Ԋu
 */
void draw_moveImage(GLfloat x, GLfloat slitWidth, int ImageMode, int slitColor)
{
  /* �X���b�g�`�� */
  // �������W���v�b�V��
  glPushMatrix();
  glTranslatef(-1.5 - (slitWidth / 2.0), 0.0, -3.5);
  createObjectSlit(slitColor);

  // �������W���v�b�V��
  glPushMatrix();
  glTranslatef(1.5 + (slitWidth / 2.0), 0.0, -3.5);
  createObjectSlit(slitColor);

  /* �摜��`�� */
  // �������W���v�b�V��
  glPushMatrix();
  // �����ʒu
  glTranslatef(x, 0.0, -3.6);
  // �摜�e�N�X�`���쐬
  bindTexture(&ImageMode);
  // �摜�̃v���[�g��`��
  createObject();

  // �������W�ɖ߂�
  glPopMatrix();
}

/**
 * @brief �摜�𒣂�ւ��� 
 * @param * id : �I�����ꂽ �摜ID
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
 * @brief �I�u�W�F�N�g�̍��W���ȗ�
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
 * @brief �X���b�g���쐬���邾���̊֐�
 */
void createObjectSlit(int slitColor)
{
  // �摜�e�N�X�`���쐬
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
  // �X���b�g1���ڂ̃v���[�g���쐬
  createObject();
  // �e�N�X�`���̃o�C���h����
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
  // �������W�ɖ߂�
  glPopMatrix();
}