#include "_targets.h"

_targets::_targets()
{
    live = false;
    radius = 1.5f;
    speed = 0.05f; // how fast the targets fall
}

_targets::~_targets()
{
    //dtor
}
void _targets::initTarget()
{
    live = true;
    pos.y = 1.0f;
    pos.x = (rand() % 60) - 30.0f; // random position within 10 units
    pos.z = (rand() % 60) - 30.0f;
}

void _targets::drawTarget()
{
    if (!live) return;

    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
        glColor3f(1.0, 0.0f, 0.0f);
        glTranslatef(pos.x, pos.y, pos.z);
        glutSolidSphere(radius, 20, 20); // the target itself, a sphere
    glPopMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
}
void _targets::updateTarget()
{
    if (!live) return;
    // makes targets "fall"
    /*
    pos.y -= speed;
    if (pos.y < 0.0f)
    {
        live = false;
    }
    */
}
