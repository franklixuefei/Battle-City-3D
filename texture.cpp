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

//  glPixelStorei(GL_UNPACK_ALIGNMENT, sizeof(GLubyte));
  glGenTextures(6, textures);
//  glBindTexture(GL_TEXTURE_2D, textures);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
//      GL_LINEAR_MIPMAP_NEAREST);
//  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE,
//      m_int_images[index]);
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

//  glEnable(GL_TEXTURE_2D);
//  //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
//  gluQuadricTexture(quadric, true);
//  glBindTexture(GL_TEXTURE_2D, textures[index]);
}

void Texture::end_tex_map()
{
  glFlush();
  glDisable(GL_TEXTURE_CUBE_MAP);
  glDisable(GL_TEXTURE_2D);
}

//bool Texture::GenerateNormalisationCubeMap()
//{
//  unsigned char * data = new unsigned char[256 * 256 * 3];
//  if (!data) {
//    printf("Unable to allocate memory for texture data for cube map\n");
//    return false;
//  }
//
//  //some useful variables
//  int size = 256;
//  float offset = 0.5f;
//  float halfSize = 128.0f;
//  Vector3D tempVector;
//  unsigned char * bytePtr;
//
//  //positive x
//  bytePtr = data;
//
//  for (int j = 0; j < size; j++) {
//    for (int i = 0; i < size; i++) {
//      tempVector[0] = halfSize;
//      tempVector[1] = (-(j + offset - halfSize));
//      tempVector[2] = (-(i + offset - halfSize));
//
//      tempVector.normalize();
//
//      bytePtr[0] = (unsigned char) (tempVector[0] * 255);
//      bytePtr[1] = (unsigned char) (tempVector[1] * 255);
//      bytePtr[2] = (unsigned char) (tempVector[2] * 255);
//
//      bytePtr += 3;
//    }
//  }
//  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB, 0, GL_RGBA8, 32, 32, 0,
//      GL_RGB, GL_UNSIGNED_BYTE, data);
//
//  //negative x
//  bytePtr = data;
//
//  for (int j = 0; j < size; j++) {
//    for (int i = 0; i < size; i++) {
//      tempVector[0] = (-halfSize);
//      tempVector[1] = (-(j + offset - halfSize));
//      tempVector[2] = ((i + offset - halfSize));
//
//      tempVector.normalize();
//
//      bytePtr[0] = (unsigned char) (tempVector[0] * 255);
//      bytePtr[1] = (unsigned char) (tempVector[1] * 255);
//      bytePtr[2] = (unsigned char) (tempVector[2] * 255);
//
//      bytePtr += 3;
//    }
//  }
//  glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB, 0, GL_RGBA8, 32, 32, 0,
//      GL_RGB, GL_UNSIGNED_BYTE, data);
//
//  //positive y
//  bytePtr = data;
//
//  for (int j = 0; j < size; j++) {
//    for (int i = 0; i < size; i++) {
//      tempVector[0] = i + offset - halfSize;
//      tempVector[1] = halfSize;
//      tempVector[2] = ((j + offset - halfSize));
//
//      tempVector.normalize();
//
//      bytePtr[0] = (unsigned char) (tempVector[0] * 255);
//      bytePtr[1] = (unsigned char) (tempVector[1] * 255);
//      bytePtr[2] = (unsigned char) (tempVector[2] * 255);
//
//      bytePtr += 3;
//    }
//  }
//  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB, 0, GL_RGBA8, 32, 32, 0,
//      GL_RGB, GL_UNSIGNED_BYTE, data);
//
//  //negative y
//  bytePtr = data;
//
//  for (int j = 0; j < size; j++) {
//    for (int i = 0; i < size; i++) {
//      tempVector[0] = (i + offset - halfSize);
//      tempVector[1] = (-halfSize);
//      tempVector[2] = (-(j + offset - halfSize));
//
//      tempVector.normalize();
//
//      bytePtr[0] = (unsigned char) (tempVector[0] * 255);
//      bytePtr[1] = (unsigned char) (tempVector[1] * 255);
//      bytePtr[2] = (unsigned char) (tempVector[2] * 255);
//
//      bytePtr += 3;
//    }
//  }
//  glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB, 0, GL_RGBA8, 32, 32, 0,
//      GL_RGB, GL_UNSIGNED_BYTE, data);
//
//  //positive z
//  bytePtr = data;
//
//  for (int j = 0; j < size; j++) {
//    for (int i = 0; i < size; i++) {
//      tempVector[0] = (i + offset - halfSize);
//      tempVector[1] = (-(j + offset - halfSize));
//      tempVector[2] = (halfSize);
//
//      tempVector.normalize();
//
//      bytePtr[0] = (unsigned char) (tempVector[0] * 255);
//      bytePtr[1] = (unsigned char) (tempVector[1] * 255);
//      bytePtr[2] = (unsigned char) (tempVector[2] * 255);
//
//      bytePtr += 3;
//    }
//  }
//  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB, 0, GL_RGBA8, 32, 32, 0,
//      GL_RGB, GL_UNSIGNED_BYTE, data);
//
//  //negative z
//  bytePtr = data;
//
//  for (int j = 0; j < size; j++) {
//    for (int i = 0; i < size; i++) {
//      tempVector[0] = (-(i + offset - halfSize));
//      tempVector[1] = (-(j + offset - halfSize));
//      tempVector[2] = (-halfSize);
//
//      tempVector.normalize();
//
//      bytePtr[0] = (unsigned char) (tempVector[0] * 255);
//      bytePtr[1] = (unsigned char) (tempVector[1] * 255);
//      bytePtr[2] = (unsigned char) (tempVector[2] * 255);
//
//      bytePtr += 3;
//    }
//  }
//  glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB, 0, GL_RGBA8, 32, 32, 0,
//      GL_RGB, GL_UNSIGNED_BYTE, data);
//
//  delete[] data;
//
//  return true;
//}

