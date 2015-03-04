#include "texture.h"
#include "STBImage.h"

void loadTextureAtStage(char *fname, int stage) {
    GLuint texture;
    int width, height, bitsPerPixel;
    unsigned char *data = stbi_load(fname, &width, &height, &bitsPerPixel, 0);
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0+stage);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    stbi_image_free(data);
    
}