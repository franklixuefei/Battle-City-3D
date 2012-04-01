#ifndef CS488_VIEWER_HPP
#define CS488_VIEWER_HPP

#include <gtkmm.h>
#include <gtkglmm.h>
#include "scene.hpp"
#include "scene_lua.hpp"
extern std::string filename;
// The "main" OpenGL widget
class Viewer : public Gtk::GL::DrawingArea
{

  public:
    enum mode_t
    {
      POSITION_ORIENTATION, JOINTS
    };

    Viewer();
    virtual ~Viewer();

    // A useful function that forces this widget to rerender. If you
    // want to render a new frame, do not call on_expose_event
    // directly. Instead call this, which will cause an on_expose_event
    // call when the time is right.
    void invalidate();
    void reset_position();
    void reset_orientation();
    void reset_joints();
    void reset_all();
    void set_mode(mode_t mode);
    void toggle_z_buffer();
  protected:

    // Events we implement
    // Note that we could use gtkmm's "signals and slots" mechanism
    // instead, but for many classes there's a convenient member
    // function one just needs to define that'll be called with the
    // event.

    // Called when GL is first initialized
    virtual void on_realize();
    // Called when our window needs to be redrawn
    virtual bool on_expose_event(GdkEventExpose* event);
    // Called when the window is resized
    virtual bool on_configure_event(GdkEventConfigure* event);
    // Called when a mouse button is pressed
    virtual bool on_button_press_event(GdkEventButton* event);
    // Called when a mouse button is released
    virtual bool on_button_release_event(GdkEventButton* event);
    // Called when the mouse moves
    virtual bool on_motion_notify_event(GdkEventMotion* event);

    // Draw a circle for the trackball, with OpenGL commands.
    // Assumes the context for the viewer is active.
    void draw_trackball_circle();
    void draw_model(bool is_picking = false);
    void draw_board();

  private:
//    SceneNode* model;
    std::list<SceneNode*> selected_joint_nodes;
    mode_t m_mode;
    gdouble m_last_x;
    gdouble m_last_y;
    bool m_left;
    bool m_right;
    bool m_middle;
    bool m_circle;
    bool m_z_buffer;
    bool m_backface_cull;
    bool m_frontface_cull;
    Matrix4x4 m_translation;
    Matrix4x4 m_rotation;
    GLuint m_texture[5];
    GLuint select_buffer[100];
    void initialize_parameters();
    void perform_transformation(float fOldX, float fNewX, float fOldY,
        float fNewY);
    void vCalcRotVec(float fNewX, float fNewY, float fOldX, float fOldY,
        float fDiameter, float *fVecX, float *fVecY, float *fVecZ);
    void vAxisRotMatrix(float fVecX, float fVecY, float fVecZ,
        Matrix4x4* mNewMat);
    void perform_joint_rotation(float fOldX, float fNewX, float fOldY,
        float fNewY);
    void draw_texture_cube();
};

#endif
