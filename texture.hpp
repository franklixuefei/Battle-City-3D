#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "algebra.hpp"
#include "image.hpp"

class Texture
{
  public:
    static Texture* getInstance();
    virtual ~Texture();
    void end_tex_map();

    void load_textures();
    void set_texture(int index);

  private:
    Texture();
    static Texture* texture_instance;
    Image m_images[6];
    Image m_normal_map;
    int width;
    int height;
    GLubyte m_int_images[6][256][256][3];
    GLubyte normal_tex_img[256][256][3];
    GLuint textures[6];
    GLuint texNameNormal;
    GLuint normalisationCubeMap;
    void makeCheckImage();
};

#endif /* TEXTURE_H_ */
