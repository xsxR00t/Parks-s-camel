#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <GL/GL.h>
#include <GL/glui.h>
#include <GL/glut.h>

/** ���[�U�[��`�֐� **/
#include "defaultParam.h"
#include "gl_init.h"
#include "texture.h"
#include "ppm.h"
#include "draw.h"

/**
 * @brief Main�֐�
 */
int main(int argc, char **argv)
{
  // Window�쐬�̂��߂̏������֐�
  glutInit(&argc, argv);
  // �f�B�X�v���C���[�h�̑I��
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  // �E�B���h�E�̃T�C�Y
  glutInitWindowSize(X_SIZE, Y_SIZE);
  // �����\���ʒu
  glutInitWindowPosition(150, 150);
  // �E�B���h�E�쐬�̖��O
  glutCreateWindow("Parks");

  realSlitWidth = (GLfloat)((3 * DISPPIX_X * 0.3) / (DISPSIZE_X * X_SIZE));
  realSlitSpeed = (GLfloat)((18000 * DISPSIZE_X * 3) / (58.823528 * DISPPIX_X * X_SIZE));

  gl_init();     // �S�̂̏������֐�
  loadTexture(); // �e�N�X�`���[�̓ǂݍ���
  setGlui();     // UI�ݒ�

  //wglSwapIntervalEXT(0);

  //glutKeyboardFunc(keyboard); // �L�[�{�[�h�C�x���g�o�^
  glutDisplayFunc(display);   // �`��C�x���g�o�^
  //glutIdleFunc(idle);         // �A�C�h���C�x���g�o�^
  glutIdleFunc(countFPS);
  //glutTimerFunc(16, timer, 0); // �^�C�}�[�֐�
  glutMainLoop();             // ���[�v����
}

/**
 * @brief UI�ݒ�֐�
 */
