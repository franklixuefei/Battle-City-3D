#include "scene.hpp"
#include <iostream>
#include "algebra.hpp"

static int m_counter = 0;

SceneNode::SceneNode(const std::string& name) :
    m_id(m_counter++), m_name(name)
{
  m_trans = Matrix4x4();
  m_invtrans = Matrix4x4();
  parent_joint = 0;
  m_selected = false;
  m_head = (m_name == "head");
}

SceneNode::~SceneNode()
{
}

void SceneNode::walk_gl(bool picking) const
{
  for (ChildList::const_iterator element_ptr = m_children.begin();
      element_ptr != m_children.end(); element_ptr++) {
    SceneNode * node = *element_ptr;
    node->set_transform(m_trans * node->get_transform());
    node->walk_gl(picking);
    node->set_transform(m_invtrans * node->get_transform());
  }
}

void SceneNode::rotate(char axis, double angle)
{
  set_transform(m_trans * Matrix4x4::rotation(angle, axis));
}

void SceneNode::scale(const Vector3D& amount)
{
  set_transform(m_trans * Matrix4x4::scaling(amount));
}

void SceneNode::translate(const Vector3D& amount)
{
  set_transform(m_trans * Matrix4x4::translation(amount));
}

bool SceneNode::is_joint() const
{
  return false;
}

JointNode::JointNode(const std::string& name) :
    SceneNode(name)
{
  m_rotate_x = 0.0;
  m_rotate_y = 0.0;
}

JointNode::~JointNode()
{
}

void JointNode::walk_gl(bool picking) const
{
  for (ChildList::const_iterator element_ptr = m_children.begin();
      element_ptr != m_children.end(); element_ptr++) {
    SceneNode * node = *element_ptr;
    node->set_transform(m_trans * node->get_transform());
    node->walk_gl(picking);
    node->set_transform(m_invtrans * node->get_transform());
  }
}

bool JointNode::is_joint() const
{
  return true;
}

void JointNode::set_joint_x(double min, double init, double max)
{
  m_joint_x.min = min;
  m_joint_x.init = init;
  m_joint_x.max = max;
  m_rotate_x = init;
  rotate('z', m_rotate_x);
}

void JointNode::set_joint_y(double min, double init, double max)
{
  m_joint_y.min = min;
  m_joint_y.init = init;
  m_joint_y.max = max;
  m_rotate_y = init;
  rotate('y', m_rotate_y);
}

void JointNode::rotate_by(float angle, bool x_axis)
{
  if (x_axis) {
    m_rotate_x += angle;
    if (m_rotate_x > m_joint_x.max)
      m_rotate_x = m_joint_x.max;
    if (m_rotate_x < m_joint_x.min)
      m_rotate_x = m_joint_x.min;
    set_transform(Matrix4x4::rotation(m_rotate_x, 'z') * Matrix4x4::rotation(m_rotate_y, 'y'));
  }
  else {
    m_rotate_y += angle;
    if (m_rotate_y > m_joint_y.max)
      m_rotate_y = m_joint_y.max;
    if (m_rotate_y < m_joint_y.min)
      m_rotate_y = m_joint_y.min;
    set_transform(Matrix4x4::rotation(m_rotate_x, 'z') * Matrix4x4::rotation(m_rotate_y, 'y'));
  }
}

GeometryNode::GeometryNode(const std::string& name, Primitive* primitive) :
    SceneNode(name), m_primitive(primitive)
{
}

GeometryNode::~GeometryNode()
{
}

void GeometryNode::walk_gl(bool picking) const
{
  glPushMatrix();

  glMultMatrixd(m_trans.transpose().begin());
  if (m_selected) {
    Material * m_selected_material = new PhongMaterial(Colour(1.0, 0.0, 0.0),
        Colour(0.1, 0.1, 0.1), 0.5);
    m_selected_material->apply_gl();
  } else {
    m_material->apply_gl();
  }
  glPushName(m_id);
  m_primitive->walk_gl(picking);
  glPopName();
  glPopMatrix();
}

