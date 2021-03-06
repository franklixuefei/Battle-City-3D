#include "viewer.hpp"
#include "algebra.hpp"
#include "texture.hpp"
#include "level.hpp"
#include <iostream>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
std::string filename;
Viewer::Viewer()
{
  Glib::RefPtr<Gdk::GL::Config> glconfig;

  // Ask for an OpenGL Setup with
  //  - red, green and blue component colour
  //  - a depth buffer to avoid things overlapping wrongly
  //  - double-buffered rendering to avoid tearing/flickering
  glconfig = Gdk::GL::Config::create(
      Gdk::GL::MODE_RGB | Gdk::GL::MODE_DEPTH | Gdk::GL::MODE_DOUBLE);
  if (glconfig == 0) {
    // If we can't get this configuration, die
    std::cerr << "Unable to setup OpenGL Configuration!" << std::endl;
    abort();
  }

  // Accept the configuration
  set_gl_capability(glconfig);

  // Register the fact that we want to receive these events
  add_events(
      Gdk::BUTTON1_MOTION_MASK | Gdk::BUTTON2_MOTION_MASK
          | Gdk::BUTTON3_MOTION_MASK | Gdk::BUTTON_PRESS_MASK
          | Gdk::BUTTON_RELEASE_MASK | Gdk::VISIBILITY_NOTIFY_MASK);

  initialize_parameters();
}

void Viewer::initialize_parameters()
{
  //Initialize variables
  m_mode = STRATEGY;
  m_last_x = 0.0;
  m_left = false;
  m_right = false;
  m_middle = false;
  m_z_buffer = false;
  m_backface_cull = false;
  Vector3D vector = Vector3D(-13.0, -13.0, 45.0);
  m_translation = Matrix4x4().translation(vector);
  m_rotation = Matrix4x4().rotation(180.0, 'x');
  m_level = new Level("levels/1");
}

Viewer::~Viewer()
{
  // Nothing to do here right now.
}

void Viewer::invalidate()
{
  // Force a rerender
  Gtk::Allocation allocation = get_allocation();
  get_window()->invalidate_rect(allocation, false);
}

void Viewer::on_realize()
{
  // Do some OpenGL setup.
  // First, let the base class do whatever it needs to
  Gtk::GL::DrawingArea::on_realize();

  Glib::RefPtr<Gdk::GL::Drawable> gldrawable = get_gl_drawable();

  if (!gldrawable)
    return;

  if (!gldrawable->gl_begin(get_gl_context()))
    return;

  glShadeModel(GL_SMOOTH);
  glClearColor(0.4, 0.4, 0.4, 0.0);
  glEnable(GL_DEPTH_TEST);

  gldrawable->gl_end();
}

bool Viewer::on_expose_event(GdkEventExpose* event)
{
  Glib::RefPtr<Gdk::GL::Drawable> gldrawable = get_gl_drawable();

  if (!gldrawable)
    return false;

  if (!gldrawable->gl_begin(get_gl_context()))
    return false;

  // Set up for perspective drawing 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, get_width(), get_height());
  gluPerspective(40.0, (GLfloat) get_width() / (GLfloat) get_height(), 0.1,
      1000.0);

  // change to model view for drawing
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Clear framebuffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (m_z_buffer) {
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
  }

  draw_skybox();
  // Set up lighting
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_position[] = { 13.0, 13.0, 40.0, 1.0 };
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  // Draw stuff
  draw_model();

  // Swap the contents of the front and back buffers so we see what we
  // just drew. This should only be done if double buffering is enabled.
  gldrawable->swap_buffers();

  gldrawable->gl_end();

  return true;
}

bool Viewer::on_configure_event(GdkEventConfigure* event)
{
  Glib::RefPtr<Gdk::GL::Drawable> gldrawable = get_gl_drawable();

  if (!gldrawable)
    return false;

  if (!gldrawable->gl_begin(get_gl_context()))
    return false;

  // Set up perspective projection, using current size and aspect
  // ratio of display

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, event->width, event->height);
  gluPerspective(40.0, (GLfloat) event->width / (GLfloat) event->height, 0.1,
      1000.0);

  // Reset to modelview matrix mode

  glMatrixMode(GL_MODELVIEW);

  gldrawable->gl_end();

  return true;
}

