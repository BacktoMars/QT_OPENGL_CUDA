#include "SimplePBO.h"

#include <cuda_runtime_api.h>

#ifndef GL_BGRA
#define GL_BGRA 0x80E1
#endif

//extern "C" void launch_Mandelbrot_kernel(uchar4* ptr, int width, int height, int time);

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
SimplePBO::SimplePBO(void)
  : pixelBuffer(0), textureID(0)
{
  image_width  = 512;
  image_height = 512;
}
//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
SimplePBO::~SimplePBO(void)
{
  cleanupCuda();
}
//-----------------------------------------------------------------------------
// initCuda
//-----------------------------------------------------------------------------
void SimplePBO::initCuda(){
  HANDLE_ERROR( cudaGLSetGLDevice(0) );
}
//-----------------------------------------------------------------------------
// resize
//-----------------------------------------------------------------------------
void SimplePBO::resize(int w, int h)
{
  // sizes must be a multiple of 16
  image_width = w+16-(w%16); 
  image_height = h+16-(h%16);

  printf("image width = %d height = %d\n", image_width, image_height);
  // delete pixelBuffer and textures if they already exist
  deletePBO();
  deleteTexture();
  // create pixel buffer object and register to cude
  createPBO();
  // create and allocate 2d texture buffer
  createTexture();
  // deactive pixelbuffer and texture object
  release();
}
//-----------------------------------------------------------------------------
// runCuda -  Run the Cuda part of the computation
//-----------------------------------------------------------------------------
void SimplePBO::runCuda(int time)
{
  uchar4 *dptr=NULL;

  Q_ASSERT(pixelBuffer);

  // map OpenGL buffer object for writing from CUDA 
  // on a single GPU no data is moved (Win & Linux). 
  // When mapped to CUDA, OpenGL should not use this buffer
  HANDLE_ERROR( cudaGLMapBufferObject((void**)&dptr, pixelBuffer->bufferId()) );
  Q_ASSERT(dptr);
  // execute the kernel
  launch_Mandelbrot_kernel(dptr, image_width, image_height);

  // unmap buffer object
  HANDLE_ERROR( cudaGLUnmapBufferObject(pixelBuffer->bufferId()) );
}
//-----------------------------------------------------------------------------
// createPBO
//-----------------------------------------------------------------------------
void SimplePBO::createPBO()
{
  // set up vertex data parameter
  int size_tex_data = sizeof(GLubyte) * image_width * image_height * 4;

  if(!pixelBuffer)
  {
    pixelBuffer = new QGLBuffer(QGLBuffer::PixelUnpackBuffer);
    /*
      FROM Qt Doc:
          The data will be modified repeatedly and used
          many times for reading data back from the GL server for
          use in further drawing operations.
    */
    pixelBuffer->setUsagePattern(QGLBuffer::DynamicCopy);
    pixelBuffer->create();
  }
  pixelBuffer->bind();
  pixelBuffer->allocate(size_tex_data);

  HANDLE_ERROR( cudaGLRegisterBufferObject( pixelBuffer->bufferId() ) );
}
//-----------------------------------------------------------------------------
// deletePBO
//-----------------------------------------------------------------------------
void SimplePBO::deletePBO()
{
  if (pixelBuffer) {
    // unregister this buffer object with CUDA
    HANDLE_ERROR( cudaGLUnregisterBufferObject(pixelBuffer->bufferId()) );

    delete pixelBuffer;
    pixelBuffer = 0;
  }
}
//-----------------------------------------------------------------------------
// createTexture
//-----------------------------------------------------------------------------
void SimplePBO::createTexture()
{
  // delete texture object if necessary
  //  for reallocating tex mem, e.g. at different size
  deleteTexture();

  // Generate a texture identifier
  textureID = new GLuint[1]; // increase if u need more
  glGenTextures(1, textureID);
  
  // Make this the current texture (remember that GL is state-based)
  glBindTexture( GL_TEXTURE_2D, textureID[0]);

  // Allocate the texture memory. The last parameter is NULL since we only
  // want to allocate memory, not initialize it
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, image_width, image_height, 0,
 			GL_BGRA,GL_UNSIGNED_BYTE, NULL);

  // Must set the filter mode, GL_LINEAR enables interpolation when scaling
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // Note: GL_TEXTURE_RECTANGLE_ARB may be used instead of
  // GL_TEXTURE_2D for improved performance if linear interpolation is
  // not desired. Replace GL_LINEAR with GL_NEAREST in the
  // glTexParameteri() call

  // normally needed for deactivating but we will take release() later
  // glBindTexture(GL_TEXTURE_2D, 0);
}
//-----------------------------------------------------------------------------
// deleteTexture
//-----------------------------------------------------------------------------
void SimplePBO::deleteTexture()
{
  if(textureID){
    glDeleteTextures(1, textureID);
    delete[] textureID;
    textureID = 0;
  }
}
//-----------------------------------------------------------------------------
// bind
//-----------------------------------------------------------------------------
void SimplePBO::bind()
{
  Q_ASSERT(pixelBuffer);
  // Create a texture from the buffer
  pixelBuffer->bind();
  // bind texture from PBO
  glBindTexture(GL_TEXTURE_2D, textureID[0]);

  // Note: glTexSubImage2D will perform a format conversion if the
  // buffer is a different format from the texture. We created the
  // texture with format GL_RGBA8. In glTexSubImage2D we specified
  // GL_BGRA and GL_UNSIGNED_BYTE. This is a fast-path combination

  // Note: NULL indicates the data resides in device memory
  // hence data is coming from PBO
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image_width, image_height, 
		  GL_RGBA, GL_UNSIGNED_BYTE, NULL);
}
//-----------------------------------------------------------------------------
// release
//-----------------------------------------------------------------------------
void SimplePBO::release()
{
  Q_ASSERT(pixelBuffer);
  // deactivate pixelbuffer object
  pixelBuffer->release();
  // deactivate texture object
  glBindTexture(GL_TEXTURE_2D, 0);
}
//-----------------------------------------------------------------------------
// cleanupCuda
//-----------------------------------------------------------------------------
void SimplePBO::cleanupCuda()
{
  deletePBO();
  deleteTexture();
  HANDLE_ERROR( cudaThreadExit() );
}