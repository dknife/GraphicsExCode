#include "texture.h"
#include "STBImage.h"

GLuint setTexture(char *filename) {
    int dummy;
    return setTexture(filename, &dummy, &dummy);
}

GLuint setTexture(char *filename, int *w, int *h) {
    GLuint texture;
    int width, height, bitsPerPixel;
    unsigned char *data = stbi_load(filename, &width, &height, &bitsPerPixel, 0);
    glGenTextures(0, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glEnable(GL_TEXTURE_2D);
    *w = width; *h = height;
    return texture;
}