bool Viewer::on_button_press_event(GdkEventButton* event)
{
  m_left = (event->button == (guint) 1);
  m_middle = (event->button == (guint) 2);
  m_right = (event->button == (guint) 3);
  m_last_x = event->x;
  m_last_y = event->y;
  return true;
}

bool Viewer::on_button_release_event(GdkEventButton* event)
{
  m_left = (event->button != (guint) 1);
  m_middle = (event->button != (guint) 2);
  m_right = (event->button != (guint) 3);
  return true;
}

bool Viewer::on_motion_notify_event(GdkEventMotion* event)
{
  guint m_current_x = event->x;
  guint m_current_y = event->y;
  perform_transformation(m_last_x, m_current_x, m_last_y, m_current_y);
  m_last_x = m_current_x;
  m_last_y = m_current_y;
  return true;
}

void Viewer::draw_model(bool is_picking)
{
  Matrix4x4 m_world_matrix = m_rotation * m_translation;
  Matrix4x4 m_world_matrix_invert = m_world_matrix.invert();
  SceneNode * level = m_level->get_model();
  level->set_transform(level->get_transform() * m_world_matrix);
  level->walk_gl(is_picking);
  level->set_transform(level->get_transform() * m_world_matrix_invert);
}

void Viewer::draw_skybox()
{
  Texture::getInstance()->set_texture(3);
  glPushMatrix();
  glScalef(100, 100, 100);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glEnd();
  glPopMatrix();
}

void Viewer::reset_position()
{
  m_translation = Matrix4x4();
  invalidate();
}

void Viewer::reset_orientation()
{
  m_rotation = Matrix4x4();
  invalidate();
}

void Viewer::reset_all()
{
  m_translation = Matrix4x4();
  m_rotation = Matrix4x4();
  invalidate();
}

void Viewer::set_mode(mode_t mode)
{
  m_mode = mode;
}

void Viewer::set_level(int level)
{
  delete m_level;
  if (level == 2) {
    m_level = new Level("levels/2");
  } else {
    m_level = new Level("levels/1");
  }
  invalidate();
}
void Viewer::toggle_z_buffer()
{
  m_z_buffer = !m_z_buffer;
  invalidate();
}

void Viewer::toggle_backface_cull()
{
  m_backface_cull = !m_backface_cull;
  invalidate();
}

void Viewer::perform_transformation(float fOldX, float fNewX, float fOldY,
    float fNewY)
{
  Matrix4x4 mNewMat;
  int current_width = get_width();
  int current_height = get_height();

  if (m_right) {
    float fRotVecX, fRotVecY, fRotVecZ;
    float fDiameter =
        current_width < current_height ?
            (float) current_width * 0.5 : (float) current_height * 0.5;

    int iCenterX = current_width / 2;
    int iCenterY = current_height / 2;
    float fOldModX = fOldX - iCenterX;
    float fOldModY = fOldY - iCenterY;
    float fNewModX = fNewX - iCenterX;
    float fNewModY = fNewY - iCenterY;

    vCalcRotVec(fNewModX, fNewModY, fOldModX, fOldModY, fDiameter, &fRotVecX,
        &fRotVecY, &fRotVecZ);
    vAxisRotMatrix(fRotVecX, -fRotVecY, fRotVecZ, &mNewMat);
    m_rotation = m_rotation * mNewMat;
  }

  if (m_left) {
    m_translation = mNewMat.translation(
        Vector3D((fNewX - fOldX) / 22.0, -(fNewY - fOldY) / 22.0, 0.0))
        * m_translation;
  }

  if (m_middle) {
    m_translation = mNewMat.translation(
        Vector3D(0.0, 0.0, (fNewY - fOldY) / 22.0)) * m_translation;
  }

  invalidate();
}

