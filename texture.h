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

    void load_planet_texture(const std::string& filename, int index);
    void apply_planet_texture(GLUquadric* quadric);

  private:
    Texture();
    static Texture* texture_instance;
    Image m_images[6];
    Image m_normal_map;
    int textureImageWidth;
    int textureImageHeight;
    GLubyte planet_tex_img[256][256][3];
    GLubyte normal_tex_img[256][256][3];
    GLuint texNamePlanet;
    GLuint texNameNormal;
    GLuint normalisationCubeMap;
    void makeCheckImage();
    bool GenerateNormalisationCubeMap();
};

#endif /* TEXTURE_H_ */
