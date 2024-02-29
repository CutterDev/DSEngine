#include "Texture2D.h"

#include <iostream>

Texture2D::Texture2D()
    : Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_NEAREST), Filter_Max(GL_NEAREST)
{

}

void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
    glGenTextures(1, &this->ID);
    this->Width = width;
    this->Height = height;
    // create Texture

    glBindTexture(GL_TEXTURE_2D, this->ID);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);

    glTexImage2D(GL_TEXTURE_2D, 0,
        this->Internal_Format,
        width,
        height, 0,
        this->Image_Format,
        GL_UNSIGNED_BYTE,
        data);
    glBindTexture(GL_TEXTURE_2D, 0);
    std::cout << glGetError() << std::endl;
}

void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &ID);
}