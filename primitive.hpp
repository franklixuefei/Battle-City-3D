#ifndef CS488_PRIMITIVE_HPP
#define CS488_PRIMITIVE_HPP

#include "algebra.hpp"

class Primitive
{
  public:
    virtual ~Primitive();
    virtual void walk_gl(bool picking) const = 0;
  protected:
    void draw_box(Point3D m_pos, double m_size) const;
    void draw_floor(Point3D m_pos, double m_size) const;
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

class Brick : public Primitive
{
  public:
    Brick(const Point3D& pos, double size) :
        m_pos(pos), m_size(size)
    {
    }

    virtual ~Brick()
    {
    }
    virtual void walk_gl(bool picking) const;
  private:
    Point3D m_pos;
    double m_size;
};

class Steel : public Primitive
{
  public:
    Steel(const Point3D& pos, double size) :
        m_pos(pos), m_size(size)
    {
    }

    virtual ~Steel()
    {
    }
    virtual void walk_gl(bool picking) const;
  private:
    Point3D m_pos;
    double m_size;
};

class Sand : public Primitive
{
  public:
    Sand(const Point3D& pos, double size) :
        m_pos(pos), m_size(size)
    {
    }

    virtual ~Sand()
    {
    }
    virtual void walk_gl(bool picking) const;
  private:
    Point3D m_pos;
    double m_size;
};

class Water : public Primitive
{
  public:
    Water(const Point3D& pos, double size) :
        m_pos(pos), m_size(size)
    {
    }

    virtual ~Water()
    {
    }
    virtual void walk_gl(bool picking) const;
  private:
    Point3D m_pos;
    double m_size;
};

class Snow : public Primitive
{
  public:
    Snow(const Point3D& pos, double size) :
        m_pos(pos), m_size(size)
    {
    }

    virtual ~Snow()
    {
    }
    virtual void walk_gl(bool picking) const;
  private:
    Point3D m_pos;
    double m_size;
};

class Grass : public Primitive
{
  public:
    Grass(const Point3D& pos, double size) :
        m_pos(pos), m_size(size)
    {
    }

    virtual ~Grass()
    {
    }
    virtual void walk_gl(bool picking) const;
  private:
    Point3D m_pos;
    double m_size;
};

class Tank : public Primitive
{
  public:
    Tank(const Point3D& pos, double size) :
        m_pos(pos), m_size(size)
    {
    }

    virtual ~Tank()
    {
    }
    virtual void walk_gl(bool picking) const;
  private:
    Point3D m_pos;
    double m_size;
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
