#include <windows.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief �A�X�L�[�R�[�h�ŕ���������ppm�t�H�[�}�b�g��ǂݍ���
 */
void LoadPPM_ascii(char file_name[], GLubyte image[], int x_size, int y_size)
{
  FILE *fp;      // �t�@�C���|�C���^�̒�`
  char buf[100]; // �o�b�t�@�[�̗p��
  int i;         // ���[�v�p�ϐ�
  int header_lines = 3;

  // �t�@�C���ɃA�N�Z�X����
  if ((fp = fopen(file_name, "r")) == NULL){ // �ǂݍ��݃��[�h
    // �G���[�\��
    fprintf(stderr, "Cannot open PPM file %s\n", file_name);
    // �I��
    exit(0);
  }

  // header_lines��'#'�܂œǂݍ���ł���
  for (i = 0; i < header_lines; i++){
    fgets(buf, 100, fp);
    if (*buf == '#'){
      i--;
    }
  }
  // �c�A���ARGB���ǂݍ���
  for (i = 0; i < x_size * y_size * 3; i++){
    fscanf(fp, "%d", &image[i]);
  }

  // �t�@�C���̃N���[�Y
  fclose(fp);
}