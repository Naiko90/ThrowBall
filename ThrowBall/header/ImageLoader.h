#pragma once

#define ILUT_USE_OPENGL	// This must be defined before calling the DevIL headers or we don't get OpenGL functionality
#define GL_CLAMP_TO_EDGE 0x812F
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include <iostream>
#include <cstdlib>

using namespace std;

// Function load a image, turn it into a texture, and return the texture ID as a GLuint for use
GLuint loadImage(const char* theFileName, bool rotate);