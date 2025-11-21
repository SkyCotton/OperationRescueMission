#include "_bullets.h"


_bullets::_bullets()
{
    //ctor
    pos.x = pos.y = pos.z =0;
    t=0;
    src.x= src.y= src.z =0;
    des.x=0;
    des.y=20;
    des.z=-50;

    live= false;
}

_bullets::~_bullets()
{
    //dtor
}
void _bullets::iniBullet(char* filename) // mispelt function, just deal with it
{
   // if we use texture on bullets
}

void _bullets::drawBullet()
{
     if(!live) return;
     glDisable(GL_TEXTURE_2D); // only if you are using glut sphere
     glPushMatrix();
        glColor3f(1.0f, 1.0f, 0.0f); // bullet color
        glTranslatef(pos.x, pos.y, pos.z);
        glutSolidSphere(0.5, 20, 20); // 0.5 is radius
     glPopMatrix();
     glColor3f(1.0f, 1.0f, 1.0f);
     glEnable(GL_TEXTURE_2D);
}

void _bullets::bulletActions()
{
    if (!live)
    {
        actionTrigger = READY;
        return;
    }
    switch(actionTrigger)
    {
    case READY:
           pos.x=0;
           pos.y=0;
           pos.z=0;

           des.x =0;
           des.y= 0;
           des.z = 0;

           live =false;
           t=0;
        break;

    case SHOOT:   // applying parametric equation
                  // p = p1+t(p2-p1)
        if (live)
        {
            pos.x += velocity.x;
            pos.y += velocity.y;
            pos.z += velocity.z;

            float maxTravelDistSq = 200.0f * 200.0f;
            float distSq = pow(pos.x - src.x, 2) + pow(pos.y - src.y, 2) + pow(pos.z - src.z, 2);

            if (distSq > maxTravelDistSq)
            {
                live = false;
                actionTrigger = READY;
            }
        }
        break;

    case HIT:
        live = false;
        actionTrigger = READY;
        break;
    }
}
