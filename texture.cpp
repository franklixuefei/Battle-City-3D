#include "texture.h"
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
  textureImageWidth = 256;
  textureImageHeight = 256;
}

Texture::~Texture()
{
  glDeleteTextures(1, &texNamePlanet);
}

void Texture::load_planet_texture(const std::string& filename, int index)
{
  m_images[index].loadPng(filename);
  textureImageWidth = m_images[index].width();
  textureImageHeight = m_images[index].height();
  //load image
  int i = 0;
  int j = 0;
  for (i = 0; i < m_images[index].width(); i++) {
    for (j = 0; j < m_images[index].height(); j++) {
      planet_tex_img[i][j][0] = (GLubyte) (m_images[index](i, j, 0) * 255);
      planet_tex_img[i][j][1] = (GLubyte) (m_images[index](i, j, 1) * 255);
      planet_tex_img[i][j][2] = (GLubyte) (m_images[index](i, j, 2) * 255);
    }
  }
  //initialize
  glPixelStorei(GL_UNPACK_ALIGNMENT, sizeof(GLubyte));
  glGenTextures(1, &texNamePlanet);
  glBindTexture(GL_TEXTURE_2D, texNamePlanet);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
      GL_LINEAR_MIPMAP_NEAREST);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, textureImageWidth, textureImageHeight,
      GL_RGB, GL_UNSIGNED_BYTE, planet_tex_img);
}

void Texture::apply_planet_texture(GLUquadric* quadric)
{
  glEnable(GL_TEXTURE_2D);
  //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  gluQuadricTexture(quadric, true);
  glBindTexture(GL_TEXTURE_2D, texNamePlanet);
}

void Texture::end_tex_map()
{
  glFlush();
  glDisable(GL_TEXTURE_CUBE_MAP);
  glDisable(GL_TEXTURE_2D);
}

bool Texture::GenerateNormalisationCubeMap()
{
  unsigned char * data = new unsigned char[256 * 256 * 3];
  if (!data) {
    printf("Unable to allocate memory for texture data for cube map\n");
    return false;
  }

  //some useful variables
  int size = 256;
  float offset = 0.5f;
  float halfSize = 128.0f;
  Vector3D tempVector;
  unsigned char * bytePtr;

  //positive x
  bytePtr = data;

  for (int j = 0; j < size; j++) {
    for (int i = 0; i < size; i++) {
      tempVector[0] = halfSize;
      tempVector[1] = (-(j + offset - halfSize));
      tempVector[2] = (-(i + offset - halfSize));

      tempVector.normalize();

      bytePtr[0] = (unsigned char) (tempVector[0] * 255);
      bytePtr[1] = (unsigned char) (tempVector[1] * 255);
      bytePtr[2] = (unsigned char) (tempVector[2] * 255);

      bytePtr += 3;
    }
  }
  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB, 0, GL_RGBA8, 32, 32, 0,
      GL_RGB, GL_UNSIGNED_BYTE, data);

  //negative x
  bytePtr = data;

  for (int j = 0; j < size; j++) {
    for (int i = 0; i < size; i++) {
      tempVector[0] = (-halfSize);
      tempVector[1] = (-(j + offset - halfSize));
      tempVector[2] = ((i + offset - halfSize));

      tempVector.normalize();

      bytePtr[0] = (unsigned char) (tempVector[0] * 255);
      bytePtr[1] = (unsigned char) (tempVector[1] * 255);
      bytePtr[2] = (unsigned char) (tempVector[2] * 255);

      bytePtr += 3;
    }
  }
  glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB, 0, GL_RGBA8, 32, 32, 0,
      GL_RGB, GL_UNSIGNED_BYTE, data);

  //positive y
  bytePtr = data;

  for (int j = 0; j < size; j++) {
    for (int i = 0; i < size; i++) {
      tempVector[0] = i + offset - halfSize;
      tempVector[1] = halfSize;
      tempVector[2] = ((j + offset - halfSize));

      tempVector.normalize();

      bytePtr[0] = (unsigned char) (tempVector[0] * 255);
      bytePtr[1] = (unsigned char) (tempVector[1] * 255);
      bytePtr[2] = (unsigned char) (tempVector[2] * 255);

      bytePtr += 3;
    }
  }
  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB, 0, GL_RGBA8, 32, 32, 0,
      GL_RGB, GL_UNSIGNED_BYTE, data);

  //negative y
  bytePtr = data;

  for (int j = 0; j < size; j++) {
    for (int i = 0; i < size; i++) {
      tempVector[0] = (i + offset - halfSize);
      tempVector[1] = (-halfSize);
      tempVector[2] = (-(j + offset - halfSize));

      tempVector.normalize();

      bytePtr[0] = (unsigned char) (tempVector[0] * 255);
      bytePtr[1] = (unsigned char) (tempVector[1] * 255);
      bytePtr[2] = (unsigned char) (tempVector[2] * 255);

      bytePtr += 3;
    }
  }
  glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB, 0, GL_RGBA8, 32, 32, 0,
      GL_RGB, GL_UNSIGNED_BYTE, data);

  //positive z
  bytePtr = data;

  for (int j = 0; j < size; j++) {
    for (int i = 0; i < size; i++) {
      tempVector[0] = (i + offset - halfSize);
      tempVector[1] = (-(j + offset - halfSize));
      tempVector[2] = (halfSize);

      tempVector.normalize();

      bytePtr[0] = (unsigned char) (tempVector[0] * 255);
      bytePtr[1] = (unsigned char) (tempVector[1] * 255);
      bytePtr[2] = (unsigned char) (tempVector[2] * 255);

      bytePtr += 3;
    }
  }
  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB, 0, GL_RGBA8, 32, 32, 0,
      GL_RGB, GL_UNSIGNED_BYTE, data);

  //negative z
  bytePtr = data;

  for (int j = 0; j < size; j++) {
    for (int i = 0; i < size; i++) {
      tempVector[0] = (-(i + offset - halfSize));
      tempVector[1] = (-(j + offset - halfSize));
      tempVector[2] = (-halfSize);

      tempVector.normalize();

      bytePtr[0] = (unsigned char) (tempVector[0] * 255);
      bytePtr[1] = (unsigned char) (tempVector[1] * 255);
      bytePtr[2] = (unsigned char) (tempVector[2] * 255);

      bytePtr += 3;
    }
  }
  glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB, 0, GL_RGBA8, 32, 32, 0,
      GL_RGB, GL_UNSIGNED_BYTE, data);

  delete[] data;

  return true;
}

