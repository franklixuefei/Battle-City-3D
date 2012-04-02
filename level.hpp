/*
 * level.hpp
 *
 *  Created on: 2012-04-01
 *      Author: sheng
 */

#ifndef LEVEL_HPP_
#define LEVEL_HPP_

#include "scene.hpp"
#include <string>
class Level
{
  public:
    Level(std::string filename);
    virtual ~Level();
    SceneNode * get_model();
  private:
    int m_map[26][26];
    SceneNode * nodes[26][26];
    SceneNode * root;
};

#endif /* LEVEL_HPP_ */
