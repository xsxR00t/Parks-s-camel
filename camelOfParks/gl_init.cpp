#include <Windows.h>
#include <GL/GL.h>
#include <GL/glut.h>

/**
 * @brief �`��ݒ�֐�
 */
void gl_init()
{
  // (RGBA)���[���ɂ���(���ŉ�ʂ�������)
  glClearColor(1.0, 1.0, 1.0, 0.0);
  // �������e�̍s����w�肷��
  glMatrixMode(GL_PROJECTION);
  // ���ݑI������Ă���s���������
  glLoadIdentity();
  // �A�X�y�N�g��Ȃǂ̐ݒ�
  gluPerspective(45.0, 1.0, 2.0, 20.0);
  // �e���p�`�̑O��֌W����
  glEnable(GL_DEPTH_TEST);
}