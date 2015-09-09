#include <ImageLoader.h>

GLuint loadImage(const char* theFileName, bool rotate)
{
	ILuint imageID;				// Create a image ID as a ULuint

	GLuint textureID;			// Create a texture ID as a GLuint

	ILboolean success;			// Create a flag to keep track of success/failure

	ILenum error;				// Create a flag to keep track of the IL error state

	ilInit();					// Inizialize DevIL

	ilGenImages(1, &imageID); 		// Generate the image ID

	ilBindImage(imageID); 			// Bind the image

	success = ilLoadImage((const ILstring)theFileName); 	// Load the image file

	// If we managed to load the image, then we can start to do things with it...
	if (success)
	{
		// If the image is flipped (i.e. upside-down and mirrored, flip it the right way up!)
		ILinfo ImageInfo;
		iluGetImageInfo(&ImageInfo);
		if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
		{
			iluFlipImage();
		}

		// Rotation of 90° 
		if (rotate){
			iluFlipImage();
		}

		// ... then attempt to conver it.
		// NOTE: If your image contains alpha channel you can replace IL_RGB with IL_RGBA
		success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);

		// Quit out if we failed the conversion
		if (!success)
		{
			error = ilGetError();
			// Debug
			// cout << "Image conversion failed - IL reports error: " << error << endl;
			exit(-1);
		}

		// Generate a new texture
		glGenTextures(1, &textureID);

		// Bind the texture to a name
		glBindTexture(GL_TEXTURE_2D, textureID);

		// Set texture clamping method
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Set texture interpolation method to use linear interpolation (no MIPMAPS)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	

		// Specify the texture specification
		glTexImage2D(GL_TEXTURE_2D, 				// Type of texture
					 0,								// Pyramid level (for mip-mapping) - 0 is the top level
					 ilGetInteger(IL_IMAGE_BPP),	// Image colour depth
					 ilGetInteger(IL_IMAGE_WIDTH),	// Image width
					 ilGetInteger(IL_IMAGE_HEIGHT),	// Image height
					 0,								// Border width in pixels (can either be 1 or 0)
					 ilGetInteger(IL_IMAGE_FORMAT),	// Image format (i.e. RGB, RGBA, BGR etc.)
					 GL_UNSIGNED_BYTE,				// Image data type
					 ilGetData());					// The actual image data itself
 	}
  	else // If we failed to open the image file in the first place...
  	{
		error = ilGetError();
		// Debug
		// cout << "Image load failed - IL reports error: " << error << endl;
		exit(-1);
  	}

 	ilDeleteImages(1, &imageID); // Because we have already copied image data into texture data we can release memory used by image.

	// Debug
	// cout << "Texture creation successful." << endl;

	return textureID; // Return the GLuint to the texture so you can use it!
}