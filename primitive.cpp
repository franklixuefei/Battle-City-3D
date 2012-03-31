#include "primitive.hpp"
#include <GL/glu.h>
Primitive::~Primitive()
{
}

Sphere::~Sphere()
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
