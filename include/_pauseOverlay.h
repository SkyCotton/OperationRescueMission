
#ifndef _PAUSEOVERLAY_H
#define _PAUSEOVERLAY_H


#include <GL/gl.h>
#include <iostream>
#include <SOIL2.h>
#include <cstring>
#include <_common.h>


class _pauseOverlay
{
public:
    _pauseOverlay();
    ~_pauseOverlay();


    void init();                    // load texture (call after GL context created)
    void draw(int screenWidth, int screenHeight);


private:
    GLuint texID;
};


#endif // _PAUSEOVERLAY_H
