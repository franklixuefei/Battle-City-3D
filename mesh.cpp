#include "mesh.hpp"
#include <iostream>

Mesh::Mesh(const std::vector<Point3D>& verts,
    const std::vector<std::vector<int> >& faces) :
    m_verts(verts), m_faces(faces)
{
  m_box = NULL;
  set_bouding_volume();
}

Mesh::~Mesh()
{
  delete m_box;
}

void Mesh::walk_gl(bool picking) const
{
  //TODO
}

std::ostream& operator<<(std::ostream& out, const Mesh& mesh)
{
  std::cerr << "mesh({";
  for (std::vector<Point3D>::const_iterator I = mesh.m_verts.begin();
      I != mesh.m_verts.end(); ++I) {
    if (I != mesh.m_verts.begin())
      std::cerr << ",\n      ";
    std::cerr << *I;
  }
  std::cerr << "},\n\n     {";

  for (std::vector<Mesh::Face>::const_iterator I = mesh.m_faces.begin();
      I != mesh.m_faces.end(); ++I) {
    if (I != mesh.m_faces.begin())
      std::cerr << ",\n      ";
    std::cerr << "[";
    for (Mesh::Face::const_iterator J = I->begin(); J != I->end(); ++J) {
      if (J != I->begin())
        std::cerr << ", ";
      std::cerr << *J;
    }
    std::cerr << "]";
  }
  std::cerr << "});" << std::endl;
  return out;
}

bool Mesh::verify_same_direction(Mesh::Face current_face, Point3D vertices[],
    Point3D& point, Vector3D& normal)
{
  bool is_same_direction = false;
  // Make sure the intersect face is pointing to the same direction
  for (unsigned int i = 0; i < current_face.size(); i++) {
    is_same_direction =
        ((vertices[(i + 1) % current_face.size()] - vertices[i]).cross(
            point - vertices[i]).dot(normal)) >= 0;
    if (!is_same_direction) {
      break;
    }
  }
  return is_same_direction;
}

void Mesh::set_bouding_volume()
{
  lower_bound = m_verts[0];
  upper_bound = m_verts[0];

  for (std::vector<Point3D>::const_iterator point_pointer = m_verts.begin();
      point_pointer != m_verts.end(); point_pointer++) {
    Point3D point = *point_pointer;
    for (int i = 0; i < 3; i++) {
      lower_bound[i] = std::min(lower_bound[i], point[i]);
      upper_bound[i] = std::max(upper_bound[i], point[i]);
    }
  }

  double x_diff = upper_bound[0] - lower_bound[0];
  double y_diff = upper_bound[1] - lower_bound[1];
  double z_diff = upper_bound[2] - lower_bound[2];
  //Take the maximum of x, y, z difference to be the size.
  double size = std::max(std::max(x_diff, y_diff), z_diff);
  m_box = new NonhierBox(lower_bound, size);
}

/**
 * Half Space test if a point is inside bounding volume
 */
bool Mesh::is_inside_bounding_volume(Point3D point)
{
  for (int i = 0; i < 3; i++) {
    if (point[i] < lower_bound[i] || point[i] > upper_bound[i])
      return false;
  }
  return true;
}
