#include "texture.hpp"
#include "algebra.hpp"
#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;

Texture* Texture::texture_instance = 0;

Texture* Texture::getInstance()
{
  if (!texture_instance) {
    texture_instance = new Texture();
  }
  return texture_instance;
}

Texture::Texture()
{
  width = 256;
  height = 256;
  load_textures();
}

Texture::~Texture()
{
  glDeleteTextures(6, textures);
}

void Texture::load_textures()
{
  m_images[0].loadPng("./textures/sand.png");
  m_images[1].loadPng("./textures/brick.png");
  m_images[2].loadPng("./textures/steel.png");
  m_images[3].loadPng("./textures/water.png");
  m_images[4].loadPng("./textures/snow.png");
  m_images[5].loadPng("./textures/grass.png");

  for (int index = 0; index < 6; index++) {
    for (int i = 0; i < width; i++) {
      for (int j = 0; j < height; j++) {
        m_int_images[index][i][j][0] =
            (GLubyte) (m_images[index](i, j, 0) * 255);
        m_int_images[index][i][j][1] =
            (GLubyte) (m_images[index](i, j, 1) * 255);
        m_int_images[index][i][j][2] =
            (GLubyte) (m_images[index](i, j, 2) * 255);
      }
    }
  }
  glGenTextures(6, textures);
}

void Texture::set_texture(int index)
{
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textures[index]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
      GL_LINEAR_MIPMAP_NEAREST);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE,
      m_int_images[index]);
}

void Texture::end_tex_map()
{
  glFlush();
  glDisable(GL_TEXTURE_CUBE_MAP);
  glDisable(GL_TEXTURE_2D);
}
