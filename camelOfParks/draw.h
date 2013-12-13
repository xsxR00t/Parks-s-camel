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
 * @brief �X���b�g������
 * @param x : �x���W
 * @param slitWidth : �X���b�g�Ԋu
 * @param ImageMode : �摜�ύX�p�̕ϐ�
 */
void draw_moveSlit(GLfloat x, GLfloat slitWidth, int ImageMode);

/**
 * @brief �X���b�g������
 * @param x : �x���W
 * @param slitWidth : �X���b�g�Ԋu
 */
void draw_moveImage(GLfloat x, GLfloat slitWidth, int ImageMode);

/**
 * @brief �摜�𒣂�ւ���
 * @param * id : �I�����ꂽ�摜ID
 */
void bindTexture(int * id);

/**
 * @brief �I�u�W�F�N�g�̍��W���ȗ�
 */
void createObject(void);

/**
 * @brief �X���b�g���쐬���邾���̊֐�
 */
void createObjectSlit(void);

#endif