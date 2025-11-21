#include "_obstacles.h"


_obstacles::_obstacles()
{
    x = y = z = 0.0f;
    rotationAngle = 0.0f;


    size = 1.0f;
    moveSpeed = 1.0f;


    mytime->reset();


    active = true;
}




_obstacles::~_obstacles()
{
    //dtor
}


void _obstacles::draw()
{
    if (!active) return;


    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotationAngle, 1, 1, 1);
    glScalef(size, size, size);
    glColor3f(1.0f, 0.5f, 0.0f);
    glutSolidCube(1.0f);
    glPopMatrix();


    rotationAngle += 0.5f;
    if(rotationAngle >= 360.0f)
        rotationAngle -= 360.0f;
}


void _obstacles::moveObstacle(string dir, float sceneSpeed)
{
    if (mytime->getTicks() > 40)
    {
        float finalSpeed = sceneSpeed * moveSpeed;


        if(dir == "left")  x -= finalSpeed;
        if(dir == "right") x += finalSpeed;
        if(dir == "up")    y += finalSpeed;
        if(dir == "down")  y -= finalSpeed;


        mytime->reset();
    }
}
