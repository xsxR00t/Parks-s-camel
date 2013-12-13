#include <Windows.h>
#include <GL/GL.h>

/**
 * @brief �e�N�X�`���摜���Z�b�g����
 */
void set_texture(GLubyte camerlTexture_image[], GLuint *camerlTexture_id, int x_size, int y_size)
{
  // �e�N�X�`����m�̓o�C�g�P�ʂɋl�ߍ��܂�Ă���
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  // �e�N�X�`���I�u�W�F�N�g�𐶐����ĉ摜��^����
  glGenTextures(1, camerlTexture_id);
  // �w�肵���e�N�X�`����L���ɂ���
  glBindTexture(GL_TEXTURE_2D, *camerlTexture_id);
  // �ǂݍ��񂾃f�[�^���e�N�X�`���I�u�W�F�N�g�ɒ�`����
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
    x_size,
    y_size, 0,
    GL_RGB, GL_UNSIGNED_BYTE,
    camerlTexture_image);

  /* �N�����v�Ɛ܂�Ԃ��̐ݒ�
  GL_REPEAT �e�N�X�`���𔽕����ē\��t����
  GL_CLAMP �e�N�X�`����ł��؂�
  */
  // �e�N�X�`�����W����s�������̐ݒ�
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  // �e�N�X�`�����W����t�������̐ݒ�
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  /* �e�N�X�`���̊g��E�k�����̐ݒ�
  GL_LINEAR ���ꂢ�����v�Z���Ԃ�������
  GL_NEAREST �������v�Z���Ԃ͏��Ȃ�
  */
  // �g�傳�ꂽ�Ƃ��̐ݒ�
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // �k�����ꂽ�Ƃ��̐ݒ�
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  // �e�N�X�`����\��t����I�u�W�F�N�g�̐F�̍������@��ݒ�
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  // �}�e���A���̒�`
  glEnable(GL_TEXTURE_2D);
  // �@���������v�Z
  glEnable(GL_AUTO_NORMAL);
  // ���K��
  glEnable(GL_NORMALIZE);
  // �f�v�X�e�X�g�L��
  glEnable(GL_DEPTH_TEST);
  // ���_�̎��v�����\�Ƃ݂Ȃ�
  glFrontFace(GL_CW);
}