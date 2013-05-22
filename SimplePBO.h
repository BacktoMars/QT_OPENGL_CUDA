/******************************************************************************
** Class SimplePBO for encapsulating pixel buffer and texturing.
*******************************************************************************/
#ifndef __SIMPLEPBO_H
#define __SIMPLEPBO_H

#include <qglbuffer.h>
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>

#include "global.h"

/**
 * SimplePBO encapsulates pixel buffer object and 2d texturing.
 * It runs cuda and launches the kernel as well.
 * Reference: http://drdobbs.com/cpp/222600097
 * (took source and adapted it to this class)
 */
class SimplePBO
{
  public:
    SimplePBO(void);
    ~SimplePBO(void);

    void initCuda();
    void resize(int w, int h);
    void bind();
    void release();
    void runCuda(int time);
    void cleanupCuda();

  private:
    void createPBO();
    void deletePBO();
    void createTexture();
    void deleteTexture();

  private:
    unsigned int image_width;
    unsigned int image_height;
    QGLBuffer*   pixelBuffer;
    GLuint*      textureID;
};

#endif
