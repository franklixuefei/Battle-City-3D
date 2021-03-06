#include "appwindow.hpp"

AppWindow::AppWindow()
{
  set_title("Battle City 3D");

  // A utility class for constructing things that go into menus, which
  // we'll set up next.
  using Gtk::Menu_Helpers::MenuElem;
  using Gtk::Menu_Helpers::SeparatorElem;
  using Gtk::Menu_Helpers::RadioMenuElem;
  using Gtk::Menu_Helpers::CheckMenuElem;

  // Set up the application menu
  // The slot we use here just causes AppWindow::hide() on this,
  // which shuts down the application.

  m_menu_app.items().push_back(
      MenuElem("_New Game", Gtk::AccelKey("n"),
          sigc::mem_fun(m_viewer, &Viewer::reset_position)));
  m_menu_app.items().push_back(
      MenuElem("_Reset Game", Gtk::AccelKey("r"),
          sigc::mem_fun(m_viewer, &Viewer::reset_all)));
  m_menu_mode.items().push_back(SeparatorElem());
  m_menu_app.items().push_back(
      MenuElem("_Quit", Gtk::AccelKey("q"),
          sigc::mem_fun(*this, &AppWindow::hide)));

  sigc::slot1<void, Viewer::mode_t> mode_slot = sigc::mem_fun(m_viewer,
      &Viewer::set_mode);
  Gtk::RadioButtonGroup m_radiobuttongroup_mode;
  m_menu_mode.items().push_back(
      RadioMenuElem(m_radiobuttongroup_mode, "_Strategy Mode",
          Gtk::AccelKey("1"),
          sigc::bind(mode_slot, Viewer::STRATEGY)));
  m_menu_mode.items().push_back(
      RadioMenuElem(m_radiobuttongroup_mode, "_Following Mode",
          Gtk::AccelKey("2"), sigc::bind(mode_slot, Viewer::FOLLOWING)));
  m_menu_mode.items().push_back(
      RadioMenuElem(m_radiobuttongroup_mode, "_Ground Mode", Gtk::AccelKey("3"),
          sigc::bind(mode_slot, Viewer::GROUND)));

  Gtk::RadioButtonGroup m_radiobuttongroup_level;
  sigc::slot1<void, int> level_slot = sigc::mem_fun(m_viewer,
        &Viewer::set_level);
  m_menu_levels.items().push_back(
      RadioMenuElem(m_radiobuttongroup_level, "Level 1",
          sigc::bind(level_slot, 1)));
  m_menu_levels.items().push_back(
      RadioMenuElem(m_radiobuttongroup_level, "Level 2",
          sigc::bind(level_slot, 2)));

  // Set up the menu bar
  m_menubar.items().push_back(
      Gtk::Menu_Helpers::MenuElem("_Application", m_menu_app));
  m_menubar.items().push_back(
      Gtk::Menu_Helpers::MenuElem("_Mode", m_menu_mode));
  m_menubar.items().push_back(
      Gtk::Menu_Helpers::MenuElem("_Levels", m_menu_levels));

  // Pack in our widgets

  // First add the vertical box as our single "top" widget
  add(m_vbox);

  // Put the menubar on the top, and make it as small as possible
  m_vbox.pack_start(m_menubar, Gtk::PACK_SHRINK);

  // Put the viewer below the menubar. pack_start "grows" the widget
  // by default, so it'll take up the rest of the window.
  m_viewer.set_size_request(500, 500);
  m_vbox.pack_start(m_viewer);

  show_all();
}
