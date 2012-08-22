#include "material.hpp"

Material::~Material()
{
}

PhongMaterial::PhongMaterial(const Colour& kd, const Colour& ks,
    double shininess) :
    m_kd(kd), m_ks(ks), m_shininess(shininess)
{
}

PhongMaterial::~PhongMaterial()
{
}

void PhongMaterial::apply_gl() const
{
  // Perform OpenGL calls necessary to set up this material.
  GLfloat diffuse[] = { m_kd.R(), m_kd.G(), m_kd.B(), 1.0 };
  GLfloat mspecular[] = { m_ks.R(), m_ks.G(), m_ks.B(), 1.0 };
  GLfloat shininess[] = { m_shininess, m_shininess, m_shininess, 1.0 };

  glShadeModel(GL_SMOOTH);

  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mspecular);
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}
