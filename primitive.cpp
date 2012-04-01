#include "primitive.hpp"
#include <GL/glu.h>
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
  GLUquadric* quadric = gluNewQuadric();

  gluQuadricNormals(quadric, GLU_SMOOTH);
  gluQuadricTexture(quadric, GL_TRUE);
  gluQuadricDrawStyle(quadric, GLU_FILL);

  gluSphere(quadric, 1.0, 45, 90);
}

void Cube::walk_gl(bool picking) const
{
  //TODO
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
  //TODO
}
