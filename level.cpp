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
    for (int y = 0; y < 26; y++) {
      for (int x = 0; x < 26; x++) {
        dataIn >> m_map[x][y];
        if (m_map[x][y] == 1) {
          Point3D point = Point3D(x, y, 0.0);
          Brick * cube = new Brick(point, 1);
          GeometryNode * node = new GeometryNode("brick", cube);
          node->set_material(material);
          root->add_child(node);
        } else if (m_map[x][y] == 2) {
          Point3D point = Point3D(x, y, 0.0);
          Steel * cube = new Steel(point, 1);
          GeometryNode * node = new GeometryNode("steel", cube);
          node->set_material(material);
          root->add_child(node);
        }  else if (m_map[x][y] == 3) {
          Point3D point = Point3D(x, y, 0.0);
          Water * cube = new Water(point, 1);
          GeometryNode * node = new GeometryNode("water", cube);
          node->set_material(material);
          root->add_child(node);
        }  else if (m_map[x][y] == 4) {
          Point3D point = Point3D(x, y, 0.0);
          Snow * cube = new Snow(point, 1);
          GeometryNode * node = new GeometryNode("snow", cube);
          node->set_material(material);
          root->add_child(node);
        }  else if (m_map[x][y] == 5) {
          Point3D point = Point3D(x, y, 0.0);
          Grass * cube = new Grass(point, 1);
          GeometryNode * node = new GeometryNode("grass", cube);
          node->set_material(material);
          root->add_child(node);
        } else {
          Point3D point = Point3D(x, y, 0.0);
          Sand * cube = new Sand(point, 1);
          GeometryNode * node = new GeometryNode("sand", cube);
          node->set_material(material);
          root->add_child(node);
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

