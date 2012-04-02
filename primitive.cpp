#include <GL/glu.h>
#include "primitive.hpp"
#include "texture.hpp"

Primitive::~Primitive()
{
}

Sphere::Sphere()
{
  m_sphere = new NonhierSphere(Point3D(0, 0, 0), 1);
}

Cube::Cube()
{
  m_box = new NonhierBox(Point3D(0, 0, 0), 1);
}

Sphere::~Sphere()
{
  delete m_sphere;
}

Cube::~Cube()
{
  delete m_box;
}

NonhierSphere::~NonhierSphere()
{
}

NonhierBox::~NonhierBox()
{
}

void Sphere::walk_gl(bool picking) const
{
  m_sphere->walk_gl(picking);
}

void Cube::walk_gl(bool picking) const
{
  m_box->walk_gl(picking);
}

void NonhierSphere::walk_gl(bool picking) const
{
  GLUquadric* quadric = gluNewQuadric();

  gluQuadricNormals(quadric, GLU_SMOOTH);
  gluQuadricTexture(quadric, GL_TRUE);
  gluQuadricDrawStyle(quadric, GLU_FILL);
  gluSphere(quadric, 1.0, 45, 90);
}

void Primitive::draw_floor(Point3D m_pos, double m_size) const
{
  glPushMatrix();
    glScalef(m_size, m_size, m_size);
    glTranslatef(m_pos[0], m_pos[1], m_pos[2]);
    glBegin (GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 1.0f);
    glEnd();
    glPopMatrix();
}

void Primitive::draw_box(Point3D m_pos, double m_size) const
{
  glPushMatrix();
  glScalef(m_size, m_size, m_size);
  glTranslatef(m_pos[0], m_pos[1], m_pos[2]);
  glBegin (GL_QUADS);
  // Front Face
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(1.0f, 0.0f, 1.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(0.0f, 1.0f, 1.0f);
  // Back Face
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(0.0f, 1.0f, 0.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 0.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(1.0f, 0.0f, 0.0f);
  // Top Face
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(0.0f, 1.0f, 0.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(0.0f, 1.0f, 1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 0.0f);
  // Bottom Face
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(1.0f, 0.0f, 0.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(1.0f, 0.0f, 1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 1.0f);
  // Right face
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(1.0f, 0.0f, 0.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 0.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(1.0f, 0.0f, 1.0f);
  // Left Face
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 1.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(0.0f, 1.0f, 1.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(0.0f, 1.0f, 0.0f);
  glEnd();
  glPopMatrix();
}

void NonhierBox::walk_gl(bool picking) const
{
  Texture::getInstance()->set_texture(0);
  draw_box(m_pos, m_size);
}

void Sand::walk_gl(bool picking) const
{
  Texture::getInstance()->set_texture(0);
  draw_floor(m_pos, m_size);
}

void Brick::walk_gl(bool picking) const
{
  Texture::getInstance()->set_texture(1);
  draw_box(m_pos, m_size);
}
void Steel::walk_gl(bool picking) const
{
  Texture::getInstance()->set_texture(2);
  draw_box(m_pos, m_size);
}

void Water::walk_gl(bool picking) const
{
  Texture::getInstance()->set_texture(3);
  draw_floor(m_pos, m_size);
}

void Snow::walk_gl(bool picking) const
{
  Texture::getInstance()->set_texture(4);
  draw_floor(m_pos, m_size);
}

void Grass::walk_gl(bool picking) const
{
  Texture::getInstance()->set_texture(5);
  draw_box(m_pos, m_size);
}
