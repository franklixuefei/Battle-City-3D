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
    for (int y = 25; y >= 0; y--) {
      for (int x = 0; x < 26; x++) {
        dataIn >> m_map[x][y];
        if (m_map[x][y] != 0) {
          if (m_map[x][y] == 1) {
            Point3D point = Point3D(x * 1.0, y * 1.0, 1.0);
            NonhierBox * cube = new NonhierBox(point, 1);
            GeometryNode * node = new GeometryNode("brick", cube);
            node->set_material(material);
            root->add_child(node);
          }
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

