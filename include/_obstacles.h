#ifndef _OBSTACLES_H
#define _OBSTACLES_H


#include<_common.h>
#include<_textureLoader.h>
#include<_timer.h>


class _obstacles
{
    public:
        _obstacles();
        virtual ~_obstacles();


        _textureLoader *btex = new _textureLoader();
        _timer *mytime = new _timer();


        void draw();
        //void moveObstacle(string);
        void moveObstacle(string dir, float sceneSpeed);
        float moveSpeed;
        float size;




        float x, y, z;
        float rotationAngle;


        bool active = true;




    protected:


    private:
};


#endif // _OBSTACLES_H
