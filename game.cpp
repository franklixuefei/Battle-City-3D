/*
 * game.cpp
 *
 *  Created on: 2012-04-02
 *      Author: sheng
 */

#include "game.hpp"

Game::Game(Viewer * viewer, Level * level) :
    m_viewer(viewer), m_level(level), m_delay_interval(100), m_critical_interval(
        1000)
{
}

void Game::start()
{
  m_handler = Glib::signal_timeout().connect(
      sigc::mem_fun(*this, &Game::update_frame), m_delay_interval);
  m_handler = Glib::signal_timeout().connect(
      sigc::mem_fun(*this, &Game::check_command), m_critical_interval);
}
Game::~Game()
{
}

int Game::update_frame()
{
  //TODO
  return 0;
}

int Game::check_command()
{
  //TODO
  return 0;
}
