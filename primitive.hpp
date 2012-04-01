#ifndef CS488_PRIMITIVE_HPP
#define CS488_PRIMITIVE_HPP

#include "algebra.hpp"

class Primitive {
public:
  virtual ~Primitive();
  virtual void walk_gl(bool picking) const = 0;
};

class NonhierSphere : public Primitive
{
  public:
    NonhierSphere(const Point3D& pos, double radius) :
        m_pos(pos), m_radius(radius)
    {
    }
    virtual ~NonhierSphere();
    virtual void walk_gl(bool picking) const;
  private:
    Point3D m_pos;
    double m_radius;
};

class NonhierBox : public Primitive
{
  public:
    NonhierBox(const Point3D& pos, double size) :
        m_pos(pos), m_size(size)
    {
    }

    virtual ~NonhierBox();
    virtual void walk_gl(bool picking) const;
  private:
    Point3D m_pos;
    double m_size;
};

class Sphere : public Primitive
{
  public:
    Sphere();
    virtual ~Sphere();
    virtual void walk_gl(bool picking) const;
  private:
    NonhierSphere * m_sphere;
};

class Cube : public Primitive
{
  public:
    Cube();
    virtual ~Cube();
    virtual void walk_gl(bool picking) const;
  private:
    NonhierBox * m_box;
};
#endif
