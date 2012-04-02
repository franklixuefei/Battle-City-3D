/*
 * level.cpp
 *
 *  Created on: 2012-04-01
 *      Author: sheng
 */

#include "level.hpp"
#include "primitive.hpp"
#include "material.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;
Level::Level(string filename)
{
  ifstream dataIn;
//  if (filename == 0) {
//    filename = "levels/1";
//  }
  dataIn.open(filename.c_str());
  root = new SceneNode("root");
  if (dataIn.fail() == true) {
  } else {
    Material * material = new PhongMaterial(Colour(1.0, 1.0, 1.0),
        Colour(1.0, 1.0, 1.0), 1.0);

    Point3D point = Point3D(0, 0, 0.0);
    Tank * cube = new Tank(point, 1);
    GeometryNode * node = new GeometryNode("tank", cube);
    node->translate(Vector3D(8.0, 24.0, 0.0));
    node->set_material(material);
    root->add_child(node);

    Steel * steel_north = new Steel(point, 1);
    GeometryNode * north_node = new GeometryNode("north", steel_north);
    north_node->translate(Vector3D(0.0, -1.0, 0.0));
    north_node->scale(Vector3D(26.0, 1.0, 1.0));
    north_node->set_material(material);
    root->add_child(north_node);

    Steel * steel_south = new Steel(point, 1);
    GeometryNode * south_node = new GeometryNode("south", steel_south);
    south_node->translate(Vector3D(0.0, 26.0, 0.0));
    south_node->scale(Vector3D(26.0, 1.0, 1.0));
    south_node->set_material(material);
    root->add_child(south_node);

    Steel * steel_west = new Steel(point, 1);
    GeometryNode * west_node = new GeometryNode("west", steel_west);
    west_node->translate(Vector3D(-1.0, 0.0, 0.0));
    west_node->scale(Vector3D(1.0, 26.0, 1.0));
    west_node->set_material(material);
    root->add_child(west_node);

    Steel * steel_east = new Steel(point, 1);
    GeometryNode * east_node = new GeometryNode("east", steel_east);
    east_node->translate(Vector3D(26.0, 0.0, 0.0));
    east_node->scale(Vector3D(1.0, 26.0, 1.0));
    east_node->set_material(material);
    root->add_child(east_node);

    Sand * floor = new Sand(point, 1);
    GeometryNode * floor_node = new GeometryNode("sand", floor);
    floor_node->translate(Vector3D(-50.0, -50.0, 0.01));
    floor_node->scale(Vector3D(126.0, 126.0, 1.0));
    floor_node->set_material(material);
    root->add_child(floor_node);

    for (int y = 0; y < 26; y++) {
      for (int x = 0; x < 26; x++) {
        dataIn >> m_map[x][y];
        if (m_map[x][y] == 1) {
          Point3D point = Point3D(x, y, 0.0);
          Brick * cube = new Brick(point, 1);
          GeometryNode * node = new GeometryNode("brick", cube);
          node->set_material(material);
          root->add_child(node);
          nodes[x][y] = node;
        } else if (m_map[x][y] == 2) {
          Point3D point = Point3D(x, y, 0.0);
          Steel * cube = new Steel(point, 1);
          GeometryNode * node = new GeometryNode("steel", cube);
          node->set_material(material);
          root->add_child(node);
          nodes[x][y] = node;
        } else if (m_map[x][y] == 3) {
          Point3D point = Point3D(x, y, 0.0);
          Water * cube = new Water(point, 1);
          GeometryNode * node = new GeometryNode("water", cube);
          node->set_material(material);
          root->add_child(node);
          nodes[x][y] = node;
        } else if (m_map[x][y] == 4) {
          Point3D point = Point3D(x, y, 0.0);
          Snow * cube = new Snow(point, 1);
          GeometryNode * node = new GeometryNode("snow", cube);
          node->set_material(material);
          root->add_child(node);
          nodes[x][y] = node;
        } else if (m_map[x][y] == 5) {
          Point3D point = Point3D(x, y, 0.0);
          Grass * cube = new Grass(point, 1);
          GeometryNode * node = new GeometryNode("grass", cube);
          node->set_material(material);
          root->add_child(node);
          nodes[x][y] = node;
        } else {
//          Point3D point = Point3D(x, y, 0.0);
//          Sand * cube = new Sand(point, 1);
//          GeometryNode * node = new GeometryNode("sand", cube);
//          node->set_material(material);
//          root->add_child(node);
//          nodes[x][y] = node;
        }
      }
    }
  }
}

Level::~Level()
{
  delete root;
}

SceneNode * Level::get_model()
{
  return root;
}

