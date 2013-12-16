#include <GL/glut.h>
#include "ppm.h"

#ifndef _DEFAULTPARAM_H_
#define _DEFAULTPARAM_H_

/* �E�B���h�E�Y�̃T�C�Y */
#define X_SIZE 640
#define Y_SIZE 480

/* �f�B�X�v���C�̕����P��(cm) */

// Display
/*static const float DISPSIZE_X = 48;
static const float DISPPIX_X  = 1900;*/

// Dynabook
static const float DISPSIZE_X = 29.2;
static const float DISPPIX_X  = 1366;

/* ���[�h�ύX�p�̕ϐ� */
#define SLIT_MOVE_MODE  0 // �X���b�g���������[�h
#define IMAGE_MOVE_MODE 1 // ���N�_�摜���������[�h

/* ppm.h�ɐ錾���ꂽ�ϐ��̒�` */
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

/* �����p�p�����[�^�[ */
// �ړ��p�ϐ�
GLfloat position_x = 0.0;
// �X���b�g���ϐ�
GLfloat slitWidth = 0.0;
// �X���b�g�X�s�[�h�ϐ�
GLfloat slitSpeed = 0.0;

// �ϊ����ʕۑ��ϐ�
GLfloat realSlitWidth = 0.0;
GLfloat realSlitSpeed = 0.0;

/* FPS�֐� */
double time; // �o�ߎ���
float fps = 60.0f;   // frame / s
float fRate = 16.666667f; // s / frame(ms)
int now = 0, old = 0, base = 0;

/* UI�p�ϐ� */
int mode = IMAGE_MOVE_MODE;   // ���[�h�I��ϐ�
int slitColor = 0;  // �X���b�g�摜�ύX
int ImageMode = 0;  // �摜�I��ϐ�
int repetition = 0; // �����@�\�p�ϐ�

/* fps�p�ϐ� */
int GLframe = 0;     // �t���[����
int GLtimenow = 0;   // �o�ߎ���
int GLtimebase = 0;  // �v���J�n����

bool Change = false;     // ��ʐ؂�ւ��t���O
bool moveChange = false; // �ړ������؂�ւ��t���O

/* �v���g�^�C�v�錾 */
// �`��֐�
void display();
// �L�[�{�[�h�A�N�V����
void keyboard(unsigned char key, int x, int y);
// �A�C�h���֐�
void idle();
// �^�C�}�[�֐�
void timer(int value);

// UI�ݒ�֐�
void setGlui();
// �X���b�g���ύX�֐�
void inputChangeSlitWidth(int num);
// �X���b�g�X�s�[�h�ύX�֐�
void inputChangeSlitSpeed(int num);
// �e�N�X�`���ǂݍ��݊֐�
void loadTexture();
// �ǂݍ��݊ȗ����֐�
void runLoadTexture(texture_t * obj, char * filename, int width, int height);
// �o�͊֐�
void viewParam();
// EXIT�p�̃R�[���o�b�N�֐�
void gluiCallBack(int num);
// �t���X�N���[�����[�h�֐�
void fullscreen(void);
void countFPS();

#endif