void Viewer::perform_joint_rotation(float fOldX, float fNewX, float fOldY,
    float fNewY)
{
  for (std::list<SceneNode*>::const_iterator element_ptr =
      selected_joint_nodes.begin(); element_ptr != selected_joint_nodes.end();
      element_ptr++) {

    SceneNode * node = *element_ptr;
    if (node->is_joint()) {
      JointNode * joint_node = (JointNode *) node;
      if (node->get_name() == "headJoint") {
        if (m_right)
          joint_node->rotate_by(fNewX - fOldX, true);
        if (m_middle)
          joint_node->rotate_by(fNewY - fOldY, false);
      } else if (m_middle) {
        joint_node->rotate_by(fNewY - fOldY, true);
        joint_node->rotate_by(fNewY - fOldY, false);
      }
    }
  }
  invalidate();
}

void Viewer::vCalcRotVec(float fNewX, float fNewY, float fOldX, float fOldY,
    float fDiameter, float *fVecX, float *fVecY, float *fVecZ)
{
  float fNewVecX, fNewVecY, fNewVecZ, /* Vector corresponding to new mouse location */
  fOldVecX, fOldVecY, fOldVecZ, /* Vector corresponding to old mouse location */
  fLength;

  fNewVecX = fNewX * 2.0 / fDiameter;
  fNewVecY = fNewY * 2.0 / fDiameter;
  fNewVecZ = (1.0 - fNewVecX * fNewVecX - fNewVecY * fNewVecY);

  if (fNewVecZ < 0.0) {
    fLength = sqrt(1.0 - fNewVecZ);
    fNewVecZ = 0.0;
    fNewVecX /= fLength;
    fNewVecY /= fLength;
  } else {
    fNewVecZ = sqrt(fNewVecZ);
  }

  fOldVecX = fOldX * 2.0 / fDiameter;
  fOldVecY = fOldY * 2.0 / fDiameter;
  fOldVecZ = (1.0 - fOldVecX * fOldVecX - fOldVecY * fOldVecY);

  if (fOldVecZ < 0.0) {
    fLength = sqrt(1.0 - fOldVecZ);
    fOldVecZ = 0.0;
    fOldVecX /= fLength;
    fOldVecY /= fLength;
  } else {
    fOldVecZ = sqrt(fOldVecZ);
  }

  *fVecX = fOldVecY * fNewVecZ - fNewVecY * fOldVecZ;
  *fVecY = fOldVecZ * fNewVecX - fNewVecZ * fOldVecX;
  *fVecZ = fOldVecX * fNewVecY - fNewVecX * fOldVecY;
}

void Viewer::vAxisRotMatrix(float fVecX, float fVecY, float fVecZ,
    Matrix4x4* mNewMat)
{
  float fRadians, fInvLength, fNewVecX, fNewVecY, fNewVecZ;

  fRadians = sqrt(fVecX * fVecX + fVecY * fVecY + fVecZ * fVecZ);

  if (fRadians > -0.000001 && fRadians < 0.000001) {
    *mNewMat = Matrix4x4();
    return;
  }

  fInvLength = 1 / fRadians;
  fNewVecX = fVecX * fInvLength;
  fNewVecY = fVecY * fInvLength;
  fNewVecZ = fVecZ * fInvLength;

  double dSinAlpha = sin(fRadians);
  double dCosAlpha = cos(fRadians);
  double dT = 1 - dCosAlpha;

  Matrix4x4 rotation = Matrix4x4();
  rotation[0][0] = dCosAlpha + fNewVecX * fNewVecX * dT;
  rotation[0][1] = fNewVecX * fNewVecY * dT + fNewVecZ * dSinAlpha;
  rotation[0][2] = fNewVecX * fNewVecZ * dT - fNewVecY * dSinAlpha;

  rotation[1][0] = fNewVecX * fNewVecY * dT - dSinAlpha * fNewVecZ;
  rotation[1][1] = dCosAlpha + fNewVecY * fNewVecY * dT;
  rotation[1][2] = fNewVecY * fNewVecZ * dT + dSinAlpha * fNewVecX;

  rotation[2][0] = fNewVecZ * fNewVecX * dT + dSinAlpha * fNewVecY;
  rotation[2][1] = fNewVecZ * fNewVecY * dT - dSinAlpha * fNewVecX;
  rotation[2][2] = dCosAlpha + fNewVecZ * fNewVecZ * dT;

  *mNewMat = Matrix4x4(rotation);
}
