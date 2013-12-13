#include <Windows.h>
#include <GL/GL.h>

/**
 * @brief テクスチャ画像をセットする
 */
void set_texture(GLubyte camerlTexture_image[], GLuint *camerlTexture_id, int x_size, int y_size)
{
  // テクスチャ画僧はバイト単位に詰め込まれている
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  // テクスチャオブジェクトを生成して画像を与える
  glGenTextures(1, camerlTexture_id);
  // 指定したテクスチャを有効にする
  glBindTexture(GL_TEXTURE_2D, *camerlTexture_id);
  // 読み込んだデータをテクスチャオブジェクトに定義する
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
    x_size,
    y_size, 0,
    GL_RGB, GL_UNSIGNED_BYTE,
    camerlTexture_image);

  /* クランプと折り返しの設定
  GL_REPEAT テクスチャを反復して貼り付ける
  GL_CLAMP テクスチャを打ち切る
  */
  // テクスチャ座標軸でs軸方向の設定
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  // テクスチャ座標軸でt軸方向の設定
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  /* テクスチャの拡大・縮小時の設定
  GL_LINEAR きれいだが計算時間がかかる
  GL_NEAREST 汚いが計算時間は少ない
  */
  // 拡大されたときの設定
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // 縮小されたときの設定
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  // テクスチャを貼り付けるオブジェクトの色の合成方法を設定
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  // マテリアルの定義
  glEnable(GL_TEXTURE_2D);
  // 法線を自動計算
  glEnable(GL_AUTO_NORMAL);
  // 正規化
  glEnable(GL_NORMALIZE);
  // デプステスト有効
  glEnable(GL_DEPTH_TEST);
  // 頂点の時計周りを表とみなす
  glFrontFace(GL_CW);
}