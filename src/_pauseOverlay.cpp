#include "_pauseOverlay.h"


_pauseOverlay::_pauseOverlay() : texID(0)
{
}


_pauseOverlay::~_pauseOverlay()
{
    if (texID != 0)
        glDeleteTextures(1, &texID);
}


void _pauseOverlay::init()
{
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);


    int width, height;
    unsigned char* image = SOIL_load_image("images/pause.png", &width, &height, 0, SOIL_LOAD_RGBA);
    if (!image)
    {
        std::cout << "Pause texture failed to load!" << std::endl;
        return;
    }


    unsigned char* flipped = new unsigned char[width * height * 4];
    for (int y = 0; y < height; ++y)
        memcpy(flipped + (height - 1 - y) * width * 4, image + y * width * 4, width * 4);


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, flipped);
    SOIL_free_image_data(image);
    delete[] flipped;


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


void _pauseOverlay::draw(int screenWidth, int screenHeight)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);


    float quadW = screenWidth * 0.6f;
    float quadH = screenHeight * 0.5f;
    float x0 = (screenWidth - quadW) / 2.0f;
    float y0 = (screenHeight - quadH) / 2.0f;


    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(x0, y0);
        glTexCoord2f(1, 0); glVertex2f(x0 + quadW, y0);
        glTexCoord2f(1, 1); glVertex2f(x0 + quadW, y0 + quadH);
        glTexCoord2f(0, 1); glVertex2f(x0, y0 + quadH);
    glEnd();


    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);


    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
