#ifndef _PPM_H_
#define _PPM_H_

// �摜�����������߂̍\����
typedef struct _TAG_TEXTURE
{
  GLubyte * texture_Image;
  GLuint texture_id;

  int imageWidth;
  int imageHeight;
} texture_t;

// �摜�v�ϐ�(extern�ɂ���Đ錾�̂�)
// ���̂� defaultParam.h �ɋL�q����

/* �q�g�R�u���N�_ */
extern texture_t dromedaryCamel_lineDrowing_black;
extern texture_t dromedaryCamel_lineDrowing_white;
extern texture_t dromedaryCamel_black;
extern texture_t dromedaryCamel_white;

/* �t�^�R�u���N�_ */
extern texture_t bactrianCamel_lineDrowing_black;
extern texture_t bactrianCamel_lineDrowing_white;
extern texture_t bactrianCamel_black;
extern texture_t bactrianCamel_white;

/* �����^���E */
extern texture_t momotaro;

/* �X���b�g�p�̍��w�i */
extern texture_t blackSlit;

/* �P���}�` */
extern texture_t circle;
extern texture_t square;
extern texture_t triangle;

/**
 * @brief �A�X�L�[�R�[�h�ŕ���������ppm�t�H�[�}�b�g��ǂݍ���
 */
void LoadPPM_ascii(char file_name[], GLubyte image[], int x_size, int y_size);

#endif