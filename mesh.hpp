#ifndef CS488_MESH_HPP
#define CS488_MESH_HPP

#include <vector>
#include <iosfwd>
#include "primitive.hpp"
#include "algebra.hpp"

// A polygonal mesh.
class Mesh : public Primitive
{
  public:
    Mesh(const std::vector<Point3D>& verts,
        const std::vector<std::vector<int> >& faces);
    ~Mesh();
    virtual void walk_gl(bool picking) const;
    typedef std::vector<int> Face;
  private:
    std::vector<Point3D> m_verts;
    std::vector<Face> m_faces;
    static const double MAX_DOUBLE = 1.79769e+308;
    NonhierBox* m_box;
    Point3D lower_bound;
    Point3D upper_bound;
    bool verify_same_direction(Mesh::Face current_face, Point3D vertices[],
        Point3D& point, Vector3D& normal);
    friend std::ostream& operator<<(std::ostream& out, const Mesh& mesh);
    void set_bouding_volume();
    bool is_inside_bounding_volume(Point3D point);
};

#endif
