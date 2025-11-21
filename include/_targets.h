#ifndef _TARGETS_H
#define _TARGETS_H
#include<_common.h>
#include<GL/glut.h>
#include<stdlib.h> // rand()


class _targets
{
    public:
        _targets();
        virtual ~_targets();

        vec3 pos;
        float radius;
        float speed;
        bool live; // is the sphere still supposed to be rendered

        void initTarget();
        void drawTarget();
        void updateTarget();

    protected:

    private:
};

#endif // _TARGETS_H
