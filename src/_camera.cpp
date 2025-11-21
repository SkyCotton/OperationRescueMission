#include "_camera.h"

_camera::_camera()
{
    //ctor
}

_camera::~_camera()
{
    //dtor
}
void _camera::camInit()
{
    eye.x =0.0f; eye.y =2.0f; eye.z =10.0f; // basically ensuring these are passed float literals
    des.x =0.0f; des.y =2.0f; des.z =-10.0f;
    up.x  =0; up.y  =1; up.z  =0;

    step =0.5;

    distance = sqrt(pow(eye.x-des.x,2)+pow(eye.y-des.y,2)+pow(eye.z-des.z,2));

    rotAngle.x =0;
    rotAngle.y =0;
}

void _camera::camReset()
{
    eye.x =0; eye.y =0; eye.z =10;
    des.x =0; des.y =0; des.z =0;
    up.x  =0; up.y  =1; up.z  =0;

    step =0.5;

    distance = sqrt(pow(eye.x-des.x,2)+pow(eye.y-des.y,2)+pow(eye.z-des.z,2));

    rotAngle.x =0;
    rotAngle.y =0;
}

void _camera::rotateXY()
{
    des.y = eye.y + distance * sin(rotAngle.y * PI / 180.0);

    double horizontal_distance = distance * cos(rotAngle.y * PI / 180.0);

    des.x = eye.x + horizontal_distance * sin(rotAngle.x * PI / 180.0);
    des.z = eye.z - horizontal_distance * cos(rotAngle.x * PI / 180.0); // - to match openGL
}

void _camera::rotateUP()
{

}

void _camera::camMoveFdBd(int dir) // dir is 1 for forward and -1 for backward
{
    double rad_yaw = rotAngle.x * PI /180.0;

    float dx = step * (float)sin(rad_yaw); // dx is delta x or change in x
    float dz = step * (float)cos(rad_yaw);
    // eye position update
    eye.x += dx * dir;
    eye.z -= dz * dir;
    // des update
    des.x += dx * dir;
    des.z -= dz * dir;
}
void _camera::camMoveLtRt(int dir) // dir is -1 for left and 1 for right
{
    double rad_yaw_offset = (rotAngle.x - 90.0) * PI / 180.0;

    float dx = step * (float)sin(rad_yaw_offset);
    float dz = step * (float)cos(rad_yaw_offset);
    // eye
    eye.x += dx * dir;
    eye.z -= dz * dir;
    // des
    des.x += dx * dir;
    des.z -= dz * dir;
}

void _camera::setUpCamera()
{
    gluLookAt(eye.x,eye.y,eye.z,
              des.x,des.y,des.z,
              up.x, up.y, up.z);
}