void setGlui(void)
{
  /* GLUI�R���g���[���[�̐ݒ� */
  GLUI * glui = GLUI_Master.create_glui("Control Panel", 0);

  /* �X���b�g�T�C�Y�̃e�L�X�g�{�b�N�X�ǉ� */
  GLUI_EditText * editSlitWidth = new GLUI_EditText(glui, "Slit width (cm)", &slitWidth, NULL, inputChangeSlitWidth);
  // ���E�l�Ƃ��̏���
  //editSlitWidth->set_float_limits(0.0, 1.0, GLUI_LIMIT_CLAMP);
  // �����l
  editSlitWidth->set_float_val(0.3);

  /* �ړ��X�s�[�h�̃e�L�X�g�{�b�N�X�ǉ� */
  GLUI_EditText * editSlitSpeed = new GLUI_EditText(glui, "Slit speed (cm)/s", &slitSpeed, NULL, inputChangeSlitSpeed);
  //editSlitSpeed->set_float_limits(0.0, 1.0, GLUI_LIMIT_CLAMP);
  editSlitSpeed->set_float_val(18000);

  // �d�؂��
  glui->add_separator();

  /* ���[�h�ύX�p�̃��W�I�{�^�� */
  // �e�L�X�g
  glui->add_statictext("Move select");
  GLUI_RadioGroup * mode_radio = new GLUI_RadioGroup(glui, &mode);
  // ���[�h�ύX�̍��ڐݒ�
  glui->add_radiobutton_to_group(mode_radio, "Slit Move");
  glui->add_radiobutton_to_group(mode_radio, "Image Move");

  // �d�؂��
  glui->add_separator();

  // �����{�^��
  new GLUI_Checkbox(glui, "Repetition", &repetition);

  glui->add_separator();

  /* �摜�ύX�̃��W�I�{�^�� */
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

  // �d�؂��
  glui->add_separator();

  /* exit�{�^�� */
  glui->add_button("Exit", 0, gluiCallBack);

  // idlez�R�[���o�b�N�֐���GLUI�œo�^
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
 * @brief �e�N�X�`���̓ǂݍ���
 */
void loadTexture()
{
  // �q�g�R�u���N�_
  runLoadTexture(&dromedaryCamel_lineDrowing_black, "dromedaryCamel_lineDrowing_black.ppm", 640, 480);
  runLoadTexture(&dromedaryCamel_lineDrowing_white, "dromedaryCamel_lineDrowing_white.ppm", 640, 480);
  runLoadTexture(&dromedaryCamel_black,       "dromedaryCamel_black.ppm",       640, 480);
  runLoadTexture(&dromedaryCamel_white,       "dromedaryCamel_white.ppm",       640, 480);

  // �t�^�R�u���N�_�摜
  runLoadTexture(&bactrianCamel_lineDrowing_black, "bactrianCamel_lineDrowing_black.ppm", 640, 480);
  runLoadTexture(&bactrianCamel_lineDrowing_white, "bactrianCamel_lineDrowing_white.ppm", 640, 480);
  runLoadTexture(&bactrianCamel_black,       "bactrianCamel_black.ppm",       640, 480);
  runLoadTexture(&bactrianCamel_white,       "bactrianCamel_white.ppm",       640, 480);

  // �����^���E
  runLoadTexture(&momotaro, "momotaro.ppm", 640, 480);

  // �X���b�g�̍��摜
  runLoadTexture(&blackSlit, "black.ppm", 512, 512);

  // �P���摜
  runLoadTexture(&circle,   "circle.ppm",   640, 480);
  runLoadTexture(&square,   "square.ppm",   640, 480);
  runLoadTexture(&triangle, "triangle.ppm", 640, 480);
}

/**
 * @brief �ǂݍ��݊ȗ����֐�
 * @param *obj : �Ώۂ̃e�N�X�`���\���̃|�C���^
 * @param filename : �Ώۂ̉摜��
 * @param width : ���T�C�Y
 * @param height : �c�T�C�Y
 */
void runLoadTexture(texture_t * obj, char * filename, int width, int height)
{
  // �摜�T�C�Y�̒�`
  obj->imageWidth = width;
  obj->imageHeight = height;

  // �e�N�X�`���摜�p�z��̊m��(���A�����ARGB��3)(���A�����ARGB��3)
  obj->texture_Image = (GLubyte *)malloc(sizeof(GLubyte)* obj->imageWidth * obj->imageHeight * 3);
  // �t�@�C���̃��[�h
  LoadPPM_ascii(filename, obj->texture_Image, obj->imageWidth, obj->imageHeight);
  // �t�@�C�����Z�b�g����
  set_texture(obj->texture_Image, &obj->texture_id, obj->imageWidth, obj->imageHeight);
}

/**
 * @brief �`��C�x���g�֐�
 */
void display()
{
  if (X_SIZE != glutGet(GLUT_WINDOW_WIDTH))
  {
    realSlitWidth = (GLfloat)((3 * DISPPIX_X * slitWidth) / (DISPSIZE_X * X_SIZE));
    realSlitSpeed = (GLfloat)((slitSpeed * DISPSIZE_X * 3) / (58.823528 * DISPPIX_X * X_SIZE)) * 100.0;
    printf("Slit speed : %lf\n", realSlitSpeed);
  }

  // �ړ���������
  if (!moveChange)
    position_x += realSlitSpeed;
  else
    position_x -= realSlitSpeed;

  // �s�p�ӂȗ̈�ɂ����Ȃ�
  switch (mode)
  {
  case SLIT_MOVE_MODE:
    if (repetition == 0)
    {
      if (position_x > 2.95)     // �E�[�ɍs���߂����Ƃ�
        position_x = 0.0 - realSlitWidth;
      else if (position_x + realSlitWidth < 0.0) // ���[�ɍs���߂����Ƃ�
        position_x = 2.95;
    }
    else
    {
      if (position_x > 2.95)     // �E�[�ɍs���߂����Ƃ�
        moveChange = true;
      else if (position_x + realSlitWidth < 0.0) // ���[�ɍs���߂����Ƃ�
        moveChange = false;
    }
    break;

  case IMAGE_MOVE_MODE:
    if (repetition == 0)
    {
      if (position_x > 1.5 + (realSlitWidth / 2.0))      // �E�[�ɍs���߂����Ƃ�
        position_x = -1.5 - (realSlitWidth / 2.0);
      else if (position_x + 3.0 < 1.5 - (realSlitWidth / 2.0)) // ���[�ɍs���߂����Ƃ�
        position_x = 1.5 + (realSlitWidth / 2.0);
    }
    else
    {
      if (position_x > 1.5 + (realSlitWidth / 2.0))      // �E�[�ɍs���߂����Ƃ�
        moveChange = true;
      else if (position_x + 3.0 < 1.5 - (realSlitWidth / 2.0)) // ���[�ɍs���߂����Ƃ�
        moveChange = false;
    }
    break;

  default:
    break;
  }

  glutPostRedisplay(); // �ĕ`��v��


  // �o�b�t�@�̃N���A
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // ���f�������鏀��
  glMatrixMode(GL_MODELVIEW);
  // �s���������
  glLoadIdentity();

  // ���݂̃p�����[�^�[��\��
  //viewParam();

  // �`�悷��
  switch (mode)
  {
  case SLIT_MOVE_MODE:  // �X���b�g������
    draw_moveSlit(position_x, realSlitWidth, ImageMode);
    break;

  case IMAGE_MOVE_MODE: // �摜������
    draw_moveImage(position_x, realSlitWidth, ImageMode);
    break;

  default:
    break;
  }

  // �`�悳����
  glFlush();
  // �o�b�t�@�̓���ւ�
  glutSwapBuffers();

  // swap buf ���I������܂�wait
  glFinish();
}

/**
 * @brief ���݂�(x,y,z)��\��
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
 * @brief �I���֐�
 */
void gluiCallBack(int num)
{
  exit(0);
}

/**
 * @brief �A�C�h���֐�
 */
void idle(void)
{
  // �ړ���������
  if (!moveChange)
    position_x += realSlitSpeed;
  else
    position_x -= realSlitSpeed;

  // �s�p�ӂȗ̈�ɂ����Ȃ�
  switch (mode)
  {
  case SLIT_MOVE_MODE:
    if (repetition == 0)
    {
      if (position_x > 2.95)     // �E�[�ɍs���߂����Ƃ�
        position_x = 0.0 - realSlitWidth;
      else if (position_x + realSlitWidth < 0.0) // ���[�ɍs���߂����Ƃ�
        position_x = 2.95;
    }
    else
    {
      if (position_x > 2.95)     // �E�[�ɍs���߂����Ƃ�
        moveChange = true;
      else if (position_x + realSlitWidth < 0.0) // ���[�ɍs���߂����Ƃ�
        moveChange = false;
    }
    break;

  case IMAGE_MOVE_MODE:
    if (repetition == 0)
    {
      if (position_x > 1.5 + (realSlitWidth / 2.0))      // �E�[�ɍs���߂����Ƃ�
        position_x = -1.5 - (realSlitWidth / 2.0);
      else if (position_x + 3.0 < 1.5 - (realSlitWidth / 2.0)) // ���[�ɍs���߂����Ƃ�
        position_x = 1.5 + (realSlitWidth / 2.0);
    }
    else
    {
      if (position_x > 1.5 + (realSlitWidth / 2.0))      // �E�[�ɍs���߂����Ƃ�
        moveChange = true;
      else if (position_x + 3.0 < 1.5 - (realSlitWidth / 2.0)) // ���[�ɍs���߂����Ƃ�
        moveChange = false;
    }
    break;

  default:
    break;
  }

  glutPostRedisplay(); // �ĕ`��v��
}

void countFPS(void)
{
  ++time;
  now = glutGet(GLUT_ELAPSED_TIME);	// �o�ߎ��Ԃ��擾
  if (now - old < fRate)	return;

  // 1�b����FPS���\��(�o�߂��ĂȂ���Ή������Ȃ�)
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
  // �ړ���������
  if (!moveChange)
    position_x += realSlitSpeed;
  else
    position_x -= realSlitSpeed;

  // �s�p�ӂȗ̈�ɂ����Ȃ�
  switch (mode)
  {
  case SLIT_MOVE_MODE:
    if (repetition == 0)
    {
      if (position_x > 2.95)     // �E�[�ɍs���߂����Ƃ�
        position_x = 0.0 - realSlitWidth;
      else if (position_x + realSlitWidth < 0.0) // ���[�ɍs���߂����Ƃ�
        position_x = 2.95;
    }
    else
    {
      if (position_x > 2.95)     // �E�[�ɍs���߂����Ƃ�
        moveChange = true;
      else if (position_x + realSlitWidth < 0.0) // ���[�ɍs���߂����Ƃ�
        moveChange = false;
    }
    break;

  case IMAGE_MOVE_MODE:
    if (repetition == 0)
    {
      if (position_x > 1.5 + (realSlitWidth / 2.0))      // �E�[�ɍs���߂����Ƃ�
        position_x = -1.5 - (realSlitWidth / 2.0);
      else if (position_x + 3.0 < 1.5 - (realSlitWidth / 2.0)) // ���[�ɍs���߂����Ƃ�
        position_x = 1.5 + (realSlitWidth / 2.0);
    }
    else
    {
      if (position_x > 1.5 + (realSlitWidth / 2.0))      // �E�[�ɍs���߂����Ƃ�
        moveChange = true;
      else if (position_x + 3.0 < 1.5 - (realSlitWidth / 2.0)) // ���[�ɍs���߂����Ƃ�
        moveChange = false;
    }
    break;

  default:
    break;
  }

  glutPostRedisplay();
  // �^�C�}�[�֐�
  glutTimerFunc(16, timer, 0);
}

/**
 * @brief �t���X�N���[���ɂ���֐�
 */
void fullscreen(){
  int nMode = 0;
  DEVMODE devMode;
  HWND hWnd;
  hWnd = GetActiveWindow();

  // �`��ύX�����
  if (Change)
  {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (EnumDisplaySettings(NULL, nMode++, &devMode))
    {

      // 640�~480���T�|�[�g���Ă��邩
      if (devMode.dmPelsWidth != X_SIZE || devMode.dmPelsHeight != Y_SIZE)
        continue;

      // 32�r�b�g�J���[���T�|�[�g���Ă��邩
      if (devMode.dmBitsPerPel != 32)
        continue;

      // �e�X�g���Đ؂�ւ����Ȃ�
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