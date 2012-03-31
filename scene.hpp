#ifndef SCENE_HPP
#define SCENE_HPP

#include <list>
#include "algebra.hpp"
#include "primitive.hpp"
#include "material.hpp"

class SceneNode
{
  public:
    SceneNode(const std::string& name);
    virtual ~SceneNode();

    virtual void walk_gl(bool picking = false) const;

    const Matrix4x4& get_transform() const
    {
      return m_trans;
    }
    const Matrix4x4& get_inverse() const
    {
      return m_invtrans;
    }

    void set_transform(const Matrix4x4& m)
    {
      m_trans = m;
      m_invtrans = m.invert();
    }

    void set_transform(const Matrix4x4& m, const Matrix4x4& i)
    {
      m_trans = m;
      m_invtrans = i;
    }

    void add_child(SceneNode* child)
    {
      m_children.push_back(child);
    }

    void remove_child(SceneNode* child)
    {
      m_children.remove(child);
    }

    SceneNode * get_node_by_id(int id)
    {
      if (id == m_id)
        return this;
      else {
        for (ChildList::const_iterator element_ptr = m_children.begin();
            element_ptr != m_children.end(); element_ptr++) {
          SceneNode * node = *element_ptr;
          if (node->m_id == id)
            return node;
          SceneNode * return_node = node->get_node_by_id(id);
          if (return_node != 0)
            return return_node;
        }
        return 0;
      }
    }

    std::string get_name()
    {
      return m_name;
    }

    bool toggle_selected()
    {
      m_selected = !m_selected;
      return m_selected;
    }

    virtual void reset()
    {
      m_selected = false;
      for (ChildList::const_iterator element_ptr = m_children.begin();
          element_ptr != m_children.end(); element_ptr++) {
        SceneNode * node = *element_ptr;
        node->reset();
      }
    }

    // Callbacks to be implemented.
    // These will be called from Lua.
    void rotate(char axis, double angle);
    void scale(const Vector3D& amount);
    void translate(const Vector3D& amount);

    // Returns true if and only if this node is a JointNode
    virtual bool is_joint() const;
    virtual SceneNode * get_parentNode()
    {
      return 0;
    }

    void set_parentNode(SceneNode *parent_node)
    {
      if (parent_node->is_joint())
        parent_joint = parent_node;
      for (ChildList::const_iterator element_ptr = m_children.begin();
          element_ptr != m_children.end(); element_ptr++) {
        SceneNode * node = *element_ptr;
        node->set_parentNode(this);
      }
    }

  protected:
    // Useful for picking
    int m_id;
    SceneNode * parent_joint;
    std::string m_name;
    bool m_selected;
    bool m_head;

    // Transformations
    Matrix4x4 m_trans;
    Matrix4x4 m_invtrans;

    // Hierarchy
    typedef std::list<SceneNode*> ChildList;
    ChildList m_children;
};

class JointNode : public SceneNode
{
  public:
    JointNode(const std::string& name);
    virtual ~JointNode();

    virtual void walk_gl(bool picking = false) const;

    virtual bool is_joint() const;

    void set_joint_x(double min, double init, double max);
    void set_joint_y(double min, double init, double max);
    void rotate_by(float angle, bool x_axis);

    struct JointRange
    {
        double min, init, max;
    };

    virtual void reset()
    {
      m_selected = false;
      m_rotate_x = m_joint_x.init;
      m_rotate_y = m_joint_y.init;
      set_transform(Matrix4x4::rotation(m_rotate_x, 'z') * Matrix4x4::rotation(m_rotate_y, 'y'));
      for (ChildList::const_iterator element_ptr = m_children.begin();
          element_ptr != m_children.end(); element_ptr++) {
        SceneNode * node = *element_ptr;
        node->reset();
      }
    }

  protected:
    JointRange m_joint_x, m_joint_y;
    double m_rotate_x;
    double m_rotate_y;
};

class GeometryNode : public SceneNode
{
  public:
    GeometryNode(const std::string& name, Primitive* primitive);
    virtual ~GeometryNode();

    virtual void walk_gl(bool picking = false) const;

    const Material* get_material() const;
    Material* get_material();

    void set_material(Material* material)
    {
      m_material = material;
    }

    virtual SceneNode * get_parentNode()
    {
      return parent_joint;
    }

  protected:
    Material* m_material;
    Primitive* m_primitive;
};

#endif
