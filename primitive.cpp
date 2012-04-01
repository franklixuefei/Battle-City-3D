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

void NonhierBox::walk_gl(bool picking) const
{
  Texture::getInstance()->set_texture(0);
  glPushMatrix();
  glScalef(m_size, m_size, m_size);
  glTranslatef(m_pos[0], m_pos[1], m_pos[2]);
  glBegin(GL_QUADS);
  // Front Face
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);  // Top Right Of The Texture and Quad
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Left Of The Texture and Quad
  // Back Face
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Right Of The Texture and Quad
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
  // Top Face
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);  // Top Right Of The Texture and Quad
  // Bottom Face
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);  // Top Right Of The Texture and Quad
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);  // Top Left Of The Texture and Quad
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
  // Right face
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);  // Top Right Of The Texture and Quad
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);  // Top Left Of The Texture and Quad
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
  // Left Face
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Right Of The Texture and Quad
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
  glEnd();
  glPopMatrix();
}
