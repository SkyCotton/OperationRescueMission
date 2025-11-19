#ifndef _COLLISIONCHECK_H
#define _COLLISIONCHECK_H

#include<_common.h>

class _collisionCheck
{
    public:
        _collisionCheck();
        virtual ~_collisionCheck();

        bool isLinearCol(vec3 p1,vec3 p2);
        bool isRadialCol(vec2 p1,vec2 p2,float r1,float r2,float thrhld);//positions x,y , radius A,B, threshold
        bool isSphereCol(vec3 p1,vec3 p2,float r1,float r2,float thrhld);//positions x,y , radius A,B, threshold
        bool isPlanoCol(vec2 p1,vec2 p2);
        bool isCubicCol(vec3 p1,vec3 p2);


    protected:

    private:
};

#endif // _COLLISIONCHECK_H
