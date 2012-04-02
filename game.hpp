/*
 * game.hpp
 *
 *  Created on: 2012-04-02
 *      Author: sheng
 */

#ifndef GAME_HPP_
#define GAME_HPP_
#include <gtkmm.h>
#include <gtkglmm.h>
#include <sys/time.h>
#include <glibmm.h>

#include "level.hpp"
#include "viewer.hpp"
class Game
{
  public:
    Game(Viewer * viewer, Level * level);
    virtual ~Game();
    void start();

  private:
    Viewer * m_viewer;
    Level * m_level;
    int m_delay_interval;
    int m_critical_interval;
    sigc::connection m_handler;
    int update_frame();
    int check_command();
};

#endif /* GAME_HPP_ */
